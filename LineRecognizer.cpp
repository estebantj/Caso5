#include "LineRecognizer.h"

LineRecognizer::LineRecognizer()
{
	probabilidadesPorNumero.insert({ 0, 35 });
	probabilidadesPorNumero.insert({ 1, 50 });
	probabilidadesPorNumero.insert({ 2, 30 });
	probabilidadesPorNumero.insert({ 3, 35 });
	probabilidadesPorNumero.insert({ 4, 40 });
	probabilidadesPorNumero.insert({ 5, 30 });
	probabilidadesPorNumero.insert({ 6, 30 });
	probabilidadesPorNumero.insert({ 7, 40 });
	probabilidadesPorNumero.insert({ 8, 30 });
	probabilidadesPorNumero.insert({ 9, 35 });

	// Se mantiene una probabilidad total de 10% por numero \
	 Esta se distribuye a la proba horizontal y vertical \
	segun la cantidad de lineas \
										 Proba vertical-horizontal
	modificadoresDeProbabilidad.insert({ 0, std::make_pair(5,5)});
	modificadoresDeProbabilidad.insert({ 1, std::make_pair(10,0) }); 
	modificadoresDeProbabilidad.insert({ 2, std::make_pair(6,4) });
	modificadoresDeProbabilidad.insert({ 3, std::make_pair(7,3) });
	modificadoresDeProbabilidad.insert({ 4, std::make_pair(4,6) });
	modificadoresDeProbabilidad.insert({ 5, std::make_pair(6,4) });
	modificadoresDeProbabilidad.insert({ 6, std::make_pair(6,4) });
	modificadoresDeProbabilidad.insert({ 7, std::make_pair(5,5) });
	modificadoresDeProbabilidad.insert({ 8, std::make_pair(6,4) });
	modificadoresDeProbabilidad.insert({ 9, std::make_pair(5,5) });
}

int LineRecognizer::encontrarRangoY(int y1, int y2, std::vector<std::array<int, 2>>  rangosY)
{
	int rangoY1, rangoY2;

	//Calculando sector Y1
	for (int rango = 0; rango< cantidadSectoresY; ++rango) {
		if (y1 < rangosY.at(rango)[1])
		{
			rangoY1 = rango;
			break;
		}
	
	}

	//Calculando sector Y2
	for (int rango = 0; rango < cantidadSectoresY; ++rango) {
		if (y2 < rangosY.at(rango)[1])
		{
			rangoY2 = rango;
			break;
		}
	}
	return (abs(rangoY1 - rangoY2));
}

int LineRecognizer::encontrarRangoX(int x1, int x2, std::vector<std::array<int, 2>>  rangosX)
{
	int rangoX1, rangoX2;

	//Calculando sector Y1
	for (int rango = 0; rango < cantidadSectoresX; ++rango) {
		if (x1 < rangosX.at(rango)[1])  
		{
			rangoX1 = rango;
			break;
		}
	}

	//Calculando sector Y2
	for (int rango = 0; rango < cantidadSectoresX; ++rango) {
		if (x2 < rangosX.at(rango)[1])
		{
			rangoX2 = rango;
			break;
		}
	}
	return (abs(rangoX1 - rangoX2));
}


void LineRecognizer::analizarLineas(std::vector<std::array<int,4>> pLineas)
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

	for (int sectorNuevo = 0;sectorNuevo<cantidadSectoresX ; ++sectorNuevo) 
	{
		rangosX.push_back({ ultimaPosX, ultimaPosX += distanciaX });
		rangosY.push_back({ ultimaPosY, ultimaPosY += distanciaY });
	}

	//int dif = encontrarRangoX(1042, 900, rangosX);

	//X1 = 0 |||| Y1 = 1 |||| X2 = 2 |||| Y2 = 3
	for (int contador = 0 ; contador<pLineas.size(); ++contador)
	{
		 linea = pLineas.at(contador);

		//Esto quiere decir que sale del lateral izquierdo
		if (linea[0] == 0) {      		
			int dif = encontrarRangoY(linea[1], linea[3], rangosY);	

			if (dif < 4) {
				aumentarProbabilidad(dif, false);
			}
			else {
				disminuirProbabilidad(dif, false);
			}
		}
		else {
			int dif = encontrarRangoX(linea[0], linea[2], rangosX); 

			if (dif < 4) {
				aumentarProbabilidad(dif, true);
			}
			else {
				disminuirProbabilidad(dif, true);
			}
		}
	}
}

// TODO factorizar codigo

void LineRecognizer::aumentarProbabilidad(int dif, bool pEsVertical)
{
	//Relevo tengo sueno aca tomando en cuenta que es diferente para cada numrro
	int contador = 0;
	if (dif < 2) // if (sumarProba && dif < 2 || !sumarProba < 7)
	{
		for (auto it : modificadoresDeProbabilidad)
		{
			std::unordered_map<int, int>::iterator itProba = probabilidadesPorNumero.find(contador);
			int valorDeCambio = pEsVertical ? it.second.first : it.second.second;
			valorDeCambio -= (dif*0.5);
			itProba->second += valorDeCambio;
			if (itProba->second > 100) itProba->second = 100;
			contador++;
			
		}
	}
	else
	{
		for (auto it : modificadoresDeProbabilidad)
		{
			std::unordered_map<int, int>::iterator itProba = probabilidadesPorNumero.find(contador);
			int valorDeCambio = pEsVertical ? it.second.first : it.second.second;
			valorDeCambio = (valorDeCambio /2) - (dif * 0.5);
			itProba->second += valorDeCambio;
			if (itProba->second > 100) itProba->second = 100;
			contador++;

		}
	}
}

void LineRecognizer::disminuirProbabilidad(int dif, bool pEsVertical)
{
	int contador = 0;
	if (dif < 7)
	{
		for (auto it : modificadoresDeProbabilidad)
		{
			std::unordered_map<int, int>::iterator itProba = probabilidadesPorNumero.find(contador);
			int valorDeCambio = pEsVertical ? it.second.first : it.second.second;
			valorDeCambio += (dif * 0.5) / (itProba->second / 10);
			itProba->second -= valorDeCambio;
			if (itProba->second < 0) itProba->second = 0;
			contador++;

		}
	}
	else
	{
		for (auto it : modificadoresDeProbabilidad)
		{
			std::unordered_map<int, int>::iterator itProba = probabilidadesPorNumero.find(contador);
			int valorDeCambio = pEsVertical ? it.second.first : it.second.second;
			valorDeCambio = ((valorDeCambio / 2) + (dif * 0.5)) / (itProba->second / 10);
			itProba->second -= valorDeCambio;
			if (itProba->second < 0) itProba->second = 0;
			contador++;

		}
	}
}

void LineRecognizer::calcularProbabilidad(std::vector<int[4]>)
{
	//la magia probabilistica
}

void LineRecognizer::imprimirProbabilidades()
{
	for (auto it : probabilidadesPorNumero)
	{
		std::cout << it.first << " -> " << it.second << "\n";
	}
}