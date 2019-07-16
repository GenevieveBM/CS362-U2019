#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), endTurn()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), displayCards(), saveCards()

int main ()
{
	const int numPlayers = 2;
	const int seed = 1;
	const int phase = 0;
	const int numActions = 1;
	const int numBuys = 1;
	const int playedCardCount = 0;
	const int handCount = 5;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState exp_state, state;
	struct cardsState exp_counts, counts;
	int totalCounts[treasure_map+1], exp_totalCounts[treasure_map+1];
	int currentPlayer, nextPlayer, coins, combinedCount, exp_combinedCount;
	
	int hand1[4] = { estate, estate, estate, silver };
	int hand1Count = 4;
	
	
	printf(TESTING, "endTurn()");
	
	
	printf(TEST, "end 1st player's turn (with one played card)");
	currentPlayer = 0;
	nextPlayer = 1;
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = currentPlayer;									// set player who is ending its turn
	state.handCount[currentPlayer] = hand1Count;						// set player's hand count
	memcpy(state.hand[currentPlayer], hand1, sizeof(int) * hand1Count);	// set player's hand
	state.playedCardCount = 1;											// set played cards count 
	state.playedCards[0] = mine;										// set played cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	addCardCounts(currentPlayer, &exp_counts, exp_totalCounts, 1);		// save current player's hand + discard + deck + playedCards combined card counts
	exp_combinedCount = state.handCount[currentPlayer] + state.discardCount[currentPlayer] + state.deckCount[currentPlayer] + state.playedCardCount;
	
	endTurn(&state);													// call endTurn()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	addCardCounts(currentPlayer, &counts, totalCounts, 0);				// save current player's hand + discard + deck combined card counts
	combinedCount = state.handCount[currentPlayer] + state.discardCount[currentPlayer] + state.deckCount[currentPlayer];
	
	coins = counts.hand[nextPlayer][copper] + counts.hand[nextPlayer][silver] * 2 + counts.hand[nextPlayer][gold] * 3;
	
	printf(TEST_NUMPLAYERS, state.numPlayers == numPlayers ? "PASS" : "FAIL", state.numPlayers, numPlayers);
	printf(TEST_TURN, state.whoseTurn == nextPlayer ? "PASS" : "FAIL", state.whoseTurn, nextPlayer);
	printf(TEST_PHASE, state.phase == phase ? "PASS" : "FAIL", state.phase, phase);
	printf(TEST_NUMACTIONS, state.numActions == numActions ? "PASS" : "FAIL", state.numActions, numActions);
	printf(TEST_NUMBUYS, state.numBuys == numBuys ? "PASS" : "FAIL", state.numBuys, numBuys);
	printf(TEST_COINS, state.coins == coins ? "PASS" : "FAIL", state.coins, coins);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == playedCardCount ? "PASS" : "FAIL", state.playedCardCount, playedCardCount);
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[currentPlayer] == handCount ? "PASS" : "FAIL", state.handCount[currentPlayer], handCount);				
	printf(TEST_HAND_DISCARD_DECK_COMBINED_COUNT, combinedCount == exp_combinedCount ? "PASS" : "FAIL", combinedCount, exp_combinedCount);
	printf(TEST_HAND_DISCARD_DECK_COMBINED_SAME, checkCardCounts(totalCounts, exp_totalCounts) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == handCount ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], handCount);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	printf(TEST, "end 2nd player's turn (no played cards)");
	currentPlayer = 1;
	nextPlayer = 0;
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.whoseTurn = currentPlayer;									// set player who is ending its turn
	state.playedCardCount = 0;											// empty played cards count
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	addCardCounts(currentPlayer, &exp_counts, exp_totalCounts, 1);		// save current player's hand + discard + deck + playedCards combined card counts
	exp_combinedCount = state.handCount[currentPlayer] + state.discardCount[currentPlayer] + state.deckCount[currentPlayer] + state.playedCardCount;
	
	endTurn(&state);													// call endTurn()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	addCardCounts(currentPlayer, &counts, totalCounts, 0);				// save current player's hand + discard + deck combined card counts
	combinedCount = state.handCount[currentPlayer] + state.discardCount[currentPlayer] + state.deckCount[currentPlayer];
	
	coins = counts.hand[nextPlayer][copper] + counts.hand[nextPlayer][silver] * 2 + counts.hand[nextPlayer][gold] * 3;
	
	printf(TEST_NUMPLAYERS, state.numPlayers == numPlayers ? "PASS" : "FAIL", state.numPlayers, numPlayers);
	printf(TEST_TURN, state.whoseTurn == nextPlayer ? "PASS" : "FAIL", state.whoseTurn, nextPlayer);
	printf(TEST_PHASE, state.phase == phase ? "PASS" : "FAIL", state.phase, phase);
	printf(TEST_NUMACTIONS, state.numActions == numActions ? "PASS" : "FAIL", state.numActions, numActions);
	printf(TEST_NUMBUYS, state.numBuys == numBuys ? "PASS" : "FAIL", state.numBuys, numBuys);
	printf(TEST_COINS, state.coins == coins ? "PASS" : "FAIL", state.coins, coins);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == playedCardCount ? "PASS" : "FAIL", state.playedCardCount, playedCardCount);
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[currentPlayer] == handCount ? "PASS" : "FAIL", state.handCount[currentPlayer], handCount);				
	printf(TEST_HAND_DISCARD_DECK_COMBINED_COUNT, combinedCount == exp_combinedCount ? "PASS" : "FAIL", combinedCount, exp_combinedCount);
	printf(TEST_HAND_DISCARD_DECK_COMBINED_SAME, checkCardCounts(totalCounts, exp_totalCounts) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == handCount ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], handCount);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	return 0;
}