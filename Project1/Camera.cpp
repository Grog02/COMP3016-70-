#include "Camera.h"


Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	
	glm::mat4	 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// makes camera look into desired position from the correct starting position
	view = glm::lookAt(Position, Position + Orientation, Up);

	// adding perspective 
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	// sets cam matrix
	cameraMatrix = projection * view;

}
void Camera::Matrix(Shader& shader, const char* uniform)
{
	// exports cam matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix	));
}

void Camera::Inputs(GLFWwindow* window	)
{
	// key inputs for moving camera left, right, up and down
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	// mouse inputs, moving cam when mouse is clicked 
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// hides cursor if clicking
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// coords of mouse cursor
		double mouseX;
		double mouseY;

		// stores mouse coord in the doubles
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// brings mouse cusor to middle of screen
		float rotX = camSensitivity * (float(mouseY - (height / 2)) / height);
		float rotY = camSensitivity * (float(mouseX - (height / 2)) / height);


		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or glm::angle(newOrientation, +Up) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}

		// rotates left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		
		// brings mouse cursor to middle of screen

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}

	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// makes cursor visible when not clicking 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

}