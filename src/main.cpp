#include "engine.h"
Engine aur;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

void say(const std::string& words, int type, bool stay) {
    if (stay) std::cout << "\r\033[K";

    if (type == 0)
        std::cout << "[DEBUG] ";
    if (type == 1) 
        std::cout << "[WATCH] ";
    if (type == 2) 
        std::cout << "[WARNING] ";
    if (type == 3) 
        std::cout << "[FATAL] ";
    
    std::cout << words;
    
    if (stay) std::cout << std::flush;
	else std::cout << "\n";
};
std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y-%X", &tstruct);
    return buf;
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

int main() {
	#if AUR_DEBUG
    auto startTime = std::chrono::high_resolution_clock::now();
    say(std::string(aur.currentVer) + "\nstart---" + currentDateTime(), -1);
    #endif

	App* app = new App();

	unsigned int cubeEntity = app->make_entity();
	TransformComponent transform;
	transform.position = {5.0f, 0.0f, 0.0f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	app->transformComponents[cubeEntity] = transform;

	PhysicsComponent physics;
	physics.velocity = {0.0f, 0.0f, 0.0f};
	physics.eulerVelocity = {0.0f, 0.0f, 10.0f};
	app->physicsComponents[cubeEntity] = physics;
	
	RenderComponent render;
	render.mesh = app->make_cube_mesh({0.25f, 0.25f, 0.25f});
	render.material = app->make_texture("../assets/textures/base_T.jpg");
	app->renderComponents[cubeEntity] = render;

	unsigned int cameraEntity = app->make_entity();
	transform.position = {0.0f, 0.0f, 1.0f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	app->transformComponents[cameraEntity] = transform;

	CameraComponent* camera = new CameraComponent();
	app->cameraComponent = camera;
	app->cameraID = cameraEntity;

	app->set_up_opengl();
	app->make_systems();
    app->update_projection();

	app->run();
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	delete app;

	#if AUR_DEBUG
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    say("stop----" + currentDateTime() + "\ntimer-----------" + formatElapsed(elapsed) + "\nHave a nice day :)", -1);
    #endif
	return 0;
}