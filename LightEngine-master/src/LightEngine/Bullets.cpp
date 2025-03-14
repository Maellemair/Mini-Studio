#include "Bullets.h"

void Bullets::OnCollision(Entity* collideWith) 
{

}

void Bullets::OnUpdate() 
{
	lifeTimer += deltaTime;	
	if (lifeTimer >= lifeTime)
	{
		Destroy();
	}
}