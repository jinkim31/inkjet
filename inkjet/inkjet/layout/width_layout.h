#ifndef INKJET_WIDTH_LAYOUT
#define INKJET_WIDTH_LAYOUT

#include <imgui_internal.h>
#include <vector>

namespace inkjet
{
static std::vector<float> widthLayoutWidths;
static int widthLayoutIndex;
static ImVec2 initialCursor, layoutSize;
static float widthAccumulation;

void BeginWLayout(const std::vector<float>& layout, bool step=true, bool visualize=false);
void StepWLayout();
ImVec2 StepWLayoutVec();
void EndWLayout();
}

#endif