#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Columnas {
	int enlace;
	string caracter;
};

struct Enlace {
	string caracter;
	int enlace;
};

struct Filas {
	Columnas col[40];
	int id;
	int cantCols;
	Enlace enlace[40];
};

struct AUT {
	int cantFilas;
	Filas fila[40];
};


bool existeEnNFA(int, string, Filas);
Columnas crearColumna(int, string);
void mostrarAutomata(AUT);
Filas recorrerEpsilon(AUT, int[]);
int* recorrerNFA(AUT, Filas, string);

int main()
{
	int check[20];
	int cantEstados;
	int cantAlfabeto = 0;
	AUT nfa;
	AUT dfa;
	string alfabeto[40];



	//Llenar todas las columnas de -1 (Se deja todo sin asignaciones)
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			nfa.fila[i].col[j].enlace = -1;
			nfa.fila[i].col[j].caracter = "-1";
			dfa.fila[i].col[j].enlace = -1;
			dfa.fila[i].col[j].caracter = "-1";
			dfa.fila[i].enlace[j].enlace = -1;
		}
		nfa.fila[i].id = -1;
		dfa.fila[i].id = -1;

	}
	for (int i = 0; i < 20; i++) {
		check[i] = -1;
	}
	//Fin quitar asignaciones


	//Inicio ingresar cantidad de estados y cantidad de caracteres
	cout << endl;
	/*cout << "                                       ";
	cout << "Cantidad de estados: "; cin >> cantEstados;
	*/

	int estadoInicial = 0;
	// |-|-|-|-|-|-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-|
	string line, tempLine, tempBasura, caracterTemp, estadoActual, estadoTemp = "a", enlaceTemp;
	int contarEstados[40], contarEstadosTxt = 0, existEstado = 0, contColumnasTxt = 0;
	for (int i = 0; i < 40; i++) {
		contarEstados[i] = -1;
	}
	ifstream archivoentrada("AFN.txt");
	
	int contAlf = 0;
	

	int prueba = -1;
	int contarCaracteres = 0, contarLineas = 0;;
	cout << "Prueba vale " << prueba << endl;
	if (archivoentrada.is_open())
	{
		while (getline(archivoentrada, line))
		{
			



			if (check[1] == -1 && line.find("T = {") != std::string::npos)
			{
				check[1] = 1;
				line.erase(line.find("T"), strlen("T = {"));
				line.erase(line.find("}"), strlen("}"));
				stringstream(line) >> cantEstados;
			}


			else if (check[3] == -1 && line.find("A = {") != std::string::npos)
			{
				check[3] = 1;
				line.erase(line.find("A"), strlen("A = {"));
				line.erase(line.find("}"), strlen("}"));
				tempLine = line;

				stringstream ss(line);


				while (getline(ss, alfabeto[contAlf], ','))
				{
					alfabeto[contAlf];

					contAlf++;
					cantAlfabeto = contAlf;
					cout << "Cantidad de alfabeto: " << cantAlfabeto << endl;
				}
			}
			else if (line.find("F(") != std::string::npos) 
			{
				contarEstadosTxt++;
				line.erase(line.find("F("), strlen("F("));
				line.erase(line.find("="), strlen("="));
				line.erase(line.find("{"), strlen("{"));
				line.erase(line.find("}"), strlen("}"));
				stringstream ss(line);


				getline(ss, estadoActual, ',');
				if (estadoTemp == estadoActual)
				{
					cout << "CoontColumnasTxt = " << contColumnasTxt << endl;
				}
				else
				{

					if (estadoTemp == "a") 
					{

					}
					else 
					{
						nfa.fila[stoi(estadoTemp)].id = stoi(estadoTemp);
						nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].caracter = "$";
						nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].enlace = stoi(estadoTemp);
						cout << "Se guardo en la fila " << stoi(estadoTemp) << ", en la columna " << contColumnasTxt << endl;
						cout << " el enlace " << nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].enlace << " con caracter " << nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].caracter << endl;
						nfa.fila[stoi(estadoTemp)].cantCols = contColumnasTxt;
					}


					contColumnasTxt = 0;
					cout << "CoontColumnasTxt = " << contColumnasTxt << endl;
				}

				estadoTemp = estadoActual;

				existEstado = 0;
				char *cstr = &estadoTemp[0];
				line.erase(line.find(estadoTemp), strlen(cstr));
				line.erase(line.find(","), strlen(","));

				cout << "Contar estados txt: " << contarEstadosTxt << endl;


				getline(ss, caracterTemp, ')');

				cout << endl;
				while (getline(ss, enlaceTemp, ',')) 
				{
					nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].caracter = caracterTemp;
					nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].enlace = stoi(enlaceTemp);
					cout << "Se guardo en la fila " << stoi(estadoTemp) << ", en la columna " << contColumnasTxt << endl;
					cout << " el enlace " << nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].enlace << " con caracter " << nfa.fila[stoi(estadoTemp)].col[contColumnasTxt].caracter << endl;
					contColumnasTxt++;
				}
				cout << endl;

			}
			if (line == "") continue;
			cout << line << endl;
			cout << endl;
			contarLineas++;
		}
		archivoentrada.close();
	}
	else { cout << "Unable to open file"; }
	// |-|-|-|-|-|-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-||-|-|-|-|
	nfa.cantFilas = cantEstados;

	/*cout << "                               ";
	cout << "Cantidad de caracteres del alfabeto: "; cin >> cantAlfabeto;
	cout << endl;*/

	//Fin ingresar cantidades


	//Inicio ingresar caracteres del alfabeto

	/*cout << "                                ";
	cout << "Ingrese los caracteres del alfabeto " << endl;
	for (int i = 0; i < cantAlfabeto; i++) {
	cout << "        ";
	cin >> alfabeto[i];
	}*/


	//Fin ingresar caracteres

	/*
	//Inicio almacenar NFA
	cout << "                               ";
	cout << "Ingrese las transiciones de cada estado" << endl;
	for (int i = 0; i < cantEstados; i++) { //Ciclo que recorre cada estado del automata

	int cantColumnas = 0;

	for (int j = 0; j <= cantAlfabeto; j++) { //Ciclo que recorre cada letra del alfabeto del automata

	int ingreso = 0; //Se inicializa para que pueda entrar al ciclo while cuando salga de el

	while (ingreso != -1) { //Sigue solicitando datos en la misma letra hasta que ingrese -1

	cout << "                                         ";
	cout << "( " << i << " , " << alfabeto[j] << " ) = "; cin >> ingreso;
	string caracter = alfabeto[j];
	if (j == cantAlfabeto&&ingreso==i) {
	cout << "                              ";
	cout << "No necesita ingresar esa transicion" << endl;
	}else if (ingreso == -1) {
	if (j == cantAlfabeto) {
	nfa.fila[i].col[cantColumnas] = crearColumna(i, caracter);
	cantColumnas++;
	nfa.fila[i].cantCols = cantColumnas;
	continue;
	}
	else {
	continue;
	}
	}else if (ingreso >= cantEstados) {
	cout << "                              ";
	cout << "Ese estado no existe, intente con otro" << endl;
	}
	else {
	bool existe = existeEnNFA(ingreso, alfabeto[j], nfa.fila[i]);
	if (existe) {
	cout << "                                ";
	cout << "Ya existe, ingrese otra transicion" << endl;
	}
	else {
	nfa.fila[i].col[cantColumnas] = crearColumna(ingreso, caracter);

	cantColumnas++;
	nfa.fila[i].cantCols = cantColumnas;
	}
	}

	}

	}

	nfa.fila[i].id = i;

	}

	*/
	//Fin almacenar NFA




	//Mostrar NFA
	cout << endl;
	mostrarAutomata(nfa);
	//Fin mostrar NFA

	int estado[40];
	for (int i = 0; i < 40; i++) {
		estado[i] = -1;
		dfa.fila[0].enlace[i].enlace = -1;
	}
	estado[0] = 0;

	dfa.fila[0] = recorrerEpsilon(nfa, estado);

	int ordenarDatos[40];
	for (int i = 0; i < 40; i++) {

		ordenarDatos[i] = -1;
	}
	for (int i = 0; dfa.fila[0].col[i].enlace != -1; i++) {

		ordenarDatos[i] = dfa.fila[0].col[i].enlace;
	}

	sort(ordenarDatos, ordenarDatos + dfa.fila[0].cantCols);
	for (int i = 0; i < 40; i++) {
	}



	dfa.cantFilas = 1;
	dfa.fila[0].id = 0;
	//--------------------------------------------------------------------
	int cantTotEstados = 0;

	for (int i = 0; dfa.fila[i].id != -1; i++) {
		for (int j = 0; j < cantAlfabeto; j++) {
			for (int w = 0; w < 40; w++) {
				estado[w] = -1;
			}
			cout << endl;
			cout << "SE RECORRERA LA FILA " << i << " CON LETRA " << alfabeto[j];

			int *estados = recorrerNFA(nfa, dfa.fila[i], alfabeto[j]);

			for (int b = 0; estados[b] != -1; b++) {
				estado[b] = estados[b];
			}



			cout << endl;
			cout << " { ";
			for (int f = 0; estado[f] != -1; f++) {

				cout << estado[f] << " , ";
			}
			cout << " } " << endl;

			Filas filaTemp = recorrerEpsilon(nfa, estado);
			int p = 0;
			int pruebaIgual = 0;
			int guardarK = 0;
			for (int k = 0; dfa.fila[k].id != -1; k++) {
				int cantColumnas = 0;
				for (int g = 0; dfa.fila[k].col[g].enlace != -1; g++) {
					cantColumnas++;
				}

				int cantColTemp = 0;
				for (int n = 0; filaTemp.col[n].enlace != -1; n++) {
					cantColTemp++;
				}
				cout <<endl<< "Cant Columnas es: " << cantColumnas << endl;
				cout << "Cant Col temp es: " << cantColTemp << endl<<endl;
				p = 0;
				if (cantColTemp == cantColumnas) {

					for (int t = 0; dfa.fila[k].col[t].enlace != -1; t++) {
						if (dfa.fila[k].col[t].enlace == filaTemp.col[t].enlace) {
							cout << dfa.fila[k].col[t].enlace << " es igual a " << filaTemp.col[t].enlace << endl;
							p++;
							cout << "P vale = " << p << endl;
							guardarK = k;
						}
					}
					if (p == cantColumnas) {
						cout << "P = " << p << ", es igual a cantCols = " << cantColumnas << endl;
						pruebaIgual = 1;

						goto salir;
					}
					else {
						pruebaIgual = 0;
					}
				}


			}
		salir:
			if (pruebaIgual == 0) {
				cantTotEstados++;
				dfa.fila[cantTotEstados] = filaTemp;
				dfa.fila[cantTotEstados].id = cantTotEstados;
				if (dfa.fila[i].enlace[0].enlace == -1) {
					dfa.fila[i].enlace[0].enlace = cantTotEstados;
					dfa.fila[i].enlace[0].caracter = alfabeto[j];
				}
				else {
					for (int q = 0; dfa.fila[i].enlace[q].enlace != -1; q++) {
						if (dfa.fila[i].enlace[q + 1].enlace == -1) {
							dfa.fila[i].enlace[q + 1].enlace = cantTotEstados;
							dfa.fila[i].enlace[q + 1].caracter = alfabeto[j];
						}
						q++;
					}
				}


				cout << "SE GUARDO UNA NUEVA FILA, LA FILA " << cantTotEstados;

			}
			else if (pruebaIgual == 1) {
				cout << endl;
				cout << "NO SE GUARDO UNA NUEVA FILA";
				cout << endl;
				if (dfa.fila[i].enlace[0].enlace == -1) {
					dfa.fila[i].enlace[0].enlace = guardarK;
					dfa.fila[i].enlace[0].caracter = alfabeto[j];
				}
				else {
					for (int q = 0; dfa.fila[i].enlace[q].enlace != -1; q++) {
						if (dfa.fila[i].enlace[q + 1].enlace == -1) {
							dfa.fila[i].enlace[q + 1].enlace = guardarK;
							dfa.fila[i].enlace[q + 1].caracter = alfabeto[j];
						}
						q++;
					}
				}
			}

		}
	}



	//-------------------------------------------------------------------------
	ofstream outfile;
	outfile.open("AFD.txt");


	string estadosDFA[40] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S" };
	int estadosFinales[40];
	for (int i = 0; i < 40; i++) {
		estadosFinales[i] = -1;
	}
	int contarEstadosFinales = 0;
	for (int i = 0; dfa.fila[i].id != -1; i++) {
		/*cout << "ESTADO ";
		outfile << "F(";
		for (int h = 0; dfa.fila[i].col[h].enlace != -1; h++) {
			if (dfa.fila[i].col[h].enlace == cantEstados - 1) {
				estadosFinales[contarEstadosFinales] = i;
				contarEstadosFinales++;
				cout << "FINAL ";
				outfile << "FINAL ";
			}
		}
		cout << estadosDFA[i] << ": { ";
		outfile << estadosDFA[i] << ": { ";

		for (int j = 0; dfa.fila[i].col[j].enlace != -1; j++) {
			cout << dfa.fila[i].col[j].enlace << " , ";
			outfile << dfa.fila[i].col[j].enlace << " , ";
		}
		cout << " } " << endl;


		outfile << " } " << endl;
		cout << " con enlaces hacia: " << endl;
		outfile << " con enlaces hacia: " << endl;
		*/
		for (int k = 0; k<cantAlfabeto; k++) {
			if (!dfa.fila[i].enlace[k].caracter.empty()) {
			cout << "ESTADO ";
			outfile << "F";
			for (int h = 0; dfa.fila[i].col[h].enlace != -1; h++) {
				if (dfa.fila[i].col[h].enlace == cantEstados - 1) {
					estadosFinales[contarEstadosFinales] = i;
					contarEstadosFinales++;
					cout << "FINAL ";
					outfile << "F";
				}
			}
			outfile << "(";
			cout << estadosDFA[i] << " , ";
			outfile << estadosDFA[i] << ",";
			
				cout << dfa.fila[i].enlace[k].caracter << ") = {" << estadosDFA[dfa.fila[i].enlace[k].enlace] << "} " << endl;
				outfile << dfa.fila[i].enlace[k].caracter << ") = {" << estadosDFA[dfa.fila[i].enlace[k].enlace] << "} " << endl;
			}
			}
			
	}
	outfile.close();
	///////////////////////////////////////////////////////////////////////////////////
	cout << endl << endl << endl;
	
	system("cls");

	string cadenaprueba;
	do {
		
		cout << endl << endl;
		cout << "Ingrese una cadena de prueba (-1 para salir)" << endl;
		if (cadenaprueba == "-1") {
			break;
		}
		cin >> cadenaprueba;

		cout << endl;
		bool aceptable = false;
		for (int i = 0; i < cadenaprueba.size(); i++) {
			aceptable = false;
			for (int j = 0; j < cantAlfabeto; j++) {

				if (cadenaprueba[i] == alfabeto[j][0]) {
					aceptable = true;
				}

			}
			if (!aceptable) {
				cout << "Caracter invalido" << endl;
				break;
			}

		}
		int terminaEnAceptacion = 0;
		if (aceptable) {

			int recorridoCadena[40];
			for (int i = 0; i < 40; i++) {
				recorridoCadena[i] = -1;
			}
			recorridoCadena[0] = 0;
			int contarRecorridoCadena = 1;

			for (int i = 0; recorridoCadena[i] != -1; i++) {
				for (int k = 0; dfa.fila[recorridoCadena[i]].enlace[k].enlace != -1; k++) {
					if (!dfa.fila[recorridoCadena[i]].enlace[k].caracter.empty()) {
						if (cadenaprueba[i] == dfa.fila[recorridoCadena[i]].enlace[k].caracter[0]) {
							recorridoCadena[contarRecorridoCadena] = dfa.fila[recorridoCadena[i]].enlace[k].enlace;

							if (i == cadenaprueba.size() - 1) {
								for (int h = 0; estadosFinales[h] != -1; h++) {
									if (recorridoCadena[contarRecorridoCadena] == estadosFinales[h]) {
										terminaEnAceptacion = 1;
									}
								}
							}
							else {

							}


							contarRecorridoCadena++;
						}

					}
				}

				if (terminaEnAceptacion == 1) {
					cout << endl;
					cout << "La cadena ingresada SI esta en un estado de aceptacion" << endl << endl << endl;
				}
				else {
					cout << endl;
					cout << "La cadena ingresada NO esta en un estado de aceptacion" << endl << endl << endl;
				}

			}
		}
		else {
			cout << endl;
			cout << "La cadena ingresada NO esta en un estado de aceptacion" << endl << endl << endl;
		}
		system("pause");
		system("cls");
	} while (cadenaprueba != "-1");
	cout << endl;
	system("pause");


	return 0;
}

bool existeEnNFA(int ingreso, string caracter, Filas fila) {
	int i = 0;
	if (fila.col[0].enlace == -1) {
		return false;
	}
	else {
		while (fila.col[i].enlace != -1) {
			//cout<<"Entrada " << i << endl;
			if (ingreso == fila.col[i].enlace && caracter == fila.col[i].caracter) {
				//cout << "El ingreso " << ingreso << " con caracter " << caracter << endl;
				//cout << " Es igual a " << fila.col[i].enlace << " con caracter " << fila.col[i].caracter << " ingresado anteriormente" << endl;
				return true;
			}
			i++;
		}

		return false;
	}
}

Columnas crearColumna(int ingreso, string caracter) {
	Filas fila;
	fila.col[0].caracter = caracter;
	fila.col[0].enlace = ingreso;
	return fila.col[0];
}



void mostrarAutomata(AUT nfa) {

	for (int i = 0; i < nfa.cantFilas; i++) {
		cout << "                                     ";
		cout << "   ";

		for (int j = 0; j < nfa.fila[i].cantCols; j++) {

			cout << nfa.fila[i].col[j].caracter << "  ";


		}

		cout << endl;
		cout << "                                     ";
		cout << " " << i << " ";
		for (int j = 0; j < nfa.fila[i].cantCols; j++) {

			cout << nfa.fila[i].col[j].enlace << "  ";


		}

		cout << endl << endl;

	}

}


Filas recorrerEpsilon(AUT nfa, int estados[]) {
	Filas fila;
	for (int i = 0; i < 40; i++) {
		fila.col[i].enlace = -1;
		fila.col[i].caracter = "-1";
	}
	int h = 0;
	int cantEstados = 0;
	for (int k = 0; estados[k] != -1; k++) {
		cantEstados++;
		int estadoActual = estados[k];
		for (int i = 0; i < nfa.fila[estadoActual].cantCols; i++) {
			if (nfa.fila[estadoActual].col[i].caracter == "$") {
				for (int j = 0; estados[j] != -1; j++) {
					if (estados[j + 1] == -1) {
						int p = 1;
						for (int h = 0; estados[h] != -1 && p != 0; h++) {
							if (estados[h] == nfa.fila[estadoActual].col[i].enlace) {
								p = 0;
							}

						}
						if (p == 1) {
							estados[j + 1] = nfa.fila[estadoActual].col[i].enlace;
							cout << "Estado " << estados[j + 1] << " agregado" << endl;
							h++;
							j++;
						}
					}
				}
			}
		}
		cout <<  endl;
	}


	fila.cantCols = h;
	cout << "Datos de la fila: ";
	cout << "{";
	int cantColumnas = 0;
	for (int i = 0; estados[i] != -1; i++) {
		cantColumnas++;
		cout << estados[i] << ", ";
		fila.cantCols = cantColumnas;
	}


	sort(estados, estados + cantColumnas);
	cout << "despues de sort" << endl;
	for (int i = 0; estados[i] != -1; i++) {
		fila.col[i].enlace = estados[i];
		cout << estados[i] << " ";
		fila.enlace[i].enlace = -1;
	}

	cout << "}";
	return fila;
}

int* recorrerNFA(AUT nfa, Filas fila, string caracter) {

	int estadosTemp[40];
	int estados[40];

	for (int i = 0; i < 40; i++) {
		estadosTemp[i] = -1;
		estados[i] = -1;
	}

	for (int i = 0; fila.col[i].enlace != -1; i++) {
		estadosTemp[i] = fila.col[i].enlace;
	}

	int h = 0;
	int cantEstados = 0;
	for (int k = 0; estadosTemp[k] != -1; k++) {
		cantEstados++;
		int estadoActual = estadosTemp[k];
		for (int i = 0; i < nfa.fila[estadoActual].cantCols; i++) {
			if (nfa.fila[estadoActual].col[i].caracter == caracter) {
				if (estados[0] == -1) {
					estados[0] = nfa.fila[estadoActual].col[i].enlace;
				}
				else {
					for (int j = 0; estados[j] != -1; j++) {
						if (estados[j + 1] == -1) {

							int p = 1;
							for (int h = 0; estados[h] != -1 && p != 0; h++) {
								if (estados[h] == nfa.fila[estadoActual].col[i].enlace) {
									p = 0;
								}

							}
							if (p == 1) {
								estados[j + 1] = nfa.fila[estadoActual].col[i].enlace;
								cout << "Estado " << estados[j + 1] << " agregado" << endl;
								h++;
								j++;
							}
						}
					}
				}

			}
		}
	}

	fila.id = 0;
	fila.cantCols = h;
	cout << "Datos de la fila: ";
	cout << "{";
	for (int i = 0; estados[i] != -1; i++) {
		cout << estados[i] << ", ";
	}
	cout << "}";
	return estados;
}

