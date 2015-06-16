///////////////////////////
//Project 2, part 3
//Brian Goga & Nicholas Smith
//CS 479
//////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "image.cpp"

using namespace std;

//Structs
struct node
{
 RGB here;
 node *next;
};

//Functions
void readImageHeader(char fname[], int& N, int& M, int& Q, bool& type);
void readImage(char fname[], ImageType& image);
void writeImage(char fname[], ImageType& image);
void gatherPoints(node* &list, int x1, int y1, int x2, int y2, ImageType& image);

//main
int main()  
{

//Variables
char pic1[30] = "Training_1.ppm";
char out1[30] = "Output_1B.ppm";
char pic3[30] = "Training_3.ppm";
char out3[30] = "Output_3B.ppm";
char pic6[30] = "Training_6.ppm";
char out6[30] = "Output_6B.ppm";
double mean[2], sigma[2][2] = {{0,0}, {0,0}};
int N,M,Q;
double Cb ,Cr ,bottom, threshCb , threshCr ;
int counter;
bool picture;
node *root, *conductor;
root = new node;
conductor = root;
RGB temp, White, Black;


//read in image
readImageHeader(pic1, N, M, Q, picture);
ImageType MyImage(N, M, Q);
ImageType TestImage(N, M, Q);
readImage(pic1,MyImage);

readImageHeader(pic3, N, M, Q, picture);
ImageType MyImage3(N, M, Q);
readImage(pic3,MyImage3);

readImageHeader(pic6, N, M, Q, picture);
ImageType MyImage6(N, M, Q);
readImage(pic6,MyImage6);



//Teach the program what is "skin color"
gatherPoints(conductor, 118, 591, 170, 614, MyImage);
gatherPoints(conductor, 319, 471, 367, 488, MyImage);
gatherPoints(conductor, 320, 244, 360, 260, MyImage);
gatherPoints(conductor, 419, 417, 460, 431, MyImage);
gatherPoints(conductor, 530, 481, 574, 496, MyImage);
gatherPoints(conductor, 607, 443, 644, 458, MyImage);
gatherPoints(conductor, 760, 475, 804, 491, MyImage);
gatherPoints(conductor, 826, 352, 869, 366, MyImage);
gatherPoints(conductor, 869, 543, 914, 558, MyImage);
gatherPoints(conductor, 988, 384, 1027, 395, MyImage);
gatherPoints(conductor, 1007, 555, 1064, 576, MyImage);
gatherPoints(conductor, 1102, 420, 1148, 438, MyImage);
gatherPoints(conductor, 1246, 416, 1288, 439, MyImage);
gatherPoints(conductor, 1403, 434, 1456, 452, MyImage);
gatherPoints(conductor, 1365, 205, 1405, 212, MyImage);
gatherPoints(conductor, 1574, 524, 1624, 538, MyImage);
gatherPoints(conductor, 1583, 106, 1625, 169, MyImage);





//Testing
White.r = 255;
White.g = 255;
White.b = 255;

Black.r = 0;
Black.g = 0;
Black.b = 0;

for(int j = 0; j < 1392; j++)
{
  for(int i = 0; i < 1856; i++ )
      {
        MyImage.getPixelVal(j, i, temp);

         Cb = -0.169*temp.r - 0.332*temp.g + .5*temp.b;
         Cr = .5*temp.r - 0.419*temp.g - .081*temp.b;

        //cout << Cb << ' ' << Cr << endl;

        if((Cb > -23 && Cb < 7) && (Cr > 12 && Cr < 37))
        {
          TestImage.setPixelVal(j, i, White);
        }
        else
        {
          TestImage.setPixelVal(j, i, Black);
        }
      }
}
writeImage(out1, TestImage);



for(int j = 0; j < 1392; j++)
{
  for(int i = 0; i < 1856; i++ )
      {
        MyImage3.getPixelVal(j, i, temp);

         Cb = -0.169*temp.r - 0.332*temp.g + .5*temp.b;
         Cr = .5*temp.r - 0.419*temp.g - .081*temp.b;

        //cout << Cb << ' ' << Cr << endl;

        if((Cb > -23 && Cb < 7) && (Cr > 12 && Cr < 37))
        {
          TestImage.setPixelVal(j, i, White);
        }
        else
        {
          TestImage.setPixelVal(j, i, Black);
        }
      }
}
writeImage(out3, TestImage);



for(int j = 0; j < 1392; j++)
{
  for(int i = 0; i < 1856; i++ )
      {
        MyImage6.getPixelVal(j, i, temp);

         Cb = -0.169*temp.r - 0.332*temp.g + .5*temp.b;
         Cr = .5*temp.r - 0.419*temp.g - .081*temp.b;

        //cout << Cb << ' ' << Cr << endl;

        if((Cb > -23 && Cb < 7) && (Cr > 12 && Cr < 37))
        {
          TestImage.setPixelVal(j, i, White);
        }
        else
        {
          TestImage.setPixelVal(j, i, Black);
        }
      }
}
writeImage(out6, TestImage);

	//return 0
	return 0;
}

//Implemenations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readImage(char fname[], ImageType& image)
{
 int i, j;
 int N, M, Q;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);
  
 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 ifp.getline(header,100,'\n');

 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=54) ) {   /* '6' */
      cout << "Image " << fname << " is not PPM" << endl;
      exit(1);
 }

 ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 M=strtol(header,&ptr,0);
 N=atoi(ptr);
 
 ifp.getline(header,100,'\n');
 Q=strtol(header,&ptr,0);

 charImage = (unsigned char *) new unsigned char [3*M*N];

 ifp.read( reinterpret_cast<char *>(charImage), (3*M*N)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();
 
 /* Convert the unsigned characters to integers */

 RGB val;
 
 for(i=0; i < N; i++)
  for(j=0; j < 3*M; j+=3) {
    val.r = (int)charImage[i*3*M+j];
    val.g = (int)charImage[i*3*M+j+1];
    val.b = (int)charImage[i*3*M+j+2];
    image.setPixelVal(i, j/3, val);
  }

delete [] charImage;

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readImageHeader(char fname[], int& N, int& M, int& Q, bool& type)
{
 int i, j;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 type = false; // PGM

 ifp.getline(header,100,'\n');
 if ( (header[0] == 80) &&  /* 'P' */
      (header[1]== 53) ) {  /* '5' */
      type = false;
 }
 else if ( (header[0] == 80) &&  /* 'P' */
      (header[1] == 54) ) {        /* '6' */
      type = true;
 } 
 else {
   cout << "Image " << fname << " is not PGM or PPM" << endl;
   exit(1);
 }

ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 M=strtol(header,&ptr,0);
 N=atoi(ptr);

 ifp.getline(header,100,'\n');

 Q=strtol(header,&ptr,0);

 ifp.close();
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void writeImage(char fname[], ImageType& image)
{
 int i, j;
 int N, M, Q;
 unsigned char *charImage;
 ofstream ofp;

 image.getImageInfo(N, M, Q);

 charImage = (unsigned char *) new unsigned char [3*M*N];

 RGB val;

 for(i=0; i<N; i++)
   for(j=0; j<3*M; j+=3) {
     image.getPixelVal(i, j/3, val);
     charImage[i*3*M+j]=(unsigned char)val.r;
     charImage[i*3*M+j+1]=(unsigned char)val.g;
     charImage[i*3*M+j+2]=(unsigned char)val.b;
   }

 ofp.open(fname, ios::out | ios::binary);

 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P6" << endl;
 ofp << M << " " << N << endl;
 ofp << Q << endl;

 ofp.write( reinterpret_cast<char *>(charImage), (3*M*N)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();

 delete [] charImage;
}

void gatherPoints(node* &list, int x1, int y1, int x2, int y2, ImageType& image)
{
  //variables
  node* pointer;
  pointer = list;

  //loop through patch gathering rgb values and adding them to the list
  //loop through Y values
  for(int i = y1; i <= y2; i++)
  {
    //loop through X values
    for(int j = x1; j <= x2; j++)
    {

      //add current points rgb values to the list
      image.getPixelVal(i,j,pointer->here);

      pointer->next = new node;
      pointer = pointer->next;
      pointer->next = NULL;
    }
  }
  //end
}
