/*******************************************************************************
 File:          Graph.h

 Created by Dandan Lin on 05/08/2017.
 Copyright © 2017 Dandan Lin. All rights reserved.

 Description:	This Graph class has following functionalities:
   void addEdge(int startVertex_, int endVertex_, float edgeWeight_)

*******************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <list>
#include <stack>
#include <queue>

#include <iostream>
using namespace std;

#define INF INT_MAX
typedef pair<int, float> vertexPair;

class Graph {
   int numberOfVertices;
   list<pair<int, float>> *adjList;

public:
   Graph(int numberOfVertices_) {
      this->numberOfVertices = numberOfVertices_;
      adjList = new list<pair<int, float>> [numberOfVertices+1];
   }

   // Add an edge to the adjList
   void addEdge(int startVertex_, int endVertex_, float edgeWeight_) {
      adjList[startVertex_].push_back(make_pair(endVertex_, edgeWeight_));
   }

   // Check if two vertices are connected
   bool isConnected(int startVertex_, int endVertex_) {
      list<pair<int, float> >::iterator i;
      for (i = adjList[startVertex_].begin(); i != adjList[startVertex_].end(); ++i) {
         if ((*i).first == endVertex_) {
            return true;
         }
      }
      return false;
   }

   // Obtain the edgeWeight for a specific edge starts from startVertex_ and ends on endVertex_
   float getEdgeWeight(int startVertex_, int endVertex_) {
      list<pair<int, float> >::iterator i;
      for (i = adjList[startVertex_].begin(); i != adjList[startVertex_].end(); ++i) {
         if ((*i).first == endVertex_) {
            return (*i).second;
         }
      }
      return -1;
   }

   // Obtain the adjList size
   int getAdjListSize() {
      return numberOfVertices;
   }

   // Function for testing if the graph was created correctly
   void printAdjList() {
      // Loop throgh all vertices and print out it's corresponding endVertex and edgeWeight
      for (int j = 0; j < numberOfVertices; ++j) {
      cout << j << ": ";
         list<pair<int, float> >::iterator i;
         for (i = adjList[j].begin(); i != adjList[j].end(); ++i) {
            cout << (*i).first << " " << (*i).second << " ";
         }
         cout << endl;
      }
   }

   // DijkstraAlgorithm function is created for completion of part two it will generte the shorted path from the sourceVertex to all other vertices using STL priorityQueue
   void dijkstraAlgorithm(int sourceVertex) {
      priority_queue<vertexPair, vector<vertexPair>, greater<vertexPair>> priorityQueue;

      // Set all the distance to Infinity
      vector<float> vertexDistance(numberOfVertices, INF);

      // Set the sourceVertex's distance to 0
      priorityQueue.push(make_pair(0, sourceVertex));
      vertexDistance[sourceVertex] = 0;

      // An path variaiable that helps to stare all the possible shortest path
      int path[numberOfVertices];
      // Initialize paths to -1
      for (int i = 0; i < numberOfVertices; ++i) {
         path[i] = -1;
      }

      // Whihle the priorityQueue contains the element
      while (!priorityQueue.empty()) {
         // Let minV be the smallest item in the priorityQueue
         int minV = priorityQueue.top().second;
         priorityQueue.pop();

         vector<int> temp;
         list<pair<int, float>>::iterator i;
         for (i = adjList[minV].begin(); i != adjList[minV].end(); ++i) {
            int tempV = (*i).first;
            float weight = (*i).second;

            if (vertexDistance[tempV] > vertexDistance[minV] + weight) {
               //cout <<"pos " << tempV << " Testing " << vertexDistance[tempV]  << " " << vertexDistance[u] + weight << endl;
               vertexDistance[tempV] = vertexDistance[minV] + weight;
               priorityQueue.push(make_pair(vertexDistance[tempV], tempV));
               // Store the path to the path array
               path[tempV] = minV;
            }
         }
      }
      // Loop to print out the paths and weight
      for (int i = 1; i < numberOfVertices; ++i) {
         cout << i << ": ";
         if (sourceVertex == i) {
            cout << i ;
         } else {
            printPath(path, i);
            cout << i;
         }
         cout << " (Cost: "<< vertexDistance[i] << ") \n";
      }
   }

   // Function printPath will print out all the paths from the sourceVertex to all other vertices
   void printPath(int predecessorVertex[], int end) {
      if (predecessorVertex[end] == -1)
         return;
      // Recursively calls the printPath
      printPath(predecessorVertex, predecessorVertex[end]);
      cout << predecessorVertex[end] << ", ";
   }

   bool isCyclicUtil(int currentNode, bool visited[], bool *recursionStack) {
      if(visited[currentNode] == false) {
         // Mark the current node as visited and part of recursion stack
         visited[currentNode] = true;
         recursionStack[currentNode] = true;

         // Recur for all the vertices adjListacent to this vertex
         list<pair<int, float>>::iterator i;
         for(i = adjList[currentNode].begin(); i != adjList[currentNode].end(); ++i) {
            if (!visited[(*i).first] && isCyclicUtil((*i).first, visited, recursionStack))
               return true;
            else if (recursionStack[(*i).first])
               return true;
         }

      }
      recursionStack[currentNode] = false;  // remove the vertex from recursion stack
      return false;
   }

   // Returns true if the graph contains a cycle, else false.
   bool isCyclic() {
      bool *visited = new bool[numberOfVertices];
      bool *recursionStack = new bool[numberOfVertices];
      for(int i = 0; i < numberOfVertices; i++) {
         visited[i] = false;
         recursionStack[i] = false;
      }

      // Call isCyclicUtil to detect cycle
      for(int i = 0; i < numberOfVertices; i++)
         if (isCyclicUtil(i, visited, recursionStack))
            return true;

      return false;
   }

   void topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {
      // Mark the current node as visited.
      visited[v] = true;

      // Recur for all the vertices adjListacent to this vertex
      list<pair<int, float>>::iterator i;
      for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
      if (!visited[(*i).first])
         topologicalSortUtil((*i).first, visited, Stack);

      // Push current vertex to stack which stores result
      Stack.push(v);
   }

   void topologicalSort() {
      stack<int> Stack;

      // Mark all the vertices as not visited
      bool *visited = new bool[numberOfVertices];
      for (int i = 0; i < numberOfVertices; i++) {
         visited[i] = false;
      }
      // Call the recursive helper function to store Topological
      // Sort starting from all vertices one by one
      for (int i = 0; i < numberOfVertices; i++) {
         if (visited[i] == false) {
            topologicalSortUtil(i, visited, Stack);
         }
      }

      int counter = 0;
      // Output the sorted contents in the stack
      while (Stack.empty() == false && counter < numberOfVertices) {
         cout << Stack.top() << " ";
         Stack.pop();

         counter++;
      }
      cout << endl;
   }

};

#endif /* Graph_h */
