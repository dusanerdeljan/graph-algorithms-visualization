#pragma once
#include "MSTAlgorithm.h"

class Kruskal : public MSTAlgorithm
{
public:
	Kruskal(Graph* graph) : MSTAlgorithm(graph) {}
	Graph* MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze=false) override;
};

