/*******************************************************************************
 File:          FindPaths.cpp
 Author:        Dandan Lin
 Date Created:  05/02/2017

 Copyright © 2017 Dandan Lin. All rights reserved.

 Description:	 This program implemented using a priority queue and use
                Dijkstra’s Algorithm to find the shortest paths from a given
                starting vertex to all vertices in the graph file.
 *******************************************************************************/

#include "Graph.h"
#include "dsexceptions.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
   if (argc != 3) {
      cout << "Usage: " << argv[0] << "<Graph_File> <Adjacency_Querie>\n";
      return 0;
   }

   ifstream inFile(argv[1]);
   if(!inFile.good()) {
      cout << "Unable to open file \"" << argv[1] << "\". Please double check. \n";

      exit(1);
   }

   int numberOfVertices;
   string str;

   // Read the numberOfVertices
   inFile >> numberOfVertices;
   int temp = numberOfVertices+1;
   Graph adjList(temp);

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

   // Output error message if the starting vertex is not valid
   if (atoi(argv[2])-1 < 0 || atoi(argv[2])-1 >= adjList.getAdjListSize()) {
      cout << "ERROR! Please enter a valid startng vertex \n";
      exit(1);
   } else {
      adjList.dijkstraAlgorithm(atoi(argv[2]));
   }

    return 0;
}
