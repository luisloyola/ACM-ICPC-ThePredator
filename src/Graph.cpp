// Código de grafos basado en:
// http://www.algolist.net/Data_structures/Graph/Internal_representation

#include "Graph.hpp"
#include <iostream>

Graph::Graph(int vertexCount) 
{
	this->vertexCount = vertexCount;
	adjacencyMatrix = new bool*[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		adjacencyMatrix[i] = new bool[vertexCount];
		for (int j = 0; j < vertexCount; j++)
		{
			adjacencyMatrix[i][j] = false;
		}
	}
}

void Graph::addEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount)
	{
		adjacencyMatrix[i][j] = true;
		adjacencyMatrix[j][i] = true;
	}
}

void Graph::removeEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount)
	{
		adjacencyMatrix[i][j] = false;
		adjacencyMatrix[j][i] = false;
	}
}

bool Graph::isEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount)
	{	
		return adjacencyMatrix[i][j];
	}
	else
	{
		return false;
	}
}

void Graph::print()
{
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)	
		{
			std::cout << adjacencyMatrix[i][j];
		}
		std::cout << std::endl;
	}
}

void Graph::flood(int i, bool* arr)
{
	//std::cout <<"I:" << i << std::endl;
	if(arr[i]==false)
	{
		//std::cout << i << std::endl;
		arr[i]=true;
		//std::cout << "arr[i]=true" << std::endl;
		for (int j = 0; j < vertexCount; j++)
		{
			//std::cout << "(i,j)="<<i <<","<<j << std::endl;
			if (this->adjacencyMatrix[i][j] == true)
			{
				//	std::cout << "entró if" << std::endl;
				flood(j,arr);	
			}
			//std::cout << "no if" << std::endl;
		}

	}
}


Graph::~Graph()
{
	for (int i = 0; i < vertexCount; i++)
	{
		delete[] adjacencyMatrix[i];
	}
	delete[] adjacencyMatrix;
}
