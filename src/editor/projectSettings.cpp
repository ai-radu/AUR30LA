#include <iostream>
#include "aur.h"

void projectSettings() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Project Settings", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();
    
    UI::End();
}