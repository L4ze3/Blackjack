#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define MAX_CARDS 11 /* Maximum amount of cards per Hand */

enum Suits { HEARTS, CLUBS, DIAMONDS, SPADES };
enum Ranks { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

const char *Suit[] = { "♥", "♣", "♦", "♠" };
const char *Rank[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

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
void deal_card(struct Card *hand, int *hand_count, struct Card *deck, int *deck_position);
void print_hand(struct Card *hand, int hand_count, bool hide_first);
int menu();
int eval(struct Card *hand, int hand_count);
bool check_win(struct Card *player, int player_count, struct Card *dealer, int dealer_count);

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

void deal_card(struct Card *hand, int *hand_count, struct Card *deck, int *deck_position)
{
    hand[*hand_count] = deck[*deck_position];
    (*hand_count)++;
    (*deck_position)++;
}

void print_hand(struct Card *hand, int hand_count, bool hide_first)
{
    for (int i = 0; i < hand_count; i++) {
        if (hide_first && i == 0) {
            printf("?? ");
        } else {
            printf("%s%s ", hand[i].rank, hand[i].suit);
        }
    }
    if (!hide_first) {
        printf("\nValue: %d", eval(hand, hand_count));
    }
    printf("\n");
}

int menu()
{
    int action;
    printf("Choose an action:\n");
    printf("Hit\t(1)\n");
    printf("Stand\t(2)\n");
    printf("> ");
    scanf("%d", &action);
    return action;
}

int eval(struct Card *hand, int hand_count)
{
    int sum = 0;
    int num_aces = 0;

    for (int i = 0; i < hand_count; i++) {
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

bool check_win(struct Card *player, int player_count, struct Card *dealer, int dealer_count)
{
    int player_value = eval(player, player_count);
    int dealer_value = eval(dealer, dealer_count);

    if (player_value > 21) {
        printf("Player busts!\n");
        return false;
    } else if (dealer_value > 21) {
        printf("Dealer busts! Player wins!\n");
        return true;
    } else if (player_value > dealer_value) {
        printf("Player wins!\n");
        return true;
    } else {
        printf("Dealer wins!\n");
        return false;
    }
}

int main(void)
{
    srand(time(NULL));

    int bet;
    int player_count = 0;
    int dealer_count = 0;
    int deck_position = 0;
    bool gameloop = true;
    bool player_turn = true;

    system("clear");

    initialize_deck(deck);
    shuffle(deck, DECK_SIZE);

    deal_card(player_hand, &player_count, deck, &deck_position);
    deal_card(dealer_hand, &dealer_count, deck, &deck_position);
    deal_card(player_hand, &player_count, deck, &deck_position);
    deal_card(dealer_hand, &dealer_count, deck, &deck_position);

    while (gameloop) {
        system("clear");

        printf("Your Hand:\n");
        print_hand(player_hand, player_count, false);
        printf("\nDealer's Hand:\n");
        print_hand(dealer_hand, dealer_count, player_turn);

        if (player_turn) {
            int action = menu();

            if (action == 1) {
                deal_card(player_hand, &player_count, deck, &deck_position);
                if (eval(player_hand, player_count) > 21) {
                    player_turn = false;
                }
            } else if (action == 2) {
                player_turn = false;
            }
        } else {
            while (eval(dealer_hand, dealer_count) <= 17) {
                deal_card(dealer_hand, &dealer_count, deck, &deck_position);
            }
            gameloop = false;
        }
    }
    
    printf("\nFinal Hands:\n");
    printf("Your Hand:\n");
    print_hand(player_hand, player_count, false);
    printf("\nDealer's Hand:\n");
    print_hand(dealer_hand, dealer_count, false);

    check_win(player_hand, player_count, dealer_hand, dealer_count);

    return 0;
}

