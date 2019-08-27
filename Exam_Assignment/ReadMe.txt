Pengu- README

in the game you can play alone or coop. you can push blocks and destroy them.
you cant kill snowbees and they cant kill you.
restart = close program.

git: https://github.com/ThibautLemmens/prog4exam-Thibaut-Lemmens


the engine has:

Time:
singleton that gives the delta time. you can slow or speed up time by a multiplier in the time object and get the current fps.

SceneRenderer:
each scene has a SceneRenderer
SceneRenderer holds vector of RenderComponents, you can ask a new one to give to a game object.

RenderComponent:
Works with a TransformComponent, but you can give a destination rect, source or attach a AnimatorComponent. User only needs to call render the components will check what its been given and will call correct render function from the renderer.

AnimatorComponent:
when making an animator, you pass the cols and rows. then you can begin making a clips, they hold a name, begin and end frame and how fast each frame last. you add those clips to the animator. then you can play them by passing a string. the Animator will Update the current clip

StatemachineComponent:
This component holds states, state is a class you inherit from when making a new state, you can overwrite the entry, update, and end fucntion. the state machine will call update of the current state. you can also attach an animatorcomponent. the default entry will call the playClip of the animationName the state holds.

TransformComponent:
holds a postion and scale. you can also parent and child other transformComponents

InputComponent:
Asks info from InputComponent (key / button down)
needs a player iD
update checks for key pressed and button pressed for each command

GridComponent:
attach to gridManager
use: easy grid movement with lerp and collision checking