#include "std_include.hpp"

#include "command.hpp"
#include "console.hpp"
#include "scheduler.hpp"
#include "game/game.hpp"
#include "loader/component_loader.hpp"
#include "utils/hook.hpp"

namespace stats
{
    namespace
    {

        void unlock_all()
        {
            if (game::CL_IsCgameInitialized())
            {
                console::error("Not allowed whilst in-game.");
                return;
            }
            
            game::LiveStorage_PlayerDataSetIntByName(0, "prestige", 10);
            game::LiveStorage_PlayerDataSetIntByName(0, "experience", 2516000);
            
            const char* nav_strings[2]{};
            nav_strings[0] = "iconUnlocked";
            nav_strings[1] = "cardicon_prestige10_02";

            const char* buffer_data = game::LiveStorage_GetBufferData(0);
            game::LiveStorage_DataSetInternalString(nav_strings, 2, "1", &buffer_data, 0);

            if (game::StringTable* challenge_table = game::DB_FindXAssetHeader(game::XAssetType::ASSET_TYPE_STRINGTABLE, "mp/allchallengestable.csv").stringTable)
            {
                for (int i = 0; i < challenge_table->rowCount; ++i)
                {
                    const char* challenge = game::TableLookup(challenge_table, i, 0);

                    int max_state = 0;
                    int max_progress = 0;
                    
                    for (int j = 0; j < 10; ++j)
                    {
                        const int progress = atoi(game::TableLookup(challenge_table, i, 6 + j * 2));
                        if (!progress) break;

                        max_state = j + 2;
                        max_progress = progress;
                    }
                    
                    nav_strings[0] = "challengeState";
                    nav_strings[1] = challenge;

                    game::LiveStorage_DataSetInternalString(nav_strings, 2, std::to_string(max_state).data(), &buffer_data, 0);
                    nav_strings[0] = "challengeProgress";
                    game::LiveStorage_DataSetInternalString(nav_strings, 2, std::to_string(max_progress).data(), &buffer_data, 0);
                }
            }
            
            game::LiveStorage_WriteStats(0);
        }
    }

    
    class component final : public component_interface
    {
        public:
        void post_load() override
        {
            scheduler::once([]()
            {
                command::add("unlockall", [&]()
                {
                    unlock_all();
                });
            }, scheduler::main);
        }
    };
}

REGISTER_COMPONENT(stats::component);