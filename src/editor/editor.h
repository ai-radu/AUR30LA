#pragma once
#include "aur.h"

struct EDITOR {
    std::string saveData = "../save/editor.json";
    enum currentWindow {
        Viewport,
        Material,
        Object,
        Sound,
        Project,
        Editor,
        // Engine,
        Industrial
    };
    currentWindow windowID;
};
extern EDITOR editor;

void saveEditorData();
void loadEditorData();
void urlButton(const char* label, const char* url);

void multiWindow(EDITOR::currentWindow i);
// windows
void viewportEditor(unsigned int texture);
void materialMaker();
void objectManipulator();
void soundOrganizer();
void projectSettings();
void editorSettings();
void engineSettings();
void industrialSettings();
// panels
void viewportPanel();
void materialPanel();
void objectPanel();
void soundPanel();
void projectPanel();
void editorPanel();
void enginePanel();
void industrialPanel();
