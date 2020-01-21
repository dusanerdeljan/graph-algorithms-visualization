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

#include "MSTAlgorithmFactory.h"

std::unique_ptr<MSTAlgorithm> MSTAlgorithmFactory::GetMSTAlgorithm(MSTAlgorithmFactory::Algorithm type, Graph * graph)
{
	switch (type)
	{
	case MSTAlgorithmFactory::Algorithm::PRIM_JARNIK:
		return std::make_unique<PrimJarnik>(graph);
	case MSTAlgorithmFactory::Algorithm::KRUSKAL:
		return std::make_unique<Kruskal>(graph);
	case MSTAlgorithmFactory::Algorithm::BORUVKA:
		return std::make_unique<Boruvka>(graph);
	default:
		return std::make_unique<Kruskal>(graph);
	}
}
