/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#ifndef IMGUI_OPENGL_HPP
#define IMGUI_OPENGL_HPP

#include "glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "melts_interface.hpp"
#include <vector>
#include <memory>
#include <future>


//Custom class for creating ImGui GUI
class ImGuiOpenGL {
public:
    ImGuiOpenGL(GLFWwindow* window);
    virtual ~ImGuiOpenGL();

    void UpdateImGUI();
    void RenderGUI(ImDrawData* draw_data);
    void UpdateAndRender();
    void DestroyAssets();
    void ClearPlotData();
    void ClearLists();
private:

    GLuint LoadShaders();
    void LoadImGuiTexture();
    void SetupOpenGL();

    std::vector<std::string> melts_files;

    GLuint vao, vbo, ibo; //buffer handles
    GLuint texture_pointer; //texture handle
    GLuint program_id; //shader handle

    GLFWwindow* window;

    double time;

    MeltsInterface _MI;

    std::future<bool> m_Future;

    bool m_PlotDataLoaded = false;

    std::vector<float> m_PlotTemperatures;
    std::vector<float> m_PlotPressures;
    std::vector<float> m_PlotEnthalpy;
    std::vector<float> m_PlotEntropy;
    std::vector<float> m_PlotMeltFraction;
    std::vector<std::vector<float>> m_PlotLiquidComp;
    std::vector<std::vector<float>> m_PlotPhaseMasses;
    std::vector<bool> m_PlotPhaseExists;

    std::vector<std::vector<float>> m_PlotFracPhaseMasses;
    std::vector<bool> m_PlotFracPhaseExists;

    std::vector<double> m_AssimilationValues;
    std::vector<double> m_SetAssimilationValues;

    double m_T0 = 1200.0;
    double m_P0 = 1000.0;

    int m_Fo2Path = FO2_NONE;
    double m_Fo2Offset = 0.0;

    std::array<double, 20> m_Composition = { 48.68, 1.01, 17.64, 0.89, 0.0425, 7.59, 0.00, 9.10, 0.0, 0.0, 12.45, 2.65, 0.03, 0.08, 0.200, 0.00, 0.00, 0.00, 0.00, 0.00 };
    std::array<bool, 42> m_Suppressed{};

    ImVec2 m_WindowPos = ImVec2(0,0);
    ImVec2 m_WindowSize = ImVec2(0,0);

};
#endif /* IMUGUI_OPENGL_HPP */

