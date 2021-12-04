#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#define PHI (1 + sqrt(5)) / 2

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Coordinate{
	float x;
	float y;
	float z;

	Coordinate(){
		x = 0;
		y = 0;
		z = 0;
	}

	Coordinate( float _x, float _y ){
		x = _x;
		y = _y;
		z = 0;
	}

	Coordinate( float _x, float _y , float _z){
		x = _x;
		y = _y;
		z = _z;
	}


	// @return the vectorial sum of two coordinates
	static Coordinate sum(Coordinate a, Coordinate b){
		return Coordinate( a.x + b.x, a.y + b.y, a.z + b.z );
	}

	// @return the vectorial diference of two coordinates
	static Coordinate diff( Coordinate a, Coordinate b ){
		return Coordinate( a.x - b.x, a.y - b.y, a.z - b.z );
	}

	// @return the divition of both values in coordinate by b
	static Coordinate divide( Coordinate a, float b ){ 
		return Coordinate( a.x / b, a.y / b, a.z / b );
	}

	// @return the rotation point p around some origin point
	static Coordinate RotatePoint( Coordinate origin, float angle, Coordinate p ){
		float rad = angle * M_PI / 180;
		float px = p.x;
		float py = p.y;

		float s = sin( rad );
		float c = cos( rad );

		// translate point back to origin:
		px -= origin.x;
		py -= origin.y;

		// rotate point
		float xnew = px * c - py * s;
		float ynew = px * s + py * c;

		// translate point back:
		px = xnew + origin.x;
		py = ynew + origin.y;
		return Coordinate( px, py, 0 );
	}

	// @return the rotation point p around some origin point r3 we can select the axis (X, Y, Z, XY, XZ, YZ)
	static Coordinate RotatePoint3D( Coordinate origin, float angle, Coordinate p, std::string axis  ){
		float rad = angle * M_PI / 180;
		glm::vec4 rotated_point = glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f );
		glm::vec4 point_to_rotate = glm::vec4(p.x - origin.x, p.y - origin.y, p.z - origin.z, 0.0f );
		glm::vec3 axis_to_rotate;

		
		if( axis == "X" ){
			axis_to_rotate = glm::vec3( 1, 0, 0 );
		} else if( axis == "Y" ){
			axis_to_rotate = glm::vec3( 0, 1, 0 );
		} else if( axis == "Z" ){
			axis_to_rotate = glm::vec3( 0, 0, 1 );
		} else if( axis == "XY" ){
			axis_to_rotate = glm::vec3( 1, 1, 0 );
		} else if( axis == "XZ" ){
			axis_to_rotate = glm::vec3( 1, 0, 1 );
		} else{
			axis_to_rotate = glm::vec3( 0, 1, 1 );
		}

		glm::mat4 identity = glm::mat4( 1.0f );

		rotated_point = point_to_rotate * glm::rotate( identity, rad, axis_to_rotate );

		return Coordinate( rotated_point.x, rotated_point.y, rotated_point.z );
	}

	// @return distance between to coordinates
	static float dist( Coordinate a, Coordinate b ){
		return sqrt( pow( ( a.x - b.x ), 2 ) + pow( ( a.y - b.y ), 2 ) + pow( ( a.z - b.z ), 2 ) );
	}
};

struct Triangle{
	Coordinate a;
	Coordinate b;
	Coordinate c;
	//  0 for 36� iso triangle, 1 for 108 degree iso triangle
	int type; 

	// Default type = 0
	Triangle(Coordinate pointA, Coordinate pointB, Coordinate pointC ){
		a = pointA;
		b = pointB;
		c = pointC;
		type = 0;
	}

	// Default t = type, 0 for green triangles, 1 for blue triangles
	Triangle( Coordinate pointA, Coordinate pointB, Coordinate pointC, int t ){
		a = pointA;
		b = pointB;
		c = pointC;
		type = t;
	}

	float *getTriangleCoordinates(){
		float coordinates[] = {
			a.x, a.y, a.z,
			b.x, b.y, b.z,
			c.x, c.y, c.z,
		};

		return coordinates;
	}

	// Depends of type 1 for blue, 0 for red
	float *getTriangleCoordinatesWithColors(){
		float coordinates[ 18 ];

		if( type ){

			// Position
			coordinates[ 0 ] = a.x;
			coordinates[ 1 ] = a.y;
			coordinates[ 2 ] = a.z;
			// Color
			coordinates[ 3 ] = 0.204;
			coordinates[ 4 ] = 0.275;
			coordinates[ 5 ] = 0.722;
			
			// Position
			coordinates[ 6 ] = b.x;
			coordinates[ 7 ] = b.y;
			coordinates[ 8 ] = b.z;
			// Color
			coordinates[ 9 ] = 0.204;
			coordinates[ 10 ] = 0.275;
			coordinates[ 11 ] = 0.722;

			// Position
			coordinates[ 12 ] = c.x;
			coordinates[ 13 ] = c.y;
			coordinates[ 14 ] = c.z;
			// Color
			coordinates[ 15 ] = 0.204;
			coordinates[ 16 ] = 0.275;
			coordinates[ 17 ] = 0.722;

		} else{

			// Position
			coordinates[ 0 ] = a.x;
			coordinates[ 1 ] = a.y;
			coordinates[ 2 ] = a.z;
			// Color
			coordinates[ 3 ] = 0.804;
			coordinates[ 4 ] = 0.141;
			coordinates[ 5 ] = 0.557;

			// Position
			coordinates[ 6 ] = b.x;
			coordinates[ 7 ] = b.y;
			coordinates[ 8 ] = b.z;
			// Color
			coordinates[ 9 ] = 0.804;
			coordinates[ 10 ] = 0.141;
			coordinates[ 11 ] = 0.557;

			// Position
			coordinates[ 12 ] = c.x;
			coordinates[ 13 ] = c.y;
			coordinates[ 14 ] = c.z;
			// Color
			coordinates[ 15 ] = 0.804;
			coordinates[ 16 ] = 0.141;
			coordinates[ 17 ] = 0.557;

		}
		

		return coordinates;
	}

	// @return a new issoceles triangle from point a, angle at point and height h
	static Triangle iso(Coordinate a, int degree, float h){
		float rad = degree * M_PI / 180;
		float dx = tan( rad / 2 ) * h;
		Coordinate b( a.x - dx, a.y + h);
		Coordinate c( a.x + dx, a.y + h );

		if( degree == 36 ){
			return Triangle( a, b, c, 0 );
		} else if ( degree == 108 ){
			return Triangle( a, b, c, 1 );
		} else{
			return Triangle( a, b, c);
		}

	}
};

class Penrose{
private:
	int loops;
	std::vector<Triangle> triangles;
	int NumTriangles;

public:
	Penrose(int _loops, Coordinate _origin, int _degree, float _height);
	~Penrose();

	void execute();
	std::vector<Triangle> deflate();
	void DoIt3D();
	float *GetVertices();
	float *GetVerticesWithColors();

	inline const int GetNumTriangles() const{ return NumTriangles; }

};