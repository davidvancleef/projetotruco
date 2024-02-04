#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
 
  typedef struct{
    char nome[20];
    int cartas;
    int mao[3];
    int cartajogada[3];
    int vitorias;
    int derrotas;
    int pontosequipe1;
    int pontosequipe2;
    int j;
    } principal;

  typedef struct {
    char cartass[20];
    int rodada;
    } maozinha;
 
void placar(principal *jogador, FILE *estatistica, maozinha *aloha); // TUDO CERTO
void menu(principal *jogador, FILE *estatistica, maozinha *aloha); // TUDO CERTO
void estatisticas (principal *jogador, FILE *estatistica, maozinha *aloha); // TUDO CERTO
int embaralhar(principal *jogador); // TUDO CERTO
void maojogadorprincipal (principal *jogador, maozinha *aloha); // TUDO CERTO
int botpensartruco(principal *jogador); // TUDO CERTO
int escolhasjogador (principal *jogador, FILE *estatistica, maozinha *aloha); // QUASE TUDO CERTO
int comecarodada (principal *jogador, FILE *estatistica, maozinha *aloha);
int comecaturnos (principal *jogador, FILE *estatistica, maozinha *aloha);
void designmesa (principal *jogador, maozinha *aloha);
int cartasdamesa (principal *jogador, FILE *estatistica, maozinha *aloha);
void cartasjogadasbots (principal *jogador);

void placar(principal *jogador, FILE *estatistica, maozinha *aloha){
if (jogador[0].pontosequipe1 == 12){
    jogador[0].vitorias++;
    jogador[0].pontosequipe1 = 0;
    jogador[0].pontosequipe2 = 0;
    printf ("Parabens, voce venceu!\n");
    menu(jogador, estatistica, aloha);
}
if (jogador[0].pontosequipe2 == 12){
    jogador[0].derrotas++;
    jogador[0].pontosequipe1 = 0;
    jogador[0].pontosequipe2 = 0;
    printf ("Que pena, voce perdeu.\n");
    menu(jogador, estatistica, aloha);
}
if (jogador[0].pontosequipe1 >= 10 && jogador[0].pontosequipe2 >= 10){
printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                  PLACAR                    ||\n||                                            ||\n||       Voces: %i        Oponentes: %i       ||\n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", jogador[0].pontosequipe1, jogador[0].pontosequipe2);   
}
if (jogador[0].pontosequipe1 < 10 && jogador[0].pontosequipe2 < 10){
printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                  PLACAR                    ||\n||                                            ||\n||       Voces: %i         Oponentes: %i        ||\n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", jogador[0].pontosequipe1, jogador[0].pontosequipe2);
}
if (jogador[0].pontosequipe1 >= 10 && jogador[0].pontosequipe2 < 10){
printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                  PLACAR                    ||\n||                                            ||\n||       Voces: %i         Oponentes: %i       ||\n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", jogador[0].pontosequipe1, jogador[0].pontosequipe2);
}
if (jogador[0].pontosequipe2 >= 10 && jogador[0].pontosequipe1 < 10){
printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                  PLACAR                    ||\n||                                            ||\n||       Voces: %i         Oponentes: %i       ||\n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", jogador[0].pontosequipe1, jogador[0].pontosequipe2);
}
}

void menu(principal *jogador, FILE *estatistica, maozinha *aloha){
    int comando;
   printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                                            ||\n||                                            ||\n||   Novo jogo(1) Estatisticas(2) Exit (3)    ||\n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf ("%i", &comando);
    while (comando > 3 || comando < 1){
    printf ("Comando invalido!\n");
    scanf ("%i", &comando);
    }
    
    if (comando == 1){
    comecarodada(jogador, estatistica, aloha);
    
    }
    if (comando == 2){
    estatisticas(jogador, estatistica, aloha);
    }
    if (comando == 3){
    exit(0);
    }
}

int comecarodada(principal *jogador, FILE *estatistica, maozinha *aloha){
    aloha[0].rodada = 0;
    printf ("\n\n\n\n\n\n\n");
    embaralhar(jogador);
    comecaturnos(jogador, estatistica, aloha);
    jogador[0].j = 0;
    while (jogador[0].vitorias < 1){
        comecarodada(jogador, estatistica, aloha);
    }
    return jogador[0].vitorias;
}

int comecaturnos(principal *jogador, FILE *estatistica, maozinha *aloha){
    placar(jogador, estatistica, aloha);
    maojogadorprincipal(jogador, aloha);
    escolhasjogador(jogador, estatistica, aloha);
    if (jogador[0].pontosequipe1 > 0 || jogador[0].pontosequipe2 > 0){
        comecarodada (jogador, estatistica, aloha);
    }
    designmesa(jogador, aloha);
    aloha[0].rodada++;  
    jogador[0].j++;
    return (jogador[0].pontosequipe1, jogador[0].pontosequipe2);
}

void designmesa (principal *jogador, maozinha *aloha){
   int i = jogador[0].j;
   printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                   MESA                     ||\n                                                \n||                                            ||\n||                                            ||\n||                  %s                        ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", jogador[0].cartajogada[i], jogador[1].cartajogada[i], jogador[2].cartajogada[i], jogador[3].cartajogada[i]);
}

void estatisticas (principal *jogador, FILE *estatistica, maozinha *aloha){
    int vitoriass, vitoriasnovas;
    int derrotass, derrotasnovas;
    estatistica = fopen ("estatistica.txt", "r");
    fscanf (estatistica, "%i Vitorias %i Derrotas", &vitoriass, &derrotass);
    fclose (estatistica);
    vitoriasnovas = vitoriass + jogador[0].vitorias;
    derrotasnovas = derrotass + jogador[0].derrotas;
    printf ("  Jogador: %s\n", jogador[0].nome);
    printf ("  Vitorias: %i\n  Derrotas: %i\n", vitoriasnovas, derrotasnovas);

    estatistica = fopen ("estatistica.txt", "w");
    fprintf (estatistica,"%i Vitorias %i Derrotas", vitoriasnovas, derrotasnovas);
    fclose (estatistica);
    jogador[0].vitorias = 0;
    jogador[0].derrotas = 0;
    menu(jogador,estatistica, aloha);
}


int embaralhar(principal *jogador){
int randnumber;
int randinho;
int i, j;
for (i = 0; i < 4; i++){
for (j = 0; j < 3; j++){
srand(time(NULL));
randinho = (rand() % 100);
randnumber = (randinho % 27) + 1;
while (randnumber == jogador[0].mao[0] || randnumber == jogador[0].mao[1] || randnumber == jogador[0].mao[2] || randnumber == jogador[1].mao[0] || randnumber == jogador[1].mao[1] || randnumber == jogador[1].mao[2] || randnumber == jogador[2].mao[0] || randnumber == jogador[2].mao[1] || randnumber == jogador[2].mao[2] || randnumber == jogador[3].mao[0] || randnumber == jogador[3].mao[1] || randnumber == jogador[3].mao[2]){
    randnumber = (rand() % 27) + 1;
  }
jogador[i].mao[j] = randnumber;
}
}
return (jogador[0].mao[0], jogador[0].mao[1], jogador[0].mao[2], jogador[1].mao[0], jogador[1].mao[1], jogador[1].mao[2], jogador[2].mao[0], jogador[2].mao[1], jogador[2].mao[2], jogador[3].mao[0], jogador[3].mao[1], jogador[3].mao[2]);
}

void maojogadorprincipal (principal *jogador, maozinha *aloha){
    
    int i;
    for (i=0;i<4;i++){
    if (jogador[0].mao[i] == 1){
        strcpy(aloha[i].cartass, "Q ouros");
    }
    if (jogador[0].mao[i] == 2){
        strcpy(aloha[i].cartass, "Q espadas");
    }
    if (jogador[0].mao[i] == 3){
        strcpy(aloha[i].cartass, "Q copas");
    }
    if (jogador[0].mao[i] == 4){
        strcpy(aloha[i].cartass, "Q paus");
    }
    if (jogador[0].mao[i] == 5){
        strcpy(aloha[i].cartass, "J ouros");
    }
    if (jogador[0].mao[i] == 6){
        strcpy(aloha[i].cartass, "J espadas");
    }
    if (jogador[0].mao[i] == 7){
        strcpy(aloha[i].cartass, "J copas");
    }
    if (jogador[0].mao[i] == 8){
        strcpy(aloha[i].cartass, "J paus");
    }
    if (jogador[0].mao[i] == 9){
        strcpy(aloha[i].cartass, "K ouros");
    }
    if (jogador[0].mao[i] == 10){
        strcpy(aloha[i].cartass, "K espadas");
    }
    if (jogador[0].mao[i] == 11){
        strcpy(aloha[i].cartass, "K copas");
    }
    if (jogador[0].mao[i] == 12){
        strcpy(aloha[i].cartass, "K paus");
    }
    if (jogador[0].mao[i] == 13){
        strcpy(aloha[i].cartass, "A ouros");
    }
    if (jogador[0].mao[i] == 14){
        strcpy(aloha[i].cartass, "A copas");
    }
    if (jogador[0].mao[i] == 15){
        strcpy(aloha[i].cartass, "A paus");
    }
    if (jogador[0].mao[i] == 16){
        strcpy(aloha[i].cartass, "2 ouros");
    }
    if (jogador[0].mao[i] == 17){
        strcpy(aloha[i].cartass, "2 espadas");
    }
    if (jogador[0].mao[i] == 18){
        strcpy(aloha[i].cartass, "2 copas");
    }
    if (jogador[0].mao[i] == 19){
        strcpy(aloha[i].cartass, "2 paus");
    }
    if (jogador[0].mao[i] == 20){
        strcpy(aloha[i].cartass, "3 ouros");
    }
    if (jogador[0].mao[i] == 21){
        strcpy(aloha[i].cartass, "3 espadas");
    }
    if (jogador[0].mao[i] == 22){
        strcpy(aloha[i].cartass, "3 copas");
    }
    if (jogador[0].mao[i] == 23){
        strcpy(aloha[i].cartass, "3 paus");
    }
    if (jogador[0].mao[i] == 24){
        strcpy(aloha[i].cartass, "$ 7 Ouros $");
    }
    if (jogador[0].mao[i] == 25){
        strcpy(aloha[i].cartass, "$ Espadilha $");
    }
    if (jogador[0].mao[i] == 26){
        strcpy(aloha[i].cartass, "$ 7 Copas $");
    }
    if (jogador[0].mao[i] == 27){
        strcpy(aloha[i].cartass, "$ Zap $");
    }
    }
    
     printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                   MAO                      ||\n||                                            ||\n     %s      %s      %s     \n||                                            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n", aloha[0].cartass, aloha[1].cartass, aloha[2].cartass);
    
}


int escolhasjogador (principal *jogador, FILE *estatistica, maozinha *aloha){
    int escolha;
    int botaceita;
    int trucado = 0;
    int a=0, b=0, c=0, d=0, e=0, f=0;
    int i = aloha[0].rodada;
    int j;
    
    if (trucado == 0){
    printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                                            ||\n||                                            ||\n||     Carta1(1)  Carta2(2)  Carta3(3)        ||\n||          Correr (4)  Trucar (5)            ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf ("%i", &escolha);
    while (escolha == 1){
        if (jogador[0].mao[0] == 0){
            printf ("Essa carta ja foi jogada!\n");
            d++;
            scanf ("%i", &escolha);
        }
        if (d == 0){
        jogador[0].cartajogada[i] = jogador[0].mao[0];
        jogador[0].mao[0] = 0;
        escolha = 0;
        }
    }
    while (escolha == 2){
        if (jogador[0].mao[0] == 0){
            printf ("Essa carta ja foi jogada!\n");
            e++;
            scanf ("%i", &escolha);
        }
        if (e == 0){
        jogador[0].cartajogada[i] = jogador[0].mao[1];
        jogador[0].mao[1] = 0;
        escolha = 0;
        }
    }
    while (escolha == 3){
        if (jogador[0].mao[0] == 0){
            printf ("Essa carta ja foi jogada!\n");
            f++;
            scanf ("%i", &escolha);
        }
        if (f == 0){
            jogador[0].cartajogada[i] = jogador[0].mao[2];
            jogador[0].mao[2] = 0;
            escolha = 0;
        }
    }
    if (escolha == 4){
        jogador[0].pontosequipe2++;
        return (jogador[0].pontosequipe1, jogador[0].pontosequipe2);
    }
    if (escolha == 5){
    botpensartruco(jogador);
    if (botaceita == 1){
    trucado = 1;
    escolhasjogador(jogador,estatistica,aloha);
    }
    if (botaceita == 0){ //o bot corre e a rodada é reiniciada, dando 1 ponto ao jogador.
    jogador[0].pontosequipe1++;
    return (jogador[0].pontosequipe1, jogador[0].pontosequipe2);
    }
    }

    j = escolha - 1;

    return (jogador[0].cartajogada[i], jogador[0].mao[j]);
    }

    if (trucado == 1){
    printf ("||||||||||||||||||||||||||||||||||||||||||||||||\n||                                            ||\n||                                            ||\n||     Carta1(1)  Carta2(2)  Carta3(3)        ||\n||              Correr (4)                    ||\n||                                            ||\n||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf ("%i", &escolha);
    while (escolha == 1){
        if (jogador[0].mao[0] == 0){
            printf ("Essa carta ja foi jogada!\n");
            a++;
            scanf ("%i", &escolha);
        }
        if (a == 0){
        jogador[0].cartajogada[i] = jogador[0].mao[0];
        jogador[0].mao[0] = 0;
        escolha = 0;
        }
    }
    while (escolha == 2){
        if (jogador[0].mao[1] == 0){
            printf ("Essa carta ja foi jogada!\n");
            b++;
            scanf ("%i", &escolha);
        }
        if (b == 0){
        jogador[0].cartajogada[i] = jogador[0].mao[1];
        jogador[0].mao[1] = 0;
        escolha = 0;
        }
    }
    while (escolha == 3){
        if (jogador[0].mao[2] == 0){
            printf ("Essa carta ja foi jogada!\n");
            c++;
            scanf ("%i", &escolha);
        }
        if (c == 0){
        jogador[0].cartajogada[i] = jogador[0].mao[2];
        jogador[0].mao[2] = 0;
        escolha = 0;
        }
    }
   if (escolha == 4){
        jogador[0].pontosequipe2++;
        jogador[0].pontosequipe2++;
        jogador[0].pontosequipe2++;
        return (jogador[0].pontosequipe1, jogador[0].pontosequipe2);
    }
    j = escolha - 1;

    return (jogador[0].cartajogada[i], jogador[0].mao[j]);
    }
    }

void cartasjogadasbots (principal *jogador)
{
 int i;
 for (i = 0; i < 4; i ++){
 jogador[1].cartajogada[i] = jogador[1].mao[i];
 jogador[3].cartajogada[i] = jogador[1].mao[i];
    }
}

int botpensartruco(principal *jogador){
    int i;
    int chance;
    int manilha;
    int botaceita;
    int trucado;
    for (i = 0; i < 3; i++){
    if ((jogador[1].mao[i]/3) >= 5){
    chance++;
    }
    if ((jogador[3].mao[i]/3) >= 5){
    chance++;
    }
    if (jogador[1].mao[i] == 23 || jogador[1].mao[i] == 24 || jogador[1].mao[i] == 25 || jogador[1].mao[i] == 26){
    manilha++;
    }
    if (jogador[3].mao[i] == 23 || jogador[3].mao[i] == 24 || jogador[3].mao[i] == 25 || jogador[3].mao[i] == 26){
    manilha++;
    }
    }
    
    if (chance >= 2 && manilha > 0){
    botaceita = 1;
    }
    if (chance < 2){
    botaceita = 0;
    }
    return botaceita;
}
/*
int cartasdamesa (principal *jogador, FILE *estatistica, maozinha *aloha){
    int maiorcarta = 0;
    int rodadaequipe1 = 0;
    int rodadaequipe2 = 0;
    int cangado, cangado2, cangado3;
    int i;
    int v[4];
    int trucado;
    int j;
    int cartajogada[4];

    j = jogador[0].j;
    cartajogada[0] = jogador[0].cartajogada[j];
    cartajogada[1] = jogador[1].cartajogada[j];
    cartajogada[2] = jogador[2].cartajogada[j];
    cartajogada[3] = jogador[3].cartajogada[j];
    

    for (i = 0; i < 4; i++){
    
            if (cartajogada[i] == maiorcarta){
                cangado++;
            }

            if (cartajogada[i] > maiorcarta){
                maiorcarta = cartajogada[i];
                cangado = 0;
            }
    }

    if (cangado > 0){ // se cangar entra aqui
        escolhasjogador(jogador, estatistica, aloha);
        cartasjogadasbots (jogador);
        maiorcarta = 0;
         for (i = 0; i < 4; i++){
            if (cartajogada[i] == maiorcarta){
                cangado2++;
             }
            if (cartajogada[i] > maiorcarta){
                maiorcarta = cartajogada[i];
                cangado2 = 0;
            }
        }
      if (cangado2 == 0){
        if (maiorcarta == jogador[0].mao[0] || maiorcarta == jogador[0].mao[1] || maiorcarta == jogador[0].mao[2] || maiorcarta == jogador[2].mao[0] || maiorcarta == jogador[2].mao[1] || maiorcarta == jogador[2].mao[2]){
            rodadaequipe1++;
            }
 
        if (maiorcarta == jogador[1].mao[0] || maiorcarta == jogador[1].mao[1] || maiorcarta == jogador[1].mao[2] || maiorcarta == jogador[3].mao[0] || maiorcarta == jogador[3].mao[1] || maiorcarta == jogador[3].mao[2] ){
            rodadaequipe2++;
            } 
        }
      if (cangado2 > 0){ // se cangar denovo, entra aqui
            escolhasjogador(jogador,estatistica, aloha);
            cartasjogadasbots (jogador);
            maiorcarta = 0;
            for (i = 0; i < 4; i++){
                if (cartajogada[i] == maiorcarta){
                    cangado3++;
                }
            if (cartajogada[i] > maiorcarta){
                maiorcarta = cartajogada[i];
                cangado3 = 0;
            }
                }
            if (cangado3 == 0){
                if (maiorcarta == jogador[0].mao[0] || maiorcarta == jogador[0].mao[1] || maiorcarta == jogador[0].mao[2] || maiorcarta == jogador[2].mao[0] || maiorcarta == jogador[2].mao[1] || maiorcarta == jogador[2].mao[2]){
                rodadaequipe1++;
                }
 
                if (maiorcarta == jogador[1].mao[0] || maiorcarta == jogador[1].mao[1] || maiorcarta == jogador[1].mao[2] || maiorcarta == jogador[3].mao[0] || maiorcarta == jogador[3].mao[1] || maiorcarta == jogador[3].mao[2] ){
                rodadaequipe2++;
                } 
            }
        }
    }   

 if (maiorcarta == jogador[0].mao[0] || maiorcarta == jogador[0].mao[1] || maiorcarta == jogador[0].mao[2] || maiorcarta == jogador[2].mao[0] || maiorcarta == jogador[2].mao[1] || maiorcarta == jogador[2].mao[2]){
 rodadaequipe1++;
 }
 
 if (maiorcarta == jogador[1].mao[0] || maiorcarta == jogador[1].mao[1] || maiorcarta == jogador[1].mao[2] || maiorcarta == jogador[3].mao[0] || maiorcarta == jogador[3].mao[1] || maiorcarta == jogador[3].mao[2] ){
 rodadaequipe2++;
 }

 if (rodadaequipe2 > 1 && trucado == 0){
    jogador[0].pontosequipe2++;
    return jogador[0].pontosequipe2;
 }

 if (rodadaequipe2 > 1 && trucado == 1){
    jogador[0].pontosequipe2++;
    jogador[0].pontosequipe2++;
    jogador[0].pontosequipe2++;
    return jogador[0].pontosequipe2;
 }

 if (rodadaequipe1 > 1 && trucado == 0){
    jogador[0].pontosequipe1++;
    return jogador[0].pontosequipe1;
 }
 
 if (rodadaequipe1 > 1 && trucado == 1){
    jogador[0].pontosequipe1++;
    jogador[0].pontosequipe1++;
    jogador[0].pontosequipe1++;
    return jogador[0].pontosequipe1;
 }
}
*/
int main (){
    maozinha aloha[3];
    principal jogador[4];
    jogador[0].pontosequipe1 = 0;
    jogador[0].pontosequipe2 = 0;
    jogador[0].vitorias = 0;
    jogador[0].derrotas = 0;
    FILE *estatistica = fopen("estatistica.txt", "r");
  if (estatistica == NULL){
    estatistica = fopen ("estatistica.txt", "w");
    fprintf (estatistica,"0 Vitorias 0 Derrotas");
    fclose(estatistica);
    }
 
    printf ("    Nome do jogador: ");
    scanf ("%s", jogador[0].nome);
    
    menu(jogador, estatistica, aloha);
}