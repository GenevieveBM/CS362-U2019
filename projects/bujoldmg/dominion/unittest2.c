#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), shuffle()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), displayCards(), saveCards()

int sameCardOrder(int*, int*, int);

int main()
{
	const int player = 0;
	const int numPlayers = 2;
	const int seed1 = 1;
	const int seed2 = 2;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState state1, state2;
	struct cardsState exp_counts, counts1, counts2;
	int i, result1, result2;
	
	int decksCount = 6;
	int decks[6][5] = {
		{     -1,     -1,     -1,     -1,     -1 },	// [0] -> 0 cards
		{ curse,      -1,     -1,     -1,     -1 },	// [1] -> 1 card
		{ estate, copper,     -1,     -1,     -1 },	// [2] -> 2 cards
		{ duchy,  silver,  feast,     -1,     -1 },	// [3] -> 3 cards
		{ province, gold, gardens,  mine,     -1 },	// [4] -> 4 cards
		{ minion, smithy,  baron, copper, estate }	// [5] -> 5 cards
	};
	
	
	printf(TESTING, "shuffle()");
	
	
	for (i = 0; i < decksCount; i++)
	{
		printf("\n*TEST: deckCount = %d\n", i);
	
		memset(&state1, 0, sizeof(struct gameState));
		initializeGame(numPlayers, kingdomCards, seed1, &state1);
		state1.deckCount[player] = i;
		memcpy(state1.deck[player], decks[i], sizeof(int) * i);

		memset(&state2, 0, sizeof(struct gameState));
		initializeGame(numPlayers, kingdomCards, seed2, &state2);
		state2.deckCount[player] = i;
		memcpy(state2.deck[player], decks[i], sizeof(int) * i);
	
		displayCards(player, "deck", decks[i], i);
		saveCards(numPlayers, &state1, &exp_counts);
	
		result1 = shuffle(player, &state1);
		result2 = shuffle(player, &state2);
	
		saveCards(numPlayers, &state1, &counts1);
		saveCards(numPlayers, &state2, &counts2);
	
		if (i == 0)
		{
			printf(TEST_RETURNED_FAILURE, result1 < 0 && result2 < 0 ? "PASS" : "FAIL");
		}
		else
		{
			printf("Seed = %d\n", seed1);
			displayCards(player, "shuffled deck", state1.deck[player], state1.deckCount[player]);
			printf(TEST_DECKCOUNT, state1.deckCount[player] == i ? "PASS" : "FAIL", state1.deckCount[player], i);
			printf(TEST_DECK_SAME, checkCardCounts((int*)&counts1.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");

			printf("Seed = %d\n", seed2);
			displayCards(player, "shuffled deck", state2.deck[player], state2.deckCount[player]);
			printf(TEST_DECKCOUNT, state2.deckCount[player] == i ? "PASS" : "FAIL", state2.deckCount[player], i);
			printf(TEST_DECK_SAME, checkCardCounts((int*)&counts2.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
			
			if (i > 2)	// 1 - 2 cards not enough to see shuffle differences
			{
				printf("Seed = %d VS Seed = %d\n", seed1, seed2);
				printf(" %s -- card order different\n", !sameCardOrder((int*)&state1.deck[player], (int*)&state2.deck[player], i) &&
														!sameCardOrder((int*)&state1.deck[player], decks[i], i) &&
														!sameCardOrder((int*)&state2.deck[player], decks[i], i) ? "PASS" : "FAIL");
			}
		}
	}
	
	
	return 0;
}

int sameCardOrder(int* cards1, int* cards2, int cardCount)
{
	int i;
	
	for (i = 0; i < cardCount; i++)
	{
		if (cards1[i] != cards2[i])
			return 0;
	}
	
	return 1;
}