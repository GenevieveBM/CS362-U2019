#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), getWinners()
#include "dominion_testing.h"	// displayCards()

int compareWinners(int [MAX_PLAYERS], int [MAX_PLAYERS]);

int main()
{
	const int seed = 1;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState state;
	int i, numPlayers;
	int winners[MAX_PLAYERS], exp_winners[MAX_PLAYERS];
	
	
	int cards1[3] = { copper, silver, gold };							// 3c 0p
	int cards1Count = 3;

	int cards2[4] = { adventurer, council_room, feast, mine };			// 4c 0p
	int cards2Count = 4;

	int cards3[5] = { estate, duchy, province, great_hall, estate };	// 5c 12p
	int cards3Count = 5;

	int cards4[5] = { curse, curse, curse, curse, curse };				// 5c -5p
	int cards4Count = 5;

	int cards5[5] = { copper, copper, gardens, copper, copper };		// 5c +1 per 10 cards
	int cards5Count = 5;

	int cards6[5] = { remodel, smithy, village, baron, minion };		// 5c 0p
	int cards6Count = 5;

	int cards7[6] = { estate, copper, duchy, silver, estate, gold };	// 6c 5p
	int cards7Count = 6;

	int cards8[9] = { steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };	// 9c 0p
	int cards8Count  = 9;
	
	
	printf(TESTING, "getWinners()");
	
	
	printf(TEST, "2 players - player 0: 17pts, player 1: -5pts");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set player ending the game
	state.playedCardCount = 0;											// set played cards count to 0
	state.handCount[0] = cards3Count;									// set players' hand, deck and discard count and contents
	memcpy(state.hand[0], cards3, sizeof(int) * cards3Count);
	state.deckCount[0] = cards7Count;									// player 0: hand (12pts), deck (5pts), discard (empty, 0pts) -> 17pts
	memcpy(state.deck[0], cards7, sizeof(int) * cards7Count);
	state.discardCount[0] = 0;
	state.handCount[1] = cards6Count;									// player 1: hand (0pts), deck (empty, 0pts), discard (-5pts) -> -5pts
	memcpy(state.hand[1], cards6, sizeof(int) * cards6Count);
	state.deckCount[1] = 0;
	state.discardCount[1] = cards4Count;
	memcpy(state.discard[1], cards4, sizeof(int) * cards4Count);
	
	displayCards(0, "hand", state.hand[0], state.handCount[0]);
	displayCards(0, "deck", state.deck[0], state.deckCount[0]);
	displayCards(0, "discard", state.discard[0], state.discardCount[0]);
	displayCards(0, "played", state.playedCards, state.playedCardCount);
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	for (i = 0; i < MAX_PLAYERS; i++)									// set expectation
	{
		if (i == 0)
			exp_winners[i] = 1;
		else 
			exp_winners[i] = 0;
	}
	
	getWinners(winners, &state);										// call getWinners()
	
	printf("Results = [ %d", winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", winners[i]);
	}
	printf(" ], expected = [ %d", exp_winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", exp_winners[i]);
	}
	printf(" ]\n");
	printf(" %s -- player 0 wins\n", compareWinners(winners, exp_winners) ? "PASS" : "FAIL");
	
	
	
	printf(TEST, "3 players - player 0: 0pts, player 1: 1pts, player 2: 1pts");
	numPlayers = 3;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 1;												// set player ending the game
	state.playedCardCount = 0;											// set played cards count to 0
	state.handCount[0] = 0;												// set players' hand, deck and discard count and contents
	state.deckCount[0] = cards2Count;
	memcpy(state.deck[0], cards2, sizeof(int) * cards2Count);			// player 0: hand (empty, 0pts), deck (0pts), discard (0pts) -> 0pts
	state.discardCount[0] = cards8Count;
	memcpy(state.discard[0], cards8, sizeof(int) * cards8Count);
	state.handCount[1] = cards1Count;									// player 1: hand (0pts), deck (0pts), discard (+1/10 Cards) -> 1pts
	memcpy(state.hand[1], cards1, sizeof(int) * cards1Count);			//           total -> 17 cards
	state.deckCount[1] = cards8Count;
	memcpy(state.deck[1], cards8, sizeof(int) * cards8Count);
	state.discardCount[1] = cards5Count;
	memcpy(state.discard[1], cards5, sizeof(int) * cards5Count);
	state.handCount[2] = cards6Count;									// player 2: hand (0pts), deck (+1/10 Cards), discard (0pts) -> 1pts
	memcpy(state.hand[2], cards6, sizeof(int) * cards6Count);			//           total -> 14 cards
	state.deckCount[2] = cards5Count;
	memcpy(state.deck[2], cards5, sizeof(int) * cards5Count);
	state.discardCount[2] = cards2Count;
	memcpy(state.discard[2], cards2, sizeof(int) * cards2Count);
	
	displayCards(0, "hand", state.hand[0], state.handCount[0]);
	displayCards(0, "deck", state.deck[0], state.deckCount[0]);
	displayCards(0, "discard", state.discard[0], state.discardCount[0]);
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	displayCards(1, "played", state.playedCards, state.playedCardCount);
	displayCards(2, "hand", state.hand[2], state.handCount[2]);
	displayCards(2, "deck", state.deck[2], state.deckCount[2]);
	displayCards(2, "discard", state.discard[2], state.discardCount[2]);
	
	for (i = 0; i < MAX_PLAYERS; i++)									// set expectation
	{
		if (i == 2)
			exp_winners[i] = 1;
		else 
			exp_winners[i] = 0;
	}
	
	getWinners(winners, &state);										// call getWinners()
	
	printf("Results = [ %d", winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", winners[i]);
	}
	printf(" ], expected = [ %d", exp_winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", exp_winners[i]);
	}
	printf(" ]\n");
	printf(" %s -- player 2 wins (as less number of turns)\n", compareWinners(winners, exp_winners) ? "PASS" : "FAIL");
	
	
	
	printf(TEST, "2 players - player 0: 5pts, player 1: 5pts");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 1;												// set player ending the game
	state.playedCardCount = 0;											// set played cards count to 0
	state.handCount[0] = cards6Count;									// set players' hand, deck and discard count and contents
	memcpy(state.hand[0], cards6, sizeof(int) * cards6Count);
	state.deckCount[0] = cards7Count;									// player 0: hand (0pts), deck (5pts), discard (0pts) -> 5pts
	memcpy(state.deck[0], cards7, sizeof(int) * cards7Count);
	state.discardCount[0] = cards1Count;
	memcpy(state.discard[0], cards1, sizeof(int) * cards1Count);
	state.handCount[1] = cards2Count;									// player 1: hand (0pts), deck (empty, 0pts), discard (5pts) -> 5pts
	memcpy(state.hand[1], cards2, sizeof(int) * cards2Count);
	state.deckCount[1] = 0;
	state.discardCount[1] = cards7Count;
	memcpy(state.discard[1], cards7, sizeof(int) * cards7Count);
	
	displayCards(0, "hand", state.hand[0], state.handCount[0]);
	displayCards(0, "deck", state.deck[0], state.deckCount[0]);
	displayCards(0, "discard", state.discard[0], state.discardCount[0]);
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	displayCards(1, "played", state.playedCards, state.playedCardCount);
	
	for (i = 0; i < MAX_PLAYERS; i++)									// set expectation
	{
		if (i == 0 || i == 1)
			exp_winners[i] = 1;
		else 
			exp_winners[i] = 0;
	}
	
	getWinners(winners, &state);										// call getWinners()
	
	printf("Results = [ %d", winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", winners[i]);
	}
	printf(" ], expected = [ %d", exp_winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", exp_winners[i]);
	}
	printf(" ]\n");
	printf(" %s -- tie, both players win\n", compareWinners(winners, exp_winners) ? "PASS" : "FAIL");
	
	
	
	printf(TEST, "2 players - player 0: 0pts, player 1: 1pts");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 1;												// set player ending the game
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = smithy;									// set played card
	state.handCount[0] = cards6Count;									// set players' hand, deck and discard count and contents
	memcpy(state.hand[0], cards6, sizeof(int) * cards6Count);
	state.deckCount[0] = cards1Count;									// player 0: hand (0pts), deck (0pst), discard (0pts) -> 0pts
	memcpy(state.deck[0], cards1, sizeof(int) * cards1Count);
	state.discardCount[0] = cards8Count;
	memcpy(state.discard[0], cards8, sizeof(int) * cards8Count);
	state.handCount[1] = cards5Count;									// player 1: hand (+1/10 Cards), deck (empty, 0pts), discard (0pts), played (0pts) -> 1pts
	memcpy(state.hand[1], cards5, sizeof(int) * cards5Count);			//			 total -> 5 + 0 + 4 + 1 = 10 cards
	state.deckCount[1] = 0;
	state.discardCount[1] = cards2Count;
	memcpy(state.discard[1], cards2, sizeof(int) * cards2Count);
	
	displayCards(0, "hand", state.hand[0], state.handCount[0]);
	displayCards(0, "deck", state.deck[0], state.deckCount[0]);
	displayCards(0, "discard", state.discard[0], state.discardCount[0]);
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	displayCards(1, "played", state.playedCards, state.playedCardCount);
	
	for (i = 0; i < MAX_PLAYERS; i++)									// set expectation
	{
		if (i == 1)
			exp_winners[i] = 1;
		else 
			exp_winners[i] = 0;
	}
	
	getWinners(winners, &state);										// call getWinners()
	
	printf("Results = [ %d", winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", winners[i]);
	}
	printf(" ], expected = [ %d", exp_winners[0]);
	for (i = 1; i < MAX_PLAYERS; i++)									// set expectation
	{
		printf(", %d", exp_winners[i]);
	}
	printf(" ]\n");
	printf(" %s -- player 1 wins\n", compareWinners(winners, exp_winners) ? "PASS" : "FAIL");
	
	
	
	
	return 0;
}

int compareWinners(int winners[MAX_PLAYERS], int exp_winners[MAX_PLAYERS])
{
	int i;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (winners[i] != exp_winners[i])
			return 0;
	}
	return 1;
}
