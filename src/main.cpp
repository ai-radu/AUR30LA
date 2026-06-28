#include "imgui_internal.h"

#include "aur.h"
#include "project.h"
#include "soundOrganizer.h"
// ?
bool mainInit  = true;
bool dock      = true;
bool bSave     = false;
bool bLoad     = false;
bool askExit   = false;
bool askExport = false;
// position, color, texture coord
float vertices[] = {
    -0.5f, 0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,   1.0f, 1.0f, 1.0f,   5.0f, 0.0f,
     0.0f, 1.0f,  0.0f,   1.0f, 1.0f, 1.0f,   2.5f, 5.0f,
};
unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};
std::vector<std::string> split(std::string line, std::string delimiter){
    std::vector<std::string> splitLine;
    size_t pos = 0;
    std::string token;
    while((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        splitLine.emplace_back(token);
        line.erase(0, pos + delimiter.size());}
    splitLine.emplace_back(line);
    return splitLine;
}
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
// TODO booleans ?
void save() {
    bSave = true;
    saveEngine();
    saveProject();
}
void load() {
    bLoad = true;
    if(std::filesystem::exists(aur.saveData)) { loadEngine(); switchTheme(aur.currentTheme); }
    else saveEngine();
    if(std::filesystem::exists(aur.saveData)) loadProject();
    else saveProject();
}
int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    say("AUR30LA\nstart | " + aur.currentDateTime());
    createDirectories();
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    // texture
    Texture baseT("../assets/texture/base_T.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    baseT.texUnit(shaderProgram, "tex0", 0);
    Camera(aur.windowWidth, aur.windowHeight, glm::vec3(0.0f, 0.5f, 2.0f));
    // imgui
    IMGUI_CHECKVERSION();
    UI::CreateContext();
    uiIO& io = UI::GetIO();
    io.ConfigFlags |= uiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= uiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= uiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(aur.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // don't move it
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
        
        Inputs(aur.window);
        Matrix(camera.fov, 0.01f, 1000.0f, shaderProgram, "camMatrix");
        baseT.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // say(std::to_string(framebufferTexture), true);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        UI::NewFrame();
        // exit
        if(UI::IsKeyReleased(uiKey_Escape) && !askExit) {
            #if (AUR_DEVELOPER)
            save();
            glfwSetWindowShouldClose(aur.window, true);
            #else
            askExit = true;
            #endif
        };
        if (!bSave) {
            if (io.KeyCtrl && UI::IsKeyPressed(uiKey_S)) {
                if (io.KeyShift) { save(); /*save all*/} else { save(); }
            };
        };
        if (UI::IsKeyReleased(uiKey_S)) bSave = false;
        if (!bLoad) {
            if (io.KeyCtrl && UI::IsKeyPressed(uiKey_D)) {
                if (io.KeyShift) { load(); /*load all*/} else { load(); }
            };
        };
        if (UI::IsKeyReleased(uiKey_D)) bLoad = false;
        
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
        UI::SetNextWindowSize(
            vec2(viewport->WorkSize.x, viewport->WorkSize.y - UI::GetFrameHeight()));
        UI::SetNextWindowViewport(viewport->ID);
        UI::PushStyleVar(uiStyleVar_WindowRounding,   0.0f);
        UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
        UI::PushStyleVar(uiStyleVar_WindowPadding,    vec2(0,0));
        UI::Begin("DockSpace", nullptr,
            uiWindowFlags_NoTitleBar |
            uiWindowFlags_NoCollapse |
            uiWindowFlags_NoResize |
            uiWindowFlags_NoMove |
            uiWindowFlags_NoBringToFrontOnFocus |
            uiWindowFlags_NoNavFocus |
            uiWindowFlags_NoDocking);
        uiWindowFlags window_flags =
            uiWindowFlags_NoDocking |
            uiWindowFlags_NoTitleBar |
            uiWindowFlags_NoResize |
            uiWindowFlags_NoMove |
            uiWindowFlags_NoScrollbar |
            uiWindowFlags_NoSavedSettings |
            uiWindowFlags_MenuBar;
        UI::SetNextWindowPos (vec2(viewport->WorkPos.x, viewport->WorkPos.y + viewport->WorkSize.y - UI::GetFrameHeight()));
        UI::SetNextWindowSize(vec2(viewport->WorkSize.x, UI::GetFrameHeight()));
        if (UI::Begin("##BottomMenuBar", nullptr, window_flags)) {
            if (UI::BeginMenuBar()) {
                UI::PopStyleVar(3);
                if (UI::BeginMenu("File")) {
                    UI::BarrierText("Favorites");
                    if (UI::Combo("Themes", (int*)&aur.currentTheme, "Dark\0Light\0Classic")) switchTheme(aur.currentTheme);
                    UI::ColorEdit4("Color",         &aur.backgroundColor.x);
                    UI::Checkbox("Load at startup", &aur.autoLoad);
                    UI::Checkbox("Save when exit",  &aur.autoSave);
                    // UI::BarrierText("Settings");
                    // if (UI::MenuItem("Project", nullptr, showProject)) showProject = !showProject;
                    // if (UI::MenuItem("Editor",  nullptr, showEditor))  showEditor  = !showEditor;
                    // if (UI::MenuItem("Engine",  nullptr, showEngine))  showEngine  = !showEngine;
                    UI::BarrierText("Edit");
                    // if (UI::MenuItem("Undo", "Ctrl+Z"));
                    // if (UI::MenuItem("Redo", "Ctrl+Y"));
                    if (UI::MenuItem("Save", "Ctrl+S"))           save();
                    // if (UI::MenuItem("Save All", "Ctrl+Shift+S")) save();
                    if (UI::MenuItem("Load", "Ctrl+D"))           load();
                    // if (UI::MenuItem("Load All", "Ctrl+Shift+D")) load();
                    UI::Barrier();
                    if (UI::MenuItem("Exit", "Alt+F4")) askExit = true;
                    UI::EndMenu();
                }
                if (UI::BeginMenu("Others")) {
                    urlButton("AUR30LA",    "https://github.com/ai-radu/AUR30LA");
                    urlButton("ai.radu",    "https://linktr.ee/ai.radu");
                    UI::Barrier();
                    urlButton("Assimp",     "https://github.com/assimp/assimp");
                    urlButton("Dear ImGui", "https://github.com/ocornut/imgui");
                    urlButton("Glad",       "https://github.com/Dav1dde/glad");
                    urlButton("GLFW",       "https://github.com/glfw/glfw");
                    urlButton("GLM",        "https://github.com/g-truc/glm");
                    urlButton("Khronos",    "https://www.khronos.org/");
                    urlButton("miniaudio",  "https://github.com/mackron/miniaudio");
                    urlButton("OpenGL",     "https://www.opengl.org/");
                    urlButton("stb",        "https://github.com/nothings/stb");
                    UI::EndMenu();
                }
                UI::Text("| %s", aur.currentDateTime().c_str());
                UI::Text("| Avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                UI::EndMenuBar();
            };
            UI::End();
        }
        if (dock) {
            dock = false;
            uiID dockspace_id = UI::GetID("MainDockSpace");
            UI::DockBuilderRemoveNode(dockspace_id);
            UI::DockBuilderAddNode(dockspace_id, uiDockFlags_DockSpace);
            UI::DockBuilderSetNodeSize(dockspace_id, UI::GetMainViewport()->Size);
            // FIXME
            uiID main, second;
            second = UI::DockBuilderSplitNode(dockspace_id, Var::Dir::Left, 0.25f, nullptr, &main);
            uiDockNode* node = UI::DockBuilderGetNode(second);
            if (node) node->LocalFlags |= uiDockFlags_NoTabBar;
            
            UI::DockBuilderDockWindow("Engine Settings",    main);
            UI::DockBuilderDockWindow("Project Settings",   main);
            
            UI::DockBuilderDockWindow("Sound Organizer",    main);
            UI::DockBuilderDockWindow("Object Manipulator", main);
            UI::DockBuilderDockWindow("Material Maker",     main);
            UI::DockBuilderDockWindow("Viewport",           main);
            UI::DockBuilderFinish(dockspace_id);
        }
        uiID dock_id = UI::GetID("MainDockSpace");
        UI::DockSpace(dock_id, vec2(0,0), uiDockFlags_NoUndocking | uiDockFlags_NoResize | uiDockFlags_PassthruCentralNode );
        UI::End();
        
        engineSettings();
        projectSettings();
        
        soundOrganizer();
        objectManipulator();
        materialMaker();
        viewportEditor(aur.framebufferTexture);
        
        if (askExit) UI::OpenPopup("Are you sure ?");
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, vec2(0.5f, 0.5f));
        if (UI::BeginPopupModal("Are you sure ?", NULL, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
            // UI::Checkbox("Don't ask again", &aur.showExit);
            if (UI::Button("Save then Exit", vec2(120, 0))) {
                saveEngine();
                saveProject();
                glfwSetWindowShouldClose(aur.window, true);
            }
            UI::SetItemDefaultFocus();
            UI::SameLine();
            if (UI::Button("Exit",   vec2(120, 0))) glfwSetWindowShouldClose(aur.window, true);
            UI::SameLine();
            if (UI::Button("Cancel", vec2(120, 0))) { askExit = false; UI::CloseCurrentPopup(); };
            UI::EndPopup();
        }
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, vec2(0.5f, 0.5f));
        if (UI::BeginPopupModal("w", NULL, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
            // UI::Text("Row %s Channel %s", trk.currentRow + 1, trk.currentChannel + 1);
            if (UI::Button("Save then Exit", vec2(120, 0))) {
                glfwSetWindowShouldClose(aur.window, true);
            }
            UI::SetItemDefaultFocus();
            UI::SameLine();
            if (UI::Button("Cancel", vec2(120, 0))) UI::CloseCurrentPopup();
            UI::EndPopup();
        }
        UI::End();
        #if AUR_DEVELOPER
        UI::ShowDemoWindow();
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
    say("stop  | " + aur.currentDateTime() + "\ntimer |           " + formatElapsed(elapsed));
    return 0;
}