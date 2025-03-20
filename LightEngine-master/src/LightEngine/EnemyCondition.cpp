#include "EnemyCondition.h"

bool EnemyCondition_isTakingDamage::OnTest(Enemy* owner)
{
    if (owner->GetIsTakingDamage() == true)
    {
        return true;
    }
    return false;
}

bool EnemyCondition_isAttacking::OnTest(Enemy* owner)
{
    if (owner->GetIsAttacking() == true)
    {
        return true;
    }
    return false;
}
