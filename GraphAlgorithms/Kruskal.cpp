#include "Kruskal.h"
#include "Partition.h"
#include <algorithm>

Graph* Kruskal::MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze)
{
	Graph* mstGraph = maze ? new Graph(m_Graph->m_VertexCount) : nullptr;
	size_t i = 0;
	std::sort(m_Edges.begin(), m_Edges.end(), [](const Graph::Edge& e1, const Graph::Edge& e2)
		{
			return e1.cost < e2.cost;
		});
	Partition partition(m_Graph->m_VertexCount);
	size_t mstVertices = 0;
	while (mstVertices < m_Graph->m_VertexCount - 1 && i < m_Graph->m_Edges.size())
	{
		Graph::Edge edge = m_Edges[i++];
		if (!maze) mst.push_back(edge);
		if (!partition.DoesMakeCycle(edge))
		{
			mstVertices++;
			if (maze)
			{
				mstGraph->AddEdge(&edge);
				mst.push_back(edge);
			}
			edgeIncluded.push_back(true);
			partition.AddEdge(edge);
		}
		else if (!maze) edgeIncluded.push_back(false);
	}
	return mstGraph;
}
