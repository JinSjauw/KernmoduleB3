#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include "CharacterController.h"

using namespace godot;

class GameManager : public Node2D
{
    GDCLASS(GameManager, Node2D);
    private:
        Label* scoreLabel;
        Label* healthLabel;

        Node* playerNode;
        Node* enemySpawnerNode;

        int score;
        int currentHP;

    protected:
        static void _bind_methods();
        
    public:
        GameManager();
        ~GameManager();
        void _ready();
        void UpdateHealth(int health);
        void IncrementScore();
};
