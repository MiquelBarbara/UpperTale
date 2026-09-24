#include "Animator.h"

void Animator::startScript()
{

}

void Animator::Update(float deltaTime)
{
    cout << ("Me mogut") << endl;
    animation.currentTime += deltaTime;

    if (animation.currentTime >= animation.frameDuration) {
        animation.currentFrame = (animation.currentFrame + 1) % animation.frameTextures.size();
        animation.currentTime = 0.0f;
        sprite->filepath = animation.frameTextures[animation.currentFrame];
    }

   
}

void Animator::resetAnimation() {
    animation.currentTime = 0;
    animation.currentFrame = 0;
}

void Animator::changeAnimation(Animation change) {
    animation.frameDuration = change.frameDuration;
    animation.frameTextures = change.frameTextures;
}






