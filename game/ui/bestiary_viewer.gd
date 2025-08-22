extends Control

@onready var split: HSplitContainer = $HSplitContainer
@onready var list: ItemList         = $HSplitContainer/List
@onready var page: RichTextLabel    = $HSplitContainer/Page

var idx := BestiaryIndexResource.new()

func _ready() -> void:
	# Load data and populate list.
	var ok := idx.load_dir("res://data/bestiary")
	if not ok:
		push_error("Bestiary: failed to scan directory")
		return

	var entries: Array = idx.list_entries()
	entries.sort_custom(func(a, b): return String(a["name"]) < String(b["name"]))

	list.clear()
	for d in entries:
		var row := "%s  [%s]" % [String(d["name"]), String(d["type"])]
		var i := list.add_item(row)
		list.set_item_metadata(i, String(d["id_str"]))

	list.item_selected.connect(_on_item_selected)

	if entries.size() > 0:
		list.select(0)
		_on_item_selected(0)

func _on_item_selected(i: int) -> void:
	var id_str: String = list.get_item_metadata(i)
	var entry: BestiaryEntryResource = idx.load_entry_by_str_id(id_str)

	if entry != null:
		page.text = entry.format_bbcode()
	else:
		page.text = "Failed to load entry: %s" % id_str
