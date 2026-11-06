# 3D Model Viewer

**A real-time 3D model viewer written in C++ with OpenGL and GLSL.**

This project is a small custom rendering engine and model viewer built from the ground up.  
It loads Wavefront OBJ files, applies textures and custom shaders, and renders them with a free-flying camera, dynamic lighting and a skybox.

The goal was to understand the full render pipeline without relying on a game engine: window creation, mesh loading, shader compilation, texture and cubemap handling, camera movement and basic scene management.

---

## What is this?

- A lightweight OpenGL-based 3D model viewer
- A small scene system with polymorphic `SceneElement`s
- Runtime model import via ImGui (select .obj, vertex/fragment shaders and texture)

---

## Core Features

- **Custom Engine loop**  
  Handles window, input, camera, lighting, skybox and scene elements.

- **SceneElement hierarchy**  
  Base class for all renderable objects (Camera, Light, Skybox, Demo models, etc.).

- **OBJ Loader**  
  Parses positions, normals, UVs and faces from Wavefront .obj files.

- **Shader system**  
  Loads, compiles and links GLSL vertex + fragment shaders. Supports common uniforms (model/view/proj, light, view position, textures).

- **Texture & Cubemap support**  
  2D textures and 6-face cubemaps for skyboxes.

- **Camera**  
  FPS-style free camera with mouse look and WASD + vertical movement.

- **Dynamic light**  
  Animated light source with changing color and position.

- **ImGui Model Import UI**  
  Select .obj, vertex shader, fragment shader and texture at runtime and load the model into the scene.

---

## Controls

| Input              | Action                  |
|--------------------|-------------------------|
| WASD               | Move camera             |
| Space / E          | Move up                 |
| Left Shift / Q     | Move down               |
| Mouse              | Look around             |
| Escape             | Toggle cursor lock      |
| Mouse X1 / X2      | Change demo rotation speed |

---

## Building

### Requirements
- C++20
- GLFW
- GLAD
- GLM
- ImGui + ImGuiFileDialog
- stb_image

### Steps
1. Make sure all dependencies are available
2. Open the project in Visual Studio (or your preferred C++ environment)
3. Build and run

The application starts with a skybox, a moving light and an empty scene. Use the ImGui window to import models.

---

## Project Structure (Core)

| Component              | Purpose                                      |
|------------------------|----------------------------------------------|
| `Engine`               | Main loop, object management, rendering      |
| `Window`               | GLFW window + OpenGL context                 |
| `SceneElement`         | Base class for all scene objects             |
| `CameraElement`        | Free-flying camera                           |
| `LightSourceElement`   | Animated light source                        |
| `SkyboxElement`        | Cubemap skybox                               |
| `Mesh` / `ObjLoader`   | Geometry and OBJ loading                     |
| `Shader`               | GLSL program management                      |
| `Texture` / `CubeMap`  | Texture and cubemap handling                 |
| `GUIDrawer`            | ImGui model import interface                 |
| `Input` / `Time`       | Input state and delta time                   |

---

## License

MIT License - see [LICENSE](LICENSE)
