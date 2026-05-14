#include "config.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void say(const std::string& words, int error, bool refresh) {
    if (refresh)
        std::cout << "\r\033[K";

    // if (error == -1)
        // nothing is shown;
    if (error == 0)
        std::cout << "[DEBUG] ";
    if (error == 1) 
        std::cout << "[WATCH] ";
    if (error == 2) 
        std::cout << "[WARNING] ";
    if (error == 3) 
        std::cout << "[FATAL] ";
    
    std::cout << words;
    
    if (refresh)
        std::cout << std::flush;
    else
        std::cout << "\n";
};