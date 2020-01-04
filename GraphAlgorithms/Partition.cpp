#include "Partition.h"

Partition::Partition(size_t numVertices) : m_Positions(new Position[numVertices])
{
	for (size_t i = 0; i < numVertices; i++)
	{
		m_Positions[i].parent = i;
		m_Positions[i].size = 1;
	}
}

Partition::~Partition()
{
	delete[] m_Positions;
}

size_t Partition::Find(int vertex)
{
	if (m_Positions[vertex].parent != vertex)
		m_Positions[vertex].parent = Find(m_Positions[vertex].parent);
	return m_Positions[vertex].parent;
}

void Partition::Union(int x, int y)
{
	int xRoot = Find(x);
	int yRoot = Find(y);
	if (m_Positions[xRoot].size < m_Positions[yRoot].size)
		m_Positions[xRoot].parent = yRoot;
	else if (m_Positions[xRoot].size > m_Positions[yRoot].size)
		m_Positions[yRoot].parent = xRoot;
	else
	{
		m_Positions[yRoot].parent = xRoot;
		m_Positions[xRoot].size++;
	}
}

bool Partition::DoesMakeCycle(const Graph::Edge& edge)
{
	return Find(edge.vertexA - 1) == Find(edge.vertexB - 1);
}

void Partition::AddEdge(const Graph::Edge& edge)
{
	Union(Find(edge.vertexA - 1), Find(edge.vertexB - 1));
}
