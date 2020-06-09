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
}
