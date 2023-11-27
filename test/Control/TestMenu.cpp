#include "CppUnitTest.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include "../../codi/Control/Menu.h"
#include "MockGame.h"
#include "MockInputGame.h"
#include "MockInputMenu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestMenu)
{
public:
	//Aquest test ens permet comprovar el correcte funcionament del menú pricipal
	TEST_METHOD(test_iniciar)
	{
		//Creem una matriu per defecte
		vector<vector<Cell>> matriu = {
			{Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
		};

		//Creem les instruccion per jugar una partida i guanyar-la
		vector<vector<int>> instruccionsVictoria = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 1, 0},
			{0, 1, 1}, {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 2, 0}, {0, 2, 2}, {0, 2, 3},
			{0, 2, 4}, {0, 2, 5}, {0, 3, 0}, {0, 3, 2}, {0, 3, 4}, {0, 4, 0}, {0, 4, 1}, {0, 4, 2},
			{0, 4, 3}, {0, 4, 4}, {0, 4, 5}, {0, 5, 0}, {0, 5, 1}, {0, 5, 3}, {0, 5, 4}, {0, 5, 5}};
		//Utilitzem la classe MockInputGame per poder simular l'us d'instruccions que es reben durant la partida
		MockInputGame mockInputGameVictoria(instruccionsVictoria);
		//Utilitzem la classe MockGame per simular la realització del joc i la matriu
		MockGame mockPartidaVictoria(1, "nom", mockInputGameVictoria, matriu);

		//Creem les instruccions per jugar i perdre la partida
		vector<vector<int>> instruccionsDerrota = { {0, 0, 0} };
		//Utilitzem la classe MockInputGame per poder simular l'us d'instruccions que es reben durant la partida
		MockInputGame mockInputGameDerrota(instruccionsDerrota);
		//Utilitzem la classe MockGame per simular la realització del joc i la matriu
		MockGame mockPartidaDerrota(1, "nom", mockInputGameDerrota, matriu);

		//Creem les instruccions per jugar una partida i sortir sense acabar-la
		vector<vector<int>> instruccionsSortir = { {3} };
		//Utilitzem la classe MockInputGame per poder simular l'us d'instruccions que es reben durant la partida
		MockInputGame mockInputGameSortir(instruccionsSortir);
		//Utilitzem la classe MockGame per simular la realització del joc i la matriu
		MockGame mockPartidaSortir(1, "nom", mockInputGameSortir, matriu);
		
		//Creem un vector amb els mocks de totes les partides que volem jugar
		vector<Game*> partides = { &mockPartidaVictoria, &mockPartidaDerrota, &mockPartidaSortir };
		//Creem un mock de InputMenu per simular els inputs del menu
		MockInputMenu mockInputMenu;

		//Creem el path del nostre fitxer de proves, que l'utilitzarem per guardar les dades de les partides simulades
		string path = "../../files/RankingTest.txt";
		
		//Esborrem el contingut que hi havia al fitxer anteriorment
		ofstream file(path, ios::trunc);
		file.close();

		Menu menu(mockInputMenu, partides, path);
		//Cridem a la funció del bucle principal
		menu.iniciar();

		ifstream file2(path);
		string linia;
		getline(file2, linia);
		//Comprovem si les dades guardades en el fitxer son les correctes
		Assert::AreEqual(string("nom 1 290 1"), linia);
		getline(file2, linia);
		Assert::AreEqual(string("nom 0 0 1"), linia);
		file2.close();
	}

	//Aquest test ens permet comprovar si s'han guardat correctament les dades (nom, puntuacio, dificultat i
	//resultat) en el  fitxer RankingTest.txt
	TEST_METHOD(test_guardarPuntuacio)
	{
		
		//Indiquem on volem crear el fitxer i el seu nom
		string path = "../../files/RankingTest.txt";
		//Esborrem el contingut que hi havia al fitxer anteriorment
		ofstream file(path, ios::trunc);
		file.close();

		Menu menu;
		string nom, resultat, puntuacio, dificultat;
		
		//Guardem la següent informació
		menu.guardarPuntuacio("nom1", 1, 290, 1, path);
		string linea;
		ifstream file2(path);
		//llegim el fitxer
		getline(file2, linea);
		//Agafem la primera línia i fem un split de la cadena que hem guardat
		stringstream input_stringstream(linea);
		getline(input_stringstream, nom, ' ');
		getline(input_stringstream, resultat, ' ');
		getline(input_stringstream, puntuacio, ' ');
		getline(input_stringstream, dificultat, ' ');
		file2.close();
		//COmprovem que la informació llegida es correcte
		Assert::AreEqual(string("nom1"), nom);
		Assert::AreEqual(string("1"), resultat);
		Assert::AreEqual(string("290"), puntuacio);
		Assert::AreEqual(string("1"), dificultat);

		//Guardem en el fitxer una altre linia d'informació d'una altra partida
		menu.guardarPuntuacio("nom2", 0, 150, 2, path);
		file2.open(path);
		//Comprovem que tenim encara la informació anterior i no ha estat sobreescrita
		getline(file2, linea);
		stringstream input_stringstream2(linea);
		getline(input_stringstream2, nom, ' ');
		getline(input_stringstream2, resultat, ' ');
		getline(input_stringstream2, puntuacio, ' ');
		getline(input_stringstream2, dificultat, ' ');
		Assert::AreEqual(string("nom1"), nom);
		Assert::AreEqual(string("1"), resultat);
		Assert::AreEqual(string("290"), puntuacio);
		Assert::AreEqual(string("1"), dificultat);
		//Comprovem que també està la nova línia que hem afegit
		getline(file2, linea);
		stringstream input_stringstream3(linea);
		getline(input_stringstream3, nom, ' ');
		getline(input_stringstream3, resultat, ' ');
		getline(input_stringstream3, puntuacio, ' ');
		getline(input_stringstream3, dificultat, ' ');
		Assert::AreEqual(string("nom2"), nom);
		Assert::AreEqual(string("0"), resultat);
		Assert::AreEqual(string("150"), puntuacio);
		Assert::AreEqual(string("2"), dificultat);
		file2.close();
	}

	//Aquest test guarda la informació de tres partides al fitxer RankingTest.txt, posteriorment 
	//es llegeix el fitxer i es comprova que sigui correcte totes les dades
	TEST_METHOD(test_llegirRanking)
	{
		//Creem la ruta i el nom del fitxer
		string path = "../../files/RankingTest.txt";
		//Esborrem el contingut que hi havia al fitxer anteriorment
		ofstream file(path, ios::trunc);
		file.close();

		//Guardem les dades de les tres partides
		Menu menu;
		menu.guardarPuntuacio("nom1", 1, 290, 1, path);
		menu.guardarPuntuacio("nom2", 0, 90, 2, path);
		menu.guardarPuntuacio("nom3", 0, 30, 3, path);

		//Fem la lectura de fitxer, guardant les dades recollides
		vector<vector<string>> ranking = menu.llegirRanking(path);

		//Fem les comprovacions corresponents per comprovar que ha estat llegit be
		Assert::AreEqual(string("nom1"), ranking[0][0]);
		Assert::AreEqual(string("1"), ranking[0][1]);
		Assert::AreEqual(string("290"), ranking[0][2]);
		Assert::AreEqual(string("1"), ranking[0][3]);
		Assert::AreEqual(string("nom2"), ranking[1][0]);
		Assert::AreEqual(string("0"), ranking[1][1]);
		Assert::AreEqual(string("90"), ranking[1][2]);
		Assert::AreEqual(string("2"), ranking[1][3]);
		Assert::AreEqual(string("nom3"), ranking[2][0]);
		Assert::AreEqual(string("0"), ranking[2][1]);
		Assert::AreEqual(string("30"), ranking[2][2]);
		Assert::AreEqual(string("3"), ranking[2][3]);
	}
};