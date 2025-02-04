#pragma once
#include "BehaviorNode.h"

class L_Talk : public BaseNode<L_Talk>
{
protected:
    virtual void on_enter() override;
};