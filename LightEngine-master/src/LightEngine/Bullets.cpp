#include "Bullets.h"
#include "Enemy.h"

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