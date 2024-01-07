#include "Camera.h"

// Initialises camera with width, height and position
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}
// Void to update camera position 
void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// view and projection matrices		
	glm::mat4	 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Calculates view matrix and looks in desired direction
	view = glm::lookAt(Position, Position + Orientation, Up);

	// Perspective projection matrix
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	// Combines projection and view matrices
	cameraMatrix = projection * view;

}
// Exports Camera matrix to uniform 
void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix	));
}
// Void to process inputs to move camera
void Camera::Inputs(GLFWwindow* window	)
{
	// Movement controls (WASD)
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	// Space and LeftControl to move camera up and down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	// Left shift to "sprint" (camera movements are quicker holding left shift)
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	// Mouse control
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// hides cursor if clicking
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		// Reset curser position after clicking
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// coords of mouse cursor
		double mouseX;
		double mouseY;

		// Current mouse position
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Rotation amount/Mouse Sensitivity
		float rotX = camSensitivity * (float(mouseY - (height / 2)) / height);
		float rotY = camSensitivity * (float(mouseX - (height / 2)) / height);

		// New orientation 
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or glm::angle(newOrientation, +Up) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}

		// Horizontal Rotation
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		
		// Reset cursor position to the center of the window
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}

	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// makes cursor visible when not clicking 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

}