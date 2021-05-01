#include "Camera.h"

Camera::Camera() {};

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed, Window* window)
{
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->front = glm::vec3(0.0f, 0.0f, 0.0f);
	this->move_speed = move_speed;
	this->turn_speed = turn_speed;
	this->window = window;
	this->fov = DEFAULT_FOV;
	this->default_projection = glm::perspective(glm::radians(45.0f), window->get_buffer_width() / window->get_buffer_width(), 0.1f, 1000.0f);

	// Calculate our camera front/right angle coordinates using the defaults
	update();
}

void Camera::key_controls(bool* keys, GLfloat delta_time, EntityGroup* const selectedModel)
{
	// Slow down movement on faster CPUs
	GLfloat velocity = move_speed * delta_time;
	GLfloat modified_speed = move_speed;

	// SHIFT - Increase movement speed
	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		// Increase the speed if the user is holding shift
		modified_speed *= 2;
	}

	// LEFT CTRL - Go straight down
	if (keys[GLFW_KEY_LEFT_CONTROL])
	{
		position.y -= modified_speed;
	}

	// SPACEBAR - Go straight up
	if (keys[GLFW_KEY_SPACE])
	{
		position.y += modified_speed;
	}

	// W - Move forward
	if (keys[GLFW_KEY_W])
	{
		position += front * modified_speed;
	}

	// S - Move backwards
	if (keys[GLFW_KEY_S])
	{
		position -= front * modified_speed;
	}

	// A - Move left
	if (keys[GLFW_KEY_A])
	{
		position -= right * modified_speed;
	}

	// D - Move right
	if (keys[GLFW_KEY_D])
	{
		position += right * modified_speed;
	}

	// UP ARROW - Rotate CW around Y-Axis
	if (keys[GLFW_KEY_UP])
	{
		y_rotation += -2.5;
	}

	// DOWN ARROW - Rotate CCW around Y-Axis
	if (keys[GLFW_KEY_DOWN])
	{
		y_rotation += 2.5;
	}

	// LEFT ARROW - Rotate CW around X-Axis
	if (keys[GLFW_KEY_LEFT])
	{
		x_rotation += -2.5;
	}

	// RIGHT ARROW - Rotate CCW around Y-Axis
	if (keys[GLFW_KEY_RIGHT])
	{
		x_rotation += 2.5;
	}

	// HOME - Reset to default values (Reposition camera to origin)
	if (keys[GLFW_KEY_HOME])
	{
		// Reset to default values
		x_rotation = 0;
		y_rotation = 0;
		front = glm::vec3(0.0f, 0.0f, 0.0f);
		position = glm::vec3(0.0f, 0.0f, 20.0f);
		world_up = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = -90.0;
		pitch = 0;
		fov = DEFAULT_FOV;
	}
	// Z - Reset FOV (Undo zooming)
	if (keys[GLFW_KEY_Z])
	{
		this->fov = DEFAULT_FOV;
	}
	
	// Model transformation below \\

	// MOVE FORWARD/BACKWARD
	if (keys[GLFW_KEY_Y])
	{
		selectedModel->translate(glm::vec3(.25f, 0.f, 0.f));
	}
	else if (keys[GLFW_KEY_H])
	{
		selectedModel->translate(glm::vec3(-.25f, 0.f, 0.f));
	}
	// MOVE LEFT/RIGHT
	if (keys[GLFW_KEY_G])
	{
		selectedModel->translate(glm::vec3(0.f, 0.f, .25f));
	}
	else if (keys[GLFW_KEY_J])
	{
		selectedModel->translate(glm::vec3(0.f, 0.f, -.25f));
	}
	// MOVE UP/DOWN
	if (keys[GLFW_KEY_F])
	{
		selectedModel->translate(glm::vec3(0.f, .25f, 0.f));
	}
	else if (keys[GLFW_KEY_V])
	{
		selectedModel->translate(glm::vec3(0.f, -.25f, 0.f));
	}
	// ROTATE LEFT/RIGHT
	if (keys[GLFW_KEY_B])
	{
		selectedModel->get_children_groups()[0]->rotate(cugl::Quaternion(0.f, glm::radians(.5f), 0.f));
	}
	else if (keys[GLFW_KEY_N])
	{
		selectedModel->get_children_groups()[0]->rotate(cugl::Quaternion(0.f, glm::radians(-.5f), 0.f));
	}
    // SHEAR LEFT/RIGHT
    if (keys[GLFW_KEY_COMMA])
    {
        selectedModel->shearY(vec2(-0.01f, 0));
    }
    else if (keys[GLFW_KEY_PERIOD])
    {
        selectedModel->shearY(vec2(0.01f, 0));
    }
}

void Camera::mouse_controls(GLfloat x_change, GLfloat y_change, bool* mouse_buttons, GLfloat delta_time)
{
	// LEFT CLICK - Zoom in and out by dragging up and down
	if (mouse_buttons[GLFW_MOUSE_BUTTON_LEFT])
	{
		fov -= y_change;

		if (fov < MIN_FOV) {
			fov = MIN_FOV;
		}
			
		if (fov > MAX_FOV) {
			fov = MAX_FOV;
		}

		return;
	}

	// MOUSE4 - Screen panning (Blender style)
	if (mouse_buttons[GLFW_MOUSE_BUTTON_4])
	{
		// Apply our left and right movement
		position += right * (x_change * delta_time);
		// Apply our upwards and downwards movement to the axis perpendicular to where our camera is facing
		position += glm::normalize(glm::cross(right, front)) * (y_change * delta_time);

		update();
		// Return right to skip freelook camera behavior
		return;
	}

	// SCROLL WHEEL BUTTON - Lock camera to Y-Axis movement (Pitch)
	if (mouse_buttons[GLFW_MOUSE_BUTTON_MIDDLE])
	{
		y_change *= turn_speed;
		pitch += y_change;
	}

	// RIGHT CLICK - Lock camera to X-Axis movement (Yaw)
	else if (mouse_buttons[GLFW_MOUSE_BUTTON_RIGHT])
	{
		x_change *= turn_speed;
		yaw += x_change;
	}

	else
	{
		// Adjust the value changes by our speed modifiers
		x_change *= turn_speed;
		y_change *= turn_speed;
		// Apply changes to our yaw and pitch
		yaw += x_change;
		pitch += y_change;
	}	

	// Limit our camera from flipping when looking too far up or down
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculate_view_matrix() const
{
	glm::mat4 view_matrix = glm::lookAt(position, position + front, up);

	// If y rotation values are set apply the appropriate changes to our view matrix
	if (y_rotation != 0) {
		view_matrix = glm::rotate(view_matrix, glm::radians(y_rotation), glm::vec3(0.0f, -1.0f, 0.0f));
	}
	// If x rotation values are set apply the appropriate changes to our view matrix
	if (x_rotation != 0) {
		view_matrix = glm::rotate(view_matrix, glm::radians(x_rotation), glm::vec3(-1.0f, 0.0f, 0.0f));
	}

	return view_matrix;
}

glm::mat4 Camera::calculate_projection()
{
	// If the zoom is not set to zero recalculate the perspective using the modified FOV
	if (fov != DEFAULT_FOV) {
		return glm::perspective(glm::radians(fov), window->get_buffer_width() / window->get_buffer_width(), 0.1f, 1000.0f);
	}

	return default_projection;
}

void Camera::update()
{
	// Calculate the front of our camera using the changes in our yaw and pitch
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}