//////////////////////////////////
// Brian Goga                   //
// CS 485 Assignment 1          //
// Code for Problem 1           //
// Collaborated with Nick Smith //
//////////////////////////////////

//Header Files
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#define pi 3.141592653589793

using namespace std;

//Functions
void ReadImage(char name[], int ***fimage, int& M, int& N, int& Q);
void WriteImage(char fname[], int **fimage, int M, int N, int Q);
void Gauss (float s, int Hsize, float * H);
void readFile(float* dest);
void writeFile(float* oFile, char dest[]);
float* mask(const float* origin, int maskSize, const float* mask);

//Main Program
int main()
{
	//variables
	//Holds Rect_128.txt
	float rect[128];

	//Masks
	float* mask_1 = new float [5];
	float* mask_5 = new float [25];
	float* mask_11 = new float [55];

	float* rectMasked1;
	float* rectMasked5;
	float* rectMasked11; 

	//output files
	char File_rect1[20] = "rectMasked1.txt";
	char File_rect5[20] = "rectMasked5.txt";
	char File_rect11[20] = "rectMasked11.txt";

	char File_rect5x2[20] = "rectMasked5x2.txt";
	char File_rect5_2[20] = "rectMasked5_2.txt";

	readFile(rect);

//////////////////////
//Number 1 Part A
//////////////////////

//Create mask for Sigma 1
Gauss(1.0, 5, mask_1);
cout << "Sigma is of size 1" << endl;
//apply mask to rect and fout
rectMasked1 = mask(rect, 5, mask_1 );
writeFile(rectMasked1, File_rect1);

//remove unused space
delete[] rectMasked1;
delete[] mask_1;

//Create mask for Sigma 5
Gauss(5.0, 25, mask_5);
cout << endl << "Sigma is of size 5" << endl;
//apply mask to rect and fout
rectMasked5 = mask(rect, 25, mask_5 );
writeFile(rectMasked5, File_rect5);

//remove unused space
delete[] rectMasked5;
delete[] mask_5;

//Create mask for Sigma 11
Gauss(11.0, 55, mask_11);
cout << endl << "Sigma is of size 11" << endl;
//apply mask to rect and fout
rectMasked11 = mask(rect, 55, mask_11 );
writeFile(rectMasked11, File_rect11);

//remove unused space
delete[] rectMasked11;
delete[] mask_11;



/////////////////////
//Number 1 Part B
/////////////////////

cout << endl << "Applying Sigma 5 twice to Rect_128" << endl;
float* Ix1;
float* Ix2;

mask_5 = new float[25];
Gauss(5.0, 25, mask_5);

//Applying mask to mask_5
rectMasked5 = mask(rect, 25, mask_5);
Ix1 = mask(rectMasked5, 25, mask_5);
writeFile(Ix1, File_rect5x2);

//remove unused space
delete[] Ix1;
delete[] rectMasked5;


cout << endl << "Applying Sigma of 5*root(2) to Rect_128" << endl;

Gauss(5.0, 25, mask_5);
Ix2 = mask(rect, 25, mask_5);
writeFile(Ix1, File_rect5_2);

//remove unused space
delete[] Ix2;
delete[] mask_5;



//////////////////////
//Number 1 Part C
//////////////////////

//Containers for PGMs
int** myImage;
int** ImageSig;
int** TempImage;

//Pre-Loaded file names
char File_Lenna[20] = "lenna.pgm";
char File_Lenna1[20] = "Lenna_2D_1.pgm";
char File_Lenna5[20] = "Lenna_2D_5.pgm";
char File_Lenna11[20] = "Lenna_2D_11.pgm";

//Dimensions
int img_length, img_width, Q;
float S = 0.0;

//Mask Matrix
float Sig1[5][5];
float Sig5[25][25];
float Sig11[55][55];

//1D Gauss
mask_1 = new float[5];
mask_5 = new float[25];
mask_11 = new float[55];

Gauss(1.0, 5 , mask_1);
Gauss(5.0, 25, mask_5);
Gauss(11.0, 55, mask_11);


//2D Gauss Mask for Sigma 1
for(int n = 0; n < 5; n++)
{
	for(int g = 0; g < 5; g++)
	{
		Sig1[n][g] = mask_1[n] * mask_1[g];
	}
}

//2D Gauss Mask for Sigma 5
for(int n = 0; n < 25; n++)
{
	for(int g = 0; g < 25; g++)
	{
		Sig5[n][g] = mask_5[n] * mask_5[g];
	}
}

//2D Gauss Mask for Sigma 11
for(int n = 0; n < 55; n++)
{
	for(int g = 0; g < 55; g++)
	{
		Sig11[n][g] = mask_11[n] * mask_11[g];
	}
}

cout << endl << "Apply a 2D Gauss mask on lenna" << endl;

//read image
ReadImage(File_Lenna, &myImage, img_length, img_width, Q);

//allocate space
ImageSig = new int* [img_width];
TempImage = new int* [img_width];															
for(int i=0; i<img_width; i++)
{
		 (ImageSig)[i] = new int[img_length];
		 (TempImage)[i] = new int[img_length];

}


//Smoothing lenna using 2D Sigma 1
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				//check for out of bounds, and use 0 if it is
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= img_width || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= img_length )
				{
					S += 0;
				}
				else
				{
					//otherwise use mask
					S += Sig1[z][h] * myImage[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		//apply calculated value to new image
		ImageSig[r][t] = S;
	}
}
//print image
WriteImage(File_Lenna1, ImageSig, img_length,  img_width,  Q);


//Smoothing lenna using 2D Sigma 5
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			for(int h = 0; h < 25; h++)
			{
				//check for out of bounds, use 0 if true
				if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= img_width || 
					(t - h + 25 / 2) < 0 || (t - h + 25 / 2) >= img_length )
				{
					S += 0;
				}
				else
				{
					//else use mask
					S += Sig5[z][h] * myImage[r - z + 25 / 2][t - h + 25 / 2];
				}
			}
		}
		//store in new image
		ImageSig[r][t] = S;

	}
}
//print image
WriteImage(File_Lenna5, ImageSig, img_length,  img_width,  Q);


//Smoothing lenna using 2D Sigma 11
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			for(int h = 0; h < 55; h++)
			{
				//check for bounds and use 0 if outside
				if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= img_width || 
					(t - h + 55 / 2) < 0 || (t - h + 55 / 2) >= img_length )
				{
					S += 0;
				}
				else
				{
					//else use mask
					S += Sig11[z][h] * myImage[r - z + 55 / 2][t - h + 55 / 2];
				}
			}
		}
		//store in new image
		ImageSig[r][t] = S;
	}
}
//print image
WriteImage(File_Lenna11, ImageSig, img_length,  img_width,  Q);


//////////////////////
//Number 1 Part D
//////////////////////

//create new out files 
char File1_1D[20] = "Lenna_1D_1.pgm";
char File5_1D[20] = "Lenna_1D_5.pgm";
char File11_1D[20] = "Lenna_1D_11.pgm";

cout << endl << "Using 2 1D Gauss masks on lenna" << endl;

//Smoothing lenna using 2 1D mask of Sigma 1
//Applying mask to rows
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_1[z] * myImage[r - z + 5 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}

//Applying mask to cols
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_1[z] * TempImage[t][r - z + 5 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
//print smoothed image
WriteImage(File1_1D, ImageSig, img_length,  img_width,  Q);


//Smoothing lenna using 2 1D mask of Sigma 5
//Applying mask to rows
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_5[z] * myImage[r - z + 25 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}
//Applying mask to cols
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_5[z] * TempImage[t][r - z + 25 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
//print smoothed image
WriteImage(File5_1D, ImageSig, img_length,  img_width,  Q);



//Smoothing lenna using 2 1D masks of Sigma 11
//Applying mask to rows
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_11[z] * myImage[r - z + 55 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}
//Applying mask to cols
for(int t = 0; t < img_width; t++)
{
	for(int r = 0; r < img_length; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= img_width)
			{
				S += 0;
			}
			else
			{
				S += mask_11[z] * TempImage[t][r - z + 55 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
//print smoothed image
WriteImage(File11_1D, ImageSig, img_length,  img_width,  Q);

	//return 0
	return 0;
	}


//Implementation
void Gauss (float s, int Hsize, float * H)

{
  
/* Create a one-dimensional Gaussian mask
 "H" of scale "s" (sigma) on "Hsize" pixels.

   The values of the mask are scaled so that the
 sum of mask values = 1.0 
*/
	int     i;  
	float  cst,tssq,x,sum; 
  
	
	cst=1./(s*sqrt(2.0*pi));  
	tssq=1./(2*s*s); 
  
	for (i=0; i<Hsize; i++)
	{    
		x=(float)(i-Hsize/2);    
		H[i]=(cst*exp(-(x*x*tssq)));  
	} 
  	
	sum=0.0;  
	for (i=0;i<Hsize;i++)    
		sum += H[i];
  
	for(i=0;i<Hsize;i++)    
	H[i] /= sum;
}



void ReadImage(char fname[], int ***fimage, int& M, int& N, int& Q)
{
 int i, j;
 unsigned char *image;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in); 

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 ifp.getline(header,100,'\n');
 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=53) ) {   /* '5' */
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
 }

 ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 M=strtol(header,&ptr,0);
 N=atoi(ptr);

 ifp.getline(header,100,'\n');

 Q=strtol(header,&ptr,0);

 image = (unsigned char *) new unsigned char [M*N];

 *fimage = new int* [N];
 for(i=0; i<N; i++)
   (*fimage)[i] = new int[M];

 ifp.read( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();

 //
 // Convert the unsigned characters to integers
 //

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     (*fimage)[i][j]=(int)image[i*M+j];
}




void WriteImage(char fname[], int **fimage, int M, int N, int Q)
{
 int i, j;
 unsigned char *image;
 ofstream ofp;

 image = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     image[i*M+j]=(unsigned char)fimage[i][j];

 ofp.open(fname, ios::out);

 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P5" << endl;
 ofp << M << " " << N << endl;
 ofp << Q << endl;

 ofp.write( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();

}

void readFile(float* dest)
{
	ifstream fin("Rect_128.txt");

	//fin.open("Rect_128.txt");

	for(int i = 0; i < 128; i++)
	{

		fin >> dest[i];

	}
	fin.close();
}

void writeFile(float* oFile, char dest[])
{
	ofstream fout;

	fout.open(dest);

	if (!fout)
	{
     cout << "Can't open file: " << dest << endl;
     exit(1);
   }

   for(int i=0; i<128; i++)
   	fout<<oFile[i] * 255.0 << endl;

   fout.close();


}

float* mask(const float* origin, int maskSize, const float* mask)
{
	int maskHalf = maskSize / 2;
	float* result = new float[128];

	for (int i = 0; i < 128; ++i)
	{
		result[i] = 0.0;
		for(int q = -maskHalf; q <= maskHalf; ++q)
		{
			if(i + q >= 0 && i + q <= 127)
			{
				result[i] += origin[i + q] * mask[q + maskHalf];
			}
		}
	}
	return result;
}


