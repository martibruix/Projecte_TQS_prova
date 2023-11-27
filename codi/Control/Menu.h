#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "../View/InputMenu.h"
#include "../View/PrinterMenu.h"
#include "../View/Ranking.h"
#include "Game.h"

using namespace std;

class Menu
{
public:
	// Constructor estàndar per la classe Menu
    Menu() {
        inputMenu = new InputMenu();
    }
    // Constructor de la classe Menu utilitzat quan es vol fer un test amb mocks
    Menu(InputMenu& input, vector<Game*> mocksGame, string path) {
        inputMenu = &input;
        mocks = mocksGame;
        pathRanking = path;
    }
    // Funció que implementa el bucle principal del menu
    void iniciar() {
        bool sortir = false;
        
        // Bucle principal que segueix fins que l'usuari indiqui que vol sortir
        while (!sortir) {
            // Print del menu principal i demanar input al jugador
            printer.netejaPantalla();
            printer.menuInici();
            int input = inputMenu->getInput();

            // S'executa una acció segons el que hagi indicat el jugador
            if (input == JUGAR) { // Cas de jugar una partida
                // Demanar dificultat i nom al jugador
                printer.netejaPantalla();
                printer.nom();
                string nom = inputMenu->getNom();
                printer.netejaPantalla();
                printer.dificutat();
                int dificultat = inputMenu->getDificultat();
                while (dificultat == -1) {
                    // Si s'introdueix una dificultat invàlida la torna a demanar
                    printer.netejaPantalla();
                    printer.dificutat();
                    dificultat = inputMenu->getDificultat();
                }
                
                // Crear un objecte de Game
                Game* partida;
                if (mocks.size() == 0) // Cas estàndar
                    partida = new Game(dificultat, nom);
                else { // Cas en el que s'està fent un test i es vol utilitzar un mock de Game
                    partida = mocks[i_mock];
                    i_mock++;
                }
                
                // S'inicialitza el tauler i es juga la partida
                partida->initTauler();
                int resultat = partida->play();
                
                // Si la partida no ha sigut abandonada, es guarda el resultat
                if (resultat != -1)
                    guardarPuntuacio(nom, resultat, partida->getPuntuacio(), dificultat, pathRanking);
            }
            else if (input == RANKING) { // Cas de veure el ranking
                // Es llegeix el ranking del fitxer
                vector<vector<string>> puntuacions = llegirRanking(pathRanking);
                
                // Es mostra per pantalla i s'espera a que el jugador premi Enter
                printer.netejaPantalla();
                ranking.mostraRanking(puntuacions);
                inputMenu->espera();
            }
            else if (input == SORTIR) { // Cas sortir del menu
                // Es posa la variable sortir a true per acabar el bucle
                sortir = true;
            }
        }
    }

    // Funció que guarda el nom del jugador, el resultat de la partida, la puntuació obtinguda i la
    // dificultat al fitxer indicat per path.
    void guardarPuntuacio(string nom, int resultat, int puntuacio, int dificultat, string path) {
        // Obre el fitxer
        ofstream file(path, ios::app);
        if (file.is_open()) {
            // S'afegeix el contingut en una línia nova i deixant un espai entre camps
            file << nom << " " << resultat << " " << puntuacio << " " << dificultat << "\n";
            file.close();
        }
    }
    
    // Funció que llegeix el contingut del fitxer indicat per path i el retorna en una matriu de strings.
    vector<vector<string>> llegirRanking(string path) {
        // Obre el fitxer
        ifstream file(path);
        // Matriu on es guarda el resultat
        vector<vector<string>> ranking;

        if (file.is_open()) {
            // Vector on s'afegirà cada línia del fitxer
            vector<string> v_aux;
            int i = 0;
            // Es llegeix mentre no s'arribi al final del fitxer
            while (!file.eof()) {
                // Llegeix una paraula i l'afegeix al vector
                string aux;
                file >> aux;
                v_aux.push_back(aux);

                if (i == 3) { // Si s'han llegit quatre paraules, s'ha llegit una línia sencera
                    // S'afegeix la línia a la matriu ranking i es reinicia v_aux i el contador
                    ranking.push_back(v_aux);
                    i = 0;
                    v_aux.clear();
                }
                else {
                    i++;
                }
            }
            file.close();
        }

        // Retorna la matriu amb totes les línies del fitxer
        return ranking;
    }
private:
    PrinterMenu printer; // Classe per imprimir per pantalla
    InputMenu* inputMenu; // Classe per rebre inputs
    Ranking ranking; // Classe per imprimir el ranking
    const int JUGAR = 1, RANKING = 2, SORTIR = 0, ERROR = -1;
    string pathRanking = "../files/Ranking.txt"; // Indica el fitxer on guardar el ranking
    
    // Utilizat només per tests
    vector<Game*> mocks; // Vector on es guarden les partides mockejades que es volen jugar
    int i_mock = 0; // Index que indica quin mock del vector mocks és el següent a utilitzar
};
