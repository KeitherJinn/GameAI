#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create an agent (using the default "Agent::AgentModel::Man" model)
    auto man = agents->create_behavior_agent("Man", BehaviorTreeTypes::Man);
    man->set_scaling(1);
    man->set_color(Vec3(1, 0.5, 0.5));

    auto NPCman = agents->create_behavior_agent("Man", BehaviorTreeTypes::NPCman);
    NPCman->set_scaling(1);

    auto NPCman2 = agents->create_behavior_agent("Man", BehaviorTreeTypes::NPCman);
    NPCman2->set_scaling(1);

    // You can change properties here or at runtime from a behavior tree leaf node
    // Look in Agent.h for all of the setters, like these:
    // man->set_color(Vec3(1, 0, 1));
    // man->set_scaling(Vec3(7,7,7));
    // man->set_position(Vec3(100, 0, 100));

    // Create an agent with a different 3D model:
    // 1. (optional) Add a new 3D model to the framework other than the ones provided:
    //    A. Find a ".sdkmesh" model or use https://github.com/walbourn/contentexporter
    //       to convert fbx files (many end up corrupted in this process, so good luck!)
    //    B. Add a new AgentModel enum for your model in Agent.h (like the existing Man or Tree).
    // 2. Register the new model with the engine, so it associates the file path with the enum
    //    A. Here we are registering all of the extra models that already come in the package.
    Agent::add_model("Assets\\tree.sdkmesh", Agent::AgentModel::Tree);
    Agent::add_model("Assets\\car.sdkmesh", Agent::AgentModel::Car);
    Agent::add_model("Assets\\bird.sdkmesh", Agent::AgentModel::Bird);
    Agent::add_model("Assets\\ball.sdkmesh", Agent::AgentModel::Ball);
    Agent::add_model("Assets\\hut.sdkmesh", Agent::AgentModel::Hut);
    // 3. Create the agent, giving it the correct AgentModel type.
    auto tree = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
    auto tree2 = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
    auto tree3 = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
    // 4. (optional) You can also set the pitch of the model, if you want it to be rotated differently
    tree->set_pitch(PI / 2);
    tree2->set_pitch(PI / 2);
    tree2->set_yaw(PI / 2);
    tree3->set_pitch(PI / 2);
    tree3->set_yaw(PI / 4);
    // 5. (optional) Set other aspects to make it start out correctly
    tree->set_color(Vec3(0, 0.5, 0));   // Set the tree to green
    tree2->set_color(Vec3(0, 0.5, 0));
    tree3->set_color(Vec3(0, 0.5, 0));
    tree->set_scaling(1);
    tree2->set_scaling(1);
    tree3->set_scaling(1);
    tree->set_position(Vec3(50, 0, 80));
    tree2->set_position(Vec3(20, 0, 50));
    tree3->set_position(Vec3(30, 0, 20));

    auto hut = agents->create_behavior_agent("Hut", BehaviorTreeTypes::Idle, Agent::AgentModel::Hut);
    hut->set_position(Vec3(60, 0, 20));
    hut->set_yaw(PI / 2);
    hut->set_scaling(1);

    auto malebird = agents->create_behavior_agent("MaleBird", BehaviorTreeTypes::MaleBird, Agent::AgentModel::Bird);
    malebird->set_scaling(0.004);
    malebird->set_position(Vec3(40, 0, 40));
    malebird->set_color(Vec3(0.5, 0.5, 1));

    auto malebird2 = agents->create_behavior_agent("MaleBird", BehaviorTreeTypes::MaleBird, Agent::AgentModel::Bird);
    malebird2->set_scaling(0.004);
    malebird2->set_position(Vec3(0, 0, 20));
    malebird2->set_color(Vec3(0.5, 0.5, 1));

    auto malebird3 = agents->create_behavior_agent("MaleBird", BehaviorTreeTypes::MaleBird, Agent::AgentModel::Bird);
    malebird3->set_scaling(0.004);
    malebird3->set_position(Vec3(20, 0, 0));
    malebird3->set_color(Vec3(0.5, 0.5, 1));

    auto femalebird = agents->create_behavior_agent("FemaleBird", BehaviorTreeTypes::FemaleBird, Agent::AgentModel::Bird);
    femalebird->set_scaling(0.004);
    femalebird->set_position(Vec3(20, 0, 20));
    femalebird->set_color(Vec3(1, 0, 0.5));

    auto food = agents->create_behavior_agent("Food", BehaviorTreeTypes::Food, Agent::AgentModel::Ball);
    food->set_scaling(0.4);
    food->set_position(Vec3(10, 0, 70));
    food->set_color(Vec3(0.6, 0.3, 0.1));

    // You can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code
    // that yourself (that's the realm of project 2)
    terrain->goto_map(0);

    // You can also enable the pathing layer and set grid square colors as you see fit.
    // Works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);

    // Camera position can be modified from this default
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-65.0f, 75.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees

    // Sound control (these sound functions can be kicked off in a behavior tree node - see the example in L_PlaySound.cpp)
    audioManager->SetVolume(0.5f);
    audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
    // Uncomment for example on playing music in the engine (must be .wav)
    // audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}