#include "Scene.h"
#include "global.h"

void Scene::startScript()
{

}

void Scene::tickScript(float deltaTime) {
	if (finish == false) {
		current += deltaTime;

		if (current >= duration) {

			dialoguePath = dialogue[aux];
			dialogueBoxActive = true;
			aux += 1;
			current = 0;
		}

		if (aux == dialogue.size()) {
			finish = true;
		}
	}
}
