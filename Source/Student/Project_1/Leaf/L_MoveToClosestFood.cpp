#include <pch.h>
#include "L_MoveToClosestFood.h"
#include "Agent/BehaviorAgent.h"
#include <cstdlib>

void L_MoveToClosestFood::on_enter()
{
    // set animation, speed, etc

    // find the agent that is the Closest from this one
    float shortestDistance = std::numeric_limits<float>().max();
    Vec3 closestPoint;
    bool targetFound = false;

    // get a list of all current agents
    const auto &allAgents = agents->get_all_agents();

    // and our agent's position
    const auto &currPos = agent->get_position();

    for (const auto & a : allAgents)
    {
        // make sure it's not our agent
        if (a != agent && a->get_type() == "Food")
        {
            const auto &agentPos = a->get_position();
            const float distance = Vec3::Distance(currPos, agentPos);

            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                closestPoint = agentPos;
                targetFound = true;
                targetAgent = a;
            }
        }
    }

    if (targetFound == true)
    {
        targetPoint = closestPoint;
		BehaviorNode::on_leaf_enter();
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }
}

void L_MoveToClosestFood::on_update(float dt)
{
    targetPoint = targetAgent->get_position();

    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}

