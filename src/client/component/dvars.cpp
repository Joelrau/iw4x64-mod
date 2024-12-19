#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "dvars.hpp"
#include "console.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include <utils/hook.hpp>

namespace dvars
{
	struct dvar_base
	{
		unsigned int flags{};
	};

	struct dvar_bool : dvar_base
	{
		bool value{};
	};

	struct dvar_float : dvar_base
	{
		float value{};
		float min{};
		float max{};
	};

	struct dvar_vector2 : dvar_base
	{
		float x{};
		float y{};
		float min{};
		float max{};
	};

	struct dvar_vector3 : dvar_base
	{
		float x{};
		float y{};
		float z{};
		float min{};
		float max{};
	};

	struct dvar_enum : dvar_base
	{
		const char* const* value_list{};
		int default_index{};
	};

	struct dvar_int : dvar_base
	{
		int value{};
		int min{};
		int max{};
	};

	struct dvar_string : dvar_base
	{
		std::string value{};
	};

	namespace
	{
		template <typename T>
		T* find_dvar(std::unordered_map<std::string, T>& map, const std::string& name)
		{
			auto i = map.find(name);
			if (i != map.end())
			{
				return &i->second;
			}

			return nullptr;
		}
		
		bool find_dvar(std::unordered_set<std::string>& set, const std::string& name)
		{
			return set.find(name) != set.end();
		}
	}

	namespace disable
	{
		static std::unordered_set<std::string> set_bool_disables;
		static std::unordered_set<std::string> set_float_disables;
		static std::unordered_set<std::string> set_int_disables;
		static std::unordered_set<std::string> set_string_disables;

		void set_bool(const std::string& name)
		{
			set_bool_disables.emplace(name);
		}

		void set_float(const std::string& name)
		{
			set_float_disables.emplace(name);
		}

		void set_int(const std::string& name)
		{
			set_int_disables.emplace(name);
		}

		void set_string(const std::string& name)
		{
			set_string_disables.emplace(name);
		}
	}

	namespace override
	{
		static std::unordered_map<std::string, dvar_bool> register_bool_overrides;
		static std::unordered_map<std::string, dvar_float> register_float_overrides;
		static std::unordered_map<std::string, dvar_int> register_int_overrides;
		static std::unordered_map<std::string, dvar_string> register_string_overrides;
		static std::unordered_map<std::string, dvar_vector2> register_vector2_overrides;
		static std::unordered_map<std::string, dvar_vector3> register_vector3_overrides;
		static std::unordered_map<std::string, dvar_enum> register_enum_overrides;

		static std::unordered_map<std::string, bool> set_bool_overrides;
		static std::unordered_map<std::string, float> set_float_overrides;
		static std::unordered_map<std::string, int> set_int_overrides;
		static std::unordered_map<std::string, std::string> set_string_overrides;
		static std::unordered_map<std::string, std::string> set_from_string_overrides;

		void register_bool(const std::string& name, const bool value, const unsigned int flags)
		{
			dvar_bool values;
			values.value = value;
			values.flags = flags;
			register_bool_overrides[name] = std::move(values);
		}

		void register_float(const std::string& name, const float value, const float min, const float max, 
			const unsigned int flags)
		{
			dvar_float values;
			values.value = value;
			values.min = min;
			values.max = max;
			values.flags = flags;
			register_float_overrides[name] = std::move(values);
		}

		void register_int(const std::string& name, const int value, const int min, const int max, 
			const unsigned int flags)
		{
			dvar_int values;
			values.value = value;
			values.min = min;
			values.max = max;
			values.flags = flags;
			register_int_overrides[name] = std::move(values);
		}

		void register_string(const std::string& name, const std::string& value, 
			const unsigned int flags)
		{
			dvar_string values;
			values.value = value;
			values.flags = flags;
			register_string_overrides[name] = std::move(values);
		}

		void register_vec2(const std::string& name, float x, float y, float min, float max, 
			const unsigned int flags)
		{
			dvar_vector2 values;
			values.x = x;
			values.y = y;
			values.min = min;
			values.max = max;
			values.flags = flags;
			register_vector2_overrides[name] = std::move(values);
		}

		void register_vec3(const std::string& name, float x, float y, float z, float min, 
			float max, const unsigned int flags)
		{
			dvar_vector3 values;
			values.x = x;
			values.y = y;
			values.z = z;
			values.min = min;
			values.max = max;
			values.flags = flags;
			register_vector3_overrides[name] = std::move(values);
		}

		void register_enum(const std::string& name, /*const char* const* value_list, int default_index,*/
			const unsigned int flags)
		{
			dvar_enum values;
			//values.value_list = value_list;
			//values.default_index = default_index;
			values.flags = flags;
			register_enum_overrides[name] = std::move(values);
		}

		void set_bool(const std::string& name, const bool value)
		{
			set_bool_overrides[name] = value;
		}

		void set_float(const std::string& name, const float value)
		{
			set_float_overrides[name] = value;
		}

		void set_int(const std::string& name, const int value)
		{
			set_int_overrides[name] = value;
		}

		void set_string(const std::string& name, const std::string& value)
		{
			set_string_overrides[name] = value;
		}
    
		void set_from_string(const std::string& name, const std::string& value)
		{
			set_from_string_overrides[name] = value;
		}
	}

	namespace callback
	{
		static std::unordered_map<const char*, std::function<void(game::dvar_value*)>> dvar_new_value_callbacks;

		static std::unordered_map<const char*, std::function<void()>> dvar_on_register_function_map;

		void on_new_value(const std::string& name, const std::function<void(game::dvar_value*)> callback)
		{
			dvar_new_value_callbacks[name.data()] = callback;
		}

		void on_register(const std::string& name, const std::function<void()>& callback)
		{
			dvar_on_register_function_map[name.data()] = callback;
		}
	}

	utils::hook::detour dvar_register_bool_hook;
	utils::hook::detour dvar_register_bool_hashed_hook;
	utils::hook::detour dvar_register_float_hook;
	utils::hook::detour dvar_register_float_hashed_hook;
	utils::hook::detour dvar_register_int_hook;
	utils::hook::detour dvar_register_int_hashed_hook;
	utils::hook::detour dvar_register_string_hook;
	utils::hook::detour dvar_register_vector2_hook;
	utils::hook::detour dvar_register_vector3_hook;
	utils::hook::detour dvar_register_enum_hook;

	utils::hook::detour dvar_register_new_hook;

	utils::hook::detour dvar_set_bool_hook;
	utils::hook::detour dvar_set_float_hook;
	utils::hook::detour dvar_set_int_hook;
	utils::hook::detour dvar_set_string_hook;
	utils::hook::detour dvar_set_from_string_hook;

	utils::hook::detour dvar_set_variant_hook;

	game::dvar_t* dvar_register_bool(const char* name, bool value, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_bool_overrides, name);
		if (var)
		{
			value = var->value;
			flags = var->flags;
		}

		return dvar_register_bool_hook.invoke<game::dvar_t*>(name, value, flags, desc);
	}
	
	game::dvar_t* dvar_register_float(const char* name, float value, float min, float max, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_float_overrides, name);
		if (var)
		{
			value = var->value;
			min = var->min;
			max = var->max;
			flags = var->flags;
		}

		return dvar_register_float_hook.invoke<game::dvar_t*>(name, value, min, max, flags, desc);
	}
	
	game::dvar_t* dvar_register_int(const char* name, int value, int min, int max, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_int_overrides, name);
		if (var)
		{
			value = var->value;
			min = var->min;
			max = var->max;
			flags = var->flags;
		}

		return dvar_register_int_hook.invoke<game::dvar_t*>(name, value, min, max, flags, desc);
	}

	game::dvar_t* dvar_register_string(const char* name, const char* value, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_string_overrides, name);
		if (var)
		{
			value = var->value.data();
			flags = var->flags;
		}

		return dvar_register_string_hook.invoke<game::dvar_t*>(name, value, flags, desc);
	}

	game::dvar_t* dvar_register_vector2(const char* name, float x, float y, float min, float max,
		                                unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_vector2_overrides, name);
		if (var)
		{
			x = var->x;
			y = var->y;
			min = var->min;
			max = var->max;
			flags = var->flags;
		}

		return dvar_register_vector2_hook.invoke<game::dvar_t*>(name, x, y, min, max, flags, desc);
	}

	game::dvar_t* dvar_register_vector3(const char* name, float x, float y, float z, float min,
		                                float max, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_vector3_overrides, name);
		if (var)
		{
			x = var->x;
			y = var->y;
			z = var->z;
			min = var->min;
			max = var->max;
			flags = var->flags;
		}

		return dvar_register_vector3_hook.invoke<game::dvar_t*>(name, x, y, z, min, max, flags, desc);
	}

	game::dvar_t* dvar_register_enum(const char* name, const char* const value_list, int default_index, unsigned int flags, const char* desc)
	{
		auto* var = find_dvar(override::register_enum_overrides, name);
		if (var)
		{
			//value_list = var->value_list;
			//default_index = var->default_index;
			flags = var->flags;
		}

		return dvar_register_enum_hook.invoke<game::dvar_t*>(name, value_list, default_index, flags, desc);
	}

	game::dvar_t* dvar_register_new(const char* name, game::dvar_type type, unsigned int flags,
		game::dvar_value* value, game::dvar_limits* domain, const char* description)
	{
		auto* dvar = dvar_register_new_hook.invoke<game::dvar_t*>(name, type, flags, value, domain, description);

		if (dvar && callback::dvar_on_register_function_map.find(name) != callback::dvar_on_register_function_map.end())
		{
			callback::dvar_on_register_function_map[name]();
			callback::dvar_on_register_function_map.erase(name);
		}

		return dvar;
	}
	
	class component final : public component_interface
	{
	public:
		void post_load() override
		{
			dvar_register_bool_hook.create(game::Dvar_RegisterBool, &dvar_register_bool);
			dvar_register_float_hook.create(game::Dvar_RegisterFloat, &dvar_register_float);
			dvar_register_int_hook.create(game::Dvar_RegisterInt, &dvar_register_int);
			dvar_register_string_hook.create(game::Dvar_RegisterString, &dvar_register_string);
			// dvar_register_vector2_hook.create(SELECT_VALUE(0x4198C0_b, 0x182CB0_b), &dvar_register_vector2);
			// dvar_register_vector3_hook.create(SELECT_VALUE(0x419A00_b, 0x182DB0_b), &dvar_register_vector3);
			// dvar_register_enum_hook.create(SELECT_VALUE(0x419500_b, 0x182700_b), &dvar_register_enum);
			//
			// dvar_register_new_hook.create(SELECT_VALUE(0x41B1D0_b, 0x184DF0_b), &dvar_register_new);
		}
	};
}

REGISTER_COMPONENT(dvars::component)
