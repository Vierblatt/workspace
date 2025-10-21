#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

// 函数声明
void shuffle(unsigned int workDeck[][FACES]);
void deal(unsigned int workDeck[][FACES], const char *workFace[], const char *workSuit[]);

int main() {
    // 初始化随机数种子
    srand(time(NULL));
    unsigned int card = 1;
    unsigned int deck[SUITS][FACES];
    const char *face[FACES] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    const char *suit[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    // 初始化牌组
    for (size_t row = 0; row < SUITS; ++row) {
        for (size_t column = 0; column < FACES; ++column) {
            deck[row][column] = card++;
        }
    }

    shuffle(deck);
    deal(deck, face, suit);
}

void shuffle(unsigned int workDeck[][FACES]) {
    for (int i = 0; i < SUITS * FACES; i++) {
        int row1 = rand() % SUITS;
        int col1 = rand() % FACES;
        int row2 = rand() % SUITS;
        int col2 = rand() % FACES;

        // 交换两张牌
        int temp = workDeck[row1][col1];
        workDeck[row1][col1] = workDeck[row2][col2];
        workDeck[row2][col2] = temp;
    }
}

void deal(unsigned int workDeck[][FACES], const char *workFace[], const char *workSuit[]) {
    int dealt[SUITS][FACES] = {0};
    int cardsInRow = 0; // 记录当前行已经打印的牌数
    for (int i = 0; i < SUITS * FACES; i++) {
        int found = 0;
        for (int row = 0; row < SUITS; row++) {
            for (int col = 0; col < FACES; col++) {
                if (!dealt[row][col]) {
                    printf("%5s of %-8s", workFace[col], workSuit[row]);
                    dealt[row][col] = 1;
                    found = 1;
                    cardsInRow++;
                    // 每打印5张牌后换行
                    if (cardsInRow % 5 == 0) {
                        printf("\n");
                    } else {
                        printf("\t");
                    }
                    break;
                }
            }
            if (found) break;
        }
    }
    // 如果最后一行的牌数少于5张，打印换行以结束输出
    if (cardsInRow % 5 != 0) {
        printf("\n");
    }
}
