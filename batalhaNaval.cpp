#include <iostream>
#include <string>
#include <new>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TAMTABULEIRO 10
#define QNTBARCOS 10
#define MAXTENTATIVAS 3

using namespace std;

void iniciaTabululeiro (char tabuleiro[TAMTABULEIRO][TAMTABULEIRO], char mascara[TAMTABULEIRO][TAMTABULEIRO]) {

    for (int i = 0; i < TAMTABULEIRO; i++) {
        for (int j = 0; j < TAMTABULEIRO; j++) {
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
}

void posicionaBarcos (char tabuleiro[TAMTABULEIRO][TAMTABULEIRO]) {
    int quantidade = QNTBARCOS;
    int linhaRandom, colunaRandom;

    for (int i = 0; i < QNTBARCOS; i++) {
        linhaRandom = rand() % TAMTABULEIRO;
        colunaRandom = rand() % TAMTABULEIRO;

        if (tabuleiro[linhaRandom][colunaRandom] == 'A') {
            tabuleiro[linhaRandom][colunaRandom] = 'P';
        }

        else {
            i--;
        }
    }
}

void exibeIndicador () {
    for (int i = 0; i < TAMTABULEIRO; i++) {
        if (i == 0) {
            cout << "   ";
        }
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < TAMTABULEIRO; i++) {
        if (i == 0) {
            cout << "   ";
        }
        cout << "| ";
    }
    cout << "\n";
}

void exibeTabuleiro (char tabuleiro[TAMTABULEIRO][TAMTABULEIRO], char mascara[TAMTABULEIRO][TAMTABULEIRO], bool gabarito) {
    exibeIndicador();
    char water[] = { 0x1b, '[', '1', ';', '3', '6', 'm', 0 };
    char boat[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    
    for (int i = 0; i < TAMTABULEIRO; i++) {
        cout << i << "--";
        for (int j = 0; j < TAMTABULEIRO; j++) {
            if (mascara[i][j] == 'A') {
                cout << water << mascara[i][j] << " " << normal;
            }

            else if (mascara[i][j] == 'P') {
                cout << boat << mascara[i][j] << " " << normal;
            }

            else {
                cout << mascara[i][j] << " ";
            }
        }
        cout << "\n";
    }

    if (gabarito == true) {
        cout << "\n";
        for (int i = 0; i < TAMTABULEIRO; i++) {
            for (int j = 0; j < TAMTABULEIRO; j++) {
                cout << tabuleiro[i][j] << " ";
            }
            cout << "\n";
        }
    }
}

string verificaJogada (char tabuleiro[TAMTABULEIRO][TAMTABULEIRO], char mascara[TAMTABULEIRO][TAMTABULEIRO], int linha, int coluna, int *pontos, int *tentativas, string nome) {
    if (tabuleiro[linha][coluna] == 'P' && mascara[linha][coluna] == '*') {
            *pontos += 10;
            return nome, ", voce acertou um barco! (+10 pts)";
        }

    else if (mascara[linha][coluna] == 'P') {
        return nome, ", essa localizacao ja foi escolhida!";
    }

    else if (linha >= TAMTABULEIRO || coluna >= TAMTABULEIRO) {
        return nome, ", digite uma localizacao valida!";
    }

    else {
        *tentativas += 1;
        return nome, ", voce acertou a agua!";
    }
}

void jogo (string nome) {
    char tabuleiro[TAMTABULEIRO][TAMTABULEIRO];
    char mascara[TAMTABULEIRO][TAMTABULEIRO];
    bool game = true, secondLoop = true;
    string mensagem = ", de o seu primeiro palpite!";
    int linha, coluna, pontos = 0, tentativas = 0, maxtentativas = MAXTENTATIVAS, reiniciar;
    system("cls");

    iniciaTabululeiro(tabuleiro, mascara);
    posicionaBarcos(tabuleiro);

    while (game) {
        system("cls");

        cout << nome << mensagem << "\n\n"; 
        cout << "Tentativas: " << maxtentativas - tentativas << "\n";
        cout << "Pontuacao: " << pontos << "\n\n";
        exibeTabuleiro(tabuleiro, mascara, false);

        cout << "\n" << nome << ", digite uma linha: ";
        cin >> linha;

        cout << nome << ", digite uma coluna: ";
        cin >> coluna;

        mensagem = verificaJogada(tabuleiro, mascara, linha, coluna, &pontos, &tentativas, nome);

        mascara[linha][coluna] = tabuleiro[linha][coluna];

        if (tentativas == MAXTENTATIVAS) {
            system("cls");
            game = false;

            cout << "Suas tentativas acabaram!\n\n";
            cout << "Sua pontuacao foi de " << pontos << " pontos\n\n";
        }
    }

    while (secondLoop) {
        cout << "Deseja reiniciar o jogo?\n\n";

        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << "[ 1 ] -- SIM" << endl;
        cout << "[ 2 ] -- NAO" << endl;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

        cout << "Sua escolha: ";
        cin >> reiniciar;
        cin.ignore();

        switch (reiniciar) {
            case 1:
                system("cls");
                secondLoop = false;
                jogo(nome);
                break;
            case 2:
                secondLoop = false;
                system("cls");
                break;
            default:
                system("cls");
                cout << "\nPor favor, escolha uma das duas opcoes.\n\n";
                break;
        }
    }
}

void menu () {
    int opcao, opcaoSobre;
    bool mainLoop = true, thirdLoop = true;
    string nome;
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    cout << normal;
    while (mainLoop) {
        thirdLoop = true;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << " Bem vindo(a) a Batalha Naval! :)\n";
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << "[ 1 ] -- Jogar" << endl;
        cout << "[ 2 ] -- Sobre" << endl;
        cout << "[ 3 ] -- Sair" << endl;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                system("cls");
                cout << "Digite o seu nome: ";
                getline(cin, nome);
                jogo(nome);
                break;

            case 2:
                system("cls");

                while (thirdLoop) {
                    cout << "Batalha Naval desenvolvido por LUCAS LIMA! :)\n\n";
                    
                    cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
                    cout << "[ 1 ] -- Voltar" << endl;
                    cout << "[ 2 ] -- Sair" << endl;
                    cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

                    cout << "Escolha uma opcao: ";
                    cin >> opcaoSobre;

                    switch (opcaoSobre) {
                        case 1:
                            system("cls");
                            thirdLoop = false;
                            break;
                        case 2:
                            system("cls");
                            cout << "Jogo encerrado com sucesso!\n";
                            mainLoop = false;
                            thirdLoop = false;
                            break;
                        default:
                            system("cls");
                            cout << "Por favor, digite uma opcao valida!\n\n";
                            break;
                    }
                }
                break;

            case 3:
                system("cls");
                mainLoop = false;
                cout << "Jogo encerrado com sucesso!\n";
                break;

            default:
                system("cls");
                cout << "Por favor, digite uma opcao valida!\n\n";
                break;
        }
    }
}

int main() {
    srand((unsigned) time(NULL));
    system("cls");
    menu();

    return 0;
}
