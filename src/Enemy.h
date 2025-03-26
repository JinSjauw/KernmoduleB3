#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

class Enemy : public Node2D
{
    GDCLASS(Enemy, Node2D);

    private:
        void Die();
    protected:
        static void _bind_methods();
    public:
        Enemy();
        ~Enemy();

        void _ready();
};

#endif;

