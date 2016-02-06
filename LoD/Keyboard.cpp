#include "Keyboard.h"
#include <iostream>


void Keyboard::HandleEvent(const Uint8* keyState, Camera& camera)
{

	if (keyState[SDL_SCANCODE_W])
	{
		W_KeyUsed(camera);
	}
	if (keyState[SDL_SCANCODE_A])
	{
		A_KeyUsed(camera);
	}
	if (keyState[SDL_SCANCODE_S])
	{
		S_KeyUsed(camera);
	}
	if (keyState[SDL_SCANCODE_D])
	{
		D_KeyUsed(camera);
	}
	if (keyState[SDL_SCANCODE_L])
	{
		std::cout << "x: " << camera.GetUp().x << "y: " << camera.GetUp().y << "z: " << camera.GetUp().z << std::endl;
	}
	if (keyState[SDL_SCANCODE_Z])
	{
		Z_KeyUsed(camera);
	}
	if (keyState[SDL_SCANCODE_X])
	{
		X_KeyUsed(camera);
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

Keyboard::~Keyboard()
{
}