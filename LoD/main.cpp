#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Display.h"
#include "Basic_Shader.h"
#include "Phong_Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Skybox.h"
#include "Terrain.h"
#include <iostream>

/*https://www.youtube.com/watch?v=RqRxhY6iLto */


int main(int argc, char ** argv[])
{

	Display display(800, 600, "TSBK07 Level of Detail on Terrain");
	Texture texture("./textures/dirt.tga");
	Camera camera(glm::vec3(0, 1, 0), 70.0f, display.GetAspectRation(), 0.01f, 1000.0f);

	Terrain terr("./textures/terrain.jpg", "./textures/terrain.jpg");
	
	Skybox sky;
	sky.SkyboxInit("./textures/skybox/", "back.jpg", "front.jpg", "left.jpg", "right.jpg", "top.jpg", "bottom.jpg");
	Transform transform;
	Keyboard keyboard;
	Mouse mouse;

	std::cout << "======CONTROLS======\n";
	std::cout << "Press ESC to quit the application\n";

	std::cout << "Hold right mouse button to look around\n";

	std::cout << "Controls: \n";
	std::cout << "W\tmove forwards\n";
	std::cout << "A\tstrafe left\n";
	std::cout << "S\tmove backwards\n";
	std::cout << "D\tstrafe right\n\n";

	std::cout << "F\tshow wireframes\n";
	std::cout << "B\tLock viewfrustrum in place";
	bool wireframe = true;
	bool lock = false;



	while (!display.IsClosed())
	{
		display.Clear(1, 0, 1, 1);

		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				display.HandleEvent(e);
			}
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				mouse.HandleEvent(e, camera);
			}
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			{
				keyboard.RegisterEvents(e.key);
			}
		}
		if (keyboard.IsPressed(SDL_SCANCODE_ESCAPE))
		{
			display.Quit();
		}

		keyboard.ExecuteEvents(camera, lock, wireframe);
		
		sky.Draw(transform, camera);
	
		terr.Draw(transform, camera, lock, wireframe);

		display.Update();
	}
	return 0;
}