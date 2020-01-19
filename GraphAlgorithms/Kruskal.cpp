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

#include "Kruskal.h"
#include "Partition.h"
#include <algorithm>

/*
1	algorithm Kruskal(G) is
2		A := ∅
3		for each v ∈ G.V do
4		MAKE-SET(v)
5			for each (u, v) in G.E ordered by weight(u, v), increasing do
6				if FIND-SET(u) ≠ FIND-SET(v) then
7					A := A ∪ {(u, v)}
8					UNION(FIND-SET(u), FIND-SET(v))
9		return A
*/
Graph* Kruskal::MST(std::vector<Graph::Edge>& mst, std::vector<bool>& edgeIncluded, bool maze)
{
	Graph* mstGraph = maze ? new Graph(m_Graph->m_VertexCount) : nullptr;
	size_t i = 0;
	std::sort(m_Edges.begin(), m_Edges.end(), [](const Graph::Edge& e1, const Graph::Edge& e2)
		{
			return e1.cost < e2.cost;
		});
	Partition partition(m_Graph->m_VertexCount);
	size_t mstVertices = 0;
	while (mstVertices < m_Graph->m_VertexCount - 1 && i < m_Graph->m_Edges.size())
	{
		Graph::Edge edge = m_Edges[i++];
		if (!maze) mst.push_back(edge);
		if (!partition.DoesMakeCycle(edge))
		{
			mstVertices++;
			if (maze)
			{
				mstGraph->AddEdge(edge.vertexA, edge.vertexB, 1);
				mst.push_back(edge);
			}
			edgeIncluded.push_back(true);
			partition.AddEdge(edge);
		}
		else if (!maze) edgeIncluded.push_back(false);
	}
	return mstGraph;
}
