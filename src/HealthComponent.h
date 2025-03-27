#pragma once

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

class HealthComponent : public Node2D
{
    GDCLASS(HealthComponent, Node2D);

    private:
        int maxHealth;
        int currentHealth;

        Node* rootNode;

        void Die();

    protected:
        static void _bind_methods();
    public:
        HealthComponent();
        ~HealthComponent();

        void _ready();

        void TakeDamage(int damage);
        void SetMaxHealth(const int maxHealth);
        int GetMaxHealth() const;
};

#endif