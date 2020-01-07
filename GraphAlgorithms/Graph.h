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

#pragma once

#include <iostream>
#include <vector>

class Graph
{
public:
	struct Edge
	{
		size_t vertexA;
		size_t vertexB;
		size_t cost;
	public:
		Edge() : vertexA(99), vertexB(99), cost(99) {}
		Edge(size_t a, size_t b, size_t c) : vertexA(a), vertexB(b), cost(c) {}
	};
public:
	size_t m_VertexCount;
	size_t** m_AdjacencyMatrix;
	std::vector<Edge> m_Edges;
public:
	Graph(size_t vertextCount);
	~Graph();
	void AddEdge(size_t firstVertex, size_t secondVertext, size_t cost);
	void AddEdge(Graph::Edge* edge);
	void GetIncidentEdges(size_t vertex, std::vector<Graph::Edge>& edges) const;
	friend std::ostream& operator << (std::ostream& out, const Graph& graph);
};

