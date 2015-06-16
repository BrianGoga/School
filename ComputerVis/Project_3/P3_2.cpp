#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "ImageP5.cpp"
#include "Scale.cpp"

using namespace std;

ImageP5 RImage(float, const ImageP5&, const ImageP5&, const ImageP5&);
ImageP5 LocalMaxima(const ImageP5&);
ImageP5 CornerOverlay( ImageP5&, const ImageP5&);
ImageP5 HarrisHelper(float, float, ImageP5&);

int main(int argc, char const *argv[])
{
	/* Check arguments */
	if(argc < 2)
	{
		cout << "Not Valid Argumetns" << endl;
		return -1;
	}

	/* Initalize Variables */
	char buffer[16];
	string filename(argv[1]);
	ImageP5 image;
	Scale* G_SS = new Scale[17];

	/** Read in image */
	image.readImageP5((filename + ".pgm").c_str() );

	/* Fill Gauss Scale Space G_SS */
	for(int k = 0; k < 17; k++)
	{
		G_SS[k].SigmaInit = 1.5 * pow(1.2, k);
		G_SS[k].SigmaDer = 0.7 * G_SS[k].SigmaInit;

		G_SS[k].Scaleimage = HarrisHelper(G_SS[k].SigmaInit, G_SS[k].SigmaDer, image);
		sprintf(buffer, "%d", k);
		G_SS[k].Scaleimage.writeImageP5((filename + "_N" + string(buffer) + ".pgm").c_str());
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function
/////////////////////////////////////////////////////////////////////////////////////////
ImageP5 RImage(float alpha, const ImageP5& Ix2, const ImageP5& Iy2, const ImageP5& IxIy)
{
	/* Initalize Variables */
	int width = Ix2.getWidth();
	int height = Ix2.getHeight();
	float Max = -1000000.0;
	//float determinant, trace;
	ImageP5 RAw(width, height);

	/* Get R(Aw) */
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			float det1 = ( Ix2.at(i,j) * Iy2.at(i,j) );
			float det2 = ( IxIy.at(i,j) * IxIy.at(i,j) );
			float det = det1 - det2;

			float trace = Ix2.at(i,j) + Iy2.at(i,j);
			RAw.at( i, j ) = det - (alpha * trace * trace);

			//if( RAw.at(i,j) > Max ) { Max = RAw.at(i,j); }
		}
	}

	/* Trheshold */
	//Max *= 0.01;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if( RAw.at(i,j) <= 0 ) { RAw.at(i,j) = 0.0; }
		}
	}
	return RAw;
}

ImageP5 LocalMaxima(const ImageP5& RAw)
{
	/* Initalize Variables */
	int width = RAw.getWidth();
	int height = RAw.getHeight();
	ImageP5 Maxima(width, height);
	float Max;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Max = -999999999;
			/*Get Max in 3x3 area */
			for(int k = -1; k < 2; k++)
			{
				for(int l = -1; l < 2; l++)
				{
					if( ((i+k) >=0) && ((i+k) < height) && ((j+l) >= 0) && ((j+l) < width) )
					{
						Max = max(Max, RAw.at( (i+k), (j+l) ));
					}
				}
			}

			if(RAw.at(i,j) != Max)
			{
				Maxima.at(i,j) = 0.0;
			}
			else
			{
				Maxima.at(i,j) = Max;
			}
		}
	}
	return Maxima;
}

ImageP5 CornerOverlay( ImageP5& image, const ImageP5& LocMax)
{
	int width = image.getWidth();
	int height = image.getHeight();
	ImageP5 Corner = image;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(LocMax.at(i, j) > 0)
			{
				for(int k = 0; k < 3; k++)
				{
					if((i + k) >=0 && (i + k) < height && (j + k) >= 0 && (j + k)< width)
					{
						Corner.at(i + k, j + k) = 255;
					}
					if((i + k) >=0 && (i + k) < height && (j - k) >= 0 && (j - k)< width)
					{
						Corner.at(i + k, j - k) = 255;
					}
					if((i - k) >=0 && (i - k) < height && (j + k) >= 0 && (j + k)< width)
					{
						Corner.at(i - k, j + k) = 255;
					}
					if((i - k) >=0 && (i - k) < height && (j - k) >= 0 && (j - k)< width)
					{
						Corner.at(i - k, j - k) = 255;
					}
				}
			}
		}
	}

	return Corner;
}

ImageP5 HarrisHelper(float SigmaInit, float SigmaDer, ImageP5& image)
{
	Mask maskInit;
	Mask maskDer;

	maskDer.buildGaussFirstDeriv(SigmaDer);
	ImageP5 Ix = image.convolveX(maskDer);
	ImageP5 Iy = image.convolveY(maskDer);

	ImageP5 Ix2 = Ix.multiply(Ix);
	ImageP5 Iy2 = Iy.multiply(Iy);
	ImageP5 IxIy = Ix.multiply(Iy);

	/* Convolve Ix2, Iy2, & IxIy with Gauss */
	maskInit.buildGauss(SigmaInit);
	ImageP5 Ix2_Con = Ix2.convolve(maskInit);
	ImageP5 Iy2_Con = Iy2.convolve(maskInit);
	ImageP5 IxIy_Con = IxIy.convolve(maskInit);

	ImageP5 rImage = RImage(0.06, Ix2_Con, Iy2_Con, IxIy_Con);

	ImageP5 LocMax = LocalMaxima(rImage);

	ImageP5 Corner = CornerOverlay(image, LocMax);

	return Corner;
}