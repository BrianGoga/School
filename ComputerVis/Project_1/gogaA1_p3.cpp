//////////////////////////////////
// Brian Goga                   //
// CS 485 Assignment 1          //
// Code for Problem 1           //
// Collaborated with Nick Smith //
//////////////////////////////////

//Header files
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

//main program
int main()
{
	//Read in
	int** myImageL;

	//scales of 256, 128, and 64 pixels
	int** L_pix256;
	int** L_pix128;
	int** L_pix64;

	//temps
	int** L_temp_128;
	int** L_temp_64;

	//Write out
	int** Image_lenna;

	//dimensions of pictures
	int L_length, L_width, Q;
	int S;

	//Read in file
	char LFile[10] = "lenna.pgm";

	//output files
	char Lout_256[20] = "lenna_p256.pgm";
	char Lout_128[20] = "lenna_p128.pgm";
	char Lout_64[20] = "lenna_p64.pgm";

	//get original picture
	ReadImage(LFile, &myImageL, L_length, L_width, Q);

	//Initializing original
	L_pix256 = new int* [L_width];
	for(int i=0; i<L_width; i++)
		(L_pix256)[i] = new int[L_length];

	//Initializing 128 pixels
	L_pix128 = new int* [L_width/2];
	L_temp_128 = new int* [L_width/2];
	for(int i=0; i<L_width/2; i++)
	{
		(L_pix128)[i] = new int[L_length/2];
		(L_temp_128)[i] = new int[L_length/2];
	}

	//Initializing 64
	L_pix64 = new int* [L_width/4];
	L_temp_64 = new int* [L_width/4];
	for(int i=0; i<L_width/4; i++)
	{
		(L_pix64)[i] = new int[L_length/4];
		(L_temp_64)[i] = new int[L_length/4];
	}



//Smooth original Lenna picture
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

//Create image with Scale of 1
for(int t = 0; t < L_width; t++)
{
	for(int r = 0; r < L_length; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				//dont go out of bounds
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
		//apply to new image
		L_pix256[r][t] = S;
	}
}

cout << "Output scale of 1" << endl;
//print image
WriteImage(Lout_256, L_pix256, L_length, L_width, Q);

//Create image with Scale of 2 (128 pixels)
for(int r = 1; r < L_width; r+=2)
{
	for(int c = 1; c < L_length; c+=2)
	{
		L_temp_128[r/2][c/2] = L_pix256[r][c];
	}
}

for(int t = 0; t < L_width/2; t++)
{
	for(int r = 0; r < L_length/2; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				//dont go out of bounds
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= L_width/2 || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= L_length/2 )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * L_temp_128[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		//apply to new image
		L_pix128[r][t] = S;
	}
}

cout << "Output scale of 2" << endl;
//print image
WriteImage(Lout_128, L_pix128, L_length/2, L_width/2, Q);


//Creating image with scale of 4 (64 pixels)
for(int r = 1; r < L_width/2; r+=2)
{
	for(int c = 1; c < L_length/2; c+=2)
	{
		L_temp_64[r/4][c/4] = L_pix128[r][c];
	}
}

for(int t = 0; t < L_width/4; t++)
{
	for(int r = 0; r < L_length/4; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				//dont go out of bounds
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= L_width/4 || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= L_length/4 )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * L_temp_64[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		//apply to new image
		L_pix64[r][t] = S;
	}
}

cout << "Output scale of 4" << endl;
//print image
WriteImage(Lout_64, L_pix64, L_length/4, L_width/4, Q);

	//return 0
	return 0;
}

//Functions

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