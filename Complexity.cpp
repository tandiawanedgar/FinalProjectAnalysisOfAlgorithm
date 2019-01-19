#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include <time.h>

#define V 7 

using namespace std;

int minDistance(int dist[], bool sptSet[]) ;
int printSolution(int dist[], int n);
void dijkstra(int graph[V][V], int src);

int minKey(int key[], bool mstSet[]);
int printMST(int parent[], int n, int graph[V][V]);
void primMST(int graph[V][V]);

string RainCheck();
int CarPlate(string a);
int Distance(int a);
void Price(int d, string r);

int main()
{
	int Destination;
	string Car;
	cout<< "Input Destination:\n1. Senayan City\n2. Plaza Indonesia\n3. Central Park\n4. Taman Anggrek\nINPUT = ";
	cin>> Destination;
	//Fix the Destination up to 4 destination available
	cout<<"\nInput Car Number:\n";
	cin>> Car;
	CarPlate(Car);
	int dist = Distance(Destination-1);
	string r;
	r = RainCheck();
    Price(dist, r);
	system("pause");
	cout<< "\n\nComparison of Dijsktra VS Prims ( Central Park to FX)\n\n";
	int graph[V][V] = {{0, 1, 0, 0, 0, 0, 0}, 
                      {1, 0, 4, 0, 0, 0, 0}, 
                      {0, 4, 0, 1, 0, 0, 0}, 
                      {0, 0, 1, 0, 2, 0, 0}, 
                      {0, 0, 0, 2, 0, 1, 0}, 
                      {0, 0, 0, 0, 1, 0, 2}, 
                      {0, 0, 0, 0, 0, 2, 0}}; 
    dijkstra(graph, 0);
    cout<<endl;
    primMST(graph);
   
}


/*
0 Tanjung duren
1 Arjuna Utara 
2 Arteri Kelapa 2 raya
3 Arteri permata hijau
4 Asia Afrika
5 Jendral Sudirman
6 FX

0-1 = 1km
1-2 = 4km
2-3 = 1km
3-4 = 2kmf
4-5 = 1km
5-6 = 2km
*/


//User Interface
int Distance(int a)
{
	int DistList[4] = {2,14,11,10};
	cout<< "Distance to Destination: "<< DistList[a]<<endl;
	return DistList[a];
	
}
int CarPlate(string a)
{
	string CarPlate = a;
	//Input the Car Plate
	int numCheck[2] = {CarPlate[3]-48, CarPlate[4]-48};
	//Find if the CarPlate is Even or Odd
	if(numCheck[0]%2==1 || numCheck[1]%2==1)
	{
		cout<< "\nCar is Odd\n";
	}
	else
	{
		cout<< "\nCar is Even\n";
	}
}
string RainCheck()
{
	cout<< "NOTE:";
	srand (time(NULL));
	int Random = rand()%2+1;
	if(rand()%2!=0)
	{
		cout<< "\nIts Raining\n";
		cout << "Price X 1.5\n\n";
		return "n";
	}
	else
	{
		cout << "\nIts Not Raining\n";
		cout << "Price Normal\n\n";
		return "r";
	}	
}
void Price(int d, string r)
{
	double x;
	if(r =="r")
	{
		x = 1;
	}
	else
	{
		x = 1.5;
	}
	double basePrice = 5000;
	double totalPrice = d/2*5000*x;
	cout<< totalPrice<<endl<<endl;
}


// DJIKSTRA Algorithm
int minDistance(int dist[], bool sptSet[]) 
{ 
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) 
         min = dist[v], min_index = v; 
   
   return min_index; 
} 
   
int printSolution(int dist[], int n) 
{ 
   printf("Vertex   Distance from Source\n"); 
   for (int i = 0; i < V; i++) 
      printf("%d \t\t %d\n", i, dist[i]); 
} 
   
void dijkstra(int graph[V][V], int src) 
{ 
     int dist[V];     
     bool sptSet[V]; 
	 for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
   
     dist[src] = 0; 
   
     for (int count = 0; count < V-1; count++) 
     { 
       int u = minDistance(dist, sptSet); 
   
       sptSet[u] = true; 
   
       for (int v = 0; v < V; v++) 
   
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  
                                       && dist[u]+graph[u][v] < dist[v]) 
            dist[v] = dist[u] + graph[u][v]; 
     } 
   
     printSolution(dist, V); 
} 


//Prims Algorithm
int minKey(int key[], bool mstSet[]) 
{ 

int min = INT_MAX, min_index; 
  
for (int v = 0; v < V; v++) 
    if (mstSet[v] == false && key[v] < min) 
        min = key[v], min_index = v; 
  
return min_index; 
} 
  

int printMST(int parent[], int n, int graph[V][V]) 
{ 
printf("Edge \tWeight\n"); 
for (int i = 1; i < V; i++) 
    printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]); 
} 
  

void primMST(int graph[V][V]) 
{ 
    int parent[V];  
	int key[V];  
	bool mstSet[V];  
  
   
    for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
  
    
    key[0] = 0;      
    parent[0] = -1; 
  
  
    for (int count = 0; count < V-1; count++) 
    { 
       
        int u = minKey(key, mstSet); 
  
        
        mstSet[u] = true; 
  
        
        for (int v = 0; v < V; v++) 
  
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
            parent[v] = u, key[v] = graph[u][v]; 
    } 
  
  
    printMST(parent, V, graph); 
} 
 

