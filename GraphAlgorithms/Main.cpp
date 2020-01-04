#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Graph.h"
#include "MSTAlgorithm.h"
#include "Kruskal.h"
#include "PrimJarnik.h"
#include <iostream>
#include <math.h>
#include <memory>

#define PI 3.14159265f
#define ORIGIN_X ScreenWidth()/2
#define ORIGIN_Y ScreenHeight()/2
#define RADIUS 40
#define CIRCLE_RADIUS 4* ORIGIN_Y / 5
#define STRING_OFFSET 5
#define TIME_BETWEEN_FRAMES 1.0f

#define USER_ANIMATION_CONTROL 1

enum class Algorithm {PRIM_JARNIK, KRUSKAL};

class GraphAlgorithms : public olc::PixelGameEngine
{
private:
	Graph* m_Graph;
	float m_Angle;
	std::vector<Graph::Edge> m_Mst;
	std::vector<bool> m_EdgeIncluded;
	Algorithm m_Type = Algorithm::KRUSKAL;
	std::unique_ptr<MSTAlgorithm> m_MstAlgorithm;
	size_t m_CurrentIndex = -1;
	float m_Time = TIME_BETWEEN_FRAMES;
private:
	std::pair<size_t, size_t> GetPosition(size_t vertex)
	{
		float angle = vertex * m_Angle;
		float newX = ORIGIN_X + CIRCLE_RADIUS * cosf(angle);
		float newY = ORIGIN_Y + CIRCLE_RADIUS * sinf(angle);
		return { (size_t)newX, (size_t)newY };
	}
public:
	GraphAlgorithms(Graph *graph) : m_Graph(graph)
	{
		m_Angle = (360.0f / graph->m_VertexCount) * 0.0174532925f;
		sAppName = "Kruskal & Prim-Jarnik Algorithm";
		if (m_Type == Algorithm::KRUSKAL) m_MstAlgorithm = std::make_unique<Kruskal>(m_Graph);
		else m_MstAlgorithm = std::make_unique<PrimJarnik>(m_Graph);
	}
	void UpdateGraphics()
	{
		bool animationFinished = m_CurrentIndex == m_Mst.size() - 1;
		Clear(olc::BLACK);
#if USER_ANIMATION_CONTROL
		if (!animationFinished)
			DrawString(STRING_OFFSET, STRING_OFFSET, "Press <<Enter>> for next step", olc::WHITE, 2);
#endif
		// Draw edges
		if (!animationFinished)
		{
			for (const auto& edge : m_Graph->m_Edges)
			{
				auto posA = GetPosition(edge.vertexA - 1);
				auto posB = GetPosition(edge.vertexB - 1);
				DrawLine(posA.first, posA.second, posB.first, posB.second, olc::GREY);
				DrawString((posA.first + posB.first) / 2, (posA.second + posB.second) / 2, std::to_string(edge.cost), olc::WHITE, 2);
			}
		}
		// Draw MST
		for (size_t i = 0; i <= m_CurrentIndex; i++)
		{
			if (m_CurrentIndex == -1) break;
			auto posA = GetPosition(m_Mst[i].vertexA - 1);
			auto posB = GetPosition(m_Mst[i].vertexB - 1);
			DrawLine(posA.first, posA.second, posB.first, posB.second, m_EdgeIncluded[i] ? olc::GREEN : animationFinished ? olc::BLACK : olc::RED);
			DrawString((posA.first + posB.first) / 2, (posA.second + posB.second) / 2, std::to_string(m_Mst[i].cost), m_EdgeIncluded[i] ? olc::WHITE : animationFinished ? olc::BLACK : olc::WHITE, 2);
			std::string edgeAdded = std::to_string(m_Mst[m_CurrentIndex].vertexA) + " -> " + std::to_string(m_Mst[m_CurrentIndex].vertexB);
			if (!animationFinished)
				DrawString(ScreenWidth() - 120, STRING_OFFSET, edgeAdded, m_EdgeIncluded[m_CurrentIndex] ? olc::GREEN : olc::RED, 2);
		}
		// Draw vertices
		for (size_t vertex = 0; vertex < m_Graph->m_VertexCount; vertex++)
		{
			auto position = GetPosition(vertex);
			FillCircle(position.first, position.second, RADIUS, animationFinished ? olc::DARK_GREEN : olc::BLUE);
			DrawString(position.first - STRING_OFFSET, position.second - STRING_OFFSET, std::to_string(vertex + 1), olc::WHITE, 2);
		}
	}
public:
	bool OnUserCreate() override
	{
		m_MstAlgorithm->MST(m_Mst, m_EdgeIncluded);
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		m_Time -= fElapsedTime;
#if USER_ANIMATION_CONTROL
		if (GetKey(olc::Key::ENTER).bPressed && (m_CurrentIndex < m_Mst.size() - 1 || m_CurrentIndex == -1)) m_CurrentIndex++;
#else
		if (m_Time <= 0 && (m_CurrentIndex < m_Mst.size() - 1 || m_CurrentIndex == -1))
		{
			m_Time = TIME_BETWEEN_FRAMES;
			m_CurrentIndex++;
		}
#endif
		UpdateGraphics();
		return true;
	}
};
int main()
{
	Graph graph(9); // Build example graph with 9 vertices
	graph.AddEdge(1, 2, 4);
	graph.AddEdge(1, 8, 8);
	graph.AddEdge(2, 3, 8);
	graph.AddEdge(2, 8, 11);
	graph.AddEdge(3, 4, 7);
	graph.AddEdge(3, 9, 2);
	graph.AddEdge(3, 6, 4);
	graph.AddEdge(4, 5, 9);
	graph.AddEdge(4, 6, 14);
	graph.AddEdge(5, 6, 10);
	graph.AddEdge(6, 7, 2);
	graph.AddEdge(7, 9, 6);
	graph.AddEdge(7, 8, 1);
	graph.AddEdge(8, 9, 7);
	GraphAlgorithms demo(&graph);
	if (demo.Construct(1366, 768, 1, 1))
		demo.Start();
	return 0;
}