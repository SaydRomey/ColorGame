
#

## Compile our loader as a GDExtension

BestiaryExtension.cpp:
```cpp
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

#include "BeastRegistry.hpp"          // ← our existing code

using namespace godot;

/* Thin wrapper that exposes a BestiaryRegistry to GDScript */
class BestiaryRegistryGD : public Object {
		GDCLASS(BestiaryRegistryGD, Object);

		BeastRegistry _reg;

protected:
		static void _bind_methods() {
				ClassDB::bind_method(D_METHOD("load_dir", "path"), &BestiaryRegistryGD::load_dir);
				ClassDB::bind_method(D_METHOD("get_ids"), &BestiaryRegistryGD::get_ids);
				ClassDB::bind_method(D_METHOD("get_beast", "id"), &BestiaryRegistryGD::get_beast);
		}

public:
		bool load_dir(String path) { return _reg.loadMetadataDirectory(path.utf8().get_data()); }

		/* Return an Array of StringNames (“BEAST_…”) */
		Array get_ids() const {
				Array ids;
				for (int i = 0; i < BESTIARY_ID_COUNT; ++i)
						if (_reg.getMetadata(static_cast<BestiaryID>(i)))
								ids.push_back(String("BEAST_") + itos(i)); // any stable naming scheme
				return ids;
		}

		/* Returned as a Dictionary to GDScript */
		Dictionary get_beast(String id_name) {
				Dictionary d;
				try {
						BestiaryID id = toBestiaryID(id_name.utf8().get_data());
						if (Beast *b = _reg.getBeast(id)) {
								d["name"]          = b->getName().c_str();
								d["type"]          = _reg.getMetadata(id)->type.c_str();
								d["threat_level"]  = _reg.getMetadata(id)->threat.c_str();
								d["description"]   = b->getDescription().c_str();
								d["quote"]         = b->getLoreQuote().c_str();
								Array notes;
								for (auto &n : b->getLoreNotes()) notes.push_back(String(n.c_str()));
								d["notes"] = notes;
						}
				} catch (...) {}          // simply return an empty dict on failure
				return d;
		}
};

/* Boilerplate */
void initialize_bestiary_extension(ModuleInitializationLevel p_level) {
		if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
				ClassDB::register_class<BestiaryRegistryGD>();
}
void uninitialize_bestiary_extension(ModuleInitializationLevel) {}
extern "C" {
GDExtensionBool GDE_EXPORT bestiary_library_init(const GDExtensionInterface *p_iface,
												 GDExtensionClassLibraryPtr  p_library,
												 GDExtensionInitialization   *r_init) {
		GDExtensionBinding::InitObject init_obj(p_iface, p_library, r_init);
		init_obj.register_initializer(initialize_bestiary_extension);
		init_obj.register_terminator(uninitialize_bestiary_extension);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
		return init_obj.init();
}}
```

---

## Godot scene hierarchy
```yaml
Bestiary (Control)
├─ Background      : NinePatchRect (paper/book texture)
├─ IndexPanel      : VBoxContainer        # list of unlocked beasts
│   └─ BeastButton : Button (created at runtime, one per beast)
├─ PageContainer   : Control              # holds current “page”
│   ├─ Sprite      : TextureRect          # tiny monster portrait
│   ├─ PageText    : RichTextLabel        # main text
│   └─ PageQuote   : RichTextLabel (ital) # quote
├─ PrevBtn         : Button  («)
└─ NextBtn         : Button  (»)
```

## GDScript logic
> File: `Bestiary.gd` (attach to the root *Bestiary* node)

```gdscript
extends Control

@onready var index_panel  : VBoxContainer = %IndexPanel
@onready var page_text    : RichTextLabel = %PageText
@onready var page_quote   : RichTextLabel = %PageQuote
@onready var sprite_rect  : TextureRect   = %Sprite
@onready var prev_btn     : Button        = %PrevBtn
@onready var next_btn     : Button        = %NextBtn

var reg       : BestiaryRegistryGD
var beast_ids : Array        # array of StringNames
var current   : int = -1

func _ready() -> void:
        reg = BestiaryRegistryGD.new()
        reg.load_dir("res://data/bestiary")     # same path we used on desktop

        beast_ids = reg.get_ids()
        _populate_index()
        _show_page(0)

func _populate_index() -> void:
        for i in beast_ids.size():
                var data = reg.get_beast(beast_ids[i])
                var btn  = Button.new()
                btn.text = data.get("name", "???")
                btn.theme_type_variation = "BestiaryIndex"
                btn.connect("pressed", _on_index_pressed.bind(i))
                index_panel.add_child(btn)

func _on_index_pressed(idx:int) -> void:
        _show_page(idx)

func _show_page(idx:int) -> void:
        if idx < 0 or idx >= beast_ids.size():
                return
        current = idx
        var data : Dictionary = reg.get_beast(beast_ids[idx])

        # TEXT
        var rt = "[center][b]%s[/b][/center]\n\n".sprintf(data["name"])
        rt += "[i]%s[/i]\n\n".sprintf(data["quote"])
        rt += "[b]Type:[/b] %s\n".sprintf(data["type"])
        rt += "[b]Threat:[/b] %s\n\n".sprintf(data["threat_level"])
        rt += "[b]Description:[/b]\n%s\n\n".sprintf(data["description"])
        if data.has("notes"):
                for n in data["notes"]:
                        rt += "• %s\n".sprintf(n)
        page_text.text = rt

        # IMAGE  (load tiny portrait: `icon/abyssal_current.png` convention)
        var tex_path = "res://assets/portraits/%s.png".sprintf(beast_ids[idx].to_lower())
        if ResourceLoader.exists(tex_path):
                sprite_rect.texture = load(tex_path)
        else:
                sprite_rect.texture = null

        # Buttons
        prev_btn.disabled = (idx == 0)
        next_btn.disabled = (idx == beast_ids.size()-1)

func _on_PrevBtn_pressed() -> void: _show_page(current-1)
func _on_NextBtn_pressed() -> void: _show_page(current+1)
```

Add signals to the two page buttons in the editor so they call 
`_on_PrevBtn_pressed` / `_on_NextBtn_pressed`

---

## Page-flip flourish (optional)
Quickest visual trick:
- Add an `AnimationPlayer` to *PageContainer*.
- Record a **rotate-Y** from `0° → 180°` over 0.4 s and add easing.
- Call `play("flip")` each time we change pages.

For a real mesh-based page-curl we’d swap in a `PageFlipShader` 
or use a mesh plane that bends over time.
There might be several open-source demos we can lift.
