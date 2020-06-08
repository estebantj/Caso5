#pragma once
#include <array>
#include "Sector.h"
#include "Variables.h"
#include <unordered_map>
#include <iostream>

class LineRecognizer
{
public:
	std::unordered_map<int,int> probabilidadesPorNumero;
	std::unordered_map<int, std::pair<int,int> > modificadoresDeProbabilidad;

	LineRecognizer();

	void calcularProbabilidad(std::vector<int[4]>);
	void aumentarProbabilidad(int dif, bool pEsVertical);
	void disminuirProbabilidad(int dif, bool pEsVertical);
	void analizarLineas(std::vector<std::array<int, 4>> pLineas);
	int encontrarRangoX(int x1, int x2, std::vector<std::array<int, 2>>  rangosX);
	int encontrarRangoY(int y1, int y2, std::vector<std::array<int, 2>>  rangosY);

	void imprimirProbabilidades();
};


