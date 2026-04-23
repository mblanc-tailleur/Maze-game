#pragma once
#include "Entity.h"

class GravityEntity : public Entity
{
protected:
	float mGravityStrength = 9.81f;
	float mYVelocity = 0.f;
	float mJumpStrength = 100.f;

public:
	void Update() override;
	void Jump();

	void SetGravityStrength(float gravityStrength) { mGravityStrength = gravityStrength; }
	void SetJumpStrength(float jumpStrength) { mJumpStrength = jumpStrength; }
};

