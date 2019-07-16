#ifndef DOMINION_TESTING_H
#define DOMINION_TESTING_H

#include "dominion.h"

#define TESTING						"\n**********TESTING %s**********\n"
#define CHOICE						"\n*CHOICE: %s\n"
#define TEST						"\n*TEST: %s\n"

#define TEST_TURN					" %s -- whoseTurn = %d, expected = %d\n"
#define TEST_PHASE					" %s -- phase = %d, expected = %d\n"
#define TEST_COINS					" %s -- coins = %d, expected = %d\n"

#define TEST_NUMPLAYERS				" %s -- numPlayers = %d, expected = %d\n"
#define TEST_NUMACTIONS 			" %s -- numActions = %d, expected = %d\n"
#define TEST_NUMBUYS 				" %s -- numBuys = %d, expected = %d\n"
#define TEST_BONUS					" %s -- bonus = %d, expected = %d\n"

#define TEST_PLAYEDCOUNT			" %s -- playedCardCount = %d, expected = %d\n"
#define TEST_HANDCOUNT				" %s -- handCount = %d, expected = %d\n"
#define TEST_DISCARDCOUNT			" %s -- discardCount = %d, expected = %d\n"
#define TEST_DECKCOUNT				" %s -- deckCount = %d, expected = %d\n"

#define TEST_PLAYED					" %s -- playedCards content correct\n"
#define TEST_HAND					" %s -- hand contents correct\n"
#define TEST_DISCARD				" %s -- discard pile contents correct\n"
#define TEST_DECK					" %s -- deck contents correct\n"
#define TEST_SUPPLY					" %s -- supply piles content correct\n"
#define TEST_HAND_DECK_INIT			" %s -- hand + deck contents == 3 Estate + 7 Copper\n"

#define TEST_PLAYED_SAME			" %s -- playedCards content unchanged\n"
#define TEST_HAND_SAME				" %s -- hand contents unchanged\n"
#define TEST_DISCARD_SAME			" %s -- discard pile contents unchanged\n"
#define TEST_DECK_SAME				" %s -- deck contents unchanged\n"
#define TEST_SUPPLY_SAME			" %s -- supply piles unchanged\n"

#define TEST_HANDCOUNT_PLAYER		" %s -- player %d handCount = %d, expected = %d\n"
#define TEST_DISCARDCOUNT_PLAYER	" %s -- player %d discardCount = %d, expected = %d\n"
#define TEST_DECKCOUNT_PLAYER		" %s -- player %d deckCount = %d, expected = %d\n"

#define TEST_HAND_PLAYER			" %s -- player %d hand contents correct\n"
#define TEST_DISCARD_PLAYER			" %s -- player %d discard pile contents correct\n"
#define TEST_DECK_PLAYER			" %s -- player %d deck contents correct\n"

#define TEST_HAND_PLAYER_SAME		" %s -- player %d hand contents unchanged\n"
#define TEST_DISCARD_PLAYER_SAME	" %s -- player %d discard pile contents unchanged\n"
#define TEST_DECK_PLAYER_SAME		" %s -- player %d deck contents unchanged\n"	

#define TEST_HAND_DISCARD_DECK_COMBINED_COUNT	" %s -- handCount + discardCount + deckCount = %d, expected = %d\n"
#define TEST_HAND_DISCARD_DECK_COMBINED_SAME	" %s -- hand + discard + deck combined content unchanged\n"

#define TEST_RETURNED_FAILURE		" %s -- returned < 0\n"
#define TEST_RETURNED_SUCCESS		" %s -- returned 0\n"


struct cardsState {
	int hand[MAX_PLAYERS][treasure_map+1];
	int deck[MAX_PLAYERS][treasure_map+1];
	int discard[MAX_PLAYERS][treasure_map+1];
	int played[treasure_map+1];
};

void getCardCounts(int* cards, int numCards, int* counts);
void addCardCounts(int, struct cardsState*, int*, int);
int checkCardCounts(int* set1, int* set2);
void displayCards(int player, char* location, int* cards, int cardCount);
void saveCards(int numPlayers, struct gameState* state, struct cardsState* counts);

#endif
