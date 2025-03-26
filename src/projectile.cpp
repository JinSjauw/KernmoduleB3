#include "projectile.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>

void Projectile::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("GetProjectileSpeed"), &Projectile::GetProjectileSpeed);
    ClassDB::bind_method(D_METHOD("SetProjectileSpeed", "ProjectileSpeed"), &Projectile::SetProjectileSpeed);

    ClassDB::add_property("Projectile", PropertyInfo(Variant::FLOAT, "ProjectileSpeed"), "SetProjectileSpeed", "GetProjectileSpeed");
}

Projectile::Projectile() 
{

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
    currentPosition = get_global_position();

    PhysicsDirectSpaceState2D* worldState = get_world_2d()->get_direct_space_state();
    Ref<PhysicsRayQueryParameters2D> rayQuery = PhysicsRayQueryParameters2D::create(lastPosition, currentPosition);
    Dictionary result = worldState->intersect_ray(rayQuery);

    if(!result.is_empty())
    {
        UtilityFunctions::print("HIT! ", result["collider_id"]);
        queue_free();
    }

    //worldState->intersect_ray()

    //send ray cast to last known position and now.
}

void Projectile::LaunchProjectile(Vector2 launchPosition, Vector2 launchDirection)
{
    set_global_position(launchPosition);
    currentPosition = launchPosition;
    this->launchDirection = launchDirection;
    projectileBody->look_at(get_global_position() + launchDirection);
    projectileBody->apply_impulse(launchDirection * projectileSpeed, get_global_position());
}

void Projectile::SetProjectileSpeed(const double speed) {
	this->projectileSpeed = speed;
}

double Projectile::GetProjectileSpeed() const 
{
	return projectileSpeed;
}
