#pragma once
#include "BehaviorNode.h"

class L_CheckBird : public BaseNode<L_CheckBird>
{
protected:
    virtual void on_update(float dt);
    Agent* targetAgent;
    Vec3 targetPoint;
};