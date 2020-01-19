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

#include "DFS.h"
#include <stack>
#include <set>

/*
1	procedure DFS-iterative(G, v) is
2		let S be a stack
3		S.push(v)
4		while S is not empty do
5			v = S.pop()
6			if v is not labeled as discovered then
7				label v as discovered
8				for all edges from v to w in G.adjacentEdges(v) do
9					S.push(w)
*/
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
