#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>

class Graph 
{
	private:

		bool** adjacencyMatrix;
		int vertexCount;

	public:

		Graph(int vertexCount);

		void addEdge(int i, int j);

		void removeEdge(int i, int j);

		bool isEdge(int i, int j);

		void print();

		void flood(int i, bool* arr); 

		~Graph();
};

#endif
