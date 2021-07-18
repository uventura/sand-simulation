#include "class/mainHeader.hpp"
#include "class/Screen.hpp"
#include "class/Rasterizer.hpp"

#define UNICODE
#include <Windows.h>

#include <deque>
#include <chrono>

struct particle
{
	float x, y;
	float velocity;
};

using namespace std::chrono;

void moveSand(particle& speck, float deltaTime, Screen& scr)
{
	//v² = v0² + 2as
	if(speck.y < scr.mHeight)
	{
		float yPos = speck.y + 1;
		float xPos = speck.x;
		
		if(scr.mElements[(unsigned int)(yPos * scr.mWidth + xPos)] == ' ')
		{
			speck.y = yPos;
		}
		else if(scr.mElements[(unsigned int)(yPos * scr.mWidth + xPos)] == '*')
		{
			if(xPos - 1 >= 0 and scr.mElements[(unsigned int)(yPos * scr.mWidth + xPos - 1)] == ' ')
			{
				xPos -= 1;
			}
			else if(xPos + 1 < scr.mWidth and scr.mElements[(unsigned int)(yPos * scr.mWidth + xPos + 1)] == ' ')
			{
				xPos += 1;
			}
			
			speck.x = xPos;
			speck.y = yPos - 1;
		}
	
	}
	else
		return;
		
	if(speck.y >= scr.mHeight)
	{
		speck.y = scr.mHeight - 1;
	}
}

void center(std::vector<console3D::vec4>& points, console3D::vec3& storage)
{
	storage.x = 0;
	storage.y = 0;
	storage.z = 0;
	
	for(int i = 0; i < points.size(); ++i)
	{
		storage.x += points[i].x;
		storage.y += points[i].y;
		storage.z += points[i].z;
	}
	
	storage.x /= points.size();
	storage.y /= points.size();
	storage.z /= points.size();
}

int main()
{	
	Screen scr;
	
	// Time
	high_resolution_clock::time_point change = high_resolution_clock::now();
	high_resolution_clock::time_point start = high_resolution_clock::now();
	high_resolution_clock::time_point moveSpot = high_resolution_clock::now();
	
	duration<float> deltaT;
	
	// Sand Particle
	std::deque<particle> sand;
	
	particle speck;
	speck.x = scr.mWidth / 2;
	speck.y = 0;
	speck.velocity = 0.1;
	
	float current = 0.5;
	bool forward = true;
	
	// Triangle
	unsigned int index[] = 
	{
		0, 1,
		1, 2,
		2, 0	
	};
	
	std::vector<console3D::vec4> triangle;
	triangle.push_back(console3D::vec4(10,10,0,1));
	triangle.push_back(console3D::vec4(20,10,0,1));
	triangle.push_back(console3D::vec4(15,20,0,1));
	
	// Setting Multiples Triangles
	const unsigned int numTriangles = 2;
	
	Rasterizer r;
	std::vector<console3D::vec4> triangles[numTriangles];
	
	console3D::Transform t;
	console3D::vec3 move(0, 0, 0);
	
	// 3 * O(n²)
	for(int i = 0; i < numTriangles; ++i)
	{
		move.x += (20 * i);
		
		// O(n)
		for(int j = 0; j < triangle.size(); ++j)
			t.translate(triangle[j], move);
		
		r.setObject(triangle, index, sizeof(index));

		// O(n)
		for(int j = 0; j < triangle.size(); ++j)
			t.translate(triangle[j], move * -1);
		
		triangles[i] = r.points; //O(n)
		r.clearBuffer();
	}
	
	// Execution
	while (true)
	{	
		deltaT = duration_cast<duration<float>>(high_resolution_clock::now() - start);
		if(deltaT.count() > 0.1)
		{
			sand.push_back(speck);
			start = high_resolution_clock::now();
		}
		
		deltaT = duration_cast<duration<float>>(high_resolution_clock::now() - change);
		if(deltaT.count() > 0.02)
		{	
			change = high_resolution_clock::now();
			
			scr.clear();
			
			for(int i = 0; i < numTriangles; ++i)
				scr.setElements(triangles[i]);
			
			for(int i = 0; i < sand.size(); ++i)
			{
				moveSand(sand[i], current, scr);
				scr.mElements[(unsigned int)std::round(scr.mWidth * sand[i].y + sand[i].x)] = '*';
			}
		}
		
		deltaT = duration_cast<duration<float>>(high_resolution_clock::now() - moveSpot);
		if(deltaT.count() > 0.2)
		{
			moveSpot = high_resolution_clock::now();
			if (forward)
				speck.x += 1;
			else
				speck.x -= 1;
			
			if(speck.x > scr.mWidth - 2)
				forward = false;
			else if(speck.x <= 0)
				forward = true;
		}
		
		scr.show();
	}
	// s = v0t - gt²/2
	return 0;
}
