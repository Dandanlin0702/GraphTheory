/*******************************************************************************
File:          CreateGraphAndTest.cpp

Created by Dandan Lin on 05/08/2017.
Copyright © 2017 Dandan Lin. All rights reserved.

Description:	This program will read a directed graph a text file and create
a graph using adjacency list and test it
*******************************************************************************/
#include "Graph.h"

#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
   if (argc != 3) {
      cout << "Usage: " << argv[0] << "<Graph_File> <Adjacency_Querie>\n";
      return 0;
   }
   // Create A Graph

   // Open <Graph_File>
   // Throw error messages if user provide an invalid <Graph_File>
   ifstream inFile(argv[1]);
   if(!inFile.good()) {
      cout << "Unable to open file \"" << argv[1] << "\". Please double check. \n";
      return 0;
   }

   int numberOfVertices;
   string str;

   // Read the numberOfVertices
   inFile >> numberOfVertices;
   Graph adjList(numberOfVertices);

   while (!inFile.eof()) {
      // Read the rest of the file line by line and parse it
      while (getline(inFile, str)) {
         int startVertex, endVertex = 0;
         float edgeWeight = 0;
         stringstream ss(str);
         // Obtain the startVetex
         ss >> startVertex;

         if (ss.eof()) {
            if (startVertex == 0) {
               ;
            } else {
               adjList.addEdge(startVertex, endVertex, edgeWeight);
            }
         } else {
            while (!ss.eof()) {
               ss >> endVertex >> edgeWeight;
               adjList.addEdge(startVertex, endVertex, edgeWeight);
            }
         }
      }
      // Testing
      // adjList.printAdjList();
   }

   inFile.close();

   // Testing the graph created above
   // Open <Adjacency_Querie> file
   // Throw error messages if user provide an invalid <Adjacency_Querie> file
   ifstream testFile(argv[2]);
   if(!testFile.good()) {
      cout << "Unable to open file \"" << argv[2] << "\". Please double check. \n";
      return 0;
   }

   string temp;
   int testStartVertex, testEndVertex;

   while (getline(testFile, temp)) {
      stringstream sss(temp);
      sss >> testStartVertex >> testEndVertex;

      bool isConnected = adjList.isConnected(testStartVertex, testEndVertex);
      float testEdgeWeight = adjList.getEdgeWeight(testStartVertex, testEndVertex);

      if (isConnected) {
         cout << testStartVertex << " " << testEndVertex << ": Connected weight of edge is " << testEdgeWeight << endl;
      } else {
         cout << testStartVertex << " " << testEndVertex << ": Not connected \n";
      }
   }

   testFile.close();

   return 0;
}
