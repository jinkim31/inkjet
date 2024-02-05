#include "inkjet.h"
#include <implot/implot.h>

void Gui()
{
    InkJet::BeginMainWindow();

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
    ImGui::PushStyleColor(ImGuiCol_ChildBg, InkJet::panel);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    ImGui::BeginChild("UtilityChild", {0, ImGui::GetFrameHeight()}, ImGuiChildFlags_None, ImGuiWindowFlags_None);

    ImGui::PushStyleColor(ImGuiCol_Button, InkJet::colorRGBA(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Text, InkJet::colorRGB(76, 175, 80));
    ImGui::Button(ICON_MD_PLAY_ARROW"##UtilityButton"); ImGui::SameLine();
    ImGui::PopStyleColor(2);

    // utility widgets
    char buffer[100] = "Hello World";
    InkJet::InputText("##UtillityText", buffer, 100); ImGui::SameLine();

    // utility child end and line
    ImGui::EndChild();
    InkJet::HLine();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    // dockspace
    InkJet::DockSpace();

    bool open = true;
    InkJet::Begin(ICON_MD_FOLDER_OPEN" Explorer");
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" main.cpp", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" main.h", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" lib.c", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" lib.h", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_TERMINAL" Terminal");
    InkJet::End();
    InkJet::Begin(ICON_MD_BAR_CHART" Plot", &open);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, InkJet::white);
        if(ImPlot::BeginPlot("Plot", ImGui::GetContentRegionAvail()))
            ImPlot::EndPlot();
        ImGui::PopStyleColor();
    InkJet::End();

    InkJet::Begin(ICON_MD_COLOR_LENS" ImGui Style Editor");
        ImGui::ShowStyleEditor();
    InkJet::End();
    InkJet::Begin(ICON_MD_COLOR_LENS" ImPlot Style Editor");
        ImPlot::ShowStyleEditor();
    InkJet::End();
    //ImPlot::ShowDemoWindow();

    InkJet::EndMainWindow();
}


int main(int , char *[])
{
    HelloImGui::RunnerParams runnerParams;
    runnerParams.callbacks.SetupImGuiStyle = InkJet::setStyle;
    runnerParams.callbacks.ShowGui = Gui;
    runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::NoDefaultWindow;
    runnerParams.callbacks.LoadAdditionalFonts = InkJet::initFont;
    runnerParams.imGuiWindowParams.enableViewports = true;
    runnerParams.fpsIdling.enableIdling = false;
    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnerParams, addOnsParams);
    return 0;
}
