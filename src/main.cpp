#include <SDL.h>
#include <imgui.h>
#include "imgui_impl/imgui_impl_sdl.h"
#include "imgui_impl/imgui_impl_opengl3.h"

#include <glbinding/glbinding.h>

#include <glbinding/gl33core/gl.h>


#include "util/logger.h"
#include <string>
#include <iostream>

#include "gui/imgui_log_window.h"

#include "gfx/context.h"

#include <assimp/Importer.hpp>

#include "gfx/shader.h"

void consoleLogger(Logger::Severity severity, const std::string& message)
{
    switch(severity)
    {
        case Logger::Severity::S_DEBUG:
            std::cout << "[DEBUG] ";
            break;
        case Logger::Severity ::S_INFO:
            std::cout << "[INFO] ";
            break;
        case Logger::Severity ::S_WARNING:
            std::cout << "[WARNING] ";
            break;
        case Logger::Severity ::S_ERROR:
            std::cout << "[ERROR] ";
            break;
        case Logger::Severity ::S_FATAL:
            std::cout << "[FATAL] ";
            break;
        default:
            std::cout << "[UNKNOWN!]";
            break;
    }

    std::cout << message << std::endl;
}

void loop()
{
    using namespace gl33core;

    Gfx::Context context;
    bool done = false;
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGuiIO &io = ImGui::GetIO();


    Gfx::Shader shader;

    shader.addStage("shaders/tonemap_reinhard.vert")
          .addStage("shaders/tonemap_reinhard.frag")
          .link();

    while (!done)
    {
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
        {
            ImGui_ImplSDL2_ProcessEvent(&ev);
            if (ev.type == SDL_QUIT)
                done = true;
        }
        // Start the Dear ImGui frame
        context.startFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        Gui::ImLogger::draw();

        // Rendering
        context.endFrame();
        context.makeCurrent();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        context.swap();

    }

}

int main(int argc, char** argv)
{
    using namespace gl33core;

    Logger::addListener(consoleLogger);
    Logger::addListener(Gui::ImLogger::addMessage);


    LogLine(S_DEBUG) << "Initializing SDL...";
    SDL_Init(SDL_INIT_EVERYTHING);

    Log(S_DEBUG) << "Showing colors: Debug";
    Log(S_INFO) << "Showing colors: Info";
    Log(S_WARNING) << "Showing colors: Warning";
    Log(S_ERROR) << "Showing colors: Error";
    Log(S_FATAL) << "Showing colors: Fatal error";

    loop();

    SDL_Quit();
    return 0;
}