#include "shader.h"

unsigned int make_shader(
    const std::string& vertex_filepath, const std::string& fragment_filepath) {

	//To store all the shader modules
	std::vector<unsigned int> modules;

	//Add a vertex shader module
	modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));

	//Add a fragment shader module
	modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

	//Attach all the modules then link the program
	unsigned int shader = glCreateProgram();
	for (unsigned int shaderModule : modules) {
		glAttachShader(shader, shaderModule);
	}
	glLinkProgram(shader);

	//Check the linking worked
	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		say("src/shader.cpp > make_shader() ? !success\n" + (std::string(errorLog)), 3);
	}

	//Modules are now unneeded and can be freed
	for (unsigned int shaderModule : modules) {
		glDeleteShader(shaderModule);
	}

	return shader;

}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
	
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	if (!file.is_open()) {
		say("src/shader.cpp > make_module() ? !file.is_open", 3);
		return 0;
	}
	while (std::getline(file, line)) {
		// say(line, -1);
		bufferedLines << line << '\n';
	}
	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	// say(shaderSource);
	bufferedLines.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		say("src/shader.cpp > make_module() ? !success\n" + (std::string(errorLog)), 3);
	}

	return shaderModule;
}