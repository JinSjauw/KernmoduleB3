
#include "EnemySpawner.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/engine.hpp>

void EnemySpawner::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetSpawnInterval"), &EnemySpawner::GetSpawnInterval);
    ClassDB::bind_method(D_METHOD("SetSpawnInterval", "SpawnInterval"), &EnemySpawner::SetSpawnInterval);

    ClassDB::add_property("EnemySpawner", PropertyInfo(Variant::FLOAT, "SpawnInterval"), "SetSpawnInterval", "GetSpawnInterval");
}

EnemySpawner::EnemySpawner() 
{
    if(Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

EnemySpawner::~EnemySpawner() 
{

}

void EnemySpawner::_ready() 
{
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    enemyPrefab = resourceLoader->load("res://prefabs/enemy.tscn");
    playerTarget = Object::cast_to<Node2D>(find_parent("Main")->find_child("PlayerBody"));
    playerCamera = Object::cast_to<Camera2D>(find_parent("Main")->find_child("PlayerCamera"));

    viewPortSize = playerCamera->get_viewport_rect().get_size() / playerCamera->get_zoom();
    viewPortOffset = viewPortSize * 1.15f / 2;

    rng.instantiate();
}

void EnemySpawner::_process(double delta) 
{
    spawnTimer += delta;

    if(spawnTimer >= spawnInterval)
    {
        spawnTimer = 0;
        UtilityFunctions::print("Enemy Spawned!");

        //Decide spawn position
        //Randomize it

        Vector2 randomDirection = Vector2(rng->randi_range(1, 2) == 2 ? -1 : 1, rng->randi_range(1, 2) == 2 ? -1 : 1);
        Vector2 randomOffset = Vector2(rng->randf_range(-100, 100), rng->randf_range(-100, 100));
        UtilityFunctions::print("RandomPoint: " + randomDirection);
        Vector2 spawnPosition =  (viewPortOffset * randomDirection + playerTarget->get_global_position()) + randomOffset;
        Node* instantiatedNode = enemyPrefab->instantiate();    
        add_child(instantiatedNode);
        
        Enemy* spawnedEnemy = Object::cast_to<Enemy>(instantiatedNode);
        spawnedEnemy->Initialize(playerTarget, spawnPosition);
    }

}

void EnemySpawner::SetSpawnInterval(double interval) 
{
    this->spawnInterval = interval;
}

double EnemySpawner::GetSpawnInterval() 
{
	return this->spawnInterval;
}
