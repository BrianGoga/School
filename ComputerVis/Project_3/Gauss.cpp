#include <math.h>

#define pi 3.141592653589793

float* Gauss( float sigma, int size )
{
	// Initialize variables
	float sum;
	float constant = 1.0000 / (sigma * sqrt(2.0000 * pi));
	float powerConstant = 1.0000 / (2 * sigma * sigma);

	// Create the array
	float* array = new float[size];

	// Loop
	for( int i = 0; i < size; i++ )
	{
		float x = i - (size / 2);
		array[i] = constant * exp( -(x * x * powerConstant) );
		sum += array[i];
	}

	// Divide by sum
	for( int i = 0; i < size; i++ )
	{
		array[i] /= sum;
	}

	// Return
	return array;
}

float* Gauss_Deriv1(float sigma, int size)
{
	float cst = 1.0 / (sigma * sigma * sigma * sqrt(2.0 * pi));
	float tssq = -1.0 / (2.0 * sigma * sigma);

	// Create the array
	float* array = new float[size];

	for( int i = 0; i < size; i++ ) 
	{
		float x = i - size/2;
		array[i] = -x * cst * exp(x * x * tssq);
	}

	// Return
	return array;
}