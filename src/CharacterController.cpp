#pragma once

#include "CharacterController.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    projectilePrefabScene = resourceLoader->load("res://scenes/projectile.tscn");
}

void CharacterController::_physics_process(double delta) {
	movementInput = Vector2(0.0f, 0.0f);

    //Input

    Input& inputSingleton = *Input::get_singleton();

    if(inputSingleton.is_action_pressed("up"))
    {
        //emit_signal("GetMovementSpeedSignal", movementSpeed);
        movementInput.y -= 1.0f;
    }
    if(inputSingleton.is_action_pressed("down"))
    {
        movementInput.y += 1.0f;
    }
    if(inputSingleton.is_action_pressed("right"))
    {
        movementInput.x += 1.0f;
    }
    if(inputSingleton.is_action_pressed("left"))
    {
        movementInput.x -= 1.0f;
    }

    if(inputSingleton.is_action_pressed("shoot"))
    {
        //Shoot
        if(projectilePrefabScene->can_instantiate())
        {
            add_child(projectilePrefabScene->instantiate());
        }   
    }


    mousePosition = get_global_mouse_position();
    
    playerBody->look_at(mousePosition);

    UtilityFunctions::print("PlayerPosition: " + playerBody->get_transform().get_origin());
    UtilityFunctions::print("Look direction: " + (playerBody->get_transform().basis_xform(Vector2(-1, 0))));

    Ref<KinematicCollision2D> hit = playerBody->move_and_collide(movementInput.normalized() * movementSpeed * delta);

    if(hit != nullptr)
    {
        UtilityFunctions::print(hit->get_collider());
    }
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
