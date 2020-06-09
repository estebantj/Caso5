#include "LineRecognizer.h"

LineRecognizer::LineRecognizer()
{

	/* 
		Se agrega la probabilidad inicial de cada numero
		que se calculó con anterioridad.

		Los cálculos fueron hechos previamente. Pero para aclarar
		se hizo probabilidad = 0.5 - (0.05 * [líneas totales - 1])
	*/
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

	// Las modificaciones se da en un rango de 10%, esta se distribuye a la proba horizontal y vertical \
	segun la importancia de las lineas, siendo mas alta cuando hay menos lineas a las que distribuirles este porcentaje\
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

/*
	Ambas funciones de encontrar rango se encagan de buscar el sector en que se
	encuentra el punto de salida y de llegada de la linea, asi como de realizar su
	resta y devolver la diferencia.
	Se elige una u otra dependiendo de si la linea empieza en la parte superior o izquierda
	de la pantalla.
*/

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

/*
	La funcion analizarLineas se encarga de recorrer todo el arreglo de lineas.
	Por cada linea se identifica de que punto sale, y segun esto se llama a la funcion
	correspondiente para saber la diferencia.
	
*/
void LineRecognizer::analizarLineas(std::vector<std::array<int,4>> pLineas)
{
	int ultimaPosX = 0;
	int ultimaPosY = 0;
	std::array<int, 4> linea;
	std::vector<std::array<int, 2>>  rangosX;
	std::vector<std::array<int, 2>>  rangosY;
	int distanciaY = alturaPantalla / cantidadSectoresY;
	int distanciaX = anchuraPantalla / cantidadSectoresX;	

	for (int sectorNuevo = 0;sectorNuevo<cantidadSectoresX ; ++sectorNuevo) 
	{
		rangosX.push_back({ ultimaPosX, ultimaPosX += distanciaX });
		rangosY.push_back({ ultimaPosY, ultimaPosY += distanciaY });
	}

	//X1 = 0 |||| Y1 = 1 |||| X2 = 2 |||| Y2 = 3
	for (int contador = 0 ; contador<pLineas.size(); ++contador)
	{
		 linea = pLineas.at(contador);

		//Esto quiere decir que sale del lateral izquierdo (horizontal)
		if (linea[0] == 0) {      		
			int dif = encontrarRangoY(linea[1], linea[3], rangosY);	

			// Se va a aumentar la probabilidad si la diferencia es menor a 4, o sino se disminuye.
			dif < 4 ? actualizarProbabilidad(dif, false, true) : actualizarProbabilidad(dif, false, false);
		}
		else { // (Vertical)
			int dif = encontrarRangoX(linea[0], linea[2], rangosX); 

			dif < 4 ? actualizarProbabilidad(dif, true, true) : actualizarProbabilidad(dif, true, false);
		}
	}
	imprimirNumeros();
}

/*
Parametros:
	dif : diferencia entre el sector de inicio y de fin de la linea
	pEsVertical : true en caso de que sea una linea vertical, false en caso contrario
	sumarProba : true si la proba va a aumentar, false en caso contrario
*/

void LineRecognizer::actualizarProbabilidad(int dif, bool pEsVertical, bool sumarProba)
{
	int contador = 0;
	// inclinacionModerada es true cuando la linea no es muy buena pero tampoco muy mala.
	// Esto quiere decir que si es regular segun su inclinacion entra al primer if
	bool inclinacionModerada = sumarProba && dif < 2 || !sumarProba && dif < 7;
	for (auto it : modificadoresDeProbabilidad) // Se va a iterar sobre cada numero para actualizar su probabilidad
	{
		std::map<int, int>::iterator itProba = probabilidadesPorNumero.find(contador);
		int valorDeCambio = pEsVertical ? it.second.first : it.second.second;
		if (inclinacionModerada)
		{
			// Se disminuye el valor de cambio segun la inclinacion que tenga
			if (sumarProba)
			{
				valorDeCambio -= (dif * 0.5);
				itProba->second += valorDeCambio;
				if (itProba->second > 100) itProba->second = 100;
			}
			// El valor de cambio aumenta entre mayor sea la diferencia
			// pero a su vez disminuye segun que tan alta es la probabilidad
			// actual, esto para mantener un equilibrio
			else
			{
				valorDeCambio = ((valorDeCambio / 2) + (dif * 0.5)) / (itProba->second / 10);
				itProba->second -= valorDeCambio;
				if (itProba->second < 0) itProba->second = 0;
			}
		}
		else
		{
			// Se aplican las mismas condiciones que en los dos casos anteriores
			// Sin embargo, aca se divide valor de cambio porque la linea tiene
			// una inclinacion mayor entonces el aumento debe ser menor
			if (sumarProba)
			{
				valorDeCambio = (valorDeCambio / 2) - (dif * 0.5);
				itProba->second += valorDeCambio;
				if (itProba->second > 100) itProba->second = 100;
			}
			else
			{
				valorDeCambio = (valorDeCambio + (dif * 0.5)) / (itProba->second / 10);
				itProba->second -= valorDeCambio;
				if (itProba->second < 0) itProba->second = 0;
			}
		}
		contador++;

	}	
}

std::vector<std::array<int, 4>> LineRecognizer::crearPruebas()
{
	std::vector<std::array<int, 4>> lineas;
	
	int contador = 0;
	for (int i = 0; i < cantidadLineasTotal; i++)
	{
		if (contador < (cantidadLineasTotal / cantidadLineasBuenas) - 1)
		{
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			int opcion = rand() % 2;
			if (opcion == 0)
			{
				x1 = rand() % anchuraPantalla;
				x2 = rand() % anchuraPantalla;
			}
			else
			{
				y1 = rand() % alturaPantalla;
				y2 = rand() % alturaPantalla;
			}
			std::array<int, 4> linea = { x1, y1, x2, y2 };
			lineas.push_back(linea);
			contador++;
		}
		else
		{
			contador = 0;

			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			int opcion = rand() % 2;
			if (opcion == 0)
			{
				x1 = rand() % 500;
				x2 = rand() % 500;
			}
			else
			{
				y1 = rand() % 100;
				y2 = rand() % 100;
			}
			std::array<int, 4> linea = { x1, y1, x2, y2 };
			lineas.push_back(linea);
		}
	}
	return lineas;
}

void LineRecognizer::imprimirNumeros()
{
	/*
		Por cada numero se utiliza la probabilidad final para guiar al random que decide
		si el numero se encuentra o no presente en las lineas.
	*/
	for (auto it : probabilidadesPorNumero)
	{
		std::cout << it.first << " : " << it.second << " -> ";
		int random = rand() % 100 + 1;
		std::cout << (random <= it.second ? "Si aparece" : "No aparece") << "\n";
	}
}