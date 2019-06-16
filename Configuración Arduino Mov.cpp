// ConsoleApplication17.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "SerialPort.h"
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

// INTRODUCCION DE ARDUINO
char output[MAX_DATA_LENGTH];
char commport[] = "\\\\.\\COM3";
char *port = commport;
char incoming[MAX_DATA_LENGTH];
SerialPort arduino(port);
bool entrada_automatizada()
{
	while (true)
	{
		int lectura_desde_puerto = arduino.readSerialPort(output, 255); //verifica que el puerto este enviando una señal
		string parametro_recibido = output; //identifica la señal recibida en output como un parametro de tipo string
		if (lectura_desde_puerto != 0) //si la señal del puerto es diferente de 0
		{
			int valor_de_teclado = parametro_recibido[0] - 48;
			if (valor_de_teclado == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
vector <int> placas;
void main_menu ()
{
	int placa=0;
	cout << "1. Entrada automatizada" << endl;
	cout << "2. Imprimir placas" << endl;
	int opcion;
	cin >> opcion;
	switch (opcion)
	{
		case 1:
			cout << "Proceda a cruzar el arco" << endl;
			if (entrada_automatizada() == true)
			{
				cout << "inserte numero de placa:  ";
				cin >> placa;
				placas.push_back(placa);
				cout << "Placa almacenada" << endl;
				main_menu();
			}
			else
			{
				cout << "Vehiculo no captado, vuelva a pasar" << endl;
			}
		case 2:
			for (int i = 0; i < placas.size(); i++)
			{
				cout << placas[i] << endl;
			}
	}
}

int main()
{
	main_menu();
	return 0;
}
