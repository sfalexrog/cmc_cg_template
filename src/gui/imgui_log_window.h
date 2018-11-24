#ifndef CMC_CG_TEMPLATE_IMGUI_LOG_WINDOW_H
#define CMC_CG_TEMPLATE_IMGUI_LOG_WINDOW_H

#include "util/logger.h"

namespace Gui
{
    namespace ImLogger
    {
        void draw();
        void addMessage(Logger::Severity severity, const std::string& message);
    }
}

#endif //CMC_CG_TEMPLATE_IMGUI_LOG_WINDOW_H
