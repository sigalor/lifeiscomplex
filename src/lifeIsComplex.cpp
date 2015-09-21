#define SFML_STATIC
#define GLEW_STATIC
#define GLM_FORCE_RADIANS
#undef __STRICT_ANSI__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <dirent.h>
#include <SDL2/SDL.h>						//SDL			(version 2.0.2,   http://www.libsdl.org/)   --> UPDATE (2.0.3)
#include <SDL2/SDL_ttf.h>					//SDL_ttf		(version 2.0.12,  http://libsdl.org/projects/SDL_ttf/)
#include <GL/glew.c>						//GLEW			(version 1.13.0,  http://glew.sourceforge.net/)
#include <GL/glew.h>
#include <SFML/System.hpp>					//SFML			(version 2.3,     http://sfml-dev.org/)
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>						//GLM			(version 0.9.7.0, http://glm.g-truc.net/)
#include <glm/gtc/matrix_transform.hpp>
#include <boost/version.hpp>				//Boost			(version 1.58.0,  http://www.boost.org/)
#include <boost/tokenizer.hpp>
#include <boost/multi_array.hpp>
#include <rapidxml.hpp>						//RapidXML		(version 1.13,    http://rapidxml.sourceforge.net/)
#include <rapidxml_utils.hpp>

using namespace std;
using namespace sf;
using namespace boost;
using namespace rapidxml;

#include "lifeIsComplex_Classes.h"
#include "lifeIsComplex_Window.h"
#include "lifeIsComplex_Camera.h"
#include "lifeIsComplex_Shader.h"
#include "lifeIsComplex_Graphics.h"

int main(int argc, char **argv)
{
	LIC_WINDOW		licWindow;
	LIC_GRAPHICS	licGraphics;
	LIC_CAMERA		licCamera;
	LIC_SHADER		licShader("resources/shaders/lic_Main");
	LIC_SHADER		licTextureShader("resources/shaders/lic_Texture");
	LIC_SHADER		licFontShader("resources/shaders/lic_Font");

	while(!licWindow.quit)
	{
		licWindow.checkEvents();
		licCamera.update(&licWindow);
		licGraphics.render(&licWindow, &licShader, &licTextureShader, &licFontShader, &licCamera);
	}
	
	licGraphics.cleanup();
	licWindow.cleanup();
	
	return 0;
}