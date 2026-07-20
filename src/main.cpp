#include "imgui_internal.h"

#include "aur.hpp"
#include "project.hpp"
// ?
c1 mainInit  = true;
c1 dockInit  = true;
c1 bSave     = false;
c1 bLoad     = false;
c1 askExit   = false;
c1 askExport = false;
// position, color, texture coord
f32 vertices[] = {
    -0.5f, 0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,   1.0f, 1.0f, 1.0f,   5.0f, 0.0f,
     0.0f, 1.0f,  0.0f,   1.0f, 1.0f, 1.0f,   2.5f, 5.0f,
};
u32 indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};
std::string formatElapsed(long long ms) {
    long long total_seconds = ms / 1000;
    long long days = total_seconds / (24 * 3600);
    long long hours = (total_seconds % (24 * 3600)) / 3600;
    long long minutes = (total_seconds % 3600) / 60;
    long long seconds = total_seconds % 60;
    char buf[64];
    snprintf(buf, sizeof(buf), "%02lld:%02lld:%02lld:%02lld", days, hours, minutes, seconds);
    return std::string(buf);
}
// TODO ?
void save() {
    bSave = true;
    SaveEngine();
    SaveProject();
}
void load() {
    bLoad = true;
    if(std::filesystem::exists(aur.saveData)) { LoadEngine(); SwitchTheme(aur.currentTheme); }
    else SaveEngine();
    if(std::filesystem::exists(aur.saveData)) LoadProject();
    else SaveProject();
}
struct PasswordOptions {
    c32 length    = 16;
    c1  uppercase = true;
    c1  lowercase = true;
    c1  numbers   = true;
    c1  symbols   = true;
};
static PasswordOptions passwordOptions;
static std::string generatedPassword;
std::string generatePassword(const PasswordOptions& po) {
    static const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    static const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string numbers   = "0123456789";
    static const std::string symbols   = "!@#$%^&*()-_=+[]{}<>?";
    std::string chars;
    if (po.uppercase) chars += uppercase;
    if (po.lowercase) chars += lowercase;
    if (po.numbers)   chars += numbers;
    if (po.symbols)   chars += symbols;
    if (chars.empty()) return "no";
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, chars.size() -1);
    std::string password;
    password.reserve(po.length);
    for (c32 i = 0; i < po.length; ++i) password += chars[dist(rng)];
    return password;
};
/* ?
static std::string randomNumber;
cc8* numberTypeNames[] = {
    "char           (c8)",
    "signed char    (s8)",
    "unsigned char  (u8)",
    "short          (c16)",
    "signed short   (s16)",
    "unsigned short (u16)",
    "signed int     (s32)",
    "unsigned int   (u32)",
    "float          (f32)",
    "signed long    (s64)",
    "unsigned long  (u64)",
    "double         (f64)",
    "long double    (f80)",
};
struct genericNumber {
    int type = 0;
    signed char        s8_v  = 0, s8_min  = -128,        s8_max  = 127;
    unsigned char      u8_v  = 0, u8_min  = 0,           u8_max  = 255;
    signed short       s16_v = 0, s16_min = -32768,      s16_max = 32767;
    unsigned short     u16_v = 0, u16_min = 0,           u16_max = 65535;
    signed int         s32_v = 0, s32_min = INT_MIN/2,   s32_max = INT_MAX/2;
    unsigned int       u32_v = 0, u32_min = 0,           u32_max = UINT_MAX/2;
    signed long long   s64_v = 0, s64_min = LLONG_MIN/2, s64_max = LLONG_MAX/2;
    unsigned long long u64_v = 0, u64_min = 0,           u64_max = ULLONG_MAX/2;
    float              f32_v = 0, f32_min = -1e8f,       f32_max = 1e8f;
    double             f64_v = 0, f64_min = -1e12,       f64_max = 1e12;
};
genericNumber genNr;
static std::mt19937 rng(std::random_device{}());
std::string generateRandomNumber(int type) {
    switch (type) {
        case 0: return std::to_string(std::uniform_int_distribution<int>     (genNr.s8_min,  genNr.s8_max)(rng));
        case 1: return std::to_string(std::uniform_int_distribution<unsigned>(genNr.u8_min,  genNr.u8_max)(rng));
        case 2: return std::to_string(std::uniform_int_distribution<int>     (genNr.s16_min, genNr.s16_max)(rng));
        case 3: return std::to_string(std::uniform_int_distribution<unsigned>(genNr.u16_min, genNr.u16_max)(rng));
        case 4: return std::to_string(std::uniform_int_distribution<int>     (genNr.s32_min, genNr.s32_max)(rng));
        case 5: return std::to_string(std::uniform_int_distribution<unsigned>(genNr.u32_min, genNr.u32_max)(rng));
        case 6: return std::to_string(std::uniform_int_distribution<long long>(genNr.s64_min, genNr.s64_max)(rng));
        case 7: return std::to_string(std::uniform_int_distribution<unsigned long long>(genNr.u64_min, genNr.u64_max)(rng));
        case 8: return std::to_string(std::uniform_real_distribution<float>  (genNr.f32_min, genNr.f32_max)(rng));
        case 9: return std::to_string(std::uniform_real_distribution<double> (genNr.f64_min, genNr.f64_max)(rng));
    }
    return "0";
};
void RandomNumberGenerator() {
    if (UI::BeginMenu("Random Number Generator")) {
        char ranNr[129] = {};
        std::strncpy(ranNr, randomNumber.c_str(), sizeof(ranNr) - 1);
        // ranNr[sizeof(ranNr) - 1] = '\0';
        UI::InputText("Output##RNG", 0, ranNr, sizeof(ranNr), uiInputTextFlags_ReadOnly);
        if (UI::Selectable("Generate", false, uiSelectFlags_NoAutoClosePopups))
            randomNumber = generateRandomNumber(genNr.type);
        if (UI::Selectable("Copy to clipboard", false, uiSelectFlags_NoAutoClosePopups) &&
            !randomNumber.empty()) UI::SetClipboardText(randomNumber.c_str());
        UI::Combo("Type", &genNr.type, numberTypeNames, 10, 0, 10);
        void* rngMin = nullptr;
        void* rngMax = nullptr;
        uiDataType rngDt = dataType_s8;
        switch (genNr.type) {
            case 0: rngDt = dataType_s8;  rngMin = &genNr.s8_min;  rngMax = &genNr.s8_max;  break;
            case 1: rngDt = dataType_u8;  rngMin = &genNr.u8_min;  rngMax = &genNr.u8_max;  break;
            case 2: rngDt = dataType_s16; rngMin = &genNr.s16_min; rngMax = &genNr.s16_max; break;
            case 3: rngDt = dataType_u16; rngMin = &genNr.u16_min; rngMax = &genNr.u16_max; break;
            case 4: rngDt = dataType_s32; rngMin = &genNr.s32_min; rngMax = &genNr.s32_max; break;
            case 5: rngDt = dataType_u32; rngMin = &genNr.u32_min; rngMax = &genNr.u32_max; break;
            case 6: rngDt = dataType_s64; rngMin = &genNr.s64_min; rngMax = &genNr.s64_max; break;
            case 7: rngDt = dataType_u64; rngMin = &genNr.u64_min; rngMax = &genNr.u64_max; break;
            case 8: rngDt = dataType_f32; rngMin = &genNr.f32_min; rngMax = &genNr.f32_max; break;
            case 9: rngDt = dataType_f64; rngMin = &genNr.f64_min; rngMax = &genNr.f64_max; break;
        }
        UI::SliderScalar("Min", rngDt, rngMin, rngMin, rngMax);
        UI::SliderScalar("Max", rngDt, rngMax, rngMin, rngMax);
        UI::EndMenu();
    }
};
*/
int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    tellme("AUR30LA Engine\nstart > " + aur.currentDateTime());
    CreateDirectories();
    initGLFW();
    initOpenGL();
    // the rest
    // g_Audio.start();
    initAudio();
    Shader shaderProgram("../src/aur/view/default.vert", "../src/aur/view/default.frag");
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices,  sizeof(indices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(f32), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(f32), (void*)(3 * sizeof(f32)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    // texture
    Texture baseT("../assets/texture/base_T.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    baseT.texUnit(shaderProgram, "tex0", 0);
    Camera(aur.windowWidth, aur.windowHeight, glm::vec3(0.0f, 0.5f, 2.0f));
    // imgui
    UI::CreateContext();
    uiIO& io = UI::GetIO();
    io.ConfigFlags |= uiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= uiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= uiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(aur.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // don't move it ?
    if (aur.autoLoad) load();
    // main loop
    while (!glfwWindowShouldClose(aur.window)) {
        glfwPollEvents();
        aur.currentFrame = glfwGetTime();
        aur.deltaTime = aur.currentFrame - aur.lastFrame;
        aur.lastFrame = aur.currentFrame;
        
        glBindFramebuffer(GL_FRAMEBUFFER, aur.frameBuffer);
        
        glViewport(0, 0, aur.windowWidth, aur.windowHeight);
        glEnable(GL_DEPTH_TEST);
        
        glClearColor(aur.backgroundColor.x, aur.backgroundColor.y, aur.backgroundColor.z, aur.backgroundColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderProgram.Activate();
        
        Matrix(camera.fov, 0.01f, 1000.0f, shaderProgram, "camMatrix");
        baseT.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(c32), GL_UNSIGNED_INT, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // tellme(std::to_string(framebufferTexture), true);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        UI::NewFrame();
        // exit
        if(UI::IsKeyReleased(INPUT::Key_Escape) && !askExit) {
            #if (AUR_DEVELOPER)
            save();
            glfwSetWindowShouldClose(aur.window, true);
            #else
            askExit = true;
            #endif
        };
        if (!bSave) {
            if (io.KeyCtrl && UI::IsKeyPressed(INPUT::Key_S)) {
                if (io.KeyShift) { save(); /*save all*/}
                else { save(); }
            };
        };
        if (UI::IsKeyReleased(INPUT::Key_S)) bSave = false;
        if (!bLoad) {
            if (io.KeyCtrl && UI::IsKeyPressed(INPUT::Key_D)) {
                if (io.KeyShift) { load(); /*load all*/}
                else { load(); }
            };
        };
        if (UI::IsKeyReleased(INPUT::Key_D)) bLoad = false;
        // if (UI::IsKeyPressed(uiKey_S)) {
            // std::ofstream out("engine.aur", std::ios::binary); // write
            // aurWrite(out, bLoad);
            // std::cout << "open: " << out.is_open() << "\n";
        // };
        // if (UI::IsKeyPressed(uiKey_D)) {
            // std::ifstream in("engine.aur", std::ios::binary); // load
            // aurRead(in, bLoad);
        // };

        // dock
        const uiViewport* viewport = UI::GetMainViewport();
        UI::SetNextWindowPos(viewport->WorkPos);
        UI::SetNextWindowSize(v2(viewport->WorkSize.x, viewport->WorkSize.y - UI::GetFrameHeight()));
        UI::SetNextWindowViewport(viewport->ID);
        UI::PushStyleVar(uiStyleVar_WindowRounding,   0.0f);
        UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
        UI::PushStyleVar(uiStyleVar_WindowPadding,    v2(0,0));
        UI::Begin("DockSpace", nullptr,
            uiWindowFlags_NoTitleBar |
            uiWindowFlags_NoCollapse |
            uiWindowFlags_NoResize |
            uiWindowFlags_NoMove |
            uiWindowFlags_NoBringToFrontOnFocus |
            uiWindowFlags_NoNavFocus |
            uiWindowFlags_NoDocking);
        UI::SetNextWindowPos (v2(viewport->WorkPos.x,  viewport->WorkPos.y + viewport->WorkSize.y - UI::GetFrameHeight()));
        UI::SetNextWindowSize(v2(viewport->WorkSize.x, UI::GetFrameHeight()));
        if (UI::Begin("##BottomMenuBar", nullptr,
            uiWindowFlags_NoDocking |
            uiWindowFlags_NoTitleBar |
            uiWindowFlags_NoResize |
            uiWindowFlags_NoMove |
            uiWindowFlags_NoScrollbar |
            uiWindowFlags_NoSavedSettings |
            uiWindowFlags_MenuBar)) {
            if (UI::BeginMenuBar()) {
                UI::PopStyleVar(3);
                if (UI::BeginMenu("File")) {
                    UI::SeparatorText("Favorites");
                    if (UI::Combo("Themes", (int*)&aur.currentTheme, "Dark\0Light\0Classic")) SwitchTheme(aur.currentTheme);
                    UI::ColorEdit4("Color",         &aur.backgroundColor.x);
                    UI::Checkbox("Load at startup", &aur.autoLoad);
                    UI::Checkbox("Save when exit",  &aur.autoSave);
                    UI::SeparatorText("Edit");
                    // if (UI::MenuItem("Help", "Ctrl+Shift+H")) { popup = !popup; if (popup) UI::OpenPopup("Help"); };
                    // if (UI::MenuItem("Undo", "Ctrl+Z"));
                    // if (UI::MenuItem("Redo", "Ctrl+Y"));
                    if (UI::MenuItem("Save", "Ctrl+S"))           save();
                    // if (UI::MenuItem("Save All", "Ctrl+Shift+S")) save();
                    if (UI::MenuItem("Load", "Ctrl+D"))           load();
                    // if (UI::MenuItem("Load All", "Ctrl+Shift+D")) load();
                    UI::Separator();
                    if (UI::MenuItem("Exit", "Alt+F4")) askExit = true;
                    UI::EndMenu();
                }
                if (UI::BeginMenu("Others")) {
                    urlButton("AUR30LA",    "https://github.com/ai-radu/AUR30LA");
                    urlButton("ai.radu",    "https://linktr.ee/ai.radu");
                    UI::Separator();
                    urlButton("Assimp",     "https://github.com/assimp/assimp");
                    urlButton("Dear ImGui", "https://github.com/ocornut/imgui");
                    urlButton("Glad",       "https://github.com/Dav1dde/glad");
                    urlButton("GLFW",       "https://github.com/glfw/glfw");
                    urlButton("GLM",        "https://github.com/g-truc/glm");
                    urlButton("Khronos",    "https://www.khronos.org/");
                    urlButton("miniaudio",  "https://github.com/mackron/miniaudio");
                    urlButton("OpenGL",     "https://www.opengl.org/");
                    urlButton("stb",        "https://github.com/nothings/stb");
                    UI::Separator();
                    UI::Text("Ctrl+Shift+H: Help On/Off");
                    // RandomNumberGenerator();
                    if (UI::BeginMenu("Password Generator")) {
                        char password[129] = {};
                        std::strncpy(password, generatedPassword.c_str(), sizeof(password) - 1);
                        password[sizeof(password) - 1] = '\0';
                        UI::InputText("Output##PG", 0, password, sizeof(password));
                        UI::SliderInt("Length##PG", &passwordOptions.length, 4, 128);
                        if (UI::Selectable("Generate", false, uiSelectFlags_NoAutoClosePopups))
                            generatedPassword = generatePassword(passwordOptions);
                        if (UI::Selectable("Copy to clipboard", false, uiSelectFlags_NoAutoClosePopups) &&
                            !generatedPassword.empty()) UI::SetClipboardText(generatedPassword.c_str());
                        UI::Checkbox("a", &passwordOptions.uppercase);
                        UI::SameLine();
                        UI::Checkbox("A", &passwordOptions.lowercase);
                        UI::SameLine();
                        UI::Checkbox("1", &passwordOptions.numbers);
                        UI::SameLine();
                        UI::Checkbox("@", &passwordOptions.symbols);
                        UI::EndMenu();
                    }
                    UI::EndMenu();
                }
                UI::Text("| %s", aur.currentDateTime().c_str());
                UI::Text("| Avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, (double)io.Framerate);
                UI::EndMenuBar();
            };
            UI::End();
        }
        if (dockInit) {
            dockInit = false;
            uiID dockspace_id = UI::GetID("MainDockSpace");
            UI::DockBuilderRemoveNode(dockspace_id);
            UI::DockBuilderAddNode(dockspace_id, uiDockFlags_DockSpace);
            UI::DockBuilderSetNodeSize(dockspace_id, UI::GetMainViewport()->Size);
            // FIXME
            uiID main, second;
            second = UI::DockBuilderSplitNode(dockspace_id, VAR::Dir_Left, 0.25f, nullptr, &main);
            uiDockNode* node = UI::DockBuilderGetNode(second);
            if (node) node->LocalFlags |= uiDockFlags_NoTabBar;
            
            UI::DockBuilderDockWindow("Settings",           main);
            UI::DockBuilderDockWindow("Project Settings",   main);
            
            UI::DockBuilderDockWindow("Sound Organizer",    main);
            UI::DockBuilderDockWindow("Object Manipulator", main);
            UI::DockBuilderDockWindow("Material Maker",     main);
            UI::DockBuilderDockWindow("Viewport",           main);
            UI::DockBuilderFinish(dockspace_id);
        }
        uiID dock_id = UI::GetID("MainDockSpace");
        UI::DockSpace(dock_id, v2(0,0), uiDockFlags_NoUndocking | uiDockFlags_NoResize | uiDockFlags_PassthruCentralNode );
        UI::End();
        
        Settings();
        SoundOrganizer();
        ObjectManipulator();
        MaterialMaker();
        ViewportEditor(aur.window, aur.framebufferTexture);
        
        if (askExit) UI::OpenPopup("Are you sure ?");
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, v2(0.5f, 0.5f));
        if (UI::BeginPopupModal("Are you sure ?", NULL, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
            // UI::Checkbox("Don't ask again", &aur.showExit);
            if (UI::Button("Save then Exit", v2(120, 0))) {
                SaveEngine();
                SaveProject();
                glfwSetWindowShouldClose(aur.window, true);
            }
            UI::SetItemDefaultFocus();
            UI::SameLine();
            if (UI::Button("Exit",   v2(120, 0))) glfwSetWindowShouldClose(aur.window, true);
            UI::SameLine();
            if (UI::Button("Cancel", v2(120, 0))) { askExit = false; UI::CloseCurrentPopup(); };
            UI::EndPopup();
        }
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, v2(0.5f, 0.5f));
        if (UI::BeginPopupModal("w", NULL, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
            // UI::Text("Row %s Channel %s", trk.currentRow + 1, trk.currentChannel + 1);
            if (UI::Button("Save then Exit", v2(120, 0))) {
                glfwSetWindowShouldClose(aur.window, true);
            }
            UI::SetItemDefaultFocus();
            UI::SameLine();
            if (UI::Button("Cancel", v2(120, 0))) UI::CloseCurrentPopup();
            UI::EndPopup();
        }
        UI::End();
        #if AUR_DEVELOPER
        // UI::ShowDemoWindow();
        // UI::ShowMetricsWindow();
        #endif
        // leave this here
        if(mainInit) {
            mainInit = false;
            UI::SetWindowFocus("Viewport");
            // add
        };
        UI::Render();
        ImGui_ImplOpenGL3_RenderDrawData(UI::GetDrawData());
        glfwSwapBuffers(aur.window);
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    baseT.Delete();
    shaderProgram.Delete();
    // in this order
    uninitAudio();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    UI::DestroyPlatformWindows();
    UI::DestroyContext();
    glfwDestroyWindow(aur.window);
    glfwTerminate();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    tellme("stop  > " + aur.currentDateTime() + "\ntimer > " + formatElapsed(elapsed));
    return 0;
}