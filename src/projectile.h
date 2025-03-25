#pragma once

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>

using namespace godot;

class Projectile : public Node2D
{
    GDCLASS(Projectile, Node2D);

    private:
        double projectileSpeed;
        double projectileDamage;
        Vector2 launchDirection;

        RigidBody2D* projectileBody;

    protected:
        static void _bind_methods();

    public:
        Projectile(Vector2 launchDirection);
        ~Projectile();
        
        void _ready();
        void _physics_process(double delta);

        void SetProjectileSpeed(const double damage);
        double GetProjectileSpeed() const;
};

#endif