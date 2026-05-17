#pragma once
#include <string>

void say(const std::string& words, int type = 0, bool stay = false);

struct Engine {
    std::string currentVer = "AUR30LA Engine Pre-Alpha v0.3.1.2.4";
    bool askExit;
    bool askExport;
};
extern Engine aur;