#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include <SDL_events.h>
#include "Camera.h"

class Mouse
{
public:
	Mouse() : m_speed(0.05f) {};

	void HandleEvent(SDL_Event& e, Camera& camera);

	~Mouse();

private:

	void Left_MouseMotion(Camera& camera);
	void Right_MouseMotion(Camera& camera);

	void Up_MouseMotion(Camera& camera);
	void Down_MouseMotion(Camera& camera);

	float m_speed;
};

#endif //MOUSE_H