#ifndef INKJET_H_
#define INKJET_H_

#ifdef _WIN32
#define INKJET_ASSET_PREFIX "./"
#elif __unix__
#define INKJET_ASSET_PREFIX
#elif __linux__
#define INKJET_ASSET_PREFIX
#elif __APPLE__
#define INKJET_ASSET_PREFIX "../Resources/"
#endif

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <immapp/immapp.h>
#include <imgui_internal.h>
#include <implot/implot.h>
#include <siglot/object.h>
#include <siglot/thread.h>
#include <siglot/lookup.h>
#include <unordered_map>
#ifdef INKJET_WITH_IMMVISION
#include <immvision/image.h>
#include <opencv2/opencv.hpp>
#endif
#include "../external/IconFontCppHeaders/IconsMaterialDesign.h"

namespace InkJet
{
static ImVec4 colorRGB(uint8_t r, uint8_t g, uint8_t b){ return {r/255.0f, g/255.0f, b/255.0f, 1.0f}; }
static ImVec4 colorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a){ return {r/255.0f, g/255.0f, b/255.0f, a/255.0f}; }
static const ImVec4 white = colorRGB(255, 255, 255);
static const ImVec4 background = colorRGB(250, 250, 250);
static const ImVec4 panel = colorRGB(242, 242, 242);
static const ImVec4 highlight = colorRGB(41, 98, 255);
static const ImVec4 textSubtitle = colorRGB(85, 85, 85);
static const ImVec4 border = colorRGB(211, 211, 211);
static std::map<std::string, ImFont*> fonts;

void BeginMainWindow();

void EndMainWindow();

void DockSpace(bool leaveSpaceForStatusBar = true);

void setStyle();

void Begin(const char* name, bool* open=NULL, bool useMenu=false);

void End();

void initFont();

bool InputText(const char *label, const char* hint, char *buf, size_t buf_size, ImGuiInputTextFlags flags = 0);

void WidgetMenuBar(const std::function<void()>& Menu, const std::function<void()>& Widget, const float& menuWidth=300);

bool TransparentButton(const char* name, const ImVec2& size=ImVec2(0, 0));

void HLine();

void VLine();

#ifdef INKJET_WITH_IMMVISION
void ImageView(char* name, cv::Mat mat, ImmVision::ImageParams& param, bool home, bool refresh);
#endif

bool Combo(const char* label, int* index, const std::vector<std::string>& items);

bool Checkbox(const char* label, bool* check);

void SiglotConnectionGraphView();

};
#endif