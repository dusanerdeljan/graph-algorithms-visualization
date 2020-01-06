#include "DFS.h"
#include <stack>
#include <set>

std::vector<size_t> DFS::FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const
{
	std::vector<size_t> path;
	std::stack<size_t> vertexStack;
	std::set<size_t> visitedVertices;
	vertexStack.push(startVertex);
	size_t* parentMap = new size_t[m_Maze->m_VertexCount + 1];
	while (!vertexStack.empty())
	{
		size_t currentVertex = vertexStack.top();
		vertexStack.pop();
		if (currentVertex == endVertex) break;
		visitedVertices.insert(currentVertex);
		std::vector<Graph::Edge> incidentEdges;
		m_Maze->GetIncidentEdges(currentVertex, incidentEdges);
		for (auto const& edge : incidentEdges)
		{
			edgesExplored.push_back(edge);
			if (visitedVertices.find(edge.vertexB) == visitedVertices.end())
			{
				visitedVertices.insert(edge.vertexB);
				vertexStack.push(edge.vertexB);
				parentMap[edge.vertexB] = currentVertex;
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
