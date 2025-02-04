#pragma once
#include "BehaviorNode.h"

class L_IncreaseFood : public BaseNode<L_IncreaseFood>
{
protected:
    virtual void on_enter();
    Agent* targetAgent;
    Vec3 targetPoint;
};