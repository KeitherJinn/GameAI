#pragma once
#include "BehaviorNode.h"

class C_ParallelSelector : public BaseNode<C_ParallelSelector>
{
protected:
    virtual void on_update(float dt) override;
};