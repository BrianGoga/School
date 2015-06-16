///////////////////////////
//Project 2, parts 1 and 2
//Brian Goga & Nicholas Smith
//CS 479
//////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct point
{ 
 double x_value;
 double y_value;

 int mean;
 int category;

};

//functions
double randomeDouble();
void Gauss(double*** );
void assignPoints(double**, point*, int);

//main program
int main()
{
	srand(time(NULL));

	ofstream fout;

	double mean1[2] = {0.0, 0.0};
	double mean2[2] = {0.0, 0.0};
	double Sigma1[2][2] = {{0,0}, {0,0}};
	double Sigma2[2][2] = {{0,0}, {0,0}};

	double** pointArray;

	point* data = new point[10000];
	point* sampleArray = new point[1000];

	double val1, val2, val3;
	double valX1, valX2 , valY2, valY1;

	//counter for misclassification
	int error = 0;

	//arithmetic values
	valX1 = valY2 = 1 - 4;
	val3 = 7;
/////////////////////////////////////////////////////////////////////////////////////////
//1a
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////
//Generate Points
/////////////////////////
	//Generate Points
	Gauss(&pointArray);	

	//assign points a mean 
	assignPoints(pointArray, data, 5);

	//Drawing sample of 10& 
	for(int i = 0, q = 0; i < 10000; i++)
	{
		if(i % 10 == 0)
		{
			sampleArray[q] = data[i];
			q++;
		}
	}

/////////////////////////
// Find Mean
/////////////////////////

for(int i = 0; i < 5000; i++)
{
	mean1[0] += data[i].x_value;
	mean1[1] += data[i].y_value;
}
mean1[0] = mean1[0] / 5000.0;
mean1[1] = mean1[1] / 5000.0; 


for(int i = 5000; i < 10000; i++)
{
	mean2[0] += data[i].x_value;
	mean2[1] += data[i].y_value;
}
mean2[0] = mean2[0] / 5000.0; 
mean2[1] = mean2[1] / 5000.0; 

//Pinrt mean
cout << endl << "Printing Mean and covariance for 1a: " << endl;
cout << mean1[0] << " " << mean1[1] << "  -  " << mean2[0]<< " " << mean2[1] << endl << endl;
 

/////////////////////////
//Find covariance
/////////////////////////

for(int i = 0; i < 5000; i++)
{
	data[i].x_value -= mean1[0];
	data[i].y_value -= mean1[1];

	Sigma1[0][0] += data[i].x_value * data[i].x_value;
	Sigma1[0][1] += data[i].x_value * data[i].y_value;
	Sigma1[1][0] += data[i].y_value * data[i].x_value;
	Sigma1[1][1] += data[i].y_value * data[i].y_value;

	data[i].x_value += mean1[0];
	data[i].y_value += mean1[1];
}

Sigma1[0][0] = Sigma1[0][0] / 5000.0;
Sigma1[0][1] = Sigma1[0][1] / 5000.0;
Sigma1[1][0] = Sigma1[1][0] / 5000.0;
Sigma1[1][1] = Sigma1[1][1] / 5000.0; 


for(int i = 5000; i < 10000; i++)
{
	data[i].x_value -= mean2[0];
	data[i].y_value -= mean2[1];

	Sigma2[0][0] += data[i].x_value * data[i].x_value;
	Sigma2[0][1] += data[i].x_value * data[i].y_value;
	Sigma2[1][0] += data[i].y_value * data[i].x_value;
	Sigma2[1][1] += data[i].y_value * data[i].y_value;

	data[i].x_value += mean2[0];
	data[i].y_value += mean2[1];
}

Sigma2[0][0] = Sigma2[0][0] / 5000.0;
Sigma2[0][1] = Sigma2[0][1] / 5000.0;
Sigma2[1][0] = Sigma2[1][0] / 5000.0;
Sigma2[1][1] = Sigma2[1][1] / 5000.0; 

//Printing  Covariance
cout << Sigma1[0][0] << ' ' << Sigma1[0][1] << "	----	" << Sigma2[0][0] << ' ' << Sigma2[0][1] << endl;
cout << Sigma1[1][0] << ' ' << Sigma1[1][1] << "	----	" << Sigma2[1][0] << ' ' << Sigma2[1][1] << endl;

for(int q = 0; q < 10000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(data[q].x_value -1) * (data[q].x_value -1));
	valY1 = (-(data[q].y_value -1) * (data[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = (-(data[q].x_value -4) * (data[q].x_value -4));
	valY2 = (-(data[q].y_value -4) * (data[q].y_value -4));
	val2 = valX2 + valY2;

	//if val2 > than val1 then point belongs to first category
	if(val1 - val2 > 0 )
	{
		data[q].category = 1;
	}

	//if val1 > than val2 then point belongs to second category	
	else
	{
		data[q].category = 2;
	}

	//determine if misclassified
	if(data[q].category != data[q].mean)
	{
		error++;
	}
}
cout << endl <<"Printing error count for 1a: ";
cout  << endl << error;
/////////////////////////////////////////////////////////////////////////////////////////
//1b
/////////////////////////////////////////////////////////////////////////////////////////
//Reset arrays
mean1[0] = 0.0;
mean1[1] = 0.0;
Sigma1[0][0] = 0.0;
Sigma1[0][1] = 0.0;
Sigma1[1][0] = 0.0;
Sigma1[1][1] = 0.0;


mean2[0] = 0.0;
mean2[1] = 0.0;
Sigma2[0][0] = 0.0;
Sigma2[0][1] = 0.0;
Sigma2[1][0] = 0.0;
Sigma2[1][1] = 0.0;

error = 0;

/////////////////////////
// Find Mean
/////////////////////////

for(int i = 0; i < 500; i++)
{
	mean1[0] += sampleArray[i].x_value;
	mean1[1] += sampleArray[i].y_value;
}
mean1[0] = mean1[0] / 500.0;
mean1[1] = mean1[1] / 500.0; 


for(int i = 500; i < 1000; i++)
{
	mean2[0] += sampleArray[i].x_value;
	mean2[1] += sampleArray[i].y_value;
}
mean2[0] = mean2[0] / 500.0; 
mean2[1] = mean2[1] / 500.0; 

//Pinrt mean
cout << endl << endl << "Printing Mean and covariance for 1b: " << endl;
cout << mean1[0] << " " << mean1[1] << "  -  " << mean2[0]<< " " << mean2[1] << endl << endl;
 

/////////////////////////
//Find covariance
/////////////////////////

for(int i = 0; i < 500; i++)
{
	sampleArray[i].x_value -= mean1[0];
	sampleArray[i].y_value -= mean1[1];

	Sigma1[0][0] += sampleArray[i].x_value * sampleArray[i].x_value;
	Sigma1[0][1] += sampleArray[i].x_value * sampleArray[i].y_value;
	Sigma1[1][0] += sampleArray[i].y_value * sampleArray[i].x_value;
	Sigma1[1][1] += sampleArray[i].y_value * sampleArray[i].y_value;

	sampleArray[i].x_value += mean1[0];
	sampleArray[i].y_value += mean1[1];
}

Sigma1[0][0] = Sigma1[0][0] / 500.0;
Sigma1[0][1] = Sigma1[0][1] / 500.0;
Sigma1[1][0] = Sigma1[1][0] / 500.0;
Sigma1[1][1] = Sigma1[1][1] / 500.0; 


for(int i = 500; i < 1000; i++)
{
	sampleArray[i].x_value -= mean2[0];
	sampleArray[i].y_value -= mean2[1];

	Sigma2[0][0] += sampleArray[i].x_value * sampleArray[i].x_value;
	Sigma2[0][1] += sampleArray[i].x_value * sampleArray[i].y_value;
	Sigma2[1][0] += sampleArray[i].y_value * sampleArray[i].x_value;
	Sigma2[1][1] += sampleArray[i].y_value * sampleArray[i].y_value;

	sampleArray[i].x_value += mean2[0];
	sampleArray[i].y_value += mean2[1];

}

Sigma2[0][0] = Sigma2[0][0] / 500.0;
Sigma2[0][1] = Sigma2[0][1] / 500.0;
Sigma2[1][0] = Sigma2[1][0] / 500.0;
Sigma2[1][1] = Sigma2[1][1] / 500.0; 

//Printing  Covariance
cout << Sigma1[0][0] << ' ' << Sigma1[0][1] << "	----	" << Sigma2[0][0] << ' ' << Sigma2[0][1] << endl;
cout << Sigma1[1][0] << ' ' << Sigma1[1][1] << "	----	" << Sigma2[1][0] << ' ' << Sigma2[1][1] << endl;

for(int q = 0; q < 1000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(sampleArray[q].x_value -1) * (sampleArray[q].x_value -1));
	valY1 = (-(sampleArray[q].y_value -1) * (sampleArray[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = (-(sampleArray[q].x_value -4) * (sampleArray[q].x_value -4));
	valY2 = (-(sampleArray[q].y_value -4) * (sampleArray[q].y_value -4));
	val2 = valX2 + valY2;

	//if val2 > than val1 then point belongs to first category
	if(val1 - val2 > 0 )
	{
		sampleArray[q].category = 1;
	}

	//if val1 > than val2 then point belongs to second category	
	else
	{
		sampleArray[q].category = 2;
	}

	//determine if misclassified
	if(sampleArray[q].category != sampleArray[q].mean)
	{
		error++;
	}
}
cout << endl <<"Printing error count for 1b: ";
cout << endl << error << endl << endl ;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cout << "============================================================" << endl;

//Reset variables
mean1[0] = 0.0;
mean1[1] = 0.0;
Sigma1[0][0] = 0.0;
Sigma1[0][1] = 0.0;
Sigma1[1][0] = 0.0;
Sigma1[1][1] = 0.0;


mean2[0] = 0.0;
mean2[1] = 0.0;
Sigma2[0][0] = 0.0;
Sigma2[0][1] = 0.0;
Sigma2[1][0] = 0.0;
Sigma2[1][1] = 0.0;

error = 0;

/////////////////////////
//Generate Points
/////////////////////////

	//assign points a mean 
	assignPoints(pointArray, data, 5);

	//Drawing sample of 10& 
	for(int i = 0, q = 0; i < 10000; i++)
	{
		if(i % 10 == 0)
		{
			sampleArray[q] = data[i];
			q++;
		}
	}

/////////////////////////
// Find Mean
/////////////////////////

for(int i = 0; i < 5000; i++)
{
	mean1[0] += data[i].x_value;
	mean1[1] += data[i].y_value;
}
mean1[0] = mean1[0] / 5000.0;
mean1[1] = mean1[1] / 5000.0; 


for(int i = 5000; i < 10000; i++)
{
	mean2[0] += data[i].x_value;
	mean2[1] += data[i].y_value;
}
mean2[0] = (mean2[0] / 5000.0); 
mean2[1] = (mean2[1] / 5000.0); 

//Pinrt mean
cout << endl  << "Printing Mean and covariance for 2a: " << endl;
cout << mean1[0] << " " << mean1[1] << "  -  " << mean2[0]<< " " << mean2[1] << endl << endl;
 

/////////////////////////
//Find covariance
/////////////////////////

for(int i = 0; i < 5000; i++)
{
	data[i].x_value -= mean1[0];
	data[i].y_value -= mean1[1];

	Sigma1[0][0] += data[i].x_value * data[i].x_value* mean1[0];
	Sigma1[0][1] += data[i].x_value * data[i].y_value;
	Sigma1[1][0] += data[i].y_value * data[i].x_value;
	Sigma1[1][1] += data[i].y_value * data[i].y_value* mean1[0] * mean1[1];

	data[i].x_value += mean1[0];
	data[i].y_value += mean1[1];
}

Sigma1[0][0] = Sigma1[0][0] / 5000.0;
Sigma1[0][1] = Sigma1[0][1] / 5000.0;
Sigma1[1][0] = Sigma1[1][0] / 5000.0;
Sigma1[1][1] = Sigma1[1][1] / 5000.0; 


for(int i = 5000; i < 10000; i++)
{
	data[i].x_value -= mean2[0];
	data[i].y_value -= mean2[1];

	Sigma2[0][0] += data[i].x_value * data[i].x_value * mean2[0];
	Sigma2[0][1] += data[i].x_value * data[i].y_value;
	Sigma2[1][0] += data[i].y_value * data[i].x_value;
	Sigma2[1][1] += data[i].y_value * data[i].y_value * mean2[0] * mean2[1];

	data[i].x_value += mean2[0];
	data[i].y_value += mean2[1];
}

Sigma2[0][0] = Sigma2[0][0] / 5000.0;
Sigma2[0][1] = Sigma2[0][1] / 5000.0;
Sigma2[1][0] = Sigma2[1][0] / 5000.0;
Sigma2[1][1] = Sigma2[1][1] / 5000.0; 

//Printing  Covariance
cout << Sigma1[0][0] << ' ' << Sigma1[0][1] << "	----	" << Sigma2[0][0] << ' ' << Sigma2[0][1] << endl;
cout << Sigma1[1][0] << ' ' << Sigma1[1][1] << "	----	" << Sigma2[1][0] << ' ' << Sigma2[1][1] << endl;

for(int q = 0; q < 10000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(data[q].x_value -1) * (data[q].x_value -1));
	valY1 = (-(data[q].y_value -1) * (data[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = (-(data[q].x_value -4) * (data[q].x_value -4));
	valY2 = (-(data[q].y_value -4) * (data[q].y_value -4));
	val2 = valX2 + valY2;

	//if val2 > than val1 then point belongs to first category
	if(val1 - val2 > 0 )
	{
		data[q].category = 1;
	}

	//if val1 > than val2 then point belongs to second category	
	else
	{
		data[q].category = 2;
	}

	//determine if misclassified
	if(data[q].category != data[q].mean)
	{
		error++;
	}
}
cout << endl <<"Printing error count for 2a: ";
cout  << endl << error;
/////////////////////////////////////////////////////////////////////////////////////////
//2b
/////////////////////////////////////////////////////////////////////////////////////////
//Reset variables
mean1[0] = 0.0;
mean1[1] = 0.0;
Sigma1[0][0] = 0.0;
Sigma1[0][1] = 0.0;
Sigma1[1][0] = 0.0;
Sigma1[1][1] = 0.0;


mean2[0] = 0.0;
mean2[1] = 0.0;
Sigma2[0][0] = 0.0;
Sigma2[0][1] = 0.0;
Sigma2[1][0] = 0.0;
Sigma2[1][1] = 0.0;

error = 0;

/////////////////////////
// Find Mean
/////////////////////////

for(int i = 0; i < 500; i++)
{
	mean1[0] += sampleArray[i].x_value;
	mean1[1] += sampleArray[i].y_value;
}
mean1[0] = mean1[0] / 500.0;
mean1[1] = mean1[1] / 500.0; 


for(int i = 500; i < 1000; i++)
{
	mean2[0] += sampleArray[i].x_value;
	mean2[1] += sampleArray[i].y_value;
}
mean2[0] = mean2[0] / 500.0; 
mean2[1] = mean2[1] / 500.0; 

//Pinrt mean
cout << endl << endl << "Printing Mean and covariance for 2b: " << endl;
cout << mean1[0] << " " << mean1[1] << "  -  " << mean2[0]<< " " << mean2[1] << endl << endl;
 

/////////////////////////
//Find covariance
/////////////////////////

for(int i = 0; i < 500; i++)
{
	sampleArray[i].x_value -= mean1[0];
	sampleArray[i].y_value -= mean1[1];

	Sigma1[0][0] += sampleArray[i].x_value * sampleArray[i].x_value* mean1[0];
	Sigma1[0][1] += sampleArray[i].x_value * sampleArray[i].y_value;
	Sigma1[1][0] += sampleArray[i].y_value * sampleArray[i].x_value;
	Sigma1[1][1] += sampleArray[i].y_value * sampleArray[i].y_value * mean1[0] * mean1[1];

	sampleArray[i].x_value += mean1[0];
	sampleArray[i].y_value += mean1[1];
}

Sigma1[0][0] = Sigma1[0][0] / 500.0;
Sigma1[0][1] = Sigma1[0][1] / 500.0;
Sigma1[1][0] = Sigma1[1][0] / 500.0;
Sigma1[1][1] = Sigma1[1][1] / 500.0; 


for(int i = 500; i < 1000; i++)
{
	sampleArray[i].x_value -= mean2[0];
	sampleArray[i].y_value -= mean2[1];

	Sigma2[0][0] += sampleArray[i].x_value * sampleArray[i].x_value * mean2[0];
	Sigma2[0][1] += sampleArray[i].x_value * sampleArray[i].y_value;
	Sigma2[1][0] += sampleArray[i].y_value * sampleArray[i].x_value;
	Sigma2[1][1] += sampleArray[i].y_value * sampleArray[i].y_value * mean2[0] * mean2[1];

	sampleArray[i].x_value += mean2[0];
	sampleArray[i].y_value += mean2[1];

}

Sigma2[0][0] = Sigma2[0][0] / 500.0;
Sigma2[0][1] = Sigma2[0][1] / 500.0;
Sigma2[1][0] = Sigma2[1][0] / 500.0;
Sigma2[1][1] = Sigma2[1][1] / 500.0; 

//Printing  Covariance
cout << Sigma1[0][0] << ' ' << Sigma1[0][1] << "	----	" << Sigma2[0][0] << ' ' << Sigma2[0][1] << endl;
cout << Sigma1[1][0] << ' ' << Sigma1[1][1] << "	----	" << Sigma2[1][0] << ' ' << Sigma2[1][1] << endl;

for(int q = 0; q < 1000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(sampleArray[q].x_value -1) * (sampleArray[q].x_value -1));
	valY1 = (-(sampleArray[q].y_value -1) * (sampleArray[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = (-(sampleArray[q].x_value -4) * (sampleArray[q].x_value -4));
	valY2 = (-(sampleArray[q].y_value -4) * (sampleArray[q].y_value -4));
	val2 = valX2 + valY2;

	//if val2 > than val1 then point belongs to first category
	if(val1 - val2 > 0 )
	{
		sampleArray[q].category = 1;
	}

	//if val1 > than val2 then point belongs to second category	
	else
	{
		sampleArray[q].category = 2;
	}

	//determine if misclassified
	if(sampleArray[q].category != sampleArray[q].mean)
	{
		error++;
	}
}
cout << endl <<"Printing error count for 2b: ";
cout << endl << error << endl << endl;

//return
 return 0;
}


//Implementation
double randomeDouble()
{
	return ((double)rand()/(double)RAND_MAX);
}

void Gauss(double*** array)
{
	
	*array = new double* [10000];
	for(int i = 0; i < 10000; i++)
	{
		(*array)[i] = new double[2];
	}


	double x1, x2, y1, y2 , w;

	for(int q = 0; q < 10000; q++)
	{
		do
		{
			x1 = 2.0 * randomeDouble() - 1.0;
			x2 = 2.0 * randomeDouble() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0 );

		w = sqrt( (-2.0 * log(w)) / w);
		(*array)[q][0] = x1 * w;
		(*array)[q][1] = x2 * w;
	}
}

void assignPoints(double** array, point* points, int percent)
{
	int i;

	for(i=0; i< 1000 * percent; i++)
	{
		points[i].x_value = array[i][0] +1.0;
		points[i].y_value = array[i][1] +1.0;

		points[i].mean = 1;
	}

	while(i<10000)
	{
		points[i].x_value = array[i][0] +4.0;
		points[i].y_value = array[i][1] +4.0;

		points[i].mean = 2;

		i++;
	}
}


