#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

void shuffle(unsigned int workDeck[][FACES]);
void deal(unsigned int workDeck[][FACES],const char *workFace[],const char *workSuit[]);

int main()
{
    srand(time(NULL));

    unsigned int card=1;
    unsigned int deck[CARDS][FACES]={0};

    const char *suit[SUITS]={"Hearts","Diamonds", "Clubs", "Spades"};
    const char *face[FACES]={"Ace", "DEUCE", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    for(size_t row=0; row<CARDS; ++row)
    {
        for(size_t column=0; column<FACES; ++column){
            deck[row][column]=card++;
    }
        }

    shuffle(deck);
    deal(deck, face, suit);

}