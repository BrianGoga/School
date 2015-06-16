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

//functions
void ReadImage(char name[], int ***fimage, int& M, int& N, int& Q);
void WriteImage(char fname[], int **fimage, int M, int N, int Q);
void Gauss (float s, int Hsize, float * H);


int main()
{
	// Read in
	int** myImageL;
	int** myImageSF;

	//Smoothing 
	int** LImage;
	int** SFImage;

	//Output
	//Lenna
	int** Lenna_X;
	int** Lenna_XX;
	int** Lenna_Y;
	int** Lenna_YY;
	int** Lenna_M;
	int** Lenna_D;

	//SF
	int** SF_X;
	int** SF_XX;
	int** SF_Y;
	int** SF_YY;
	int** SF_M;
	int** SF_D;

	int L_length, L_width, Q;
	int SF_length, SF_width, C;
	float S;

	//Read in name
	char LFile[10] = "lenna.pgm";
	char SFFile[10] = "sf.pgm";

	//Read out name
	char XLout[20] = "lenna_X.pgm";
	char YLout[20] = "lenna_Y.pgm";
	char MLout[20] = "lenna_M.pgm";
	char DLout[20] = "lenna_D.pgm";
	char TLout[20] = "lenna_T.pgm";

	char XSFout[20] = "SF_X.pgm";
	char YSFout[20] = "SF_Y.pgm";
	char MSFout[20] = "SF_M.pgm";
	char DSFout[20] = "SF_D.pgm";
	char TSFout[20] = "SF_T.pgm";

	//Soble Masks X & Y
	float SobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	float SobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

	//Read in images
	ReadImage(LFile, &myImageL, L_length, L_width, Q);
	ReadImage(SFFile, &myImageSF, SF_length, SF_width, C);

//Initializing
Lenna_X = new int* [L_width];
Lenna_XX = new int* [L_width];
Lenna_Y = new int* [L_width];
Lenna_YY = new int* [L_width];
Lenna_M = new int* [L_width];
Lenna_D = new int* [L_width];

SF_X = new int* [SF_width];
SF_XX = new int* [SF_width];
SF_Y = new int* [SF_width];
SF_YY = new int* [SF_width];
SF_M = new int* [SF_width];
SF_D = new int* [SF_width];

LImage = new int* [L_width];
SFImage = new int* [SF_width];
for(int i=0; i<L_width; i++)
{
	(Lenna_X)[i] = new int[L_length];
	(Lenna_XX)[i] = new int[L_length];
	(Lenna_Y)[i] = new int[L_length];
	(Lenna_YY)[i] = new int[L_length];
	(Lenna_M)[i] = new int[L_length];
	(Lenna_D)[i] = new int[L_length];

	(SF_X)[i] = new int[SF_length];
	(SF_XX)[i] = new int[SF_length];
	(SF_Y)[i] = new int[SF_length];
	(SF_YY)[i] = new int[SF_length];
	(SF_M)[i] = new int[SF_length];
	(SF_D)[i] = new int[SF_length];

	(LImage)[i] = new int[L_length];
	(SFImage)[i] = new int[SF_length];
}

//Smooth
float* Sigma1 = new float[25];
float Sig1[5][5];

Gauss(1.0, 5 , Sigma1);

for(int n = 0; n < 5; n++)
{
	for(int g = 0; g < 5; g++)
	{
		Sig1[n][g] = Sigma1[n] * Sigma1[g];
	}
}
//Smoothing of lenna
for(int t = 0; t < L_width; t++)
{
	for(int r = 0; r < L_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= L_width || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= L_length )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * myImageL[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage[r][t] = S;
	}
}

//Smoothing SF
for(int t = 0; t < SF_width; t++)
{
	for(int r = 0; r < SF_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= SF_width || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= SF_length )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * myImageSF[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		SFImage[r][t] = S;
	}
}

/////////////////////
//Number 2 Part A
/////////////////////

//Soble X mask Lenna
cout << "Applying Sx Mask to Lenna" <<endl;

for(int t = 0; t < L_width; t++)
{
	for(int r = 0; r < L_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= L_width || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= L_length )
				{
					S += 0.0;
				}
				else
				{
					S += SobelX[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Lenna_X[r][t] = S;
	}
}
WriteImage(XLout, Lenna_X, L_length,  L_width,  Q);

//Sobel X mask sf
cout << "Applying Sx Mask to SF" <<endl;
for(int t = 0; t < SF_width; t++)
{
	for(int r = 0; r < SF_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= SF_width || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= SF_length )
				{
					S += 0.0;
				}
				else
				{
					S += SobelX[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		SF_X[r][t] = S;
	}
}
WriteImage(XSFout, SF_X, SF_length,  SF_width,  Q);


/////////////////////
//Number 2 Part B
////////////////////

//Soble Y mask Lenna
cout << "Applying Sy Mask to Lenna" <<endl;

for(int t = 0; t < L_width; t++)
{
	for(int r = 0; r < L_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= L_width || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= L_length )
				{
					S += 0.0;
				}
				else
				{
					S += SobelY[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Lenna_Y[r][t] = S;
	}
}
WriteImage(YLout, Lenna_Y, L_length,  L_width,  Q);

//Sobel Y mask sf
cout << "Applying Sy Mask to SF" <<endl;
for(int t = 0; t < SF_width; t++)
{
	for(int r = 0; r < SF_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= SF_width || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= SF_length )
				{
					S += 0.0;
				}
				else
				{
					S += SobelY[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		SF_Y[r][t] = S;
	}
}
WriteImage(YSFout, SF_Y, SF_length,  SF_width,  Q);


/////////////////////
//Number 2 Part C
/////////////////////

cout << "Acquiring Magnitude of Lenna" <<endl;

//Squaring X Lenna
for(int r = 0; r < L_width; r++)
{
	for(int c = 0; c < L_length; c++)
	{
		Lenna_XX[r][c] += (Lenna_X[r][c] * Lenna_X[r][c]);
	}
}

// Squaring Y lenna
for(int r = 0; r < L_width; r++)
{
	for(int c = 0; c < L_length; c++)
	{
		Lenna_YY[r][c] += (Lenna_Y[r][c] * Lenna_Y[r][c]); 
	}
}

//Adding both into M leena
for(int r = 0; r < L_width; r++)
{
	for(int c = 0; c < L_length; c++)
	{
		Lenna_M[r][c] = (sqrt(Lenna_XX[r][c] + Lenna_YY[r][c]));
	}
}
WriteImage(MLout, Lenna_M, L_length,  L_width,  Q);


cout << "Acquiring Magnitude of SF" <<endl;


//Squaring X SF
for(int r = 0; r < SF_width; r++)
{
	for(int c = 0; c < SF_length; c++)
	{
		SF_XX[r][c] += (SF_X[r][c] * SF_X[r][c]);
	}
}

// Squaring Y SF
for(int r = 0; r < SF_width; r++)
{
	for(int c = 0; c < SF_length; c++)
	{
		SF_YY[r][c] += (SF_Y[r][c] * SF_Y[r][c]); 
	}
}

//Adding both into M SF
for(int r = 0; r < SF_width; r++)
{
	for(int c = 0; c < SF_length; c++)
	{
		SF_M[r][c] = (sqrt(SF_XX[r][c] + SF_YY[r][c]));
	}
}
WriteImage(MSFout, SF_M, SF_length,  SF_width,  Q);

///////////////////
//Number 2 Part D
///////////////////

cout << "Acquiring Gradient Direction  of Lenna" <<endl;

//Tangent of Lenna
for(int r = 0; r < L_width; r++)
{
	for(int c = 0; c < L_length; c++)
	{
		Lenna_D[r][c] = atan2(Lenna_Y[r][c], Lenna_X[r][c]);
	}
}
WriteImage(DLout, Lenna_D, L_length,  L_width,  Q);


cout << "Acquiring Gradient Direction  of SF" <<endl;

//Tangent of SF
for(int r = 0; r < SF_width; r++)
{
	for(int c = 0; c < SF_length; c++)
	{
		SF_D[r][c] = atan2(SF_Y[r][c], SF_X[r][c]);
	}
}
WriteImage(DSFout, SF_D, SF_length,  SF_width,  Q);
/////////////////////
//Number 2 Part E
/////////////////////
cout << "Acquiring Threshold of Lenna" <<endl;

int thresh;

cout << "Enter Threshold for Lenna (0-255): ";
cin >> thresh;

for(int r = 0; r < L_width; r++)
{
	for(int c = 0; c < L_length; c++)
	{
		if(Lenna_M[r][c] < thresh)
		{
			Lenna_M[r][c] = 0;
		}
	}
}

WriteImage(TLout, Lenna_M, L_length,  L_width,  Q);

cout << "Acquiring Threshold of SF" <<endl;

cout << "Enter Threshold for SF (0-255): ";
cin >> thresh;

for(int r = 0; r < SF_width; r++)
{
	for(int c = 0; c < SF_length; c++)
	{
		if(SF_M[r][c] < thresh)
		{
			SF_M[r][c] = 0;
		}
	}
}

WriteImage(TSFout, SF_M, SF_length,  SF_width,  Q);


	//return 0
	return 0;
}





//Implementation

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