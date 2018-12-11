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

#include "gfx/shader.h"

#include "util/sceneloader.h"

#include "gfx/camera.h"

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

    Gfx::Scene s = loadSceneFromFile("scenes/sponza/sponza.obj");

    Gfx::Shader tonemapShader;

    tonemapShader.addStage("shaders/tonemap_reinhard.vert")
        .addStage("shaders/tonemap_reinhard.frag")
        .link();

    Gfx::Shader normalShader;
    normalShader.addStage("shaders/debug_normal.vert")
        .addStage("shaders/debug_normal.frag")
        .link();

    Gfx::Camera c;
    c.moveTo(glm::vec3(0.0f, 1.0f, 0.0f));

    s.initVAO();

    glEnable(GL_DEPTH_TEST);

    enum Btn
    {
        Forward = 0,
        Back = 1,
        Left = 2,
        Right = 3,

        NUM_BUTTONS
    };

    bool buttonsState[NUM_BUTTONS];

    struct MousePos{
        int x;
        int y;
    } lastMousePos{};

    SDL_GetMouseState(&lastMousePos.x, &lastMousePos.y);

    const float camSpeed = 0.05f;

    while (!done)
    {
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
        {
            ImGui_ImplSDL2_ProcessEvent(&ev);
            if (ev.type == SDL_QUIT)
                done = true;
        }
        // Read buttons state
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        buttonsState[Forward] = state[SDL_SCANCODE_W];
        buttonsState[Back] = state[SDL_SCANCODE_S];
        buttonsState[Left] = state[SDL_SCANCODE_A];
        buttonsState[Right] = state[SDL_SCANCODE_D];
        if (!io.WantCaptureKeyboard)
        {
            if (buttonsState[Forward])
            {
                c.moveForward(camSpeed);
            }
            if (buttonsState[Back])
            {
                c.moveForward(-camSpeed);
            }
            if (buttonsState[Left])
            {
                c.moveSide(-camSpeed);
            }
            if (buttonsState[Right])
            {
                c.moveSide(camSpeed);
            }
        }

        MousePos curMousePos{};

        int mousePressed = SDL_GetMouseState(&curMousePos.x, &curMousePos.y);

        if (mousePressed && !io.WantCaptureMouse)
        {
            MousePos delta{curMousePos.x - lastMousePos.x, curMousePos.y - lastMousePos.y};
            c.rotateX(delta.x * 0.005f)
             .rotateY(-delta.y * 0.005f);

        }

        lastMousePos = curMousePos;

        // Start the Dear ImGui frame
        context.startFrame();

        Gui::ImLogger::draw();

        // Rendering
        context.endFrame();
        context.makeCurrent();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        c.setAspect(io.DisplaySize.x / io.DisplaySize.y);

        s.draw(c, normalShader);

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

    loop();

    SDL_Quit();
    return 0;
}