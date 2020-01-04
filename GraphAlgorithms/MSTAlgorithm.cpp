#include "MSTAlgorithm.h"
#include <algorithm>

MSTAlgorithm::MSTAlgorithm(Graph* graph) : m_Graph(graph)
{
	m_Edges = graph->m_Edges;
}
