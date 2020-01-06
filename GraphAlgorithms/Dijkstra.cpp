#include "Dijkstra.h"
#include <set>
#include <unordered_map>
#include <algorithm>

#define INF 99999999

struct HeapEntry
{
	size_t vertex;
	size_t distance;
	HeapEntry() : vertex(INF), distance(INF) {}
	HeapEntry(size_t v, size_t d) : vertex(v), distance(d) {}
};

std::vector<size_t> Dijkstra::FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const
{
	std::vector<size_t> path;
	std::unordered_map<size_t, size_t> distanes;
	for (size_t vertex = 1; vertex <= m_Maze->m_VertexCount; vertex++)
	{
		distanes[vertex] = INF;
	}
	std::unordered_map<size_t, HeapEntry> entryMap;
	std::set<size_t> visitedVertices;
	std::vector<HeapEntry*> unvisitedNodes;
	size_t* parentMap = new size_t[m_Maze->m_VertexCount + 1];
	distanes[startVertex] = 0;
	entryMap[startVertex] = HeapEntry(startVertex, 0);
	unvisitedNodes.push_back(&entryMap[startVertex]);
	while (!unvisitedNodes.empty())
	{
		HeapEntry* minVertex = unvisitedNodes.back();
		unvisitedNodes.pop_back();
		size_t currentVertex = minVertex->vertex;
		if (distanes[currentVertex] == INF || currentVertex == endVertex) break;
		std::vector<Graph::Edge> incidentEdges;
		m_Maze->GetIncidentEdges(currentVertex, incidentEdges);
		for (auto const& edge : incidentEdges)
		{
			size_t neighbour = edge.vertexB;
			size_t newDistance = distanes[currentVertex];
			if (visitedVertices.find(neighbour) == visitedVertices.end())
			{
				if (newDistance < distanes[neighbour])
				{
					edgesExplored.push_back(edge);
					if (entryMap.find(neighbour) == entryMap.end())
					{
						entryMap[neighbour] = HeapEntry(neighbour, newDistance);
						unvisitedNodes.push_back(&entryMap[neighbour]);
						std::sort(unvisitedNodes.begin(), unvisitedNodes.end(), [](HeapEntry* a, HeapEntry* b) { return a->distance > b->distance; });
					}
					else
					{
						entryMap[neighbour].distance = newDistance;
						std::sort(unvisitedNodes.begin(), unvisitedNodes.end(), [](HeapEntry* a, HeapEntry* b) { return a->distance > b->distance; });
					}
					distanes[neighbour] = newDistance;
					parentMap[neighbour] = currentVertex;
				}
			}
		}
		visitedVertices.insert(currentVertex);
	}
	size_t current = endVertex;
	while (current != startVertex)
	{
		path.push_back(current);
		current = parentMap[current];
	}
	path.push_back(startVertex);
	delete[] parentMap;
	return path;
}
