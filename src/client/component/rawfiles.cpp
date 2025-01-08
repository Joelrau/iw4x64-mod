#include "std_include.hpp"

#include "command.hpp"
#include "game/game.hpp"
#include "loader/component_loader.hpp"
#include "utils/io.hpp"
#include "utils/string.hpp"

namespace rawfiles
{

    namespace
    {
        
    }
    
    class component final : public component_interface
    {
        public:
        void post_load() override
        {
            command::add("rawFileDump", []()
            {
                game::DB_EnumXAssetEntries(game::XAssetType::ASSET_TYPE_RAWFILE, [&](game::XAssetEntry* entry)
                {
                    auto asset = entry->asset.header.rawFile;

                    if (asset != nullptr)
                    {
                        const auto* data = game::Scr_AddSourceBuffer(nullptr, asset->name);
                        
                        std::string filename = utils::string::to_lower(asset->name);
                        utils::io::write_file(utils::string::va("raw/dump/rawfile/%s", filename.c_str()), data, false);
                    }
                }, true);
            });

        }
    };
}

REGISTER_COMPONENT(rawfiles::component);