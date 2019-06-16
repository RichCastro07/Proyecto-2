//Proyecto de Programacion: Parte 1
//Ricardo Castro Barrenechea
//Juan Pablo Cruz
//Parqueo
//20 de mayo de 2019
//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//Inclusion de librerias 
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "SerialPort.h"

using namespace std;

//Funcion para modulo
int module(int x, int y)
//Funcion de modulo que recibe dos numeros enteros y retorna el residuo de la division de los mismos
//No posee restricciones
{
	if (y == 0)
	{
		return 0;
	}
	else
	{
		return x % y;
	}
}

//Numero falso para simular lo que debe pagar el carro
int monto_falso = 800;

//Estructura de datos configuracion 
struct parking_data
	//Estructura de datos que contiene los tipos de variable para la configuracion del parqueo
{
	int spaces;
	float price;
	int minimum_pay;
	int round_out_min;
	int min_to_leave;
	int coin1;
	int coin2;
	int coin3;
	int bill1;
	int bill2;
	int bill3;
	int bill4;
	int bill5;
} main_parking, parking_aux;

//Estructura de datos cajero automatico 
struct amt_data
	//Estructura de datos que contiene 
{
	// Tipos de dato para cada moneda o billete
	int coin1_total;
	int coin2_total;
	int coin3_total;
	int bill1_total;
	int bill2_total;
	int bill3_total;
	int bill4_total;
	int bill5_total;
	// Tipos de dato para cada moneda o billete en cuanto a ingresos
	int in_c1 = 0;
	int in_c2 = 0;
	int in_c3 = 0;
	int in_b1 = 0;
	int in_b2 = 0;
	int in_b3 = 0;
	int in_b4 = 0;
	int in_b5 = 0;
	// Tipos de dato para cada moneda o billete en cuanto a salidas
	int out_c1 = 0;
	int out_c2 = 0;
	int out_c3 = 0;
	int out_b1 = 0;
	int out_b2 = 0;
	int out_b3 = 0;
	int out_b4 = 0;
	int out_b5 = 0;
} main_atm, atm_aux;

//Prototipo de funcion para u menu principal 
// NO ES EL MAIN
int main_menu();

//Funcion para configurar los datos iniciales
void option_configuration()
//Funcion que no recibe parametros que se encarga de modificar los valores de la configuracion del parqueo, asi como aceptar los existentes o cancelar una modificacion
{
	int option_configuration_selected = 0;
	cout << "" << endl;
	printf("\tConfiguracion\n\n"); //cada \t es una tabulacion  y cada \n funciona como salto de linea (sirve para centrar texto) 
	printf("Cantidad de espacios disponibles: ");
	cout << parking_aux.spaces << endl;
	printf("Precio por hora: ");
	cout << parking_aux.price << endl;
	printf("Pago minimo: ");
	cout << parking_aux.minimum_pay << endl;
	printf("Redondear el cobro al minuto: ");
	cout << parking_aux.round_out_min << endl;
	printf("Minutos para salir luego del pago: ");
	cout << parking_aux.min_to_leave << endl;
	printf("Moneda 1: ");
	cout << parking_aux.coin1 << endl;
	printf("Moneda 2: ");
	cout << parking_aux.coin2 << endl;
	printf("Moneda 3: ");
	cout << parking_aux.coin3 << endl;
	printf("Billete 1: ");
	cout << parking_aux.bill1 << endl;
	printf("Billete 2: ");
	cout << parking_aux.bill2 << endl;
	printf("Billete 3: ");
	cout << parking_aux.bill3 << endl;
	printf("Billete 4: ");
	cout << parking_aux.bill4 << endl;
	printf("Billete 5: ");
	cout << parking_aux.bill5 << endl;

	// Opciones para aceptar la configuracion existente o ingresada, modificarla o cancelar
	printf("\n1. Ok \n");
	printf("2. Modificar \n");
	printf("3. Cancelar \n");

	while (option_configuration_selected < 1 || option_configuration_selected>3)
		// Ciclo que valida que la opcion ingresada cuente este en el rango de las opciones (1-3)
	{
		cout << "" << endl;
		printf("Elija una opcion: ");
		cin >> option_configuration_selected;
	}

	std::system("cls");

	switch (option_configuration_selected)
		// Switch encargado de perimitir la seleccion de las opciones Ok para aceptar, modificar para ingresar y cancelar para rechazar los valores ingresados
	{
	case 1: //Aceptar los valores preestablecidos o ingresados

		main_parking.spaces = parking_aux.spaces;
		main_parking.price = parking_aux.price;
		main_parking.minimum_pay = parking_aux.minimum_pay;
		main_parking.round_out_min = parking_aux.round_out_min;
		main_parking.min_to_leave = parking_aux.min_to_leave;
		main_parking.coin1 = parking_aux.coin1;
		main_parking.coin2 = parking_aux.coin2;
		main_parking.coin3 = parking_aux.coin3;
		main_parking.bill1 = parking_aux.bill1;
		main_parking.bill2 = parking_aux.bill2;
		main_parking.bill3 = parking_aux.bill3;
		main_parking.bill4 = parking_aux.bill4;
		main_parking.bill5 = parking_aux.bill5;
		std::system("cls");
		main_menu();

	case 2: //modificar los valores ingresados o preestablecidos
		cout << "" << endl;
		do //Ingreso de cantidad de espacios 
		{
			printf("Cantidad de espacios disponibles: ");
			cin >> parking_aux.spaces;
		} while (parking_aux.spaces < 0);

		do //Ingreso de precio por hora 
		{
			printf("Precio por hora: ");
			cin >> parking_aux.price;
		} while (parking_aux.price < 0);

		do //Ingreso del pago minimo
		{
			printf("Pago minimo: ");
			cin >> parking_aux.minimum_pay;
		} while (parking_aux.minimum_pay < 0);

		do //Ingreso de minutos para redondear cobro, se valida que sea mayor que 0 y menor que 60
		{
			printf("Redondear el cobro al minuto: ");
			cin >> parking_aux.round_out_min;
		} while (parking_aux.round_out_min < 0 || parking_aux.round_out_min>60);

		do //Ingreso de minutos para salir del parqueo 
		{
			printf("Minutos para salir luego del pago: ");
			cin >> parking_aux.min_to_leave;
		} while (parking_aux.min_to_leave < 0);

		do //Ingreso de moneda 1
		{
			printf("Moneda 1: ");
			cin >> parking_aux.coin1;

		} while (parking_aux.coin1 < 0);

		do  //Ingreso de la moneda 2
		{
			if (parking_aux.coin1 == 0)
			{
				parking_aux.coin2 = 0;
			}
			else
			{
				printf("Moneda 2: ");
				cin >> parking_aux.coin2;
			}
			if (parking_aux.coin2 == 0)
			{
				break;
			}
		} while (parking_aux.coin2 <= parking_aux.coin1);

		do //Ingreso de la moneda 3
		{
			if (parking_aux.coin2 == 0) {
				parking_aux.coin3 = 0;
				break;
			}
			else {
				printf("Moneda 3: ");
				cin >> parking_aux.coin3;
			}
		} while (parking_aux.coin3 <= parking_aux.coin2 || parking_aux.coin3 == 0);

		do //Ingreso del billete 1
		{
			printf("Billete 1: ");
			cin >> parking_aux.bill1;
		} while (parking_aux.bill1 < 0);

		do //Ingreso del billete 2
		{
			if (parking_aux.bill1 == 0)
			{
				parking_aux.bill2 = 0;
			}
			else
			{
				printf("Billete 2: ");
				cin >> parking_aux.bill2;
			}
			if (parking_aux.bill2 == 0)
			{
				break;
			}
		} while (parking_aux.bill2 <= parking_aux.bill1);

		do //Ingreso del billete 3
		{
			if (parking_aux.bill2 == 0)
			{
				parking_aux.bill3 = 0;
			}
			else
			{
				printf("Billete 3: ");
				cin >> parking_aux.bill3;
			}
			if (parking_aux.bill3 == 0)
			{
				break;
			}
		} while (parking_aux.bill3 <= parking_aux.bill2);

		do //Ingreso del billete 4
		{
			if (parking_aux.bill3 == 0)
			{
				parking_aux.bill4 = 0;
			}
			else
			{
				printf("Billete 4: ");
				cin >> parking_aux.bill4;
			}
			if (parking_aux.bill4 == 0)
			{
				break;
			}
		} while (parking_aux.bill4 <= parking_aux.bill3);

		do //Ingreso del billete 5
		{
			if (parking_aux.bill4 == 0)
			{
				parking_aux.bill5 = 0;
			}
			else
			{
				printf("Billete 5: ");
				cin >> parking_aux.bill5;
			}
			if (parking_aux.bill5 == 0)
			{
				break;
			}
		} while (parking_aux.bill5 <= parking_aux.bill4);

		if (parking_aux.bill2 == 0)
		{
			parking_aux.bill3 = 0;
			parking_aux.bill4 = 0;
			parking_aux.bill5 = 0;
		}

		else if (parking_aux.bill3 == 0)
		{
			parking_aux.bill4 = 0;
			parking_aux.bill5 = 0;
		}

		else if (parking_aux.bill4 == 0)
		{
			parking_aux.bill5 = 0;
		}

		if (parking_aux.coin1 == 0 && parking_aux.bill1 == 0) //El pago minimo debe ir de la mano del minimo monto de moneda y billete

		{
			parking_aux.minimum_pay = 0;
		}

		else
			//el pago minimo debe ir de la mano con el valor minimo de cada metodo de pago
			//&& funciona como un condicional "y"
		{
			while (module(parking_aux.minimum_pay, parking_aux.coin1) != 0
				&& module(parking_aux.minimum_pay, parking_aux.coin2) != 0
				&& module(parking_aux.minimum_pay, parking_aux.coin3) != 0
				&& module(parking_aux.minimum_pay, parking_aux.bill1) != 0
				&& module(parking_aux.minimum_pay, parking_aux.bill2) != 0
				&& module(parking_aux.minimum_pay, parking_aux.bill3) != 0
				&& module(parking_aux.minimum_pay, parking_aux.bill4) != 0
				&& module(parking_aux.minimum_pay, parking_aux.bill5)) {
				do {
					printf("Pago minimo: ");
					cin >> parking_aux.minimum_pay;
				} while (parking_aux.minimum_pay < 0);
			}
		}

		std::system("cls"); //limpia la pantalla

		option_configuration(); //Reinicia el menu

	case 3:
		parking_aux.spaces = main_parking.spaces;
		parking_aux.price = main_parking.price;
		parking_aux.minimum_pay = main_parking.minimum_pay;
		parking_aux.round_out_min = main_parking.round_out_min;
		parking_aux.min_to_leave = main_parking.min_to_leave;
		parking_aux.coin1 = main_parking.coin1;
		parking_aux.coin2 = main_parking.coin2;
		parking_aux.coin3 = main_parking.coin3;
		parking_aux.bill1 = main_parking.bill1;
		parking_aux.bill2 = main_parking.bill2;
		parking_aux.bill3 = main_parking.bill3;
		parking_aux.bill4 = main_parking.bill4;
		parking_aux.bill5 = main_parking.bill5;
		std::system("cls");
		main_menu();
	}
}

//Funcion para convertir de un entero a un tipo caracter (char)
string itoa(int number) {
	char buffer[10];
	sprintf(buffer, "%d", number);
	return buffer;
}

//Funcion para cargar cuantas monedas y billetes hay de cada tipo
void load_ATM()
{
	int option_configuration_selected = 0;
	char buffer[8];
	char coin1[8];
	char coin2[8];
	char coin3[8];
	char bill1[8];
	char bill2[8];
	char bill3[8];
	char bill4[8];
	char bill5[8];

	cout << "" << endl;
	printf("\t\t\t\t\t\tCargar cajero\n\n\n");
	printf("\t\t\tSaldo antes de la carga");
	printf("\t\t\tCarga");
	printf("\t\t\t\tSaldo\n\n");
	printf("Denominacion");
	printf("\t\tCantidad");
	printf("\tTotal");
	printf("\t\tCantidad");
	printf("\tTotal");
	printf("\t\tCantidad");
	printf("\tTotal");

	//Fila monedas 1
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin1).c_str()); //Convierte el entero a char y luego a string para poderlo imprimir mediante printf
	printf("\t\t");
	printf(itoa(main_atm.coin1_total).c_str()); //Convierte el entero a char y luego a string para poderlo imprimir mediante printf
	printf("\t\t");
	printf(itoa(main_atm.coin1_total * main_parking.coin1).c_str()); //Realiza la multiplicacion de enteros, lo hace un char y luego un string
	printf("\t\t");
	printf(itoa(atm_aux.coin1_total).c_str());  //Convierte el entero a char y luego a string para poderlo imprimir mediante printf
	printf("\t\t");
	printf(itoa(atm_aux.coin1_total * main_parking.coin1).c_str()); //Realiza la multiplicacion de enteros, lo hace un char y luego un string
	printf("\t\t");
	printf(itoa(main_atm.coin1_total + atm_aux.coin1_total).c_str()); //realiza la suma de enteros, lo hace un char y luego un string
	printf("\t\t");
	printf(itoa((main_atm.coin1_total * main_parking.coin1) + (atm_aux.coin1_total * main_parking.coin1)).c_str());//Realiza la multiplicacion y suma  de enteros, lo hace un char y luego un string

	//Repite el mismo procedimient con cada tipo de moneda y billete 

	//Fila monedas 2
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin2_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin2_total * main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.coin2_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.coin2_total * main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin2_total + atm_aux.coin2_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.coin2_total * main_parking.coin2) + (atm_aux.coin2_total * main_parking.coin2)).c_str());

	//Fila monedas 3
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin3_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin3_total * main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.coin3_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.coin3_total * main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin3_total + atm_aux.coin3_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.coin3_total * main_parking.coin3) + (atm_aux.coin3_total * main_parking.coin3)).c_str());

	//Fila total monedas
	printf("\nTOTAL DE MONEDAS: ");
	printf("\t");
	printf(itoa(main_atm.coin1_total + main_atm.coin2_total + main_atm.coin3_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.coin1_total * main_parking.coin1) + (main_atm.coin2_total * main_parking.coin2) + (main_atm.coin3_total * main_parking.coin3)).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.coin1_total + atm_aux.coin2_total + atm_aux.coin3_total).c_str());
	printf("\t\t");
	printf(itoa((atm_aux.coin1_total * main_parking.coin1) + (atm_aux.coin2_total * main_parking.coin2) + (atm_aux.coin3_total * main_parking.coin3)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.coin1_total + main_atm.coin2_total + main_atm.coin3_total + atm_aux.coin1_total + atm_aux.coin2_total + atm_aux.coin3_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.coin1_total * main_parking.coin1) + (main_atm.coin2_total * main_parking.coin2) + (main_atm.coin3_total * main_parking.coin3) + (atm_aux.coin1_total * main_parking.coin1) + (atm_aux.coin2_total * main_parking.coin2) + (atm_aux.coin3_total * main_parking.coin3)).c_str());


	//Fila billetes 1
	printf("\n\nBilletes de: ");
	printf(itoa(main_parking.bill1).c_str());
	printf("\t");
	printf(itoa(main_atm.bill1_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill1_total * main_parking.bill1).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill1_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill1_total * main_parking.bill1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill1_total + atm_aux.bill1_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill1_total * main_parking.bill1) + (atm_aux.bill1_total * main_parking.bill1)).c_str());

	//Fila billetes 2
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill2).c_str());
	printf("\t");
	printf(itoa(main_atm.bill2_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill2_total * main_parking.bill2).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill2_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill2_total * main_parking.bill2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill2_total + atm_aux.bill2_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill2_total * main_parking.bill2) + (atm_aux.bill2_total * main_parking.bill2)).c_str());


	//Fila billetes 3
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill3).c_str());
	printf("\t");
	printf(itoa(main_atm.bill3_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill3_total * main_parking.bill3).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill3_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill3_total * main_parking.bill3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill3_total + atm_aux.bill3_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill3_total * main_parking.bill3) + (atm_aux.bill3_total * main_parking.bill3)).c_str());


	//Fila billetes 4
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill4).c_str());
	printf("\t");
	printf(itoa(main_atm.bill4_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill4_total * main_parking.bill4).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill4_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill4_total * main_parking.bill4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill4_total + atm_aux.bill4_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill4_total * main_parking.bill4) + (atm_aux.bill4_total * main_parking.bill4)).c_str());


	//Fila billetes 5
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill5).c_str());
	printf("\t");
	printf(itoa(main_atm.bill5_total).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill5_total * main_parking.bill5).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill5_total).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill5_total * main_parking.bill5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill5_total + atm_aux.bill5_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill5_total * main_parking.bill5) + (atm_aux.bill5_total * main_parking.bill5)).c_str());


	//Fila total billetes
	printf("\nTOTAL DE BILLETES: ");
	printf("\t");
	printf(itoa(main_atm.bill1_total + main_atm.bill2_total + main_atm.bill3_total + main_atm.bill4_total + main_atm.bill5_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill1_total * main_parking.bill1) + (main_atm.bill2_total * main_parking.bill2) + (main_atm.bill3_total * main_parking.bill3) + (main_atm.bill4_total * main_parking.bill4) + (main_atm.bill5_total * main_parking.bill5)).c_str());
	printf("\t\t");
	printf(itoa(atm_aux.bill1_total + atm_aux.bill2_total + atm_aux.bill3_total + atm_aux.bill4_total + atm_aux.bill5_total).c_str());
	printf("\t\t");
	printf(itoa((atm_aux.bill1_total * main_parking.bill1) + (atm_aux.bill2_total * main_parking.bill2) + (atm_aux.bill3_total * main_parking.bill3) + (atm_aux.bill4_total * main_parking.bill4) + (atm_aux.bill5_total * main_parking.bill5)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.bill1_total + main_atm.bill2_total + main_atm.bill3_total + main_atm.bill4_total + main_atm.bill5_total + atm_aux.bill1_total + atm_aux.bill2_total + atm_aux.bill3_total + atm_aux.bill4_total + atm_aux.bill5_total).c_str());
	printf("\t\t");
	printf(itoa((main_atm.bill1_total * main_parking.bill1) + (main_atm.bill2_total * main_parking.bill2) + (main_atm.bill3_total * main_parking.bill3) + (main_atm.bill4_total * main_parking.bill4) + (main_atm.bill5_total * main_parking.bill5) + (atm_aux.bill1_total * main_parking.bill1) + (atm_aux.bill2_total * main_parking.bill2) + (atm_aux.bill3_total * main_parking.bill3) + (atm_aux.bill4_total * main_parking.bill4) + (atm_aux.bill5_total * main_parking.bill5)).c_str());


	//Opciones varias para determinar lo que se desea hacer con los valores ingresados o preestablecidos
	printf("\n\n\n1. Ok \n");
	printf("2. Modificar \n");
	printf("3. Cancelar \n");

	while (option_configuration_selected < 1 || option_configuration_selected>3)
		//Ciclo que se encarga de rstringir solo las opciones seleccionables entre 1 y 3
	{
		cout << "" << endl;
		printf("Elija una opcion: ");
		cin >> option_configuration_selected;
	}

	std::system("cls");

	switch (option_configuration_selected)
	{
	case 1: //aceptar mantiene los valores establecidos o, por default, los preestablecidos

		//Totales
		main_atm.coin1_total = main_atm.coin1_total + atm_aux.coin1_total;
		main_atm.coin2_total = main_atm.coin2_total + atm_aux.coin2_total;
		main_atm.coin3_total = main_atm.coin3_total + atm_aux.coin3_total;
		main_atm.bill1_total = main_atm.bill1_total + atm_aux.bill1_total;
		main_atm.bill2_total = main_atm.bill2_total + atm_aux.bill2_total;
		main_atm.bill3_total = main_atm.bill3_total + atm_aux.bill3_total;
		main_atm.bill4_total = main_atm.bill4_total + atm_aux.bill4_total;
		main_atm.bill5_total = main_atm.bill5_total + atm_aux.bill5_total;

		main_atm.in_c1 = main_atm.in_c1 + atm_aux.coin1_total;
		main_atm.in_c2 = main_atm.in_c2 + atm_aux.coin2_total;
		main_atm.in_c3 = main_atm.in_c3 + atm_aux.coin3_total;
		main_atm.in_b1 = main_atm.in_b1 + atm_aux.bill1_total;
		main_atm.in_b2 = main_atm.in_b2 + atm_aux.bill2_total;
		main_atm.in_b3 = main_atm.in_b3 + atm_aux.bill3_total;
		main_atm.in_b4 = main_atm.in_b4 + atm_aux.bill4_total;
		main_atm.in_b5 = main_atm.in_b5 + atm_aux.bill5_total;

		atm_aux.coin1_total = 0;
		atm_aux.coin2_total = 0;
		atm_aux.coin3_total = 0;
		atm_aux.bill1_total = 0;
		atm_aux.bill2_total = 0;
		atm_aux.bill3_total = 0;
		atm_aux.bill4_total = 0;
		atm_aux.bill5_total = 0;

		std::system("cls"); //limpia la pantalla
		main_menu(); //retorna al menu
	case 2:
		cout << "" << endl;

		do //Ingresa la cantidad de monedas correspondientes al tipo 1
		{
			printf("Cantidad de primer moneda: ");
			cin >> atm_aux.coin1_total;
		} while (atm_aux.coin1_total < 0);

		do //Ingresa la cantidad de monedas correspondientes al tipo 2
		{
			printf("Cantidad de segunda moneda: ");
			cin >> atm_aux.coin2_total;
		} while (atm_aux.coin2_total < 0);

		do //Ingreso de cantidad de monedas de tipo 3 
		{
			printf("Cantidad de tercera moneda: ");
			cin >> atm_aux.coin3_total;
		} while (atm_aux.coin3_total < 0);

		do //Cantidad de billetes de tipo 1
		{
			printf("Cantidad de primer billete: ");
			cin >> atm_aux.bill1_total;
		} while (atm_aux.bill1_total < 0);

		do //Cantidad de billetes de tipo 2
		{
			printf("Cantidad de segundo billete: ");
			cin >> atm_aux.bill2_total;
		} while (atm_aux.bill2_total < 0);

		do //Cantidad de billetes de tipo 3
		{
			printf("Cantidad de tercer billete: ");
			cin >> atm_aux.bill3_total;
		} while (atm_aux.bill3_total < 0);

		do //cantidad de billetes de tipo 4
		{
			printf("Cantidad de cuarto billete: ");
			cin >> atm_aux.bill4_total;
		} while (atm_aux.bill4_total < 0);

		do //cantidad de billetes de tipo 5
		{
			printf("Cantidad de quinto billete: ");
			cin >> atm_aux.bill5_total;
		} while (atm_aux.bill5_total < 0);

		std::system("cls"); //Limpiar pantalla
		load_ATM(); //Reiniciar menu

	case 3:
		atm_aux.coin1_total = main_atm.coin1_total;
		atm_aux.coin2_total = main_atm.coin2_total;
		atm_aux.coin3_total = main_atm.coin3_total;
		atm_aux.bill1_total = main_atm.bill1_total;
		atm_aux.bill2_total = main_atm.bill2_total;
		atm_aux.bill3_total = main_atm.bill3_total;
		atm_aux.bill4_total = main_atm.bill4_total;
		atm_aux.bill5_total = main_atm.bill5_total;

		std::system("cls"); //Limpiar pantalla
		main_menu(); //Menu principal
	}
}

//Funcion para saber cuanto saldo queda en el cajero en cuanto a ingresos y salidas
int balance_ATM()
{
	int option_configuration_selected = 0;
	char buffer[3];
	cout << "" << endl;
	printf("\t\t\t\t\t\tSaldo del cajero\n\n\n");
	printf("\t\t\t\tEntradas");
	printf("\t\t\tSalidas");
	printf("\t\t\t\tSaldo\n\n");
	printf("Denominacion");
	printf("\t\tCantidad");
	printf("\tTotal");
	printf("\t\tCantidad");
	printf("\tTotal");
	printf("\t\tCantidad");
	printf("\tTotal");

	//Fila monedas 1
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c1 * main_parking.coin1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c1 * main_parking.coin1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c1 - main_atm.out_c1).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_c1 * main_parking.coin1) - (main_atm.out_c1 * main_parking.coin1)).c_str());

	//Fila monedas 2
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c2 * main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c2 * main_parking.coin2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c2 - main_atm.out_c2).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_c2 * main_parking.coin2) - (main_atm.out_c2 * main_parking.coin2)).c_str());

	//Fila monedas 3
	printf("\nMonedas de: ");
	printf(itoa(main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c3 * main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c3 * main_parking.coin3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c3 - main_atm.out_c3).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_c3 * main_parking.coin3) - (main_atm.out_c3 * main_parking.coin3)).c_str());

	//Fila total monedas
	printf("\nTOTAL DE MONEDAS: ");
	printf("\t");
	printf(itoa(main_atm.in_c1 + main_atm.in_c2 + main_atm.in_c3).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_c1 * main_parking.coin1) + (main_atm.in_c2 * main_parking.coin2) + (main_atm.in_c3 * main_parking.coin3)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_c1 + main_atm.out_c2 + main_atm.out_c3).c_str());
	printf("\t\t");
	printf(itoa((main_atm.out_c1 * main_parking.coin1) + (main_atm.out_c2 * main_parking.coin2) + (main_atm.out_c3 * main_parking.coin3)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_c1 + main_atm.in_c2 + main_atm.in_c3 + main_atm.out_c1 + main_atm.out_c2 + main_atm.out_c3).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_c1 * main_parking.coin1) + (main_atm.in_c2 * main_parking.coin2) + (main_atm.in_c3 * main_parking.coin3) + (main_atm.out_c1 * main_parking.coin1) + (main_atm.out_c2 * main_parking.coin2) + (main_atm.out_c3 * main_parking.coin3)).c_str());


	//Fila billetes 1
	printf("\n\nBilletes de: ");
	printf(itoa(main_parking.bill1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b1 * main_parking.bill1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b1 * main_parking.bill1).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b1 - main_atm.out_b1).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b1 * main_parking.bill1) - (main_atm.out_b1 * main_parking.bill1)).c_str());

	//Fila billetes 2
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b2 * main_parking.bill2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b2 * main_parking.bill2).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b2 - main_atm.out_b2).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b2 * main_parking.bill2) - (main_atm.out_b2 * main_parking.bill2)).c_str());


	//Fila billetes 3
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b3 * main_parking.bill3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b3 * main_parking.bill3).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b3 - main_atm.out_b3).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b3 * main_parking.bill3) - (main_atm.out_b3 * main_parking.bill3)).c_str());


	//Fila billetes 4
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b4 * main_parking.bill4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b4 * main_parking.bill4).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b4 - main_atm.out_b4).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b4 * main_parking.bill4) - (main_atm.out_b4 * main_parking.bill4)).c_str());


	//Fila billetes 5
	printf("\nBilletes de: ");
	printf(itoa(main_parking.bill5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b5 * main_parking.bill5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b5 * main_parking.bill5).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b5 - main_atm.out_b5).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b5 * main_parking.bill5) - (main_atm.out_b5 * main_parking.bill5)).c_str());


	//Fila total billetes
	printf("\nTOTAL DE BILLETES: ");
	printf("\t");
	printf(itoa(main_atm.in_b1 + main_atm.in_b2 + main_atm.in_b3 + main_atm.in_b4 + main_atm.in_b5).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b1 * main_parking.bill1) + (main_atm.in_b2 * main_parking.bill2) + (main_atm.in_b3 * main_parking.bill3) + (main_atm.in_b4 * main_parking.bill4) + (main_atm.in_b5 * main_parking.bill5)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.out_b1 + main_atm.out_b2 + main_atm.out_b3 + main_atm.out_b4 + main_atm.out_b5).c_str());
	printf("\t\t");
	printf(itoa((main_atm.out_b1 * main_parking.bill1) + (main_atm.out_b2 * main_parking.bill2) + (main_atm.out_b3 * main_parking.bill3) + (main_atm.out_b4 * main_parking.bill4) + (main_atm.out_b5 * main_parking.bill5)).c_str());
	printf("\t\t");
	printf(itoa(main_atm.in_b1 + main_atm.in_b2 + main_atm.in_b3 + main_atm.in_b4 + main_atm.in_b5 + main_atm.out_b1 + main_atm.out_b2 + main_atm.out_b3 + main_atm.out_b4 + main_atm.out_b5).c_str());
	printf("\t\t");
	printf(itoa((main_atm.in_b1 * main_parking.bill1) + (main_atm.in_b2 * main_parking.bill2) + (main_atm.in_b3 * main_parking.bill3) + (main_atm.in_b4 * main_parking.bill4) + (main_atm.in_b5 * main_parking.bill5) - (main_atm.out_b1 * main_parking.bill1) - (main_atm.out_b2 * main_parking.bill2) - (main_atm.out_b3 * main_parking.bill3) - (main_atm.out_b4 * main_parking.bill4) - (main_atm.out_b5 * main_parking.bill5)).c_str());

	cout << "" << endl;
	printf("\n\nVaciar cajero (Si  /  No): ");
	cin >> buffer;

	printf("\n\n\n1. Ok \n");
	printf("3. Cancelar \n");

	while (option_configuration_selected < 1 || option_configuration_selected > 3)
	{
		cout << "" << endl;
		printf("Elija una opcion: ");
		cin >> option_configuration_selected;
	}
	if (option_configuration_selected == 1)
	{
		if (strcmp(buffer, "Si") == 0) //compara dos strings y si son iguales vacia el cajero
		{
			main_atm.coin1_total = 0;
			main_atm.coin2_total = 0;
			main_atm.coin3_total = 0;
			main_atm.bill1_total = 0;
			main_atm.bill2_total = 0;
			main_atm.bill3_total = 0;
			main_atm.bill4_total = 0;
			main_atm.bill5_total = 0;

			main_atm.in_c1 = 0;
			main_atm.in_c2 = 0;
			main_atm.in_c3 = 0;
			main_atm.in_b1 = 0;
			main_atm.in_b2 = 0;
			main_atm.in_b3 = 0;
			main_atm.in_b4 = 0;
			main_atm.in_b5 = 0;

			main_atm.out_c1 = 0;
			main_atm.out_c2 = 0;
			main_atm.out_c3 = 0;
			main_atm.out_b1 = 0;
			main_atm.out_b2 = 0;
			main_atm.out_b3 = 0;
			main_atm.out_b4 = 0;
			main_atm.out_b5 = 0;

			atm_aux.coin1_total = 0;
			atm_aux.coin2_total = 0;
			atm_aux.coin3_total = 0;
			atm_aux.bill1_total = 0;
			atm_aux.bill2_total = 0;
			atm_aux.bill3_total = 0;
			atm_aux.bill4_total = 0;
			atm_aux.bill5_total = 0;
		}
	}
	std::system("cls");
	main_menu();
	return 0;
}

//Funcion para dar el mejor vuelto posible con la menor cantidad de billetes/monedas
//Recibe un parametro que es el monto a devolver
int dar_vuelto(int monto) 
{
	printf("\n\nVuelto faltante:\t");
	printf(itoa(monto_falso).c_str());
	if (monto <= 0) 
	{
		if (((monto*-1) >= main_parking.bill5) && (main_atm.bill5_total > 0)) 
//Evalua el valor del monto con respecto al billete 5 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.bill5).c_str());
			monto_falso = monto_falso + main_parking.bill5;
			main_atm.bill5_total = main_atm.bill5_total - 1;
			main_atm.out_b5 = main_atm.out_b5 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}

		else if (((monto*-1) >= main_parking.bill4) && (main_atm.bill4_total > 0))
//Evalua el valor del monto con respecto al billete 4 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.bill4).c_str());
			monto_falso = monto_falso + main_parking.bill4;
			main_atm.bill4_total = main_atm.bill4_total - 1;
			main_atm.out_b4 = main_atm.out_b4 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}

		else if (((monto*-1) >= main_parking.bill3) && (main_atm.bill3_total > 0)) 
//Evalua el valor del monto con respecto al billete 3 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.bill3).c_str());
			monto_falso = monto_falso + main_parking.bill3;
			main_atm.bill3_total = main_atm.bill3_total - 1;
			main_atm.out_b3 = main_atm.out_b3 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}

		else if (((monto*-1) >= main_parking.bill2) && (main_atm.bill2_total > 0)) 
//Evalua el valor del monto con respecto al billete 2 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.bill2).c_str());
			monto_falso = monto_falso + main_parking.bill2;
			main_atm.bill2_total = main_atm.bill2_total - 1;
			main_atm.out_b2 = main_atm.out_b2 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}
		else if (((monto*-1) >= main_parking.bill1) && (main_atm.bill1_total > 0))
//Evalua el valor del monto con respecto al billete 1 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.bill1).c_str());
			monto_falso = monto_falso + main_parking.bill1;
			main_atm.bill1_total = main_atm.bill1_total - 1;
			main_atm.out_b1 = main_atm.out_b1 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}
		else if (((monto*-1) >= main_parking.coin3) && (main_atm.coin3_total > 0))
//Evalua el valor del monto con respecto a la moneda 3 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.coin3).c_str());
			monto_falso = monto_falso + main_parking.coin3;
			main_atm.coin3_total = main_atm.coin3_total - 1;
			main_atm.out_c3 = main_atm.out_c3 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}
		else if (((monto*-1) >= main_parking.coin2) && (main_atm.coin2_total > 0))
//Evalua el valor del monto con respecto al moneda 2 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.coin2).c_str());
			monto_falso = monto_falso + main_parking.coin2;
			main_atm.coin2_total = main_atm.coin2_total - 1;
			main_atm.out_c2 = main_atm.out_c2 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}
		else if (((monto*-1) >= main_parking.coin1) && (main_atm.coin1_total > 0)) 
//Evalua el valor del monto con respecto al moneda 1 para asi dar el posible vuelto con respecto a este metodo de pago
		{
			printf("\nMoneda devuelta:\t");
			printf(itoa(main_parking.coin1).c_str());
			monto_falso = monto_falso + main_parking.coin1;
			main_atm.coin1_total = main_atm.coin1_total - 1;
			main_atm.out_c1 = main_atm.out_c1 + 1;
			dar_vuelto(monto_falso); //Reinicia la funcion 
		}
		else 
// Acaba el sistema de pago
		{
			printf("\n\nGracias por confiar en nosotros");
			main_menu();
		}
	}
	else {
		printf("\n\nGracias por confiar en nosotros");
		main_menu();
	}
	return 0;
}

// INTRODUCCION DE ARDUINO
char output[MAX_DATA_LENGTH];
char commport[] = "\\\\.\\COM3";
char *port = commport;
char incoming[MAX_DATA_LENGTH];
SerialPort arduino(port);

//Funcion conectada con el teclado
int cajero_ATM() 
{
	cout << "El monto a pagar corresponde a:  " << monto_falso << endl;
	if (monto_falso > 0) //Evalua que el cobro sea positivo
	{
		cout << "Seleccionar el boton \n" << endl;
		while (true)
		{
			int lectura_desde_puerto = arduino.readSerialPort(output, 255); //verifica que el puerto este enviando una señal
			string parametro_recibido = output; //identifica la señal recibida en output como un parametro de tipo string
			if (lectura_desde_puerto != 0) //si la señal del puerto es diferente de 0
			{
				int valor_de_teclado = parametro_recibido[0] - 48;
				cout << valor_de_teclado;
				printf("\n\nExtraer monedas\n");
				printf(itoa(monto_falso).c_str());
				printf("\n");
				cout << "" << endl;
				std::system("cls");
				while (valor_de_teclado >= 1 and valor_de_teclado <= 9)
				{
					switch (valor_de_teclado)
					{
					case 1:
						if (main_atm.coin1_total > 0) //conecta el boton 1 del teclado matricial con la moneda 1 y modifica el valor que se debe
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.coin1).c_str());
							monto_falso = monto_falso - main_parking.coin1;
							main_atm.coin1_total = main_atm.coin1_total - 1;
							main_atm.out_c1 = main_atm.out_c1 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM(); //Reinicia el cajero porque aun no se cumplen los requerimientos
						break;

					case 2:
						if (main_atm.coin2_total > 0)  //conecta el boton 2 del teclado matricial con la moneda 2 y modifica el valor que se debe
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.coin2).c_str());
							monto_falso = monto_falso - main_parking.coin2;
							main_atm.coin2_total = main_atm.coin2_total - 1;
							main_atm.out_c2 = main_atm.out_c2 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM(); //Reinicia el cajero porque aun no se cumplen los requerimientos
						break;

					case 3:
						if (main_atm.coin3_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.coin3).c_str());
							monto_falso = monto_falso - main_parking.coin3;
							main_atm.coin3_total = main_atm.coin3_total - 1;
							main_atm.out_c3 = main_atm.out_c3 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 4:
						if (main_atm.bill1_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.bill1).c_str());
							monto_falso = monto_falso - main_parking.bill1;
							main_atm.bill1_total = main_atm.bill1_total - 1;
							main_atm.out_b1 = main_atm.out_b1 + 1;
						}
						else {
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 5:
						if (main_atm.bill2_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.bill2).c_str());
							monto_falso = monto_falso - main_parking.bill2;
							main_atm.bill2_total = main_atm.bill2_total - 1;
							main_atm.out_b2 = main_atm.out_b2 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 6:
						if (main_atm.bill3_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.bill3).c_str());
							monto_falso = monto_falso - main_parking.bill3;
							main_atm.bill3_total = main_atm.bill3_total - 1;
							main_atm.out_b3 = main_atm.out_b3 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 7:
						if (main_atm.bill4_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.bill4).c_str());
							monto_falso = monto_falso - main_parking.bill4;
							main_atm.bill4_total = main_atm.bill4_total - 1;
							main_atm.out_b4 = main_atm.out_b4 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 8:
						if (main_atm.bill5_total > 0)
						{
							printf("Moneda/billete extraido\n");
							printf(itoa(main_parking.bill5).c_str());
							monto_falso = monto_falso - main_parking.bill5;
							main_atm.bill5_total = main_atm.bill5_total - 1;
							main_atm.out_b5 = main_atm.out_b5 + 1;
						}
						else
						{
							printf("No hay monedas/billetes de esa denominacion");
							printf("\n");
						}
						cajero_ATM();
						break;
					case 9:
						int numero_de_cuenta;
						int pin;
						int monto_debitado;
						printf("Digite numero de cuenta\n");
						cin >> numero_de_cuenta;
						printf("Digite pin de cuenta\n");
						cin >> pin;
						printf("Digite monto a debitar de la cuenta\n");
						cin >> monto_debitado;
						monto_falso = monto_falso - monto_debitado;
						cajero_ATM();
						break;
					}
				}
			}
		}
	}
	else 
	{
		dar_vuelto(monto_falso);
	}
	return 0;
}

void ayuda()
{
	string abrir = "open";
	ShellExecuteA(GetDesktopWindow(), abrir.c_str(), "manual.pdf", NULL, NULL, SW_SHOWNORMAL);
}

int main_menu()
// Menu principal donde se toman las acciones relacionadas al programa sin necesidad de reiniciar y perder datos en el main
{

	int option_menu_selected = 0;

	cout << "" << endl;
	printf("1. Configuracion \n");
	printf("2. Cargar cajero \n");
	printf("3. Saldo del cajero \n");
	printf("4. Ingreso de dinero \n");
	printf("5. Entrada de vehiculo \n");
	printf("6. Cajero del parquero \n");
	printf("7. Salida de vehiculo \n");
	printf("8. Ayuda \n");
	printf("9. Acerca de \n");
	printf("0. Fin \n");

	do 
	// Validar que la opcion ingresada sea mayor que 0 y menor que 9
	{
		cout << "" << endl;
		printf("Elija una opcion: ");
		cin >> option_menu_selected;
	} while (option_menu_selected < 0 || option_menu_selected>9);

	std::system("cls");

	switch (option_menu_selected)
	//Opciones del menu
	{
	case 0:
		exit(0);
	case 1:
		option_configuration();
	case 2:
		load_ATM();
	case 3:
		balance_ATM();
	case 6:
		cajero_ATM();
	case 8:
		ayuda();
	case 9:
		int retornar_a_menu;
		cout << "Gracias por utilizar Parking Deluxe 2019" << endl;
		cout << endl;
		cout << "Desarrolladores:" << endl;
		cout << "Ricardo Castro" << endl;
		cout << "Juan Pablo Cruz" << endl;
		cout << endl;
		cout << "Version 1.0.0" << endl;
		cout << endl;
		cout << "Agradecimientos especiales al profesor William Mata y a los tutores Jose Monse y Adrian Sanchez por ser guias en el desarrollo de este proyecto" << endl;
		cout << endl;
		cout << "Que desea hacer?" << endl;
		cout << endl;
		cout << "1. Volver a menu principal" << endl;
		cout << "2. Salir del programa" << endl;
		cin >> retornar_a_menu;
		switch (retornar_a_menu)
		{
		case 1:
			main_menu();
		}

	}

	return 0;
}

int main()
{
//Main del programa
	main_menu();
	return 0;
}
