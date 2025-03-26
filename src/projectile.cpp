#include "Projectile.h"
#include "HealthComponent.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>

void Projectile::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetProjectileSpeed"), &Projectile::GetProjectileSpeed);
    ClassDB::bind_method(D_METHOD("SetProjectileSpeed", "ProjectileSpeed"), &Projectile::SetProjectileSpeed);

    ClassDB::add_property("Projectile", PropertyInfo(Variant::FLOAT, "ProjectileSpeed"), "SetProjectileSpeed", "GetProjectileSpeed");

    ClassDB::bind_method(D_METHOD("GetProjectileDamage"), &Projectile::GetProjectileDamage);
    ClassDB::bind_method(D_METHOD("SetProjectileDamage", "ProjectileDamage"), &Projectile::SetProjectileDamage);

    ClassDB::add_property("Projectile", PropertyInfo(Variant::FLOAT, "ProjectileDamage"), "SetProjectileDamage", "GetProjectileDamage");
}

Projectile::Projectile() 
{
    if(Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

Projectile::~Projectile() 
{

}

void Projectile::_ready() 
{
    //Get rigidbody
    Node* projectileBodyNode = get_child(0);
    projectileBody = Object::cast_to<RigidBody2D>(projectileBodyNode);
}

void Projectile::_physics_process(double delta) 
{
    //Handle collision
    lastPosition = currentPosition;
    currentPosition = projectileBody->get_global_position();

    PhysicsDirectSpaceState2D* worldState = get_world_2d()->get_direct_space_state();
    Ref<PhysicsRayQueryParameters2D> rayQuery = PhysicsRayQueryParameters2D::create(lastPosition, currentPosition, collisionMask);
    Dictionary result = worldState->intersect_ray(rayQuery);

    if(result.size() > 0)
    {
        UtilityFunctions::print("HIT! ", result["collider"]);

        Node2D* hitObject = Object::cast_to<Node2D>(result["collider"]);

        HealthComponent* target = Object::cast_to<HealthComponent>(hitObject->find_child("HealthComponent"));

        if(target != nullptr)
        {
            target->TakeDamage(projectileDamage);
        }

        queue_free();
    }
}

void Projectile::LaunchProjectile(Vector2 launchPosition, Vector2 launchDirection)
{
    set_global_position(launchPosition);
    currentPosition = launchPosition;
    this->launchDirection = launchDirection;
    projectileBody->look_at(get_global_position() + launchDirection);
    projectileBody->apply_impulse(launchDirection * projectileSpeed, get_global_position());
}

void Projectile::SetProjectileSpeed(const double speed) 
{
	this->projectileSpeed = speed;
}

double Projectile::GetProjectileSpeed() const 
{
	return projectileSpeed;
}

void Projectile::SetProjectileDamage(const double damage)
{
    this->projectileDamage = damage;
}

double Projectile::GetProjectileDamage() const
{
    return projectileDamage;
}
