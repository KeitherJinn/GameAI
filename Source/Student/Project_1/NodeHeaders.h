#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes
#include "ControlFlow/C_ParallelSelector.h"

// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"

// Student Decorator Nodes
#include "Decorator/D_Repeater.h"
#include "Decorator/D_Inverter.h"

// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"

// Student Leaf Nodes
#include "Leaf/L_MoveToClosestAgent.h"
#include "Leaf/L_FlyToClosestTreetop.h"
#include "Leaf/L_Talk.h"
#include "Leaf/L_MoveToClosestHuman.h"
#include "Leaf/L_FlyToRandomPlace.h"
#include "Leaf/L_MoveAwayFromHuman.h"
#include "Leaf/L_CheckHuman.h"
#include "Leaf/L_MoveToClosestFood.h"
#include "Leaf/L_MoveToClosestHut.h"
#include "Leaf/L_MoveToClosestFemale.h"
#include "Leaf/L_Door.h"
#include "Leaf/L_PlayMusic.h"
#include "Leaf/L_IncreaseFood.h"
#include "Leaf/L_DecreaseFood.h"
#include "Leaf/L_CheckBird.h"