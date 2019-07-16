#include <stdio.h>				// printf()
#include <string.h>				// memset()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), saveCards()

void setExpCounts(int, int*);
void testResults(int, int, struct gameState*, struct cardsState*, int [treasure_map+1]);

int main()
{
	int numPlayers, result;
	int seed = 1; 
	int kingdomCards1[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int kingdomCards2[10] = { village, baron, minion, steward, tribute, ambassador, cutpurse, salvager, sea_hag, treasure_map };
	int kingdomCards3[10] = { village, baron, minion, steward, tribute, ambassador, cutpurse, salvager, village, treasure_map };
	int exp_supplyCounts1[treasure_map+1] = { 0 };
	exp_supplyCounts1[silver] = 40;
	exp_supplyCounts1[gold] = 30;
	exp_supplyCounts1[adventurer] = 10;
	exp_supplyCounts1[council_room] = 10;
	exp_supplyCounts1[feast] = 10;
	exp_supplyCounts1[mine] = 10;
	exp_supplyCounts1[remodel] = 10;
	exp_supplyCounts1[smithy] = 10;
	exp_supplyCounts1[village] = 10;
	exp_supplyCounts1[baron] = 10;
	exp_supplyCounts1[minion] = -1;
	exp_supplyCounts1[steward] = -1;
	exp_supplyCounts1[tribute] = -1;
	exp_supplyCounts1[ambassador] = -1;
	exp_supplyCounts1[cutpurse] = -1;
	exp_supplyCounts1[embargo] = -1;
	exp_supplyCounts1[outpost] = -1;
	exp_supplyCounts1[salvager] = -1;
	exp_supplyCounts1[sea_hag] = -1;
	exp_supplyCounts1[treasure_map] = -1;
	int exp_supplyCounts2[treasure_map+1] = { 0 };
	exp_supplyCounts2[silver] = 40;
	exp_supplyCounts2[gold] = 30;
	exp_supplyCounts2[adventurer] = -1;
	exp_supplyCounts2[council_room] = -1;
	exp_supplyCounts2[feast] = -1;
	exp_supplyCounts2[mine] = -1;
	exp_supplyCounts2[remodel] = -1;
	exp_supplyCounts2[smithy] = -1;
	exp_supplyCounts2[village] = 10;
	exp_supplyCounts2[baron] = 10;
	exp_supplyCounts2[minion] = 10;
	exp_supplyCounts2[steward] = 10;
	exp_supplyCounts2[tribute] = 10;
	exp_supplyCounts2[ambassador] = 10;
	exp_supplyCounts2[cutpurse] = 10;
	exp_supplyCounts2[embargo] = -1;
	exp_supplyCounts2[outpost] = -1;
	exp_supplyCounts2[salvager] = 10;
	exp_supplyCounts2[sea_hag] = 10;
	exp_supplyCounts2[treasure_map] = 10;
	struct gameState state;
	struct cardsState counts;
	
	
	printf(TESTING, "initializeGame()");
	
	
	printf(TEST, "numPlayers = 1");
	numPlayers = 1;
	memset(&state, 0, sizeof(struct gameState));
	
	result = initializeGame(numPlayers, kingdomCards1, seed, &state);
	
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	printf(TEST, "numPlayers = 2\n       kingdomCards = adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall");
	numPlayers = 2;
	memset(&state, 0, sizeof(struct gameState));
	
	setExpCounts(numPlayers, exp_supplyCounts1);
	
	result = initializeGame(numPlayers, kingdomCards1, seed, &state);
	
	saveCards(numPlayers, &state, &counts);
	
	testResults(numPlayers, result, &state, &counts, exp_supplyCounts1);
	
	
	
	printf(TEST, "numPlayers = 3\n       kingdomCards = adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall");
	numPlayers = 3;
	memset(&state, 0, sizeof(struct gameState));
	
	setExpCounts(numPlayers, exp_supplyCounts1);
	
	result = initializeGame(numPlayers, kingdomCards1, seed, &state);
	
	saveCards(numPlayers, &state, &counts);
	
	testResults(numPlayers, result, &state, &counts, exp_supplyCounts1);
	
	
	
	printf(TEST, "numPlayers = 4\n       kingdomCards = adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall");
	numPlayers = 4;
	memset(&state, 0, sizeof(struct gameState));
	
	setExpCounts(numPlayers, exp_supplyCounts1);
	
	result = initializeGame(numPlayers, kingdomCards1, seed, &state);
	
	saveCards(numPlayers, &state, &counts);
	
	testResults(numPlayers, result, &state, &counts, exp_supplyCounts1);
	
	
	
	printf(TEST, "numPlayers > MAX_PLAYERS");
	numPlayers = MAX_PLAYERS + 1;
	memset(&state, 0, sizeof(struct gameState));
	
	result = initializeGame(numPlayers, kingdomCards1, seed, &state);
	
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	printf(TEST, "numPlayers = 2\n       kingdomCards = village, baron, minion, steward, tribute, ambassador, cutpurse, salvager, village, treasure_map");
	numPlayers = 2;
	memset(&state, 0, sizeof(struct gameState));
	
	setExpCounts(numPlayers, exp_supplyCounts2);
	exp_supplyCounts2[gardens] = -1;
	exp_supplyCounts2[great_hall] = -1;
	
	result = initializeGame(numPlayers, kingdomCards2, seed, &state);
	
	saveCards(numPlayers, &state, &counts);
	
	testResults(numPlayers, result, &state, &counts, exp_supplyCounts2);
	
	
	
	printf(TEST, "numPlayers = 2\n       kingdomCards = village, baron, minion, steward, tribute, ambassador, cutpurse, salvager, sea_hag, treasure_map (duplicate village)");
	numPlayers = 2;
	memset(&state, 0, sizeof(struct gameState));
	
	result = initializeGame(numPlayers, kingdomCards3, seed, &state);
	
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	return 0;
}

void setExpCounts(int numPlayers, int* counts)
{
	counts[copper] = 60 - (7 * numPlayers);
	
	if (numPlayers == 2)
	{
		counts[curse] = 10;
		counts[estate] = 8;
		counts[duchy] = 8;
		counts[province] = 8;
		counts[gardens] = 8;
		counts[great_hall] = 8;
	}
	else if (numPlayers <= MAX_PLAYERS)
	{
		counts[curse] = 30;
		counts[estate] = 12;
		counts[duchy] = 12;
		counts[province] = 12;
		counts[gardens] = 12;
		counts[great_hall] = 12;
		
		if (numPlayers == 3)
			counts[curse] = 20;
	}
	else
	{
		counts[copper] = -1;
		counts[curse] = -1;
		counts[estate] = -1;
		counts[duchy] = -1;
		counts[province] = -1;
		counts[gardens] = -1;
		counts[great_hall] = -1;
	}
}

void testResults(int numPlayers, int result, struct gameState* state, struct cardsState* counts, int exp_supplyCounts[treasure_map+1])
{
	int i;
	const int firstPlayer = 0;
	const int phase = 0;
	const int numActions = 1;
	const int numBuys = 1;
	const int playedCardCount = 0;
	const int handCount = 5;
	const int deckCount = 5;
	const int discardCount = 0;
	
	printf(TEST_RETURNED_SUCCESS, result == 0 ? "PASS" : "FAIL");
	printf(TEST_NUMPLAYERS, state->numPlayers == numPlayers ? "PASS" : "FAIL", state->numPlayers, numPlayers);
	printf(TEST_TURN, state->whoseTurn == firstPlayer ? "PASS" : "FAIL", state->whoseTurn, firstPlayer);
	printf(TEST_PHASE, state->phase == phase ? "PASS" : "FAIL", state->phase, phase);
	printf(TEST_NUMACTIONS, state->numActions == numActions ? "PASS" : "FAIL", state->numActions, numActions);
	printf(TEST_NUMBUYS, state->numBuys == numBuys ? "PASS" : "FAIL", state->numBuys, numBuys);
	printf(TEST_COINS, state->coins == counts->hand[firstPlayer][copper] ? "PASS" : "FAIL", state->coins, counts->hand[firstPlayer][copper]);
	printf(TEST_PLAYEDCOUNT, state->playedCardCount == playedCardCount ? "PASS" : "FAIL", state->playedCardCount, playedCardCount);
	printf(TEST_SUPPLY, checkCardCounts(state->supplyCount, exp_supplyCounts) ? "PASS" : "FAIL");
	for (i = 0; i < numPlayers; i++)
	{
		printf("Player %d\n", i);
		printf(TEST_HANDCOUNT, state->handCount[i] == handCount ? "PASS" : "FAIL", state->handCount[i], handCount);
		printf(TEST_DECKCOUNT, state->deckCount[i] == deckCount ? "PASS" : "FAIL", state->deckCount[i], deckCount);
		printf(TEST_DISCARDCOUNT, state->discardCount[i] == discardCount ? "PASS" : "FAIL", state->discardCount[i], discardCount);
		printf(TEST_HAND_DECK_INIT, (counts->hand[i][estate] + counts->deck[i][estate] == 3) && (counts->hand[i][copper] + counts->deck[i][copper] == 7) ? "PASS" : "FAIL");
	}
}
