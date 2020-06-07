#include "LineRecognizer.h"

int LineRecognizer::encontrarRangoY(int y1, int y2, std::vector<std::array<int, 2>>  rangosY)
{
	int rangoY1, rangoY2;

	//Calculando sector Y1
	for (int rango = 0; rango< 19; ++rango) {
		if (y1 < rangosY.at(rango)[1])  rangoY1 = rango;
	
	}

	//Calculando sector Y2
	for (int rango = 0; rango < 19; ++rango) {
		if (y1 < rangosY.at(rango)[1])  rangoY2 = rango;

	}
	return (abs(rangoY1 - rangoY2));
}



int LineRecognizer::encontrarRangoX(int x1, int x2, std::vector<std::array<int, 2>>  rangosX)
{
	return 4;
}


void LineRecognizer::ordenarSectores(std::vector<std::array<int,4>> pLineas)
{
	int ultimaPosX = 0;
	int ultimaPosY = 0;
	std::array<int, 4> linea;
	std::vector<std::array<int, 2>>  rangosX;
	std::vector<std::array<int, 2>>  rangosY;
	int distanciaY = alturaPantalla / cantidadSectoresY;
	int distanciaX = anchuraPantalla / cantidadSectoresX;	

	//Los cálculos fueron hechos previamente. Pero para aclarar
	//Se hizo probabilidad = 0.5 - (0.05 * [líneas totales - 1])
	int probabilidadIni[] = {35, 50, 30, 35, 40, 30, 30, 40, 30, 35};
	tablaProbabilidades.assign(probabilidadIni, probabilidadIni + 9);

	for (int sectorNuevo = 0;sectorNuevo<cantidadSectoresX ; ++sectorNuevo) 
	{
		rangosX.push_back({ ultimaPosX, ultimaPosX += distanciaX });
		rangosY.push_back({ ultimaPosY, ultimaPosY += distanciaY });
	}

	//X1 = 0 |||| Y1 = 1 |||| X2 = 2 |||| Y2 = 3
	for (int contador = 0 ; contador<pLineas.size(); ++contador)
	{
		 linea = pLineas.at(contador);

		//Esto quiere decir que sale del lateral izquierdo
		if (linea[0] == 0) {      		
			int dif = encontrarRangoY(linea[1], linea[3], rangosY);	

			if (dif < 4) {
				aumentarProbabilidad(dif);
			}
			else {
				disminuirProbabilidad(dif);
			}
			
		}
		else {
			int dif = encontrarRangoX(linea[0], linea[2], rangosX); 

			if (dif < 4) {
				aumentarProbabilidad(dif);
			}
			else {
				disminuirProbabilidad(dif);
			}
		}
	}
}


void LineRecognizer::aumentarProbabilidad(int dif)
{
	//Relevo tengo sueno aca tomando en cuenta que es diferente para cada numrro
}

void LineRecognizer::disminuirProbabilidad(int dif)
{

}

void LineRecognizer::calcularProbabilidad(std::vector<int[4]>)
{
	//la magia probabilistica
}
