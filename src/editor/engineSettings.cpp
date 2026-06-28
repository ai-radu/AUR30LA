#include <iostream>
#include "aur.h"
void engineSettings() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Engine Settings", NULL,
        uiWindowFlags_MenuBar |
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();
    
    static int engineHeaderOpen = -1;
    if (UI::BeginMenuBar()) {
        if (UI::MenuItem("Collapse All")) engineHeaderOpen = 0;
        if (UI::MenuItem("Expand All"))   engineHeaderOpen = 1;
        UI::Text("| AUR30LA Engine v0.3c");
        UI::EndMenuBar();
    };
    if (engineHeaderOpen != -1) UI::SetNextItemOpen(engineHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("User Interface", uiTreeFlags_DefaultOpen)) {
        UI::SliderFloat("Mouse Cursor Scale ?", &AUR::Engine::mouseCursorScale, 0.1f, 5.0f, "%.3f");
        UI::SliderFloat("Mouse Double Click Time", &AUR::Engine::mouseDoubleClickTime, 0.1f, 1.0f, "%.3f");
        
        UI::SliderFloat("Key Repeat Delay", &AUR::Engine::keyRepeatDelay, 0.1f, 1.0f, "%.3f");
        UI::SliderFloat("Key Repeat Rate", &AUR::Engine::keyRepeatRate, 0.001f, 1.0f, "%.3f");
        
        UI::SliderInt("Tooltip Offset", &AUR::Engine::tooltipOffset, -50, 50);
        UI::SetItemTooltip("Tooltip");
        
        UI::SliderFloat("Hover Delay", &AUR::Engine::hoverDelay, 0.0f, 2.0f, "%.3f");
        UI::SetItemTooltip("Delay");
        
        UI::Combo("Color Button Position", (int*)&AUR::Engine::colorButtonPosition, "Left\0Right\0");
        UI::SliderFloat("Color Marker Size", &AUR::Engine::colorMarkerSize, 0.0f, 8.0f, "%.0f");
        
        UI::Checkbox("Anti-Aliased lines", &AUR::Engine::antiAliasedLines);
        UI::SetItemTooltip("When disabling anti-aliasing lines, you'll probably want to disable borders as well.");
        
        UI::Checkbox("Anti-Aliased lines use texture", &AUR::Engine::antiAliasedLinesUseTex);
        UI::SetItemTooltip("Faster lines using texture data. Require backend to render with bilinear filtering (not point/nearest filtering).");
        
        UI::Checkbox("Anti-Aliased fill", &AUR::Engine::antiAliasedFill);
    }
    if (engineHeaderOpen != -1) UI::SetNextItemOpen(engineHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("Editor", uiTreeFlags_DefaultOpen)) {
        if (UI::Combo("Themes", (int*)&aur.currentTheme, "Dark\0Light\0Classic")) switchTheme(aur.currentTheme);
        UI::Combo("Viewport Panel Location", (int*)&AUR::Editor::viewportPanelLocation, "Left\0Right\0");
    }
    engineHeaderOpen = -1;
    UI::End();
}