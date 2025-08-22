# res://test_loader.gd
extends SceneTree

func _initialize() -> void:
	print("test_loader: start")

	var idx: BestiaryIndexResource = BestiaryIndexResource.new()
	var ok: bool = idx.load_dir("res://data/bestiary")
	print("load_dir=", ok, " size=", idx.size())

	var L: Array = idx.list_entries()
	print("entries: ", L.size())

	if L.is_empty():
		quit(1)
		return

	var first: Dictionary = L[0]

	# Cast to String (fixes the “Cannot infer type” error)
	var id_str: String = String(first.get("id_str", ""))

	print("first id_str: ", id_str)

	var entry: BestiaryEntryResource = idx.load_entry_by_str_id(id_str)
	if entry:
		print(entry.format_console())
	else:
		print("failed to load entry: ", id_str)

	quit()
