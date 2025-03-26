#include "projectile.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

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
    //send ray cast to last known position and now.
}

void Projectile::LaunchProjectile(Vector2 launchDirection)
{
    this->launchDirection = launchDirection;
    projectileBody->apply_impulse(launchDirection * projectileSpeed);
}

void Projectile::SetProjectileSpeed(const double speed) {
	this->projectileSpeed = speed;
}

double Projectile::GetProjectileSpeed() const 
{
	return projectileSpeed;
}
