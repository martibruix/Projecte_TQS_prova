#pragma once
#include <string>
#include <iostream>
using namespace std;

class InputMenu
{
public:
	InputMenu() {};
	//Ens permet controlar els inputs introduits en el menu principal, descartant totes les opcions que no siguin 
	//les de JUGAR=1, RANKING=2
	virtual int getInput() {
		int input;
		
		if (cin >> input) {
			if (input < 0 || input > 2)
				input = -1;
		}
		else {
			cin.clear();
			input = -1;
		}
		//Instrucció que ens permet descartar l'entrada no desitjada de comandes de l'usuari
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return input;
	}

	//Ens permet fer el input en el menú d'introduir el nom del jugador
	virtual string getNom() {
		string nom;
		cin >> nom;
		//Instrucció que ens permet descartar l'entrada no desitjada de comandes de l'usuari
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return nom;
	}

	//Ens permet fer el input de l'elecció de la dificultat de la partida. Si s'introdueix un valor invàlid
	//es retornarà -1
	virtual int getDificultat() {
		int dificultat;
		if (cin >> dificultat) {
			if (dificultat < 1 || dificultat > 3)
				dificultat = -1;
		}
		else {
			cin.clear();
			dificultat = -1;
		}
		//Instrucció que ens permet descartar l'entrada no desitjada de comandes de l'usuari
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return dificultat;
	}

	//Ens permet que el programa s'aturi fins que el jugador no premi la tecla enter
	virtual void espera() {
		cout << endl << endl << "Prem Enter per continuar" << endl;
		char a;
		cin.get(a);
	}
};