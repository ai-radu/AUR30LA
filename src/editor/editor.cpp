#include "editor.h"
EDITOR editor;

void urlButton(const char* label, const char* url) {
    UI::TextLinkOpenURL(label, url);
    if (UI::IsItemHovered()) UI::SetTooltip("Open '%s'", url);
}
void multiWindow(EDITOR::currentWindow i) {
    UI::Begin("multiWindow");
    switch (i) {
        case EDITOR::currentWindow::Viewport: viewportPanel(); break;
        case EDITOR::currentWindow::Material: materialPanel(); break;
        case EDITOR::currentWindow::Object:   objectPanel();   break;
        case EDITOR::currentWindow::Sound:    soundPanel();    break;
        case EDITOR::currentWindow::Project:  projectPanel();  break;
        case EDITOR::currentWindow::Editor:   editorPanel();   break;
        default: viewportPanel(); break;
    }
        UI::End();
}
void saveEditorData() {
    // nlohmann::json editorData;
    
    // vars
    
    // std::ofstream file(editor.saveData);
    // if (!file.is_open()) { say("[WARNING] editor.cpp > saveEditorData() ? !file.is_open"); return; }
    // file << editorData.dump(4);
    // file.close();
    // say("[NOTIF] editor.cpp > saveEditorData()");
}
void loadEditorData() {
    // std::ifstream file(editor.saveData);
    // if (!file.is_open()) { say("[WARNING] editor.cpp > loadEditorData() ? !file.is_open"); return; }
    // nlohmann::json editorData;
    // file >> editorData;

    // vars

    // say("[NOTIF] editor.cpp > loadEditorData()");
}