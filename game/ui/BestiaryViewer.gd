extends Control

@onready var split: HSplitContainer = $HSplitContainer
@onready var list: ItemList         = $HSplitContainer/List
@onready var page: RichTextLabel    = $HSplitContainer/Page

var index := BestiaryIndexResource.new()

# Toggle these if we want console output:
const DEBUG_PRINT_LIST := false
const DEBUG_PRINT_SELECTED := false

func _ready() -> void:
	# 1) Load data
	## Assuming our JSON files live under: game/data/bestiary/*.json
	var ok : bool = index.load_dir("res://data/bestiary")
	if not ok:
		push_error("Bestiary: failed to scan directory")
		return

	# 2) Fetch & sort entries
	var entries: Array = index.list_entries()
	entries.sort_custom(self._cmp_by_name)

	if DEBUG_PRINT_LIST:
		BestiaryDebug.print_index_summary(entries)

	# 3) Populate the list
	list.clear()
	for d in entries:
		var row := "%s  [%s]" % [String(d.get("name", "")), String(d.get("type", ""))]
		var i := list.add_item(row)
		list.set_item_metadata(i, String(d.get("id_str", "")))

	list.item_selected.connect(_on_item_selected)

	# Default select first
	if entries.size() > 0:
		list.select(0)
		_on_item_selected(0)

func _cmp_by_name(a: Dictionary, b: Dictionary) -> bool:
	# Return true if a < b
	return String(a.get("name", "")) < String(b.get("name", ""))

func _on_item_selected(i: int) -> void:
	var id_str: String = list.get_item_metadata(i)
	var entry: BestiaryEntryResource = index.load_entry_by_str_id(id_str)

	if entry != null:
		if DEBUG_PRINT_SELECTED:
			BestiaryDebug.print_entry_console(entry)
		page.text = entry.format_bbcode()
	else:
		page.text = "Failed to load entry: %s" % id_str
