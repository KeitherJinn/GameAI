#include <pch.h>
#include "L_PlayMusic.h"

void L_PlayMusic::on_enter()
{
	audioManager->PlayMusic(L"Assets\\Audio\\Scene7.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}