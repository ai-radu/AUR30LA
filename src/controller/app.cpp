#include "app.h"
#include "../stb_image.h"

App::App() {
    set_up_glfw();
}

App::~App() {
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteTextures(textures.size(), textures.data());
    glDeleteProgram(shader);

    delete motionSystem;
    delete cameraSystem;
    delete renderSystem;
    
    glfwTerminate();
}

unsigned int App::make_entity() {
    return entity_count++;
}

unsigned int App::make_cube_mesh(glm::vec3 size) {
    float l = size.x;
    float w = size.y;
    float h = size.z;

    std::vector<float> vertices = {
        // Z-
         l,  w, -h, 1.0f, 1.0f,
         l, -w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l,  w, -h, 0.0f, 1.0f,
         l,  w, -h, 1.0f, 1.0f,

        // Z+
        -l, -w,  h, 0.0f, 0.0f,
         l, -w,  h, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f,
        -l,  w,  h, 0.0f, 1.0f,
        -l, -w,  h, 0.0f, 0.0f,

        -l,  w,  h, 1.0f, 1.0f,
        -l,  w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l,  w,  h, 1.0f, 1.0f,

         l, -w, -h, 0.0f, 0.0f,
         l,  w, -h, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f,
         l, -w,  h, 0.0f, 1.0f,
         l, -w, -h, 0.0f, 0.0f,

        -l, -w, -h, 0.0f, 0.0f,
         l, -w, -h, 1.0f, 0.0f,
         l, -w,  h, 1.0f, 1.0f,  
         l, -w,  h, 1.0f, 1.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l, -w, -h, 0.0f, 0.0f,

         l,  w,  h, 1.0f, 1.0f,
         l,  w, -h, 1.0f, 0.0f,
        -l,  w, -h, 0.0f, 0.0f, 
        -l,  w, -h, 0.0f, 0.0f,
        -l,  w,  h, 0.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
        vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int App::make_texture(const char* filename) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

	// make texture
    unsigned int texture;
	glGenTextures(1, &texture);
    textures.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	
    // load it
    glTexImage2D(
        GL_TEXTURE_2D, // target texture
        0, // LOD
        GL_RGBA, // nr of color comps
        width,
        height,
        0, // border
        GL_RGBA, // format
        GL_UNSIGNED_BYTE, // type
        data);

    // delete
	stbi_image_free(data);

    // configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

static void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (!app) return;

    app->screenW = w;
    app->screenH = h;

    glViewport(0, 0, w, h);

    app->update_projection();
}

void App::update_projection() {
    glUseProgram(shader);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)screenW / (float)screenH,
        0.01f,
        100.0f
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shader, "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );
}

void App::run() {
    glfwSetWindowUserPointer(window, this);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    
    bool show_demo_window = false;
    TransformComponent& cameraTransform = transformComponents[cameraID];
    glm::vec3& pos = transformComponents[cameraID].position;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        {
            ImGui::Begin("WOW", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("Avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::ColorEdit4("Clear Color", &clearColor.x);
            
            ImGui::SeparatorText("Camera");
            ImGui::SliderFloat("Sensitivity", &cameraSystem->cameraSens, 0.01f, 1.0f, "%.2f");
            ImGui::DragFloat2("Rotation", &cameraTransform.eulers.y, 0.01f);
            ImGui::DragFloat3("Location", &pos.x, 0.01f);
            
            ImGui::SeparatorText("Others");
            ImGui::SliderFloat("Movement Speed", &cameraSystem->moveSpeed, 0.01f, 1.0f, "%.2f");
            ImGui::Checkbox("Dear ImGui Demo", &show_demo_window);
            ImGui::Text("ESC exit\nWASD to move\nE up Q down, local Z axis\nRMB to rotate the camera\nScroll Wheel to change move speed\nPress & Hold CTRL to change from .01 to .1");
            ImGui::End();
        }
       
        motionSystem->update(
            transformComponents,
            physicsComponents,
            16.67f/1000.0f);

        double scroll = scrollY;
        scrollY = 0.0;
        
        bool should_close = cameraSystem->update(
            transformComponents,
            cameraID,
            *cameraComponent,
            16.67f/1000.0f,
            scroll);
        
        if (should_close) {
            break;
        }

        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        glClearColor(
            clearColor.r,
            clearColor.g,
            clearColor.b,
            clearColor.a
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderSystem->update(transformComponents, renderComponents);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
	}
}

void App::set_up_glfw() {
    glfwInit();
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
	window = glfwCreateWindow(screenW, screenH, "AUR30LA Engine Pre-Alpha v0.1", NULL, NULL);
    if (!window) {
        say("src/controller/app.cpp > set_up_glfw() ? !window", 3);
        glfwTerminate();
        return;
    }
	
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glfwShowWindow(window);
    glfwMaximizeWindow(window);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetScrollCallback(window, [](GLFWwindow* window, double, double yoffset) {
            App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
            if (app)
                app->scrollY += yoffset;
        }
    );

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        say("src/controller/app.cpp > set_up_glfw() ? !gladLoadGLLoader", 3);
		glfwTerminate();
	}
}

void App::set_up_opengl() {
	glfwGetFramebufferSize(window, &screenW, &screenH);
	glViewport(0, 0, screenW, screenH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    shader = make_shader(
		"../src/shaders/vertex.glsl", 
		"../src/shaders/fragment.glsl");
    
    glUseProgram(shader);
	unsigned int projLocation = glGetUniformLocation(shader, "projection");
    
    update_projection();
}

void App::make_systems() {
    motionSystem = new MotionSystem();
    cameraSystem = new CameraSystem(shader, window);
    renderSystem = new RenderSystem(shader, window);
}