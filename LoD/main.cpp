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

	Display display(800, 600, "TSBK07 Space");
	Basic_Shader base_shader("./shaders/space");
	Phong_Shader phong("./shaders/phong");
	Texture texture("./textures/dirt.tga");
	Camera camera(glm::vec3(0, 0, 0), 70.0f, display.GetAspectRation(), 0.01f, 1000.0f);

	Terrain terr("./textures/terrain.jpg", "./textures/terrain.jpg");
	
	Skybox sky;
	sky.SkyboxInit("./textures/skybox/", "back.jpg", "front.jpg", "left.jpg", "right.jpg", "top.jpg", "bottom.jpg");
	Transform transform;
	Keyboard keyboard;
	Mouse mouse;

	float counter = 0.0f;
	Mesh monkey("./models/monkey3.obj");
	Mesh box("./models/box.obj");

	std::cout << "init complete" << std::endl;


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
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		keyboard.HandleEvent(currentKeyStates, camera);
		
		//sky.Draw(transform, camera);

		//phong.Use();
		//phong.UpdateValues(transform, camera);
		
		//texture.Use();
		//monkey.Draw();
		//box.Draw();
		
		terr.Draw(transform, camera);

		display.Update();

		counter += 0.001f;
	}
	return 0;
}