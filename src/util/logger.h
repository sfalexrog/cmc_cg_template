#ifndef CMC_CG_TEMPLATE_LOGGER_H
#define CMC_CG_TEMPLATE_LOGGER_H

#include <string>
#include <sstream>
#include <functional>

namespace Logger
{
    /**
     * Log message severity
     *
     * Prefixed with S_ to avoid name clashes
     *
     */
    enum class Severity : unsigned int
    {
        S_DEBUG = 0,
        S_INFO = 1,
        S_WARNING = 2,
        S_ERROR = 3,
        S_FATAL = 4,
        S_NUM_SEVERITIES
    };

    using LogListener = std::function<void(Logger::Severity, const std::string&)>;

    void addListener(const LogListener &listener);
    void clearListeners();

    class Logstream {
    private:
        Severity severity;
        std::stringstream ss;
    public:
        explicit Logstream(Severity s) : severity(s) {}
        ~Logstream();

        static Severity& minSeverity()
        {
            static Severity minSeverity = Severity::S_DEBUG;
            return minSeverity;
        }

        std::stringstream& get() { return ss; }
    };
}

#define Log(SEVERITY) if (static_cast<unsigned int>(Logger::Severity::SEVERITY) >= static_cast<unsigned int>(Logger::Logstream::minSeverity())) Logger::Logstream(Logger::Severity::SEVERITY).get()
#undef __stringify2
#undef __stringify
#define __stringify2(X) #X
#define __stringify(X) __stringify2(X)
#define LogLine(SEVERITY) Log(SEVERITY) << "(" __FILE__ "@" __stringify(__LINE__) ") "


#endif //CMC_CG_TEMPLATE_LOGGER_H
