#include "MapEditor.h"
#include "Enemy.h"
#include "LifeBonus.h"
#include "WaterBonus.h"
#include "ObjectEntity.h"
#include "GameManager.h"

void MapEditor::Load(const char* path)
{
	fichier.close();
	fichier.open(path);

	if (!fichier.is_open()) {
		std::cout << "Erreur : Impossible d ouvrir le fichier." << std::endl;
	}
}

void MapEditor::CreateMap(float pResolution, std::map<char, ObjectEntity*> pMapObject)
{
	if (!fichier.is_open()) {
		std::cout << "Erreur : Impossible d ouvrir le fichier." << std::endl;
		return;
	}

	Scene* currentScene = GameManager::Get()->GetScene();
	std::string line = "";

	int posX = pResolution / 2;
	int posY = pResolution / 2;

	while (std::getline(fichier, line))
	{
		for (char c : line) 
		{
			auto it = pMapObject.find(c);
			if (it != pMapObject.end()) {
				ObjectEntity* newObject = it->second->Clone(pResolution, pResolution, posX, posY);
				newObject->SetRigidBody(false);
				mPlateforms.push_back(newObject);
			}
			else if (c == 'X')
			{
				Enemy* newEnemy = currentScene->CreateRectangle<Enemy>(64, 106, sf::Color::Green);
				newEnemy->SetPosition(posX + pResolution / 2, posY + pResolution / 2);
				newEnemy->SetCollider(posX + pResolution / 2, posY + pResolution / 2, 64, 50);
				newEnemy->SetRigidBody(true);
				mEnemy.push_back(newEnemy);
			}
			else if (c == 'l')
			{
				LifeBonus* newLifeBonus = currentScene->CreateRectangle<LifeBonus>(9, 9, sf::Color::Green);
				newLifeBonus->SetPosition(posX, posY);
				newLifeBonus->SetCollider(posX, posY, 9, 9);
				newLifeBonus->SetRigidBody(true);
				mBonus.push_back(newLifeBonus);
			}
			else if (c == 'w')
			{
				WaterBonus* newWaterBonus = currentScene->CreateRectangle<WaterBonus>(9, 9, sf::Color::Green);
				newWaterBonus->SetPosition(posX, posY);
				newWaterBonus->SetCollider(posX, posY, 9, 9);
				newWaterBonus->SetRigidBody(true);
				mBonus.push_back(newWaterBonus);
			}
			posX += pResolution;
		}
		posY += pResolution;
		posX = pResolution / 2;
	}
	fichier.close();
}

std::vector<ObjectEntity*> MapEditor::GetMap()
{
	std::vector<ObjectEntity*> tempVector;
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		if (mPlateforms[i]->GetTag() != 1)
		{
			tempVector.push_back(mPlateforms[i]);
		}
	}
	return tempVector;
}

std::vector<Enemy*> MapEditor::GetEnemy()
{
	return mEnemy;
}

std::vector<Bonus*> MapEditor::GetBonus()
{
	return mBonus;
}
