#include <pch.h>
#include "L_IncreaseFood.h"
#include "../Agent/BehaviorAgent.h"

void L_IncreaseFood::on_enter() {
	Vec3 col = agent->get_color();
	if (col.x < 1) {
		col.x += 0.1;
	}
	agent->set_color(col);

	on_success();
	display_leaf_text();
}
