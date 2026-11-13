#include "KER_rigid_body.hh"

RigidBody::RigidBody() = default;

RigidBody::RigidBody(float2 position, float theta, float mass, float inertia) : position(position), theta(theta), mass(mass), inertia(inertia) {
}

RigidBody::~RigidBody() {
}
