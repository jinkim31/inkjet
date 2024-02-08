#include "inkjet.h"

void InkJet::BeginMainWindow()
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

void InkJet::EndMainWindow()
{
    ImGui::End();
}

void InkJet::HLine()
{
    auto draw_list = ImGui::GetCurrentWindow()->DrawList;
    draw_list->AddLine(
            ImGui::GetCursorScreenPos(),
            ImGui::GetCursorScreenPos() + ImVec2(ImGui::GetContentRegionAvail().x, 0),
            ImGui::GetColorU32(ImGuiCol_Border));
    ImGui::Dummy({0, 1});
}

void InkJet::VLine()
{
    auto draw_list = ImGui::GetCurrentWindow()->DrawList;
    draw_list->AddLine(
            ImGui::GetCursorScreenPos(),
            ImGui::GetCursorScreenPos() + ImVec2(0, ImGui::GetContentRegionAvail().y),
            ImGui::GetColorU32(ImGuiCol_Border));
    ImGui::Dummy({1, 0});
}

void InkJet::DockSpace(bool leaveSpaceForStatusBar)
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

void InkJet::setStyle()
{
    ImGuiStyle* style =  &ImGui::GetStyle();
    ImVec4* colors = style->Colors;


    colors[ImGuiCol_Text]                   = colorRGB(34, 34, 34);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]               = white;
    colors[ImGuiCol_ChildBg]                = panel;
    colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
    colors[ImGuiCol_Border]                 = border;
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
    style->WindowRounding = 0;
}

bool InkJet::TransparentButton(const char* name)
{
    ImGui::PushStyleColor(ImGuiCol_Button, InkJet::colorRGBA(0, 0, 0, 0));
    bool ret = ImGui::Button(name);
    ImGui::PopStyleColor();
    return ret;
}

void InkJet::Begin(const char* name, bool* open)
{
    // check tab active
    ImGuiWindow* window = ImGui::FindWindowByName(name);
    bool isActive = window != nullptr && !window->Hidden;

    // check tab hover
    bool isHovering = window != nullptr && ImGui::IsMouseHoveringRect(window->DockTabItemRect.Min, window->DockTabItemRect.Max);


    ImGui::PushStyleColor(ImGuiCol_Text, isActive ? highlight : (isHovering ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : textSubtitle));

    // zero window padding for tab border
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});

    // begin window
    ImGuiWindowFlags window_flags =  ImGuiWindowFlags_None;
    ImGui::Begin(name, open, window_flags);

    // pop inactive title color
    ImGui::PopStyleColor();

    // tab border without spacing below
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0,0});
    HLine();
    ImGui::PopStyleVar();

    // push child padding. -1 to compensate for the child window border(which is needed to get child window padding)
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {16-1, 8-1});

    // push child window background color to be same as the window background
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

    // push child border color to be same as the window background
    ImGui::PushStyleColor(ImGuiCol_Border, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

    // begin window child
    ImGui::BeginChild("windowChild", ImGui::GetContentRegionAvail(), true);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {6, 6});

    // push regular border color for the user contents
    ImGui::PushStyleColor(ImGuiCol_Border, border);
}

void InkJet::End()
{
    // pop regular border color
    ImGui::PopStyleColor();

    // pop frame padding for tab spacing
    ImGui::PopStyleVar();

    // end child
    ImGui::EndChild();

    // pop child background, border color
    ImGui::PopStyleColor(2);

    // pop child window padding
    ImGui::PopStyleVar();

    // end window
    ImGui::End();

    // pop window padding for tab border
    ImGui::PopStyleVar();

    // pop title font
    //ImGui::PopFont();
}

void InkJet::initFont()
{
    auto& io = ImGui::GetIO();

    float baseFontSize = 16.0f * io.DisplayFramebufferScale.x;
    ImFontConfig config;
    fonts.insert({"body", io.Fonts->AddFontFromFileTTF(INKJET_ASSET_PREFIX"assets/fonts/SpaceGrotesk/SpaceGrotesk-Regular.ttf", baseFontSize, NULL, io.Fonts->GetGlyphRangesDefault())});
    float iconFontSize = baseFontSize * 1.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly
    static const ImWchar icons_ranges[] = { ICON_MIN_MD, ICON_MAX_16_MD, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;
    icons_config.GlyphOffset = {0, 4* io.DisplayFramebufferScale.x};
    io.Fonts->AddFontFromFileTTF( INKJET_ASSET_PREFIX"assets/fonts/MaterialIcons-Regular.ttf", iconFontSize, &icons_config, icons_ranges );
}

bool InkJet::InputText(const char *label, const char* hint, char *buf, size_t buf_size, ImGuiInputTextFlags flags)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, InkJet::white);
    bool ret = ImGui::InputTextWithHint(label, hint, buf, buf_size, flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    return ret;
}

void InkJet::WidgetMenuBar()
{
    // menu child
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, InkJet::panel);
    ImGui::BeginChild("MenuChild", {300, ImGui::GetFrameHeight()}, ImGuiChildFlags_None, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create")) {
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem("Save as..")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Dummy")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Dummy")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();

    // same line in between
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    ImGui::SameLine();
    ImGui::PopStyleVar();

    // utility child
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    ImGui::BeginChild("UtilityChild", {0, ImGui::GetFrameHeight()}, ImGuiChildFlags_None, ImGuiWindowFlags_None);

    // utility widgets
    ImGui::PushStyleColor(ImGuiCol_Text, InkJet::colorRGB(76, 175, 80));
    InkJet::TransparentButton(ICON_MD_PLAY_ARROW"##UtilityButton"); ImGui::SameLine();
    ImGui::PopStyleColor();
    char buffer[100] = "";
    InkJet::InputText("##UtillityText", "Utility Text", buffer, 100); ImGui::SameLine();

    // utility child end and line
    ImGui::EndChild();
    InkJet::HLine();
    ImGui::PopStyleVar();
}

void InkJet::ImageView(char* name, cv::Mat mat, ImmVision::ImageParams& param, bool home, bool refresh)
{
    if(home)
        param = ImmVision::ImageParams();


    param.RefreshImage = refresh;
    param.ShowZoomButtons = false;
    param.ShowOptionsButton = false;
    param.ShowSchoolPaperBackground = false;
    param.ShowGrid = false;
    param.ShowImageInfo = false;
    param.ShowAlphaChannelCheckerboard = true;
    param.ShowOptionsPanel = false;
    param.DrawValuesOnZoomedPixels = false;
    param.ShowOptionsInTooltip = false;
    param.ShowPixelInfo = false;
    param.ImageDisplaySize = cv::Size(
            std::max(ImGui::GetContentRegionAvail().x, 20.0f),
            std::max(ImGui::GetContentRegionAvail().y-24, 20.0f));

    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    ImmVision::Image(name, mat, &param);
    //ImGui::PopStyleVar();
    param.RefreshImage = false;
}

void InkJet::SiglotConnectionGraphView()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, panel);
    InkJet::Begin(ICON_MD_HUB" Siglot Connection Graph");
    {
        static cv::Mat connectionGraphImage = cv::Mat::zeros(100, 100, CV_8UC1);
        static ImmVision::ImageParams param;
        bool refresh = false;

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {12, 0});
        if (TransparentButton(ICON_MD_CAMERA" Capture"))
        {
            siglot::Lookup::instance().dumpConnectionGraph("png", "ConnectionGraph.png");
            connectionGraphImage = cv::imread("ConnectionGraph.png");
            refresh = true;
        }
        ImGui::SameLine();
        bool home = TransparentButton(ICON_MD_HOME" Reset View");
        ImageView("##imageView",connectionGraphImage, param, home, refresh);
        ImGui::PopStyleVar();
    }InkJet::End();
    ImGui::PopStyleColor();
}