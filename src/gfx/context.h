#ifndef CMC_CG_TEMPLATE_CONTEXT_H
#define CMC_CG_TEMPLATE_CONTEXT_H

#include <memory>


namespace Gfx
{
    struct ContextData;

    class Context
    {
    private:
        std::unique_ptr<ContextData> data;

    public:
        Context();
        ~Context();

        void startFrame();
        void endFrame();
        void swap();

        void makeCurrent();
    };
}

#endif //CMC_CG_TEMPLATE_CONTEXT_H
