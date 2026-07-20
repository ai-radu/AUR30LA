#include <iostream>
#include "aur.hpp"
#include "imgui_internal.h"
static uiTextFilter viewportFilter;
c1 vInit = true;
static c1 vPopup = false;
void ViewportEditor(GLFWwindow* window, unsigned int texture) {
    uiContext& g = *GImGui;
    uiIO& io = g.IO;
    UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
    UI::PushStyleVar(uiStyleVar_WindowPadding, v2(0,0));
    c1 viewportActive = UI::Begin("Viewport", NULL, uiWindowFlags_NoMove | uiWindowFlags_NoResize | uiWindowFlags_NoCollapse);
    uiID dockspace = UI::GetID("ViewportDock");
    if (vInit) {
        vInit = false;
        UI::DockBuilderRemoveNode(dockspace);
        UI::DockBuilderAddNode(dockspace, uiDockFlags_DockSpace);
        UI::DockBuilderSetNodeSize(dockspace, UI::GetMainViewport()->Size);
        uiID panel, viewport;
        UI::DockBuilderSplitNode(dockspace, AUR::Editor::viewportPanel, 0.25f, &panel, &viewport);
        UI::DockBuilderDockWindow("Viewport Panel", panel);
        UI::DockBuilderDockWindow("Viewport Main", viewport);
        UI::DockBuilderFinish(dockspace);
    }
    UI::DockSpace(dockspace, v2(0, 0), uiDockFlags_NoUndocking | uiDockFlags_NoTabBar | uiDockFlags_NoResize | uiDockFlags_PassthruCentralNode );
    UI::End();
    UI::PopStyleVar(2);
    
    UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
    UI::PushStyleVar(uiStyleVar_WindowPadding, v2(0,0));
    if (UI::Begin("Viewport Main", nullptr, uiWindowFlags_MenuBar)) vInit = !vInit;
    UI::PopStyleVar(2);
    if (UI::BeginMenuBar()) {
        char moveLabel[16];
        std::snprintf(moveLabel, sizeof(moveLabel), "Move %.2f", AUR::Snap::MovePresets[AUR::Snap::MoveIndex]);
        if (UI::BeginMenu(moveLabel)) {
            for (int i = 0; i < AUR::Snap::MovePresets.size(); i++) {
                c1 isSelected = (AUR::Snap::MoveIndex == i);
                c8 label[8];
                std::snprintf(label, sizeof(label), "%.2f", AUR::Snap::MovePresets[i]);
                if (UI::Selectable(label, isSelected)) {
                    AUR::Snap::MoveIndex = i;
                };
                if (isSelected)UI::SetItemDefaultFocus();
            }
            UI::EndMenu();
        };
        c8 rotateLabel[16];
        std::snprintf(rotateLabel, sizeof(rotateLabel), "Rotate %.2f", AUR::Snap::RotatePresets[AUR::Snap::RotateIndex]);
        if (UI::BeginMenu(rotateLabel)) {
            for (int i = 0; i < (int)AUR::Snap::RotatePresets.size(); i++) {
                c1 isSelected = (AUR::Snap::RotateIndex == i);
                c8 label[8];
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
            for (c32 i = 0; i < (int)AUR::Snap::ScalePresets.size(); i++) {
                c1 isSelected = (AUR::Snap::ScaleIndex == i);
                c8 label[8];
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
    v2 pos = UI::GetWindowPos();
    aur.viewportPosition = pos;
    aur.viewportWidth = (int)UI::GetContentRegionAvail().x;
    aur.viewportHeight = (int)UI::GetContentRegionAvail().y;
    UI::Image((ImTextureID)(uintptr_t)texture, UI::GetContentRegionAvail(), v2(0, 1), v2(1, 0));
    c1 imageActive = UI::IsItemHovered();
    // overlay
    UI::SetNextWindowPos(pos + v2(10.0f, 30.0f));
    UI::SetNextWindowBgAlpha(0.2f);
    UI::BeginChild("Overlay", v2(),
        uiChildFlags_AutoResizeX |
        uiChildFlags_AutoResizeY,
        uiWindowFlags_NoMouseInputs |
        uiWindowFlags_NoDecoration |
        uiWindowFlags_NoDocking |
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoSavedSettings |
        uiWindowFlags_NoFocusOnAppearing
    );
    UI::Text("Location: X %s Y %s Z %s",
        std::to_string(camera.location.x).c_str(),
        std::to_string(camera.location.y).c_str(),
        std::to_string(camera.location.z).c_str()
    );
    UI::Text("Rotation: X %s Y %s Z %s",
        std::to_string(camera.rotation.x).c_str(),
        std::to_string(camera.rotation.y).c_str(),
        std::to_string(camera.rotation.z).c_str()
    );
    UI::Text("Vertices:  %d", io.MetricsRenderVertices);
    UI::Text("Indices:   %d", io.MetricsRenderIndices);
    UI::Text("Triangles: %d", io.MetricsRenderIndices / 3);
    UI::EndChild();
    UI::End();
    // help
    if (viewportActive &&
        UI::IsKeyDown(INPUT::Key_LeftCtrl) &&
        UI::IsKeyDown(INPUT::Key_LeftShift) &&
        UI::IsKeyPressed(INPUT::Key_H, false))  { vPopup = !vPopup; if (vPopup) UI::OpenPopup("Help##V"); };
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, v2(0.5f, 0.5f));
        if (vPopup) UI::OpenPopup("Help##V");
        if (UI::BeginPopupModal("Help##V", &vPopup, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
        UI::SeparatorText("Edit");
        UI::Text("        O: Open");
        UI::Text("  Shift+O: Open External"); Marker("This feature will be removed.", true);
        UI::Text("   Ctrl+S: Save");
        UI::Text("  Shift+S: Save All"); Marker("This feature will be removed.", true);
        UI::Text("    Alt+S: Save As..."); Marker("This feature will be removed.", true);
        UI::Text("   Ctrl+D: Load");
        UI::Text("  Shift+D: Load All"); Marker("This feature will be removed.", true);
        UI::Text("    Alt+D: Load External"); Marker("This feature will be removed.", true);
        UI::Text("        Z: Undo");
        UI::Text("        Y: Redo");
        UI::Text("   Alt+F4: Exit");
        // UI::Text("Esc       Exit Menu");
        UI::SeparatorText("Actions");
        UI::Separator();
        UI::Text("      0-9: Camera Locations"); Marker("Press once to set. If the camera angle hasn't change, press the same button to delete.");
        UI::Text("        A: Add New");
        UI::Text("   Ctrl+A: Add Latest"); Marker("Add the previously added item in the same location.");
        UI::Text("        C: Copy"); Marker("Copy the selected item, including all the changes.");
        UI::Text("        D: Duplicate"); Marker("Create a mirror image of the selected object.");
        UI::Text("        H: Hide/Show"); Marker("Set the alpha to 0.2f of the selected object. Press again to set to 1.0f.");
        UI::Text("   Ctrl+H: Show All"); Marker("Set the alpha off all hidden objects to 1.0f.");
        UI::Text("        Q: Quick Menu");
        UI::Text("        N: Newspaper"); Marker("This feature will be removed ?", true);
        UI::Text("        M: Tool: Move");
        UI::Text("        R: Tool: Rotate");
        UI::Text("        S: Tool: Scale");
        UI::Text("        V: Tool: Swap"); Marker("Selected object will be swapped with the next object you interact once. This feature will be removed ?", true);
        UI::Text("      Del: Delete");
        UI::Text("       F2: Rename");
        UI::SeparatorText("Movement");
        UI::Text("RMB+Mouse: Rotate Camera");
        UI::Text("    RMB+W: Forward");
        UI::Text("    RMB+A: Left");
        UI::Text("    RMB+S: Backward");
        UI::Text("    RMB+D: Right");
        UI::Text("    RMB+E: Up");
        UI::Text("    RMB+Q: Down");
        UI::EndPopup();
    }
    // input
    double mouseX, mouseY;
    if (imageActive && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.move = true;
        if (camera.firstClick) {
            glfwSetCursorPos(window, (aur.windowWidth / 2), (aur.windowHeight / 2));
            camera.firstClick = false;
        }
        glfwGetCursorPos(window, &mouseX, &mouseY);
        f32 rotx = camera.sensitivity * (f32)(mouseY - (aur.windowHeight / 2)) / (float)aur.windowHeight;
        f32 roty = camera.sensitivity * (f32)(mouseX - (aur.windowWidth  / 2)) / (float)aur.windowWidth;
        glm::vec3 newRotation = glm::rotate(
            camera.rotation,
            glm::radians(-rotx),
            glm::normalize(glm::cross(camera.rotation, camera.up))
        );
        if (!((glm::angle(newRotation, camera.up) <= glm::radians(5.0f)) 
        or (glm::angle(newRotation, -camera.up) <= glm::radians(5.0f)))) { camera.rotation = newRotation; }
        camera.rotation = glm::rotate(camera.rotation, glm::radians(-roty), camera.up);
        glfwSetCursorPos(window, (aur.windowWidth / 2), (aur.windowHeight / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        camera.move = false;
        camera.firstClick = true;
    }
    // tellme(std::to_string(camera.move), true);
    if (imageActive && camera.move) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.location += camera.speed / 10000 * camera.rotation; }; // forward
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera.location += camera.speed / 10000 * -glm::normalize(glm::cross(camera.rotation, camera.up)); }; // left
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.location += camera.speed / 10000 * -camera.rotation; }; // backwards
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera.location += camera.speed / 10000 * glm::normalize(glm::cross(camera.rotation, camera.up)); }; // right
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { camera.location += camera.speed / 10000 * camera.up; }; // up
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { camera.location += camera.speed / 10000 * -camera.up; }; // down
    }
    static int viewportHeaderOpen = -1;
    UI::Begin("Viewport Panel", nullptr, uiWindowFlags_MenuBar);
    if (UI::BeginMenuBar()) {
        if (UI::MenuItem("Collapse")) viewportHeaderOpen = 0;
        if (UI::MenuItem("Expand"))   viewportHeaderOpen = 1;
        viewportFilter.Draw("##viewportFiler", "Type to search...");
        UI::EndMenuBar();
    };
    if (viewportHeaderOpen != -1) UI::SetNextItemOpen(viewportHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("Camera")) {
        UI::SliderFloat("FOV",      &camera.fov,               1.0f,  140.0f, "%.3f", &viewportFilter, aur.sliderFlags);
        UI::DragFloat3 ("Position", &camera.location.x, 0.01f, 0.0f,    0.0f, "%.3f", &viewportFilter, aur.sliderFlags);
        UI::DragFloat3 ("Rotation", &camera.rotation.x, 0.01f, 0.0f,    0.0f, "%.3f", &viewportFilter, aur.sliderFlags);
        UI::SliderFloat("Speed",    &camera.speed,             0.0f, 5000.0f, "%.3f", &viewportFilter, aur.sliderFlags);
    }
    viewportHeaderOpen = -1;
    UI::End();
}