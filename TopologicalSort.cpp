/*******************************************************************************
 File:          TopologicalSort.cpp

 Created by Dandan Lin on 05/08/2017.
 Copyright © 2017 Dandan Lin. All rights reserved.

 Description:	This program will computes a sequence of vertices that satisfy
                the topological sorting sequence and output the sequence of
                vertices.
                The program will be terminated if a cycle is detected.
*******************************************************************************/

#include "Graph.h"
#include "dsexceptions.h"

#include <stdio.h>
#include <fstream>
#include <sstream>

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << "<Graph_File>\n";
        return 0;
    }

    // Open <Graph_File>
    // Output error message if file doesn't exist
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
   }

   inFile.close();
   if (adjList.isCyclic())
      cout << "Cycle found" << endl;
    else
      adjList.topologicalSort();

    return 0;
}
