#include "MapEditor.h"
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

// - pour ciel
// T pour terre
// A pour arbre ?
// P pour plante


void MapEditor::CreateMap(float pResolution)
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
		for (int i = 0; i < line.size(); ++i)
		{
			switch (line[i])
			{
			case '-':
			{
				ObjectEntity* tempEntityCiel = currentScene->CreateRectangle<ObjectEntity>(pResolution,
					pResolution, sf::Color::Cyan);
				mObjects.push_back(tempEntityCiel);
				tempEntityCiel->SetTag(1);
				tempEntityCiel->SetPosition(posX, posY);
				tempEntityCiel->SetCollider(posX, posY, pResolution, pResolution);
				tempEntityCiel->SetRigidBody(true);
				break;
			}

			case 'T':
			{
				ObjectEntity* tempEntityDirt = currentScene->CreateRectangle<ObjectEntity>(pResolution,
					pResolution, sf::Color(88, 41, 0, 255));
				mObjects.push_back(tempEntityDirt);
				tempEntityDirt->SetTag(2);
				tempEntityDirt->SetCollider(posX, posY, pResolution, pResolution);
				tempEntityDirt->SetPosition(posX, posY);
				tempEntityDirt->SetRigidBody(true);
				break;
			}

			case 'A':
			{
				ObjectEntity* tempEntityArbre = currentScene->CreateRectangle<ObjectEntity>(pResolution,
					pResolution, sf::Color::Green);
				mObjects.push_back(tempEntityArbre);
				tempEntityArbre->SetTag(3);
				tempEntityArbre->SetCollider(posX, posY, pResolution, pResolution);
				tempEntityArbre->SetPosition(posX, posY);
				tempEntityArbre->SetRigidBody(true);
				break;
			}

			case 'P':
			{
				ObjectEntity* tempEntityPlante = currentScene->CreateRectangle<ObjectEntity>(pResolution,
					pResolution, sf::Color(0, 140, 0, 255));
				mObjects.push_back(tempEntityPlante);
				tempEntityPlante->SetTag(4);
				tempEntityPlante->SetCollider(posX, posY, pResolution, pResolution);
				tempEntityPlante->SetPosition(posX, posY);
				tempEntityPlante->SetRigidBody(true);
				break;
			}
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
	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i]->GetTag() != 1)
		{
			tempVector.push_back(mObjects[i]);
		}
	}
	return tempVector;
}
