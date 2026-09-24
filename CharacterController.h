#pragma once
#include "Script.h"
#include <vector>
using namespace std;

class CharacterController : public Script
{
    using Script::Script;

public:

    void startScript() override;

    void tickScript(float deltaTime) override;

    void UpdateAnimation(float deltaTime);

    void resetAnimation();

    void changeAnimation(Animation animation);

    void Interact(Entity* entity, float deltaTime);

    glm::vec2 currDir = glm::vec2(0., 1.);

    bool AFK = true;

    bool collisionRight;
    bool collisionLeft;
    bool collisionTop;
    bool collisionDown;

private:

    std::vector<const char*> topTexture = {"Textures/Frisk/Top/Frisk_Top_0001.png", "Textures/Frisk/Top/Frisk_Top_0002.png", "Textures/Frisk/Top/Frisk_Top_0003.png", "Textures/Frisk/Top/Frisk_Top_0004.png" };
    Animation top = Animation(topTexture, 100);

    std::vector<const char*> downTexture = { "Textures/Frisk/Down/Frisk_Down_0001.png", "Textures/Frisk/Down/Frisk_Down_0002.png", "Textures/Frisk/Down/Frisk_Down_0003.png", "Textures/Frisk/Down/Frisk_Down_0004.png" };
    Animation down = Animation(downTexture, 100);

    std::vector<const char*> leftTexture = { "Textures/Frisk/Left/Frisk_Left_0001.png", "Textures/Frisk/Left/Frisk_Left_0002.png", "Textures/Frisk/Left/Frisk_Left_0003.png", "Textures/Frisk/Left/Frisk_Left_0004.png" };
    Animation left = Animation(leftTexture, 100);

    std::vector<const char*> rightTexture = { "Textures/Frisk/Right/Frisk_Right_0001.png", "Textures/Frisk/Right/Frisk_Right_0002.png", "Textures/Frisk/Right/Frisk_Right_0003.png", "Textures/Frisk/Right/Frisk_Right_0004.png" };
    Animation right = Animation(rightTexture, 100);

    void CheckCollision(float deltaTime);

    Animation current = down;

    float interactionTime = 0;
    float interactionDuration = 165;
    
};
