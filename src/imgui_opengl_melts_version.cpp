/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

#include <chrono>
#include <future>

#include "imgui_opengl.hpp"

#include "imgui/imgui.h"
#include "imgui/implot.h"

#ifndef NO_EXCEL_OUTPUT
#include "xlsx_writer.hpp"
#endif

#include "e_utility.hpp"
#include "file_utility.hpp"

const std::string ILLEGAL_CHARS = "\\/\":?*<>|";

static bool CheckString(std::string &string) {
    for (std::string::iterator it = string.begin(); it != string.end(); it++) {
        if (ILLEGAL_CHARS.find(*it) != std::string::npos) {
            (*it) = ' ';
            return false;
        }
    }
    return true;
}

static void HelpMarker(const char *help_text) {
    ImGui::TextColored(ImVec4(0.8, 0.1, 0.1, 1), "(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(help_text);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
/*
 Helper to make combos with const std::vector<std::string> & returned by the melts interface
 */
namespace ImGui {

bool Combo(const char *label, int *current_item, const std::vector<std::string> &items, int items_count, int height_in_items = -1) {
    return Combo(
        label, current_item, [](void *data, int idx, const char **out_text) {
            *out_text = ((const std::vector<std::string>*)data)->at(idx).c_str(); return true; }, (void *)&items, items_count, height_in_items);
}
} // namespace ImGui

const int VERTEX_POSITION = 1;
const int TEXTURE_COORDINATE = 2;
const int IMGUI_COLOR_RGBA = 3;

const GLchar *fragment_shader_glsl_130 =
    "#version 330 core\n"
    "in vec2 frag_uv;\n"
    "in vec4 frag_color;\n"
    "out vec4 color_out;\n"
    "uniform sampler2D tex;\n"
    "void main() {\n"
    "color_out = frag_color * texture(tex, frag_uv.st);\n"
    "}\n";

const GLchar *vertex_shader_glsl_130 =
    "#version 330 core\n"
    "in vec2 position;\n"
    "in vec2 texture_coordinate;\n"
    "in vec4 color;\n"
    "out vec2 frag_uv;\n"
    "out vec4 frag_color;\n"
    "uniform mat4 projection_matrix;\n"
    "void main() {\n"
    "frag_uv = texture_coordinate;\n"
    "frag_color = color;\n"
    "gl_Position = projection_matrix * vec4(position.xy, 0, 1);\n"
    "}\n";

GLuint ImGuiOpenGL::LoadShaders() {
    GLuint vao_name; // Mac workaround
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int info_log_length;

    glGenVertexArrays(1, &vao_name); // Mac workaround
    glBindVertexArray(vao_name);

    glShaderSource(vertex_shader_id, 1, &vertex_shader_glsl_130, NULL);
    glCompileShader(vertex_shader_id);

    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0) {
        std::vector<char> vertex_shader_error_msg(info_log_length + 1);
        glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, &vertex_shader_error_msg[0]);
        printf("%s\n", &vertex_shader_error_msg[0]);
    }

    glShaderSource(fragment_shader_id, 1, &fragment_shader_glsl_130, NULL);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0) {
        std::vector<char> fragment_shader_error_msg(info_log_length + 1);
        glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, &fragment_shader_error_msg[0]);
        printf("%s\n", &fragment_shader_error_msg[0]);
    }

    printf("Linking program.\n");
    program_id = glCreateProgram();

    glBindAttribLocation(program_id, 1, "position");
    glBindAttribLocation(program_id, 2, "texture_coordinate");
    glBindAttribLocation(program_id, 3, "color");

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    glLinkProgram(program_id);

    glValidateProgram(program_id);

    //check program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> error_message(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, NULL, &error_message[0]);
        printf("%s\n", &error_message[0]);
    }

    glBindVertexArray(0); // Mac workaround

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

void ImGuiOpenGL::LoadImGuiTexture() {
    ImGuiIO &io = ImGui::GetIO();
    int width, height;
    unsigned char *pixels = NULL;
    ImFontConfig config;
    config.OversampleH = 3;
    config.OversampleV = 1;
    //Icon ranges need to be set for symbols to work, see ImGui font readme
    static const ImWchar icon_ranges[] = {0x0020, 0x00B9, 0};

    io.Fonts->AddFontFromMemoryCompressedBase85TTF(MyFont::LiberationSans_Regular_compressed_data_base85, 16.f, &config, icon_ranges);
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    glGenTextures(1, &texture_pointer);
    io.Fonts->TexID = (ImTextureID)(intptr_t)texture_pointer;
    glBindTexture(GL_TEXTURE_2D, texture_pointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    //glUniform1i(glGetUniformLocation(program_id, "tex"), 0);
}

void ImGuiOpenGL::SetupOpenGL() {
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)IM_OFFSETOF(ImDrawVert, pos));
    glEnableVertexAttribArray(VERTEX_POSITION);

    glVertexAttribPointer(TEXTURE_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)IM_OFFSETOF(ImDrawVert, uv));
    glEnableVertexAttribArray(TEXTURE_COORDINATE);

    glVertexAttribPointer(IMGUI_COLOR_RGBA, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid *)IM_OFFSETOF(ImDrawVert, col));
    glEnableVertexAttribArray(IMGUI_COLOR_RGBA);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ImGuiOpenGL::ImGuiOpenGL(GLFWwindow *window) {
    this->window = window;

    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui::GetStyle().WindowRounding = 0.0f;
    ImGui::GetStyle().FrameRounding = 0.0f;

    LoadShaders();
    LoadImGuiTexture();
    SetupOpenGL();

    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = NULL;

    int w, h;
    int display_w, display_h;
    glfwGetWindowSize(window, &w, &h);
    glfwGetFramebufferSize(window, &display_w, &display_h);

    io.DisplaySize = ImVec2((float)w, (float)h);
    io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);
    io.DeltaTime = 1.0f / 60.0f;

    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    //Check cwd for melts input
    FileUtility f_util;
    melts_files = f_util.GetFilesWithName(".melts");

}

ImGuiOpenGL::~ImGuiOpenGL() {
}

void ImGuiOpenGL::DestroyAssets() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

    glDeleteTextures(1, &texture_pointer);

    ImGui::DestroyContext();
}

void ImGuiOpenGL::RenderGUI(ImDrawData *draw_data) {

    glEnable(GL_SCISSOR_TEST);

    glBindVertexArray(vao);

    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    ImVec2 clip_off = draw_data->DisplayPos;
    ImVec2 clip_scale = draw_data->FramebufferScale;

    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

    float L = draw_data->DisplayPos.x;
    float r = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

    const float ortho_projection_matrix[4][4] = {
        {2.0f / (r - L), 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f / (T - B), 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {(r + L) / (L - r), (T + B) / (B - T), 0.0f, 1.0f},
    };

    glUseProgram(program_id);

    GLuint loc = glGetUniformLocation(program_id, "projection_matrix");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &ortho_projection_matrix[0][0]);

    //TBC
    for (int i = 0; i < draw_data->CmdListsCount; i++) {
        const ImDrawList *cmd_list = draw_data->CmdLists[i];
        size_t index_buffer_offset = 0;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid *)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid *)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

        for (int j = 0; j < cmd_list->CmdBuffer.Size; j++) {
            const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[j];
            if (pcmd->UserCallback) {
                pcmd->UserCallback(cmd_list, pcmd);
            } else {

                ImVec4 clip_rect;
                clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

                if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f) {
                    glScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));
                    glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                    glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void *)index_buffer_offset);
                }
            }
            index_buffer_offset += pcmd->ElemCount * sizeof(ImDrawIdx);
        }
    }
    glDisable(GL_SCISSOR_TEST);
}

void ImGuiOpenGL::UpdateAndRender() {
    UpdateImGUI();
    ImGui::Render();
    RenderGUI(ImGui::GetDrawData());
}

void ImGuiOpenGL::ClearPlotData() {
    if (!m_PlotTemperatures.empty()) m_PlotTemperatures.clear();
    if (!m_PlotPressures.empty()) m_PlotPressures.clear();
    if (!m_PlotEnthalpy.empty()) m_PlotEnthalpy.clear();
    if (!m_PlotEntropy.empty()) m_PlotEntropy.clear();
    if (!m_PlotMeltFraction.empty()) m_PlotMeltFraction.clear();
    if (!m_PlotPhaseMasses.empty()) m_PlotPhaseMasses.clear();
    if (!m_PlotLiquidComp.empty()) m_PlotLiquidComp.clear();
    if (!m_PlotPhaseExists.empty()) m_PlotPhaseExists.clear();
    if (!m_PlotFracPhaseMasses.empty()) m_PlotFracPhaseMasses.clear();
    if (!m_PlotFracPhaseExists.empty()) m_PlotFracPhaseExists.clear();
}

void ImGuiOpenGL::ClearLists() {
    for (int i = 0; i < 42; ++i)
        m_Suppressed[i] = false;
}

void ImGuiOpenGL::UpdateImGUI() {

    ImGuiIO &io = ImGui::GetIO();
    double time_now = glfwGetTime();
    io.DeltaTime = time > 0.0 ? (float)(time_now - time) : (float)(1.0f / 60.0f);
    time = time_now;

    ImGui::NewFrame();

    //FORCE FULL FRAME WINDOW
    ImVec2 vec(0, 0);
    ImGui::SetNextWindowPos(vec);
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin("easyMelts 0.3.0 (beta)", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse /*ImGuiWindowFlags_None*/);

    static int current_melts_version = 0;
    static const char *version_string = "";

    static int fo2_path = 0;
    static int _mode = 0;
    static bool fsolids = false;
    static bool fliquids = false;
    static bool ffluids = false;
    static bool assimilate = false;

    static double fo2_offset = 0.0;
    static double inc_t = 0.0;
    static double inc_p = 0.0;
    static double inc_h = 0.0;
    static double inc_s = 0.0;
    static double inc_v = 0.0;

    static bool normalize_on_save = true;
    static bool state_loaded_from_file = false;
    static bool state_copied_from_step = false;

    /*MAIN MENU*/
    //BeginMenuBar creates fullscreen menu
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Init")) {
            //ImGui::MenuItem("(file_m)", NULL, false, false);
            if (!_MI.MeltsInitialized()) {
                if (ImGui::BeginMenu("Version")) {
                    for (size_t i = 0; i < _MI.GetMeltsVersions().size(); ++i) {
                        if (ImGui::MenuItem(_MI.GetMeltsVersions()[i].c_str())) {
                            _MI.InitializeMelts(i + 1); //no xMELTS
                            current_melts_version = i;
                            version_string = _MI.GetMeltsVersions()[current_melts_version].c_str();
                            m_AssimilationValues = std::vector<double>(npc + nc, 0.0);
                            m_SetAssimilationValues = std::vector<double>(npc + nc + 1, 0.0);
                            ClearLists();
                        }
                    }
                    ImGui::EndMenu();
                }
            } else {
                ImGui::MenuItem(version_string, NULL, false, false);
            }

            ImGui::EndMenu();
        }
        if (_MI.MeltsInitialized()) {

            if (ImGui::BeginMenu("Export/Load")) {
#ifndef NO_EXCEL_OUTPUT
                if (_MI.GetData().empty()) {
                    ImGui::MenuItem("Export XLSX", NULL, false, false);
                } else {
                    if (ImGui::MenuItem("Export XLSX")) {
                        XLSXWriter(_MI.GetData(), _MI.GetTitle());
                    }
                }
#endif
#ifdef NO_EXCEL_OUTPUT
                ImGui::MenuItem("Export XLSX (TBD)", NULL, false, false);
#endif
                if (!_MI.GetSilminState()) {
                    ImGui::MenuItem("Export .melts", NULL, false, false);
                } else {
                    if (ImGui::MenuItem("Export .melts"))
                        _MI.SaveMeltsInputData(m_SetAssimilationValues);
                }
                // IMPORT .melts file
                if (ImGui::MenuItem("Update folder")) {
                    FileUtility f_util;
                    melts_files = f_util.GetFilesWithName(".melts");
                }
                if (ImGui::BeginMenu("Load .melts")) {
                    //FileUtility f_util;
                    //auto dir_files = f_util.GetFilesWithName(".melts");
                    if (melts_files.empty())
                        ImGui::MenuItem("No files", NULL, false, false);
                    else {
                        for (size_t i = 0; i < melts_files.size(); ++i) {
                            const char *fname = melts_files[i].c_str();
                            if (ImGui::MenuItem(fname)) {
                                //Clear state
                                ClearPlotData();
                                ClearLists();

                                _MI.step_inc.H = 0.0;
                                _MI.step_inc.P = 0.0;
                                _MI.step_inc.S = 0.0;
                                _MI.step_inc.T = 0.0;
                                _MI.step_inc.V = 0.0;

                                //Get Assimilation values and attempt to reload SilminState from file.
                                m_SetAssimilationValues = _MI.LoadFromFile(melts_files[i].c_str());
                                SilminState *s = _MI.GetSilminState();
                                fo2_path = s->fo2Path;

                                inc_t = _MI.step_inc.T;
                                inc_p = _MI.step_inc.P;
                                inc_h = _MI.step_inc.H;
                                inc_s = _MI.step_inc.S;
                                inc_v = _MI.step_inc.V;

                                _mode = 0;
                                if (s->isenthalpic) _mode = 1;
                                if (s->isentropic) _mode = 2;
                                if (s->isochoric) _mode = 3;
                                fsolids = s->fractionateSol;
                                fliquids = s->fractionateLiq;
                                ffluids = s->fractionateFlu;
                                assimilate = s->assimilate;

                                //Suppressed phases, (TODO: this code needs refactoring badly)
                                int i, j;
                                for (i = 0, j = 0; i < npc; i++)
                                    if (solids[i].type == PHASE) {
                                        if (s->incSolids[j] == FALSE) {
                                            m_Suppressed[j] = true;
                                        }
                                        j++;
                                    }

                                int count = 0;

                                std::map<int, std::string> suppressed_phases;
                                for (const auto &a : _MI.GetPhases()) {
                                    if (m_Suppressed[count])
                                        suppressed_phases.insert(std::make_pair(a.first, a.second));
                                    count++;
                                }
                                _MI.SetSuppressedPhases(suppressed_phases);

                                state_loaded_from_file = true;
                            }
                        }
                    }
                    ImGui::EndMenu(); //import
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Samples")) {
                ImGui::MenuItem("Compositions", NULL, false, false);
                if (ImGui::MenuItem("MORB")) {
                    m_Composition = std::array<double, 20>{48.68, 1.01, 17.64, 0.89, 0.0425, 7.59, 0.00, 9.10, 0.0, 0.0, 12.45, 2.65, 0.03, 0.08, 0.200, 0.00, 0.00, 0.00, 0.00, 0.00};
                }
                else if (ImGui::MenuItem("Bishop Tuff")) {
                    /* Composition from MELTS for Excel since ~2020 */
                    m_Composition = std::array<double, 20>{74.39, 0.180, 13.55, 0.36, 0.000, 0.976, 0.00, 0.5, 0.0, 0.0, 1.43, 3.36, 5.09, 0.00, 10.0, 0.00, 0.00, 0.00, 0.00, 0.00};
                }

                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
    }
    ImGui::Spacing();
    /*END MAIN MENU*/

    ImGuiTabBarFlags tab_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("TabBar", tab_flags)) {

        if (ImGui::BeginTabItem("Input/Output")) {

            ImGui::BeginChild("Left", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.333f, 0));

            static char title_buf[32] = "Title";

            if (state_loaded_from_file) {
                for (size_t i = 0; i<32; ++i) title_buf[i] = 0;
                strncpy(title_buf, _MI.GetTitle().c_str(), _MI.GetTitle().length() > 31 ? 31 : _MI.GetTitle().length());
                state_loaded_from_file = false;
            }

            ImGui::Dummy(ImVec2(0, 5.f));
            ImGui::InputText("Run title", title_buf, IM_ARRAYSIZE(title_buf));
            std::string tit(title_buf);
            if (!CheckString(tit))
                ImGui::Text("Title cannot contain: %s", ILLEGAL_CHARS.c_str());
            else
                _MI.SetTitle(tit);

            if (!_MI.MeltsInitialized()) {
                ImGui::Dummy(ImVec2(0, 5.f));
                ImGui::TextColored(ImVec4(1.f, 0.5f, 0.1f, 1.f), "Melts must be initialized.");
            }

            if (_MI.MeltsInitialized()) {
                ImGui::Dummy(ImVec2(0, 5.f));
                if (ImGui::Button("Reset state")) {
                    strncpy(title_buf, "Title", strlen(title_buf));
                    fo2_path = 0;
                    fo2_offset = 0.0;
                    _mode = 0;
                    fsolids = false;
                    fliquids = false;
                    ffluids = false;
                    assimilate = false;
                    m_SetAssimilationValues = std::vector<double>(npc + nc + 1, 0.0);
                    ClearLists();
                    _MI.CreateSilminState();
                    ClearPlotData();
                }
            } else {
                ImGui::Dummy(ImVec2(0, 10.f));
            }
            ImGui::Dummy(ImVec2(0, 10.f));

            /*START COMPOSITION AND INITIAL TP*/
            if (_MI.MeltsInitialized()) {
                if (ImGui::TreeNode("Set initial T & P")) {
                    ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.25f);
                    static double T0 = 1200.0;
                    ImGui::InputDouble("Initial T (C): ", &T0, 0.0, 100.0, "%.1f");
                    static double P0 = 1000.0;
                    ImGui::InputDouble("Initial P (bar): ", &P0, 0.0, 100.0, "%.1f");

                    if (ImGui::Button("Save")) {
                        if (!_MI.GetData().empty()) {
                            fo2_path = 0, _mode = 0;
                            fsolids = false, fliquids = false, ffluids = false, assimilate = false;
                            m_SetAssimilationValues = std::vector<double>(npc + nc + 1, 0.0);
                            _MI.CreateSilminState();
                            ClearPlotData();
                            ClearLists();
                        }

                        _MI.SetInitialTP(T0, P0);
                        _MI.SetInitTP(T0, P0);
                    }
                    ImGui::SameLine();
                    HelpMarker("Saving initial TP resets state if modeling steps exist!");

                    if (ImGui::Button("Clear")) {
                        T0 = 0.0;
                        P0 = 0.0;
                    }

                    ImGui::PopItemWidth();
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Set initial composition")) {
                    // default composition set in imgui_opengl.hpp
                    ImGui::SameLine(); HelpMarker("Units are grams - normalize to 100 g to approximate wt%");
                    ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.25f);

                    ImGui::InputDouble("SiO2", &m_Composition[0], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("TiO2", &m_Composition[1], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("Al2O3", &m_Composition[2], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("Fe2O3", &m_Composition[3], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("Cr2O3", &m_Composition[4], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("FeO", &m_Composition[5], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("MnO", &m_Composition[6], 0.0, 100.0, "%.3f");
                    if (current_melts_version == MODE_pMELTS - 1) {
                        ImGui::SameLine(); HelpMarker("Warning: MnO not calibrated in pMELTS!");
                    }
                    ImGui::InputDouble("MgO", &m_Composition[7], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("NiO", &m_Composition[8], 0.0, 100.0, "%.3f");
                    if (current_melts_version == MODE_pMELTS - 1) {
                        ImGui::SameLine(); HelpMarker("Warning: NiO not calibrated in pMELTS!");
                    }
                    ImGui::InputDouble("CoO", &m_Composition[9], 0.0, 100.0, "%.3f");
                    if (current_melts_version == MODE_pMELTS - 1) {
                        ImGui::SameLine(); HelpMarker("Warning: CoO not calibrated in pMELTS!");
                    }
                    ImGui::InputDouble("CaO", &m_Composition[10], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("Na2O", &m_Composition[11], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("K2O", &m_Composition[12], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("P2O5", &m_Composition[13], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("H2O", &m_Composition[14], 0.0, 100.0, "%.3f");
                    ImGui::InputDouble("CO2", &m_Composition[15], 0.0, 100.0, "%.3f");
                    if (current_melts_version == MODE_pMELTS - 1) {
                        ImGui::SameLine(); HelpMarker("Warning: CO2 not calibrated in pMELTS!");
                    } else if (current_melts_version == MODE__MELTS - 1) {
                        ImGui::SameLine(); HelpMarker("Warning: CO2 not calibrated in MELTS_v1.0.x!");
                    }
                    ImGui::InputDouble("SO3", &m_Composition[16], 0.0, 100.0, "%.3f");
                    ImGui::SameLine(); HelpMarker("Warning: SO3 not calibrated in (p)MELTS!");
                    ImGui::InputDouble("Cl2O-1", &m_Composition[17], 0.0, 100.0, "%.3f");
                    ImGui::SameLine(); HelpMarker("Warning: Cl not calibrated in (p)MELTS!");
                    ImGui::InputDouble("F2O-1", &m_Composition[18], 0.0, 100.0, "%.3f");
                    ImGui::SameLine(); HelpMarker("Warning: F not calibrated in (p)MELTS!");

                    for (size_t i = 0; i < m_Composition.size(); ++i) {
                        if (m_Composition[i] < 0.0) m_Composition[i] = 0.0;
                    }

                    if (ImGui::Button("Save")) {
                        if (!_MI.GetData().empty()) {
                            //reset!
                            fo2_path = 0;
                            _mode = 0;
                            fsolids = false;
                            fliquids = false;
                            ffluids = false;
                            assimilate = false;
                            m_SetAssimilationValues = std::vector<double>(npc + nc + 1, 0.0);
                            _MI.CreateSilminState();
                            ClearPlotData();
                            ClearLists();
                        }

                        _MI.SetComposition(m_Composition);
                    }
                    ImGui::SameLine();
                    HelpMarker("Saving initial composition resets state if modeling steps exist!");

                    ImGui::SameLine();
                    ImGui::Checkbox("Normalize on save", &normalize_on_save);
                    ImGui::SameLine();
                    HelpMarker("Normalize initial system to 100 g (~ wt%) when saving\n");
                    _MI.SetNormalizeOnSave(normalize_on_save);

                    if (ImGui::Button("Clear")) {
                        for (size_t i = 0; i < m_Composition.size(); ++i) {
                            m_Composition[i] = 0.0;
                        }
                    }

                    ImGui::PopItemWidth();
                    ImGui::TreePop();
                }

                /* FO2 BUFFER*/
                ImGui::Dummy(ImVec2(0, 5.f));
                ImGui::Text("fO2 path: buffer and offset (log 10 units)");
                ImGui::SameLine();
                HelpMarker("Calibrated range ~ HM-15<->HM, NNO-10<->NNO+5, FMQ-9<->FMQ+6, COH-3<->COH+12, IW-5<->IW+10\nWarning: imposing fO2 paths outside the calibrated range is NOT recommended");
                ImGui::Combo("fO2 buffer", &fo2_path, _MI.GetFO2Paths(), (int)_MI.GetFO2Paths().size());
                if (_MI.SilminStateExists()) _MI.GetSilminState()->fo2Path = fo2_path;
                ImGui::InputDouble("fO2 offset", &fo2_offset, 0.5, 1.0, "%.1f");
                MyUtil::Limit<double>(-15., 15., &fo2_offset);
                if (_MI.SilminStateExists()) _MI.GetSilminState()->fo2Delta = (fo2_path != FO2_NONE) ? fo2_offset : 0.0;

                if (_MI.CompositionSet() && _MI.TPSet() && _MI.GetData().empty()) {
                    ImGui::Dummy(ImVec2(0, 5.f));
                    if (ImGui::Button("RedistFeOx")) {
                        _MI.RedistributeFeOx(fo2_path);
                    }
                    ImGui::SameLine();
                    HelpMarker("Redistribute Fe oxides according to initial T and P and selected fO2 buffer");
                    ImGui::SameLine();
                    ImGui::Checkbox("Normalize on save", &normalize_on_save);
                    ImGui::SameLine();
                    HelpMarker("Normalize initial system to 100 g (~ wt%) after redistribution\n");
                    _MI.SetNormalizeOnSave(normalize_on_save);

                    if (ImGui::Button("Liquidus&RedistFeOx")) {
                        _MI.Liquidus();
                    }
                    ImGui::SameLine();
                    HelpMarker("Attempt to change T to liquidus T and redistribute Fe oxides\naccording to PT-conditions and selected fO2 buffer");
                    ImGui::SameLine();
                    if (ImGui::Button("WetLiquidus&RedistFeOx")) {
                        _MI.WetLiquidus();
                    }
                    ImGui::SameLine();
                    HelpMarker("Attempt to change T to fluid-saturated liquidus T and redistribute\nFe oxides according to PT-conditions and selected fO2 buffer");

                    //                    if (!std::isnan(_MI.GetLiquidusT())) {
                    //                        ImGui::Text("Liquidus found at: %.2f C", _MI.GetLiquidusT());
                    //                    }
                }
                /*END COMPOSITION AND INITIAL TP*/

                /*CALCULATION MODE */
                ImGui::Dummy(ImVec2(0, 15.f));
                ImGui::Combo("Calc mode", &_mode, _MI.GetCalculationModes(), (int)_MI.GetCalculationModes().size());
                ImGui::SameLine();
                HelpMarker("First calculation is always Isothermal/Isobaric\nSet calculation parameters for subsequent steps");
                _MI.SetMode(_mode);

                //ImGui::Dummy(ImVec2(0, 5.f));
                /*RUN SETTINGS (i.e steps to calculate and increments between steps)*/
                if (ImGui::TreeNode("Set calculation parameters")) {

                    static int calc_steps = 1;

                    ImGui::InputInt("Calc steps", &calc_steps);
                    MyUtil::Limit<int>(1, 1000, &calc_steps);
                    _MI.SetCalcSteps(calc_steps);
                    ImGui::Text("Increment between steps");
                    ImGui::SameLine();
                    HelpMarker("Isothermal/Isobaric: TP, Isenthalpic: HP\nIsentropic: SP, Isochoric: VT\nNote: the increments are signed quantities");
                    if (_mode == 0 || _mode == 3) {
                        ImGui::InputDouble("T (C)", &inc_t, 1.0, 100.0, "%.2f");
                        MyUtil::Limit<double>(-2000., 2000., &inc_t);
                        _MI.step_inc.T = inc_t;
                        _MI.step_inc.H = 0;
                        _MI.step_inc.S = 0;
                    }
                    if (_mode >= 0 && _mode < 3) {
                        ImGui::InputDouble("P (bar)", &inc_p, 10., 100.0, "%.2f");
                        MyUtil::Limit<double>(-10000., 10000., &inc_p);
                        _MI.step_inc.P = inc_p;
                        _MI.step_inc.V = 0;
                    }
                    if (_mode == 1) {
                        ImGui::InputDouble("H (J)", &inc_h, 100.0, 1000.0, "%.2f");
                        MyUtil::Limit<double>(-2000000., 2000000, &inc_h);
                        _MI.step_inc.H = inc_h;
                        _MI.step_inc.T = 0;
                        _MI.step_inc.S = 0;
                        _MI.step_inc.V = 0;
                    }
                    if (_mode == 2) {
                        ImGui::InputDouble("S (J/K)", &inc_s, 1.0, 10.0, "%.2f");
                        MyUtil::Limit<double>(-500., 500., &inc_s);
                        _MI.step_inc.S = inc_s;
                        _MI.step_inc.T = 0;
                        _MI.step_inc.H = 0;
                        _MI.step_inc.V = 0;
                    }
                    if (_mode == 3) {
                        ImGui::InputDouble("V (cc)", &inc_v, 0.1, 1.0, "%.2f");
                        MyUtil::Limit<double>(-50., 50., &inc_v);
                        _MI.step_inc.V = inc_v;
                        _MI.step_inc.P = 0;
                        _MI.step_inc.H = 0;
                        _MI.step_inc.S = 0;
                    }

                    if (ImGui::Button("Reset##parameters")) {
                        inc_t = 0.0;
                        inc_p = 0.0;
                        inc_h = 0.0;
                        inc_s = 0.0;
                        inc_v = 0.0;
                        calc_steps = 1;
                        _MI.step_inc.T = inc_t;
                        _MI.step_inc.P = inc_p;
                        _MI.step_inc.H = inc_h;
                        _MI.step_inc.S = inc_s;
                        _MI.step_inc.V = inc_v;
                        _MI.SetCalcSteps(calc_steps);
                    }
                    ImGui::TreePop();
                }
                /*END RUN SETTINGS*/

                ImGui::Dummy(ImVec2(0, 15.f));
                /*FRACTIONATION*/
                ImGui::Text("Fractionate phases");
                ImGui::Checkbox("Solids", &fsolids);
                ImGui::SameLine();
                ImGui::Checkbox("Fluids", &ffluids);
                ImGui::SameLine();
                ImGui::Checkbox("Liquids", &fliquids);
                ImGui::SameLine();
                HelpMarker("Warning: Fractionating liquid may lead to unexpected behavior\nof the Melts engine and is NOT recommended");
                _MI.SetFractionate(fsolids, ffluids, fliquids);
                /*END FRACTIONATION*/

                /*ASSIMILATION*/
                ImGui::Text("Assimilate composition");
                ImGui::Checkbox("Assimilate", &assimilate);
                if (assimilate)
                    _MI.GetSilminState()->assimilate = 1;
                else
                    _MI.GetSilminState()->assimilate = 0;

                ImGui::SameLine();
                if (ImGui::Button("Set assimilants")) {
                    ImGui::OpenPopup("Set Assimilants");
                }

                ImGui::SameLine();
                HelpMarker("Composition to assimilate is added every calculated step.");

                static bool assimilation_popup = true;

                ImGui::SetNextWindowSize(ImVec2(600.f, 680.f));

                if (ImGui::BeginPopupModal("Set Assimilants", &assimilation_popup, ImGuiWindowFlags_NoDecoration)) {

                    static double liq_mass = 0.0;
                    static double ass_t = 1000.;
                    ImGui::Dummy(ImVec2(2.f, 5.f));
                    if (ImGui::Button("Clear ALL assimilant data")) {
                        m_AssimilationValues = std::vector<double>(npc + nc, 0.0);
                        m_SetAssimilationValues = std::vector<double>(npc + nc + 1, 0.0);
                        _MI.ClearAllAssimilants();
                    }
                    ImGui::Dummy(ImVec2(0, 5.f));
                    ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.30f);
                    ImGui::InputDouble("T of assimilants (C)", &ass_t, 1.0, 10.0, "%.2f");
                    MyUtil::Limit<double>(0.0, 5000., &ass_t);
                    ImGui::SameLine();
                    //                    if (ImGui::Button("Save T")) {
                    if (_MI.GetSilminState()) {
                        _MI.GetSilminState()->dspAssimT = ass_t;
                        _MI.GetSilminState()->assimT = ass_t;
                    }
                    //                    }
                    ImGui::SameLine();
                    HelpMarker("Temperature is not taken into account in isothermal mode.");
                    //                    ImGui::SameLine();
                    //                    ImGui::Text("T set to: %.2f C", _MI.GetSilminState()->dspAssimT);

                    ImGui::BeginChild("Solid_ass", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 0));

                    static const char *preview = solids[0].label;
                    static int current_index = 0;
                    ImGui::Text("Solid assimilants");
                    if (ImGui::BeginCombo("Assimilant", preview)) {
                        for (int i = 0; i < npc; ++i) {
                            if (solids[i].type == PHASE) {
                                const bool is_selected = (solids[i].label == preview);
                                if (ImGui::Selectable(solids[i].label, is_selected)) {
                                    preview = solids[i].label;
                                    current_index = i;
                                }
                            }
                        }
                        ImGui::EndCombo();
                    }

                    if (solids[current_index].na == 1) {
                        //ImGui::Text(solids[current_index].label);
        		        ImGui::Text("%s", solids[current_index].label);
                        ImGui::InputDouble("Mass/Step", &m_AssimilationValues[current_index], 1.0, 10.0, "%.2f");
                        if (m_AssimilationValues[current_index] < 0) m_AssimilationValues[current_index] = 0;
                    } else if (solids[current_index].na > 1) {
                        //ImGui::Text(solids[current_index].label);
		                ImGui::Text("%s", solids[current_index].label);
                        ImGui::InputDouble("Mass/Step", &m_AssimilationValues[current_index], 1.0, 10.0, "%.2f");
                        if (m_AssimilationValues[current_index] < 0) m_AssimilationValues[current_index] = 0;
                        //ImGui::Text("Set end member mol.% (0-100)");
                        ImGui::Text("Set end member mol%% (0-100)");
                        for (int j = 0; j < solids[current_index].na; ++j) {
                            ImGui::InputDouble(solids[current_index + 1 + j].label, &m_AssimilationValues[current_index + 1 + j], 1.0, 10.0, "%.2f");
                            if (m_AssimilationValues[current_index + 1 + j] < 0.0) m_AssimilationValues[current_index + 1 + j] = 0.0;
                            if (m_AssimilationValues[current_index + 1 + j] > 100.0) m_AssimilationValues[current_index + 1 + j] = 100.;
                        }
                    }
                    if (ImGui::Button("Add solid")) {
                        double total = 0.0;
                        std::vector<double> values;
                        for (int j = 0; j < solids[current_index].na; ++j) {
                            total += m_AssimilationValues[current_index + j + 1];
                        }
                        for (int j = 0; j < solids[current_index].na; ++j) {
                            m_AssimilationValues[current_index + j + 1] = m_AssimilationValues[current_index + j + 1] / total * 100.;
                            if (std::isnan(m_AssimilationValues[current_index + j + 1])) m_AssimilationValues[current_index + j + 1] = 0.0;
                        }
                        for (int j = 0; j < solids[current_index].na + 1; ++j) {
                            values.push_back(m_AssimilationValues[current_index + j]);
                        }
                        if (solids[current_index].na == 1)
                            if (values[0] != 0.0) {
                                _MI.AddAssimilant(current_index, m_AssimilationValues[current_index], values);
                                m_SetAssimilationValues[current_index] += m_AssimilationValues[current_index];
                            }

                        if (solids[current_index].na > 1) {
                            if (values[0] != 0.0 && total != 0.0) {
                                _MI.AddAssimilant(current_index, m_AssimilationValues[current_index], values);

                                for (int i = 0; i < solids[current_index].na; ++i) {
                                    m_SetAssimilationValues[current_index + 1 + i] =
                                        (m_AssimilationValues[current_index] * m_AssimilationValues[current_index + i + 1] +
                                         m_SetAssimilationValues[current_index] * m_SetAssimilationValues[current_index + 1 + i]) /
                                        (m_AssimilationValues[current_index] + m_SetAssimilationValues[current_index]);
                                }
                                m_SetAssimilationValues[current_index] += m_AssimilationValues[current_index];
                            }
                        }
                    }
                    ImGui::SameLine();
                    HelpMarker("Adds Mass/Step of phase to assimilate (normalizes its end-members if applicable).");

                    ImGui::Dummy(ImVec2(0.f, 45.0f));
                    //Calculate thermodynamic data of assimilants and close
                    if (ImGui::Button("Save and Close")) {
                        _MI.InitAssimilantTData();
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    HelpMarker("Initializes the thermodynamic properties of assimilants you have 'Added' (solids) and 'Set' (liquid).");

                    ImGui::EndChild();

                    ImGui::SameLine();

                    ImGui::BeginChild("Liquid_ass", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 0));
                    ImGui::Text("Liquid assimilant (melt)");
                    ImGui::SameLine();
                    HelpMarker("Note that Melts liquid species tend to include SiO2.\nLeaving SiO2 empty while including other oxides\nwill usually result in a crash to desktop.\nGiving a realistic liquid composition is advisable.\n\nThis problem does not include Al2O3, TiO2, Fe2O3,\nor the fluid components.");
                    ImGui::InputDouble("Mass/Step", &liq_mass, 1.0, 10.0, "%.2f");
                    if (liq_mass < 0.0) liq_mass = 0.0;
                    ImGui::LabelText("Oxide", "wt%%");
                    {

                        ImGui::InputDouble("SiO2", &m_AssimilationValues[npc], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("TiO2", &m_AssimilationValues[npc + 1], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("Al2O3", &m_AssimilationValues[npc + 2], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("Fe2O3", &m_AssimilationValues[npc + 3], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("Cr2O3", &m_AssimilationValues[npc + 4], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("FeO", &m_AssimilationValues[npc + 5], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("MnO", &m_AssimilationValues[npc + 6], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("MgO", &m_AssimilationValues[npc + 7], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("NiO", &m_AssimilationValues[npc + 8], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("CoO", &m_AssimilationValues[npc + 9], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("CaO", &m_AssimilationValues[npc + 10], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("Na2O", &m_AssimilationValues[npc + 11], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("K2O", &m_AssimilationValues[npc + 12], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("P2O5", &m_AssimilationValues[npc + 13], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("H2O", &m_AssimilationValues[npc + 14], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("CO2", &m_AssimilationValues[npc + 15], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("SO3", &m_AssimilationValues[npc + 16], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("Cl2O-1", &m_AssimilationValues[npc + 17], 0.0, 100.0, "%.3f");
                        ImGui::InputDouble("F2O-1", &m_AssimilationValues[npc + 18], 0.0, 100.0, "%.3f");

                        if (ImGui::Button("Set liquid")) {
                            //Selected assimilation values are normalized
                            double total = 0.0;
                            for (int i = 0; i < nc; ++i) {
                                if (m_AssimilationValues[npc + i] < 0.0f) m_AssimilationValues[npc + i] = 0.0f;
                                total += m_AssimilationValues[npc + i];
                            }
                            for (int i = 0; i < nc; ++i) {
                                m_AssimilationValues[npc + i] = m_AssimilationValues[npc + i] / total * 100.;
                            }
                            std::vector<double> values;
                            for (int i = 0; i < nc; ++i)
                                values.push_back(m_AssimilationValues[npc + i]);
                            _MI.AddAssimilant(npc, liq_mass, values);

                            //Displayed saved assimilation values
                            for (int i = 0; i < nc; ++i) {
                                m_SetAssimilationValues[npc + i] = m_AssimilationValues[npc + i];
                            }
                            m_SetAssimilationValues[npc + nc] = liq_mass;
                        }
                         ImGui::SameLine();
                        HelpMarker("Normalizes composition and sets Mass/Step of liquid to assimilate.");
                    }

                    ImGui::EndChild();
                    ImGui::EndPopup();
                }
                /*END ASSIMILATION*/
                ImGui::Dummy(ImVec2(0, 15.f));

                /*Suppress phases*/
                if (ImGui::TreeNode("Suppress phases")) {

                    ImGui::Columns(3, NULL, false);
                    int count = 0;
                    for (const auto &a : _MI.GetPhases()) {
                        ImGui::Selectable(a.second.c_str(), &m_Suppressed[count]);
                        count++;
                        ImGui::NextColumn();
                    }
                    ImGui::Columns(1);
                    count = 0;
                    if (ImGui::Button("Suppress")) {
                        std::map<int, std::string> suppressed_phases;
                        for (const auto &a : _MI.GetPhases()) {
                            if (m_Suppressed[count])
                                suppressed_phases.insert(std::make_pair(a.first, a.second));
                            count++;
                        }
                        _MI.SetSuppressedPhases(suppressed_phases);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Reset##suppressed")) {
                        for (int i = 0; i < 42; ++i)
                            m_Suppressed[i] = false;
                        _MI.ClearSuppressedPhases();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Select all##suppressed")) {
                        for (int i = 0; i < 42; ++i)
                            m_Suppressed[i] = true;
                    }
                    ImGui::SameLine();
                    HelpMarker("Select phases not present in the crystallizing assemblage");
                    ImGui::TreePop();
                }
                /*END SUPPRESS PHASES*/

                ImGui::Dummy(ImVec2(0, 40.f));

                /*EQUILIBRATION*/
                static bool launch_equilibration_thread = false;

                if (_MI.SilminFailed()) {
                    ImGui::TextColored(ImVec4(1.f, 0.5f, 0.1f, 1.f), "Equilibration failed! See log.\n\n-Export results from 'Export' menu\n-Start over by pressing 'Reset state'");
                } else {
                    if (_MI.ReadyToEquilibrate()) {
                        if (ImGui::Button("Equilibrate")) {
                            //Set assimilation OFF if assimilation is set ON but no assimilants are selected (avoids Melts crash)
                            if (assimilate && (_MI.GetSilminState()->dspAssimMass == 0.0 || std::isnan(_MI.GetSilminState()->dspAssimMass))) assimilate = false;
                            launch_equilibration_thread = true;
                            ImGui::OpenPopup("Equilibration");

                            //_MI.Equilibrate();
                            //m_PlotDataLoaded = true;
                        }
                    } else
                        ImGui::TextColored(ImVec4(1.f, 0.5f, 0.1f, 1.f), "Set Composition and Parameters");
                }

                static bool close_eq_popup = true;

                ImGui::SetNextWindowBgAlpha(0.0f);

                if (ImGui::BeginPopupModal("Equilibration", &close_eq_popup, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize)) {
                    //Launches silmin() calculation in a separate thread. Program is not usable during the run because of thread-safety issues.
                    if (launch_equilibration_thread) {
                        launch_equilibration_thread = false;
                        m_Future = std::async(std::launch::async, &MeltsInterface::Equilibrate, &_MI);
                    }
                    //Checks the status of the thread
                    std::chrono::milliseconds zero_msec(0);
                    auto status = m_Future.wait_for(zero_msec);

                    if (status == std::future_status::ready) {
                        m_PlotDataLoaded = true;
                        ImGui::CloseCurrentPopup();
                    }

                    if (status != std::future_status::ready) {
                        ImGui::Text("Calculating... %.1f %%", 100.f - ((float)_MI.GetStepsRemaining() / _MI.GetStepsToCalculate() * 100.f));
                        ImGui::Dummy(ImVec2(1.0f, 5.f));
                        //End silmin() calculation on next silmin() function return.
                        if (ImGui::Button("Stop equilibration")) {
                            _MI.StopEquilibration();
                            if (!_MI.GetData().empty())
                                m_PlotDataLoaded = true;
                            ImGui::CloseCurrentPopup();
                        }
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::EndChild();

            ImGui::SameLine();
            //Shows state of the system
            ImGui::BeginChild("Center", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.222f, 0));
            ImGui::Text("Set options");
            ImGui::Separator();
            ImGui::Text("Title: %s", _MI.GetTitle().c_str());
            ImGui::Text("Melts version: %s", version_string);
            ImGui::Separator();

            if (_MI.SilminStateExists()) {
                ImGui::Text("System state");
                ImGui::Separator();
                ImGui::Text("Initial T %.1f C, P %.1f bar", _MI.GetInitTP().first, _MI.GetInitTP().second);
                if (std::isnan(_MI.GetLiquidusT()))
                    ImGui::Text("Initial liquidus T (C):");
                else
                    ImGui::Text("Initial liquidus T (C): %.1f", _MI.GetLiquidusT());
                ImGui::Text("Current T (C): %.1f", std::max(_MI.GetSilminState()->T - 273.15, 0.0));
                ImGui::Text("Current P (bar): %.1f", _MI.GetSilminState()->P);

                ImGui::Separator();
                ImGui::Text("Calculation parameters");
                ImGui::Text("Steps to calculate: %i", _MI.GetStepsToCalculate());
                ImGui::Text("Increment T (C): %.1f", _MI.step_inc.T);
                ImGui::Text("Increment P (bar): %.1f", _MI.step_inc.P);
                ImGui::Text("Increment H (J): %.1f", _MI.step_inc.H);
                ImGui::Text("Increment S (J/K): %.1f", _MI.step_inc.S);
                ImGui::Text("Increment V (cc): %.1f", _MI.step_inc.V);
            }
            ImGui::Separator();
            ImGui::Text("Constraints");
            ImGui::Text("fO2 buffer: %s", _MI.GetFO2Paths().at(fo2_path).c_str());
            ImGui::Text("fO2 offset: %.1f", fo2_offset);

            ImGui::Text("Mode:");
            if (_MI.SilminStateExists()) {
                ImGui::SameLine();
                //ImGui::Text(_MI.GetCalculationModes()[_mode].c_str());
                ImGui::Text("%s", _MI.GetCalculationModes()[_mode].c_str());
            }

            ImGui::Text("Fractionate:");
            if (_MI.SilminStateExists()) {
                if (_MI.GetSilminState()->fractionateSol) {
                    ImGui::SameLine();
                    ImGui::Text("Solids  ");
                }
                if (_MI.GetSilminState()->fractionateLiq) {
                    ImGui::SameLine();
                    ImGui::Text("Liquids  ");
                }
                if (_MI.GetSilminState()->fractionateFlu) {
                    ImGui::SameLine();
                    ImGui::Text("Fluids");
                }
            }
            ImGui::Text("Assimilation active: %s", assimilate ? "Yes" : "No");
            if (_MI.GetSilminState() && !std::isnan(_MI.GetSilminState()->dspAssimMass)) {
                ImGui::Text("Mass of assimilants: %.2f g", _MI.GetSilminState()->dspAssimMass);
                if (ImGui::TreeNode("Composition to assimilate")) {
                    for (int i = 0; i < npc; ++i) {
                        if (i < npc) {
                            if (m_SetAssimilationValues[i] > 0 && solids[i].type == PHASE) {
                                if (solids[i].na == 1) {
                                    ImGui::Text("%s: %.2f g", solids[i].label, m_SetAssimilationValues[i]);
                                } else {
                                    ImGui::Text("%s: %.2f g", solids[i].label, m_SetAssimilationValues[i]);
                                    if (ImGui::TreeNode("Endmembers")) {
                                        for (int j = 0; j < solids[i].na; ++j) {
                                            ImGui::Text("-%s: %.2f mol%%", solids[i + 1 + j].label, m_SetAssimilationValues[i + 1 + j]);
                                        }
                                        ImGui::TreePop();
                                    }
                                }
                            }
                        }
                    }
                    if (m_SetAssimilationValues[nc + npc] != 0.0) {
                        ImGui::Text("%s: %.2f g", "Liquid", m_SetAssimilationValues[nc + npc]);
                        if (ImGui::TreeNode("Composition of liquid")) {
                            for (int i = npc; i < npc + nc; ++i)
                                ImGui::Text("%s: %.3f wt%%", bulkSystem[i - npc].label, m_SetAssimilationValues[i]);
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
            }

            std::string suppressed_phases = "";
            for (const auto &a : _MI.GetSuppressedPhases()) {
                suppressed_phases += a.second + "; ";
            }
            if (suppressed_phases.size() > 1) suppressed_phases.erase(suppressed_phases.size() - 2, 2);

            ImGui::TextWrapped("Suppressed phases: %s", suppressed_phases.c_str());
            ImGui::Separator();

            ImGui::Text("Bulk composition set: %s", _MI.CompositionSet() ? "Yes" : "No");


                        //if (_MI.SilminStateExists()) {

                          //  ImGui::Text("Mass of system: %.2f g", _MI.GetSilminState()->mass);



            if (ImGui::TreeNode("Initial bulk composition")) {
                ImGui::Separator();
                /*NOTE: theres 20 in total!*/
                for (int i = 0; i < 19; ++i) {
                    ImGui::Text("%-8s%.3f", _MI.GetOxideNames()[i].c_str(), _MI.GetComposition()[i]);
                }
                ImGui::TreePop();
            }

            ImGui::EndChild();

            ImGui::SameLine();

            //Shows system state at each calculated step
            ImGui::BeginChild("Right", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.444f, 0));

            if (!_MI.GetData().empty()) {

                static int jump_to_step = 0;
                int max_index = _MI.GetData().size() - 1;

                //Slider for selecting data step
                ImGui::SliderInt("Steps", _MI.GetStep(), 0, max_index);

                //Input step to go to, useful if there are >100 steps
                if (max_index > 0) {
                    ImGui::PushItemWidth(90.f);
                    ImGui::InputInt("", &jump_to_step);
                    ImGui::PopItemWidth();
                    if (jump_to_step < 0) jump_to_step = 0;
                    if (jump_to_step > max_index) jump_to_step = max_index;
                    ImGui::SameLine();
                    if (ImGui::Button("Go to step")) *_MI.GetStep() = jump_to_step;
                    ImGui::SameLine();
                    ImGui::Text("  ");
                    ImGui::SameLine();
                    if (ImGui::Button("Go to last step")) *_MI.GetStep() = max_index;
                }

                int step = *_MI.GetStep();

                ImGui::Text("State of the system at step %i\n(Fractionated phases not included in total)", step);
                ImGui::Separator();

                const SilminData &sd = _MI.GetData(step);

                ImGui::Text("Temperature: %.2f C", sd.T);
                ImGui::Text("Pressure: %.2f bar", sd.P);
                ImGui::Text("log 10 fO2: %.3f ", sd.fO2);
                ImGui::Text("G = %.2f kJ, H = %.02f kJ, S = %.2f J/K", sd.sys_prop_nofrac.gibbs_energy / 1000., sd.sys_prop_nofrac.enthalpy / 1000., sd.sys_prop_nofrac.entropy);
                ImGui::Text("m = %.2f g, V = %.2f cc, r = %.2f g/cc,", sd.sys_prop_nofrac.mass, sd.sys_prop_nofrac.volume, sd.sys_prop_nofrac.density);
                ImGui::Text("n = %.2f log(10) poise, Cp = %.2f J", sd.sys_prop_nofrac.viscosity, sd.sys_prop_nofrac.spec_heat_cap);
                if (ImGui::TreeNode("Bulk composition")) {
                    int oxides = 0;
                    for (const std::string &ss : _MI.GetOxideNames()) {
                        ImGui::Text("%-8s%.2f", ss.c_str(), sd.bulk_comp_n.at(oxides));
                        oxides++;
                    }
                    ImGui::TreePop();
                }

                ImGui::Separator();

                for (unsigned int i = 0; i < sd.liq_properties.size(); ++i) {
                    const auto &prop = sd.liq_properties.at(i);
                    ImGui::Text("m liquid %i: %.2f g", i + 1, prop.mass);
                    if (ImGui::TreeNode("Liquid")) {
                        ImGui::Text("Liquid %i:", i + 1);
                        ImGui::Text("G = %.2f kJ, H = %.02f kJ, S = %.2f J/K", prop.gibbs_energy / 1000., prop.enthalpy / 1000., prop.entropy);
                        ImGui::Text("m = %.2f g, V = %.2f cc, r = %.2f g/cc", prop.mass, prop.volume, prop.density);
                        ImGui::Text("n = %.2f log(10) poise, Cp = %.2f J", prop.viscosity, prop.spec_heat_cap);
                        int oxides = 0;
                        for (const std::string &ss : _MI.GetOxideNames()) {
                            ImGui::Text("%-8s%.2f wt%%", ss.c_str(), sd.liquid_composition.at(i).at(oxides));
                            oxides++;
                        }
                        ImGui::TreePop();
                    }
                }

                if (!std::isnan(sd.sol_tot_properties.mass) && sd.sol_tot_properties.mass > 0.0)
                    ImGui::Text("m solid & fluid: %.2f g", sd.sol_tot_properties.mass);
                if (ImGui::TreeNode("Solid and fluid")) {
                    for (size_t i = 0; i < sd.sol_properties.size(); ++i) {
                        const auto &prop = sd.sol_properties[i];
                        ImGui::Text("%s", prop.label.c_str());
                        ImGui::Text("Formula:  %s", prop.formula.c_str());
                        ImGui::Text("G = %.2f kJ, H = %.02f kJ, S = %.2f J/K", prop.gibbs_energy / 1000., prop.enthalpy / 1000., prop.entropy);
                        ImGui::Text("m = %.2f g, V = %.2f cc, r = %.2f g/cc", prop.mass, prop.volume, prop.density);
                        ImGui::Text("Cp = %.2f J", prop.spec_heat_cap);
                        if (!prop.end_members.empty()) {
                            std::string id("Endmembers##Eq" + std::to_string(i));
                            if (ImGui::TreeNode(id.c_str())) {
                                for (size_t i = 0; i < prop.end_members.size(); ++i) {
                                    ImGui::Text("%s : %.2f %%", prop.end_members[i].first.c_str(), prop.end_members[i].second);
                                }
                                ImGui::TreePop();
                            }
                        }
                        ImGui::Separator();
                    }
                    ImGui::TreePop();
                }

                if (!std::isnan(sd.frac_mass) && sd.frac_mass > 0.0) {
                    ImGui::Text("m fractionated solids & fluids: %.2f g", sd.frac_mass);
                    if (ImGui::TreeNode("Fractionated solids and fluids")) {
                        for (size_t i = 0; i < sd.frac_properties.size(); ++i) {

                            const auto &prop = sd.frac_properties[i];
                            ImGui::Text("%s", prop.label.c_str());
                            ImGui::Text("Formula:  %s", prop.formula.c_str());
                            ImGui::Text("G = %.2f kJ, H = %.02f kJ, S = %.2f J/K", prop.gibbs_energy / 1000., prop.enthalpy / 1000., prop.entropy);
                            ImGui::Text("m = %.2f g, V = %.2f cc, r = %.2f g/cc", prop.mass, prop.volume, prop.density);
                            ImGui::Text("Cp = %.2f J", prop.spec_heat_cap);
                            if (!prop.end_members.empty()) {
                                std::string id("Endmembers##Fr" + std::to_string(i));
                                if (ImGui::TreeNode(id.c_str())) {
                                    for (size_t i = 0; i < prop.end_members.size(); ++i) {
                                        ImGui::Text("%s : %.2f %%", prop.end_members[i].first.c_str(), prop.end_members[i].second);
                                    }
                                    ImGui::TreePop();
                                }
                            }
                            ImGui::Separator();
                        }

                        ImGui::TreePop();
                    }
                    if (!std::isnan(sd.frac_liq_properties.mass)) {
                        if (ImGui::TreeNode("Fractionated liquid")) {
                            ImGui::Text("%s", sd.frac_liq_properties.label.c_str());
                            ImGui::Text("Formula:  %s", sd.frac_liq_properties.formula.c_str());
                            ImGui::Text("G = %.2f kJ, H = %.02f kJ, S = %.2f J/K", sd.frac_liq_properties.gibbs_energy / 1000., sd.frac_liq_properties.enthalpy / 1000., sd.frac_liq_properties.entropy);
                            ImGui::Text("m = %.2f g, V = %.2f cc, r = %.2f g/cc", sd.frac_liq_properties.mass, sd.frac_liq_properties.volume, sd.frac_liq_properties.density);
                            ImGui::Text("Cp = %.2f J", sd.frac_liq_properties.spec_heat_cap);

                            ImGui::TreePop();
                        }
                    }
                }
            }
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Plot")) {

            if (!_MI.GetData().size()) {
                ImGui::EndTabItem(); //Plot data premature ending
            } else {
                /*
                 CONTROLS
                 */
                ImGui::BeginChild("Upper", ImVec2(ImGui::GetWindowContentRegionWidth() / 2.f, 60.f));
                ImGui::Dummy(ImVec2(10.f, 3.f));
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "(?)");
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("Axes do not automatically update after reloading data. Double-click on plot to fit the new data.");
                ImGui::SameLine();
                ImGui::TextWrapped("INSTRUCTIONS: Double-click on plot to fit data. Pan and zoom with mouse. Click legend entries to turn series on/off.");

                ImGui::EndChild(); //Upper

                ImGui::SameLine();
                ImGui::BeginChild("UpperRight", ImVec2(ImGui::GetWindowContentRegionWidth() / 2.f, 60.f));
                static int second_plot = 0;
                ImGui::Dummy(ImVec2(15.f, 23.f));
                ImGui::SameLine();
                ImGui::PushItemWidth(150.f);
                ImGui::Combo("Right plot", &second_plot, "Phases in magma\0Fractionated phases\0\0");

                static int x_axis_v = 0;
                ImGui::Dummy(ImVec2(15.f, 23.f));
                ImGui::SameLine();
                ImGui::Combo("X-axis", &x_axis_v, "Temperature\0Pressure\0Enthalpy\0Entropy\0Melt fraction\0\0");
                ImGui::PopItemWidth();
                ImGui::EndChild();

                ImGui::BeginChild("Leftcontrols", ImVec2(75.f, 0));

                static std::unordered_map<int, bool> show_element{
                    {0, true},
                    {1, true},
                    {2, true},
                    {3, true},
                    {4, true},
                    {5, true},
                    {6, true},
                    {7, true},
                    {8, false},
                    {9, false},
                    {10, true},
                    {11, true},
                    {12, true},
                    {13, true},
                    {14, true},
                    {15, true},
                    {16, false},
                    {17, false},
                    {18, false}};

                if (ImGui::Button("All", ImVec2(60, 0))) {
                    for (int i = 0; i < 19; ++i) {
                        show_element[i] = true;
                    }
                }
                if (ImGui::Button("Major", ImVec2(60, 0))) {
                    for (int i = 0; i < 16; ++i) {
                        if (i == 8 || i == 9) {
                            show_element[i] = false;
                            continue;
                        }
                        show_element[i] = true;
                    }
                    for (int i = 16; i < 19; ++i) {
                        show_element[i] = false;
                    }
                }
                if (ImGui::Button("Clear", ImVec2(60, 0))) {
                    for (int i = 0; i < 19; ++i) {
                        show_element[i] = false;
                    }
                }

                for (int i = 0; i < 19; ++i) {
                    if (ImGui::Selectable(_MI.GetOxideNames()[i].c_str(), show_element[i] != false, 0, ImVec2(60, 0))) {
                        show_element[i] = !show_element[i];
                    }
                }

                ImGui::EndChild();

                ImGui::SameLine();

                /*
                 DATA
                 */

                const int plot_items = _MI.GetData().size();

                if (m_PlotDataLoaded) {
                    m_PlotDataLoaded = false;

                    int prev_size = m_PlotTemperatures.empty() ? 0 : m_PlotTemperatures.size();
                    int added_items = plot_items - prev_size;

                    if (prev_size == 0) {
                        for (int i = 0; i < 19; ++i)
                            m_PlotLiquidComp.push_back(std::vector<float>());

                        for (size_t i = 0; i < _MI.GetPhasesVec().size(); ++i) {
                            m_PlotPhaseMasses.push_back(std::vector<float>(plot_items, 0.0));
                            m_PlotPhaseExists.push_back(false);
                            m_PlotFracPhaseMasses.push_back(std::vector<float>(plot_items, 0.0));
                            m_PlotFracPhaseExists.push_back(false);
                        }
                    } else {
                        for (size_t i = 0; i < _MI.GetPhasesVec().size(); ++i) {
                            for (int j = 0; j < added_items; ++j)
                                m_PlotPhaseMasses[i].push_back(0.f);
                            m_PlotFracPhaseMasses[i].push_back(0.f);
                        }
                    }

                    int indexx = 0;
                    std::unordered_map<int, int> phase_indices; //first melts, second index in plot data
                    for (int i = 0; i < npc; ++i)
                        if (solids[i].type == PHASE) phase_indices.emplace(i, indexx++);

                    for (size_t i = prev_size; i < _MI.GetData().size(); ++i) {
                        m_PlotTemperatures.push_back((float)_MI.GetData()[i].T);
                        m_PlotPressures.push_back((float)_MI.GetData()[i].P);
                        m_PlotEnthalpy.push_back((float)_MI.GetData()[i].sys_prop_nofrac.enthalpy / 1000.f);
                        m_PlotEntropy.push_back((float)_MI.GetData()[i].sys_prop_nofrac.entropy);
                        if (!_MI.GetData()[i].liq_properties.empty()) {
			    m_PlotMeltFraction.push_back((float)_MI.GetData()[i].liq_properties.at(0).mass / _MI.GetData()[i].sys_properties.mass);
			}
			else {
			  m_PlotMeltFraction.push_back(0.0f);
			}
			for (int j = 0; j < 19; ++j) {
                            if (!_MI.GetData()[i].liquid_composition.empty())
                                m_PlotLiquidComp.at(j).push_back((float)_MI.GetData()[i].liquid_composition.at(0)[j]);
                            else {
                                m_PlotLiquidComp.at(j).push_back(0.0f);
                            }
                        }
                        for (const auto &a : _MI.GetData()[i].sol_properties) {
                            m_PlotPhaseMasses.at(phase_indices.at(a.melts_phase_index))[i] += (float)a.mass;
                            m_PlotPhaseExists.at(phase_indices.at(a.melts_phase_index)) = true;
                        }
                        for (const auto &f : _MI.GetData()[i].frac_properties) {
                            m_PlotFracPhaseMasses.at(phase_indices.at(f.melts_phase_index))[i] += (float)f.mass;
                            m_PlotFracPhaseExists.at(phase_indices.at(f.melts_phase_index)) = true;
                        }
                    }
                }

                /*
                 DIAGRAMS
                 */
                ImGui::BeginChild("Halfscreen", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f - 37.5f, 0));

                int axis_flags = ImAxisFlags_Default | ImAxisFlags_Invert;
                int axis_flags_y = ImAxisFlags_Default; // | ImAxisFlags_LockMin;
                float x_axis_low = m_PlotTemperatures.at(m_PlotTemperatures.size() - 1);
                float x_axis_high = m_PlotTemperatures.at(0);

                int plot_flags = ImPlotFlags_Default;

                ImGui::PushPlotColor(ImPlotCol_PlotBg, ImVec4(0.1f, 0.1f, 0.1f, 0));

                float *x_data_address = 0;
                const char *x_axis_label = "";
                if (x_axis_v == 0) {
                    x_data_address = &m_PlotTemperatures[0];
                    x_axis_label = u8"T \u00B0C (system)";
                }
                if (x_axis_v == 1) {
                    x_data_address = &m_PlotPressures[0];
                    x_axis_label = "P bar (system)";
                }
                if (x_axis_v == 2) {
                    x_data_address = &m_PlotEnthalpy[0];
                    x_axis_label = "H kJ (magma)";
                }
                if (x_axis_v == 3) {
                    x_data_address = &m_PlotEntropy[0];
                    x_axis_label = "S J/K (magma)";
                }
                if (x_axis_v == 4) {
                    x_data_address = &m_PlotMeltFraction[0];
                    x_axis_label = "X (melt)";
                }

                ImGui::SetNextPlotRange(x_axis_low, x_axis_high, 0.f, 100.f);
                if (ImGui::BeginPlot("Melt composition", x_axis_label, "Wt.%", {ImGui::GetWindowWidth() - 5.f, ImGui::GetWindowHeight()}, plot_flags, axis_flags, axis_flags_y)) {
                    ImGui::PushPlotColor(ImPlotCol_MarkerFill, ImVec4(0, 0, 0, 0));
                    ImGui::PushPlotStyleVar(ImPlotStyleVar_Marker, ImMarker_Circle);
                    ImGui::PushPlotStyleVar(ImPlotStyleVar_MarkerSize, 3.f);
                    for (int i = 0; i < 19; ++i) {
                        if (show_element[i])
                            ImGui::Plot(_MI.GetOxideNames()[i].c_str(), x_data_address, &m_PlotLiquidComp.at(i)[0], plot_items); //label, data_x, data_y, amount
                    }
                    ImGui::PopPlotStyleVar(2);
                    ImGui::PopPlotColor();
                    ImGui::EndPlot();
                }

                ImGui::EndChild(); //First child

                ImGui::SameLine();

                ImGui::BeginChild("Halfscreen2", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f - 37.5f, 0));

                ImGui::SetNextPlotRange(x_axis_low, x_axis_high, 0.f, 100.f);
                if (!second_plot) {
                    if (ImGui::BeginPlot("Phases in magma", x_axis_label, "Mass (in magma)", {ImGui::GetWindowWidth() - 5.f, ImGui::GetWindowHeight()}, plot_flags, axis_flags, axis_flags_y)) {
                        ImGui::PushPlotColor(ImPlotCol_MarkerFill, ImVec4(0, 0, 0, 0));
                        ImGui::PushPlotStyleVar(ImPlotStyleVar_Marker, ImMarker_Circle);
                        ImGui::PushPlotStyleVar(ImPlotStyleVar_MarkerSize, 3.f);
                        //int n = 0;
                        for (size_t i = 0; i < m_PlotPhaseExists.size(); ++i) {
                            if (m_PlotPhaseExists[i])
                                ImGui::Plot(_MI.GetPhasesVec()[i].c_str(), x_data_address, &m_PlotPhaseMasses.at(i)[0], plot_items); //label, data_x, data_y, amount
                        }

                        ImGui::PopPlotStyleVar(2);
                        ImGui::PopPlotColor();
                        ImGui::EndPlot();
                    }
                } else {
                    if (ImGui::BeginPlot("Fractionated phases", x_axis_label, "Mass (fractionated)", {ImGui::GetWindowWidth() - 5.f, ImGui::GetWindowHeight()}, plot_flags, axis_flags, axis_flags_y)) {
                        ImGui::PushPlotColor(ImPlotCol_MarkerFill, ImVec4(0, 0, 0, 0));
                        ImGui::PushPlotStyleVar(ImPlotStyleVar_Marker, ImMarker_Circle);
                        ImGui::PushPlotStyleVar(ImPlotStyleVar_MarkerSize, 3.f);
                        //int n = 0;
                        for (size_t i = 0; i < m_PlotFracPhaseExists.size(); ++i) {
                            if (m_PlotFracPhaseExists[i])
                                ImGui::Plot(_MI.GetPhasesVec()[i].c_str(), x_data_address, &m_PlotFracPhaseMasses.at(i)[0], plot_items); //label, data_x, data_y, amount
                        }

                        ImGui::PopPlotStyleVar(2);
                        ImGui::PopPlotColor();
                        ImGui::EndPlot();
                    }
                }
                ImGui::EndChild();     //Second child
                ImGui::PopPlotColor(); //BG color

                ImGui::EndTabItem();
            }
        }

        if (ImGui::BeginTabItem("Log")) {
            ImGui::Text("Log");
            ImGui::Separator();

            //vector<T>::reverse_iterator
            ImVec4 color;
            size_t log_length = Elog::Log().GetLog().size();
            for (auto it = Elog::Log().GetLog().rbegin(); log_length >= 50 ? it != Elog::Log().GetLog().rbegin() + 50 : it != Elog::Log().GetLog().rend(); ++it) {
                switch ((*it).second) {
                case NOTICE:
                    color = ImVec4(1, 1, 1, 1);
                    break;
                case CAUTION:
                    color = ImVec4(1, 0.9f, 0.1f, 1);
                    break;
                case WARNING:
                    color = ImVec4(0.9f, 0.5f, 0, 1);
                    break;
                case CRITICAL:
                    color = ImVec4(1, 0.2f, 0.1f, 1);
                    break;
                }
                ImGui::TextColored(color, "%s", (*it).first.c_str());
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Information")) {
            ImGui::Text("License");
            ImGui::Separator();

            ImGui::TextWrapped("easyMelts 0.3.0 (beta) Paula Antoshechkina (c) 2025"
                                "\n\nOriginally created by Einari Suikkanen (c) 2020-2024"
                                "\n\nSee License.txt distributed with this application for legal information.");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("Information");
            ImGui::Separator();
            ImGui::TextWrapped(
                "easyMelts is intended for thermodynamic modeling of phase equilibria\n"
                "using the Melts engine and thermodynamic database by Mark S. Ghiorso.\n"
                "Note that easyMelts is not connected to or endorsed by the author(s) of Melts."
                //"\n\nThe prefix 'easy' does not imply that Melts is simple!\n"
                //" Instead, it refers to a specific design philosophy:"
                //" Software tools should be as intuitive and easy as possible, so that"
                //" the scientist can fully concentrate on the science."

                "\n\nHave a pleasant day modeling!"
                //"\n\nContact: einari.suikkanen[at]gmail.com\n\n");
                "\n\nContact: psmith[at]gps.caltech.edu\n\n");

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
#ifdef DEBUG
    ImGui::ShowDemoWindow();
#endif
    ImGui::EndFrame();
}
