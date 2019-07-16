#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), mineEffect()
#include "dominion_testing.h"	// struct cardsState, checkCardCounts(), displayCards(), saveCards()

int main()
{
	const int player = 0;
	const int nextPlayer = 1;
	const int numPlayers = 2;
	const int seed = 1;
	int kingdomCards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron };
	struct gameState exp_state, state;
	struct cardsState exp_counts, counts;
	int choice1, choice2, result;
	
	int hand1[5] = { copper, mine, copper, copper, copper };
	int hand1Count = 5;
	int hand1Pos = 1;
	int hand1Trade = 2;
	
	int hand2[5] = { mine, copper, estate, copper, silver };
	int hand2Count = 5;
	int hand2Pos = 0;
	int hand2Trade = 4;
	int hand2Victory = 2;
	
	
	printf(TESTING, "mineEffect()");
	
	
	// trade copper for silver
	printf(TEST, "trade copper for silver");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Trade;														// set index of copper to be traded
	choice2 = silver;															// set card to be gain in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[mine]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][mine]--;
	exp_state.handCount[player]--;		// trashed, not added anywhere
	exp_counts.hand[player][copper]--;
	exp_state.handCount[player]++;
	exp_counts.hand[player][silver]++;
	exp_state.supplyCount[silver]--;
	
	
	mineEffect(choice1, choice2, &state, hand1Pos, player);						// call mineEffect()
	
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
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// trade silver for gold
	printf(TEST, "trade silver for gold");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand2Trade;														// set index of silver to be traded
	choice2 = gold;																// set card to be gain in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[mine]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][mine]--;
	exp_state.handCount[player]--;		// trashed, not added anywhere
	exp_counts.hand[player][silver]--;
	exp_state.handCount[player]++;
	exp_counts.hand[player][gold]++;
	exp_state.supplyCount[gold]--;
	
	
	mineEffect(choice1, choice2, &state, hand2Pos, player);						// call mineEffect()
	
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
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// trade copper for gold
	printf(TEST, "trade copper for gold");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand1Trade;														// set index of copper to be traded
	choice2 = gold;															// set card to be gain in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	result = mineEffect(choice1, choice2, &state, hand1Pos, player);			// call mineEffect()
	
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
	
	
	
	// trade invalid card (not treasure)
	printf(TEST, "trade/trash a victory card instead of a treasure card");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand2Victory;														// set index of a victory card in hand
	choice2 = gold;																// set card to be gain in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	result = mineEffect(choice1, choice2, &state, hand2Pos, player);			// call mineEffect()
	
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
	
	
	
	
	// choose invalid card to get (not treasure)
	printf(TEST, "trade/gain a victory card instead of a treasure card");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = hand2Trade;														// set index of silver to be traded
	choice2 = province;															// set card to be gain in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	result = mineEffect(choice1, choice2, &state, hand2Pos, player);			// call mineEffect()
	
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
	
	
	// invalid choice1 -> card index
	printf(TEST, "trade/trash a card outside of hand (position outside of hand array)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = MAX_HAND;															// set index of card outside hand array
	choice2 = gold;																// set card to be gained in the trade
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	result = mineEffect(choice1, choice2, &state, hand2Pos, player);			// call mineEffect()
	
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