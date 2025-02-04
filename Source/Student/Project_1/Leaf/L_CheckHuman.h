#pragma once
#include "BehaviorNode.h"

class L_CheckHuman : public BaseNode<L_CheckHuman>
{
protected:
    virtual void on_update(float dt);
    Agent* targetAgent;
    Vec3 targetPoint;
};