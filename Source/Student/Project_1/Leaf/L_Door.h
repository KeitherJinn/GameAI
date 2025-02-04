#pragma once
#include "BehaviorNode.h"

class L_Door : public BaseNode<L_Door>
{
protected:
    virtual void on_enter() override;
};