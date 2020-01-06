#pragma once
#include "PathfindingAlgorithm.h"
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "Graph.h"
#include <memory>

class PathfindingAlgorithmFactory
{
public:
	enum class Pathfinding { BFS, DFS, DIJKSTRA, ASTAR };
	static std::shared_ptr<PathfindingAlgorithm> GetPathfindingAlgorithm(Pathfinding type, Graph* maze);
};

