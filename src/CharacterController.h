#pragma once

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>


#include "Projectile.h"

using namespace godot;

class CharacterController : public Node2D
{
    GDCLASS(CharacterController, Node2D);

    private:
        double movementSpeed;
        Vector2 movementInput;
        Vector2 lookDirection;
        Vector2 mousePosition;

        Node2D* firingPoint;
        CharacterBody2D* playerBody;
        Ref<PackedScene> projectilePrefabScene;

        Ref<AudioStream> sfx_stream;
        AudioStreamPlayer2D* sfx_player;

    protected:
        static void _bind_methods();

    public:
        CharacterController();
        ~CharacterController();
        void _ready();
        void _physics_process(double delta);

        void SetMovementSpeed(const double speed);
        double GetMovementSpeed() const;
};

#endif
