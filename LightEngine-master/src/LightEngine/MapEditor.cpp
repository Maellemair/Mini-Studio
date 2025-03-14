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
				mPlateforms.push_back(newObject);
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
