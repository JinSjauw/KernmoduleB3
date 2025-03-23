#pragma once

#include "CharacterController.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>

void CharacterController::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetMovementSpeed"), &CharacterController::GetMovementSpeed);
    ClassDB::bind_method(D_METHOD("SetMovementSpeed", "MovementSpeed"), &CharacterController::SetMovementSpeed);

    ClassDB::add_property("CharacterController", PropertyInfo(Variant::FLOAT, "MovementSpeed"), "SetMovementSpeed", "GetMovementSpeed");
    ADD_SIGNAL(MethodInfo("GetMovementSpeedSignal", PropertyInfo(Variant::FLOAT, "data")));
}

void CharacterController::_ready() 
{
    Node* playerBodyNode = get_child(0);
    playerBody = Object::cast_to<CharacterBody2D>(playerBodyNode);
}

void CharacterController::_physics_process(double delta) {
	movementDirection = Vector2(0.0f, 0.0f);

    //Input

    Input& inputSingleton = *Input::get_singleton();

    if(inputSingleton.is_action_pressed("up"))
    {
        //emit_signal("GetMovementSpeedSignal", movementSpeed);
        movementDirection.y -= 1.0f;
    }
    if(inputSingleton.is_action_pressed("down"))
    {
        movementDirection.y += 1.0f;
    }
    if(inputSingleton.is_action_pressed("right"))
    {
        movementDirection.x += 1.0f;
    }
    if(inputSingleton.is_action_pressed("left"))
    {
        movementDirection.x -= 1.0f;
    }

    playerBody->move_and_collide(movementDirection * movementSpeed * delta);
    //set_position(get_position() + (movementDirection * movementSpeed * delta));
}

void CharacterController::SetMovementSpeed(const double speed) 
{
    this->movementSpeed = speed;
}

double CharacterController::GetMovementSpeed() const 
{
	return movementSpeed;
}

CharacterController::CharacterController()
{
    if(Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}
CharacterController::~CharacterController(){}
