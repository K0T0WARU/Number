#include "numpch.h"
#include "OrthographicCameraController.h"

#include "Number/Input.h"
#include "Number/KeyCodes.h"

namespace Number {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_isRotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep& timestep)
    {
        if (Input::IsKeyPresed(NUM_KEY_D))
            m_CameraPosition.x += m_CameraTranslationSpeed * timestep;
        else if (Input::IsKeyPresed(NUM_KEY_A))
            m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;

        if (Input::IsKeyPresed(NUM_KEY_W))
            m_CameraPosition.y += m_CameraTranslationSpeed * timestep;
        else if (Input::IsKeyPresed(NUM_KEY_S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;

        if (m_isRotation)
        {
            if (Number::Input::IsKeyPresed(NUM_KEY_E))
                m_CameraRotation += m_CameraRotationSpeed * timestep;
            else if (Number::Input::IsKeyPresed(NUM_KEY_Q))
                m_CameraRotation -= m_CameraRotationSpeed * timestep;
        }

        m_Camera.SetRotation(m_CameraRotation);
        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(NUM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(NUM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * m_ZoomSpeed;
        m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomMin);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return true;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return true;
    }

}