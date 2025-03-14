#pragma once
#include "BehaviorNode.h"

class L_MoveToClosestHuman : public BaseNode<L_MoveToClosestHuman>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Agent* targetAgent;
};