#pragma once

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>

using namespace godot;

class CharacterController : public Node2D
{
    GDCLASS(CharacterController, Node2D);

    private:
        double movementSpeed;
        Vector2 movementInput;
        Vector2 lookDirection;
        Vector2 mousePosition;

        CharacterBody2D* playerBody;


    protected:
        static void _bind_methods();

    public:
        CharacterController();
        ~CharacterController();
        //void _process(double delta);
        void _ready();
        void _physics_process(double delta);

        void SetMovementSpeed(const double speed);
        double GetMovementSpeed() const;
};

#endif
