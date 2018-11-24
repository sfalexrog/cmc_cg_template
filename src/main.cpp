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
    }

    std::cout << message << std::endl;
}

int main(int argc, char** argv)
{
    using namespace gl33core;

    Logger::addListener(consoleLogger);
    Logger::addListener(Gui::ImLogger::addMessage);


    LogLine(S_DEBUG) << "Initializing SDL...";
    SDL_Init(SDL_INIT_EVERYTHING);
    LogLine(S_DEBUG) << "Creating window...";
    SDL_Window *w = SDL_CreateWindow("CMC Computer Graphics Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 800, SDL_WINDOW_OPENGL);
    LogLine(S_DEBUG) << "Creating context...";
    const char* glsl_version = "#version 130";

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GLContext ctx = SDL_GL_CreateContext(w);
    glbinding::initialize(reinterpret_cast<glbinding::ContextHandle>(ctx), [](const char* name){return reinterpret_cast<void(*)()>(SDL_GL_GetProcAddress(name));}, true, true);

    bool done = false;

    LogLine(S_DEBUG) << "Creating ImGui rendering context...";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(w, ctx);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Style
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Log(S_DEBUG) << "Showing colors: Debug";
    Log(S_INFO) << "Showing colors: Info";
    Log(S_WARNING) << "Showing colors: Warning";
    Log(S_ERROR) << "Showing colors: Error";
    Log(S_FATAL) << "Showing colors: Fatal error";

    while(!done)
    {
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
        {
            ImGui_ImplSDL2_ProcessEvent(&ev);
            if (ev.type == SDL_QUIT)
                done = true;
        }
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(w);
        ImGui::NewFrame();

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
        ImGui::Render();
        SDL_GL_MakeCurrent(w, ctx);
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(w);
    }



    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}