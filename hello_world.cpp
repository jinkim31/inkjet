#include "inkjet.h"
#include <implot/implot.h>

void Gui()
{
    InkJet::BeginMainWindow();

    if (ImGui::BeginMainMenuBar()) {
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
        ImGui::EndMainMenuBar();
    }

    InkJet::NavBar();

    ImGui::Button("NavBar Button");

    InkJet::DockSpace();

    ImGui::ShowDemoWindow();

    ImPlot::ShowDemoWindow();

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
