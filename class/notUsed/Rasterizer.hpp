#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>

#define PI 3.14159265359
#include "math/vector.hpp"
/*
#include "math/transformations.hpp"
#include "Timer.hpp"*/

class Rasterizer
{
private:
	void interpolate(console3D::vec4 A, console3D::vec4 B);
	void createShape(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer);
	void fillShape(std::vector<console3D::vec4>& points);
public:
	std::vector<console3D::vec4> storage;
	//Rasterizer(std::vector<console3D::vec4> vertexBuffer, unsigned int* indexBuffer, unsigned int sizeIndexBuffer);
};
