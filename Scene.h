#pragma once
#include "Script.h"
#include <vector>
using namespace std;

class Scene : public Script
{
    using Script::Script;

public:

    void startScript() override;

    void tickScript(float deltaTime) override;

private:
    float duration = 3000;
    float current = 0;
    int aux = 0;
    bool finish = false;
    std::vector<const char*> dialogue = { "Textures/Dialogue/Sans/Start/undertale_text_box_1.png", "Textures/Dialogue/Sans/Start/undertale_text_box_1.png", "Textures/Dialogue/Sans/Start/undertale_text_box_2.png", "Textures/Dialogue/Sans/Start/undertale_text_box_3.png", "Textures/Dialogue/Sans/Start/undertale_text_box_4.png", "Textures/Dialogue/Sans/Start/undertale_text_box_5.png" , "Textures/Dialogue/Sans/Start/undertale_text_box_6.png" };
};