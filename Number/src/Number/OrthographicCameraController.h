#pragma once

#include "Number/Renderer/OrthographicCamera.h"
#include "Number/Core/Timestep.h"

#include "Number/Events/ApplicationEvent.h"
#include "Number/Events/MouseEvent.h"

namespace Number {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep& timestep);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        float m_ZoomSpeed = 0.25f;
        float m_ZoomMin = 0.25f;
        OrthographicCamera m_Camera;

        bool m_isRotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 1.0f;
        float m_CameraRotationSpeed = 10.0f;
    };

}