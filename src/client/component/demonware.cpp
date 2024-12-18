#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <utils/hook.hpp>
#include <utils/nt.hpp>

#include "game/game.hpp"

namespace demonware
{
	namespace
	{
		void bd_logger_stub(int /*type*/, const char* const /*channelName*/, const char*, const char* const /*file*/,
		                    const char* const function, const unsigned int /*line*/, const char* const msg, ...)
		{		
			static const auto* bd_logger_enabled = game::Dvar_RegisterBool("bd_logger_enabled", false, game::DVAR_NONE, "Enable logging of DemonWare Services");
			if (!bd_logger_enabled->current.enabled)
			{
				return;
			}

			char buffer[2048]{};

			va_list ap;
			va_start(ap, msg);

			vsnprintf_s(buffer, _TRUNCATE, msg, ap);
			printf("%s: %s\n", function, buffer);
			va_end(ap);
		}
	}

	class component final : public component_interface
	{
	public:
		void post_load() override
		{			
			if (game::environment::is_mp())
			{
				utils::hook::jump(0x140331F60, bd_logger_stub);
			}
		}
	};
}

REGISTER_COMPONENT(demonware::component)