#include <std_include.hpp>
#include "game.hpp"

#include <utils/flags.hpp>
#include <utils/string.hpp>
#include <utils/io.hpp>

namespace game
{
	int Cmd_Argc()
	{
		return cmd_args->argc[cmd_args->nesting];
	}

	void DB_EnumXAssetEntries(XAssetType type, std::function<void(XAssetEntry*)> callback, bool overrides)
	{
		auto hash = &game::db_hashTable[0];
		for (auto c = 0; c < 37000; c++)
		{
			for (auto i = *hash; i; )
			{
				const auto entry = &game::EntryPool[i];

				if (entry->asset.type == type)
				{
					callback(entry);

					if (overrides && entry->nextOverride)
					{
						auto next_ovveride = entry->nextOverride;
						while (next_ovveride)
						{
							const auto override = &game::EntryPool[next_ovveride];
							callback(override);
							next_ovveride = override->nextOverride;
						}
					}
				}

				i = entry->nextHash;
			}

			++hash;
		}
	}

	const char* TableLookup(StringTable* stringtable, int row, int column)
	{
		if (!stringtable || !stringtable->values || row >= stringtable->rowCount || column >= stringtable->columnCount) return "";

		const char* value = stringtable->values[row * stringtable->columnCount + column].string;
		if (!value) value = "";

		return value;
	}
	
	uint64_t base_address;

	namespace environment
	{
		mode mode_{none};

		bool is_sp()
		{
			return mode_ == sp;
		}

		bool is_mp()
		{
			return mode_ == mp;
		}

		bool is_dedi()
		{
			return mode_ == dedi;
		}

		void set_mode(mode mode)
		{
			mode_ = mode;
		}
	}
}

size_t reverse_b(const size_t ptr)
{
	return ptr - game::base_address;
}

size_t reverse_b(const void* ptr)
{
	return reverse_b(reinterpret_cast<size_t>(ptr));
}
