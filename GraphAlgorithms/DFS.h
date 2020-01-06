#pragma once
#include "PathfindingAlgorithm.h"

class DFS : public PathfindingAlgorithm
{
public:
	DFS(Graph* graph) : PathfindingAlgorithm(graph) {}
	virtual std::vector<size_t> FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const override;
};

