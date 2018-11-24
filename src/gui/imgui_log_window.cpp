#include "imgui_log_window.h"
#include "util/logger.h"
#include <imgui.h>

#include <vector>


namespace Gui
{
    namespace ImLogger
    {
        namespace
        {
            using LogMessage = std::pair<Logger::Severity, const std::string>;
            std::vector<LogMessage> messages;

            ImGuiTextFilter filter;

            /* Text colors for different types of messages */
            ImVec4 colors[static_cast<unsigned int>(Logger::Severity::S_NUM_SEVERITIES)] = {
                    ImVec4{0.7f, 0.7f, 0.7f, 1.0f},    /* debug */
                    ImVec4{1.0f, 1.0f, 1.0f, 1.0f},    /* info */
                    ImVec4{1.0f, 1.0f, 0.0f, 1.0f},    /* warning */
                    ImVec4{1.0f, 0.0f, 0.0f, 1.0f},    /* error */
                    ImVec4{0.7f, 0.0f, 0.0f, 1.0f}     /* fatal */
            };

            void clear()
            {
                messages.clear();
            }
            void drawMessage(const LogMessage& msg)
            {
                const char* prefix = "";
                auto color = static_cast<unsigned int>(msg.first);
                switch(msg.first)
                {
                    case Logger::Severity::S_DEBUG:
                        prefix = "[DEBUG] ";
                        break;
                    case Logger::Severity::S_INFO:
                        prefix = "[INFO] ";
                        break;
                    case Logger::Severity::S_WARNING:
                        prefix = "[WARNING] ";
                        break;
                    case Logger::Severity::S_ERROR:
                        prefix = "[ERROR] ";
                        break;
                    case Logger::Severity::S_FATAL:
                        prefix = "[FATAL] ";
                        break;
                    default:
                        break;
                }
                ImGui::PushStyleColor(ImGuiCol_Text, colors[color]);
                ImGui::TextUnformatted(prefix);
                ImGui::SameLine();
                ImGui::TextUnformatted(msg.second.c_str());
                ImGui::PopStyleColor();
            }
        }

        void draw()
        {
            ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
            ImGui::Begin("Logger");
            if (ImGui::Button("Clear")) clear();
            ImGui::SameLine();
            filter.Draw();
            ImGui::Separator();
            ImGui::BeginChild("scrolling");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));
            for(const auto& line : messages)
            {
                if (!filter.IsActive() || filter.PassFilter(line.second.c_str()))
                {
                    drawMessage(line);
                }
            }
            ImGui::PopStyleVar();
            ImGui::EndChild();
            ImGui::End();
        }

        void addMessage(Logger::Severity severity, const std::string &message)
        {
            messages.emplace_back(severity, message);
        }
    }
}
