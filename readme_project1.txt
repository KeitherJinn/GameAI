Student Name: Daoming Wang

Project Name: Camp In Woods

What I implemented:
	A simulation scene of a camp in the woods. You can manipulate one of the humans. Other humans will do random things like adding food to the food spot or talk to each other. Blue male birds tend to avoid humans but will eat the food in the food spot, and will try chasing female birds. Pink female birds sometimes approach humans, and will also eat the food in the food spot. The food left in the spot can be judged by it's color. The food spot has its own behavior tree and also is in charge of playing music in the scene.

Directions (if needed): What are all the control flow nodes type?

What I liked about the project and framework:
The framework is easy to understand and operate. It's highly modular so I can learn it easily by looking through the example code. Also, developing your own scene is really fun. I can't really do much because of some personal issues, but I'd like to do more if given time.

What I disliked about the project and framework:
If allowed to write derived class of BehaviorAgent, there's more thing we can do. Can we write derived class of more classes in project 2?

Any difficulties I experienced while doing the project:
I only had .m4a audio materials and it doesn't work. Luckily I only need to put it in a converter and get .wav versions.

Hours spent: 11

New selector node (name): ParallelSelector

New decorator nodes (names): Inverter, Repeater

10 (18) total nodes (names): ParallelSelector, Inverter, Repeater, Talk, Door, MoveToClosestAgent, FlyToClosestTreetop, MoveToClosestHuman, FlyToRandomPlace, MoveAwayFromHuman, CheckHuman, CheckBird, MoveToClosestFood, MoveToClosestFemale, MoveToClosestHut, PlayMusic, IncreaseFood, DecreaseFood

4 (5) Behavior trees (names): FemaleBird, MaleBird, Food, Man, NPCman

Extra credit: None