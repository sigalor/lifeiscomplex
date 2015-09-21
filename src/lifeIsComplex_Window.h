#ifndef LIFEISCOMPLEX_WINDOW_H
#define LIFEISCOMPLEX_WINDOW_H



LIC_WINDOW::LIC_WINDOW()
{
	//Initialize variables
	window     = NULL;
	width      = 1280;
	height     = 720;
	mouseXChg  = 0;
	mouseYChg  = 0;
	context    = 0;
	fps        = 0;
	quit       = false;

	printf("Starting lifeIsComplex (built at %s %s)...\n\n", __DATE__, __TIME__);
	
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL error while initializing SDL: %s\n", SDL_GetError());
		cleanup();
	}
	printf("Loaded SDL            %d.%d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

	//Set some OpenGL attributes (must be set before window creation!)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,           1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            24);
	
	//Create main window
	window = SDL_CreateWindow("Life Is Complex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		printf("SDL error while creating window: %s\n", SDL_GetError());
		cleanup();
	}
	
	//Create OpenGL context
	context = SDL_GL_CreateContext(window);
	if(context == NULL)
	{
		printf("SDL error while creating OpenGL context: %s\n", SDL_GetError());
		cleanup();
	}
	
	//Initialize SDL_ttf
	if(TTF_Init() != 0)
	{
		printf("SDL_ttf error while initializing SDL_ttf: %s\n", TTF_GetError());
		cleanup();
	}
	printf("Loaded SDL_ttf        %d.%d.%d\n", TTF_MAJOR_VERSION, TTF_MINOR_VERSION, TTF_PATCHLEVEL);
	
	//Initialize GLEW (OpenGL Extension Wrangler)
	GLenum glewErr = glewInit();
	if(glewErr != GLEW_OK)
	{
		printf("GLEW error while initializing GLEW: %s\n", glewGetErrorString(glewErr));
		cleanup();
	}
	
	//Check support for required OpenGL version 4.0
	if(!GLEW_VERSION_4_0)
	{
		printf("GLEW error: OpenGL 4.0 not supported\n");
		cleanup();
	}
	printf("Loaded GLEW           %s\n\n", glewGetString(GLEW_VERSION));
	
	//Print some version information from other libraries
	printf("Using  SFML           %d.%d\n", SFML_VERSION_MAJOR, SFML_VERSION_MINOR);
	printf("Using  GLM            %d.%d.%d.%d\n", GLM_VERSION_MAJOR, GLM_VERSION_MINOR, GLM_VERSION_PATCH, GLM_VERSION_REVISION);
	printf("Using  Boost          %d.%d.%d\n\n", BOOST_VERSION/100000, BOOST_VERSION/100%1000, BOOST_VERSION%100);
	
	//Initialize mouse
	SDL_WarpMouseInWindow(window, width/2, height/2);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void LIC_WINDOW::checkEvents()
{
	SDL_Event e;
	
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			//General events
			case SDL_QUIT:
			{
				quit = true;
				break;
			}
			
			//Mouse events
			case SDL_MOUSEMOTION:
			{
				mouseXChg = e.motion.xrel;
				mouseYChg = e.motion.yrel;
				break;
			}
		}
	}
	
	//Process keyboard events
	if(Keyboard::isKeyPressed(Keyboard::Escape))
		quit = true;
}

void LIC_WINDOW::cleanup()
{
	quit = true;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



#endif