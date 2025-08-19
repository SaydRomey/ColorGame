// gdext/src/bestiary/BestiaryEntryResource.h

#ifndef BESTIARY_ENTRY_RESSOURCE_H
# define BESTIARY_ENTRY_RESSOURCE_H

# include "godot_includes.h"
# include "BeastJsonLoader.hpp"

# include <string>


namespace godot
{
	class BestiaryEntryResource : public Resource
	{
		GDCLASS(BestiaryEntryResource, Resource)

		// Raw data loaded from JSON
		private:
			BeastData	_data;
			String		_source_path;

		protected:
			static void					_bind_methods();

			static String				to_gd(const std::string &s);
			static PackedStringArray	to_gd(const std::vector<std::string> &v);

		public:
			BestiaryEntryResource(void);
			~BestiaryEntryResource(void);

			// Load one JSON file into _data
			bool				load_from_file(const String &path);

			// Read-only getters exposed to GDScript/Inspector
			String				get_id(void) const;

			// Entry section
			String				get_name(void) const;
			String				get_type(void) const;
			String				get_threat_level(void) const;
			String				get_first_emerged(void) const;
			String				get_description(void) const;
			String				get_hue_interaction(void) const;
			String				get_behavior(void) const;
			String				get_weaknesses(void) const;
			String				get_notes(void) const;

			// Lore section
			String				get_lore_title(void) const;
			String				get_lore_quote(void) const;
			PackedStringArray	get_lore_flavor_description(void) const;
			PackedStringArray	get_lore_field_notes(void) const;
			String				get_lore_source(void) const;

			// Drops
			PackedStringArray	get_drops(void) const;

			// Source path
			String				get_source_path(void) const;

			// Expose the raw JSON fields for UI binding
			const BeastData& 	get_raw(void) const;

			// test: page formatter
			String	format_console() const;
			
	};
} // namespace godot

#endif // BESTIARY_ENTRY_RESSOURCE_H
