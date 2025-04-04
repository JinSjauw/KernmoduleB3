#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>

using namespace godot;

class Projectile : public Node2D
{
    GDCLASS(Projectile, Node2D);

    private:
        double projectileSpeed;
        double projectileDamage;
        
        uint32_t collisionMask = 0b00000000000000000000000000000111;

        Vector2 launchDirection;
        Vector2 lastPosition;
        Vector2 currentPosition;

        RigidBody2D* projectileBody;

    protected:
        static void _bind_methods();

    public:
        Projectile();
        ~Projectile();
        
        void _ready();
        void _physics_process(double delta);

        void LaunchProjectile(Vector2 launchPosition, Vector2 launchDirection);
        void SetProjectileSpeed(const double speed);
        double GetProjectileSpeed() const;

        void SetProjectileDamage(const double damage);
        double GetProjectileDamage() const;
};

#endif