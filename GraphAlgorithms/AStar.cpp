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

#include "AStar.h"
#include <set>
#include <unordered_map>
#include <algorithm>

#define INFF 9999999

struct HeapEntryAStar
{
	size_t vertex;
	size_t distance;
	HeapEntryAStar() : vertex(999999), distance(INFF) {}
	HeapEntryAStar(size_t v, size_t d) : vertex(v), distance(d) {}
};

/*
1	// A* finds a path from start to goal.
2	// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
3	function A_Star(start, goal, h)
4		// The set of discovered nodes that may need to be (re-)expanded.
5		// Initially, only the start node is known.
6		openSet := {start}
7
8		// For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start to n currently known.
9		cameFrom := an empty map
10
11		// For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
12		gScore := map with default value of Infinity
13		gScore[start] := 0
14
15		// For node n, fScore[n] := gScore[n] + h(n).
16		fScore := map with default value of Infinity
17		fScore[start] := h(start)
18
19		while openSet is not empty
20			current := the node in openSet having the lowest fScore[] value
21			if current = goal
22				return reconstruct_path(cameFrom, current)
23
24			openSet.Remove(current)
25			for each neighbor of current
26				// d(current,neighbor) is the weight of the edge from current to neighbor
27				// tentative_gScore is the distance from start to the neighbor through current
28				tentative_gScore := gScore[current] + d(current, neighbor)
29				if tentative_gScore < gScore[neighbor]
30				// This path to neighbor is better than any previous one. Record it!
31					cameFrom[neighbor] := current
32					gScore[neighbor] := tentative_gScore
33					fScore[neighbor] := gScore[neighbor] + h(neighbor)
34					if neighbor not in openSet
35						openSet.add(neighbor)
36
37	// Open set is empty but goal was never reached
38	return failure
*/
std::vector<size_t> AStar::FindPath(size_t startVertex, size_t endVertex, std::vector<Graph::Edge>& edgesExplored) const
{
	int ROOT = (int)sqrt(m_Maze->m_VertexCount - 2);
	std::vector<size_t> path;
	std::unordered_map<size_t, size_t> distanes;
	for (size_t vertex = 1; vertex <= m_Maze->m_VertexCount; vertex++)
	{
		distanes[vertex] = INFF;
	}
	std::unordered_map<size_t, HeapEntryAStar> entryMap;
	std::set<size_t> visitedVertices;
	std::vector<HeapEntryAStar*> unvisitedNodes;
	size_t* parentMap = new size_t[m_Maze->m_VertexCount + 1];
	distanes[startVertex] = 0;
	entryMap[startVertex] = HeapEntryAStar(startVertex, 0);
	unvisitedNodes.push_back(&entryMap[startVertex]);
	while (!unvisitedNodes.empty())
	{
		HeapEntryAStar* minVertex = unvisitedNodes.back();
		unvisitedNodes.pop_back();
		size_t currentVertex = minVertex->vertex;
		if (distanes[currentVertex] == INFF || currentVertex == endVertex) break;
		std::vector<Graph::Edge> incidentEdges;
		m_Maze->GetIncidentEdges(currentVertex, incidentEdges);
		for (auto const& edge : incidentEdges)
		{
			size_t neighbour = edge.vertexB;
			// We assusme that the end vertex is at the bottom right corner of the graph
			size_t remainingDistance = abs(ROOT-1 - ((int)currentVertex-1)%ROOT) + abs(ROOT-1 - (int)(currentVertex-1)/ROOT);
			size_t newDistance = distanes[currentVertex] + edge.cost;
			if (visitedVertices.find(neighbour) == visitedVertices.end())
			{
				if (newDistance < distanes[neighbour])
				{
					edgesExplored.push_back(edge);
					if (entryMap.find(neighbour) == entryMap.end())
					{
						entryMap[neighbour] = HeapEntryAStar(neighbour, newDistance + remainingDistance);
						unvisitedNodes.push_back(&entryMap[neighbour]);
						std::sort(unvisitedNodes.begin(), unvisitedNodes.end(), [](HeapEntryAStar* a, HeapEntryAStar* b) { return a->distance > b->distance; });
					}
					else
					{
						entryMap[neighbour].distance = newDistance + remainingDistance;
						std::sort(unvisitedNodes.begin(), unvisitedNodes.end(), [](HeapEntryAStar* a, HeapEntryAStar* b) { return a->distance > b->distance; });
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
