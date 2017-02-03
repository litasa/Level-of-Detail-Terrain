#include "Keyboard.h"
#include <iostream>


void Keyboard::RegisterEvents(SDL_KeyboardEvent& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		auto it = std::find(keys_down.begin(), keys_down.end(), e.keysym.scancode);
		if (it == keys_down.end())
		{
			keys_down.push_back(e.keysym.scancode);
		}
	}
	if (e.type == SDL_KEYUP)
	{
		auto it = std::find(keys_down.begin(), keys_down.end(), e.keysym.scancode);
		if (it != keys_down.end())
		{
			keys_down.erase(it);
		}
	}
}

void Keyboard::ExecuteEvents(Camera& camera, bool& lock_frustum, bool& wireframe)
{
	for (size_t i = 0; i < keys_down.size(); ++i)
	{
		switch (keys_down[i])
		{
		case SDL_SCANCODE_W:
		{
			W_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_A:
		{
			A_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_S:
		{
			S_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_D:
		{
			D_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_L:
		{
			std::cout << "x: " << camera.GetUp().x << "y: " << camera.GetUp().y << "z: " << camera.GetUp().z << std::endl;
			break;
		}
		case SDL_SCANCODE_Z:
		{
			Z_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_X:
		{
			X_KeyUsed(camera);
			break;
		}
		case SDL_SCANCODE_B:
		{
			B_KeyUsed(lock_frustum);
			keys_down.erase(keys_down.begin() + i);
			break;
		}
		case SDL_SCANCODE_F:
		{
			F_KeyUsed(wireframe);
			keys_down.erase(keys_down.begin() + i);
			break;
		}
		default:
			break;
		}
	}
}

void Keyboard::A_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetLeft(), m_speed);
}

void Keyboard::S_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetBackwards(), m_speed);
}

void Keyboard::D_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetRight(), m_speed);
}

void Keyboard::W_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetForward(), m_speed);
}

void Keyboard::Z_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetUp(), m_speed);
}

void Keyboard::X_KeyUsed(Camera& camera)
{
	camera.Move(camera.GetUp(), -m_speed);
}

void Keyboard::B_KeyUsed(bool& lock_frustum)
{
		lock_frustum = (!lock_frustum);
		std::cout << "frustum lock: " << lock_frustum << std::endl;
}

void Keyboard::F_KeyUsed(bool& wireframe)
{
		wireframe = (!wireframe);
		std::cout << "wireframe: " << wireframe << std::endl;
}
Keyboard::~Keyboard()
{
}