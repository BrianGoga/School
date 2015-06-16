///////////////////////////
//Project 3
//Brian Goga & Nicholas Smith
//CS 479
//////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#include <dirent.h>
#include "eigen/Eigen/Core"

using namespace std;

void ReadImage(ifstream& file, vector<double> &face);
void wrightImage(string file,vector<double> face);

int Counter = 0;

int main()
{
//Variables
vector< vector<double> > faces (1196, vector<double>(2880,0));
int** test;

/////////////////////////////////////////////////////////////////////
//INPUT
/////////////////////////////////////////////////////////////////////
DIR* dr = NULL;
char* dirn = new char[50];
struct dirent *drnt = NULL;

cout << "Enter File name to import pictures: ";

gets(dirn);
dr = opendir(dirn);
drnt = readdir(dr);
drnt = readdir(dr);

cout << endl << "Reading in pictures..." << endl;
for(int i = 0; i < 1196; i++)
{
    drnt = readdir(dr);
    stringstream filename;

    filename << dirn << "/" << drnt->d_name;
    ifstream picture(filename.str().c_str());

    ReadImage(picture, faces[i]);
    
}

for(int g = 0; g < 1196; g++)
{
    ostringstream outfilename;
    outfilename << "TEST/" << g << ".pgm";
    wrightImage(outfilename.str(), faces[g]);
}

//////////////////////////////////////////////////////////////////////
//Mean
/////////////////////////////////////////////////////////////////////
cout << "Calulating Mean..." << endl;
vector<double> mean;

for (int i = 0; i < 2880; ++i)
    {
    double sum = 0;
    for (int j = 0; j < 1196; ++j)
        {
        sum += faces[j][i];
        }
    mean.push_back(sum/1196);
    }


vector< vector<double> > MeanFaces (1196, vector<double>(2880,0));

for(int i = 0; i < 1196; i++)
{
    for(int j = 0; j < 2880; j++)
    {
        MeanFaces[i][j] = faces[i][j] - mean[j];
    }
}

//////////////////////////////////////////////////////////////////////
//Covariance
/////////////////////////////////////////////////////////////////////
cout << "Creating Covariance Matrix" << endl;
vector< vector<double> > Trans (0, vector<double>(1196,0));
vector< vector<double> > Cov (1196, vector<double>(1196,0));


for(int s = 0; s < 2880; s++)
{
    vector<double> row (0, 0);
    for(int t = 0; t < 1196; t++)
    {
        row.push_back(MeanFaces[t][s]);
    }
    Trans.push_back(row);
}

for(int r =0; r < 1196; r++)
{
    for(int c = 0; c < 1196; c++)
    {
        for (int k = 0; k < 2880; k++)
        {
            Cov[r][c] = MeanFaces[r][k] * Trans[k][c];
        }
    }
}


//////////////////////////////////////////////////////////////////////
//Eigen
/////////////////////////////////////////////////////////////////////
cout << "Calulating Eigen Values & Vectors" << endl;
vector< vector<double> > A (1196, vector<double>(1196,0));
vector< vector<double> > Idenity (1196, vector<double>(1196,0));
std::vector<double> eigenvalues;
vector< vector<double> > IdenityTrans (1196, vector<double>(1196,0));


for (int r = 0; r < 1196; ++r)
{
    Idenity[r][r] = 1;
}

for(int i = 0; i< 1196; i++)
{
    std::vector<double> v(0,0);
    for(int j=0;j<1196;j++)
    {
        v.push_back(Cov[i][j]);
    }
    A.push_back(v);
}

for(int it = 0; it < 5*1196; it++)
{
    double max = 0, k, l;
    for(int r = 0; r < 1196; r++)
    {
        for(int c = r + 1; c < 1196; c++)
        {
            if(fabs(A[r][c]) >= max)
            {
                max = fabs(A[r][c]);
                k = r;
                l = c;
            }
        }
    }
    if(max < 1.0e-12)
    {
        for(int i = 0; i <1196; i++)
        {
            eigenvalues.push_back(A[i][i]);
        }
        for(int c = 0; c < 1196; c++)
        {
            double len = 0;
            for(int r = 0; r < 1196; r++)
            {
                len += Idenity[r][c] * Idenity[r][c];
            }
            for(int r = 0; r < 1196; r++)
            {
                Idenity[r][c] = Idenity[r][c]/len;
            }
        }

        pair<vector<double>, vector< vector<double> > > result(eigenvalues, Idenity);
        for (int i = 0; i < result.first.size() - 1; ++i)
        {
            int index = i;
            double value = result.first[i];
            for (int j = i + 1; j < result.first.size(); ++j)
            {
                if (result.first[j] > value)
                {
                    index = j;
                    value = result.first[j];
                }
            }
            
            if (index != i)
            {
                std::swap(result.first[i], result.first[index]);
                for (int r = 0; r < 1196; ++r)
                {
                    std::swap(result.second[r][i], result.second[r][index]);
                }
            }
        }
    }
        else
        {
            double diff = A[l][l] - A[k][k];
            double t;

            if(fabs(A[k][l]) < fabs(diff)*1.0e-36)
            {
                t = A[k][l]/diff;
            }
            else
            {
                double phi = diff/(2.0*A[k][l]);
                t = 1.0/(fabs(phi) + sqrt(phi* phi + 1));
                if(phi < 0)
                {
                    t = -t;
                }
            }
            double c = 1.0/sqrt(t*t + 1.0);
            double s = t*c;
            double tau = s/(1.0 + c);
            double temp = A[k][l];
            A[k][l] = 0;
            A[k][k] = A[k][k] - t*temp;
            A[l][l] = A[l][l] + t*temp;

            for (int i = 0; i < k; ++i)
            {
                temp = A[i][k];
                A[i][k] = temp - s*(A[i][l] + tau*temp);
                A[i][l] = A[i][l] + s*(temp - tau*A[i][l]);
            }
            for (int i = k + 1; i < l; ++i)
            {
                temp = A[k][i];
                A[k][i] = temp - s*(A[i][l] + tau*A[k][i]);
                A[i][l] = A[i][l] + s*(temp - tau*A[i][l]);
            }
            for (int i = l + 1; i < 1196; ++i)
            {
                temp = A[k][i];
                A[k][i] = temp - s*(A[l][i] + tau*temp);
                A[l][i] = A[l][i] + s*(temp - tau*A[l][i]);
            }
            for (int i = 0; i < 1196; ++i)
            {
                temp = Idenity[i][k];
                Idenity[i][k] = temp - s*(Idenity[i][l] + tau*Idenity[i][k]);
                Idenity[i][l] = Idenity[i][l] + s*(temp - tau*Idenity[i][l]);
            }
        }
        for (int i = 0; i < 1196; ++i)
        {
            eigenvalues.push_back(A[i][i]);
        }
    
    pair<vector<double>, vector< vector<double> > > result(eigenvalues, Idenity);
        for (int i = 0; i < result.first.size() - 1; ++i)
            {
                int index = i;
                double value = result.first[i];
                for (int j = i + 1; j < result.first.size(); ++j)
                {
                    if (result.first[j] > value)
                    {
                        index = j;
                        value = result.first[j];
                    }
                }
                
                if (index != i)
                {
                    std::swap(result.first[i], result.first[index]);
                    for (int r = 0; r < 1196; ++r)
                    {
                        std::swap(result.second[r][i], result.second[r][index]);
                    }
                }
            }
            for(int s = 0; s < 2880; s++)
            {
                vector<double> row (0, 0);
                for(int t = 0; t < 1196; t++)
                {
                    row.push_back(result.second[t][s]);
                }
                IdenityTrans.push_back(row);
            }
}

            
/////////////////////////////////////////////////////////////////////
//EIGEN face
/////////////////////////////////////////////////////////////////////
cout << "Calulating Eigenfaces" << endl;

for(int s = 0; s < 2880; s++)
{
    vector<double> row (0, 0);
    for(int t = 0; t < 1196; t++)
    {
        row.push_back(Idenity[t][s]);
    }
    IdenityTrans.push_back(row);
}


vector< vector<double> > U (1196, vector<double>(2880,0));
vector< vector<double> > tempface (1196, vector<double>(2880,0));
for(int r = 0; r < 1196; r++)
{

    for (int c = 0; c < 2880; ++c)
    {
        tempface[r][c] += IdenityTrans[r][r]*MeanFaces[r][c];
    }


    for(int i = 0; i < 2880; i++)
    {
        U[r][i] = tempface[r][i]; 
    }


    double normal = 0;
    for(int i=0; i<2880; i++)
    {
        normal += pow(U[r][i], 2);
    }

    normal = sqrt(normal);
    for(int i=0; i<2880; i++)
    {
        U[r][i] /= normal;
    }

    //tempface = scale(U[r])
    double min = U[r][0];
    double max = U[r][0];
    
    for(int c =0; c<2880; c++)
    {
        if(U[r][c] < min)
            min = U[r][c];
        if(U[r][c] > max)
            max = U[r][c];
    }
    double rangeOld = max - min;
    double rangeNew = 255;
    std::vector<double> swag;
    for (int i = 0; i < 2880; ++i)
    {
        tempface[r][i] = ((U[r][i] - min) * rangeNew/rangeOld +min);
    }
}

/////////////////////////////////////////////////////////////////////
//Weights
/////////////////////////////////////////////////////////////////////
cout << "Calculating Weights" << endl;
//vector< vector<double> > U (1196, vector<double>(2880,0));



/////////////////////////////////////////////////////////////////////
//OUTPUT
/////////////////////////////////////////////////////////////////////
/*cout << "Writing out pictures" << endl;
for(int g = 0; g < 1196; g++)
{
    ostringstream outfilename;
    outfilename << "Temp/" << g << ".pgm";
    wrightImage(outfilename.str(), IdenityTrans[g]);
}*/





	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//ReadImage
/////////////////////////////////////////////////////////////////////////////////////////
void ReadImage(ifstream& file, vector<double> &face)
{
 int i, j, M, N, Q;
 unsigned char *image;
 char header [1196], *ptr;
 
 string list;
 getline(file, list);




 M = 48;
 N= 60;
 Q = 255;

 image = (unsigned char *) new unsigned char [M*N];

 file.read( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 file.close();

 //
 // Convert the unsigned characters to integers
 //

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     face[i*M+j] = (double)image[i*M+j];
}

/////////////////////////////////////////////////////////////////////////////////////////
//WriteImage
/////////////////////////////////////////////////////////////////////////////////////////
void wrightImage(string file, vector<double> face)
{
stringstream filename;
filename << file;
ofstream picture(filename.str().c_str());

 int i, j, M, N, Q;
 unsigned char *image;
 char header [1196], *ptr;

 M = 48;
 N= 60;
 Q = 255;

picture << "P2"  << endl;
picture << 48 << endl << 60 << endl;
picture << 255 << endl;

cout << "Here" << endl;

for(i=0; i<N; i++)
   for(j=0; j<M; j++)
    picture << (int)face[i*M+j] << " ";


cout << "Her 2e" << endl;

picture.close();
}
