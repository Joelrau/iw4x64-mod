#include "std_include.hpp"

#include "script.hpp"
#include "game/game.hpp"

#include "component/console.hpp"
#include "loader/component_loader.hpp"
#include "utils/hook.hpp"
#include "utils/io.hpp"
#include "utils/string.hpp"

namespace gsc_script
{
    std::unordered_map<std::string, int> script_main_handles{};
    std::unordered_map<std::string, int> script_int_handles{};
    
    namespace
    {
        void scr_load_game_type_stub()
        {
            for (const auto& [fst, snd] : script_main_handles)
            {
                console::info("Executing '%s::main'\n", fst.data());
                const auto id = game::Scr_ExecThread(snd, 0);
                game::Scr_FreeThread(static_cast<std::uint16_t>(id));
            }

            game::Scr_LoadGameType();
        }

        void scr_startup_game_type_stub()
        {
            for (const auto& [fst, snd] : script_int_handles)
            {
                console::info("Executing '%s::init'\n", fst.data());

                const auto id = game::Scr_ExecThread(snd, 0);
                game::Scr_FreeThread(static_cast<std::uint16_t>(id));
            }

            game::Scr_StartupGameType();
        }

        void load_custom_scripts_from_folder(const char* dir)
        {
            char path[256]{};
            char searchPath[256]{};

            strncpy_s(searchPath, dir, _TRUNCATE);
            strncat_s(searchPath, "/", _TRUNCATE);

            auto numFiles = 0;
            const auto** files = game::FS_ListFiles(searchPath, "gsc", game::FS_LIST_ALL, &numFiles, 10);

            for (auto i = 0; i < numFiles; ++i)
            {
                const auto* script_file = files[i];
                console::info("Loading script %s...\n", script_file);

                const auto len = sprintf_s(path, "%s/%s", dir, script_file);
                if (len == -1)
                {
                    continue;
                }

                // Scr_LoadScriptInternal will add the '.gsc' suffix so we remove it
                path[len - 4] = '\0';
                
                if (!game::Scr_LoadScript(path))
                {
                    console::info("Script %s encountered an error while loading. A compilation error is the most likely cause\n", path);
                    continue;
                }

                console::info("Script %s.gsc loaded successfully.\n", path);

                if (const auto init_handle = game::Scr_GetFunctionHandle(path, "init"); init_handle != 0)
                {
                    console::debug("Loaded '%s::init'", path);
                    script_int_handles.insert_or_assign(path, init_handle);
                }

                if (const auto main_handle = game::Scr_GetFunctionHandle(path, "main"); main_handle != 0)
                {
                    console::debug("Loaded '%s::main'", path);
                    script_main_handles.insert_or_assign(path, main_handle);
                }
            }

            game::FSFreeFileList(files, 10);
        }

        void load_custom_scripts()
        {
            load_custom_scripts_from_folder("scripts");

            // Game specific
            const auto* gameDir = "scripts/mp";
            load_custom_scripts_from_folder(gameDir);

            // Map specific
            auto mapname = game::Dvar_FindVar("mapname");
            const auto* mapDir = utils::string::va("scripts/mp/%s", mapname->current.string);
            load_custom_scripts_from_folder(mapDir);

            // Mode specific
            auto g_gametype = game::Dvar_FindVar("g_gametype");
            const auto* modeDir = utils::string::va("scripts/mp/%s", g_gametype->current.string);
            load_custom_scripts_from_folder(modeDir);
        }

        void gscr_load_game_type_script_stub()
        {
            game::GScr_LoadGameTypeScript();
            script_main_handles.clear();
            script_int_handles.clear();
            load_custom_scripts();
        }

        const char* scr_read_file_load_obj([[maybe_unused]] const char* ext_filename)
        {
            std::string buffer = utils::io::read_file(ext_filename);
            *game::g_loadedImpureScript = true;
            return utils::string::va("%s", buffer.c_str());
        }

        utils::hook::detour scr_add_source_buffer_hook;
        const char* scr_add_source_buffer_stub(const char* filename, const char* ext_filename)
        {
            auto file_path = utils::string::va("raw/%s", ext_filename);
            console::debug("checking for %s\n", file_path);
            if (utils::io::file_exists(file_path))
            {
                return scr_read_file_load_obj(file_path);
            }
            
            auto* rawfile = game::DB_FindXAssetHeader(game::ASSET_TYPE_RAWFILE, ext_filename).rawFile;
            if (rawfile == nullptr)
            {
                return nullptr;
            }
                
            const auto len = game::DB_GetRawFileLen(rawfile);
            auto* source_buf = static_cast<char*>(game::Hunk_AllocateTempMemoryHigh(len));
            game::DB_GetRawBuffer(rawfile, source_buf, len);
            return source_buf;
        }
    }
    
    class component final : public component_interface
    {
        public:
        void post_load() override
        {
            utils::hook::set<std::uint8_t>(0x1401AAD42, 0xEB);

            utils::hook::call(0x1401A1C38, scr_load_game_type_stub);
            utils::hook::call(0x1401A1C42, scr_startup_game_type_stub);

            utils::hook::call(0x1401AB421, gscr_load_game_type_script_stub);

            scr_add_source_buffer_hook.create(game::Scr_AddSourceBuffer, scr_add_source_buffer_stub);
        }
    };
}

REGISTER_COMPONENT(gsc_script::component);
