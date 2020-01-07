/*
Graph algorithms visualization made using olcPixelGameEngine
Copyright (C) 2020 Du�an Erdeljan

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

