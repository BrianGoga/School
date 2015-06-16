///////////////////////////////////////////////////////////////////////////////
// Project 4
// CS 479
// Brian Goga
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define PRINT_CSV 0

//functions
vector<Point2f> readImagePoints(const char[]);
vector<Point3f> readWorldPoints(const char[]);

int main()
{

////////////////////////////////////////////////////////////////////////////////////////////
//Variables
///////////////////////////////////////////////////////////////////////////////////////////
char buffer [128];
double calibError;
double singleSum = 0.0;

vector< vector<Point2f> > imgCoords;
vector< vector<Point3f> > objCoords;
vector<Mat> rvecs, tvecs;

Mat cameraMatrix, distCoeffs;
Mat pointToMat(3, 1, CV_64FC1);

////////////////////////////////////////////////////////////////////////////////////////////
//Initialize Vectors
///////////////////////////////////////////////////////////////////////////////////////////
for( int i = 1; i <= 15; ++i )
	{
		// Read the pixel file
		sprintf( buffer, "data/pixel%02d.txt", i );
		imgCoords.push_back( readImagePoints(buffer) );

		// Read the world file
		sprintf( buffer, "data/world%02d.txt", i );
		objCoords.push_back( readWorldPoints(buffer) );
	}

////////////////////////////////////////////////////////////////////////////////////////////
//Calibrate Camera
///////////////////////////////////////////////////////////////////////////////////////////
calibError = calibrateCamera( objCoords, imgCoords, Size(640, 480), cameraMatrix, distCoeffs,
										rvecs, tvecs );


////////////////////////////////////////////////////////////////////////////////////////////
//Loop through images looking for/calculating errors
///////////////////////////////////////////////////////////////////////////////////////////
for( int i = 0; i < 15; ++i )
	{
		// Project points using projectPoints
		vector<Point2f> output;
		projectPoints( objCoords[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, output );

		// Loop through the output from projectPoints
		singleSum = 0.0;
		for( int j = 0; j < 96; ++j )
		{
			//calculate error rate
			double err = sqrt( 
				pow(output[j].x - imgCoords[i][j].x, 2) + 
				pow(output[j].y - imgCoords[i][j].y, 2) );
			singleSum += err;

			#if PRINT_CSV == 1
			cout << i << ',' << err << endl;
			#endif
		}

		#if PRINT_CSV == 0
		cout << "Image " << i+1 << ": " << singleSum / 96.0 << endl;
		#endif
	}

  //we're out of here...
  return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////
//Functions
///////////////////////////////////////////////////////////////////////////////////////////
vector<Point2f> readImagePoints(const char filename[])
{
	// Initialize variables
	Point2f temp(0, 0);
	vector<Point2f> result;

	// Open the file
	fstream fin(filename);

	// Loop
	for( int i = 0; i < 96; ++i )
	{
		// Read and push back the point
		fin >> temp.x >> temp.y;
		result.push_back(temp);
	}

	// Return
	return result;
}

vector<Point3f> readWorldPoints(const char filename[])
{
	// Initialize variables
	Point3f temp(0, 0, 0);
	vector<Point3f> result;

	// Open the file
	fstream fin(filename);

	// Loop
	for( int i = 0; i < 96; ++i )
	{
		// Read and push back the point
		fin >> temp.x >> temp.y;
		result.push_back(temp);
	}

	// Return
	return result;
}