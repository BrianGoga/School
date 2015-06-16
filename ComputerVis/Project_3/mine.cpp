///////////////////////////////////////////////////////////////////////////////
// Project 3
// CS 479
// Brian Goga
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
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
Image pictureOverlay(Image, Image);


int main()
{

//variables
//filenames (had to break them up so I know what goes where)
  //input images
char in1[10] = "Test1.pgm";
char in2[10] = "Test2.pgm";
char in3[10] = "Test3.pgm";
  //input convolved in x direction
char xD1[10] = "1xD.pgm";
char xD2[10] = "2xD.pgm";
char xD3[10] = "3xD.pgm";
  //input convolved in y direction
char yD1[10] = "1yD.pgm";
char yD2[10] = "2yD.pgm";
char yD3[10] = "3yD.pgm";
  //x direction multiplied with self
char xx1P[10] = "1xx.pgm";
char xx2P[10] = "2xx.pgm";
char xx3P[10] = "3xx.pgm";
  //y direction multiplied with self
char yy1P[10] = "1yy.pgm";
char yy2P[10] = "2yy.pgm";
char yy3P[10] = "3yy.pgm";
  //x direction multiplied with y
char xy1P[10] = "1yy.pgm";
char xy2P[10] = "2yy.pgm";
char xy3P[10] = "3yy.pgm";
  //xx convolved with guassian
char xx1PG[10] = "1xxG.pgm";
char xx2PG[10] = "2xxG.pgm";
char xx3PG[10] = "3xxG.pgm";
  //yy convolved with gaussian
char yy1PG[10] = "1yyG.pgm";
char yy2PG[10] = "2yyG.pgm";
char yy3PG[10] = "3yyG.pgm";
  //xy convolved with gaussian
char xy1PG[10] = "1yyG.pgm";
char xy2PG[10] = "2yyG.pgm";
char xy3PG[10] = "3yyG.pgm";
  //RAw of pic1 w/ and w/o thrsh
char Raw1O[10] = "1RAw.pgm";
char Raw1OT[10] = "1RAwT.pgm";
  //RAw of pic2 w/ and w/o thrsh
char Raw2O[10] = "2RAw.pgm";
char Raw2OT[10] = "2RAwT.pgm";
  //RAw of pic3 w/ and w/o thrsh
char Raw3O[10] = "3RAw.pgm";
char Raw3OT[10] = "3RAwT.pgm";
  //Local Max of RAwXT
char Raw1M[10] = "1RAwM.pgm";
char Raw2M[10] = "2RAwM.pgm";
char Raw3M[10] = "3RAwM.pgm";
  //Final pictures, overlays
char Over1[10] = "1Over.pgm";
char Over2[10] = "2Over.pgm";
char Over3[10] = "3Over.pgm";


//image1 
Image picture1;
Image xDirc1;
Image yDirc1;
Image xx1;
Image yy1;
Image xy1;
Image xx1G;
Image yy1G;
Image xy1G;
Image RAw1;
Image RAw1T;
Image RAw1Max;
Image Ovly1;

//image2
Image picture2;
Image xDirc2;
Image yDirc2;
Image xx2;
Image yy2;
Image xy2;
Image xx2G;
Image yy2G;
Image xy2G;
Image RAw2;
Image RAw2T;
Image RAw2Max;
Image Ovly2;

//image3
Image picture3;
Image xDirc3;
Image yDirc3;
Image xx3;
Image yy3;
Image xy3;
Image xx3G;
Image yy3G;
Image xy3G;
Image RAw3;
Image RAw3T;
Image RAw3Max;
Image Ovly3;

//masks
Mask firstDeriv;
Mask gaussMask;

////////////////////////////////////////////////////////////////////////////////////////////
//Read In Images
///////////////////////////////////////////////////////////////////////////////////////////

picture1.readImage(in1);
picture2.readImage(in2);
picture3.readImage(in3);

////////////////////////////////////////////////////////////////////////////////////////////
//Convolve in x-Direc and in y-Dirc
///////////////////////////////////////////////////////////////////////////////////////////
//first create the first derivative 

firstDeriv.buildGaussFirstDeriv(1.5*0.7);

//now convolve in x/y Dirc
//Image 1
xDirc1 = picture1.convolveX(firstDeriv);
yDirc1 = picture1.convolveY(firstDeriv);

//Image 2
xDirc2 = picture2.convolveX(firstDeriv);
yDirc2 = picture2.convolveY(firstDeriv);

//Image 3
xDirc3 = picture3.convolveX(firstDeriv);
yDirc3 = picture3.convolveY(firstDeriv);

//Intermediate step, evidently, should print pictures
//Image 1
xDirc1.writeImage(xD1);
yDirc1.writeImage(yD1);

//Image 2
xDirc2.writeImage(xD2);
yDirc2.writeImage(yD2);

//Image 3
xDirc3.writeImage(xD3);
yDirc3.writeImage(yD3);

////////////////////////////////////////////////////////////////////////////////////////////
//Multiply the pictures to get xDirc^2, yDirc^2, and xyDirc
///////////////////////////////////////////////////////////////////////////////////////////

//Image 1
xx1 = xDirc1.multiply(xDirc1);
yy1 = yDirc1.multiply(yDirc1);
xy1 = xDirc1.multiply(yDirc1);

//Image 2
xx2 = xDirc2.multiply(xDirc2);
yy2 = yDirc2.multiply(yDirc2);
xy2 = xDirc2.multiply(yDirc2);

//Image 3
xx3 = xDirc3.multiply(xDirc3);
yy3 = yDirc3.multiply(yDirc3);
xy3 = xDirc3.multiply(yDirc3);

//Another intermediate step, print the pics, yo
//Image 1
xx1.writeImage(xx1P);
yy1.writeImage(yy1P);
xy1.writeImage(xy1P);

//Image 2
xx2.writeImage(xx2P);
yy2.writeImage(yy2P);
xy2.writeImage(xy2P);

//Image 3
xx3.writeImage(xx3P);
yy3.writeImage(yy3P);
xy3.writeImage(xy3P);

////////////////////////////////////////////////////////////////////////////////////////////
//Convolve xx,yy,xy with gaussian
///////////////////////////////////////////////////////////////////////////////////////////
//gotta create gaussian first

gaussMask.buildGauss(1.5);

//now convolve with xx,yy,xy
//Image 1
xx1G = xx1.convolve(gaussMask);
yy1G = yy1.convolve(gaussMask);
xy1G = xy1.convolve(gaussMask);

//Image 2
xx2G = xx2.convolve(gaussMask);
yy2G = yy2.convolve(gaussMask);
xy2G = xy2.convolve(gaussMask);

//Image 3
xx3G = xx3.convolve(gaussMask);
yy3G = yy3.convolve(gaussMask);
xy3G = xy3.convolve(gaussMask);

//Intermediate print job, theres quite a few this time
//Image 1
xx1G.writeImage(xx1PG);
yy1G.writeImage(yy1PG);
xy1G.writeImage(xy1PG);

//Image 2
xx2G.writeImage(xx2PG);
yy2G.writeImage(yy2PG);
xy2G.writeImage(xy2PG);

//Image 3
xx3G.writeImage(xx3PG);
yy3G.writeImage(yy3PG);
xy3G.writeImage(xy3PG);

////////////////////////////////////////////////////////////////////////////////////////////
//Compute R(Aw), the tricky part
///////////////////////////////////////////////////////////////////////////////////////////
//Write some R(Aw) functions
//alright have to call each picture twice, once with thrsh and once without

//Image 1
RAw1 = compRaw(xx1G, yy1G, xy1G, 0.06, false);
RAw1T = compRaw(xx1G, yy1G, xy1G, 0.06, true);

//Image 2
RAw2 = compRaw(xx2G, yy2G, xy2G, 0.06, false);
RAw2T = compRaw(xx2G, yy2G, xy2G, 0.06, true);

//Image 3
RAw3 = compRaw(xx3G, yy3G, xy3G, 0.06, false);
RAw3T = compRaw(xx3G, yy3G, xy3G, 0.06, true);

//OUTPUT!!! AGAIN!!
//Image 1 
RAw1.writeImage(Raw1O);
RAw1T.writeImage(Raw1OT);

//Image 2 
RAw2.writeImage(Raw2O);
RAw2T.writeImage(Raw2OT);

//Image 3 
RAw3.writeImage(Raw3O);
RAw3T.writeImage(Raw3OT);

////////////////////////////////////////////////////////////////////////////////////////////
//Find Local Maxima of the RAws
///////////////////////////////////////////////////////////////////////////////////////////
//can only call compLocalMax on the RAwXT images because they have been threshed

//Image1
RAw1Max = compLocalMax(RAw1T);

//Image2
RAw2Max = compLocalMax(RAw2T);

//Image3
RAw3Max = compLocalMax(RAw3T);

//Print dem babies
//Image 1
RAw1Max.writeImage(Raw1M);

//Image 2
RAw2Max.writeImage(Raw2M);

//Image 3
RAw3Max.writeImage(Raw3M);

//Overlay the pictures
Ovly1 = pictureOverlay(RAw1Max, picture1);
Ovly2 = pictureOverlay(RAw2Max, picture2);
Ovly3 = pictureOverlay(RAw3Max, picture3);

//print these final pictures
Ovly1.writeImage(Over1);
Ovly2.writeImage(Over2);
Ovly3.writeImage(Over3);


  //we're out of here...
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

Image pictureOverlay(Image maxPnts, Image scr)
{
  //variables
  int length = scr.getHeight();
  int width = scr.getWidth();
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
      }
    }
  }

return Overlay;
}










