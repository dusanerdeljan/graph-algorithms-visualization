#include "Graph.h"

Graph::Graph(size_t vertextCount) : m_VertexCount(vertextCount), m_AdjacencyMatrix(new size_t*[m_VertexCount])
{
	for (size_t i = 0; i < m_VertexCount; i++)
	{
		m_AdjacencyMatrix[i] = new size_t[m_VertexCount];
		for (size_t j = 0; j < m_VertexCount; j++)
		{
			m_AdjacencyMatrix[i][j] = 0;
		}
	}
}

Graph::~Graph()
{
	for (size_t i = 0; i < m_VertexCount; i++)
	{
		delete[] m_AdjacencyMatrix[i];
	}
	delete[] m_AdjacencyMatrix;
}

void Graph::AddEdge(size_t firstVertex, size_t secondVertext, size_t cost)
{
	m_AdjacencyMatrix[firstVertex-1][secondVertext-1] = cost;
	m_AdjacencyMatrix[secondVertext-1][firstVertex-1] = cost;
	m_Edges.push_back(Edge(firstVertex, secondVertext, cost));
}

void Graph::GetIncidentEdges(size_t vertex, std::vector<Graph::Edge>& edges) const
{
	vertex -= 1;
	for (size_t other = 0; other < m_VertexCount; other++)
	{
		if (other != vertex && m_AdjacencyMatrix[vertex][other])
			edges.push_back(Edge(vertex+1, other+1, m_AdjacencyMatrix[vertex][other]));
	}
}

std::ostream& operator<<(std::ostream& out, const Graph& graph)
{
	for (size_t i = 0; i < graph.m_VertexCount; i++)
	{
		for (size_t j = 0; j < graph.m_VertexCount; j++)
		{
			out << graph.m_AdjacencyMatrix[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}
