#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52

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

void deal_card()
{
     
}

int main(void)
{
    srand(time(NULL));
    struct Card deck[DECK_SIZE];

    int bet;
    int tracker;
    
    system("clear");

    printf("Place bet: ");
    scanf("%d", &bet);

    
    initialize_deck(deck);

    for (int i = 0; i < DECK_SIZE; i++) {
        printf("%s%s\n", deck[i].rank, deck[i].suit);
    }

    shuffle(deck, DECK_SIZE);
   
    return 0;
}
