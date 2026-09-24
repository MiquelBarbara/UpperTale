#include<iostream>
#include<algorithm>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "ScriptManager.h"
#include "Script.h"

#include "CharacterController.h"
#include "Animator.h"
#include "global.h"
#include "Scene.h"

#include "ECS.h"

using std::cout; 
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace ECS;

GLFWwindow* window; // Game window
const unsigned int width = 800;
const unsigned int height = 800;

float t = 0;
time_t current_time;

World* world;
ScriptManager* scriptManager;

glm::vec2 GLOBALplayerPosition = glm::vec2(600, 400);
glm::vec2 GLOBALsceneID = glm::vec2(0,0);
glm::vec2 LastSceneID = glm::vec2(0, 0);
bool GLOBALsceneUpdate = false;
int eventSans = 0;

Entity* fonsnegreReference;
Entity* friskReference;
Entity* sansReference;
Entity* doorReference;
Entity* dialogueBox;

const char* dialoguePath;
bool dialogueBoxActive;


void SetupGLFW() {

	glfwInit();

	// Tell GLFW we are using OpenGL 3.3 and the CORE profile (only the modern functions)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

bool SetupWindow() {
	//Create a GLFWwindow with size 800x800
	window = glfwCreateWindow(800, 800, "ProgramacioVideojocs", NULL, NULL);
	if (window == NULL) {

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make window part of the current context
	glfwMakeContextCurrent(window);

	//Load GLAD and specify the viewport
	gladLoadGL();
	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

Entity* CreateEntity(glm::vec2 position, float rotation, float scale, const char* filepath, glm::vec3 color,
	bool autoSize = true, glm::vec2 size = glm::vec2(1.0, 1.0), const char* shaderName = "default", bool isActive = true) {
	Entity* ent = world->create();
	ent->assign<Transform>(position, rotation, scale);
	ent->assign<Sprite>(filepath, color, autoSize, size, shaderName, isActive);

	return ent;
}

Entity* CreateEntity() {
	Entity* ent = world->create();

	return ent;
}

Entity* CreateEntity(glm::vec2 position, float rotation, float scale) {
	Entity* ent = world->create();
	ent->assign<Transform>(position, rotation, scale);

	return ent;
}


void CreateFrisk() 
{
	glm::vec2 positionPlayer = GLOBALplayerPosition;
	Entity* frisk = CreateEntity(glm::vec2(positionPlayer.x, positionPlayer.y), 0.f, 1.f, "Textures/Frisk/Down/Frisk_Down_0001.png", glm::vec3(1., 1., 1.), false, glm::vec2(60, 90));
	frisk->assign<BoxCollider>(30.f, 45.f);

	CharacterController* frisk_script = new CharacterController(window, world, frisk);

	frisk->assign<ScriptComponent>(scriptManager->AddScript(frisk_script));

	friskReference = frisk;
}

void CreateSans() {

	Entity* sans = CreateEntity(glm::vec2(500.f, 300.f), 0.f, 1.f, "Textures/Sans/Sans.png", glm::vec3(1., 1., 1.), false, glm::vec2(80, 100));
	sans->assign<BoxCollider>(60, 70, true);
	std::vector<const char*> dialogue4 = { "Textures/Dialogue/Sans/Interaction1/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_2.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_3.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_4.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_6.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_5.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_7.png", "Textures/Dialogue/Sans/Interaction1/undertale_text_box_8.png" };
	sans->assign<Dialogue>(dialogue4);
	sans->assign<EventChanger>(0, 1);
	sansReference = sans;

}

void CreateRoom_1_Scene1() 
{

	Entity* room_1 = CreateEntity(glm::vec2(400.f, 400.f), 0.f, 1.f, "Textures/World/Room_1.png", glm::vec3(1., 1., 1.), false, glm::vec2(800, 800));
	
	Entity* collider_room = CreateEntity(glm::vec2(400.f, 250.f), 0.f, 1.f);
	collider_room->assign<BoxCollider>(900.f, 1.f);

	Entity* collider_room2 = CreateEntity(glm::vec2(660.f, 250.f), 0.f, 1.f);
	collider_room2->assign<BoxCollider>(1.f, 900.f);

	Entity* collider_room3 = CreateEntity(glm::vec2(110.f, 250.f), 0.f, 1.f);
	collider_room3->assign<BoxCollider>(1.f, 900.f);

	Entity* collider_room4 = CreateEntity(glm::vec2(100.f, 800.f), 0.f, 1.f);
	collider_room4->assign<BoxCollider>(220.f, 300.f);

	Entity* collider_room5 = CreateEntity(glm::vec2(600.f, 800.f), 0.f, 1.f);
	collider_room5->assign<BoxCollider>(500.f, 300.f);

	Entity*bed = CreateEntity(glm::vec2(605.f, 350.f), 0.f, 1.f);
	bed->assign<BoxCollider>(130, 130, true);
	std::vector<const char*> dialogue = { "Textures/Dialogue/Objects/Cama/undertale_text_box_1.png", "Textures/Dialogue/Objects/Cama/undertale_text_box_1.png" };
	bed->assign<Dialogue>(dialogue);

	Entity* armario = CreateEntity(glm::vec2(220.f, 300.f), 0.f, 1.f);
	armario->assign<BoxCollider>(170, 80, true);
	std::vector<const char*> dialogue2 = { "Textures/Dialogue/Objects/Armario/undertale_text_box_1.png", "Textures/Dialogue/Objects/Armario/undertale_text_box_1.png", "Textures/Dialogue/Objects/Armario/undertale_text_box_2.png" };
	armario->assign<Dialogue>(dialogue2);

	Entity* calcetines = CreateEntity(glm::vec2(160.f, 620.f), 0.f, 1.f, "Textures/World/Room_1.png", glm::vec3(1., 1., 1.), false, glm::vec2(100, 0));
	calcetines->assign<BoxCollider>(110, 80, true);
	std::vector<const char*> dialogue3 = { "Textures/Dialogue/Objects/Calcetines/undertale_text_box_1.png", "Textures/Dialogue/Objects/Calcetines/undertale_text_box_1.png"};
	calcetines->assign<Dialogue>(dialogue3);
	calcetines->assign<EventChanger>(-1, 2);

	Entity* trigger = CreateEntity(glm::vec2(300.f, 800.f), 0.f, 1.f);
	trigger->assign<BoxCollider>(500.f, 100.f, true);
	trigger->assign<Teleporter>(glm::vec2(500, 300), glm::vec2(1,0));
}


void CreateRoom_2_Scene2() 
{

	Entity* room_2 = CreateEntity(glm::vec2(400.f + width, 400.f ), 0.f, 1.f, "Textures/World/House.png", glm::vec3(1., 1., 1.), false, glm::vec2(800, 800));


	Entity* collider_room = CreateEntity(glm::vec2(400.f + width , 210.f), 0.f, 1.f);
	collider_room->assign<BoxCollider>(800.f, 1.f);

	Entity* collider_room2 = CreateEntity(glm::vec2(700.f + width, 250.f), 0.f, 1.f);
	collider_room2->assign<BoxCollider>(1.f, 800.f);

	Entity* collider_room3 = CreateEntity(glm::vec2(110.f + width, 250.f), 0.f, 1.f);
	collider_room3->assign<BoxCollider>(1.f, 800.f);

	Entity* collider_room4 = CreateEntity(glm::vec2(100.f + width, 800.f), 0.f, 1.f);
	collider_room4->assign<BoxCollider>(780.f, 300.f);

	Entity* collider_room5 = CreateEntity(glm::vec2(700.f + width, 800.f), 0.f, 1.f);
	collider_room5->assign<BoxCollider>(200.f, 300.f);

	Entity* door = CreateEntity(glm::vec2(500.f + width, 170.f), 0.f, 1.f);
	door->assign<BoxCollider>(100.f, 100.f, true);
	door->assign<Teleporter>(glm::vec2(300, 700), glm::vec2(0, 0), false);
	doorReference = door;

	Entity* cartel = CreateEntity(glm::vec2(200.f + width, 170.f), 0.f, 1.f);
	cartel->assign<BoxCollider>(200, 100, true);
	std::vector<const char*> dialogue4 = { "Textures/Dialogue/Objects/Bandera/undertale_text_box_1.png", "Textures/Dialogue/Objects/Bandera/undertale_text_box_1.png", "Textures/Dialogue/Objects/Bandera/undertale_text_box_2.png", "Textures/Dialogue/Objects/Bandera/undertale_text_box_3.png" };
	cartel->assign<Dialogue>(dialogue4);

	Entity* exterior = CreateEntity(glm::vec2(600.f + width, 800.f), 0.f, 1.f);
	exterior->assign<BoxCollider>(200, 100, true);
	std::vector<const char*> dialogue5 = { "Textures/Dialogue/Objects/Exterior/undertale_text_box_1.png", "Textures/Dialogue/Objects/Exterior/undertale_text_box_1.png"};
	exterior->assign<Dialogue>(dialogue5);
}

int CloseUp() {
	// Cleanup

	glfwDestroyWindow(window);
	glfwTerminate();

	world->destroyWorld();

	return 0;
}

void UpdateSansEvents(int change) {
	ComponentHandle<Dialogue> dialogueS = sansReference->get<Dialogue>();
	ComponentHandle<Transform> sansPosition = sansReference->get<Transform>();

	ComponentHandle<EventChanger> event = sansReference->get<EventChanger>();

	vector<const char*> dialogues1 = { "Textures/Dialogue/Sans/Interaction2/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction2/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction2/undertale_text_box_2.png" };
	vector<const char*> dialogues2 = { "Textures/Dialogue/Sans/Interaction3/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction3/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction3/undertale_text_box_2.png"};
	vector<const char*> dialogues3 = { "Textures/Dialogue/Sans/Interaction4/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction4/undertale_text_box_1.png", "Textures/Dialogue/Sans/Interaction4/undertale_text_box_2.png", "Textures/Dialogue/Sans/Interaction4/undertale_text_box_3.png" };

	switch (change) {
	case 1:
		sansPosition->position += glm::vec2((GLOBALsceneID.x - LastSceneID.x) * 900, (GLOBALsceneID.y - LastSceneID.y) * 200);
		dialogueS->dialogues = dialogues1;
		break;
	case 2:
		dialogueS->dialogues = dialogues2;
		event->eventIn = 2;
		event->eventToGo = 3;
		break;
	case 3: 
		dialogueS->dialogues = dialogues3;
		break;
	}
}

void UpdatePosition() {
	world->each<Transform>([&](Entity* other_ent, ComponentHandle<Transform> other_collider) {
		ComponentHandle<Transform> transform = other_ent->get<Transform>();
		transform->position -= glm::vec2((GLOBALsceneID.x - LastSceneID.x) * width, (GLOBALsceneID.y  - LastSceneID.y)* height);
		
	});
}

void UpdateFriskPosition() {
	ComponentHandle<Transform> friskPosition = friskReference->get<Transform>();
	friskPosition->position = GLOBALplayerPosition;
}

void UpdateDialogue() {
	ComponentHandle<Sprite> sprite = dialogueBox->get<Sprite>();
	sprite->filepath = dialoguePath;
	sprite->isActive = dialogueBoxActive;
}

void UpdateEvents() {
	UpdateSansEvents(eventSans);
}

void UpdateDialogueBoxPosition() {
	ComponentHandle<Transform> dialogueBox2 = dialogueBox->get<Transform>();
	dialogueBox2->position += glm::vec2((GLOBALsceneID.x - LastSceneID.x) * width, (GLOBALsceneID.y - LastSceneID.y) * height);
}

void SetupWorld() {

	world = World::createWorld();
	world->registerSystem(new RenderSystem(width, height));
	ScriptSystem* scriptSystem = new ScriptSystem();
	world->registerSystem(scriptSystem);
	ScriptManager* scriptManager2 = scriptSystem->getScriptManager();

	scriptManager = scriptManager2;

	CreateRoom_1_Scene1();
	CreateRoom_2_Scene2();
	CreateSans();
	CreateFrisk();

	Entity* fonsnegre = CreateEntity(glm::vec2(400.f, 400), 0.f, 1.f, "Textures/Dialogue/World/fonsnegre.png", glm::vec3(1., 1., 1.), false, glm::vec2(800, 800));
	Scene* fons_script = new Scene(window, world, fonsnegre);
	fonsnegre->assign<ScriptComponent>(scriptManager->AddScript(fons_script));
	fonsnegreReference = fonsnegre;

	Entity* dialogueBox2 = CreateEntity(glm::vec2(400.f, 600.f), 0.f, 1.f, "Textures/Dialogue/Sans/Start/undertale_text_box_1.png", glm::vec3(1., 1., 1.), false, glm::vec2(700, 200));

	dialogueBox = dialogueBox2;

	scriptSystem->start(world);
	
}


int  main() {
	
	SetupGLFW();

	if (!SetupWindow()) {
		return -1;
	}

	SetupWorld();

	double previousTime = glfwGetTime();

	//Program core loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;
		// Clamp delayed frames to prevent large movement steps.
		dt = std::min(dt, 0.05f);
		world->tick(dt);
				
		if (GLOBALsceneUpdate) {
			UpdatePosition();
			UpdateEvents();
			UpdateFriskPosition();
			UpdateDialogueBoxPosition();
			GLOBALsceneUpdate = false;
			LastSceneID = GLOBALsceneID;
		}
		UpdateDialogue();
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
			fonsnegreReference->removeAll();
		}

		glfwSwapBuffers(window); //Swap buffers

		// Take care of GLFW events
		glfwPollEvents();

	}

	return CloseUp();

}
