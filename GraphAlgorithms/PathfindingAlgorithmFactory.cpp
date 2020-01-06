#include "PathfindingAlgorithmFactory.h"

std::shared_ptr<PathfindingAlgorithm> PathfindingAlgorithmFactory::GetPathfindingAlgorithm(Pathfinding type, Graph* maze)
{
	switch (type)
	{
	case Pathfinding::ASTAR:
		return std::make_shared<AStar>(maze);
	case Pathfinding::BFS:
		return std::make_shared<BFS>(maze);
	case Pathfinding::DFS:
		return std::make_shared<DFS>(maze);
	case Pathfinding::DIJKSTRA:
		return std::make_shared<Dijkstra>(maze);
	default:
		return std::make_shared<Dijkstra>(maze);
	}
}
