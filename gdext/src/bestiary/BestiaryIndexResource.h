// gdnext/src/bestiary/BestiaryIndexResource.h

#ifndef BESTIARY_INDEX_RESSOURCE_H
# define BESTIARY_INDEX_RESSOURCE_H

# include "godot_includes.h"

# include <map>
# include <string>

namespace godot
{
	class BestiaryEntryResource;

	class BestiaryIndexResource : public Resource
	{
		GDCLASS(BestiaryIndexResource, Resource)

		struct Meta {
			String	id_str;
			String	name;
			String	type;
			String	threat;
			String	json_path_res;	// res:// path
			String	json_path_abs;	// OS path
		};

		std::map<String, Meta>	by_id_;

		protected:
			static void	_bind_methods(void);

		public:
			BestiaryIndexResource(void);
			~BestiaryIndexResource(void);

			// Scan a res:// directory for *.json bestiary files and index them
			bool	load_dir(const String &res_dir);

			// List as Array<Dictionary> for UI
			TypedArray<Dictionary>	list_entries(void) const;

			// Load one entry as a BestiaryEntryResource by string id
		    Ref<class BestiaryEntryResource> load_entry_by_str_id(const String &id_str) const;

			// Helpers
			int	size(void) const;
		};

} // namespace godot

#endif // BESTIARY_INDEX_RESSOURCE_H
