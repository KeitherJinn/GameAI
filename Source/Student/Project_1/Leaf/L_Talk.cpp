#include <pch.h>
#include "L_Talk.h"

void L_Talk::on_enter()
{
	audioManager->PlaySoundEffect(L"Assets\\Audio\\talk.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}