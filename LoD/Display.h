#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL.h>
#undef main

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Update();
	void Clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f);

	void HandleEvent(SDL_Event& e);

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }

	float GetAspectRation() { return (float)m_width / (float)m_height; }

	bool IsClosed() { return m_isClosed; }


private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

	int m_width;
	int m_height;
};

#endif //DISPLAY_H
