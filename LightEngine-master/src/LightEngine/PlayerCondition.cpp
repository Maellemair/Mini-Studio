#include "PlayerCondition.h"

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
