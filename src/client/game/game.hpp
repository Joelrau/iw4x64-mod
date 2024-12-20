#pragma once

#include "structs.hpp"

#define PROTOCOL 1

#define SELECT_VALUE(sp, mp) (game::environment::is_sp() ? (sp) : (mp))

namespace game
{
	extern uint64_t base_address;

	template <typename T>
	class symbol
	{
	public:
		symbol(const size_t address)
			: address_(reinterpret_cast<T*>(address))
		{
		}

		T* get() const
		{
			return reinterpret_cast<T*>(reinterpret_cast<uint64_t>(address_));
		}

		operator T* () const
		{
			return this->get();
		}

		T* operator->() const
		{
			return this->get();
		}

	private:
		T* address_;
	};

	namespace environment
	{
		enum mode
		{
			none,
			sp,
			mp,
			dedi,
		};

		bool is_sp();
		bool is_mp();
		bool is_dedi();
		void set_mode(mode mode);
	}
	
	int Cmd_Argc();
	void DB_EnumXAssetEntries(XAssetType type, std::function<void(XAssetEntry*)> callback, bool overrides);
	const char* TableLookup(StringTable* stringtable, int row, int column);
}

size_t reverse_b(const size_t ptr);
size_t reverse_b(const void* ptr);

#include "symbols.hpp"
