#pragma once
#include "BehaviorNode.h"

class L_DecreaseFood : public BaseNode<L_DecreaseFood>
{
protected:
    virtual void on_enter();
    Agent* targetAgent;
    Vec3 targetPoint;
};