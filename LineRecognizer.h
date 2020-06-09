#pragma once
#include <array>
#include "Variables.h"
#include <unordered_map>
#include <map>
#include <iostream>

class LineRecognizer
{
private:
	std::map<int,int> probabilidadesPorNumero;
	std::unordered_map<int, std::pair<int,int> > modificadoresDeProbabilidad;

	void actualizarProbabilidad(int dif, bool pEsVertical, bool sumarProba);
	int encontrarRangoX(int x1, int x2, std::vector<std::array<int, 2>>  rangosX);
	int encontrarRangoY(int y1, int y2, std::vector<std::array<int, 2>>  rangosY);

public:
	LineRecognizer();

	std::vector<std::array<int, 4>> crearPruebas();
	void imprimirNumeros();
	void analizarLineas(std::vector<std::array<int, 4>> pLineas);
};


