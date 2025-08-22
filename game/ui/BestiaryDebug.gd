extends Object
class_name BestiaryDebug

static func print_index_summary(entries: Array) -> void:
	for d in entries:
		print("[", d.get("id_str", "?"), "] ", d.get("name", ""), " (", d.get("type", ""), ")")

static func print_entry_console(entry: BestiaryEntryResource) -> void:
	# Calls your C++ formatter and prints to Output
	print(entry.format_console())
