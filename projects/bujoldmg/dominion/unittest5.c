#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), saveCards()
#include "dominion_helpers.h"	// drawCard()

int main()
{
	const int player = 0;
	const int nextPlayer = 1;
	const int numPlayers = 2;
	const int seed = 1;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState exp_state, state;
	struct cardsState exp_counts, counts;
	int result;
	
	int cards[10] = { copper, copper, copper, copper, copper, copper, copper, copper, copper, copper };
	int cardsCount = 10;
	
	int cards1[7] = { estate, copper, silver, mine, gold, baron, gardens };
	int cards1Count = 7;
	
	
	printf(TESTING, "drawCard()");
	
	
	printf(TEST, "empty deck and empty discard pile");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.deckCount[player] = 0;										// empty player's deck
	state.discardCount[player] = 0;										// empty player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	
	result = drawCard(player, &state);									// call drawCard()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED_SAME, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND_SAME, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	printf(TEST, "empty deck but cards in discard pile");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.deckCount[player] = 0;										// empty player's deck
	state.discardCount[player] = cardsCount;							// set player's discard count
	memcpy(state.discard[player], cards, sizeof(int) * cardsCount);		// set player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	
	exp_state.discardCount[player] = 0;									// set expectations
	exp_counts.discard[player][copper] -= cardsCount;
	exp_state.deckCount[player] = cardsCount - 1;
	exp_counts.deck[player][copper] = cardsCount - 1;
	exp_state.handCount[player]++;
	exp_counts.hand[player][copper]++;
	
	result = drawCard(player, &state);									// call drawCard()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	
	printf(TEST_RETURNED_SUCCESS, result == 0 ? "PASS" : "FAIL");
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED_SAME, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	printf(TEST, "cards in deck (empty discard pile)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.deckCount[player] = cardsCount;								// set player's deck count
	memcpy(state.deck[player], cards, sizeof(int) * cardsCount);		// set player's deck
	state.discardCount[player] = 0;										// empty player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	
	exp_state.deckCount[player]--;										// set expectations
	exp_counts.deck[player][copper]--;
	exp_state.handCount[player]++;
	exp_counts.hand[player][copper]++;
	
	result = drawCard(player, &state);									// call drawCard()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	
	printf(TEST_RETURNED_SUCCESS, result == 0 ? "PASS" : "FAIL");
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED_SAME, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	
	printf(TEST, "cards in deck and discard pile");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
	state.deckCount[player] = cardsCount;								// set player's deck count
	memcpy(state.deck[player], cards, sizeof(int) * cardsCount);		// set player's deck
	state.discardCount[player] = cards1Count;							// set player's discard pile count
	memcpy(state.discard[player], cards1, sizeof(int) * cards1Count);	// set player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
	
	exp_state.deckCount[player]--;										// set expectations
	exp_counts.deck[player][copper]--;
	exp_state.handCount[player]++;
	exp_counts.hand[player][copper]++;
	
	result = drawCard(player, &state);									// call drawCard()
	
	saveCards(numPlayers, &state, &counts);								// save players' resulting cards
	
	printf(TEST_RETURNED_SUCCESS, result == 0 ? "PASS" : "FAIL");
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED_SAME, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	return 0;
}
