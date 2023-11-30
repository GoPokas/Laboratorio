#include "lab.h"
// Estrutura da pista

typedef enum // Enum para definir o tipo de pista
{
    STARTING_BOX,
    STRAIGHT_BOX,
    RIVER_BOX,
    FINISH_BOX,
    PODIUM_BOX,
} TipoPista;

typedef struct 
{
    TipoPista tipo;
    int id;
} Peças;

typedef struct 
{
    Peças peças[14];
} Pista;


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
    printf("Guilherme Temporão");
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
void inicializarJogador(Jogador *jogador, Baralho *baralho){
    printf("Insira o nome do jogador: ");
    scanf("%s", jogador->nome);
    jogador->pontos = 0;
    
    for (int i = 0; i < 6; i++)
    {
        // Atribuir as cartas ao jogador
        jogador->mao[i].id = baralho->cartas[i].id;    
        jogador->mao[i].tipo = baralho->cartas[i].tipo;
    }
}

// Função para inicializar e baralhar a pista
void inicializarPista(Pista *pista){
    // Inicializar a pista
    for (int i = 0; i < 14; i++)
    {
        if (i < 1)    
        {
            pista->peças[i].tipo = STARTING_BOX;
        }
        else if (i < 10)
        {
            pista->peças[i].tipo = STRAIGHT_BOX;
        }
        else if (i < 12)
        {
            pista->peças[i].tipo = RIVER_BOX;
        }
        else if (i < 13)
        {
            pista->peças[i].tipo = FINISH_BOX;
        }
        else
        {
            pista->peças[i].tipo = PODIUM_BOX;
        }
        pista->peças[i].id = i;
      } 
    // Baralhar as peças
    srand(time(NULL));
    for (int i = 13; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Peças temp = pista->peças[i];
        pista->peças[i] = pista->peças[j];
        pista->peças[j] = temp;
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

// Função para imprimir a pista (para testes)
void imprimirPista(Pista *pista)
{
    for (int i = 0; i < 14; i++)
    {
        printf("A pista %d é um(a) ", pista->peças[i].id);
        switch (pista->peças[i].tipo)
        {
        case STARTING_BOX:
            printf("Caixa de inicio\n");
            break;
        case STRAIGHT_BOX:
            printf("Caixa reta\n");
            break;
        case RIVER_BOX:
            printf("Caixa de rio\n");
            break;
        case FINISH_BOX:
            printf("Caixa de fim\n");
            break;
        case PODIUM_BOX:
            printf("Caixa de pódio\n");
            break;
        }
    }
}

// Função para imprimir o baralho (para testes)
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
    Pista pista;
    Baralho baralho;
    Jogador jogador1, jogador2;
    inicializarBaralho(&baralho);
    inicializarPista(&pista);
    inicializarJogador(&jogador1, &baralho);
    // inicializarJogador(&bot, &baralho);
    

}


int main() {
    int opcao, loop = 1;
    Baralho baralho;
    Pista pista;
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
