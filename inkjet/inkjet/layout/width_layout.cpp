#define IMGUI_DEFINE_MATH_OPERATORS
#include "width_layout.h"
#include "iostream"

void inkjet::BeginWLayout(const std::vector<float> &layout, bool step, bool visualize)
{
    widthAccumulation = 0.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, ImGui::GetStyle().ItemSpacing.y});
    ImGui::Dummy({0,0}); ImGui::SameLine(); // remove spacing
    initialCursor = ImGui::GetCursorScreenPos();
    layoutSize = ImVec2{ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight()};
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    if(visualize)
        draw_list->AddRect(initialCursor, initialCursor + layoutSize,ImColor(255, 0, 0));


    float fixedWidthsPx = 0;
    float nGrowWidthSteps = 0;

    for(const auto& width : layout)
    {
        if(0 <= width)
            fixedWidthsPx += width;
        else
            nGrowWidthSteps -= width;
    }

    fixedWidthsPx += ImGui::GetStyle().ItemSpacing[0] * (layout.size()-1);
    float growStep = (ImGui::GetContentRegionAvail()[0] - fixedWidthsPx) / nGrowWidthSteps;

    // parse width arguments
    widthLayoutWidths.clear();
    for(const auto& width : layout)
    {
        if(0 <= width)
            widthLayoutWidths.push_back((float)width);
        else
            widthLayoutWidths.push_back((float)-width * growStep);
    }

    // visualize
    if(visualize)
    {
        float widthSum = 0.0;
        for (const auto &width: widthLayoutWidths)
        {
            draw_list->AddLine(
                    initialCursor + ImVec2(widthSum, 0),
                    initialCursor + ImVec2(widthSum, layoutSize.y),
                    ImColor(255, 0, 0));
            widthSum += width;
        }
    }

    widthLayoutIndex = 0;
    ImGui::PushItemWidth(widthLayoutWidths[widthLayoutIndex]);

    if(step)
    {
        widthAccumulation += widthLayoutWidths[widthLayoutIndex];
        widthLayoutIndex++;
    }
}

void inkjet::StepWLayout()
{
    if(widthLayoutWidths.size() <= widthLayoutIndex)
    {
        std::cerr<<"inkjet::StepWLayout() index out of bound.";
        return;
    }
    ImGui::PopItemWidth();
    ImGui::PushItemWidth(widthLayoutWidths[widthLayoutIndex]);
    ImGui::SameLine();
    ImGui::SetCursorPosX(initialCursor.x + widthAccumulation);
    widthAccumulation += widthLayoutWidths[widthLayoutIndex];
    widthLayoutIndex++;
}

ImVec2 inkjet::StepWLayoutVec()
{
    if(widthLayoutWidths.size() <= widthLayoutIndex)
    {
        std::cerr<<"inkjet::StepWLayout() index out of bound.";
        return {0, 0};
    }
    ImGui::SameLine();
    ImVec2 vec = {widthLayoutWidths[widthLayoutIndex], 0};
    ImGui::SetCursorPosX(initialCursor.x + widthAccumulation);
    widthAccumulation += widthLayoutWidths[widthLayoutIndex];
    widthLayoutIndex++;
    return vec;
}

void inkjet::EndWLayout()
{
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
}
