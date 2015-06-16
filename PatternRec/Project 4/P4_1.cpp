///////////////////////////////////////////////////////////////////////////////
// Name 
// Date
// Project
// Other Info
///////////////////////////////////////////////////////////////////////////////

// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

// Other Includes
#include "config.h"
#include "libsvm/svm.cpp"

// Define

using namespace std;

// Function Headers



// Main
int main()
{
	//Varibles
	svm_problem Tr_1;
	svm_parameter param;
	svm_model *model;
	svm_node **node = new svm_node*[train_Size];
	svm_node **tests = new svm_node*[test_Size];
	string line;
	double* temp = new double[train_Size];
	//Tr_1.y = new double[train_Size];

	//////////////////////////////////////////////
	//Getting Training data
	/////////////////////////////////////////////

	//stringstream TtrFile;

	//Getting x
	//TtrFile << Path << "trPCA_" << Fold <<".txt";
	//ifstream X(TtrFile.str().c_str());
	ifstream X;
	X.open("genderdata/16_20/trPCA_01.txt");

	Tr_1.x = new svm_node*[train_Size];
	for(int q = 0; q < train_Size; q++)
	{
		node[q] = new svm_node[eigen_Size + 1];
		for(int i = 0; i < eigen_Size; i++)
		{
			node[q][i].index = i;
			//node[q][i].value = X.get();
			X >> node[q][i].value;
		}
		//Setting end of vector
		node[q][eigen_Size].index = -1;
		node[q][eigen_Size].value = 0.0;

		//gets rest of line
		getline(X, line);
	}
	Tr_1.x = node;
	X.close();

	// Getting y
	//TtrFile << Path << "TtrPCA_" << Fold <<".txt";
	//ifstream Y(TtrFile.str().c_str());
	//ifstream Y("genderdata/16_20/TtrPCA_01.txt");
	X.open("genderdata/16_20/TtrPCA_01.txt");

	for(int i = 0; i < train_Size; i++)
	{	
		X >> temp[i];
	}
	Tr_1.y = temp;
	X.close();

	//Setting l
	Tr_1.l = train_Size;

	/////////////////////////////////////////////
	//Training using data
	/////////////////////////////////////////////
	//Initalizing Param
	param.svm_type = 0;
	param.kernel_type = mode;
	param. degree = 3;
	param.gamma = (1.0);
	param.coef0 = 0.0;
	param.C = our_C; 
	
	// Checking parameters
	svm_check_parameter(&Tr_1, &param);

	//Generated model
	model = svm_train(&Tr_1, &param);

	/////////////////////////////////////////////
	//Testing using data
	/////////////////////////////////////////////
	//Initalizing test data
	
	X.open("genderdata/16_20/tsPCA_01.txt");

	for(int q = 0; q < test_Size; q++)
	{
		tests[q] = new svm_node[eigen_Size + 1];
		for(int i = 0; i < eigen_Size; i++)
		{
			tests[q][i].index = i;
			X >> tests[q][i].value;
		}
		//Setting end of vector
		tests[q][eigen_Size].index = -1;
		tests[q][eigen_Size].value = 0.0;

		//gets rest of line
		getline(X, line);

	}	
	X.close();

	/////////////////////////////
	//Call predict at this point
	/////////////////////////////

double testClass;
	for(int i = 0; i< test_Size; i++)
	{
		testClass = svm_predict(model, tests[i]);
		cout<<testClass<<" ";
	}

	cout<<endl;
	return 0;
}
