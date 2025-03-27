#pragma once

#include "GameManager.h"
#include "HealthComponent.h"
#include "EnemySpawner.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>



void GameManager::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("IncrementScore"), &GameManager::IncrementScore);
    ClassDB::bind_method(D_METHOD("UpdateHealth"), &GameManager::UpdateHealth);
    ClassDB::bind_method(D_METHOD("EndGame"), &GameManager::EndGame);
}

GameManager::GameManager() 
{

}

GameManager::~GameManager() 
{

}

void GameManager::_ready() 
{
    scoreLabel = Object::cast_to<Label>(find_child("ScoreText"));
    healthLabel = Object::cast_to<Label>(find_child("HealthText"));

    playerNode = find_child("Player");
    enemySpawnerNode = find_child("EnemySpawner");

    HealthComponent* playerHealth = Object::cast_to<HealthComponent>(playerNode->find_child("HealthComponent"));
    playerHealth->connect("health_update_signal", Callable(this, "UpdateHealth"));
    playerHealth->connect("die_signal", Callable(this, "EndGame"));

    healthLabel->set_text("HP: " + itos(playerHealth->GetMaxHealth()));

    Object::cast_to<EnemySpawner>(enemySpawnerNode)->connect("enemy_death_signal", Callable(this, "IncrementScore"));
    
    bgm_player = Object::cast_to<AudioStreamPlayer2D>(find_child("AudioStreamPlayer2D"));
    bgm_stream = ResourceLoader::get_singleton()->load("res://Assets/universe-space-sounds-3595.mp3");

    if (bgm_stream.is_valid() && bgm_player != nullptr) 
    {
        bgm_player->set_stream(bgm_stream);
        bgm_player->play();
    }
}

void GameManager::EndGame() 
{
    SceneTree* sceneTree = get_tree();

    if(sceneTree)
    {
        sceneTree->change_scene_to_file("res://scenes/mainMenu.tscn");
    }
}

void GameManager::UpdateHealth(String value) 
{
    healthLabel->set_text("HP: " + value);
}

void GameManager::IncrementScore() 
{
    UtilityFunctions::print("score updated!");
    score += 25;
    scoreLabel->set_text("Score: " + itos(score));
}
