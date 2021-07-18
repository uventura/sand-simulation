#pragma once
#include "mainHeader.hpp"

class Rasterizer
{
private:
	void interpolate(std::vector<console3D::vec4>& storage, console3D::vec4 A, console3D::vec4 B);
	void createShape(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer);
	void fillShape(std::vector<console3D::vec4>& points);

public:	
	std::vector<console3D::vec4> points; // The Shape Resultant
	
	// sizeIndexBuffer -> sizeof(indexBuffer);
	void setObject(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer, const bool fillShape = true);
	
	inline void clearBuffer(){points.clear();};
};
