#ifndef LIFEISCOMPLEX_GRAPHICS_H
#define LIFEISCOMPLEX_GRAPHICS_H


#define LIC_LON_FACTOR 11129.186910704148f
#define LIC_LAT_FACTOR 11057.42727f



LIC_GRAPHICS::LIC_GRAPHICS()
{	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	font = TTF_OpenFont("resources/fonts/Anonymous_Pro.ttf", 20);
	if(font == NULL)
		printf("SDL_ttf error while opening font file: %s\n\n", TTF_GetError());
	
	noise.loadFromFile("resources/maps/noise.png");
	noiseBBox = make_pair(glm::vec2(9.732352f, 53.410409f), glm::vec2(10.327111f, 53.728385f));
	
	//bgTBO = SOIL_load_OGL_texture("resources/maps/bg.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	bgBBox = make_pair(glm::vec2(9.7350f, 53.4433f), glm::vec2(10.0497f, 53.6274f));
	
	bg.loadFromFile("resources/maps/bg.png");
	glGenTextures(1, &bgTBO);
	glBindTexture(GL_TEXTURE_2D, bgTBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bg.getSize().x, bg.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bg.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//glm::vec2 test = UTMtoLL(548877.483f, 5936734.482f, 32);
	//printf("%f / %f\n", test.x, test.y);
	//abort();
	
	vector<glm::vec3> bgVertices = { glm::vec3(bgBBox.second.x*LIC_LON_FACTOR, 0.0f, bgBBox.first.y*LIC_LAT_FACTOR),
									 glm::vec3(bgBBox.second.x*LIC_LON_FACTOR, 0.0f, bgBBox.second.y*LIC_LAT_FACTOR),
									 glm::vec3(bgBBox.first.x*LIC_LON_FACTOR, 0.0f, bgBBox.second.y*LIC_LAT_FACTOR),
									 glm::vec3(bgBBox.first.x*LIC_LON_FACTOR, 0.0f, bgBBox.first.y*LIC_LAT_FACTOR) };
	vector<glm::vec3> bgNormals = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) };
	vector<glm::vec2> bgTexCoords = { glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };
	
	printf("%f / %f / %f\n", bgVertices[0].x, bgVertices[0].y, bgVertices[0].z);
	
	glGenBuffers(1, &bgVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glBufferData(GL_ARRAY_BUFFER, bgVertices.size()*sizeof(glm::vec3), bgVertices.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &bgNBO);
	glBindBuffer(GL_ARRAY_BUFFER, bgNBO);
	glBufferData(GL_ARRAY_BUFFER, bgNormals.size()*sizeof(glm::vec3), bgNormals.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &bgTCBO);
	glBindBuffer(GL_ARRAY_BUFFER, bgTCBO);
	glBufferData(GL_ARRAY_BUFFER, bgTexCoords.size()*sizeof(glm::vec2), bgTexCoords.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	
	rapidxml::file<> treeFile("resources/maps/trees.xml");
	treeDoc.parse<0>(treeFile.data());
	xml_node<>* trees = treeDoc.first_node("trees");
	for(xml_node<>* tree = trees->first_node(); tree; tree = tree->next_sibling())
	{
		glm::vec2 pos = glm::vec2(atof(tree->first_node("lon")->value()), atof(tree->first_node("lat")->value()));
		if(pos.x < bgBBox.first.x  ||  pos.y < bgBBox.first.y  ||  pos.x > bgBBox.second.x  ||  pos.y > bgBBox.second.y)
			continue;
		pos *= glm::vec2(LIC_LON_FACTOR, LIC_LAT_FACTOR);
		
		float dm = atof(tree->first_node("DM")->value());
		vector<glm::vec3> treeVerts = { glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y-dm/20.0f),
									    glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y+dm/20.0f),
										
										glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y-dm/20.0f),
										glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, dm/10.0f+1.0f, pos.y-dm/20.0f),
										
										glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f),
										glm::vec3(pos.x+dm/20.0f, dm/10.0f+1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f),
										
										glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y+dm/20.0f),
										glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, dm/10.0f+1.0f, pos.y+dm/20.0f),
										
										glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f),
										glm::vec3(pos.x-dm/20.0f, dm/10.0f+1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f),
										
										glm::vec3(pos.x-dm/20.0f, 1.0f, pos.y-dm/20.0f), glm::vec3(pos.x+dm/20.0f, dm/10.0f+1.0f, pos.y-dm/20.0f),
									    glm::vec3(pos.x+dm/20.0f, 1.0f, pos.y+dm/20.0f), glm::vec3(pos.x-dm/20.0f, dm/10.0f+1.0f, pos.y+dm/20.0f) };
		vector<glm::vec3> treeNorms = { glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f),
										glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f),
										glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f),
										glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f),
										glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
										glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) };
										
										
		vertices.insert(vertices.end(), treeVerts.begin(), treeVerts.end());
		normals.insert(normals.end(), treeNorms.begin(), treeNorms.end());
		for(int i=0; i<24; i++)
			colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	
	
	
	DIR *dir;
	struct dirent *ent;
	dir = opendir("resources/xmldata/");
	while((ent = readdir(dir)) != NULL)
	{
		if(strcmp(ent->d_name, ".") == 0  ||  strcmp(ent->d_name, "..") == 0)
			continue;
		loadMapPiece(ent->d_name);
	}
	closedir(dir);
	
	printf("%f %f %f\n", vertices[0].x, vertices[0].y, vertices[0].z);
	printf("%d vertices, %d normals\n", vertices.size(), normals.size());
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	numVertices = vertices.size();
	vertices.clear();
	normals.clear();
	
	/*DIR *dir;
	struct dirent *ent;
	dir = opendir("resources/xmldata/");
	while((ent = readdir(dir)) != NULL)
	{
		if(strcmp(ent->d_name, ".") == 0  ||  strcmp(ent->d_name, "..") == 0)
			continue;
		convertToObj(ent->d_name);
		printf("Converted %s (indices = %d, vertices = %d)\n", ent->d_name, indices.size(), buildingsPolygons_Easy.size());
	}
	closedir(dir);
	
	
	FILE* out = fopen("resources/objdata/out.obj", "w");
	for(glm::vec3& v : buildingsPolygons_Easy)
		fprintf(out, "v %f %f %f\n", v.x, v.y, v.z);
	for(vector<unsigned long>& v1 : indices)
	{
		fprintf(out, "f ");
		for(unsigned long& v2 : v1)
			fprintf(out, "%d ", v2);
		fprintf(out, "\n");
	}
	fclose(out);*/
}

/*void LIC_GRAPHICS::convertToObj(string filename)
{
	rapidxml::file<> map1File(("resources/xmldata/" + filename).c_str());
	doc.parse<0>(map1File.data());
	
	xml_node<>* cityModel = doc.first_node("core:CityModel");
	for(xml_node<>* building = cityModel->first_node(); building; building = building->next_sibling())
	{
		if(strcmp(building->name(), "core:cityObjectMember") == 0)
		{
			vector<vector<glm::vec3> > polygons;
			xml_node<>* surfaces = building->first_node("bldg:Building")->first_node("bldg:lod1Solid")->first_node("gml:Solid")->first_node("gml:exterior")->first_node("gml:CompositeSurface");
			for(xml_node<>* surface = surfaces->first_node(); surface; surface = surface->next_sibling())
			{
				vector<glm::vec3> polygonPts;
				vector<unsigned long> polygonIndices;
				xml_node<>* curMapPolygon = surface->first_node("gml:Polygon")->first_node("gml:exterior")->first_node("gml:LinearRing");
				for(xml_node<>* pos = curMapPolygon->first_node(); pos; pos = pos->next_sibling())
				{
					vector<float> pt;
					string value(pos->value());
					tokenizer<char_separator<char>> tokens(value, char_separator<char>(" "));
					for(const auto &t : tokens)
						pt.push_back(atof(t.c_str()));
					if(pt.size() == 3)
					{
						pair<float, float> lonLat = UTMtoLL(pt[0], pt[1], 32);	//32 is germany's UTM zone
						polygonPts.push_back(glm::vec3((lonLat.first*100.0f - 5309.0f)*100.0f, pt[2], (lonLat.second*100.0f - 354.0f)*100.0f));
						buildingsPolygons_Easy.push_back(polygonPts.back());
						polygonIndices.push_back(buildingsPolygons_Easy.size());
					}
				}
				indices.push_back(polygonIndices);
				polygons.push_back(polygonPts);
			}
			//buildingsPolygons.push_back(polygons);
		}
	}
}*/

void LIC_GRAPHICS::loadMapPiece(string filename)
{
	rapidxml::file<> map1File(("resources/xmldata/" + filename).c_str());
	doc.parse<0>(map1File.data());
	
	xml_node<>* cityModel = doc.first_node("core:CityModel");
	for(xml_node<>* building = cityModel->first_node(); building; building = building->next_sibling())
	{
		if(strcmp(building->name(), "core:cityObjectMember") == 0)
		{
			vector<vector<glm::vec3> > polygons;
			xml_node<>* surfaces = building->first_node("bldg:Building")->first_node("bldg:lod1Solid")->first_node("gml:Solid")->first_node("gml:exterior")->first_node("gml:CompositeSurface");
			for(xml_node<>* surface = surfaces->first_node(); surface; surface = surface->next_sibling())
			{
				glm::vec2 avgLonLat;
				vector<glm::vec3> polygonPts;
				xml_node<>* curMapPolygon = surface->first_node("gml:Polygon")->first_node("gml:exterior")->first_node("gml:LinearRing");
				for(xml_node<>* pos = curMapPolygon->first_node(); pos; pos = pos->next_sibling())
				{
					vector<float> pt;
					string value(pos->value());
					tokenizer<char_separator<char>> tokens(value, char_separator<char>(" "));
					for(const auto &t : tokens)
						pt.push_back(atof(t.c_str()));
					if(pt.size() == 3)
					{
						glm::vec2 lonLat = UTMtoLL(pt[1], pt[0], 32);	//32 is germany's UTM zone
						if(polygonPts.size() == 0)
							avgLonLat = lonLat;
						else
							avgLonLat = (avgLonLat + lonLat)/2.0f;
						polygonPts.push_back(glm::vec3(lonLat.x*LIC_LON_FACTOR, pt[2]*0.1f, lonLat.y*LIC_LAT_FACTOR));
					}
				}
				if(polygonPts.size() == 5)
				{
					polygonPts.pop_back();
					vertices.insert(vertices.end(), polygonPts.begin(), polygonPts.end());
					glm::vec2 pxPos = (avgLonLat - noiseBBox.first) / (noiseBBox.second - noiseBBox.first) * 2048.0f;
					Color px;
					if(pxPos.x < 0.0f  ||  pxPos.y < 0.0f  ||  pxPos.x >= 2048.0f  ||  pxPos.y >= 2048.0f)
					{
						//printf("noiseBBoxDelta = %f / %f, avgLonLat = %f / %f, pxPos = %f / %f\n", (noiseBBox.second - noiseBBox.first).x, (noiseBBox.second - noiseBBox.first).y, avgLonLat.x, avgLonLat.y, pxPos.x, pxPos.y);
						px = Color::White;
					}
					else
						px = noise.getPixel(static_cast<unsigned int>(pxPos.x), static_cast<unsigned int>(pxPos.y));
					for(int i=0; i<4; i++)
					{
						normals.push_back(getNormal(vertices[vertices.size()-1], vertices[vertices.size()-2], vertices[vertices.size()-3]));
						colors.push_back(glm::vec3(px.r/255.0f, px.g/255.0f, px.b/255.0f));
					}
					//polygons.push_back(polygonPts);
				}
				//if(polygonPts.size() != 5)
				//	printf("Polygon with %d vertices!\n", polygonPts.size());
				//polygons.push_back(polygonPts);
			}
			//buildingsPolygons.push_back(polygons);
		}
	}
}

glm::vec2 LIC_GRAPHICS::UTMtoLL(double f, double f1, double j)		//f = NORTH, f1 = EAST
{
	double d = 0.99960000000000004f;
	double d1 = 6378137.0f;
	double d2 = 0.0066943799999999998f;

	double d4 = (1.0f - sqrt(1.0f-d2))/(1.0f + sqrt(1.0f - d2));
	double d15 = f1 - 500000.0f;
	double d16 = f;
	double d11 = ((j - 1.0f) * 6.0f - 180.0f) + 3.0f;

	double d3 = d2/(1.0f - d2);
	double d10 = d16 / d;
	double d12 = d10 / (d1 * (1.0f - d2/4.0f - (3.0f * d2 *d2)/64.0f - (5.0f * pow(d2, 3.0f))/256.0f));
	double d14 = d12 + ((3.0f*d4)/2.0f - (27.0f*pow(d4, 3.0f))/32.0f) * sin(2.0f*d12) + ((21.0f*d4*d4)/16.0f - (55.0f * pow(d4, 4.0f))/32.0f) * sin(4.0f*d12) + ((151.0f * pow(d4, 3.0f))/96.0f) * sin(6.0f*d12);
	double d13 = d14 * 180.0f / M_PI;
	double d5 = d1 / sqrt(1.0f - d2 * sin(d14) * sin(d14));
	double d6 = tan(d14)*tan(d14);
	double d7 = d3 * cos(d14) * cos(d14);
	double d8 = (d1 * (1.0f - d2))/pow(1-d2*sin(d14)*sin(d14), 1.5f);

	double d9 = d15/(d5 * d);
	double d17 = d14 - ((d5 * tan(d14))/d8)*(((d9*d9)/2.0f-(((5.0f + 3.0f*d6 + 10.0f*d7) - 4.0f*d7*d7-9.0f*d3)*pow(d9, 4.0f))/24.0f) + (((61.0f + 90.0f*d6 + 298.0f*d7 + 45.0f*d6*d6) - 252.0f*d3 - 3.0f * d7 *d7) * pow(d9, 6.0f))/720.0f); 
	d17 = d17 * 180.0f / M_PI;
	double d18 = ((d9 - ((1.0f + 2.0f * d6 + d7) * pow(d9, 3.0f))/6.0f) + (((((5.0f - 2.0f * d7) + 28.0f*d6) - 3.0f * d7 * d7) + 8.0f * d3 + 24.0f * d6 * d6) * pow(d9, 5.0f))/120.0f)/cos(d14);
	d18 = d11 + d18 * 180.0f / M_PI;
	
	return glm::vec2(d18, d17);
}

glm::vec3 LIC_GRAPHICS::getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	return glm::normalize(glm::cross(c-a, b-a));
}

void LIC_GRAPHICS::renderFonts(LIC_WINDOW *licWindow, LIC_SHADER *licFontShader, LIC_CAMERA *licCamera)
{
	static Clock fpsClock, showInfoClock;
	static bool showInfo = true;
	int fps = 1000000.0 / fpsClock.getElapsedTime().asMicroseconds();
	fpsClock.restart();
	
	if(font != NULL  &&  showInfo)
	{
		wchar_t infoText[200];
		GLuint vbo, tcbo, tbo;
		glm::vec2 origin = glm::vec2(5, 5);
		
		swprintf(infoText, L"lifeIsComplex    %d FPS\nCamera position: %.2f/%.2f/%.2f\nCamera angle:    %.2f/%.2f\nCamera speed:    %.2f/%.2f", fps, licCamera->position.x, licCamera->position.y, licCamera->position.z, licCamera->yaw, licCamera->pitch, licCamera->playerSpeedFB, licCamera->playerSpeedLR);
		
		SDL_Surface *info = TTF_RenderUNICODE_Blended_Wrapped(font, (unsigned short*)infoText, {0, 0, 0}, 1280);
		vector<float> vertices = { origin.x, origin.y,   origin.x+(float)info->w, origin.y,   origin.x+(float)info->w, origin.y+(float)info->h,   origin.x, origin.y+(float)info->h };
		vector<float> texcoord = { 0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f };
		
		glUseProgram(licFontShader->program);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		
		glGenBuffers(1, &tcbo);
		glBindBuffer(GL_ARRAY_BUFFER, tcbo);
		glBufferData(GL_ARRAY_BUFFER, texcoord.size()*sizeof(float), texcoord.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
		
		glGenTextures(1, &tbo);
		glBindTexture(GL_TEXTURE_2D, tbo);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info->w, info->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, info->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(licFontShader->program, "texFont"), 0);
		
		vMatrix = glm::ortho(0.0f, (float)licWindow->width, (float)licWindow->height, 0.0f, 0.00001f, 1000.0f);
		glUniformMatrix4fv(glGetUniformLocation(licFontShader->program, "vMatrix"), 1, GL_FALSE, &vMatrix[0][0]);
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_QUADS, 0, 4);
		
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &tcbo);
		glDeleteTextures(1, &tbo);
		SDL_FreeSurface(info);
	}
	
	if(Keyboard::isKeyPressed(Keyboard::F2)  &&  showInfoClock.getElapsedTime().asMilliseconds() > 200)
	{
		showInfo = !showInfo;
		showInfoClock.restart();
	}
}

void LIC_GRAPHICS::render(LIC_WINDOW *licWindow, LIC_SHADER *licShader, LIC_SHADER *licTextureShader, LIC_SHADER *licFontShader, LIC_CAMERA *licCamera)
{
	Clock fpsAdjustClock;
	float bgColor[] = { 0.0f, 0.71f, 1.0f, 1.0f };
	float depthOne  = 1.0f;
	
	glClearBufferfv(GL_COLOR, 0, bgColor);
	glClearBufferfv(GL_DEPTH, 0, &depthOne);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//light position for shadows: -10 30 45
	glm::vec3 lightDirection = glm::vec3(-0.5f, -1.0f, 0.3f);
	
	mMatrix = glm::mat4(1.0f);
	vMatrix = glm::rotate(glm::mat4(1.0f), (float)-(licCamera->pitch*(M_PI/180.0)), glm::vec3(1, 0, 0));
	vMatrix = glm::rotate(vMatrix, (float)-(licCamera->yaw*(M_PI/180.0)),   glm::vec3(0, 1, 0));
	vMatrix = glm::translate(vMatrix, -licCamera->position);
	pMatrix = glm::perspective(45.0f * (float)(M_PI/180.0), (float)licWindow->width/(float)licWindow->height, 0.1f, 100000.0f);
	
	glUseProgram(licShader->program);
	glUniformMatrix4fv(glGetUniformLocation(licShader->program, "mMatrix"),        1, GL_FALSE, &mMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(licShader->program, "vMatrix"),        1, GL_FALSE, &vMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(licShader->program, "pMatrix"),        1, GL_FALSE, &pMatrix[0][0]);
	glUniform3fv      (glGetUniformLocation(licShader->program, "lightDirection"), 1,           &lightDirection[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
	glDrawArrays(GL_QUADS, 0, numVertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	
	
	glUseProgram(licTextureShader->program);
	glUniformMatrix4fv(glGetUniformLocation(licTextureShader->program, "mMatrix"),        1, GL_FALSE, &mMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(licTextureShader->program, "vMatrix"),        1, GL_FALSE, &vMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(licTextureShader->program, "pMatrix"),        1, GL_FALSE, &pMatrix[0][0]);
	glUniform3fv      (glGetUniformLocation(licTextureShader->program, "lightDirection"), 1,           &lightDirection[0]);
	glUniform1i       (glGetUniformLocation(licTextureShader->program, "texBG"),                       0);
	
	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, bgNBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, bgTCBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bgTBO);
	glDrawArrays(GL_QUADS, 0, 4);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	

	renderFonts(licWindow, licFontShader, licCamera);
	
	SDL_GL_SwapWindow(licWindow->window);
	while(1000000.0/60.0 > fpsAdjustClock.getElapsedTime().asMicroseconds());		//Force 60 fps
}

void LIC_GRAPHICS::cleanup()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &nbo);
	glDeleteBuffers(1, &cbo);
	
	glDeleteBuffers(1, &bgVBO);
	glDeleteBuffers(1, &bgNBO);
	glDeleteBuffers(1, &bgTCBO);
	glDeleteTextures(1, &bgTBO);
	
	TTF_CloseFont(font);
	glDeleteVertexArrays(1, &vao);
}



#endif