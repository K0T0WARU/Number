#pragma once

#include "Number/Layer.h"

namespace Number
{
    class NUMBER_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        float m_Time = 0.0f;
    };
}

