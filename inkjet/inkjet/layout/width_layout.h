#ifndef INKJET_WIDTH_LAYOUT
#define INKJET_WIDTH_LAYOUT

#include <imgui_internal.h>

namespace inkjet
{
static std::vector<float> widthLayoutWidths;
static int widthLayoutIndex;

void BeginWLayout(const std::vector<float>& layout, bool step=true);
void StepWLayout();
ImVec2 StepWLayoutVec();
void EndWLayout();
}

#endif