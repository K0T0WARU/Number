#pragma once

#include "Event.h"

#include <sstream>

namespace Number {

    class NUMBER_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }


    };

}