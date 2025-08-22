extends Control

const VIEWER_SCENE := preload("res://ui/BestiaryViewer.tscn")

func _ready() -> void:
	var viewer: Control = VIEWER_SCENE.instantiate()
	add_child(viewer)
	#viewer.set_anchors_preset(Control.PRESET_FULL_RECT)

	## Make it act like a root Control that fills the screen.
	#viewer.top_level = true
	#viewer.position = Vector2.ZERO
	#viewer.size = get_viewport().get_visible_rect().size
#
	## Keep it filling when window resizes.
	#get_viewport().size_changed.connect(func():
		#viewer.size = get_viewport().get_visible_rect().size
	#)
