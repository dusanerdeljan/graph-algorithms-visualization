#include "BFS.h"
#include <queue>
#include <set>

std::vector<size_t> BFS::FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const
{
	std::vector<size_t> path;
	std::queue<size_t> vertexQueue;
	std::set<size_t> visitedVertices;
	visitedVertices.insert(startVertex);
	vertexQueue.push(startVertex);
	size_t* parentMap = new size_t[m_Maze->m_VertexCount + 1];
	while (!vertexQueue.empty())
	{
		size_t currentVertex = vertexQueue.front();
		vertexQueue.pop();
		if (currentVertex == endVertex) break;
		std::vector<Graph::Edge> incidentEdges;
		m_Maze->GetIncidentEdges(currentVertex, incidentEdges);
		for (auto const& edge : incidentEdges)
		{
			size_t otherVertex = edge.vertexB;
			edgesExplored.push_back(edge);
			if (visitedVertices.find(otherVertex) == visitedVertices.end())
			{
				parentMap[otherVertex] = currentVertex;
				visitedVertices.insert(otherVertex);
				vertexQueue.push(otherVertex);
			}
		}
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
