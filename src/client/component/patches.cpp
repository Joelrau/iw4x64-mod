#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <game/game.hpp>

#include <utils/hook.hpp>
#include <utils/string.hpp>

#include "console.hpp"
#include "dvars.hpp"

namespace patches
{
	namespace
	{
		std::string GetExecutableName()
		{
			char path[MAX_PATH];
			if (GetModuleFileNameA(NULL, path, MAX_PATH) > 0)
			{
				std::string fullPath(path);
				size_t pos = fullPath.find_last_of("\\/");
				return (pos == std::string::npos) ? fullPath : fullPath.substr(pos + 1);
			}
			return "";
		}

		utils::hook::detour relaunch_hook;
		void relaunch_stub(const char* filename, const char* params)
		{
			if (filename == "iw4sp.exe"s || filename == "iw4mp.exe"s)
			{
				static char buf[MAX_PATH];
				memset(buf, 0, sizeof(buf));
				
				auto exe_name = GetExecutableName();
				assert(exe_name.size() < MAX_PATH);
				memcpy(buf, exe_name.data(), exe_name.size());
				
				filename = buf;

				params = utils::string::va("%s -%s", params, game::environment::is_sp() ? "mp" : "sp");

				relaunch_hook.invoke<void>(filename, params);
				return;
			}

			relaunch_hook.invoke<void>(filename, params);
		}

		utils::hook::detour alt_tab_hook;
		bool alt_tab_stub()
		{
			return true;	
		}

		utils::hook::detour com_error_hook;
		void com_error_stub(const int error, const char* msg, ...)
		{
			char buffer[2048]{};
			va_list ap;

			va_start(ap, msg);
			vsnprintf_s(buffer, _TRUNCATE, msg, ap);
			va_end(ap);

			console::error("Error: %s\n", buffer);

			com_error_hook.invoke<void>(error, "%s", buffer);
		}
	}

	class component final : public component_interface
	{
	public:
		void post_load() override
		{
			relaunch_hook.create(SELECT_VALUE(0x140295D20, 0x1402A8D20), relaunch_stub);

			if (game::environment::is_sp())
				return;

			patch_mp();
		}

		static void patch_mp()
		{
			alt_tab_hook.create(0x1402A7C10, alt_tab_stub);

			utils::hook::copy_string(0x14040B020, "IW4x64-Mod Multiplayer");

			dvars::override::register_float("cg_fov", 65.f, 40.f, 200.f, game::DvarFlags::DVAR_SAVED);
			dvars::override::register_float("cg_fovScale", 1.f, 0.1f, 2.f, game::DvarFlags::DVAR_SAVED);
			dvars::override::register_float("cg_fovMin", 1.f, 1.0f, 90.f, game::DvarFlags::DVAR_SAVED);
			
			if (game::environment::is_dedi())
			{
				dvars::override::register_int("com_maxfps", 85, 0, 100, game::DVAR_NONE);
			}
			else
			{
				dvars::override::register_int("com_maxfps", 0, 0, 1000, game::DVAR_SAVED);
			}
			
			dvars::override::register_string("sv_hostname", "^2IW4x64-Mod^7 Default Server", game::DVAR_CODINFO);

			com_error_hook.create(game::Com_Error, com_error_stub);
		}
	};
}

REGISTER_COMPONENT(patches::component)
