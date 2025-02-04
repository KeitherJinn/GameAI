#pragma once
#include "BehaviorNode.h"

class L_MoveToClosestAgent : public BaseNode<L_MoveToClosestAgent>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};