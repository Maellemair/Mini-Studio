#pragma once

#include "Scene.h"
#include <vector>

class PhysicalEntity;
class ObjectEntity;

class SampleScene : public Scene
{
	PhysicalEntity* pEntity1;
	PhysicalEntity* pEntity2;

	PhysicalEntity* pEntitySelected;

	std::vector<ObjectEntity*> mPlateforms;

private:
	void TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


