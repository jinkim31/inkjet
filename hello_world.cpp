#include "inkjet.h"
#include <implot/implot.h>

void Gui()
{
    // begin main
    InkJet::BeginMainWindow();

    // menu bar
    InkJet::WidgetMenuBar();

    // dockspace
    InkJet::DockSpace();

    // status bar
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    InkJet::HLine();
    ImGui::BeginChild("StatusBarChild");
    InkJet::TransparentButton("Status Bar Button");
    ImGui::EndChild();
    ImGui::PopStyleVar();

    // windows
    bool open = true;
    InkJet::Begin(ICON_MD_FOLDER_OPEN" Explorer");
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" main.cpp", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" main.h", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" mylib.c", &open);
    InkJet::End();
    InkJet::Begin(ICON_MD_INSERT_DRIVE_FILE" mylib.h", &open);
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

    // end main
    InkJet::EndMainWindow();
}


int main(int , char *[])
{
    HelloImGui::RunnerParams runnerParams;
    runnerParams.callbacks.SetupImGuiStyle = InkJet::setStyle;
    runnerParams.callbacks.ShowGui = Gui;
    runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::NoDefaultWindow;
    runnerParams.callbacks.LoadAdditionalFonts = InkJet::initFont;
    runnerParams.imGuiWindowParams.enableViewports = false;
    runnerParams.fpsIdling.enableIdling = false;
    runnerParams.appWindowParams.windowTitle = "InkJet";
    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnerParams, addOnsParams);
    return 0;
}
