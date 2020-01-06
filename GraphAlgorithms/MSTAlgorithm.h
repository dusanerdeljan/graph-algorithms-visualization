#pragma once
#include "Graph.h"
class MSTAlgorithm
{
protected:
	Graph* m_Graph;
	std::vector<Graph::Edge> m_Edges;
public:
	MSTAlgorithm(Graph* graph);
	virtual Graph* MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze=false) = 0;
};

