#include <pch.h>
#include "L_CheckBird.h"
#include "../Agent/BehaviorAgent.h"

void L_CheckBird::on_update(float dt)
{
    // set animation, speed, etc

    // find the agent that is the Closest from this one
    float range = 15;
    float shortestDistance = std::numeric_limits<float>().max();
    Vec3 closestPoint;
    bool targetFound = false;

    // get a list of all current agents
    const auto& allAgents = agents->get_all_agents();

    // and our agent's position
    const auto& currPos = agent->get_position();

    for (const auto& a : allAgents)
    {
        // make sure it's not our agent
        if (a != agent && (a->get_type() == "FemaleBird" || a->get_type() == "MaleBird"))
        {
            const auto& agentPos = a->get_position();
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

    if (targetFound == true && shortestDistance < range)
    {
        targetPoint = 2 * agent->get_position() - targetAgent->get_position();
        if (targetPoint == agent->get_position()) {
            targetPoint = RNG::world_position();
        }
        // write the world position into the blackboard
        auto& bb = agent->get_blackboard();
        bb.set_value("Target Position", targetPoint);

        on_success();
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }

    display_leaf_text();
}
