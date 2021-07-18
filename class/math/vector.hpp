#pragma once
#include <iostream>
namespace console3D
{
	struct vec3
	{
		float x, y, z;
		vec3(float xCoord, float yCoord, float zCoord):x(xCoord), y(yCoord), z(zCoord){};
		
		inline vec3 operator +(vec3 B)
		{
			return vec3(x + B.x, y + B.y, z + B.z);
		}
		
		inline vec3 operator - (vec3 B)
		{
			return vec3(x - B.x, y - B.y, z - B.z);
		}
		
		inline vec3 operator * (const float alpha)
		{
			return vec3(alpha * x, alpha * y, alpha * z);
		}
		
		friend std::ostream& operator<<(std::ostream& os, const vec3& vector)
		{
			os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
			return os;
		}				
	};
	
	struct vec4
	{
	public:
		float x, y, z, w;
		vec4(float xCoord, float yCoord, float zCoord, float wCoord):x(xCoord), y(yCoord), z(zCoord), w(wCoord){};
		
		inline vec4 operator +(vec4 B)
		{
			return vec4(x + B.x, y + B.y, z + B.z, w + B.w);
		}
		
		inline vec4 operator - (vec4 B)
		{
			return vec4(x - B.x, y - B.y, z - B.z, w - B.w);
		}
		
		inline vec4 operator * (const float alpha)
		{
			return vec4(alpha * x, alpha * y, alpha * z, alpha * w);
		}
		
		inline bool operator == (vec4 B)
		{
			return x == B.x and y == B.y and z == B.z and w == B.w;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const vec4& vector)
		{
			os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ',' << vector.w << ')';
			return os;
		}
	};
}
