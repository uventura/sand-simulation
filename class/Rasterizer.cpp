#include "Rasterizer.hpp"

void Rasterizer::setObject(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer, const bool fill)
{
	createShape(vertexBuffer, indexBuffer, sizeIndexBuffer);
	if(fill)
		fillShape(points);
}

void Rasterizer::interpolate(std::vector<console3D::vec4>& storage, console3D::vec4 A, console3D::vec4 B)
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
	/*
	else if(A.z != B.z)
	{
		int minZ = std::min(A.z, B.z);
		int maxZ = std::max(A.z, B.z);
		
		for(int z = minZ; z <= maxZ; ++z)
		{
			newVector.z = z;
			newVector.x = std::round((A.x - B.x)*(z - B.z)/(A.z - B.z) + B.x);
			newVector.y = std::round((A.y - B.y)*(z - B.y)/(A.z - B.z) + B.y);
			points.push_back(newVector);
		}
	}*/
	
	//std::sort(storage.begin(), points.end(), [](console3D::vec4 A, console3D::vec4 B){return A.y < B.y;});
}

void Rasterizer::createShape(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer)
{
	int IBsize = sizeIndexBuffer/sizeof(unsigned int);
	
	for(int i = 0; i < vertexBuffer.size(); i += 1)
	{
		vertexBuffer[i].x = std::round(vertexBuffer[i].x);
		vertexBuffer[i].y = std::round(vertexBuffer[i].y);
		vertexBuffer[i].z = std::round(vertexBuffer[i].z);
	}
	
	for(int i = 0; i < IBsize; i += 2)
	{	
		interpolate(points, vertexBuffer[indexBuffer[i]], vertexBuffer[indexBuffer[i + 1]]);
	}
	
	std::sort(points.begin(), points.end(), [](console3D::vec4 A, console3D::vec4 B){return A.y < B.y;});
}

void Rasterizer::fillShape(std::vector<console3D::vec4>& storage)
{
	int storageSize = storage.size() - 1;
	console3D::vec4 vector(0,0,0,1);
	
	std::vector<console3D::vec4> inside;
	
	int begin, end;
	for(int i = 0; i < storageSize - 1; ++i)
	{
		if(storage[i].y == storage[i + 1].y)
		{
			begin = std::min(storage[i].x, storage[i + 1].x);
			end = std::max(storage[i].x, storage[i + 1].x);
			
			for(int j = begin; j < end; ++j)
			{
				vector.x = j;
				vector.y = storage[i].y;
				vector.z = std::round((storage[i].z - storage[i + 1].z)*(j - storage[i + 1].x)/(storage[i].x - storage[i + 1].x) + storage[i + 1].z);
	
				inside.push_back(vector);
			}
		}
	}
	
	// TODO: REMOVE DUPLICATES
	
	storage.insert(storage.end(), inside.begin(), inside.end());
}
