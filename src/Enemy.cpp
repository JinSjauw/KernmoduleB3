#include "Enemy.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

void Enemy::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("Die"), &Enemy::Die);
}

Enemy::Enemy() 
{
    if(Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

Enemy::~Enemy() {
}

void Enemy::Die() 
{
    UtilityFunctions::print("Received DIE Signal");
    queue_free();
}

void Enemy::Initialize(Node2D* target, Vector2 spawnPosition) 
{
    //Set target
    this->target = target;
    set_global_position(spawnPosition);
    
    UtilityFunctions::print("Spawned!: " + spawnPosition);
}

void Enemy::_ready() {
	
    find_child("HealthComponent")->connect("die_signal", Callable(this, "Die"));
    enemyBody = Object::cast_to<RigidBody2D>(find_child("EnemyBody"));
}

void Enemy::_physics_process(double delta) 
{
    //Move & look towards target 
    enemyBody->look_at(this->target->get_global_position());
    Vector2 moveDirection = target->get_global_position() - enemyBody->get_global_position();
    Ref<KinematicCollision2D> hit = enemyBody->move_and_collide(moveDirection.normalized() * 100 * delta);

    if(hit != nullptr)
    {
       Node* target = Object::cast_to<Node>(hit->get_collider())->find_child("HealthComponent");
       Object::cast_to<HealthComponent>(target)->TakeDamage(35);
       queue_free();
    }
}
