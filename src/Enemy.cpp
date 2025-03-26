#include "Enemy.h"
#include <godot_cpp/core/class_db.hpp>


void Enemy::Die() 
{
    UtilityFunctions::print("Received DIE Signal");
    queue_free();
}

void Enemy::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("Die"), &Enemy::Die);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::_ready() 
{
    find_child("HealthComponent")->connect("die_signal", Callable(this, "Die"));
}
