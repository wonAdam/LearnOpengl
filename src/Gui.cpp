#include "Gui.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Game.h"
#include "Camera.h"
#include "Cube.h"
#include "GameObject.h"
#include "PointLight.h"
#include "Spotlight.h"

Gui::Gui()
{
}

Gui::~Gui()
{
}

void Gui::Update()
{
    //------ ImGui Frame ------//
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto& gameObject : Game::Instance()->_gameObjects)
        MakePositioningPanel(gameObject);

    for (auto& pl : Game::Instance()->pointLights)
        MakePositioningPanel(static_cast<GameObject*>(pl));

    for (auto& sl : Game::Instance()->spotLights)
        MakePositioningPanel(static_cast<GameObject*>(sl));

    Camera* camera = Game::Instance()->gCamera;
    ImGui::Begin("Camera");
    std::string buttonText = camera->mouseMode ? "Docking Mode" : "To Mouse Mode";
    if (ImGui::Button(buttonText.c_str()))
    {
        camera->mouseMode = !camera->mouseMode;
    }
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::MakePositioningPanel(GameObject* gameObject)
{
    ImGui::Begin(gameObject->_name.c_str());
    //if (ImGui::Button("Reset"))
    //{
    //    gameObject->_forward.x = 0.0f;
    //    gameObject->_forward.y = 0.0f;
    //    gameObject->_forward.z = 1.0f;
    //    gameObject->_position = glm::vec3(0.0f);
    //}
    ImGui::SliderFloat("forwardX", &gameObject->_forward.x, -1.0f, 1.0f);
    ImGui::SliderFloat("forwardY", &gameObject->_forward.y, -1.0f, 1.0f);
    ImGui::SliderFloat("forwardZ", &gameObject->_forward.z, -1.0f, 1.0f);
    ImGui::SliderFloat("positionX", &gameObject->_position.x, -10.0f, 10.0f);
    ImGui::SliderFloat("positionY", &gameObject->_position.y, -10.0f, 10.0f);
    ImGui::SliderFloat("positionZ", &gameObject->_position.z, -10.0f, 10.0f);
    ImGui::End();
}
