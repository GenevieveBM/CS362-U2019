#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), callMinion()
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
	int exp_bonus, bonus;
	int choice1, choice2;
	
	int hand1[1] = { minion };
	int hand1Count = 1;
	int hand1Pos = 0;
	
	int hand2[2] = { copper, minion };
	int hand2Count = 2;
	int hand2Pos = 1;
	
	int hand3[3] = { copper, minion, copper };
	int hand3Count = 3;
	int hand3Pos = 1;
	
	int hand4[4] = { copper, copper, minion, copper };
	int hand4Count = 4;
	int hand4Pos = 2;
	
	int hand5[5] = { copper, copper, copper, minion, copper };
	int hand5Count = 5;
	int hand5Pos = 3;
	
	int deck[5] = { copper, copper, copper, copper, copper };
	int deckCount = 5;
	
	
	printf(TESTING, "callMinion()");

	
	// gain 2 coins
	printf(CHOICE, "gain 2 coins");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand5Count;										// set player's hand count
	memcpy(state.hand[player], hand5, sizeof(int) * hand5Count);				// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	choice1 = 1;																// set choice to gain 2 coins
	choice2 = 0;																// "cancel" choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = 2;
	
	callMinion(player, choice1, choice2, &state, hand5Pos);
	//minionEffect(choice1, choice2, &state, hand5Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
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
	
	
	
	// discard hand, draw 4 cards - players 1 card in hand
	printf(CHOICE, "discard hand, draw 4 cards - players 1 card in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand1Count;										// set player's hand count
	memcpy(state.hand[player], hand1, sizeof(int) * hand1Count);				// set player's hand
	displayCards(player, "initial hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn)
	state.handCount[nextPlayer] = hand1Count;									// set next player's hand count
	memcpy(state.hand[nextPlayer], hand1, sizeof(int) * hand1Count);			// set next player's hand
	state.deckCount[nextPlayer] = deckCount;									// set next player's deck count
	memcpy(state.deck[nextPlayer], deck, sizeof(int) * deckCount);				// set next player's deck (to know which card is drawn)
	choice1 = 0;																// "cancel" choice to gain 2 coins
	choice2 = 1;																// set choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = bonus;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -= 4;
	exp_counts.deck[player][copper] -= 4;
	
	callMinion(player, choice1, choice2, &state, hand1Pos);
	//minionEffect(choice1, choice2, &state, hand1Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD_SAME, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	displayCards(nextPlayer, "initial hand", hand1, hand1Count);
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);



	// discard hand, draw 4 cards - players 2 cards in hand
	printf(CHOICE, "discard hand, draw 4 cards - players 2 cards in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand2Count;										// set player's hand count
	memcpy(state.hand[player], hand2, sizeof(int) * hand2Count);				// set player's hand
	displayCards(player, "initial hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn)
	state.handCount[nextPlayer] = hand2Count;									// set next player's hand count
	memcpy(state.hand[nextPlayer], hand2, sizeof(int) * hand2Count);			// set next player's hand
	state.deckCount[nextPlayer] = deckCount;									// set next player's deck count
	memcpy(state.deck[nextPlayer], deck, sizeof(int) * deckCount);				// set next player's deck (to know which card is drawn)
	choice1 = 0;																// "cancel" choice to gain 2 coins
	choice2 = 1;																// set choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = bonus;
	exp_state.discardCount[player]++;
	exp_counts.discard[player][copper]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][copper]--;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -= 4;
	exp_counts.deck[player][copper] -= 4;
	
	callMinion(player, choice1, choice2, &state, hand2Pos);
	//minionEffect(choice1, choice2, &state, hand2Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	displayCards(nextPlayer, "initial hand", hand2, hand2Count);
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// discard hand, draw 4 cards - players 3 cards in hand
	printf(CHOICE, "discard hand, draw 4 cards - players 3 cards in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand3Count;										// set player's hand count
	memcpy(state.hand[player], hand3, sizeof(int) * hand3Count);				// set player's hand
	displayCards(player, "initial hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn)
	state.handCount[nextPlayer] = hand3Count;									// set next player's hand count
	memcpy(state.hand[nextPlayer], hand3, sizeof(int) * hand3Count);			// set next player's hand
	state.deckCount[nextPlayer] = deckCount;									// set next player's deck count
	memcpy(state.deck[nextPlayer], deck, sizeof(int) * deckCount);				// set next player's deck (to know which card is drawn)
	choice1 = 0;																// "cancel" choice to gain 2 coins
	choice2 = 1;																// set choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = bonus;
	exp_state.discardCount[player] += 2;
	exp_counts.discard[player][copper] += 2;
	exp_state.handCount[player] -= 2;;
	exp_counts.hand[player][copper] -= 2;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -= 4;
	exp_counts.deck[player][copper] -= 4;
	
	callMinion(player, choice1, choice2, &state, hand3Pos);
	//minionEffect(choice1, choice2, &state, hand3Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	displayCards(nextPlayer, "initial hand", hand3, hand3Count);
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// discard hand, draw 4 cards - players 4 cards in hand
	printf(CHOICE, "discard hand, draw 4 cards - players 4 cards in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand4Count;										// set player's hand count
	memcpy(state.hand[player], hand4, sizeof(int) * hand4Count);				// set player's hand
	displayCards(player, "initial hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn)
	state.handCount[nextPlayer] = hand4Count;									// set next player's hand count
	memcpy(state.hand[nextPlayer], hand4, sizeof(int) * hand4Count);			// set next player's hand
	state.deckCount[nextPlayer] = deckCount;									// set next player's deck count
	memcpy(state.deck[nextPlayer], deck, sizeof(int) * deckCount);				// set next player's deck (to know which card is drawn)
	choice1 = 0;																// "cancel" choice to gain 2 coins
	choice2 = 1;																// set choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = bonus;
	exp_state.discardCount[player] += 3;
	exp_counts.discard[player][copper] += 3;
	exp_state.handCount[player] -= 3;;
	exp_counts.hand[player][copper] -= 3;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -= 4;
	exp_counts.deck[player][copper] -= 4;
	
	callMinion(player, choice1, choice2, &state, hand4Pos);
	//minionEffect(choice1, choice2, &state, hand4Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	displayCards(nextPlayer, "initial hand", hand4, hand4Count);
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// discard hand, draw 4 cards - players 5 cards in hand
	printf(CHOICE, "discard hand, draw 4 cards - players 5 cards in hand");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = hand5Count;										// set player's hand count
	memcpy(state.hand[player], hand5, sizeof(int) * hand5Count);				// set player's hand
	displayCards(player, "initial hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn)
	state.handCount[nextPlayer] = hand5Count;									// set next player's hand count
	memcpy(state.hand[nextPlayer], hand5, sizeof(int) * hand5Count);			// set next player's hand
	state.deckCount[nextPlayer] = deckCount;									// set next player's deck count
	memcpy(state.deck[nextPlayer], deck, sizeof(int) * deckCount);				// set next player's deck (to know which card is drawn)
	choice1 = 0;																// "cancel" choice to gain 2 coins
	choice2 = 1;																// set choice to discard and draw 4 cards
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[minion]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][minion]--;
	exp_state.numActions += 1;
	exp_bonus = bonus;
	exp_state.discardCount[player] += 4;
	exp_counts.discard[player][copper] += 4;
	exp_state.handCount[player] -= 4;
	exp_counts.hand[player][copper] -= 4;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -= 4;
	exp_counts.deck[player][copper] -= 4;
	exp_state.discardCount[nextPlayer] += 5;
	exp_counts.discard[nextPlayer][copper] += 4;
	exp_counts.discard[nextPlayer][minion] += 1;
	exp_state.handCount[nextPlayer] -= 5;
	exp_counts.hand[nextPlayer][copper] -= 4;
	exp_counts.hand[nextPlayer][minion] -= 1;
	exp_state.handCount[nextPlayer] += 4;
	exp_counts.hand[nextPlayer][copper] += 4;
	exp_state.deckCount[nextPlayer] -= 4;
	exp_counts.deck[nextPlayer][copper] -= 4;
	
	callMinion(player, choice1, choice2, &state, hand5Pos);
	//minionEffect(choice1, choice2, &state, hand5Pos, &bonus, player);			// call minionEffect()
	
	saveCards(numPlayers, &state, &counts);										// save players' resulting cards
	
	printf(TEST_NUMACTIONS, state.numActions == exp_state.numActions ? "PASS" : "FAIL", state.numActions, exp_state.numActions);
	printf(TEST_NUMBUYS, state.numBuys == exp_state.numBuys ? "PASS" : "FAIL", state.numBuys, exp_state.numBuys);
	printf(TEST_BONUS, bonus == exp_bonus ? "PASS" : "FAIL", bonus, exp_bonus);
	printf(TEST_PLAYEDCOUNT, state.playedCardCount == exp_state.playedCardCount ? "PASS" : "FAIL", state.playedCardCount, exp_state.playedCardCount);
	printf(TEST_PLAYED, checkCardCounts(counts.played, exp_counts.played) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT, state.handCount[player] == exp_state.handCount[player] ? "PASS" : "FAIL", state.handCount[player], exp_state.handCount[player]);				
	printf(TEST_HAND, checkCardCounts((int*)&counts.hand[player], (int*)&exp_counts.hand[player]) ? "PASS" : "FAIL");
	printf(TEST_DISCARDCOUNT, state.discardCount[player] == exp_state.discardCount[player] ? "PASS" : "FAIL", state.discardCount[player], exp_state.discardCount[player]);
	printf(TEST_DISCARD, checkCardCounts((int*)&counts.discard[player], (int*)&exp_counts.discard[player]) ? "PASS" : "FAIL");
	printf(TEST_DECKCOUNT, state.deckCount[player] == exp_state.deckCount[player] ? "PASS" : "FAIL", state.deckCount[player], exp_state.deckCount[player]);
	printf(TEST_DECK, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY_SAME, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	displayCards(nextPlayer, "initial hand", hand5, hand5Count);
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	return 0;
}