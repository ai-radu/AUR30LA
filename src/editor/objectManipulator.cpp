#include <iostream>
#include "aur.h"

void objectManipulator() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Object Manipulator", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();

    UI::End();
}