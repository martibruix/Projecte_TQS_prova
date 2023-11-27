#pragma once
#include "../Model/Board.h"
#include <string>
#include "../View/InputGame.h"
#include "../View/Printer.h"
using namespace std;

class Game
{
public:
    // Constructor est�ndar per la classe Game
    Game(int dif, string name) {
        dificultat = dif;
        nom = name;
        puntuacio = 0;

        // Creem el tauler amb la dimensi� i les mines segons la dificultat
        if (dif == FACIL) {
            tauler = new Board(6, 6, 7);
        }
        else if (dif == MITJA) {
            tauler = new Board(8, 8, 10);
        }
        else if (dif == DIFICIL) {
            tauler = new Board(15, 15, 35);
        }
        else {
            // Si s'ha introduit un valor incorrecte de dificultat, s'estableix com a f�cil
            tauler = new Board(6, 6, 7);
            dificultat = FACIL;
        }
        inputGame = new InputGame();
    }
    // Constructor utilitzat quan es vol fer un test amb un mock de InputGame
    Game(int dif, string name, InputGame& input) {
        dificultat = dif;
        nom = name;
        puntuacio=0;
        // Creem el tauler amb la dimensi� i les mines segons la dificultat
        if (dif == FACIL){
            tauler = new Board(6, 6, 7);
        }
        else if (dif == MITJA){
            tauler = new Board(8, 8, 10);
        }
        else if (dif == DIFICIL){
            tauler = new Board(15, 15, 35);
        }
        else {
            // Si s'ha introduit un valor incorrecte de dificultat, s'estableix com a f�cil
            tauler = new Board(6, 6, 7);
            dificultat = FACIL;
        }
        // Assignem el mock
        inputGame = &input;
    }
    // Funci� per crear les mines del tauler aleat�riament i calcular el nombre de subjacents.
    virtual void initTauler() {
        tauler->crearMines();
        tauler->calculSubjacents();
    }
    // Funci� que implementa el bucle de la partida.
    int play(){
        bool mort = false; // Indica si s'ha perdut
        bool victoria = false; // Indica si s'ha guanyat
        bool sortir = false; // Indica si es vol sortir de la partida
        
        do {
            // Fer print del tauler i rebre una instrucci�
            printer.netejaPantalla();
            printer.tauler(printMatriu());
            printer.missatgePartida(tauler->getFlags(), puntuacio);
            vector<int> instruccio = inputGame->getInstruccio();
            
            // Segons la instrucci� es duu a terme unes accions
            if (instruccio[0] == OPEN) { // Cas d'obrir una casella
                // S'obre la casella
                int punts = tauler->obrirCasella(instruccio[1], instruccio[2]);
                if (punts == -1) {
                    // Si retorna -1 s'ha obert una mina
                    mort = true;
                }
                else if (punts > -1) {
                    // S'ha obert una casella buida i s'actualitza la puntuaci�
                    puntuacio += punts;
                    if (tauler->victoria()) // Es comprova si s'ha guanyat
                        victoria = true;
                }
            }
            else if (instruccio[0] == POSAR_FLAG) { // Cas de posar una flag
                tauler->posarFlags(instruccio[1], instruccio[2]);
            }
            else if (instruccio[0] == TREURE_FLAG) { // Cas de treure una flag
                tauler->treureFlags(instruccio[1], instruccio[2]);
            }
            else if (instruccio[0] == EXIT) { // Cas de sortir de la partida
                // Es posa sortir a true per acabar amb el bucle
                sortir = true;
            }
        // El bucle s'acaba un cop es perd, es guanya o s'indica que es vol sortir
        } while (!mort && !victoria && !sortir);

        // Print del tauler i del missatge final
        printer.netejaPantalla();
        printer.tauler(printMatriu());
        printer.finalPartida(sortir, victoria, puntuacio);
        inputGame->espera();

        // Valor de retorn segons si s'ha guanyat, s'ha perdut o s'ha abandonat la partida
        if (victoria)
            return 1;
        if (mort)
            return 0;
        return -1;
    }
    // Funci� que segons els atributs d'una casella concreta (mina, oberta, flag i subjacents) retorna el
    // car�cter que s'haur� d'imprimir per pantalla per representar aquesta casella.
    char getCharMatriu(bool mina, bool oberta, bool flag, int subjacents) {
        if (subjacents < 0 || subjacents > 8)
            // Si el nombre de subjacents �s inv�lid retorna car�cter d'error
            return 'E';
        if (oberta && flag)
            // Si est� oberta i t� flag a la vegada retorna car�cter d'error
            return 'E';
        if (mina && subjacents > 0)
            // Si t� mina i el nombre de subjacents no �s 0 retorna car�cter d'error
            return 'E';
        if (flag)
            // Cas d'una casella amb flag
            return 'F';
        else if (!oberta)
            // Cas d'una casella no oberta i sense flag
            return ' ';
        else if (mina)
            // Cas d'una mina oberta
            return 'X';
        else {
            // Cas d'una casella oberta sense mina, es retorna el n�mero de subjacents com a string
            string aux = to_string(subjacents);
            return *aux.c_str();
        }
    }
    // Funci� que retorna una matriu amb tots els car�cters que s'han d'imprimir per pantalla per representar
    // el tauler.
    vector<vector<char>> printMatriu(){
        // Es crea la matriu de car�cters a la mida necess�ria
        vector<vector<char>> matriuFinal;
        matriuFinal.resize(tauler->getAltura());
        for (int i = 0; i < matriuFinal.size(); i++)
            matriuFinal[i].resize(tauler->getAmplada());

        vector<vector<Cell>> matriuBoard = tauler->getMatriu();
        // Per cada posici� de la matriu crida a la funci� getCharMatriu per obtenir el car�cter
        for (int i = 0; i < matriuFinal.size(); i++) {
            for (int j = 0; j < matriuFinal[i].size(); j++) {
                matriuFinal[i][j] = getCharMatriu(matriuBoard[i][j].esMina(), matriuBoard[i][j].estaOberta(), matriuBoard[i][j].teFlag(), matriuBoard[i][j].getSubjacents());
            }
        }

        // Retorna la matriu amb tots els car�cters
        return matriuFinal;
    }
    // Funci� per obtenir el tauler
    Board* getTauler() { return tauler; }
    // Funci� per obtenir la puntuaci�
    int getPuntuacio() { return puntuacio; }
    // Funci� per obtenir la dificultat
    int getDificultat() { return dificultat; }
    // Funci� per obtenir el nom
    string getNom() { return nom; }
private:
    Board *tauler; // Tauler de la partida
    int puntuacio; // Puntuaci� que es porta en cada moment
    int dificultat; // Dificultat de la partida (1=f�cil, 2=mitja, 3=dif�cil)
    string nom; // Nom del jugador
    const int FACIL = 1, MITJA = 2, DIFICIL = 3;
    const int OPEN = 0, POSAR_FLAG = 1, TREURE_FLAG = 2, EXIT = 3, ERROR = -1;
    InputGame* inputGame; // Classe per rebre inputs
    Printer printer; // Classe per imprimir per pantalla
};

