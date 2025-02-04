#include <pch.h>
#include "C_ParallelSelector.h"

void C_ParallelSelector::on_update(float dt)
{
    // run all children
    // if all child fails, the node fails
    // if any children succeed, the node succeeds

    bool allFailed = true;

    for (auto&& child : children)
    {
        child->tick(dt);

        if (child->succeeded() == true)
        {
            allFailed = false;
            on_success();
        }
        else if (child->is_running() == true && child->failed() == false)
        {
            allFailed = false;
        }
    }

    if (allFailed == true)
    {
        on_failure();
    }
}
