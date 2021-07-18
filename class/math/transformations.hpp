#pragma once
namespace console3D
{
	struct Transform
	{
		inline float toRad(float degrees){return (degrees * PI) / 180;}
	
		void rotate(console3D::vec4& vector, console3D::vec3 axisAngle)
		{
			/*
				     Y
				 	 .
				 	 .
				 	 .
				 	 .
				 	 .
				 	 . . . . . . X (When you rotate this axis is like the axis stays in the same coordinate and the others rotate)
				   .
				 .
			   .
			 .
		   Z	
			*/
			
			// In Axis you define the angle in each axis.
			
			float vectorBefore[3] = {vector.x, vector.y, vector.z};
			axisAngle.x = toRad(axisAngle.x);
			axisAngle.y = toRad(axisAngle.y);
			axisAngle.z = toRad(axisAngle.z);
			
			// X Rotation
			vector.y = vector.y * cos(axisAngle.x) - vector.z * sin(axisAngle.x);
			vector.z = vector.y * sin(axisAngle.x) + vector.z * cos(axisAngle.x);
			
			// Y Rotation
			vector.x = vector.x * cos(axisAngle.y) + vector.z * sin(axisAngle.y);
			vector.z = -vector.x * sin(axisAngle.y) + vector.z * cos(axisAngle.y);
			
			// Z Rotation
			vector.x = vector.x * cos(axisAngle.z) - vector.y * sin(axisAngle.z);
			vector.y = vector.x * sin(axisAngle.z) + vector.y * cos(axisAngle.z);	
		}
		
		void translate(console3D::vec4& vector, console3D::vec3 movement)
		{
			vector.x += movement.x;
			vector.y += movement.y;
			vector.z += movement.z;
		}
		
		void scale(console3D::vec4& vector, console3D::vec3 scaleFactor)
		{
			vector.x *= scaleFactor.x;
			vector.y *= scaleFactor.y;
			vector.z *= scaleFactor.z;
		}
	};
}
