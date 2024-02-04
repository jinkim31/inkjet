#include "inkjet.h"

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

    ImGui::Button("asdf");

    InkJet::DockSpace();

    ImGui::ShowDemoWindow();

    static bool openApple = true;
    InkJet::Begin("Apple", &openApple);
    InkJet::End();

    InkJet::Begin("Banana", &openApple);
    ImGui::Button("Banana");
    InkJet::End();

    InkJet::Begin("Cherry", &openApple);
    InkJet::End();

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
    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnerParams, addOnsParams);
    return 0;
}
