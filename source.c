#include "lab.h"
//Estrutura do baralho
typedef enum // Enum para definir o tipo de carta
{
    HARE,
    TURTLE,
    WOLF,
    WOLF_HOWL,
    FOX,
    SHEEP
} TipoCarta;

typedef struct // Estrutura da carta
{
    TipoCarta tipo;
    int id;
} Carta;

typedef struct // Estrutura do baralho
{
    Carta cartas[81];
} Baralho;

typedef struct // Estrutura do jogador
{
    char nome[50];
    int pontos;
    Carta mao[6];
} Jogador;

// Função do ecrã inicial
void ecraInicial(){
    setFullScreen(true);
    // Definir a cor do background e da letra
    setColor(MY_COLOR_BLACK, MY_COLOR_WHITE);
    // Meter a consola em Fullscreen
    setFullScreen(true);
    // Apagar a consola
    system("cls");
    // Apresentar o nome do jogo
    gotoxy(90, 10);
    printf("Jogo da Lebra e da Tartaruga");
    gotoxy(90, 11);
    printf("Rodrigo Alves");
    // Pausa para avançar para o menu
    gotoxy(90, 15);
    system("pause");
    system("cls");
}
// Função do menu
int menu(int opcao){
    // Apresentar o menu
    system("cls");
    do {
        gotoxy(90, 10);
        printf("Menu");
        gotoxy(90, 11);
        printf("1 - Novo Jogo");
        gotoxy(90, 12);
        printf("2 - Continuar Jogo");
        gotoxy(90, 13);
        printf("3 - Regras");
        gotoxy(90, 14);
        printf("0 - Sair");
        gotoxy(90, 15);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        system("cls");
        } while (opcao < 0 || opcao > 3); // Loop para repetir o menu caso o utilizador insira uma opção inválida
    return opcao;
}

// Função para inicializar o jogador
void inicializarJogador(Jogador *jogador, Carta carta){
    printf("Insira o nome do jogador: ");
    scanf("%s", jogador->nome);
    jogador->pontos = 0;
    
    for (int i = 0; i < 6; i++)
    {
        if (jogador->mao[i].id == -1)
        {
            jogador->mao[i] = carta;    
        }
    }
}

// Função para inicializar e baralhar o baralho
void inicializarBaralho(Baralho *baralho){
        // Inicializar o baralho
    for (int i = 0; i < 81; i++)
    {
        if (i < 18)
        {
            baralho->cartas[i].tipo = HARE;
        }
        else if (i < 35)
        {
            baralho->cartas[i].tipo = TURTLE;
        }
        else if (i < 48)
        {
            baralho->cartas[i].tipo = WOLF;
        }
        else if (i < 51)
        {
            baralho->cartas[i].tipo = WOLF_HOWL;
        }
        else if (i < 66)
        {
            baralho->cartas[i].tipo = FOX;
        }
        else
        {
            baralho->cartas[i].tipo = SHEEP;
        }
        baralho->cartas[i].id = i;
    }
    // Baralhar o baralho
    srand(time(NULL));
    for (int i = 80; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Carta temp = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = temp;
    }
    }

// Função para imprimir o baralho
void imprimirBaralho(Baralho *baralho)
{
    for (int i = 0; i < 81; i++)
    {
        printf("A carta %d é um(a) ", baralho->cartas[i].id);
        switch (baralho->cartas[i].tipo)
        {
        case HARE:
            printf("Lebre\n");
            break;
        case TURTLE:
            printf("Tartaruga\n");
            break;
        case WOLF:
            printf("Lobo\n");
            break;
        case WOLF_HOWL:
            printf("Lobo_Uivar\n");
            break;
        case FOX:
            printf("Raposa\n");
            break;
        case SHEEP:
            printf("Ovelha\n");
            break;
        }
    }
}

// Função para criar um novo jogo
void novoJogo(){
    Baralho baralho;
    inicializarBaralho(&baralho);
    imprimirBaralho(&baralho);
}


int main() {
    int opcao, loop = 1;
    Baralho baralho;
    setlocale(LC_ALL, "pt_PT.UTF-8");
    setFullScreen(true);
    ecraInicial();
    // Loop para poder voltar ao menu depois do utilizador escolher a opção das regras
    while(loop == 1){
        opcao = menu(opcao);
        switch (opcao) {
        case 1:
            // Novo Jogo
            loop = 0;
            novoJogo();
            break;
        case 2:
            // Continuar Jogo
            loop = 0;
            break;
        case 3:
            // Regras
            FILE *regras;
            if ((regras = fopen("regras.txt", "r")) == NULL)
            {
                printf("Erro ao abrir o ficheiro!\n");
                exit(1);
            }
            int c;
            while ((c = fgetc(regras)) != EOF)
            {
                putchar(c);
            }
            fclose(regras);
            printf("\n\n"); system("pause");
            break;
        case 0:
            // Sair
            exit(0);
            break;
        default:
            break;
        }
    }
}