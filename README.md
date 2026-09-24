# UpperTale

**UpperTale** is a small Undertale-inspired 2D walking simulator developed in **C++ and OpenGL** as part of my **Multimedia Engineering degree**.

The project was built to learn the fundamentals of **Entity Component System (ECS) architecture** and **2D texture rendering**. The demo allows the player to explore a small environment, interact with objects, and progress through dialogues with Sans.

<img width="794" height="792" alt="image" src="https://github.com/user-attachments/assets/487bab86-6c15-42a3-a75c-6905d11dade7" />


## What I Implemented

My main contributions to the project were:

* **Character Controller** — movement, input and interactions
* **Collision System** — AABB collisions and trigger areas
* **Animation System** — frame-based sprite animations
* **Event System** — simple event progression that changes dialogue and interactions

The project also includes scene transitions, dialogue interactions, sprite rendering, shaders, and texture management.

## Tech Stack

**C++ · OpenGL 3.3 · GLSL · ECS · GLFW · GLAD · GLM · stb_image**

## Controls

| Key     | Action                         |
| ------- | ------------------------------ |
| `WASD`  | Move                           |
| `E`     | Interact / advance dialogue    |
| `Enter` | Start / dismiss initial screen |

## Running the Project

Clone the repository and open `UpperTale.sln` with **Visual Studio**. The required third-party libraries are included in the repository.

```bash
git clone https://github.com/MiquelBarbara/UpperTale.git
```

> **Note:** UpperTale is a non-commercial educational project inspired by Undertale. Undertale and its characters/assets belong to their respective copyright holders.
