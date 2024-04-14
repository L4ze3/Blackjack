#include <stdio.h>
#include <stdlib.h>
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
void deal_card(struct Card *player_hand, struct Card *deck, int *track);

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

void deal_card(struct Card *player_hand, struct Card *deck, int *track)
{
     player_hand[*track] = deck[*track];
     *track = *track + 1;
}

int main(void)
{
    srand(time(NULL));
    struct Card deck[DECK_SIZE];
    struct Card player_hand[MAX_CARDS];
    struct Card dealer_hand[MAX_CARDS];

    int bet;
    int track = 0; /* Tracks the amount of dealt cards */

    system("clear");

    printf("Place bet: ");
    scanf("%d", &bet);

    initialize_deck(deck);
    shuffle(deck, DECK_SIZE);

    deal_card(player_hand, deck, &track);

    printf("%d\n", track);

    for (int i = 0; i < track; i++) {
        printf("%s%s\n", player_hand[i].rank, player_hand[i].suit);
    }
   
    return 0;
}
