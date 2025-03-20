#include "EnemyCondition.h"

bool EnemyCondition_IsColliding::OnTest(Enemy* owner)
{
    if (owner->GetStateCollision() != None)
    {
        return true;
    }
    return false;
}
