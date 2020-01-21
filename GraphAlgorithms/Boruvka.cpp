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

#include "Boruvka.h"
#include "Partition.h"

std::unique_ptr<Graph> Boruvka::MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze)
{
	std::unique_ptr<Graph> mstGraph = maze ? std::make_unique<Graph>(m_Graph->m_VertexCount) : nullptr;
	Partition partition(m_Graph->m_VertexCount);
	int* cheapest = new int[m_Graph->m_VertexCount+1];
	for (size_t i = 0; i <= m_Graph->m_VertexCount; i++) cheapest[i] = -1;
	int treeCount = m_Graph->m_VertexCount;
	while (treeCount > 1)
	{
		for (size_t i = 0; i <= m_Graph->m_VertexCount; i++) cheapest[i] = -1;
		for (size_t i = 0; i < m_Graph->m_Edges.size(); i++)
		{
			Graph::Edge edge = m_Graph->m_Edges[i];
			if (!partition.DoesMakeCycle(edge))
			{
				size_t firstRoot = partition.Find(edge.vertexA-1) + 1;
				size_t secondRoot = partition.Find(edge.vertexB-1) + 1;
				if (cheapest[firstRoot] == -1 || m_Graph->m_Edges[cheapest[firstRoot]].cost > edge.cost)
					cheapest[firstRoot] = i;
				if (cheapest[secondRoot] == -1 || m_Graph->m_Edges[cheapest[secondRoot]].cost > edge.cost)
					cheapest[secondRoot] = i;
			}
		}
		for (size_t vertex = 1; vertex <= m_Graph->m_VertexCount; vertex++)
		{
			if (cheapest[vertex] != -1)
			{
				if (!partition.DoesMakeCycle(m_Graph->m_Edges[cheapest[vertex]]))
				{
					if (maze) mstGraph->AddEdge(m_Graph->m_Edges[cheapest[vertex]].vertexA, m_Graph->m_Edges[cheapest[vertex]].vertexB, 1);
					edgeIncluded.push_back(true);
					mst.push_back(m_Graph->m_Edges[cheapest[vertex]]);
					partition.AddEdge(m_Graph->m_Edges[cheapest[vertex]]);
					treeCount--;
				}
			}
		}
	}
	delete[] cheapest;
	return mstGraph;
}
