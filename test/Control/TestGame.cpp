#include "CppUnitTest.h"
#include "../../codi/Control/Game.h"	
#include "MockInputGame.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestGame)
{
public:
    //Aquest test serveix per comprovar que el constructor de Game inicialitzi 
    //correctament els seus atributs i s'inicialitzi la matriu amb la mida adecuada
	TEST_METHOD(test_game)
	{
        string nom = "prova_1";

        //En aquest primer cas es comprova que s'inicialitzi correctament amb la 
        //dificultat FACIL on la matriu es un 6x6 i 7 mines
        Game joc(1, nom);
		Assert::AreEqual(joc.getPuntuacio(), 0);
        Assert::AreEqual(joc.getDificultat(), 1);
        Assert::AreEqual(joc.getNom(), nom);
        Board *tauler = joc.getTauler();
        Assert::AreEqual(tauler->getAltura(), 6);
        Assert::AreEqual(tauler->getAmplada(), 6);
        Assert::AreEqual(tauler->getMines(), 7);

        //En aquest segon cas es comprova que s'inicialitzi correctament amb la 
        //dificultat MITJA on la matriu es un 8x8 i 10 mines
        Game joc2(2, nom);
		Assert::AreEqual(joc2.getPuntuacio(), 0);
        Assert::AreEqual(joc2.getDificultat(), 2);
        Assert::AreEqual(joc2.getNom(), nom);
        tauler = joc2.getTauler();
        Assert::AreEqual(tauler->getAltura(), 8);
        Assert::AreEqual(tauler->getAmplada(), 8);
        Assert::AreEqual(tauler->getMines(), 10);

        //En aquest tercer cas es comprova que s'inicialitzi correctament amb la 
        //dificultat DIFICIL on la matriu es un 15x15 i 35 mines
        Game joc3(3, nom);
		Assert::AreEqual(joc3.getPuntuacio(), 0);
        Assert::AreEqual(joc3.getDificultat(), 3);
        Assert::AreEqual(joc3.getNom(), nom);
        tauler = joc3.getTauler();
        Assert::AreEqual(tauler->getAltura(), 15);
        Assert::AreEqual(tauler->getAmplada(), 15);
        Assert::AreEqual(tauler->getMines(), 35);

        //En aquest últim cas es comprova que introduint un nombre incorrecte de dificultat
        //s'inicialitzi una matriu es un 6x6 i 7 mines amb la dificultat en FACIL
        Game joc4(4, nom);
		Assert::AreEqual(joc4.getPuntuacio(), 0);
        Assert::AreEqual(joc4.getDificultat(), 1);
        Assert::AreEqual(joc4.getNom(), nom);
        tauler = joc4.getTauler();
        Assert::AreEqual(tauler->getAltura(), 6);
        Assert::AreEqual(tauler->getAmplada(), 6);
        Assert::AreEqual(tauler->getMines(), 7);
	}

    //Aquest test ens permet testejar el caràcter correcte que haurà de 
    //retornar la nostra funció a partir de les carecterístiques en aquell moment 
    //la casella. L'ordre de les variables de la funció es: mina, oberta, flags, subjacents
    TEST_METHOD(test_getCharMatriu)
    {
        Game partida(1, "nom");

        //Test per veure si retorna una F quan la casella té Flag
        char a = partida.getCharMatriu(false, false, true, 2);
        Assert::AreEqual('F', a);

        //Test per veure si retorna un 0 quan la casella es oberta
        a = partida.getCharMatriu(false, true, false, 0);
        Assert::AreEqual('0', a);
        
        //Test per veure si retorna una E (Error) quan es una casella amb mina pero té
        //un nombre diferente de la varaible de subjacents
        a = partida.getCharMatriu(true, false, false, 2);
        Assert::AreEqual('E', a);

        //Test per veure si retorna una E (Error) quan es una casella amb mina, oberta, amb flag i
        //un nombre de subjacents invalid
        a = partida.getCharMatriu(true, true, true, -1);
        Assert::AreEqual('E', a);

        //Test per veure si retorna una E (Error) quan en una casella obtenim un nombre
        //invalid de subjacents
        a = partida.getCharMatriu(false, false, false, -1);
        Assert::AreEqual('E', a);
        
        //Test per veure si retorna una X quan es una casella que s'ha obert i es mina
        a = partida.getCharMatriu(true, true, false, 0);
        Assert::AreEqual('X', a);
        
        //Test per veure si retorna una F quan es una casella amb mina pero es marcada amb una Flag
        a = partida.getCharMatriu(true, false, true, 0);
        Assert::AreEqual('F', a);
        
        //Test per veure si retorna una E (Error) quan es una casella amb mina que ha estat oberta, 
        //però que te un nombre invàlid de subjacents
        a = partida.getCharMatriu(true, true, false, 2);
        Assert::AreEqual('E', a);
    }

    //Aquest test comprova que, a partir d'una matriu formada per caselles amb diferents estats retorna la matriu que
    //conté tots els caràcters que s'hauran d'imprimir per la terminal i aquest són correctes
    TEST_METHOD(test_printMatriu)
    {
        //Creació de la matriu, on cada Cell conté l'estat de cada casella, si es mina, esta oberta,
        //si té flag i el nombre de subjacents
        vector<vector<Cell>> matriu = {
            {Cell(1, 0, 0, 0), Cell(0, 0, 1, 1), Cell(0, 1, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
            {Cell(0, 1, 0, 3), Cell(0, 0, 0, 3), Cell(0, 1, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
            {Cell(1, 1, 0, 0), Cell(1, 0, 1, 0), Cell(0, 0, 1, 2), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
            {Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
            {Cell(1, 0, 0, 0), Cell(0, 0, 0, 4), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
            {Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };

        Game partida(1, "nom");
        Board* tauler = partida.getTauler();
        tauler->setMatriu(matriu);
        //Crida de la funció printMatriu per crear la matriu dels caràcters
        vector<vector<char>> matriu_partida = partida.printMatriu();

        //Creació de la matriu esperada manualment 
        vector<vector<char>> matriu_esperada = {
            {' ', 'F', '0', ' ', ' ', ' '},
            {'3', ' ', '1', ' ', ' ', ' '},
            {'X', 'F', 'F', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '}
        };

        //Comprovem que totes dues matrius són iguals per tant, els caràcters són correctes
        for (int i=0; i < matriu_esperada.size(); i++){
            for (int j=0; j < matriu_esperada[i].size(); j++){
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j], matriu_partida[i][j], message.c_str());
            }
        }
    }

    //Aquest test es comproven el funcionament del joc a través d'una serie de partides amb diferents seqüències
    //d'instruccions
    TEST_METHOD(test_play)
    {
        //Creació de la matriu inicial, utilitzada com a base per fer les instruccions corresponents
        vector<vector<Cell>> matriu = {
            {Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };

        //Aquesta primera prova es la d'obrir una casella amb mina, en conseqüència perdre la partida
        vector<vector<int>> instruccions = { {0, 0, 0} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput(instruccions);
        Game partida(1, "nom", mockInput);
        Board* tauler = partida.getTauler();
        tauler->setMatriu(matriu);

        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        int result = partida.play();
        //Es comprova que efectivament s'ha perdut la partida
        Assert::AreEqual(0, result);
        //Es comprova que la puntuació es nula
        int puntuacio = partida.getPuntuacio();
        Assert::AreEqual(0, puntuacio);
        //Creació manual de la matriu resultant despres d'executar les intruccions
        vector<vector<Cell>> matriu_esperada = {
            {Cell(1, 1, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };
        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        vector<vector<Cell>> matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }

        //Aquesta segona prova es la d'obrir tres caselles i posteriorment abandonar la partida
        instruccions = { {0, 1, 0}, {0, 1, 1}, {0, 1, 2}, {3} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput2(instruccions);
        Game partida2(1, "nom", mockInput2);
        tauler = partida2.getTauler();
        tauler->setMatriu(matriu);
        
        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        result = partida2.play();
        //Es comprova que efectivament s'ha abandonat la partida
        Assert::AreEqual(-1, result);
        puntuacio = partida2.getPuntuacio();
        //Es comprova que la puntuació de la partida avnas d'abandonar es 30 (10 per cada casella oberta)
        Assert::AreEqual(30, puntuacio);
        
        //Creació manual de la matriu resultant despres d'executar les intruccions
        matriu_esperada = {
            {Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 1, 0, 2), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };

        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }
        
        //Aquesta tercera prova es la d'obrir totes les caselles sense mina, es a dir guanyar la partida
        instruccions = { {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 1, 0}, {0, 1, 1}, {0, 1, 2},
            {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 2, 0}, {0, 2, 2}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5},
            {0, 3, 0}, {0, 3, 2}, {0, 3, 4}, {0, 4, 0}, {0, 4, 1}, {0, 4, 2}, {0, 4, 3}, {0, 4, 4},
            {0, 4, 5}, {0, 5, 0}, {0, 5, 1}, {0, 5, 3}, {0, 5, 4}, {0, 5, 5} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput3(instruccions);
        Game partida3(1, "nom", mockInput3);
        tauler = partida3.getTauler();
        tauler->setMatriu(matriu);
        
        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        result = partida3.play();
        //Es comprova que efectivament s'ha guanyat la partida
        Assert::AreEqual(1, result);
        puntuacio = partida3.getPuntuacio();
        //Es comprova que obtenim la puntuació correcte
        Assert::AreEqual(290, puntuacio);
        
        //Creació manual de la matriu resultant despres d'executar les intruccions
        matriu_esperada = {
            {Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 1, 0, 2), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1)},
            {Cell(0, 1, 0, 2), Cell(1, 0, 0, 0), Cell(0, 1, 0, 3), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1)},
            {Cell(0, 1, 0, 2), Cell(1, 0, 0, 0), Cell(0, 1, 0, 3), Cell(1, 0, 0, 0), Cell(0, 1, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 3), Cell(0, 1, 0, 2), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1)},
            {Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0)}
        };
        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }

        //Aquest test preten obrir dos caselles (una amb recursivitat i l'altre sense) i posteriorment apretar una mina
        instruccions = { {0, 0, 3}, {0, 5, 3}, {0, 3, 1} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput4(instruccions);
        Game partida4(1, "nom", mockInput4);
        tauler = partida4.getTauler();
        tauler->setMatriu(matriu);
        
        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        result = partida4.play();
        //Es comprova que efectivament s'ha perdut la partida
        Assert::AreEqual(0, result);
        puntuacio = partida4.getPuntuacio();
        //Es comprova que obtenim la puntuació correcte
        Assert::AreEqual(120, puntuacio);
        //Creació manual de la matriu resultant despres d'executar les intruccions
        matriu_esperada = {
            {Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 2), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 1, 0, 3), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 1, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };
        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }

        //Aquest test pretén posar una flag, tornar a posar flag a la mateixa posicio, provar d'obrir la casella on hi ha 
        //flag, posar totes les flags, veure que no es poden posar més, treure flag a posicio incorrecta,
        // treure 2 flags a posicions correctes i abnadonar
        instruccions = { {1, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 1}, {1, 0, 2}, {1, 0, 3}, {1, 0, 4},
            {1, 0, 5}, {1, 1, 0}, {1, 1, 1}, {2, 2, 0}, {2, 0, 0}, {2, 0, 1}, {3} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput5(instruccions);
        Game partida5(1, "nom", mockInput5);
        tauler = partida5.getTauler();
        tauler->setMatriu(matriu);
        
        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        result = partida5.play();
        //Es comprova que efectivament s'ha abandonat la partida
        Assert::AreEqual(-1, result);
        puntuacio = partida5.getPuntuacio();
        //Es comprova que obtenim la puntuació correcte
        Assert::AreEqual(0, puntuacio);
        //Creació manual de la matriu resultant despres d'executar les intruccions
        matriu_esperada = {
            {Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 1, 0), Cell(0, 0, 1, 0), Cell(0, 0, 1, 1), Cell(1, 0, 1, 0)},
            {Cell(0, 0, 1, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };
        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }

        //Aquest test preten rebre una instruccio incorrecta, obrir una casella i abandonar la partida
        instruccions = { {-1}, {0, 0, 1}, {3} };
        //S'utilitza la classe MockInputGame per simular les instruccions
        MockInputGame mockInput6(instruccions);
        Game partida6(1, "nom", mockInput6);
        tauler = partida6.getTauler();
        tauler->setMatriu(matriu);
        
        //Es crida la funció play per tal de que realitzi les intruccions corresponents de la partida
        result = partida6.play();
        //Es comprova que efectivament s'ha abandonat la partida
        Assert::AreEqual(-1, result);
        puntuacio = partida6.getPuntuacio();
        //Es comprova que obtenim la puntuació correcte
        Assert::AreEqual(10, puntuacio);
        //Creació manual de la matriu resultant despres d'executar les intruccions
        matriu_esperada = {
            {Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
            {Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
            {Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
        };
        //Es comprova que s'han realitzat correctament les instruccions i han cambiat l'estat de les caselles
        matriu_board = tauler->getMatriu();
        for (int i = 0; i < matriu_esperada.size(); i++) {
            for (int j = 0; j < matriu_esperada[i].size(); j++) {
                wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
                Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
                Assert::AreEqual(matriu_esperada[i][j].teFlag(), matriu_board[i][j].teFlag(), message.c_str());
            }
        }
    }
};