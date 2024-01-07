#include "Mesh.h"
#include "Model.h"
#include "texture.h"
#include "Camera.h"
#pragma

const unsigned int width = 1000;
const unsigned int height = 1000;
int main()
{
#pragma region GLFW Window
	// Initialise GLFW
	glfwInit();
	// Specify OpenGL version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using modern OpenGL functions 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create GLFWwindow of specified height and width
	GLFWwindow* window = glfwCreateWindow(width, height, "Space!", NULL, NULL);
	// Error checking for window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the context current
	glfwMakeContextCurrent(window);
#pragma endregion GLFW Window
	// Load GLAD 
	gladLoadGL();

	// Specify Viewport of the window
	glViewport(0, 0, width, height);
	
	// Shader program initialising
	Shader shaderProgram("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	
	// colour of the light source (white)
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//  position of the light source
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	// scale of the light source
	glm::mat4 lightModel = glm::mat4(1000.0f);
	// apply transform values to lightModel
	lightModel = glm::translate(lightModel, lightPos);

	// activate shader program
	shaderProgram.Activate();
	//sets the light colour to the colour used above
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	//sets the light position to the position used above
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// depth testing 
	glEnable(GL_DEPTH_TEST);
	
	// Camera setup with positions
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// a Model object loading from the specified file paths
	Model model("models/planet/planet4.gltf");
	Model model1("models/planet2/planet5.gltf");
	Model model2("models/planet3/planet3.gltf");
	Model model3("models/planet4/planet6.gltf");
	Model model4("models/planet5/planet.gltf");
	Model model5("models/planet6/planet.gltf");
	Model model6("models/planet7/planet.gltf");
	Model model7("models/planet8/planet.gltf");
	Model model8("models/planet9/moon.gltf");
	Model model9("models/planet10/jupiter.gltf");

	// Swap back and front Buffer
	glfwSwapBuffers(window);
	// Main While loop
	while (!glfwWindowShouldClose(window))
	{
		// background colour
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


		// clear back and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Process camera inputs
		camera.Inputs(window);
		// update camera's matrix when inputs are given
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		// activate the shaders for the models
		shaderProgram.Activate();
		lightShader.Activate();

		// draw the models specified previously	
		model.Draw(shaderProgram, camera);
		model1.Draw(shaderProgram, camera);
		model2.Draw(shaderProgram, camera);
		model3.Draw(shaderProgram, camera);
		model4.Draw(shaderProgram, camera);
		model5.Draw(shaderProgram, camera);
		model6.Draw(shaderProgram, camera);
		model7.Draw(shaderProgram, camera);
		model8.Draw(shaderProgram, camera);
		model9.Draw(shaderProgram, camera);
		

		// swap back buffer with front
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// deleting shader program and window to optimise power consumption
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}