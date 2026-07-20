#include <iostream>
#include "aur.hpp"

void ObjectManipulator() {
    UI::Begin("Object Manipulator", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );

    UI::End();
}