#pragma once
#include "PathfindingAlgorithm.h"
class BFS : public PathfindingAlgorithm
{
public:
	BFS(Graph* graph) : PathfindingAlgorithm(graph) {}
	virtual std::vector<size_t> FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const override;
};

