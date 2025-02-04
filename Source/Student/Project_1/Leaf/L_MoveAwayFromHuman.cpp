#include <pch.h>
#include "L_MoveAwayFromHuman.h"
#include "Agent/BehaviorAgent.h"
#include <cstdlib>

void L_MoveAwayFromHuman::on_enter()
{
    // set animation, speed, etc

    // grab the target position from the blackboard
    const auto& bb = agent->get_blackboard();
    targetPoint = bb.get_value<Vec3>("Target Position");

    //agent->look_at_point(targetPoint);

    BehaviorNode::on_leaf_enter();
}

void L_MoveAwayFromHuman::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}