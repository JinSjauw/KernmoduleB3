#pragma once

#include "GameManager.h"
#include "HealthComponent.h"
#include "EnemySpawner.h"
#include <godot_cpp/core/class_db.hpp>

void GameManager::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("IncrementScore"), &GameManager::IncrementScore);
    ClassDB::bind_method(D_METHOD("UpdateHealth"), &GameManager::UpdateHealth);
}

GameManager::GameManager() 
{

}

GameManager::~GameManager() 
{

}

void GameManager::_ready() 
{
    // scoreLabel = Object::cast_to<Label>(find_child("ScoreText"));
    // healthLabel = Object::cast_to<Label>(find_child("HealthText"));

    // scoreLabel->set_text("Score: 0");

    // playerNode = find_child("Player");
    // enemySpawnerNode = find_child("EnemySpawner");

    // Object::cast_to<HealthComponent>(playerNode->find_child("HealthComponent"))->connect("health_update_signal", Callable(this, "UpdateHealth"));
    // Object::cast_to<EnemySpawner>(enemySpawnerNode)->connect("enemy_death_signal", Callable(this, "IncrementScore"));
}

void GameManager::UpdateHealth(int health) 
{
    currentHP = health;
    healthLabel->set_text("HP: " + currentHP);
}

void GameManager::IncrementScore() 
{
    score += 25;
    scoreLabel->set_text("Score: " + score);
}
