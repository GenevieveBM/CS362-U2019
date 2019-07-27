#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), ambassadorEffect()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), displayCards(), saveCards()

int main()
{
	const int player = 0;
	const int nextPlayer = 1;
	const int numPlayers = 2;
	const int seed = 1;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, ambassador };
	struct gameState exp_state, state;
	struct cardsState exp_counts, counts;
	int choice1, choice2, result;
	
	int hand1[5] = { copper, copper, ambassador, copper, copper };
	int hand1Count = 5;
	int hand1Pos = 2;
	int hand1Reveal = 1;
	
	int hand2[5] = { copper, ambassador, silver, silver, gold };
	int hand2Count = 5;
	int hand2Pos = 1;
	int hand2Reveal = 0;
	
	int hand3[5] = { copper, ambassador, silver, ambassador, estate };
	int hand3Count = 5;
	int hand3Pos = 1;
	int hand3Reveal = 3; 
	
	
	printf(TESTING, "ambassadorEffect()");
	
	
	// return 0 copies to supply
	printf(CHOICE, "reveal Copper - return 0 copies to supply");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Reveal;														// reveal Copper
	choice2 = 0;																// return 0 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[ambassador]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][ambassador]--;
	exp_state.supplyCount[hand1[choice1]]--;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][hand1[choice1]]++;

	ambassadorEffect(choice1, choice2, &state, hand1Pos, player);				// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// return 1 copy to supply
	printf(CHOICE, "reveal Copper - return 1 copy to supply");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Reveal;														// reveal Copper
	choice2 = 1;																// return 1 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[ambassador]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][ambassador]--;
	exp_state.supplyCount[hand1[choice1]]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][hand1[choice1]]--;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][hand1[choice1]]++;
	exp_state.supplyCount[hand1[choice1]]--;

	ambassadorEffect(choice1, choice2, &state, hand1Pos, player);				// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// return 2 copies to supply
	printf(CHOICE, "reveal Copper - return 2 copies to supply");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Reveal;														// reveal Copper
	choice2 = 2;																// return 2 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[ambassador]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][ambassador]--;
	exp_state.supplyCount[hand1[choice1]] += 2;
	exp_state.handCount[player] -= 2;
	exp_counts.hand[player][hand1[choice1]] -=2;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][hand1[choice1]]++;
	exp_state.supplyCount[hand1[choice1]]--;

	ambassadorEffect(choice1, choice2, &state, hand1Pos, player);				// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// return 3 copies to supply 
	printf(CHOICE, "reveal Copper - return 3 copies to supply");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Reveal;														// reveal Copper
	choice2 = 3;																// return 3 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	// expect no change as can't return 3 copies

	result = ambassadorEffect(choice1, choice2, &state, hand1Pos, player);		// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
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
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	// return 2 copies when only one in hand
	printf(CHOICE, "reveal Copper - return 2 copies to supply when only 1 Copper in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand2Reveal;														// reveal Copper
	choice2 = 2;																// return 2 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards

	// expect no change as can't return 2 when only 1 in hand
	
	result = ambassadorEffect(choice1, choice2, &state, hand2Pos, player);		// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
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
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	// return played Ambassador card to supply
	printf(CHOICE, "reveal Ambassador - return 1 copy to supply (but revealing played Ambassador card)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Pos;															// reveal Ambassador
	choice2 = 1;																// return 1 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	// expect no change as can't return played Ambassador card
	
	result = ambassadorEffect(choice1, choice2, &state, hand1Pos, player);		// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
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
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	
	// reveal Ambassador (not the played Ambassador) return 2 copy to supply
	printf(CHOICE, "reveal Ambassador (not played Ambassador) - return 2 copy to supply (played Ambassador + other Ambassador)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand3Count;										// set player's hand count
	memcpy(state.hand[player], hand3, sizeof(int) * hand3Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand3Reveal;														// reveal Ambassador
	choice2 = 2;																// return 1 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	// expect no change as can't return 1st/played Ambassador
	
	result = ambassadorEffect(choice1, choice2, &state, hand3Pos, player);		// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
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
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	// reveal card outside of hand
	printf(CHOICE, "reveal invalid card (outside hand array) - return 1 copy to supply");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = MAX_HAND;															// reveal card outside hand array
	choice2 = 1;																// return 1 to supply
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	// expect no change as can't return an invalid card
	
	result = ambassadorEffect(choice1, choice2, &state, hand1Pos, player);		// call ambassadorEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
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
	printf(TEST_RETURNED_FAILURE, result < 0 ? "PASS" : "FAIL");
	
	
	return 0;
}
