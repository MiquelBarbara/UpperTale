#pragma once
#include "Script.h"

using namespace std;

class Animator : public Script 
{
    using Script::Script;

public:

    void startScript() override;

    void Update(float deltaTime);

    void resetAnimation();

    void changeAnimation(Animation animation);

    ComponentHandle<Sprite> sprite = entity->get<Sprite>();

    Animation animation;

};
