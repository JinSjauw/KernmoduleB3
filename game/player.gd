extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var summator = Summator.new()
	summator.add(3)
	summator.add(10)
	summator.add(-4)
	print(summator.get_total())

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_character_controller_get_movement_speed_signal(data: float) -> void:
	print(data)
	pass # Replace with function body.
