#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define MAX_CARDS 11 /* Maximum amount of cards per Hand */

enum Suits { HEARTS, CLUBS, DIAMONDS, SPADES };
enum Ranks { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

const char Suit[4][5] = {
    { "♥" },
    { "♣" },
    { "♦" },
    { "♠" },
};

const char Rank[13][5] = {
    { "A" },
    { "2" },
    { "3" },
    { "4" },
    { "5" },
    { "6" },
    { "7" },
    { "8" },
    { "9" },
    { "10" },
    { "J" },
    { "Q" },
    { "K" },
};

struct Card {
    char suit[10];
    char rank[10];
};

void initialize_deck(struct Card *deck);
void shuffle(struct Card *deck, int size);
void swap(struct Card *x, struct Card *y);
void deal_card(struct Card *hand, struct Card *deck, int *track);
void print_hand(struct Card *hand, int track);
int menu();

void initialize_deck(struct Card *deck)
{
    int index = 0;

    for (enum Suits suit = HEARTS; suit <= SPADES; suit++) {
        for (enum Ranks rank = ACE; rank <= KING; rank++) {
             strcpy(deck[index].rank, Rank[rank]);
             strcpy(deck[index].suit, Suit[suit]);
             index++;
        }
    }
}

void swap(struct Card *x, struct Card *y)
{
    struct Card tmp = *x;
    *x = *y;
    *y = tmp;
}

void shuffle(struct Card *deck, int size)
{
    int rng;
    for (int i = size - 1; i > 0; i--) {
        rng = rand() % (i + 1);
        swap(&deck[i], &deck[rng]);
    }
}

void deal_card(struct Card *hand, struct Card *deck, int *track)
{
    hand[*track] = deck[*track];
    *track = *track + 1;
}

void print_hand(struct Card *hand, int track)
{
    for (int i = 0; i < track; i++) {
        printf("\033[47m%s%s \033[0m", hand[i].rank, hand[i].suit);
    }
    printf("\n");
}

int menu()
{
    int action;
    printf("Choose an action:\n");
    printf("Hit\t(1)\n");
    printf("Stand\t(2)\n");
    printf("\033[35m> \033[0m");
    scanf("%d", &action);
    return action;
}

int main(void)
{
    srand(time(NULL));
    struct Card deck[DECK_SIZE];
    struct Card player_hand[MAX_CARDS];
    struct Card dealer_hand[MAX_CARDS];

    int bet, action;
    int track = 0; /* Tracks the amount of dealt cards */
    bool gameloop = true;

    system("clear");

    initialize_deck(deck);
    shuffle(deck, DECK_SIZE);

    while (gameloop) {
        action = menu();
        if (action == 1)
            deal_card(player_hand, deck, &track);
        else if (action == 2)
            gameloop = false;
        
        print_hand(player_hand, track);
    }
        
    return 0;
}
