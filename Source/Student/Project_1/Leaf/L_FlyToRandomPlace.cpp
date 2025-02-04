#include <pch.h>
#include "L_FlyToRandomPlace.h"
#include "Agent/BehaviorAgent.h"

void L_FlyToRandomPlace::on_enter()
{
    // set animation, speed, etc

    targetPoint = RNG::world_position();
    //agent->look_at_point(targetPoint);
    targetPoint += Vec3(0, rand() % 20, 0);
	BehaviorNode::on_leaf_enter();
}

void L_FlyToRandomPlace::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
