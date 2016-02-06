#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL_events.h>
#include "glm\glm.hpp"
#include "Camera.h"

class Keyboard
{
public:
	Keyboard() { m_speed = 0.01f; }

	void HandleEvent(const Uint8* keyState, Camera& camera);

	~Keyboard();

private:
	void A_KeyUsed(Camera& camera);
	void S_KeyUsed(Camera& camera);
	void D_KeyUsed(Camera& camera);
	void W_KeyUsed(Camera& camera);
	void Z_KeyUsed(Camera& camera);
	void X_KeyUsed(Camera& camera);

	float m_speed;
};
#endif //KEYBOARD_H