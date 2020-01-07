/*
Graph algorithms visualization made using olcPixelGameEngine
Copyright (C) 2020 Dušan Erdeljan

This file is part of graph-algorithms-visualization

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

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
