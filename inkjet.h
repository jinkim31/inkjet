#ifndef INKJET_H_
#define INKJET_H_

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "immapp/immapp.h"
#include "imgui_internal.h"
#include "external/IconFontCppHeaders/IconsMaterialDesign.h"
#include <unordered_map>

namespace InkJet
{
static ImVec4 colorRGB(uint8_t r, uint8_t g, uint8_t b){ return {r/255.0f, g/255.0f, b/255.0f, 1.0f}; }
static ImVec4 colorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a){ return {r/255.0f, g/255.0f, b/255.0f, a/255.0f}; }
static const ImVec4 white = colorRGB(255, 255, 255);
static const ImVec4 background = colorRGB(250, 250, 250);
static const ImVec4 panel = colorRGB(242, 242, 242);
static const ImVec4 highlight = colorRGB(41, 98, 255);
static const ImVec4 textSubtitle = colorRGB(85, 85, 85);
static std::map<std::string, ImFont*> fonts;

void BeginMainWindow();

void EndMainWindow();

void DockSpace(bool leaveSpaceForStatusBar = true);

void setStyle();

void Begin(const char* name, bool* open=NULL);

void End();

void initFont();

bool InputText(const char *label, const char* hint, char *buf, size_t buf_size, ImGuiInputTextFlags flags = 0);

void WidgetMenuBar();

bool TransparentButton(const char* name);

void HLine();

void VLine();

};
#endif