#include <math.h>
#include "Sphere.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sphere::Sphere()
{

	m_radius = 0;
	m_position = { 0, 0 };

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetRadius(int radius)
{

	m_radius = radius;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns position of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetPosition(int x, int y)
{

	m_position.x = x;
	m_position.y = y;

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Sphere::IsColliding(const Sphere& secondSphere)
{

	//first calculate the middle point of the sphere bound
	//we need this because the position is always top left
	//the centre point is the corner plus the radius offset
	SDL_Point centrePoint_1{ m_position.x + m_radius, m_position.y + m_radius  };
	SDL_Point centrePoint_2{ secondSphere.m_position.x + secondSphere.m_radius,
							 secondSphere.m_position.y + secondSphere.m_radius };

	//calculate the 'distance vector' between the two sphere positions
	SDL_Point distanceVector{ centrePoint_1.x - centrePoint_2.x,
							  centrePoint_1.y - centrePoint_2.y };
	
	//calculate the distance between both spheres by using the Pythagoras theorem
	int distance = (int)(sqrt((double)distanceVector.x * (double)distanceVector.x + 
		                      (double)distanceVector.y * (double)distanceVector.y));

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}