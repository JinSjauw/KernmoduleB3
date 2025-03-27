#pragma once

#include "Enemy.h"
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

using namespace godot;

class EnemySpawner : public Node2D
{
    GDCLASS(EnemySpawner, Node2D);

    private:

        double spawnInterval;
        double spawnTimer;

        Ref<PackedScene> enemyPrefab;
        Camera2D* playerCamera;
        Node2D* playerTarget;
        Vector2 viewPortSize;
        Vector2 viewPortOffset;
        Ref<RandomNumberGenerator> rng;

    protected:
        static void _bind_methods();

    public:
        EnemySpawner();
        ~EnemySpawner();

        void _ready();
        void _process(double delta);

        void EnemyDied();

        void SetSpawnInterval(double interval);
        double GetSpawnInterval();
};
