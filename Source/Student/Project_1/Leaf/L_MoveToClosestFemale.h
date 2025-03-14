#pragma once
#include "BehaviorNode.h"

class L_MoveToClosestFemale : public BaseNode<L_MoveToClosestFemale>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Agent* targetAgent;
};