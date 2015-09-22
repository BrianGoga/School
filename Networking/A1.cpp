///////////////////////////////////////////////////////////////////////////////
// Assignment 1
// CPE400
// Brian Goga
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>

using namespace std;

//Functions
void clearArray(int *array, int size);

void arrayOut(int *array);

//Main
int main()
{
	//variables
	int packetCounter = 0;
	int lowCounter = 0;
	int medCounter = 0;
	int hiCounter = 0;
	int packetArray[1000];
	int packetDrop = 0;

	srand(time(NULL));

	//Initialize Array
	clearArray(packetArray, 1000);

	//Start sending packets
	for(int i=0; i<1000; i++)
	{
		//create variable to keep track of packets this cycle
		int currentPackets = 0;

		//determine if packet is created
		for(int j=0; j<35; j++)
		{
			int packFlag = 0;
			packFlag = rand() % 100 +1;

			if(packFlag <= 40)
			{
				//if packet is created increament packet counters
				packetCounter++;
				currentPackets++;

				//if more than 18 packets are created, then packets are dropped
				if(currentPackets > 18)
				{
					packetDrop++;
				}

			}

		}
		//save how many packets were created this cycle
		packetArray[i] = currentPackets;

		//increament counter if # of packets were 10, 15, or 20 exactly
		if(currentPackets == 10)
		{
			lowCounter++;

		}

		else if(currentPackets == 15)
		{
			medCounter++;
		}

		else if(currentPackets == 20)
		{
			hiCounter++;
		}

	}

	//print results
	cout<<"Total # of packets created: " << packetCounter <<endl;
	cout<<"# of cycles were 10 packets were sent: " << lowCounter << endl;
	cout<<"# of cycles were 15 packets were sent: " << medCounter << endl;
	cout<<"# of cycles were 20 packets were sent: " << hiCounter << endl;
	cout<<"# of packets dropped: " << packetDrop <<endl;
	
	//print array to file
	arrayOut(packetArray);

	//Closing shop and heading home
	return 0;
}

//Implementation
void clearArray(int *array, int size )
{
	for(int i = 0; i<size; i++)
	{
		array[i] = 0;
	}


}

void arrayOut(int* array)
{
	ofstream fout;
	fout.open("packets.txt");

	for(int i=0; i<1000; i++)
	{
		fout<<array[i]<<" ";
	}

	fout.close();
}



