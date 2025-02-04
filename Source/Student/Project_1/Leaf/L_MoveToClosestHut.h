#pragma once
#include "BehaviorNode.h"

class L_MoveToClosestHut : public BaseNode<L_MoveToClosestHut>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Agent* targetAgent;
};