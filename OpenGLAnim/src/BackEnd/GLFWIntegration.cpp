#include "GLFWIntegration.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

namespace GLFWIntegration {
    GLFWwindow* g_window = NULL;
    WindowedMode g_windowedMode = WindowedMode::WINDOWED;

    GLFWmonitor* g_monitor;
    const GLFWvidmode* g_mode;
    bool g_forceCloseWindow = false;
    bool g_windowHasFocus = true;
    int g_windowedWidth = 0;
    int g_windowedHeight = 0;
    int g_fullscreenWidth = 0;
    int g_fullscreenHeight = 0;
    int g_currentWindowWidth = 0;
    int g_currentWindowHeight = 0;

    bool Init(API api, WindowedMode windowedMode)
    {
        glfwInit();
        if (api == API::OPENGL)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            glfwWindowHint(GLFW_SAMPLES, 0);
        }
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

        g_monitor = glfwGetPrimaryMonitor();
        g_mode = glfwGetVideoMode(g_monitor);
        glfwWindowHint(GLFW_RED_BITS, g_mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, g_mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, g_mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, g_mode->refreshRate);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        g_fullscreenWidth = g_mode->width;
        g_fullscreenHeight = g_mode->height;
        g_windowedWidth = g_fullscreenWidth * 0.75f;
        g_windowedHeight = g_fullscreenHeight * 0.75f;

        g_windowedMode = windowedMode;
        if (g_windowedMode == WindowedMode::WINDOWED) {
            g_currentWindowWidth = g_windowedWidth;
            g_currentWindowHeight = g_windowedHeight;
            g_window = glfwCreateWindow(g_windowedWidth, g_windowedHeight, "Unloved", NULL, NULL);
            glfwSetWindowPos(g_window, 0, 0);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) {
            g_currentWindowWidth = g_fullscreenWidth;
            g_currentWindowHeight = g_fullscreenHeight;
            g_window = glfwCreateWindow(g_fullscreenWidth, g_fullscreenHeight, "Unloved", g_monitor, NULL);
        }
        g_windowedMode = windowedMode;
        if (g_window == NULL) {
            std::cout << "GLFWIntegration() Failed to create window\n";
            glfwTerminate();
            return false;
        }

        return true;
    }

    void BeginFrame(API api) {
        glfwPollEvents();

        // Query window focus
        int focused = glfwGetWindowAttrib(g_window, GLFW_FOCUSED);
        g_windowHasFocus = (focused != 0);
    }

    void EndFrame(API api) {
        if (api == API::OPENGL) {
            glfwSwapBuffers(g_window);
        }
        else if (api == API::VULKAN) {
            // Nothing required
        }
    }

    void MakeContextCurrent() {
        glfwMakeContextCurrent(g_window);
    }

    void* GetWindowPointer() {
        return g_window;
    }

    bool WindowIsOpen() {
        return !(glfwWindowShouldClose(g_window) || g_forceCloseWindow);
    }
}