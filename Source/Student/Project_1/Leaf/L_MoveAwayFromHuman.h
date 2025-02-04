#pragma once
#include "BehaviorNode.h"

class L_MoveAwayFromHuman : public BaseNode<L_MoveAwayFromHuman>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Agent* targetAgent;
};