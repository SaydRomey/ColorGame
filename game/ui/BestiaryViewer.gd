extends Control

@onready var split: HSplitContainer = $HSplitContainer
@onready var list: ItemList         = $HSplitContainer/List
@onready var page: RichTextLabel    = $HSplitContainer/Page

var index := BestiaryIndexResource.new()

# Toggle these if you want console output:
#const DEBUG_PRINT_LIST := false
#const DEBUG_PRINT_SELECTED := false
const DEBUG_PRINT_LIST := true
const DEBUG_PRINT_SELECTED := true

func _ready() -> void:
	## Stretch to window (keeps things from cramming top-left).
	#anchor_left = 0.0;  anchor_top = 0.0
	#anchor_right = 1.0; anchor_bottom = 1.0
	#offset_left = 0.0;  offset_top = 0.0
	#offset_right = 0.0; offset_bottom = 0.0
#
	#split.anchor_left = 0.0;  split.anchor_top = 0.0
	#split.anchor_right = 1.0; split.anchor_bottom = 1.0
	#split.offset_left = 0.0;  split.offset_top = 0.0
	#split.offset_right = 0.0; split.offset_bottom = 0.0
#
	## Make children expand nicely.
	#for c in [split, list, page]:
		#c.size_flags_horizontal = Control.SIZE_EXPAND_FILL
		#c.size_flags_vertical   = Control.SIZE_EXPAND_FILL
#
	## RichText settings
	#page.bbcode_enabled = true
	#page.autowrap_mode  = TextServer.AUTOWRAP_WORD_SMART
	#page.scroll_active  = true

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
