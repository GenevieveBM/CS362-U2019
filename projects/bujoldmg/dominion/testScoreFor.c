#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), scoreFor()
#include "dominion_testing.h"	// displayCards()



int main()
{
	const int seed = 1;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState state;
	int numPlayers, score, exp_score;
	
	
	int cards1[5] = { estate, duchy, province, great_hall, estate };	// 5c 12p
	int cards1Count = 5;
	
	int cards2[4] = { copper, copper, gardens, copper };				// 4c +1 per 10 cards
	int cards2Count = 4;
	
	int cards3[6] = { remodel, smithy, village, baron, minion, gardens };// 6c +1 per 10 cards
	int cards3Count = 6;
	
	int cards4[9] = { gardens, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag };	// 9c +1 per 10 cards
	int cards4Count  = 9;
	
	int cards5[5] = { adventurer, council_room, feast, mine, curse };	// 5c -1p
	int cards5Count = 5;
	
	int cards6[4] = { copper, silver, curse, gold };					// 4c -1p
	int cards6Count = 4;

	int cards7[3] = { curse, treasure_map, curse };						// 3c -2p
	int cards7Count = 3;
	
	int cards8[6] = { estate, copper, duchy, silver, estate, gold };	// 6c 5p
	int cards8Count = 6;
	
	
	printf(TESTING, "scoreFor()");
	
	
	printf(TEST, "score for player 0 (current player) - test all victory cards except gardens and curse");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[0] = cards1Count;									// set players' hand, deck and discard count and contents
	memcpy(state.hand[0], cards1, sizeof(int) * cards1Count);
	state.deckCount[0] = cards1Count;									// player 0: hand (12pts), deck (12pts), discard (12pts), played (1pts) -> 37pts
	memcpy(state.deck[0], cards1, sizeof(int) * cards1Count);
	state.discardCount[0] = cards1Count;
	memcpy(state.discard[0], cards1, sizeof(int) * cards1Count);
	exp_score = 37;														// set expectation
	
	displayCards(0, "hand", state.hand[0], state.handCount[0]);
	displayCards(0, "deck", state.deck[0], state.deckCount[0]);
	displayCards(0, "discard", state.discard[0], state.discardCount[0]);
	displayCards(0, "played", state.playedCards, state.playedCardCount);
	
	score = scoreFor(0, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test all victory cards except gardens and curse");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = cards1Count;									// set other players' hand, deck and discard count and contents
	memcpy(state.hand[1], cards1, sizeof(int) * cards1Count);
	state.deckCount[1] = cards1Count;
	memcpy(state.deck[1], cards1, sizeof(int) * cards1Count);			// player 1: hand (12pts), deck (12pts), discard (12pts) -> 36pts
	state.discardCount[1] = cards1Count;
	memcpy(state.discard[1], cards1, sizeof(int) * cards1Count);
	exp_score = 36;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test gardens card");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = cards2Count;									// set other players' hand, deck and discard count and contents
	memcpy(state.hand[1], cards2, sizeof(int) * cards2Count);
	state.deckCount[1] = cards3Count;
	memcpy(state.deck[1], cards3, sizeof(int) * cards3Count);			// player 1: hand (+1/10 Cards), deck (+1/10 Cards), discard (+1/10 Cards) -> 3pts
	state.discardCount[1] = cards4Count;								//			 total -> 4 + 6 + 9 = 19 cards
	memcpy(state.discard[1], cards4, sizeof(int) * cards4Count);
	exp_score = 3;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test curse card");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = cards5Count;									// set other players' hand, deck and discard count and contents
	memcpy(state.hand[1], cards5, sizeof(int) * cards5Count);
	state.deckCount[1] = cards6Count;
	memcpy(state.deck[1], cards6, sizeof(int) * cards6Count);			// player 1: hand (-1pt), deck (-1pt), discard (-2pts) -> -4pts
	state.discardCount[1] = cards7Count;
	memcpy(state.discard[1], cards7, sizeof(int) * cards7Count);
	exp_score = -4;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test points in hand only (empty deck and discard)");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = cards8Count;									// set other players' hand, deck and discard count and contents
	memcpy(state.hand[1], cards8, sizeof(int) * cards8Count);
	state.deckCount[1] = 0;												// player 1: hand (5pts), deck (empty), discard (empty) -> 5pts
	state.discardCount[1] = 0;
	exp_score = 5;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test points in deck only (empty hand and discard)");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = 0;												// set other players' hand, deck and discard count and contents
	state.deckCount[1] = cards8Count;
	memcpy(state.deck[1], cards8, sizeof(int) * cards8Count);			// player 1: hand (empty), deck (5pts), discard (empty) -> 5pts
	state.discardCount[1] = 0;
	exp_score = 5;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	printf(TEST, "score for player 1 (other player) - test points in discard only (empty hand and deck)");
	numPlayers = 2;														// set number of players
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = 0;												// set current player
	state.playedCardCount = 1;											// set played cards count to 1
	state.playedCards[0] = great_hall;									// set played card
	state.handCount[1] = 0;												// set other players' hand, deck and discard count and contents
	state.deckCount[1] = 0;
	state.discardCount[1] = cards8Count;								// player 1: hand (empty), deck (empty), discard (5pts) -> 5pts
	memcpy(state.discard[1], cards8, sizeof(int) * cards8Count);
	exp_score = 5;														// set expectation
	
	displayCards(1, "hand", state.hand[1], state.handCount[1]);
	displayCards(1, "deck", state.deck[1], state.deckCount[1]);
	displayCards(1, "discard", state.discard[1], state.discardCount[1]);
	
	score = scoreFor(1, &state);										// call scoreFor()
	
	printf(" %s -- score = %d, expected = %d\n", score == exp_score ? "PASS" : "FAIL", score, exp_score);
	
	
	
	return 0;
}