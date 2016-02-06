#include "Mouse.h"
#include <iostream>

void Mouse::HandleEvent(SDL_Event& e, Camera& camera)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			std::cout << "Relative Mouse Mode On" << std::endl;
		}
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			std::cout << "Relative Mouse Mode Off" << std::endl;
		}
	}

	if (e.type == SDL_MOUSEMOTION)
	{
		if (SDL_GetRelativeMouseMode() == SDL_TRUE)
		{
			int x, y;
			SDL_GetRelativeMouseState(&x, &y);
			//std::cout << "Mouse x,y: " << x << ", " << y << std::endl;
			if (x < 0)
			{
				Left_MouseMotion(camera);
			}
			if (x > 0)
			{
				Right_MouseMotion(camera);
			}
			if (y < 0)
			{
				Up_MouseMotion(camera);
			}
			if (y > 0)
			{
				Down_MouseMotion(camera);
			}
		}
	}
}

void Mouse::Left_MouseMotion(Camera& camera)
{
	camera.RotateY(m_speed);
}

void Mouse::Right_MouseMotion(Camera& camera)
{
	camera.RotateY(-m_speed);
}

void Mouse::Up_MouseMotion(Camera& camera)
{
	camera.RotateX(-m_speed);
}

void Mouse::Down_MouseMotion(Camera& camera)
{
	camera.RotateX(m_speed);
}

Mouse::~Mouse()
{
}