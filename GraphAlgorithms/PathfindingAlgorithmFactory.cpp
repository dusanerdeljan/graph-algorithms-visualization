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
