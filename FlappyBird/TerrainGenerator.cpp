#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(float width, float height)
{
	m_width = width;
	m_height = height;
	xPos1 = width + width * 0.5f;
	xSpeed = -2.f;
	obstacles.push_back(Obstacle(200.0f, 300.0f, m_width, m_height));
	obstacles.push_back(Obstacle(200.0f, 400.0f, m_width, m_height));
}

void TerrainGenerator::Generate(GLuint shaderID, float deltaTime)
{
	if (xPos1 < -m_width / 2 - obstacles[0].sizeX / 2)
	{
		xPos1 = m_width / 2 + obstacles[0].sizeX / 2;
		obstacles[0].Regenerate();
	}

	if (obstacles.size() != 0)
	{
		obstacles[0].Draw(xPos1, -m_height / 2 + obstacles[0].sizeY / 2, shaderID);
		obstacles[1].Draw(xPos1, m_height / 2 - obstacles[1].sizeY / 2, shaderID);
	}

	xPos1 += xSpeed;

	if (xSpeed > -20.0f && xSpeed < 0.0f)
		xSpeed -= deltaTime * 0.5f;
}

bool TerrainGenerator::DetectCollision(float objX, float objY, float sizeX, float sizeY)
{

	for (int i = 0; i < 2; i++)
	{
		float playerTop = objY + sizeY / 2;
		float playerBottom = objY - sizeY / 2;
		float playerLeft = objX - sizeX / 2;
		float playerRight = objX + sizeX / 2;

		float obstacleTop = obstacles[i].posY + obstacles[i].sizeY / 2;
		float obstacleRight = obstacles[i].posX + obstacles[i].sizeX / 2;
		float obstacleLeft = obstacles[i].posX - obstacles[i].sizeX / 2;
		float obstacleBottom = obstacles[i].posY - obstacles[i].sizeY / 2;

		if (playerLeft < obstacleRight &&
			playerRight > obstacleLeft &&
			playerTop > obstacleBottom &&
			playerBottom < obstacleTop)
			return true;
	}
	return false;
}

void TerrainGenerator::setSpeed(float speed)
{
	xSpeed = speed;
}
