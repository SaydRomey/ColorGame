extends Control

const VIEWER_SCENE := preload("res://ui/BestiaryViewer.tscn")

func _ready() -> void:
	var viewer: Control = VIEWER_SCENE.instantiate()
	add_child(viewer)
	viewer.set_anchors_preset(Control.PRESET_FULL_RECT)

	## Make it act like a root Control that fills the screen.
	#viewer.top_level = true
	#viewer.position = Vector2.ZERO
	#viewer.size = get_viewport().get_visible_rect().size
#
	## Keep it filling when window resizes.
	#get_viewport().size_changed.connect(func():
		#viewer.size = get_viewport().get_visible_rect().size
	#)


#var index := BestiaryIndexResource.new()
#
#func _ready():
	#print("Main ready")
	#
	#var ok := index.load_dir("res://data/bestiary") # confirm the dir exists
	#print("Index load: ", ok, " entries=", index.size())
#
	 ## Assuming our JSON files live under: game/data/bestiary/*.json
	#if not index.load_dir("res://data/bestiary"):
		#push_error("Failed to load bestiary dir")
		#return
#
	#var entries := index.list_entries()
	#for d in entries:
		#print("[", d.id_str, "] ", d.name, " (", d.type, ")")
#
	#if entries.size() > 0:
		#var id_str : String = entries[0].id_str
		#var entry: BestiaryEntryResource = index.load_entry_by_str_id(id_str)
		#if entry:
			#print(entry.format_console())
