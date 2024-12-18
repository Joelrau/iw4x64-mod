#include "std_include.hpp"

#include "game/game.hpp"
#include "game/symbols.hpp"
#include "loader/component_loader.hpp"
#include "utils/hook.hpp"

namespace name
{
    utils::hook::detour Com_PlayerName_Hook;
    utils::hook::detour Live_GetLocalClientName_Hook;
    namespace
    {
        const char* GetPlayerDvarName()
        {
            const auto nameDvar = game::Dvar_FindVar("name");
            if (!nameDvar || nameDvar->current.string == nullptr || !strcmp(nameDvar->current.string, ""))
                return "Unknown Soldier";

            return nameDvar->current.string;
        }
        
        const char* GetPlayerName(int _)
        {
            return GetPlayerDvarName();
        }
    }
    
    class component final : public component_interface
    {
    public:
        void post_load() override
         {
            if (!game::environment::is_mp())
                return;
            
            Com_PlayerName_Hook.create(0x1401B59D0, &GetPlayerName);
            Live_GetLocalClientName_Hook.create(0x1402A6780, &GetPlayerName);
         }
    };
}

REGISTER_COMPONENT(name::component);