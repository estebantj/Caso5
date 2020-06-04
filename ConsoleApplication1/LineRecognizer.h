#pragma once
#include <unordered_map>
#include "Sector.h"
#include "Variables.h"
class LineRecognizer
{
	std::unordered_map<int,int> probabilidades;
	Sector sectorSI, sectorSD, sectorII, sectorID;

	LineRecognizer(int ) {
		
	}

	void ordenarSectores(std::vector<std::array<int,4>> pLineas);
	void calcularProbabilidad(std::vector<int[4]>);
};


