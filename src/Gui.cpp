#include "Gui.h"
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Game.h"
#include "Camera.h"
#include "Cube.h";

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

    GameObject* cube = Game::Instance()->_gameObjects[0];
    // render your GUI
    ImGui::Begin("Cube");
    ImGui::Button("Hello!");
    ImGui::SliderFloat("forwardX", &cube->_forward.x, 0, 1.0f);
    ImGui::SliderFloat("forwardY", &cube->_forward.y, 0, 1.0f);
    ImGui::SliderFloat("forwardZ", &cube->_forward.z, 0, 1.0f);
    ImGui::SliderFloat("positionX", &cube->_position.x, -2.0f, 2.0f);
    ImGui::SliderFloat("positionY", &cube->_position.y, -2.0f, 2.0f);
    ImGui::SliderFloat("positionZ", &cube->_position.z, -2.0f, 2.0f);
    ImGui::End();

    Camera* camera = Game::Instance()->gCamera;
    ImGui::Begin("Camera");
    std::string buttonText = camera->mouseMode ? "To Slide Mode" : "To Mouse Mode";
    if (ImGui::Button(buttonText.c_str()))
    {
        camera->mouseMode = !camera->mouseMode;
    }
    if (!camera->mouseMode)
    {
        ImGui::SliderFloat("forwardX", &camera->_forward.x, -2.0f, 2.0f);
        ImGui::SliderFloat("forwardY", &camera->_forward.y, -2.0f, 2.0f);
        ImGui::SliderFloat("forwardZ", &camera->_forward.z, -2.0f, 2.0f);
        ImGui::SliderFloat("positionX", &camera->_position.x, -2.0f, 2.0f);
        ImGui::SliderFloat("positionY", &camera->_position.y, -2.0f, 2.0f);
        ImGui::SliderFloat("positionZ", &camera->_position.z, -2.0f, 2.0f);
    }
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
