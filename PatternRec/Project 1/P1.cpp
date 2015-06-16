///////////////////////////////////////////////////////////////////////////////
// Project 1
// CS479
// Nicholas Smith
// Brian Goga
///////////////////////////////////////////////////////////////////////////////
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

int main()
{
	srand(time(NULL));

	ofstream fout;

	double mean1[2][1] = {{1.0}, {1.0}};
	double mean2[2][1] = {{4.0}, {4.0}};
	double** pointArray;

	point* data = new point[10000];

	double x1, x2, y1, y2 , w;

	Gauss(&pointArray);



//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1 A
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//assign points a mean 
assignPoints(pointArray, data, 5);

double val1, val2, val3;
double valX1, valX2 , valY2, valY1;

//counter for misclassification
int error = 0;

//arithmetic values
valX1 = valY2 = 1 - 4;
val3 = 7;

//classify points
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

//cout error count
cout<<"---Printing error count for 1B---"<<endl;
cout << error << endl;

//print data to file

//print x_values
fout.open("text1_x.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].x_value<<endl;
	}
fout.close();

//print x_values
fout.open("text1_y.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].y_value<<endl;
	}
fout.close();

//print x_values
fout.open("text1_m.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].mean<<endl;
	}
fout.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1 B
//////////////////////////////////////////////////////////////////////////////////////////////////////////
assignPoints(pointArray, data, 7);
int error1B = 0;

for (int q = 0; q < 10000; q++)
{
//calculating X-mean * X-mean transpose of first mean
	valX1 = ((data[q].x_value -1) * (data[q].x_value -1));
	valY1 = ((data[q].y_value -1) * (data[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = (-(data[q].x_value -4) * (data[q].x_value -4));
	valY2 = (-(data[q].y_value -4) * (data[q].y_value -4));
	val2 = valX2 + valY2;

	val1 = val1 * (-.5);
	val2 = val2 * (-.5);

	val1 = val1 + log(.3);
	val2 = val2 + log(.7);


	if((val1 + val2) > 0 )
	{
		data[q].category = 1;
	}
	else
	{
		data[q].category = 2;
	}

	if(data[q].category != data[q].mean)
	{
		error1B++;
	}
}
cout<<"---Printing error count for 1B---"<<endl;
cout << error1B << endl;

//calculate Chernoff Bound
double betaPoints[20];
double coef, beta, decimal;
double top, bottom;
double temp[2];

for(int i = 0; i<20; i++)
{
	beta = i *.05;
	coef = (beta * (1-beta)) /2;

	temp[0] = beta + (1-beta);
	temp[1] = beta + (1-beta);

	top = temp[0] * temp[1];
	bottom = 1;

	decimal = .5 * log(top/bottom);

	betaPoints[i] = coef * (3 * 3 * (1/temp[0]) + 3 * 3 * (1/temp[1])) + decimal;
}

//output data to text files to be graphed
fout.open("C_Bound1.txt");
for(int i = 0; i<20; i++)
	{
		fout<<betaPoints[i]<<endl;
	}
fout.close();

fout.open("text2_x.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].x_value<<endl;
	}
fout.close();

//print x_values
fout.open("text2_y.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].y_value<<endl;
	}
fout.close();

//print x_values
fout.open("text2_m.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].mean<<endl;
	}
fout.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2 A
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//assign points a mean 
assignPoints(pointArray, data, 5);

double Sigma [2][2] = {{4,0},{0, 16}};

//counter for misclassification
int error2A = 0;

//arithmetic values
valX1 = valY2 = 1 - 4;
val3 = 7;

//classify points
for(int q = 0; q < 10000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(data[q].x_value -1) * (data[q].x_value -1));
	valY1 = (-(data[q].y_value -1) * (data[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = ((data[q].x_value -4) * (data[q].x_value -4) * .25);
	valY2 = ((data[q].y_value -4) * (data[q].y_value -4) * .0625);
	val2 = valX2 + valY2;

	val1 = val1 * (.25);
	val2 = val2 * (.25);


	//if val2 > than val1 then point belongs to first category
	if(val1 + val2 > -2 )
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
		error2A++;
	}
}

//cout error count
cout<<"---Printing error count for 2A---"<<endl;
cout << error2A << endl;

//print data to file

//print x_values
fout.open("text3_x.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].x_value<<endl;
	}
fout.close();

//print x_values
fout.open("text3_y.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].y_value<<endl;
	}
fout.close();

//print x_values
fout.open("text3_m.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].mean<<endl;
	}
fout.close();


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2 B
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//assign points a mean 
//assign points a mean 
assignPoints(pointArray, data, 7);

//counter for misclassification
int error2B= 0;

//arithmetic values
valX1 = valY2 = 1 - 4;
val3 = 7;

//classify points
for(int q = 0; q < 10000; q++)
{

	//calculating X-mean * X-mean transpose of first mean
	valX1 = (-(data[q].x_value -1) * (data[q].x_value -1));
	valY1 = (-(data[q].y_value -1) * (data[q].y_value -1));
	val1 = valX1 + valY1;

	//calculating X-mean * X-mean transpose of second mean
	valX2 = ((data[q].x_value -4) * .25 * (data[q].x_value -4));
	valY2 = ((data[q].y_value -4) * .0625 * (data[q].y_value -4));
	val2 = valX2 + valY2;

	val1 = val1 * (.25);
	val2 = val2 * (.25);

	/*val1 = val1 + log(.7);
	val2 = val2 + log(.3);*/

	//if val2 > than val1 then point belongs to first category
	if(val1 + val2 > -2 )
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
		error1B++;
	}
}

//cout error count
cout<<"---Printing error count for 2B---"<<endl;
cout << error1B << endl;

//calculate Chernoff Bound

for(int i = 0; i<20; i++)
{
	beta = i *.05;
	coef = (beta * (1-beta)) /2;

	temp[0] = beta + (1-beta) * 4;
	temp[1] = beta + (1-beta) * 16;

	top = temp[0] * temp[1];
	bottom = pow(64, (1-beta));

	decimal = .5 * log(top/bottom);

	betaPoints[i] = coef * (3 * 3 * (1/temp[0]) + 3 * 3 * (1/temp[1])) + decimal;
}

//output data to text files to be graphed
fout.open("C_Bound2.txt");
for(int i = 0; i<20; i++)
	{
		fout<<betaPoints[i]<<endl;
	}
fout.close();

//print x_values
fout.open("text4_x.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].x_value<<endl;
	}
fout.close();

//print x_values
fout.open("text4_y.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].y_value<<endl;
	}
fout.close();

//print x_values
fout.open("text4_m.txt");
for(int i = 0; i<10000; i++)
	{
		fout<<data[i].mean<<endl;
	}
fout.close();



	delete pointArray;
	delete data;
	return 0;
}