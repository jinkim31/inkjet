#include "width_layout.h"
#include "iostream"

void InkJet::BeginWLayout(const std::vector<float> &layout, bool step)
{
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

    widthLayoutWidths.clear();
    for(const auto& width : layout)
    {
        if(0 <= width)
            widthLayoutWidths.push_back((float)width);
        else
            widthLayoutWidths.push_back((float)-width * growStep);
    }

    widthLayoutIndex = 0;
    if(step)
        ImGui::PushItemWidth(widthLayoutWidths[widthLayoutIndex++]);
    else
        ImGui::PushItemWidth(widthLayoutWidths[widthLayoutIndex]);
}

void InkJet::StepWLayout()
{
    if(widthLayoutWidths.size() <= widthLayoutIndex)
    {
        std::cerr<<"InkJet::StepWLayout() index out of bound.";
        return;
    }
    ImGui::PopItemWidth();
    ImGui::PushItemWidth(widthLayoutWidths[widthLayoutIndex++]);
    ImGui::SameLine();
}

ImVec2 InkJet::StepWLayoutVec()
{
    if(widthLayoutWidths.size() <= widthLayoutIndex)
    {
        std::cerr<<"InkJet::StepWLayout() index out of bound.";
        return {0, 0};
    }
    ImGui::SameLine();
    return {widthLayoutWidths[widthLayoutIndex++], 0};
}

void InkJet::EndWLayout()
{
    ImGui::PopItemWidth();
}
