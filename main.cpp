#include <iostream>
#include "LineRecognizer.h"
#include <stdlib.h>
#include<time.h> 

int main()
{	
	srand(time(0));
	LineRecognizer * algoritmito = new LineRecognizer();
	std::vector<std::array<int, 4>> lineas = algoritmito->crearPruebas();
	algoritmito->analizarLineas(lineas);

	for (int i = 0; i < 10; i++) {
		std::cout << rand() % 100 << "\n";
	}
}
