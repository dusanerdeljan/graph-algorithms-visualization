#pragma once
#include "Graph.h"

class Partition
{
public:
	struct Position
	{
		size_t parent;
		size_t size;
	};
private:
	Position* m_Positions;
public:
	Partition(size_t numVertices);
	~Partition();
	size_t Find(int vertex);
	void Union(int x, int y);
	bool DoesMakeCycle(const Graph::Edge& edge);
	void AddEdge(const Graph::Edge& edge);
};

