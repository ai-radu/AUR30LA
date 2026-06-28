#include "aur.h"
AUR aur;
void say(const std::string& words, bool flush) {
    if (flush) std::cout << "\r\033[K";
    std::cout << words;
    if (flush) std::cout << std::flush;
    else std::cout << "\n";
}
void asBytes(std::ofstream &file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

void urlButton(const char* label, const char* url) {
    UI::TextLinkOpenURL(label, url);
    if (UI::IsItemHovered()) UI::SetTooltip("Open '%s'", url);
}
void createDirectories() { // easier than everywhere
    std::filesystem::create_directories("../assets/audio");
    std::filesystem::create_directories("../assets/audio/soundOrganizer");
    std::filesystem::create_directories("../assets/texture");
    std::filesystem::create_directories("../save");
}

void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    aur.window = glfwCreateWindow(aur.windowWidth, aur.windowHeight, "AUR30LA Engine", NULL, NULL);
    if (!aur.window) { say("[ERROR] aur.cpp > !window"); glfwTerminate(); return; }
    
    glfwMakeContextCurrent(aur.window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(aur.window, framebuffer_size_callback);
    
    glfwShowWindow     (aur.window);
    glfwMaximizeWindow (aur.window);
    glfwSetInputMode   (aur.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { say("[ERROR] aur.cpp > !gladLoadGLLoader"); glfwTerminate(); return; }
}
void initOpenGL() {
    glfwGetFramebufferSize(aur.window, &aur.viewportWidth, &aur.viewportHeight);
    glViewport(0, 0, aur.windowWidth, aur.windowHeight);
    
    glGenFramebuffers(1, &aur.frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, aur.frameBuffer);
    
    glGenTextures(1, &aur.framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, aur.framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, aur.windowWidth, aur.windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, aur.framebufferTexture, 0);
    
    glGenRenderbuffers(1, &aur.renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, aur.renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, aur.windowWidth, aur.windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, aur.renderBuffer);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) say("[ERROR] aur.cpp > !GL_FRAMEBUFFER_COMPLETE");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    aur.viewportWidth = width;
    aur.viewportHeight = height;
    glViewport(0, 0, width, height);
}
void switchTheme (enum AUR::Theme theme) {
    switch (theme)
    {
    case AUR::Theme::Dark: UI::StyleColorsDark(); break;
    case AUR::Theme::Light: UI::StyleColorsLight(); break;
    case AUR::Theme::Classic: UI::StyleColorsClassic(); break;
    }
}
void saveEngine() {
    nlohmann::json aurData;
    
    aurData["settings"]["tooltipOffset"] = AUR::Engine::tooltipOffset;

    aurData["color"]   = {
        aur.backgroundColor.x,
        aur.backgroundColor.y,
        aur.backgroundColor.z
    };

    aurData["data"]["autoSave"]    = aur.autoSave;
    aurData["data"]["autoLoad"]    = aur.autoLoad;
    
    aurData["snap"]["moveIndex"]   = AUR::Snap::MoveIndex;
    aurData["snap"]["rotateIndex"] = AUR::Snap::RotateIndex;
    aurData["snap"]["scaleIndex"]  = AUR::Snap::ScaleIndex;

    aurData["camera"]["fov"]       = camera.fov; 
    aurData["camera"]["location"]  = {
        camera.location.x,
        camera.location.y,
        camera.location.z
    };
    aurData["camera"]["rotation"]  = {
        camera.rotation.x,
        camera.rotation.y,
        camera.rotation.z
    };
    aurData["camera"]["sensitivity"] = camera.sensitivity;
    aurData["camera"]["speed"]       = camera.speed;
    
    aurData["theme"]                 = static_cast<int>(aur.currentTheme);

    std::ofstream file(aur.saveData);
    if (!file.is_open()) { say("[WARNING] aur.cpp > saveAurData() ? !file.is_open"); return; }
    file << aurData.dump(4);
    file.close();
    say("[NOTIF] aur.cpp > saveAurData()");
}
void loadEngine() {
    std::ifstream file(aur.saveData);
    if (!file.is_open()) { say("[WARNING] aur.cpp > loadAurData() ? !file.is_open"); return; }
    nlohmann::json aurData;
    file >> aurData;

    AUR::Engine::tooltipOffset = aurData["settings"]["tooltipOffset"];

    aur.backgroundColor.x  = aurData["color"][0];
    aur.backgroundColor.y  = aurData["color"][1];
    aur.backgroundColor.z  = aurData["color"][2];
    
    aur.autoSave           = aurData["data"]["autoSave"];
    aur.autoLoad           = aurData["data"]["autoLoad"];
    
    AUR::Snap::MoveIndex   = aurData["snap"]["moveIndex"];
    AUR::Snap::RotateIndex = aurData["snap"]["rotateIndex"];
    AUR::Snap::ScaleIndex  = aurData["snap"]["scaleIndex"];

    camera.fov             = aurData["camera"]["fov"];
    
    camera.location.x      = aurData["camera"]["location"][0];
    camera.location.y      = aurData["camera"]["location"][1];
    camera.location.z      = aurData["camera"]["location"][2];
  
    camera.rotation.x      = aurData["camera"]["rotation"][0];
    camera.rotation.y      = aurData["camera"]["rotation"][1];
    camera.rotation.z      = aurData["camera"]["rotation"][2];
 
    camera.sensitivity     = aurData["camera"]["sensitivity"];
    camera.speed           = aurData["camera"]["speed"];
    
    aur.currentTheme       = static_cast<AUR::Theme>(aurData["theme"]);
    
    say("[NOTIF] aur.cpp > loadAurData()");
}