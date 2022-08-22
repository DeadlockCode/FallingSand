#pragma once

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>

#include "Renderer.h"
#include "Texture.h"

enum class ColorChannel {
    RED,
    GREEN,
    BLUE,
    ALPHA
};

class BaseApplication {
private:
    GLFWwindow* m_window;
    Texture* m_texture;
public:
    BaseApplication();
    ~BaseApplication();

    void Run();

    virtual void Start()   = 0;
    virtual void Update()  = 0;
    virtual void Draw()    = 0;
    virtual void OnImGui() = 0;
    virtual void Quit()    = 0;

    void SetPixel(u32 i, u32 color) {
        m_texture->SetPixel(i, color);
    }
    void SetPixel(u32 i, ColorChannel colorChannel, u8 color) {
        m_texture->SetPixel(i, (int)colorChannel, color);
    }

    bool GetButton(int button) { return glfwGetMouseButton(m_window, button) == GLFW_PRESS; }
    void GetMousePos(double& x, double& y) { glfwGetCursorPos(m_window, &x, &y); }
};