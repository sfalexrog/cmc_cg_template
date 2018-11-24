#include "logger.h"
#include <vector>

namespace Logger
{
    std::vector<LogListener> listeners;

    void addListener(const LogListener &listener)
    {
        listeners.push_back(listener);
    }

    void clearListeners()
    {
        listeners.clear();
    }

    Logstream::~Logstream()
    {
        for(auto& listener : listeners)
        {
            listener(severity, ss.str());
        }
    }
}
