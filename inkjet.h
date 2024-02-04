#ifndef INKJET_H_
#define INKJET_H_

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "immapp/immapp.h"
#include "imgui_internal.h"
#include <unordered_map>

namespace InkJet
{
    static ImVec4 colorRGB(uint8_t r, uint8_t g, uint8_t b){ return {r/255.0f, g/255.0f, b/255.0f, 1.0f}; }
    static ImVec4 colorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a){ return {r/255.0f, g/255.0f, b/255.0f, a/255.0f}; }
    static const ImVec4 white = colorRGB(255, 255, 255);
    static const ImVec4 background = colorRGB(248, 248, 248);
    static std::map<std::string, ImFont*> fonts;

    static void BeginMainWindow()
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, background);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("MAIN", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(2);
    }

    static void EndMainWindow()
    {
        ImGui::End();
    }

    static void NavBar(float height = 0.0)
    {
        height = height==0.0f ? ImGui::GetFrameHeightWithSpacing() : height;
        auto draw_list = ImGui::GetCurrentWindow()->DrawList;
        draw_list->AddRectFilled(
                ImGui::GetCursorScreenPos(),
                ImGui::GetCursorScreenPos() + ImVec2(ImGui::GetContentRegionAvail().x, height),
                ImGui::GetColorU32(ImGuiCol_MenuBarBg));
        draw_list->AddLine(
                ImGui::GetCursorScreenPos() + ImVec2(0, height-1),
                ImGui::GetCursorScreenPos() + ImVec2(ImGui::GetContentRegionAvail().x, height-1),
                IM_COL32(241, 243, 250, 255));
        ImGui::Dummy({0, 0}); ImGui::SameLine();
    }
    static void DockSpace()
    {
        const int padding = 8;
        const int dockSpacing = 8;
        ImGui::PushStyleVar(ImGuiStyleVar_DockingSeparatorSize, dockSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
        ImGui::PushStyleColor(ImGuiCol_Border, background);
        ImGui::Dummy({0, padding});
        ImGui::Dummy({padding, 0});
        ImGui::SameLine();
        ImGui::PushFont(fonts["heading"]);
        ImGui::DockSpace(ImGui::GetID("MainDockSpace"), ImVec2(-padding, -padding),
                         ImGuiDockNodeFlags_PassthruCentralNode |
                         ImGuiDockNodeFlags_NoWindowMenuButton |
                         ImGuiDockNodeFlags_NoCloseButton);
        ImGui::PopFont();
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor();
    }

    static void setStyle()
    {
        ImGuiStyle* style =  &ImGui::GetStyle();
        ImVec4* colors = style->Colors;


        colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg]               = white;
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
        colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_TitleBg]                = white;
        colors[ImGuiCol_TitleBgActive]          = white;
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = colorRGB(252, 252, 252);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        colors[ImGuiCol_CheckMark]              = colorRGB(0, 0, 0);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
        colors[ImGuiCol_Button]                 = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_ButtonHovered]          = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_ButtonActive]           = colorRGBA(220, 220, 220, 170);
        colors[ImGuiCol_Header]                 = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_HeaderHovered]          = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_HeaderActive]           = colorRGBA(220, 220, 220, 170);
        colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab]                    = white;
        colors[ImGuiCol_TabHovered]             = white;
        colors[ImGuiCol_TabActive]              = white;
        colors[ImGuiCol_TabUnfocused]           = white;
        colors[ImGuiCol_TabUnfocusedActive]     = white;
        //colors[ImGuiCol_DockingPreview]         = colors[ImGuiCol_Header] * ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
        colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_NavHighlight]           = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

        style->WindowMenuButtonPosition = ImGuiDir_None;
        style->WindowPadding = {16, 16};
        style->FramePadding = {8, 8};
        style->ItemSpacing = {8, 8};
        style->ItemInnerSpacing = {4, 4};
        style->WindowBorderSize = 0;
    }

    static void Begin(const char* name, bool* open=NULL)
    {
        // set splitter color
        ImGui::PushStyleColor(ImGuiCol_WindowBg, white);

        // set title color if inactive
        ImGuiWindow* window = ImGui::FindWindowByName(name);
        bool changeColor = window != nullptr && window->Hidden;
        if (changeColor)
            ImGui::PushStyleColor(ImGuiCol_Text, colorRGB(120, 120, 120));

        // push heading font
        ImGui::PushFont(fonts["heading"]);

        // begin window
        ImGuiWindowFlags window_flags =  ImGuiWindowFlags_None;
        ImGui::Begin(name, open, window_flags);

        // push body font
        ImGui::PushFont(fonts["body"]);

        // pop inactive title color
        if (changeColor)
            ImGui::PopStyleColor();

        // pop style
        ImGui::PopStyleColor(1);
    }

    static void End()
    {
        // draw tab underline
        /*
        auto window = ImGui::GetCurrentWindow();
        auto draw_list = window->DrawList;
        bool tabActive = window != nullptr && !window->Hidden;
        draw_list->AddRectFilled(
                {window->DockTabItemRect.Min.x, window->DockTabItemRect.Max.y+4},
                {window->DockTabItemRect.Max.x - (tabActive ? 16.0f : 0) , window->DockTabItemRect.Max.y}, 0xFF000000);
        */

        // pop body font
        ImGui::PopFont();

        // end window
        ImGui::End();

        // pop heading font
        ImGui::PopFont();

    }

    static void initFont()
    {
        auto& io = ImGui::GetIO();
        fonts.insert({"body", io.Fonts->AddFontFromFileTTF("../Resources/assets/fonts/SpaceGrotesk/SpaceGrotesk-Regular.ttf", 32.0f, NULL, io.Fonts->GetGlyphRangesDefault())});
        fonts.insert({"heading", io.Fonts->AddFontFromFileTTF("../Resources/assets/fonts/SpaceGrotesk/SpaceGrotesk-Bold.ttf", 46.0f, NULL, io.Fonts->GetGlyphRangesDefault())});
    }
};
#endif