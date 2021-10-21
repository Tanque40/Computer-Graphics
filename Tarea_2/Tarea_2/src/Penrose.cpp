#include "Penrose.h"
#include <iostream>

/**
 * Constructor of Penrose Class
 * 
 * @param _loops: The number of times for deflate tringles, MAX_RECOMENDED = 8
 * @param _origin: First coordinate for do a triangle
 * @param _degree: Just 36 degrees or 108 degrees
 * @param _height: The height of the tringle 
 * 
 */
Penrose::Penrose( int _loops, Coordinate _origin, int _degree, float _height ){

	loops = _loops;



	Coordinate origin = Coordinate( 0, 0 );
	Coordinate p = Coordinate( 1, 0 );
	for( int i = 0; i < 10; i++ ){
		Coordinate temp = Coordinate::RotatePoint( origin, 36, p );
		if( i % 2 == 0 ){
			triangles.push_back( Triangle( origin, p, temp, 0 ) );
		} else{
			triangles.push_back( Triangle( origin, temp, p, 0 ) );
		}
		p = temp;
	}

	NumTriangles = triangles.size();

}

/*
 * Clear the triangles vector 
 */
Penrose::~Penrose(){
	triangles.clear();
}

void Penrose::execute(){

	for( int i = 0; i < loops; i++ )

		triangles = deflate();

	NumTriangles = triangles.size();
}

/**
 * Create the deflate around the principal triangle 
 */
std::vector<Triangle> Penrose::deflate(){
	std::vector<Triangle> temp;

	for( const Triangle& t : triangles ){

		if( t.type ){

			// B + ( ( A - B) / PHI )
			Coordinate Q = Coordinate::sum( t.b, Coordinate::divide( Coordinate::diff( t.a, t.b ), PHI ) );
			// B + ( ( C - B) / PHI )
			Coordinate R = Coordinate::sum( t.b, Coordinate::divide( Coordinate::diff( t.c, t.b ), PHI ) );

			temp.push_back( Triangle( R, t.c, t.a, 1) );
			temp.push_back( Triangle( Q, R, t.b, 1 ) );
			temp.push_back( Triangle( R, Q, t.a, 0 ) );

		} else {

			Coordinate P = Coordinate::sum( t.a, Coordinate::divide( Coordinate::diff( t.b, t.a ), PHI ) );

			temp.push_back( Triangle( t.c, P, t.b, 0 ) );
			temp.push_back( Triangle( P, t.c, t.a, 1 ) );

		}

	}

	return temp;
}

float *Penrose::GetVertices(){
	int vectorSize = NumTriangles * 9;
	float* vertices = new float[ vectorSize ];

	int i = 0;
	for( Triangle t : triangles ){

		float *triangleVertices = t.getTriangleCoordinates();

		for( int j = 0; j < 9; j++ ){

			vertices[ i ] = triangleVertices[ j ];
			i++;

		}

	}

	return vertices;
}

float *Penrose::GetVerticesWithColors(){
	int vectorSize = NumTriangles * 18;
	float *vertices = new float[ vectorSize ];

	int i = 0;
	for( Triangle t : triangles ){

		float *triangleVertices = t.getTriangleCoordinatesWithColors();

		for( int j = 0; j < 18; j++ ){

			vertices[ i ] = triangleVertices[ j ];
			i++;
		}

	}

	return vertices;
}
