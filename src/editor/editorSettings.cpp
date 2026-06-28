#include <iostream>
#include "editor.h"

void editorSettings() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Editor Settings", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();
    
    if (UI::IsWindowFocused(uiFocusFlags_RootAndChildWindows)) editor.windowID = EDITOR::currentWindow::Editor;

    UI::End();
}
void editorPanel() {
    UI::Text("editor");
    
}