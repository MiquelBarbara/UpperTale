#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include "global.h"

struct Transform
{
    Transform(glm::vec2 position, float rotation, float scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::vec2 position;
    float rotation;
    float scale;
};

struct Sprite
{
    Sprite(const char* filepath, glm::vec3 color, bool autoSize = true, glm::vec2 size = glm::vec2(1, 1), const char* shaderName = "default",bool isActive = true) {
        this->filepath = filepath;
        this->color = color;
        this->autoSize = autoSize;
        this->size = size;
        this->shaderName = shaderName;
        this->isActive = isActive;
    }

    const char* filepath;
    glm::vec3 color;
    bool autoSize;
    glm::vec2 size = glm::vec2(1, 1);
    const char* shaderName;
    bool isActive;
};

struct BoxCollider
{
    BoxCollider(float w, float h, bool isTrigger = false) {
        this->width = w;
        this->height = h;
        this->isTrigger = isTrigger;
    }

    float width = 0;
    float height = 0;
    bool collidedWith = false;
    bool isTrigger;
};

struct ScriptComponent
{
    ScriptComponent(int scriptId) {
        this->scriptId = scriptId;
    }

    int scriptId = -1;
};

struct Animation 
{
    Animation(){}

    Animation(std::vector<const char*> filepath, float frameDuration)
    {
        this->frameTextures = filepath;
        this->frameDuration = frameDuration;
    }

    std::vector<const char*>  frameTextures;  // Texturas de cada fotograma
    int currentFrame;                   // Fotograma actual
    float frameDuration;                // Duración de cada fotograma en segundos
    float currentTime;                  // Tiempo actual de la animación
      
};


struct Teleporter {

    Teleporter(glm::vec2 playerPosition, glm::vec2 sceneID, bool instant = true) {
        this->playerPosition = playerPosition;
        this->sceneID = sceneID;
        this->instant = instant;
    }
    void teleport() {
        GLOBALplayerPosition = playerPosition;
        GLOBALsceneID = sceneID;
        GLOBALsceneUpdate = true;
    }

    bool instant;
    glm::vec2 playerPosition;
    glm::vec2 sceneID;
};

struct Dialogue {

    Dialogue(std::vector<const char*>  dialogues) {
        this->dialogues = dialogues;
    }

    void NextDialogue(int i) {

        if (numDialog == dialogues.size()) {
            numDialog = 0;
            dialogueBoxActive = false;
            dialoguePath = NULL;
            return;
        }
        else {
            dialoguePath = dialogues[i];
            dialogueBoxActive = true;
        }

    }

    std::vector<const char*>  dialogues;
    int numDialog = 1;
};

struct EventChanger{
    EventChanger(int eventIn, int eventToGo) {
        this->eventToGo = eventToGo;
        this->eventIn = eventIn;
    }

    void goNext() {
        if (eventIn == eventSans || eventIn == -1) {
            eventSans = eventToGo;
        }
    }

    int eventToGo;
    int eventIn;
};



