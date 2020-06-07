#pragma once
#include <array>
#include "Sector.h"
#include "Variables.h"
#include <unordered_map>
class LineRecognizer
{
public:
	std::vector<int> tablaProbabilidades;
	std::unordered_map<int,int> probabilidadesPorNumero;

	void aumentarProbabilidad(int dif);
	void disminuirProbabilidad(int dif);	
	void calcularProbabilidad(std::vector<int[4]>);
	void ordenarSectores(std::vector<std::array<int, 4>> pLineas);
	int encontrarRangoX(int x1, int x2, std::vector<std::array<int, 2>>  rangosX);
	int encontrarRangoY(int y1, int y2, std::vector<std::array<int, 2>>  rangosY);
};


