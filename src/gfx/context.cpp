#include "context.h"
#include <SDL.h>
#include <imgui.h>
#include "imgui_impl/imgui_impl_opengl3.h"
#include "imgui_impl/imgui_impl_sdl.h"
#include "util/logger.h"
#include "util/config.h"

#include <glbinding/glbinding.h>
#include <glbinding-aux/ContextInfo.h>

namespace Gfx
{
    struct ContextData
    {
        SDL_Window *window;
        SDL_GLContext glContext;
        ImGuiContext *imGuiContext;
    };

    const char* glsl_version = "#version 330";

    Context::Context() : data(new ContextData)
    {
        LogLine(S_DEBUG) << "Creating window (size: " << Config::windowWidth << "x" << Config::windowHeight << ")";
        data->window = SDL_CreateWindow("CMC Computer Graphics Task",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                Config::windowWidth,
                Config::windowHeight,
                SDL_WINDOW_OPENGL);
        LogLine(S_DEBUG) << "Setting OpenGL context attributes";

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        LogLine(S_DEBUG) << "Creating OpenGL context";
        data->glContext = SDL_GL_CreateContext(data->window);

        glbinding::initialize(reinterpret_cast<glbinding::ContextHandle>(data->glContext),
                [](const char* name){return reinterpret_cast<void(*)()>(SDL_GL_GetProcAddress(name));},
                true,
                false);

        LogLine(S_DEBUG) << "Context information: " << glbinding::aux::ContextInfo::version().toString();

        IMGUI_CHECKVERSION();
        data->imGuiContext = ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(data->window, data->glContext);
        ImGui_ImplOpenGL3_Init(glsl_version);

    }

    Context::~Context()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext(data->imGuiContext);

        SDL_GL_DeleteContext(data->glContext);
        SDL_DestroyWindow(data->window);
    }

    void Context::startFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(data->window);
        ImGui::NewFrame();
    }

    void Context::endFrame()
    {
        ImGui::Render();
    }

    void Context::swap()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(data->window);
    }

    void Context::makeCurrent()
    {
        SDL_GL_MakeCurrent(data->window, data->glContext);
    }
}