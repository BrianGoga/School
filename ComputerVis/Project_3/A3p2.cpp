///////////////////////////////////////////////////////////////////////////////
// Project 3
// CS 479
// Brian Goga
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "Image.cpp"   //class of images

using namespace std;

//functions

//give it xx,yy,xy and the alpha, in that order
//bool is used for thresholding, if true then R(aw) 
//will be thresholded by 1% of observed value
Image compRaw(Image, Image, Image, double, bool); 

//pass RAw and it will find local max of 3x3 grid
Image compLocalMax(Image);

//Function takes the RAw local max and overlays it on the original image
//pass it the RAw max first and then the original image
Image pictureOverlay(Image, Image, int);

//This functions does pretty much everything that A3p1 does except print images
//pass it the value for the first derivative, the value for the gaussian and 
//then the image you wish to detect corners on and finally the scale
Image cornerDetector(double, double, Image, int);

//structs
struct Scale
{
	float Sigma;
	float Der;
	Image Scaledimage;

};

int main()
{
//variables
char input[20];
char buffer[5];
string output = "out_";
Image picture;
Scale* G_SS = new Scale[17];

//Get file name
cout<<"Enter image name:";
cin>>input;

//read in image
picture.readImage(input);

//Fill G_SS
for (int i = 0; i < 17; ++i)
{
	//doing calculations
	G_SS[i].Sigma = 1.5 * pow(1.2, i);
	G_SS[i].Der = 0.7 * G_SS[i].Sigma;

	//call cornerDector to find keypoints
	G_SS[i].Scaledimage = cornerDetector(G_SS[i].Der, G_SS[i].Sigma, picture, i);

	//print image
	sprintf(buffer, "%d", i);
	G_SS[i].Scaledimage.writeImage((output + string(buffer) + ".pgm").c_str());

}


return 0;
}


//Functions
Image compRaw(Image xx, Image yy, Image xy, double alpha, bool thrsh)
{
  //variables
  int length = xx.getHeight();
  int width = xx.getWidth();
  double s1, s2, diff, trace;
  Image RAw (width, length);
  double obsMax = -9999.9; //super small number

  //Calculate RAw
  //loop through the whole picture
  for (int i = 0; i < length; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      //get determinants
      //det of xx * yy
      s1 = (xx.at(i,j) * yy.at(i,j));
      //det of xy * xy
      s2 = (xy.at(i,j) * xy.at(i,j));
      //calculate difference
      diff = s1 - s2;

      //calculate trace, going to need this later
      trace = xx.at(i,j) + yy.at(i,j);
      //get RAw at the current location
      //Told you we were going to need the trace
      RAw.at(i,j) = diff - (trace * alpha * trace);

      //Keep track of the max
      if( RAw.at(i,j) > obsMax)
      {
        obsMax = RAw.at(i,j);
      }

    }
  }

if(thrsh == true)
{
  //Alright, this is where we threshold
  //gotta get 1% of observed max
  obsMax = obsMax * 0.01;

  //have to loop through image and threshold all the values
  for (int i = 0; i < length; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      //check if current value is greater than 1% observed, otherwise set 0
      if(RAw.at(i,j) <= obsMax)
      {
        RAw.at(i,j) = 0.0;
      }
    }
  }
}

//return the RAw image
return RAw;

}


Image compLocalMax(Image RAw)
{
  //variables
  int length = RAw.getHeight();
  int width = RAw.getWidth();
  float obsMax;
  Image maxRAw(width, length);

  //loop through the whole image
  for(int i = 0; i < length; ++i)
  {
    for(int j = 0; j < width; ++j)
    {
      //make max super small
      obsMax = -9999.9;
      //get max in 3x3 neighborhood around current pixel
      for(int m = -1; m < 2; ++m)
      {
        for(int n = -1; n < 2; ++n)
        {
          //check the bounds of the image
          if( (i+m) >= 0 && ((i+m) < length) && ((j+n) >= 0) && ((j+n) < width) )
          {
            //get max of current max and current pixel
            obsMax = max(obsMax, RAw.at( (i+m), (j+n) ) );
          }
        }
      }

      //reassign pixel values to only keep local max
      if(RAw.at(i,j) != obsMax)
      {
        maxRAw.at(i,j) = 0.0;
      }
      else
      {
        maxRAw.at(i,j) = obsMax;
      }
    }
  }

return maxRAw;
}

Image pictureOverlay(Image maxPnts, Image scr, int scale)
{
  //variables
  int length = scr.getHeight();
  int width = scr.getWidth();
  int radius = 2 * scale;
  Image Overlay = scr;

  //loop through maxPnts looking for points
  for(int i = 0; i < length; ++i)
  {
    for(int j = 0; j < width; ++j)
    {
      if(maxPnts.at(i, j) > 0)
      {
        //move through neighbors 
        for(int m = 0; m < 3; ++m)
        {
          //check bounds, if good then draw an "X"
          if((i + m) >=0 && (i + m) < length && (j + m) >= 0 && (j + m)< width)
          {
            Overlay.at(i + m, j + m) = 255;
          }
          if((i + m) >=0 && (i + m) < length && (j - m) >= 0 && (j - m)< width)
          {
            Overlay.at(i + m, j - m) = 255;
          }
          if((i - m) >=0 && (i - m) < length && (j + m) >= 0 && (j + m)< width)
          {
            Overlay.at(i - m, j + m) = 255;
          }
          if((i - m) >=0 && (i - m) < length && (j - m) >= 0 && (j - m)< width)
          {
            Overlay.at(i - m, j - m) = 255;
          }
        }
        //draw circle around point
        for(int k = 0; k < length; ++k)
        {
        	for(int l = 0; l < width; ++l)
        	{
        		int d = sqrt(pow((i-k),2) + pow((j-l),2));
        		if ( d == radius)
        		{
        		  Overlay.at(k, l) = 255;	
        		}
        	}
        }
      }
    }
  }

return Overlay;
}

Image cornerDetector(double firstVal, double gaussVal, Image picture, int scale)
{
	//variables
	Mask firstDeriv;
	Mask gaussMask;

	Image x;
	Image y;
	Image xx;
	Image yy;
	Image xy;
	Image xxG;
	Image yyG;
	Image xyG;
	Image RAw;
	Image RAwMax;
	Image detected;

	//create first derivative
	firstDeriv.buildGaussFirstDeriv(firstVal);

	//create x and y of image
	x = picture.convolveX(firstDeriv);
	y = picture.convolveY(firstDeriv);

	//create xx, yy, xy
	xx = x.multiply(x);
	yy = y.multiply(y);
	xy = x.multiply(y);

	//convolve xx, yy, xy with gaussian
	gaussMask.buildGauss(gaussVal);
	xxG = xx.convolve(gaussMask);
	yyG = yy.convolve(gaussMask);
	xyG = xy.convolve(gaussMask);

	//Create RAw with thresh
	RAw = compRaw(xxG, yyG, xyG, 0.06, true);

	//Find local maxima
	RAwMax = compLocalMax(RAw);

	//overlay the images
	detected = pictureOverlay(RAwMax, picture, scale);


return detected;
}








