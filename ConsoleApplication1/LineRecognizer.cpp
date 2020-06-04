#include "LineRecognizer.h"

void LineRecognizer::ordenarSectores(std::vector<std::array<int, 4>> pLineas)
{
	int posXcentral = anchuraPantalla / 2, posYcentral = alturaPantalla/2;
	sectorSI.rangoX[0] = 0; sectorSI.rangoX[1] = posXcentral - 1;
	sectorSI.rangoY[0] = 0; sectorSI.rangoY[1] = posYcentral - 1;

	sectorSD.rangoX[0] = posXcentral - 1; sectorSD.rangoX[1] = anchuraPantalla - 1;
	sectorSD.rangoY[0] = posXcentral - 1; sectorSD.rangoY[1] = alturaPantalla - 1;

	for (std::array<int, 4> linea : pLineas)
	{

	}
}

void LineRecognizer::calcularProbabilidad(std::vector<int[4]>)
{
	//la magia probabilistica
}
