#include <iostream>
#include <chrono>
#include <ctime>
#include <clocale>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;
using namespace std::chrono;


const int ROW = 6; //numero de linhas
const int COL = 7; //numero de colunas
const int MAXNUMPLAYS = ROW * COL; //numero de jogadas maximo -> numero de "casas" no board

//criacao de structs

//carolina
struct Board { //board
	char board[ROW][COL]; //tabuleiro e array de caracteres 
};


struct Player { //jogador
	string name;//nome do jogador
	bool ishuman = true; //é humano ou não. true para inicializar
	int numplayer; //para atribuicao aleatoria do caracter, nao tem a ver com a ordem do jogador, mas sim se ele fica com X (1) ou O (2)
};


//ver como fazer para nao se poder inserir numeros no nome (ou nao e necessario pq pode ser como um user?)

//ler nome do(s) jogador(es)
Player readPlayer() {
	Player p;

	cout << "\nWhat is your name? ";


	getline(cin, p.name);
	p.ishuman = true;


	return p;

}

Player readComputer() {
	Player p;

	p.name = "Computer";
	p.ishuman = false;

	return p;

}


//retorna a data atual
string date() {


	time_t t = time(NULL);
	tm time;
	errno_t err;
	err = localtime_s(&time, &t);

	string day, month, year;

	int mon = time.tm_mon + 1; //adiciona-se 1 ao mes e 1900 ao ano 
	int y = time.tm_year + 1900;

	//para aparecer com 2 digitos em vez de apenas 1
	if (time.tm_mday < 10) {
		day = "0" + to_string(time.tm_mday);
	}
	else {
		day = to_string(time.tm_mday);
	}

	if (mon < 10) {
		month = "0" + to_string(mon);
	}
	else {
		month = to_string(mon);
	}

	//nao se fez o mesmo para o ano, porque o ano atual nunca vai ter menos de 4 digitos
	year = to_string(y);

	string data = year + "-" + month + "-" + day;


	return data;

}

//ver como por (este e a data) com 2 digitos automaticamente, agora esta manual
//retorna a hora atual
string time() {

	time_t t = time(NULL);
	tm time;
	errno_t err;
	err = localtime_s(&time, &t);

	string hour, minute;

	if (time.tm_hour < 10) {
		hour = "0" + to_string(time.tm_hour);
	}
	else {
		hour = to_string(time.tm_hour);
	}

	if (time.tm_min < 10) {
		minute = "0" + to_string(time.tm_min);
	}
	else {
		minute = to_string(time.tm_min);
	}

	string tempo = hour + ":" + minute;

	return tempo;
}

//leonor
//Distribui os números 1 e 2 aleatoriamente pelos jogadores, para depois definir carateres correspondentes a cada jogador na função printfunction

void randplayer(Player& p1, Player& p2)
{
	p1.numplayer = 1 + (rand() % 2);

	if (p1.numplayer == 1)
	{
		p2.numplayer = 2;

	}
	else {

		p2.numplayer = 1;
	}

}

//Define os carateres correspondentes a cada jogador
char printfunction(Player p)
{

	if (p.numplayer == 1) {

		return 'X';
	}
	else {
		return 'O';
	}
}


//gera a escolha do computador
char cmpt_choice() {
	char choice = (rand() % 7) + 'a'; //a = 97 gerar números de 97 a 104

	return choice;
}




//tem de se avaliar se jogador e pessoa ou computador. atribuir nome automatico ao computador e passar para aqui na mesma
//jose
void play(Player p, Board& b, int* registration)
{
	//jogador escolhe uma letra
	//a jogada tem de ocupar um lugar livre
	//a letra escolhida tem de ser uma das disponíveis
	//caso não cumpra os critérios erro!


	char choose;



	if (p.ishuman) {
		cout << "\nPlayer " << p.name << " (" << p.numplayer << ")" << ", choose one column: ";
		cin >> choose;
		choose = tolower(choose);
	}
	else {
		//se for o pc gera um numero aleatorio
		cout << "Computer playing..." << endl;
		choose = cmpt_choice();
		cout << "Computer played on " << choose << endl;
	}


	if (cin.eof()) {
		cin.clear();
		char op;
		cout << "\nDo you want to leave the program? (y/n) "; //ver pq aparece caracter


		cin >> op;

		op = toupper(op);

		if (op == 'Y') { //falta validar oq acontece se nao for sim/nao (de momento, outra opcao funciona como "nao", ou seja, continua)
			exit(1);
		}
		else if (op == 'N') {
			system("PAUSE");
		}

	}


	while (choose > 'g' || choose < 'a' || registration[choose - 'a'] >= 6)
	{
		if (p.ishuman) {
			cout << "Please choose the column again: ";
			cin >> choose;
			choose = tolower(choose);

			if (cin.fail()) //ao pressionar ^z aqui estava a entrar em loop. acrescentei isto para isso nao acontecer, mas nao e a solucao ideal pq termina o programa logo
			{
				cout << "Error!";
				exit(1);
			}
		}

		else {
			choose = cmpt_choice();
		}
	}



	int numcol = choose - 'a';

	//porque e que tem este if else? nao faz exatamente a mesma coisa?
	if (p.numplayer == 1)
	{
		b.board[5 - registration[numcol]][numcol] = printfunction(p);

	}
	else {
		b.board[5 - registration[numcol]][numcol] = printfunction(p);
	}


	registration[numcol] ++;
}


//imprime o tabuleiro com as cores certas (X vermelho, O azul, ponto final branco)
void printboard(Board& b) {
	cout << "\nA B C D E F G" << endl;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (b.board[i][j] == 'X') {
				cout << "\033[31m" << b.board[i][j] << "\033[0m ";
			}
			else if (b.board[i][j] == 'O') {
				cout << "\033[34m" << b.board[i][j] << "\033[0m ";
			}
			else {
				cout << b.board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << "A B C D E F G" << endl;
}


//inicializa o tabuleiro a branco
void initBoard(Board& b) {


	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			b.board[i][j] = '.';

		}

	}

}



//ver se da para simplificar
//criterio para ganhar
//true se ganha, false se nao
bool win(Board b, Player p1, Player p2, Player& winner) {


	//percorrer linhas e colunas
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < 4; j++) {
			if (b.board[i][j] != '.' && b.board[i][j + 1] != '.' && b.board[i][j + 2] != '.' && b.board[i][j + 3] != '.') {
				//testar 4 em linha para linhas (percorrer colunas)
				if (b.board[i][j] == b.board[i][j + 1] && b.board[i][j + 1] == b.board[i][j + 2] && b.board[i][j + 2] == b.board[i][j + 3]) {
					if ((b.board[i][j] == 'X' && p1.numplayer == 1) || (b.board[i][j] == 'O' && p1.numplayer == 2)) {
						winner = p1;
						return true;
					}
					else if ((b.board[i][j] == 'X' && p2.numplayer == 1) || (b.board[i][j] == 'O' && p2.numplayer == 2)) {
						winner = p2;
						return true;
					}

				}
			}

		}
	}

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < 3; j++) { // ********NOVO/Leonor - Alterei de 4 para 3****************



			if (b.board[j][i] != '.' && b.board[j + 1][i] != '.' && b.board[j + 2][i] != '.' && b.board[j + 3][i] != '.') {
				//testar 4 em linha para colunas (percorrer linhas)
				if (b.board[j][i] == b.board[j + 1][i] && b.board[j + 1][i] == b.board[j + 2][i] && b.board[j + 2][i] == b.board[j + 3][i]) {
					if ((b.board[j][i] == 'X' && p1.numplayer == 1) || (b.board[j][i] == 'O' && p1.numplayer == 2)) {
						winner = p1;
						return true;
					}
					else if ((b.board[j][i] == 'X' && p2.numplayer == 1) || (b.board[j][i] == 'O' && p2.numplayer == 2)) {
						winner = p2;
						return true;
					}
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (b.board[j][i] != '.' && b.board[j + 1][i + 1] != '.' && b.board[j + 2][i + 2] != '.' && b.board[j + 3][i + 3] != '.') {
				//testar 4 em linha diagonais começar em cima
				if (b.board[j][i] == b.board[j + 1][i + 1] && b.board[j + 2][i + 2] == b.board[j + 3][i + 3] && b.board[j][i] == b.board[j + 2][i + 2]) {
					if ((b.board[j][i] == 'X' && p1.numplayer == 1) || (b.board[j][i] == 'O' && p1.numplayer == 2)) {
						winner = p1;
						return true;
					}
					else if ((b.board[j][i] == 'X' && p2.numplayer == 1) || (b.board[j][i] == 'O' && p2.numplayer == 2)) {
						winner = p2;
						return true;
					}
				}

			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 5; j > 2; j--) {
			if (b.board[j][i] != '.' && b.board[j - 1][i + 1] != '.' && b.board[j - 2][i + 2] != '.' && b.board[j - 3][i + 3] != '.') {
				//testar 4 em linha diagonais começar em baixo
				if (b.board[j][i] == b.board[j - 1][i + 1] && b.board[j - 2][i + 2] == b.board[j - 3][i + 3] && b.board[j][i] == b.board[j - 2][i + 2] && b.board[j][i] != ' ') {
					//pq e q so este e q tem opcao para espaco????
					if ((b.board[j][i] == 'X' && p1.numplayer == 1) || (b.board[j][i] == 'O' && p1.numplayer == 2)) {
						winner = p1;
						return true;
					}
					else if ((b.board[j][i] == 'X' && p2.numplayer == 1) || (b.board[j][i] == 'O' && p2.numplayer == 2)) {
						winner = p2;
						return true;
					}
				}
			}
		}
	}


	return false;
}


//comecar o jogo
void playerMove(Player& p1, Player& p2, Board& b, Player& winner) {

	int registration[COL] = { 0 }; //explicar

	randplayer(p1, p2);

	initBoard(b);
	printboard(b);


	int i = 0;

	while (win(b, p1, p2, winner) == false) { //se win for falso, ninguem ganhou
		if (i < MAXNUMPLAYS) { //nao pode haver mais jogadas do que "casas" no tabuleiro
			if (i % 2 == 0) {
				play(p1, b, registration);
				printboard(b);
				i++;
				win(b, p1, p2, winner);
			}
			else {
				play(p2, b, registration);
				printboard(b);
				i++;
				win(b, p1, p2, winner);
			}
		}
		if ((i == MAXNUMPLAYS) && (win(b, p1, p2, winner) == false())) { //ha empate quando o tabuleiro esta completo e ninguem ganhou
			cout << "\nThere was a draw!\n";
			winner.name = "draw";
			break;
		}

		else if (win(b, p1, p2, winner)) {
			cout << "\nThe winner is " << winner.name << endl;
		}

	}
}



void writeFile(Player p1, Player p2, Player winner, string data, string tempo) {

	ofstream endFile;


	endFile.open("gameResults.txt");

	if (!endFile.is_open()) { //is_open permite testar se ficheiro foi aberto com sucesso ou nao
		cerr << "File could not be created!\n";
		exit(2); //termina programa em qlq sitio, neste caso com codigo de erro diferente  
	}


	endFile << data << " / " << tempo << " " << p1.numplayer << ") " << p1.name << " vs " << p2.numplayer << ") " << p2.name << " - Winner is: " << winner.name << " (" << winner.numplayer << ")" << endl;

	endFile.close();




}




//criar menus


//menu de 2 jogadores
int menuPlayer()
{
	Player p1, p2, winner; //dois jogadores e vencedor (que vai ser um dos 2 primeiros)
	Board b; //tabuleiro
	char op; //opcao do menu. char para evitar um ciclo sem fim se o user inserir carateres em vez de numeros
	string data, hour; //data e hora atuais

	//OUTRA opcao: fazer com cin.fail e int. ver se funciona!

	cout << "          PLAYER MENU             " << endl;
	cout << "--------------------------------" << endl;
	cout << "1 - Start playing with a friend!" << endl;
	cout << "2 - Start playing with computer!" << endl;
	cout << "3 - Go back" << endl;

	cin >> op;


	switch (op)
	{
	case '1':
	{
		cin.ignore();

		p1 = readPlayer(); //le nome do primeiro jogador
		data = date();
		hour = time();


		p2 = readPlayer(); //le nome do segundo jogador
		data = date();
		hour = time();

		cout << "Game began in " << data << ", at " << hour << endl; //data e hora de inicio do jogo
		cout << "Press ctrl+Z to end the game." << endl;


		playerMove(p1, p2, b, winner);

		writeFile(p1, p2, winner, data, hour);

		system("PAUSE");

		break;
	}

	case '2':
	{
		cin.ignore();

		p1 = readPlayer(); //le nome de 2 jogadores 1 humano 1 bot


		p2 = readComputer();

		data = date();
		hour = time();

		cout << "Game began in " << data << ", at " << hour << endl; //data e hora de inicio do jogo


		playerMove(p1, p2, b, winner);

		writeFile(p1, p2, winner, data, hour);

		system("PAUSE");

		break;
	}
	case '3':
	{
		system("PAUSE");
		break;
	}
	default:
	{
		cout << "Invalid option. Please select another one." << endl;
	}

	}
	return 0;
}

//elementos do grupo
void showCredits() {
	cout << "Ana Lima" << "\nJosé Afonso" << "\nLeonor Soares\n";
}


int mainMenu() {

	char op; //opcao do menu


	//OUTRA opcao: fazer com cin.fail e int. ver se funciona!

	do {
		cout << "          MAIN MENU             " << endl;
		cout << "--------------------------------" << endl;
		cout << "1 - Start the game" << endl;
		cout << "2 - Credits" << endl;
		cout << "3 - Exit the program" << endl;

		cin >> op;


		switch (op) {
		case '1':
		{
			//levar ao menu de jogadores
			menuPlayer();
			break;
		}
		case '2':
		{
			showCredits();
			system("PAUSE");
			break;
		}
		case '3':
			//system("PAUSE");
			return 0;
		default:
			cout << "Invalid option. Please select another one." << endl;
			break;
		}
	} while (op != '3');



	return 0;
}


int main() {

	setlocale(LC_ALL, ""); //para aparecer acentos, cedilha, ...

	srand(time(NULL));

	mainMenu();


	return 0;
}