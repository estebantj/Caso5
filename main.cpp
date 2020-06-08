#include <iostream>
#include "LineRecognizer.h"
#include <stdlib.h>

int main()
{
	std::vector<std::array<int, 4>> lineas;
	int cantidadDeLineas = 15;
	/*
	std::array<int, 4> linea = { 0,150,0,150 }; lineas.push_back(linea);
	linea = { 0,150,0,900 }; lineas.push_back(linea);

	linea = { 150,0,150,0 }; lineas.push_back(linea);
	linea = { 150,0,1000,0 };  lineas.push_back(linea);
	*/
	
	std::array<int, 4> linea = { 0,150,0,150 }; lineas.push_back(linea);
	linea = { 0,900,0,900 }; lineas.push_back(linea);

	linea = { 150,0,150,0 }; lineas.push_back(linea);
	linea = { 1000,0,1000,0 };  lineas.push_back(linea);

	linea = { 500,0,525,0 }; lineas.push_back(linea);
	linea = { 0,500,0,522 };  lineas.push_back(linea);

	/*
	for (int i = 0; i < cantidadDeLineas; i++)
	{
		std::array<int, 4> linea = { rand() % 1080, rand() % 920, rand() % 1080, rand() % 920};
		lineas.push_back(linea);
	}
	*/
	
	LineRecognizer * algoritmito = new LineRecognizer();
	algoritmito->analizarLineas(lineas);
	algoritmito->imprimirProbabilidades();
}
