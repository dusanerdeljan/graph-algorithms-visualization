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

