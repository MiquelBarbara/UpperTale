#include "CharacterController.h"
#include "global.h"
#include <cmath>

void CharacterController::startScript() 
{

}

void CharacterController::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	const float movement = 125.f * deltaTime;
	CheckCollision(deltaTime, movement);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dialogueBoxActive = false;
		if (collisionRight == false) {
			transform->position += glm::vec2(movement, 0.f);
		}
		AFK = false;
		if (currDir.x == 1.0 && currDir.y == 0.0) {
			UpdateAnimation(deltaTime);
		}
		else {
			currDir.x = 1;
			currDir.y = 0;
			changeAnimation(right);
		}	
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		dialogueBoxActive = false;
		if (collisionLeft == false) {
			transform->position += glm::vec2(-movement, 0.f);
		}
		AFK = false;
		if (currDir.x == -1.0 && currDir.y == 0.0) {
			UpdateAnimation(deltaTime);
		}
		else {
			currDir.x = -1;
			currDir.y = 0;
			changeAnimation(left);
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		dialogueBoxActive = false;
		if (collisionTop == false) {
			transform->position += glm::vec2(0.f, -movement);
		}
		AFK = false;
		if (currDir.x == 0. && currDir.y == -1.0) {
			UpdateAnimation(deltaTime);
		}
		else {
			currDir.x = 0;
			currDir.y = -1;
			changeAnimation(top);
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		if (collisionDown == false) {
			transform->position += glm::vec2(0.f, movement);
		}
		AFK = false;
		if (currDir.x == 0.0 && currDir.y == 1.0) {
			UpdateAnimation(deltaTime);
		}
		else {
			currDir.x = 0;
			currDir.y = 1;
			changeAnimation(down);
		}
	}

	else {
		resetAnimation();
		AFK = true;
		UpdateAnimation(deltaTime);
	}


}

void CharacterController::UpdateAnimation(float deltaTime)
{

	ComponentHandle<Sprite> sprite = entity->get<Sprite>();

	if (AFK == false) {
		current.currentTime += deltaTime;

		if ((current.currentTime >= current.frameDuration)) {

			sprite->filepath = current.frameTextures[current.currentFrame];

			current.currentFrame = (current.currentFrame + 1) % current.frameTextures.size();
			current.currentTime = 0.0f;
		}
	}

	if (AFK == true) {
		sprite->filepath = current.frameTextures[0];
	}

	if (current.currentFrame == current.frameTextures.size()) {
		resetAnimation();
	}

}

void CharacterController::resetAnimation() {
	current.currentTime = 0;
	current.currentFrame = 0;
}

void CharacterController::changeAnimation(Animation change) {
	resetAnimation();
	current.frameDuration = change.frameDuration;
	current.frameTextures = change.frameTextures;
}

void CharacterController::CheckCollision(float deltaTime, float movement)
{

	collisionRight = false;
	collisionLeft = false;
	collisionTop = false;
	collisionDown = false;

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	world->each<BoxCollider>([&](Entity* other_ent, ComponentHandle<BoxCollider> other_collider) {

		if (other_ent->getEntityId() == entity->getEntityId()) {
			return;
		}

		ComponentHandle<Transform> other_transform = other_ent->get<Transform>();

		const glm::vec2 playerPosition = transform->position;
		const glm::vec2 otherPosition = other_transform->position;
		const float halfWidth = (collider->width + other_collider->width) * 0.5f;
		const float halfHeight = (collider->height + other_collider->height) * 0.5f;
		auto overlapsAt = [&](const glm::vec2& position) {
			return std::fabs(position.x - otherPosition.x) < halfWidth &&
				std::fabs(position.y - otherPosition.y) < halfHeight;
		};

		const bool overlapsNow = overlapsAt(playerPosition);
		const bool hitsRight = overlapsAt(playerPosition + glm::vec2(movement, 0.f));
		const bool hitsLeft = overlapsAt(playerPosition + glm::vec2(-movement, 0.f));
		const bool hitsTop = overlapsAt(playerPosition + glm::vec2(0.f, -movement));
		const bool hitsDown = overlapsAt(playerPosition + glm::vec2(0.f, movement));

		if (other_collider->isTrigger) {
			if (overlapsNow || hitsRight || hitsLeft || hitsTop || hitsDown) {
				Interact(other_ent, deltaTime);
			}
			return;
		}

		collisionRight = collisionRight || hitsRight;
		collisionLeft = collisionLeft || hitsLeft;
		collisionTop = collisionTop || hitsTop;
		collisionDown = collisionDown || hitsDown;


	});	
}

void CharacterController::Interact(Entity* other_entity, float deltaTime) {

	ComponentHandle<Teleporter> teleporter = other_entity->get<Teleporter>();
	ComponentHandle<Dialogue> dialogue = other_entity->get<Dialogue>();
	ComponentHandle<EventChanger> event = other_entity->get<EventChanger>();


	if (teleporter != NULL) {
		if (teleporter->instant) {
			teleporter->teleport();
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				teleporter->teleport();
			}
		}

	}

	if (dialogue != NULL) {
		interactionTime += deltaTime;
		if (interactionTime >= interactionDuration) {
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				int i = dialogue->numDialog;
				dialogue->NextDialogue(i);
				dialogue->numDialog += 1;
				if (event != NULL) {
					event->goNext();
				}
			}
			interactionTime = 0;
		}
		
	}



}
