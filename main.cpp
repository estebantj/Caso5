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

	//linea = { 10,0,1000,0 }; lineas.push_back(linea);
	
	/*
	for (int i = 0; i < cantidadDeLineas; i++)
	{
		int x1 = rand() % 1080;
		int x2 = (x1 != 0 ? rand() % 1080 : 0);
		
		int y1 = (x1 == 0 ? rand() % 920 : 0);
		int y2 = (y1 != 0 ? rand() % 920 : 0);

		std::array<int, 4> linea = { x1, x2, y1, y1};
		lineas.push_back(linea);
	}
	*/
	
	
	
	LineRecognizer * algoritmito = new LineRecognizer();
	algoritmito->analizarLineas(lineas);
	algoritmito->imprimirProbabilidades();
}
