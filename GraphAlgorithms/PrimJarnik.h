#pragma once
#include "MSTAlgorithm.h"

class PrimJarnik : public MSTAlgorithm
{
public:
	PrimJarnik(Graph* graph) : MSTAlgorithm(graph) {}
	void MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze=false) override;
};

