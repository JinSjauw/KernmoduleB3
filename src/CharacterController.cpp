#pragma once

#include "CharacterController.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>

void CharacterController::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetMovementSpeed"), &CharacterController::GetMovementSpeed);
    ClassDB::bind_method(D_METHOD("SetMovementSpeed", "MovementSpeed"), &CharacterController::SetMovementSpeed);

    ClassDB::add_property("CharacterController", PropertyInfo(Variant::FLOAT, "MovementSpeed"), "SetMovementSpeed", "GetMovementSpeed");
}

void CharacterController::_ready() 
{
    Node* playerBodyNode = get_child(0);
    playerBody = Object::cast_to<CharacterBody2D>(playerBodyNode);

    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    projectilePrefabScene = resourceLoader->load("res://prefabs/projectile.tscn");

    firingPoint = Object::cast_to<Node2D>(find_child("FiringPoint"));

    sfx_player = Object::cast_to<AudioStreamPlayer2D>(find_child("AudioStreamPlayer2D"));
    sfx_stream = ResourceLoader::get_singleton()->load("res://Assets/laser-45816.mp3");

    if (sfx_stream.is_valid() && sfx_player != nullptr) 
    {
        sfx_player->set_stream(sfx_stream);
    }
}

void CharacterController::_physics_process(double delta) 
{
    movementInput = Vector2(0.0f, 0.0f);

    //Input
    Input& inputSingleton = *Input::get_singleton();

    if(inputSingleton.is_action_pressed("up"))
    {
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
    if(inputSingleton.is_action_just_pressed("shoot"))
    {
        //Shoot
        if(projectilePrefabScene->can_instantiate())
        {
            if(firingPoint != nullptr)
            {
                   Node* instantiatedNode = projectilePrefabScene->instantiate();
                   add_child(instantiatedNode);

                   Projectile* spawnedProjectile = Object::cast_to<Projectile>(instantiatedNode);
                   spawnedProjectile->LaunchProjectile(firingPoint->get_global_position(), playerBody->get_transform().basis_xform(Vector2(1, 0)));
                   UtilityFunctions::print("Look firing point direction: " + (playerBody->get_transform().basis_xform(Vector2(1, 0))));

                   sfx_player->play();
            }
        }   
    }

    mousePosition = get_global_mouse_position();
    
    playerBody->look_at(mousePosition);
    playerBody->move_and_collide(movementInput.normalized() * movementSpeed * delta);
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
