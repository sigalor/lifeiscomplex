#ifndef LIFEISCOMPLEX_CLASSES_H
#define LIFEISCOMPLEX_CLASSES_H



class LIC_WINDOW;
class LIC_CAMERA;
class LIC_SHADER;
class LIC_GRAPHICS;



class LIC_WINDOW
{
	private:
		SDL_GLContext  context;                //OpenGL context handle
	
	public:
		SDL_Window    *window;                 //Window handle
		int            width, height;          //Window's width and height
		int            mouseXChg, mouseYChg;   //Relative changed mouse position in pixels
		int            fps;                    //Frames per second
		bool           quit;                   //quit==true --> the window will quit
		
		LIC_WINDOW();
	
		void checkEvents();
		void cleanup();
};



class LIC_CAMERA
{
	private:
		void move(float, float);
		
		float maxPlayerSpeed;
		float playerAcceleration;
		float playerSlowdown;
		
	public:
		glm::vec3 position;     //Camera's position
		float yaw;              //Rotation around vertical axis
		float pitch;            //Rotation around horizontal axis
		float cameraSpeed;		//Camera's speed
		float playerSpeedFB;	//Speed of the player (forward and backward)
		float playerSpeedLR;	//Speed of the player (left and right)
		float playerSpeedUD;	//Speed of the player (up and down)
	
		LIC_CAMERA();
	
		void update(LIC_WINDOW*);
};



class LIC_SHADER
{
	private:
		void debugOutput(string, GLuint, GLuint, GLuint);

	public:
		GLuint program;
		
		LIC_SHADER(string, bool=false);
};



class LIC_GRAPHICS
{
	private:
		GLuint						vao;			//Vertex Array Object
		GLuint						vbo, nbo, cbo;
		GLuint						bgVBO, bgNBO, bgTCBO, bgTBO;
		unsigned long				numVertices;
		TTF_Font				   *font;
		xml_document<>				doc;
		xml_document<>				treeDoc;
		//vector<vector<vector<glm::vec3> > > buildingsPolygons;
		vector<glm::vec3>			vertices, normals, colors;
		//vector<glm::vec3>			buildingsPolygons_Easy;
		//vector<vector<unsigned long> >	indices;
		Image						noise;
		pair<glm::vec2, glm::vec2>	noiseBBox;
		Image						bg;
		pair<glm::vec2, glm::vec2>	bgBBox;

	public:
		glm::mat4					mMatrix;		//Model matrix
		glm::mat4					vMatrix;		//View matrix
		glm::mat4					pMatrix;		//Projection matrix
	
		LIC_GRAPHICS();
		
		glm::vec2					UTMtoLL(double, double, double);
		//void						convertToObj(string);
		void						loadMapPiece(string);
		glm::vec3					getNormal(glm::vec3, glm::vec3, glm::vec3);
		void						renderFonts(LIC_WINDOW*, LIC_SHADER*, LIC_CAMERA*);
		void						render(LIC_WINDOW*, LIC_SHADER*, LIC_SHADER*, LIC_SHADER*, LIC_CAMERA*);
		void						cleanup();
};



#endif