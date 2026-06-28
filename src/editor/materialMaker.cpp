#include <iostream>
#include "aur.h"

void materialMaker() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Material Maker", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();

    UI::End();
}