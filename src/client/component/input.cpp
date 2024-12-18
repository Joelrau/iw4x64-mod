#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "game_console.hpp"

#include <utils/hook.hpp>

namespace input
{
	namespace
	{
		utils::hook::detour cl_char_event_hook;
		utils::hook::detour cl_key_event_hook;

		void cl_char_event_stub(const int local_client_num, const int key)
		{
			if (!game_console::console_char_event(local_client_num, key))
			{
				return;
			}

			cl_char_event_hook.invoke<void>(local_client_num, key);
		}

		void cl_key_event_stub(const int local_client_num, const int key, const int down)
		{
			if (!game_console::console_key_event(local_client_num, key, down))
			{
				return;
			}

			cl_key_event_hook.invoke<void>(local_client_num, key, down);
		}
	}

	class component final : public component_interface
	{
	public:
		void post_load() override
		{
			if (!game::environment::is_mp())
			{
				return;
			}

			cl_char_event_hook.create(0x1400EA8A0, cl_char_event_stub);
			cl_key_event_hook.create(0x1400EAA80, cl_key_event_stub);
		}
	};
}

REGISTER_COMPONENT(input::component)
