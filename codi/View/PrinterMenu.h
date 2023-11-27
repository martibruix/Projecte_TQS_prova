#pragma once
#include <vector>
#include <iostream>
using namespace std;

class PrinterMenu
{
public:
    //Ens permet veure la vista del menu principal, per poder jugar, veure el ranking o sortir
    void menuInici() {
        cout << "==========" << endl;
        cout << "BUSCAMINES" << endl;
        cout << "==========" << endl;
        cout << endl;
        cout << "1- Jugar" << endl;
        cout << "2- Ranking" << endl;
        cout << endl;
        cout << "0- Sortir" << endl;
        cout << endl;
        cout << "Selecciona una opcio: " << endl;
    }
    
    //Ens permet veure la vista del menú d'escollir la dificultat de la partida
    void dificutat() {
        cout << "==========" << endl;
        cout << "DIFICULTAT" << endl;
        cout << "==========" << endl;
        cout << endl;
        cout << "1- Facil" << endl;
        cout << "2- Mitja" << endl;
        cout << "3- Dificil" << endl;
        cout << endl;
        cout << "Selecciona una opcio: " << endl;
    }

    //Ens permet veure la vista del menu per introduir el nom del jugador en la partida
    void nom() {
        cout << "=====================" << endl;
        cout << "INTRODUEIX EL TEU NOM" << endl;
        cout << "=====================" << endl;
    }

    //Ens permet natejar la pantalla per cada transicció entre menus
    void netejaPantalla() {
        system("cls");
    }
};