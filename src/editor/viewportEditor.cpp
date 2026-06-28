#include <iostream>
#include "aur.h"
#include "imgui_internal.h"
bool viewportInit = true;
void viewportDock() {
    UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0,0));
    UI::Begin("Viewport", NULL, uiWindowFlags_NoMove | uiWindowFlags_NoResize | uiWindowFlags_NoCollapse);
    uiID dockspace = UI::GetID("ViewportDock");
    if (viewportInit) {
        viewportInit = false;
        UI::DockBuilderRemoveNode(dockspace);
        UI::DockBuilderAddNode(dockspace, uiDockFlags_DockSpace);
        UI::DockBuilderSetNodeSize(dockspace, UI::GetMainViewport()->Size);
        uiID panel, viewport;
        UI::DockBuilderSplitNode(dockspace, AUR::Editor::viewportPanelLocation ? Var::Dir::Right : Var::Dir::Left, 0.25f, &panel, &viewport);
        UI::DockBuilderDockWindow("Viewport Panel", panel);
        UI::DockBuilderDockWindow("Viewport Main", viewport);
        UI::DockBuilderFinish(dockspace);
    }
    UI::DockSpace(dockspace, vec2(0, 0), uiDockFlags_NoUndocking | uiDockFlags_NoTabBar | uiDockFlags_NoResize | uiDockFlags_PassthruCentralNode );
    UI::End();
    UI::PopStyleVar(2);
}
void viewportEditor(unsigned int texture) {
    viewportDock();
    UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0,0));
    if (UI::Begin("Viewport Main", nullptr, uiWindowFlags_MenuBar)) viewportInit = !viewportInit;
    UI::PopStyleVar(2);
    if (UI::BeginMenuBar()) {
        char moveLabel[16];
        std::snprintf(moveLabel, sizeof(moveLabel), "Move %.2f", AUR::Snap::MovePresets[AUR::Snap::MoveIndex]);
        if (UI::BeginMenu(moveLabel)) {
            for (int i = 0; i < AUR::Snap::MovePresets.size(); i++) {
                bool isSelected = (AUR::Snap::MoveIndex == i);
                char label[8];
                std::snprintf(label, sizeof(label), "%.2f", AUR::Snap::MovePresets[i]);
                if (UI::Selectable(label, isSelected)) {
                    AUR::Snap::MoveIndex = i;
                };
                if (isSelected)UI::SetItemDefaultFocus();
            }
            UI::EndMenu();
        };
        char rotateLabel[16];
        std::snprintf(rotateLabel, sizeof(rotateLabel), "Rotate %.2f", AUR::Snap::RotatePresets[AUR::Snap::RotateIndex]);
        if (UI::BeginMenu(rotateLabel)) {
            for (int i = 0; i < AUR::Snap::RotatePresets.size(); i++) {
                bool isSelected = (AUR::Snap::RotateIndex == i);
                char label[8];
                std::snprintf(label, sizeof(label), "%.2f", AUR::Snap::RotatePresets[i]);
                if (UI::Selectable(label, isSelected)) {
                    AUR::Snap::RotateIndex = i;
                };
                if (isSelected)UI::SetItemDefaultFocus();
            }
            UI::EndMenu();
        };
        char scaleLabel[16];
        std::snprintf(scaleLabel, sizeof(scaleLabel), "Scale %.2f", AUR::Snap::ScalePresets[AUR::Snap::ScaleIndex]);
        if (UI::BeginMenu(scaleLabel)) {
            for (int i = 0; i < AUR::Snap::ScalePresets.size(); i++) {
                bool isSelected = (AUR::Snap::ScaleIndex == i);
                char label[8];
                std::snprintf(label, sizeof(label), "%.2f", AUR::Snap::ScalePresets[i]);
                if (UI::Selectable(label, isSelected)) {
                    AUR::Snap::ScaleIndex = i;
                };
                if (isSelected)UI::SetItemDefaultFocus();
            }
            UI::EndMenu();
        };
        UI::EndMenuBar();
    };
    
    vec2 pos = UI::GetWindowPos();
    aur.viewportPosition = pos;
    aur.viewportWidth = UI::GetContentRegionAvail().x;
    aur.viewportHeight = UI::GetContentRegionAvail().y;
    UI::Image((ImTextureID)(uintptr_t)texture, UI::GetContentRegionAvail(), vec2(0, 1), vec2(1, 0));
    UI::End();
    
    static int viewportHeaderOpen = -1;
    UI::Begin("Viewport Panel", nullptr, uiWindowFlags_MenuBar);
    if (UI::BeginMenuBar()) {
        if (UI::MenuItem("Collapse All")) viewportHeaderOpen = 0;
        if (UI::MenuItem("Expand All"))   viewportHeaderOpen = 1;
        if (UI::MenuItem("Panel Location")) { AUR::Editor::viewportPanelLocation = !AUR::Editor::viewportPanelLocation; viewportInit = !viewportInit; };
        UI::EndMenuBar();
    };
    if (viewportHeaderOpen != -1) UI::SetNextItemOpen(viewportHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("Camera", uiTreeFlags_DefaultOpen)) {
        UI::DragFloat ("Field of View", &camera.fov, 0.01f);
        UI::DragFloat3("Position", &camera.location.x, 0.01f);
        UI::DragFloat2("Rotation", &camera.rotation.x, 0.01f);
        UI::DragFloat ("Speed", &camera.speed, 0.01f, 0.0f, 5.0f);
    }
    viewportHeaderOpen = -1;
    UI::End();
}