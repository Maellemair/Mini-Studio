#include "EnemyCondition.h"

bool EnemyVolantCondition_isTakingDamage::OnTest(EnemyVolant* owner)
{
    if (owner->GetIsTakingDamage() == true)
    {
        return true;
    }
    return false;
}

bool EnemyVolantCondition_isAttacking::OnTest(EnemyVolant* owner)
{
    if (owner->GetIsAttacking() == true)
    {
        return true;
    }
    return false;
}

bool EnemyGroundCondition_isTakingDamage::OnTest(EnemyGround* owner)
{
    if (owner->GetIsTakingDamage() == true)
    {
        return true;
    }
    return false;
}

bool EnemyGroundCondition_isAttacking::OnTest(EnemyGround* owner)
{
    if (owner->GetIsAttacking() == true)
    {
        return true;
    }
    return false;
}

bool EnemyVolantCondition_isDead::OnTest(EnemyVolant* owner)
{
    if (owner->IsDead())
        return true;

    return false;
}

bool EnemyGroundCondition_isDead::OnTest(EnemyGround* owner)
{
    if (owner->IsDead())
        return true;

    return false;
}
