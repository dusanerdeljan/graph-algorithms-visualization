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

/*
1	algorithm Borůvka is
2		input: A graph G whose edges have distinct weights.
3		output: F is the minimum spanning forest of G.
4
5		Initialize a forest F to be a set of one-vertex trees, one for each vertex of the graph.
6
7		while F has more than one component do
8			Find the connected components of F and label each vertex of G by its component
9			Initialize the cheapest edge for each component to "None"
10			for each edge uv of G do
11				if u and v have different component labels:
12					if uv is cheaper than the cheapest edge for the component of u then
13						Set uv as the cheapest edge for the component of u
14					if uv is cheaper than the cheapest edge for the component of v then
15						Set uv as the cheapest edge for the component of v
16		for each component whose cheapest edge is not "None" do
17			Add its cheapest edge to F
*/
Graph * Boruvka::MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze)
{
	Graph* mstGraph = maze ? new Graph(m_Graph->m_VertexCount) : nullptr;
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
