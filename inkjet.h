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

    static void HLine()
    {
        auto draw_list = ImGui::GetCurrentWindow()->DrawList;
        draw_list->AddLine(
                ImGui::GetCursorScreenPos(),
                ImGui::GetCursorScreenPos() + ImVec2(ImGui::GetContentRegionAvail().x, 0),
                ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Dummy({0, 1});
    }

    static void VLine()
    {
        auto draw_list = ImGui::GetCurrentWindow()->DrawList;
        draw_list->AddLine(
                ImGui::GetCursorScreenPos(),
                ImGui::GetCursorScreenPos() + ImVec2(0, ImGui::GetContentRegionAvail().y),
                ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Dummy({1, 0});
    }

    static void DockSpace(bool leaveSpaceForStatusBar = true)
    {
        const int padding = 0;
        const int dockSpacing = 1;
        ImGui::PushStyleVar(ImGuiStyleVar_DockingSeparatorSize, dockSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, {0, 4});
        ImGui::PushStyleColor(ImGuiCol_Border, ImGui::GetStyleColorVec4(ImGuiCol_Border));
        ImGui::PushStyleColor(ImGuiCol_Text, textSubtitle);
        ImGui::Dummy({0, padding});
        ImGui::Dummy({padding, 0});
        ImGui::SameLine();
        ImGui::DockSpace(ImGui::GetID("MainDockSpace"),
                         ImVec2(-padding, -padding - (leaveSpaceForStatusBar ? ImGui::GetFrameHeight()+1 : 0)),
                         ImGuiDockNodeFlags_PassthruCentralNode|ImGuiDockNodeFlags_NoCloseButton);
        ImGui::PopStyleVar(3);
        ImGui::PopStyleColor(2);
    }

    static void setStyle()
    {
        ImGuiStyle* style =  &ImGui::GetStyle();
        ImVec4* colors = style->Colors;


        colors[ImGuiCol_Text]                   = colorRGB(34, 34, 34);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg]               = white;
        colors[ImGuiCol_ChildBg]                = panel;
        colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
        colors[ImGuiCol_Border]                 = colorRGBA(228, 228, 228, 255);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_FrameBgHovered]         = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_FrameBgActive]          = colorRGBA(220, 220, 220, 170);
        colors[ImGuiCol_TitleBg]                = panel;
        colors[ImGuiCol_TitleBgActive]          = panel;
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = white;
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        colors[ImGuiCol_CheckMark]              = colorRGB(34, 34, 34);
        colors[ImGuiCol_SliderGrab]             = colorRGB(170, 170, 170);
        colors[ImGuiCol_SliderGrabActive]       = highlight;
        colors[ImGuiCol_Button]                 = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_ButtonHovered]          = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_ButtonActive]           = colorRGBA(220, 220, 220, 170);
        colors[ImGuiCol_Header]                 = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_HeaderHovered]          = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_HeaderActive]           = colorRGBA(220, 220, 220, 170);
        colors[ImGuiCol_Separator]              = colorRGBA(220, 220, 220, 70);
        colors[ImGuiCol_SeparatorHovered]       = colorRGBA(220, 220, 220, 120);
        colors[ImGuiCol_SeparatorActive]        = colorRGBA(220, 220, 220, 150);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab]                    = panel;
        colors[ImGuiCol_TabHovered]             = panel;
        colors[ImGuiCol_TabActive]              = panel;
        colors[ImGuiCol_TabUnfocused]           = panel;
        colors[ImGuiCol_TabUnfocusedActive]     = panel;
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

        style->WindowMenuButtonPosition = ImGuiDir_Right;
        style->WindowPadding = {16, 8};
        style->FramePadding = {8, 8};
        style->ItemSpacing = {12, 12};
        style->ItemInnerSpacing = {4, 4};
        style->WindowBorderSize = 0;
    }

    static bool TransparentButton(const char* name)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, InkJet::colorRGBA(0, 0, 0, 0));
        bool ret = ImGui::Button(name);
        ImGui::PopStyleColor();
        return ret;
    }

    static void Begin(const char* name, bool* open=NULL)
    {
        // check tab active
        ImGuiWindow* window = ImGui::FindWindowByName(name);
        bool isActive = window != nullptr && !window->Hidden;

        // check tab hover
        bool isHovering = window != nullptr && ImGui::IsMouseHoveringRect(window->DockTabItemRect.Min, window->DockTabItemRect.Max);


        ImGui::PushStyleColor(ImGuiCol_Text, isActive ? highlight : (isHovering ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : textSubtitle));

        // begin window
        ImGuiWindowFlags window_flags =  ImGuiWindowFlags_None;
        ImGui::Begin(name, open, window_flags);

        // pop inactive title color
        ImGui::PopStyleColor();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
    }

    static void End()
    {
        ImGui::PopStyleVar();
        // pop body font
        //ImGui::PopFont();

        // end window
        ImGui::End();

        // pop title font
        //ImGui::PopFont();

    }

    static void initFont()
    {
        auto& io = ImGui::GetIO();

        float baseFontSize = 16.0f * io.DisplayFramebufferScale.x;
        ImFontConfig config;
        fonts.insert({"body", io.Fonts->AddFontFromFileTTF("../Resources/assets/fonts/SpaceGrotesk/SpaceGrotesk-Regular.ttf", baseFontSize, NULL, io.Fonts->GetGlyphRangesDefault())});
        float iconFontSize = baseFontSize * 1.1f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly
        static const ImWchar icons_ranges[] = { ICON_MIN_MD, ICON_MAX_16_MD, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.GlyphMinAdvanceX = iconFontSize;
        icons_config.GlyphOffset = {0, 4* io.DisplayFramebufferScale.x};
        io.Fonts->AddFontFromFileTTF( "../Resources/assets/fonts/MaterialIcons-Regular.ttf", iconFontSize, &icons_config, icons_ranges );
    }

    static bool InputText(const char *label, const char* hint, char *buf, size_t buf_size, ImGuiInputTextFlags flags = 0)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, InkJet::white);
        bool ret = ImGui::InputTextWithHint(label, hint, buf, buf_size, flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        return ret;
    }
};
#endif