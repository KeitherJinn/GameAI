#pragma once
#include "BehaviorNode.h"

class L_FlyToClosestTreetop : public BaseNode<L_FlyToClosestTreetop>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};