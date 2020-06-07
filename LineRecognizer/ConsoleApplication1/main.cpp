#include <iostream>
#include "LineRecognizer.h"

int main()
{
	std::vector<std::array<int, 4>> lineas;
	LineRecognizer * algoritmito = new LineRecognizer();
	algoritmito->ordenarSectores(lineas);
}
