#include "PlayerCondition.h"
#include "Enemy.h"

bool PlayerCondition_IsMoving::OnTest(Player* owner)
{
    if (owner->GetDirection().x != 0)
    {
        return true;
    }
    return false;
}

bool PlayerCondition_isGround::OnTest(Player* owner)
{
    if (owner->GetColliderEntity() != nullptr)
    {
        return true;
    }
    return false;
}

bool PlayerCondition_isJumping::OnTest(Player* owner)
{
    if (owner->GetGravitySpeed() < 0)
    {
        return true;
    }
    return false;
}

bool PlayerCondition_isFalling::OnTest(Player* owner)
{
    if (owner->GetGravitySpeed() > 0)
    {
        return true;
    }
    return false;
}

bool PlayerCondition_isDead::OnTest(Player* owner)
{
    if (owner->IsDead())
    {
        return true;
    }
    return false;
}

bool PlayerCondition_takeDamage::OnTest(Player* owner)
{
    if (owner->GetIsTakingDamage() == true)
    {
        return true;
    }
    return false;
}
