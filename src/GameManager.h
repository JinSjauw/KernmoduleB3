#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>

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

        Ref<AudioStream> bgm_stream;
        AudioStreamPlayer2D* bgm_player;

        int score = 0;

    protected:
        static void _bind_methods();
        
    public:
        GameManager();
        ~GameManager();
        void _ready();
        void EndGame();
        void UpdateHealth(String value);
        void IncrementScore();
};
