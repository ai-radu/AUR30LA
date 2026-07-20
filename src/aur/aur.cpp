#include "aur.hpp"
AUR aur;
void Marker(cc8* text, c1 attention) {
    UI::SameLine();
    if (attention) UI::TextDisabled("(!)");
    else UI::TextDisabled("(?)");
    if (UI::BeginItemTooltip()) {
        UI::PushTextWrapPos(UI::GetFontSize() * 35.0f);
        UI::TextUnformatted(text);
        UI::PopTextWrapPos();
        UI::EndTooltip();
    }
}
void tellme(const std::string& words, c1 stay) {
    if (stay) std::cout << "\r\033[K";
    std::cout << words;
    if (stay) std::cout << std::flush;
    else std::cout << "\n";
}
template<typename T>
void showme(T) {
    std::cout << "has_unique_object_representations_v: " <<std::has_unique_object_representations_v<T> << '\n';
    std::cout << "                             sizeof: " << sizeof(T) << '\n';
    std::cout << "                     alignment_of_v: " << std::alignment_of_v<T> << '\n';
    std::cout << "                        is_signed_v: " << std::is_signed_v<T> << '\n';
    std::cout << "                      is_unsigned_v: " << std::is_unsigned_v<T> << '\n';
    std::cout << "                      is_integral_v: " << std::is_integral_v<T> << '\n';
    std::cout << "                is_floating_point_v: " << std::is_floating_point_v<T> << '\n';
    std::cout << "                          is_enum_v: " << std::is_enum_v<T> << '\n';
    std::cout << "                       is_pointer_v: " << std::is_pointer_v<T> << '\n';
    std::cout << "                         is_array_v: " << std::is_array_v<T> << '\n';
    std::cout << "                         is_class_v: " << std::is_class_v<T> << '\n';
    std::cout << "                         is_const_v: " << std::is_const_v<T> << '\n';
    std::cout << "                      is_volatile_v: " << std::is_volatile_v<T> << '\n';
    std::cout << "                       is_trivial_v: " << std::is_trivial_v<T> << '\n';
    std::cout << "            is_trivially_copyable_v: " << std::is_trivially_copyable_v<T> << '\n';
    std::cout << "               is_standard_layout_v: " << std::is_standard_layout_v<T> << '\n';
    std::cout << "         is_default_constructible_v: " << std::is_default_constructible_v<T> << '\n';
    std::cout << "              is_copy_constructible: " << std::is_copy_constructible_v<T> << '\n';
    std::cout << "              is_move_constructible: " << std::is_move_constructible_v<T> << '\n';
    std::cout << "                  is_destructible_v: " << std::is_destructible_v<T> << '\n';
    std::cout << "                 numeric_limits_min: " << std::numeric_limits<T>::min() << '\n';
    std::cout << "                 numeric_limits_max: " << std::numeric_limits<T>::max() << '\n';
    std::cout << "              numeric_limits_lowest: " << std::numeric_limits<T>::lowest() << '\n';
    std::cout << "              numeric_limits_digits: " << std::numeric_limits<T>::digits << '\n';
    std::cout << "            numeric_limits_digits10: " << std::numeric_limits<T>::digits10 << '\n';
    std::cout << "         numeric_limits_is_interger: " << std::numeric_limits<T>::is_integer << '\n';
    std::cout << "           numeric_limits_is_signed: " << std::numeric_limits<T>::is_signed << '\n';
    std::cout << "            numeric_limits_is_exact: " << std::numeric_limits<T>::is_exact << '\n';
    std::cout << "             numeric_limits_epsilon: " << std::numeric_limits<T>::epsilon() << '\n';
    std::cout << "            numeric_limits_infinity: " << std::numeric_limits<T>::infinity() << '\n';
    std::cout << "           numeric_limits_quiet_NaN: " << std::numeric_limits<T>::quiet_NaN() << '\n';
    std::cout << "           has_virtual_destructor_v: " << std::has_virtual_destructor_v<T> << '\n';
    std::cout << "                   is_polymorphic_v: " << std::is_polymorphic_v<T> << '\n';
    std::cout << "                      is_abstract_v: " << std::is_abstract_v<T> << '\n';
    std::cout << "                         is_empty_v: " << std::is_empty_v<T> << '\n';
    std::cout << "                         is_final_v: " << std::is_final_v<T> << '\n';
}
void asBytes(std::ofstream &file, c32 value, c32 byte_size) { // keep ?
    file.write(reinterpret_cast<cc8*>(&value), byte_size);
}
void urlButton(cc8* label, cc8* url) {
    UI::TextLinkOpenURL(label, url);
    if (UI::IsItemHovered()) UI::SetTooltip("Open '%s'", url);
}
void CreateDirectories() { // easier than everywhere, i guess
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
    if (!aur.window) { tellme("[ERROR] aur.cpp > !window"); glfwTerminate(); return; }
    glfwMakeContextCurrent(aur.window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(aur.window, framebuffer_size_callback);
    glfwShowWindow     (aur.window);
    glfwMaximizeWindow (aur.window);
    glfwSetInputMode   (aur.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { tellme("[ERROR] aur.cpp > !gladLoadGLLoader"); glfwTerminate(); return; }
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
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) tellme("[ERROR] aur.cpp > !GL_FRAMEBUFFER_COMPLETE");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void framebuffer_size_callback(GLFWwindow* window, c32 width, c32 height) {
    aur.viewportWidth = width;
    aur.viewportHeight = height;
    glViewport(0, 0, width, height);
}
void SwitchTheme (enum AUR::Theme theme) {
    switch (theme) {
    case AUR::Theme::Dark: UI::StyleColorsDark(); break;
    case AUR::Theme::Light: UI::StyleColorsLight(); break;
    case AUR::Theme::Classic: UI::StyleColorsClassic(); break;
    }
}
void SaveEngine() {
    nlohmann::json aurData;
    
    aurData["settings"]["tooltipOffset"] = AUR::Settings::tooltipOffset;

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
    
    aurData["theme"]                 = static_cast<c32>(aur.currentTheme);

    std::ofstream file(aur.saveData);
    if (!file.is_open()) { tellme("[WARNING] aur.cpp > saveAurData() ? !file.is_open"); return; }
    file << aurData.dump(4);
    file.close();
    if (AUR::Editor::terminalNOTIF) tellme("[NOTIF] aur.cpp > saveEngine()");
}
void LoadEngine() {
    std::ifstream file(aur.saveData);
    if (!file.is_open()) { tellme("[WARNING] aur.cpp > loadAurData() ? !file.is_open"); return; }
    nlohmann::json aurData;
    file >> aurData;

    AUR::Settings::tooltipOffset = aurData["settings"]["tooltipOffset"];

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
    
    if (AUR::Editor::terminalNOTIF) tellme("[NOTIF] aur.cpp > loadAurData()");
}