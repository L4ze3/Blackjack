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

struct Card deck[DECK_SIZE];
struct Card player_hand[MAX_CARDS];
struct Card dealer_hand[MAX_CARDS];

/* Function prototypes */
void initialize_deck(struct Card *deck);
void shuffle(struct Card *deck, int size);
void deal_card(struct Card *hand, struct Card *deck, int *track);
void print_hand(struct Card *hand, int track);
int menu();
int eval(struct Card *hand, int track);


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

void shuffle(struct Card *deck, int size)
{
    int rng;
    for (int i = size - 1; i > 0; i--) {
        rng = rand() % (i + 1);
        struct Card tmp = deck[i];
        deck[i] = deck[rng];
        deck[rng] = tmp;
    }
}

void deal_card(struct Card *hand, struct Card *deck, int *track)
{
    hand[*track] = deck[*track];
    //if (hand == player_hand)
        *track = *track + 1;
}

void print_hand(struct Card *hand, int track)
{
    for (int i = 0; i < track; i++) {
        //printf("%s:\n", (hand == player_hand) ? "Your Hand" : "Dealers Hand" );
        printf("%s%s ", hand[i].rank, hand[i].suit);
    }
    printf("\nValue: %d\n", eval(hand, track));
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

int eval(struct Card *hand, int track)
{
    int sum = 0;
    int num_aces = 0;

    for (int i = 0; i < track; i++) {
        if (strcmp(hand[i].rank, "A") == 0) {
            num_aces++;
        } else if (strcmp(hand[i].rank, "J") == 0 || strcmp(hand[i].rank, "Q") == 0 || strcmp(hand[i].rank, "K") == 0) {
            sum += 10;
        } else {
            sum += atoi(hand[i].rank);
        }
    }

    while (num_aces > 0) {
        if (sum + 11 <= 21) {
            sum += 11;
        } else {
            sum += 1;
        }
        num_aces--;
    }
    
    return sum;
}

int main(void)
{
    srand(time(NULL));

    int bet, action;
    int track = 0; /* Tracks the amount of dealt cards */
    bool gameloop = true;

    system("clear");

    initialize_deck(deck);
    shuffle(deck, DECK_SIZE);

    deal_card(player_hand, deck, &track);
    deal_card(dealer_hand, deck, &track);    
    deal_card(player_hand, deck, &track);



    while (gameloop) {

        print_hand(player_hand, track);
        printf("\n\n");
        print_hand(dealer_hand, track);

        action = menu();
        if (action == 1)
            deal_card(player_hand, deck, &track);
        else if (action == 2)
            while (eval(dealer_hand, track) <= 17)
                deal_card(dealer_hand, deck, &track);

    }
        
    return 0;
}
