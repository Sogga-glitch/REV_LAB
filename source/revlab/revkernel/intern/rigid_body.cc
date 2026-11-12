#include "KER_rigid_body.hh"

RigidBody::RigidBody() = default;

RigidBody::RigidBody(float2 position, float theta, float mass, float inertia) : position(position), theta(theta), mass(mass), inertia(inertia) {
}

RigidBody::~RigidBody() {
}

// TODO; move the implementation of matrix creation to revlib

float4x4 RigidBody::matrix() const {
	/* clang-format off */
	return float4x4(
		float4(+cosf(this->theta), -sinf(this->theta), 0.0f, this->position.x),
		float4(+sinf(this->theta), +cosf(this->theta), 0.0f, this->position.y),
		float4(				+0.0f, 				+0.0f, 1.0f, 			+0.0f),
		float4(				+0.0f, 				+0.0f, 0.0f, 			+1.0f)
	);
	/* clang-format on */
}
