#pragma once

#include "Number/Layer.h"

namespace Number
{
    class NUMBER_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRenderer() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}

