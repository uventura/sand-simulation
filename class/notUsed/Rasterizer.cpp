#include "Rasterizer.hpp"

Rasterizer::Rasterizer(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer)
{
	//createShape(storage, vertexBuffer, indexBuffer, sizeIndexBuffer);
	//fillShape(storage);
}

void Rasterizer::interpolate(console3D::vec4 A, console3D::vec4 B)
{
	/*
		Let (x0, y0,z0) and (x1, y1, z1) be defined (as A and B).
		
		(y - y0)/(x - x0) = (y1 - y0)/(x1 - x0)
		
		y = (y1 - y0)(x - x0)/(x1 - x0) + y0
		x = (x1 - x0)(y - y0)/(y1 - y0) + x0
		[...]
	*/
	
	console3D::vec4 newVector(0,0,0,1);
	if(A.y != B.y)
	{
		int minY = std::min(A.y, B.y);
		int maxY = std::max(A.y, B.y);
		
		for(int y = minY; y <= maxY; ++y)
		{
			newVector.y = y;
			newVector.x = std::round((A.x - B.x)*(y - B.y)/(A.y - B.y) + B.x);
			newVector.z = std::round((A.z - B.z)*(y - B.y)/(A.y - B.y) + B.z);
			storage.push_back(newVector);
		}
	}
	else if(A.x != B.x)
	{
		int minX = std::min(A.x, B.x);
		int maxX = std::max(A.x, B.x);
		
		for(int x = minX; x <= maxX; ++x)
		{
			newVector.x = x;
			newVector.y = std::round((A.y - B.y)*(x - B.x)/(A.x - B.x) + B.y);
			newVector.z = std::round((A.z - B.z)*(x - B.x)/(A.x - B.x) + B.z);
			storage.push_back(newVector);
		}
	}
	else if(A.z != B.z)
	{
		int minZ = std::min(A.z, B.z);
		int maxZ = std::max(A.z, B.z);
		
		for(int z = minZ; z <= maxZ; ++z)
		{
			newVector.z = z;
			newVector.x = std::round((A.x - B.x)*(z - B.z)/(A.z - B.z) + B.x);
			newVector.y = std::round((A.y - B.y)*(z - B.y)/(A.z - B.z) + B.y);
			storage.push_back(newVector);
		}
	}
	
	std::sort(storage.begin(), storage.end(), [](console3D::vec4 A, console3D::vec4 B){return A.y < B.y;});
}

void Rasterizer::createShape(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer)
{
	int IBsize = sizeIndexBuffer/sizeof(unsigned int);
	for(int i = 0; i < IBsize; i += 2)
		interpolate(storage, vertexBuffer[indexBuffer[i]], vertexBuffer[indexBuffer[i + 1]]);	
}

void Rasterizer::fillShape(std::vector<console3D::vec4>& points)
{
	int pointsSize = points.size() - 1;
	console3D::vec4 vector(0,0,0,1);
	
	std::vector<console3D::vec4> inside;
	
	int begin, end;
	for(int i = 0; i < pointsSize - 1; ++i)
	{
		if(points[i].y == points[i + 1].y)
		{
			begin = std::min(points[i].x, points[i + 1].x);
			end = std::max(points[i].x, points[i + 1].x);
			
			for(int j = begin; j < end; ++j)
			{
				vector.x = j;
				vector.y = points[i].y;
				vector.z = std::round((points[i].z - points[i + 1].z)*(j - points[i + 1].x)/(points[i].x - points[i + 1].x) + points[i + 1].z);
	
				inside.push_back(vector);
			}
		}
	}
	
	// TODO: REMOVE DUPLICATES
	
	points.insert(points.end(), inside.begin(), inside.end());
}
