#ifndef LIFEISCOMPLEX_CAMERA_H
#define LIFEISCOMPLEX_CAMERA_H



void LIC_CAMERA::move(float direction, float speed)
{
	float radians = (yaw + direction) * (M_PI / 180.0f);
	
	position.x -= sin(radians) * speed;
	position.z -= cos(radians) * speed;
}

LIC_CAMERA::LIC_CAMERA()
{
	//constants
	maxPlayerSpeed = 5.0f;
	playerAcceleration = 0.04f;
	playerSlowdown = 0.04f;
	
	//variables
	position = glm::vec3(111122.0f, 8.0f, 592029.0f);
	yaw      = 225.0f;
	pitch    = -90.0f;
	
	cameraSpeed = 0.5f;
	playerSpeedFB = 0.0f;
	playerSpeedLR = 0.0f;
	playerSpeedUD = 0.5f;
}

void LIC_CAMERA::update(LIC_WINDOW *licWindow)
{
	yaw   -= cameraSpeed * (float)licWindow->mouseXChg;
	pitch -= cameraSpeed * (float)licWindow->mouseYChg;
	licWindow->mouseXChg = 0;
	licWindow->mouseYChg = 0;
	
	if(yaw < 0.0f)
		yaw += 360.0f;
	else if(yaw > 360.0f)
		yaw -= 360.0f;
	if(pitch > 90.0f)
		pitch = 90.0f;
	else if(pitch < -90.0f)
		pitch = -90.0f;
		
	bool k[] = { Keyboard::isKeyPressed(Keyboard::W),
				 Keyboard::isKeyPressed(Keyboard::A),
				 Keyboard::isKeyPressed(Keyboard::S),
				 Keyboard::isKeyPressed(Keyboard::D),
				 Keyboard::isKeyPressed(Keyboard::Space),
				 Keyboard::isKeyPressed(Keyboard::LShift),
				 Keyboard::isKeyPressed(Keyboard::RShift) };
		
	if(k[0] && !k[2])		//W & !S
	{
		if(playerSpeedFB < maxPlayerSpeed)
			playerSpeedFB += playerAcceleration * (playerSpeedFB<0.0f ? 3.0f : 1.0f);
	}
	if(k[2] && !k[0])		//S & !W
	{
		if(playerSpeedFB > -maxPlayerSpeed)
			playerSpeedFB -= playerAcceleration * (playerSpeedFB>0.0f ? 3.0f : 1.0f);
	}
	
	if(k[1] && !k[3])		//A & !D
	{
		if(playerSpeedLR < maxPlayerSpeed)
			playerSpeedLR += playerAcceleration * (playerSpeedLR<0.0f ? 3.0f : 1.0f);
	}
	if(k[3] && !k[1])		//D & !A
	{
		if(playerSpeedLR > -maxPlayerSpeed)
			playerSpeedLR -= playerAcceleration * (playerSpeedLR>0.0f ? 3.0f : 1.0f);
	}
	
	if(k[4])				//Space
		position.y += playerSpeedUD;
	if(k[5] || k[6])		//LShift | RShift
		position.y -= playerSpeedUD;
		
	move( 0.0f, playerSpeedFB);
	move(90.0f, playerSpeedLR);
		
	if(!k[0] && !k[2])		//!W & !S
	{
		if(playerSpeedFB >= 0.0f  &&  playerSpeedFB-playerSlowdown < 0.0f   ||   playerSpeedFB < 0.0f  &&  playerSpeedFB+playerSlowdown > 0.0f)
			playerSpeedFB = 0.0f;
		else
		{
			if(playerSpeedFB > 0.0f)
				playerSpeedFB -= playerSlowdown;
			else if(playerSpeedFB < 0.0f)
				playerSpeedFB += playerSlowdown;
		}
	}
					
	if(!k[1]  &&  !k[3])	//!A & !D
	{
		if(playerSpeedLR >= 0.0f  &&  playerSpeedLR-playerSlowdown < 0.0f   ||   playerSpeedLR < 0.0f  &&  playerSpeedLR+playerSlowdown > 0.0f)
			playerSpeedLR = 0.0f;
		else
		{
			if(playerSpeedLR > 0.0f)
				playerSpeedLR -= playerSlowdown;
			else if(playerSpeedLR < 0.0f)
				playerSpeedLR += playerSlowdown;
		}
	}
}



#endif