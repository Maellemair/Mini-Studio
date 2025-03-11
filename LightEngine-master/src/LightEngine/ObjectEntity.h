#pragma once
#include "Entity.h"

class ObjectEntity : public Entity
{

public:
	void OnInitialize() override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	bool IsColliding(const AABBCollider& c1);
};

