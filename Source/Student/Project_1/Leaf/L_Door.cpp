#include <pch.h>
#include "L_Door.h"

void L_Door::on_enter()
{
	audioManager->PlaySoundEffect(L"Assets\\Audio\\41_Door5_A.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}