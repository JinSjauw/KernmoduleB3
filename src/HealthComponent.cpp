#include "HealthComponent.h"

#include <godot_cpp/core/class_db.hpp>

void HealthComponent::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetMaxHealth"), &HealthComponent::GetMaxHealth);
    ClassDB::bind_method(D_METHOD("SetMaxHealth", "MaxHealth"), &HealthComponent::SetMaxHealth);

    ClassDB::add_property("HealthComponent", PropertyInfo(Variant::INT, "MaxHealth"), "SetMaxHealth", "GetMaxHealth");
    ADD_SIGNAL(MethodInfo("die_signal"));
    ADD_SIGNAL(MethodInfo("health_update_signal", PropertyInfo(Variant::INT, "currentHealth")));
}

HealthComponent::HealthComponent() 
{

}

HealthComponent::~HealthComponent() 
{

}

void HealthComponent::_ready() 
{
    this->currentHealth = this->maxHealth;
}

void HealthComponent::TakeDamage(int damage) 
{
    currentHealth -= damage;
    emit_signal("health_update_signal", currentHealth);
    UtilityFunctions::print( get_name(), " Taking Damage! ", currentHealth);
    if(currentHealth <= 0)
    {   
        Die();
    }
}

void HealthComponent::SetMaxHealth(const int maxHealth) 
{
    this->maxHealth = maxHealth;
}

double HealthComponent::GetMaxHealth() const 
{
	return maxHealth;
}

void HealthComponent::Die() 
{
    UtilityFunctions::print("Emitting DIE signal!");
    emit_signal("die_signal");
    //queue_free();
}

