#ifndef LIFEISCOMPLEX_SHADER_H
#define LIFEISCOMPLEX_SHADER_H


//#define LIC_SHADER_LOGOUTPUT


void LIC_SHADER::debugOutput(string shaderName, GLuint vShader, GLuint fShader, GLuint program)
{
	ofstream output;
	int      logLength;
	string   log;

	output.open((shaderName + ".shader_debug").c_str(), ifstream::out);

	output << "Vertex Shader Log (" << shaderName << "):" << endl;
	glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLength);
	glGetShaderInfoLog(vShader, logLength, NULL, &log[0]);
	output << log << endl << endl;
	
	output << "Fragment Shader Log (" << shaderName << "):" << endl;
	glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &logLength);
	glGetShaderInfoLog(fShader, logLength, NULL, &log[0]);
	output << log << endl << endl;
	
	output << "Program Log (" << shaderName << "):" << endl;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	glGetProgramInfoLog(program, logLength, NULL, &log[0]);
	output << log << endl << endl;
	
	output.close();
}

LIC_SHADER::LIC_SHADER(string shaderName, bool debug)
{
	ifstream    vssFile,  fssFile;
	string      vssName,  fssName;
	string      vsSource, fsSource;
	const char *source;                //Need to convert   std::string   to   const char*   for OpenGL
	GLuint      vShader,  fShader;
	
	//Create filenames
	vssName = shaderName + ".vss";
	fssName = shaderName + ".fss";
	
	//Open vertex shader source file and fragment shader source file
	vssFile.open(vssName.c_str(), ifstream::in);
	fssFile.open(fssName.c_str(), ifstream::in);
	
	//Check for invalid files
	if(!vssFile)
	{
		printf("Unable to open Vertex Shader Source File \"%s\"!\n", vssName.c_str());
		return;
	}
	if(!fssFile)
	{
		printf("Unable to open Fragment Shader Source File \"%s\"!\n", fssName.c_str());
		return;
	}
	
	//Read entire files
	vsSource = string((std::istreambuf_iterator<char>(vssFile)), std::istreambuf_iterator<char>());
	fsSource = string((std::istreambuf_iterator<char>(fssFile)), std::istreambuf_iterator<char>());
	
	//Close files
	vssFile.close();
	fssFile.close();
	
	#ifdef LIC_SHADER_LOGOUTPUT
	int compiled, linked, logLength;
	char *log;
	printf("Info for \"%s\"\n", shaderName.c_str());
	for(int i=0; i<60; i++)
		printf("=");
	printf("\n");
	source = vsSource.c_str();
	glGetError();		//For clearing the OpenGL error variable
	vShader = glCreateShader(GL_VERTEX_SHADER);
	printf("Error %4d - vShader = glCreateShader(GL_VERTEX_SHADER)\n", glGetError());
	glShaderSource(vShader, 1, &source, NULL);
	printf("Error %4d - glShaderSource(vShader, 1, &source, NULL)\n", glGetError());
	glCompileShader(vShader);
	printf("Error %4d - glCompileShader(vShader)\n");
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &compiled);
	printf("vShader compile status: %d\n", compiled);
	glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLength);
	log = (char*)malloc(logLength);
	glGetShaderInfoLog(vShader, logLength, NULL, log);
	printf("vShader log:\n%s\n\n", log);
	free(log);
	#else
	source = vsSource.c_str();
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &source, NULL);
	glCompileShader(vShader);
	#endif
	
	#ifdef LIC_SHADER_LOGOUTPUT
	source = fsSource.c_str();
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	printf("Error %4d - fShader = glCreateShader(GL_FRAGMENT_SHADER)\n", glGetError());
	glShaderSource(fShader, 1, &source, NULL);
	printf("Error %4d - glShaderSource(fShader, 1, &source, NULL)\n", glGetError());
	glCompileShader(fShader);
	printf("Error %4d - glCompileShader(fShader)\n", glGetError());
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &compiled);
	printf("fShader compile status: %d\n", compiled);
	glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &logLength);
	log = (char*)malloc(logLength);
	glGetShaderInfoLog(fShader, logLength, NULL, log);
	printf("fShader log:\n%s\n\n", log);
	free(log);
	#else
	source = fsSource.c_str();
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &source, NULL);
	glCompileShader(fShader);
	#endif
	
	#ifdef LIC_SHADER_LOGOUTPUT
	program = glCreateProgram();
	printf("Error %4d - program = glCreateProgram()\n", glGetError());
	glAttachShader(program, vShader);
	printf("Error %4d - glAttachShader(program, vShader)\n", glGetError());
	glAttachShader(program, fShader);
	printf("Error %4d - glAttachShader(program, fShader)\n", glGetError());
	glLinkProgram(program);
	printf("Error %4d - glLinkProgram(program)\n", glGetError());
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	printf("program link status: %d\n", linked);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	log = (char*)malloc(logLength);
	glGetProgramInfoLog(program, logLength, NULL, log);
	printf("program log:\n%s\n\n", log);
	free(log);
	#else
	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	#endif
	
	if(debug)
		debugOutput(shaderName, vShader, fShader, program);
	
	glDeleteShader(vShader);
	#ifdef LIC_SHADER_LOGOUTPUT
	printf("Error %4d - glDeleteShader(vShader)\n", glGetError());
	#endif
	glDeleteShader(fShader);
	#ifdef LIC_SHADER_LOGOUTPUT
	printf("Error %4d - glDeleteShader(fShader)\n\n\n\n", glGetError());
	#endif
}



#endif