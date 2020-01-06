#pragma once
#include "Graph.h"
#include <vector>

class PathfindingAlgorithm
{
protected:
	Graph* m_Maze;
public:
	PathfindingAlgorithm(Graph* graph);
	virtual std::vector<size_t> FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const = 0;
};

