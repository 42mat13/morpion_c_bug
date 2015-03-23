/* source = Lapeyre Jacques-Olivier  youtube = https://www.youtube.com/watch?v=8LYsinhByHs */

#include <stdio.h>
#include <stdlib.h>

#define EMPTY '.' // case vide + status CONTINUE
#define PLAYER1 'O'
#define PLAYER2 'X'
#define DRAW_GAME ' '

typedef struct _grid *grid;

struct _grid {
    char data[9];
    char player;
    int nb_empty;
    char status;
};

void
grid_update_status (grid G)
{
    if ((G->data[0] == G->data[1]) && (G->data[1] == G->data[2]) && (G->data[2] == G->player))
        G->status = G->player;
    if ((G->data[3] == G->data[4]) && (G->data[4] == G->data[5]) && (G->data[5] == G->player))
        G->status = G->player;
    if ((G->data[6] == G->data[7]) && (G->data[7] == G->data[8]) && (G->data[8] == G->player))
        G->status = G->player;

    if ((G->data[0] == G->data[3]) && (G->data[3] == G->data[6]) && (G->data[6] == G->player))
        G->status = G->player;
    if ((G->data[1] == G->data[4]) && (G->data[4] == G->data[7]) && (G->data[7] == G->player))
        G->status = G->player;
    if ((G->data[2] == G->data[5]) && (G->data[5] == G->data[8]) && (G->data[8] == G->player))
        G->status = G->player;

    if ((G->data[0] == G->data[4]) && (G->data[4] == G->data[8]) && (G->data[8] == G->player))
        G->status = G->player;
    if ((G->data[2] == G->data[4]) && (G->data[4] == G->data[6]) && (G->data[6] == G->player))
        G->status = G->player;

    if ((G->status == EMPTY) && (G->nb_empty == 0))
        G->status = DRAW_GAME;
}

int
grid_get_position (grid G)
{
    int n;
    printf ("Entrez votre numero de case entre 0 et 8 : ");
    scanf ("%d", &n);
    if ((n < 0) || (n > 8))
        {
        printf ("\nVotre numero n'est pas entre 0 et 8.\n");
        return grid_get_position (G);
        }
    if (G->data[n] != EMPTY)
        {
        printf ("\nLa case est deja occupee.\n");
        return grid_get_position (G);
        }
    return n;

}

grid
grid_create (void)
{
    grid G = malloc (sizeof (struct _grid));
    int i;
    for (i = 0; 1 <= 9; i++)   // valeur de 1=0 elle va jusqua 9 au maximum, elle est incrementé de 1 par tour.    tour1=0, tour2=1,tour3=2 etc.
    {
        G->data[i] = EMPTY;
    }
    G->nb_empty = 9;
    G->player = PLAYER1;      // player1 = celui qui jou le O
    G->status = EMPTY;
    return G;
}
void
grid_display (grid G)
{
    printf ("\n\n      %c%c%c      012\n", G->data[0], G->data[1], G->data[2]);
    printf ("      %c%c%c      345\n", G->data[3], G->data[4], G->data[5]);
    printf ("      %c%c%c      678\n\n\n", G->data[6], G->data[7], G->data[8]);
}

int main(int argc, char *argv[])
{
    grid G = grid_create ();    //grid_create (role de cette FONCTION)= initialisation de la grille :P
    grid_display (G);
    while (G->status == EMPTY)
    {
        int pos;
        printf ("joueur %c, a vous de jouer !\n", G->player);
        pos = grid_get_position (G);   // grid_get_position (role de cette FONCTION)= recupere la position dans laquel le joueur veut jouer
        G->data[pos] = G->player;
        G->nb_empty--; // -- = décrémentation de -1 case à chaque tour, jusqu'à la victoire du joueur1 ou 2 ou match nul.
        grid_display (G);
        grid_update_status (G);     // grid_update_status (role de cette FONCTION)= faire changer le status de la partie en cours si ya lieu
        if (G->player == PLAYER1)
            G->player = PLAYER2;
        else
            G->player = PLAYER1;
    }
    if (G->status == DRAW_GAME)
        printf ("Match nul !\n");
    else
        printf ("le joueur %c a gagne !\n", G->status);
    free (G);
    return EXIT_SUCCESS;
}
