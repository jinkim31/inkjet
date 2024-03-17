#include "application.h"

Application::Application()
{
    mThread.setName("main thread");
    this->setName("application");
    this->move(mThread);

    HelloImGui::RunnerParams runnerParams;
    runnerParams.callbacks.SetupImGuiStyle = InkJet::setStyle;
    runnerParams.callbacks.ShowGui = [&]{mThread.step(); Render();};
    runnerParams.callbacks.BeforeExit = [&]{
        this->remove();
    };
    runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::NoDefaultWindow;
    runnerParams.callbacks.LoadAdditionalFonts = InkJet::initFont;
    runnerParams.imGuiWindowParams.enableViewports = false;
    runnerParams.fpsIdling.enableIdling = false;
    runnerParams.appWindowParams.windowTitle = "InkJet";
    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnerParams, addOnsParams);
}

Application::~Application()
{

}

void Application::Render()
{
    // begin main
    InkJet::BeginMainWindow();

    // menu bar
    InkJet::WidgetMenuBar([]{
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
    }, []{
        ImGui::PushStyleColor(ImGuiCol_Text, InkJet::colorRGB(76, 175, 80));
        InkJet::TransparentButton(ICON_MD_PLAY_ARROW"##UtilityButton"); ImGui::SameLine();
        ImGui::PopStyleColor();
        char buffer[100] = "";
        InkJet::InputText("##UtillityText", "Utility Text", buffer, 100); ImGui::SameLine();
    });

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
    InkJet::SiglotConnectionGraphView();

    InkJet::Begin(ICON_MD_TERMINAL" Terminal");
    InkJet::End();

    InkJet::Begin(ICON_MD_BAR_CHART" Plot");
    ImGui::PushStyleColor(ImGuiCol_FrameBg, InkJet::white);
    if(ImPlot::BeginPlot("Plot", ImGui::GetContentRegionAvail()))
        ImPlot::EndPlot();
    ImGui::PopStyleColor();
    InkJet::End();

    // end main
    InkJet::EndMainWindow();
}