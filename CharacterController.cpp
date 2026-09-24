#include "CharacterController.h"
#include "global.h"

void CharacterController::startScript() 
{

}

void CharacterController::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	CheckCollision(deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dialogueBoxActive = false;
		if (collisionRight == false) {
			transform->position += glm::vec2(1., 0.) * deltaTime / 8.f;
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
			transform->position += glm::vec2(-1., 0.) * deltaTime / 8.f;
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
			transform->position += glm::vec2(0., -1.) * deltaTime / 8.f;
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
			transform->position += glm::vec2(0., 1.) * deltaTime / 8.f;
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

void CharacterController::CheckCollision(float deltaTime) 
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

		glm::vec2 p1 = transform->position;
		glm::vec2 p2 = other_transform->position;

		float XD1 = p2.y - other_collider->height / 2;
		float XD2 = p1.y - collider->height / 2;
		float XD3 = p2.y + other_collider->height / 2;
		float XD4 = p1.y + collider->height / 2;
		float XD5 = p1.x - collider->width / 2;
		float XD6 = p2.x + other_collider->width / 2;
		float XD7 = p2.x - other_collider->width / 2;
		float XD8 = p1.x + collider->width / 2;

		bool point1 = (XD1 < XD2) && (XD2 < XD3);
		bool point2 = (XD3 > XD4) && (XD4 > XD1);

		bool point3 = (XD7 < XD8) && (XD8 < XD6);
		bool point4 = (XD6 > XD5) && (XD5 > XD7);
		


		if ((point1 || point2) && (fabs(XD5-XD6) == 1)) {

			if (other_collider->isTrigger == true) {
				Interact(other_ent, deltaTime);
				
			}
			collisionLeft = true;
		}

		if ((point1 || point2) && (fabs(XD8-XD7) == 1)) {
			if (other_collider->isTrigger == true) {

				Interact(other_ent, deltaTime);
				
			}
			collisionRight = true;
		}

		if ((point3 || point4) && (fabs(XD2-XD3) == 1)) {
			if (other_collider->isTrigger == true) {
				Interact(other_ent, deltaTime);
				
			}
			collisionTop = true;
		}

		if ((point3 || point4) && (fabs(XD4-XD1) == 1)) {

			if (other_collider->isTrigger == true) {

				Interact(other_ent, deltaTime);
				
			}
			collisionDown = true;
		}


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


