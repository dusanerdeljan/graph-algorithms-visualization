#include "PrimJarnik.h"
#include <algorithm>
#include <unordered_map>

#define INF 99999999

struct PQEntry
{
	size_t cost;
	size_t vertex;
	Graph::Edge* edge;

	PQEntry() : cost(INF), vertex(INF), edge(nullptr) {}
	PQEntry(size_t c, size_t v, Graph::Edge* e) : cost(c), vertex(v), edge(e) {}
};

Graph* PrimJarnik::MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze)
{
	Graph* mstGraph = maze ? new Graph(m_Graph->m_VertexCount) : nullptr;
	std::unordered_map<size_t, size_t> treeBounds;
	std::vector<PQEntry*> priorityQueue;
	std::unordered_map<size_t, PQEntry> entryMap;
	for (size_t vertex = 0; vertex < m_Graph->m_VertexCount; vertex++)
	{
		treeBounds[vertex+1] = treeBounds.size() == 0 ? 0 : INF;
		entryMap[vertex+1] = PQEntry(treeBounds[vertex+1], vertex+1, nullptr);
		priorityQueue.push_back(&entryMap[vertex+1]);
	}
	std::sort(priorityQueue.begin(), priorityQueue.end(), [](PQEntry* a, PQEntry* b) { return a->cost > b->cost; });
	while (!priorityQueue.empty())
	{
		PQEntry* minElement = priorityQueue.back();
		priorityQueue.pop_back();
		if (minElement->edge != nullptr)
		{
			if (maze) mstGraph->AddEdge(minElement->edge);
			mst.push_back(*minElement->edge);
			edgeIncluded.push_back(true);
		}
		std::vector<Graph::Edge> incidentEdges;
		m_Graph->GetIncidentEdges(minElement->vertex, incidentEdges);
		for (const auto& edge : incidentEdges)
		{
			if (entryMap.find(edge.vertexB) != entryMap.end())
			{
				if (edge.cost < treeBounds[edge.vertexB])
				{
					treeBounds[edge.vertexB] = edge.cost;
					entryMap[edge.vertexB].cost = edge.cost;
					entryMap[edge.vertexB].edge = new Graph::Edge(edge.vertexA, edge.vertexB, edge.cost);
					std::sort(priorityQueue.begin(), priorityQueue.end(), [](PQEntry* a, PQEntry* b) { return a->cost > b->cost; });
				}
			}
		}
		delete entryMap[minElement->vertex].edge;
		entryMap.erase(minElement->vertex);
	}
	return mstGraph;
}
