////////////////////////////
//  CPE 400               //
//  Brian Goga            //
//  Battery Life of       //
//  Sensor nodes          //
////////////////////////////

//Header Files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

//Structs
struct Node
{
  int batteryLife;
  bool isOn;
  queue<int> data;
  int waitTime;
  int sleepCounter;

};

//Functions
int senseData();
float simulation(float sleeplength);
int findBest(float *array);

//main
int main()
{
  //variables
  float results[9];
  float ratios[9] = {0, 0.3, 0.5, 0.8, 1, 1.5, 2, 2.5, 3};
  int best = 0;
  
  //Rand it up
  srand(time(NULL));
  
  for(int i = 0; i < 9; i++)
  {
    //run through all the ratios and save results in an array
    cout<<endl<<"Testing a ratio of " << ratios[i]<<" sleep/wake cycle"<<endl;
    results[i] = simulation(ratios[i]);
    
  }
  
  //used to find the best ratio in results
  cout<<endl;
  cout<<"Finding best sleep/wake ratio..."<<endl;
  best = findBest(results);
  
  cout<<"The best sleep/wake ratio was: " << ratios[best] << " with a efficency of " << results[best] <<endl;
  cout<<"This means the nodes only slept " << ratios[best] * 10 <<" percent of the time."<<endl<<endl;
  
  //going home
  return 0;
}

//Implementations
int senseData()
{
  return rand() % 1000;
}

float simulation(float sleeplength)
{
  //variables
  vector<Node> sensorArray;
  Node tempNode;
  int cycleCounter = 0;
  int throughput = 0;
  int offset = 0;
  float ratio;
  
  //initialize Vector
  tempNode.batteryLife = 100;
  tempNode.isOn = false;
  tempNode.sleepCounter = 0;
  ratio = sleeplength;
  
  for(int i = 0; i<9; i++)
  {
    //create offset so all sensors are not on at the same time
    offset = rand() %5;
    tempNode.waitTime = offset;
    sensorArray.push_back(tempNode);
    
  }
  
  //Simulate sensors communicating
  while(sensorArray[0].batteryLife > 0)
  {
    
    //go through each node and turn on after wait time
    if(cycleCounter < 5)
    {
      for(int i = 0; i< 9; i++)
      {
        if(cycleCounter == sensorArray[i].waitTime)
        {
          sensorArray[i].isOn = true;
        }
      }
    }
    
    //decrement battery life
    for(int i = 0; i<9; i++)
    {
      if(sensorArray[i].isOn)
      {
        sensorArray[i].batteryLife = sensorArray[i].batteryLife - 3;
        
        //try to send data
        //Check if recieving node is awake
        if(i == 0 && !sensorArray[i].data.empty())
        {
          //Node 0 is home so it will cout what it recieves
          cout<<"I have recieved data: " << sensorArray[i].data.front() <<endl;
          sensorArray[i].data.pop();
          
          //increament throughput counter
          throughput++;
        }
        else if(sensorArray[(i-1)/2].isOn && !sensorArray[i].data.empty())
        {
          //all other nodes can send data
          //cout<<"I am node: " << i <<" and I am pushing: "<< sensorArray[i].data.front() <<" to node: "<< (i-1)/2 << endl;
          sensorArray[(i-1)/2].data.push(sensorArray[i].data.front());
          sensorArray[i].data.pop();
          
        }
        
        //furthermore, Nodes 4->8 are sensor nodes and create data
        if(i > 3)
        {
          sensorArray[i].data.push(senseData());
        }
        
      }
      
      //even being off drains battery
      else
      {
        sensorArray[i].batteryLife = sensorArray[i].batteryLife - 1;
        sensorArray[i].sleepCounter++;
      }
    }
    
    //Sensors are only on for 10 cycles at a time
    //Sensors need to be turned off if on for more than 10 cycles
    //Sensors need to be turned on if off for more than 10 * ratio cycles
    for(int i = 0; i<9; i++)
    {
      if((sensorArray[i].isOn) && ((cycleCounter - sensorArray[i].waitTime) % 10 == 0) && cycleCounter > 4)
      {
        sensorArray[i].isOn = false;
      }
      else if ((!sensorArray[i].isOn) && (sensorArray[i].sleepCounter == (10 * ratio) ))
      {
        sensorArray[i].isOn = true;
        sensorArray[i].sleepCounter = 0;
      }
    }
    
    //count cycles alive
    cycleCounter++;
  }
  
  cout<<"The Home node lasted: "<<cycleCounter<<" cycles out of "<< tempNode.batteryLife<<endl;
  cout<<"The throughput of this ratio was: "<<throughput<<" units of data."<<endl; 
  cout<<"This sleep/wake ratio efficency is: "<<float(throughput)/float(cycleCounter)<<" percent."<<endl;
  
  return float(throughput)/float(cycleCounter);
}

int findBest(float *array)
{
  int best = array[0];
  
  //loop through passed array looking for best ratio and return it
  for(int i = 0; i < 9; i++)
  {
    if(array[i] > array[best])
    {
      best = i;
    }
  }
  
  
  return best;
}





























