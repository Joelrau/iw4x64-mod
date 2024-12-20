#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <game/game.hpp>

#include <utils/hook.hpp>
#include <utils/string.hpp>

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
	}

	class component final : public component_interface
	{
	public:
		void post_load() override
		{
			relaunch_hook.create(SELECT_VALUE(0x140295D20, 0x1402A8D20), relaunch_stub);

			if (game::environment::is_sp())
				return;

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

			patch_mp();
		}

		static void patch_mp()
		{
			dvars::override::register_string("sv_hostname", "^2IW4x64-Mod^7 Default Server", game::DVAR_CODINFO);
		}
	};
}

REGISTER_COMPONENT(patches::component)
