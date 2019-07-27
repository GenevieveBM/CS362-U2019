#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), callTribute()
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
	int exp_bonus, bonus ;
	
	int hand[5] = { copper, copper, copper, tribute, copper };
	int handCount = 5;
	int handPos = 3;
	
	int deck[5] = { copper, copper, copper, copper, copper };
	int deckCount = 5;
	
	printf(TESTING, "callTribute()");
	
	
	// next player no cards to reveal
	printf(TEST, "next player has no cards to reveal");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[nextPlayer] = 0;											// empty next player's deck
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	
	
	
	// next player has 1 action card to reveal from its deck, discard pile empty
	printf(TEST, "next player has 1 card (Action) to reveal (from deck, discard empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 1;											// set next player's deck count to 1
	state.deck[nextPlayer][0] = baron;											// set next player's deck card to an action card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 2;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][baron]++;
	exp_state.deckCount[nextPlayer]--;
	exp_counts.deck[nextPlayer][baron]--;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 1 treasure card to reveal from its deck, discard pile empty
	printf(TEST, "next player has 1 card (Treasure) to reveal (from deck, discard empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 1;											// set next player's deck count to 1
	state.deck[nextPlayer][0] = gold;											// set next player's deck card to a treasure card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = 2;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][gold]++;
	exp_state.deckCount[nextPlayer]--;
	exp_counts.deck[nextPlayer][gold]--;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 1 victory card to reveal from its deck, discard pile empty
	printf(TEST, "next player has 1 card (Victory) to reveal (from deck, discard empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 1;											// set next player's deck count to 1
	state.deck[nextPlayer][0] = province;										// set next player's deck card to a victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][province]++;
	exp_state.deckCount[nextPlayer]--;
	exp_counts.deck[nextPlayer][province]--;
	exp_state.handCount[player] += 2;
	exp_counts.hand[player][copper] += 2;
	exp_state.deckCount[player] -= 2;
	exp_counts.deck[player][copper] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 1 action-victory card to reveal from its deck, discard pile empty
	printf(TEST, "next player has 1 card (Action-Victory) to reveal (from deck, discard empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 1;											// set next player's deck count to 1
	state.deck[nextPlayer][0] = great_hall;										// set next player's deck card to an action-victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][great_hall]++;
	exp_state.deckCount[nextPlayer]--;
	exp_counts.deck[nextPlayer][great_hall]--;
	exp_state.numActions += 2;
	exp_state.handCount[player] += 2;
	exp_counts.hand[player][copper] += 2;
	exp_state.deckCount[player] -= 2;
	exp_counts.deck[player][copper] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 1 card (Action) to reveal (from discard, deck empty)
	printf(TEST, "next player has 1 card (Action) to reveal (from discard pile, deck empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 0;											// empty next player's deck
	state.discardCount[nextPlayer] = 1;											// set next player's discard pile count to 1
	state.discard[nextPlayer][0] = baron;										// set next player's discard pile card to an action card
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 2;
	// baron card should go from and to discard, so discard unchanged
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	
	
	// next player has 2 cards to reveal, 1 in deck and 1 in discard
	printf(TEST, "next player has 2 cards (Actions) to reveal (1 from deck, 1 from discard pile)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 1;											// set next player's deck count to 1
	state.deck[nextPlayer][0] = baron;											// set next player's deck card to an action card
	state.discardCount[nextPlayer] = 1;											// set next player's discard pile count to 1
	state.discard[nextPlayer][0] = minion;										// set next player's discard pile card to an action card
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 4;
	exp_state.discardCount[nextPlayer]++;
	exp_counts.discard[nextPlayer][baron]++;
	exp_state.deckCount[nextPlayer]--;
	exp_counts.deck[nextPlayer][baron]--;
	// minion card should go from and to discard
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	// next player has 2 cards (Actions) to reveal (2 from discard, deck empty)
	printf(TEST, "next player has 2 cards (Actions) to reveal (2 from discard, deck empty)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 0;											// empty next player's deck
	state.discardCount[nextPlayer] = 2;											// set next player's discard pile count to 2
	state.discard[nextPlayer][0] = baron;										// set next player's discard pile cards to action cards
	state.discard[nextPlayer][1] = minion;
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 4;
	// baron and minion cards should go from and to discard, so discard pile unchanged
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	
	
	
	// next player has 2 cards (Treasures) to reveal (from deck)
	printf(TEST, "next player has 2 cards (Treasures) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = copper;											// set next player's 1st deck card to a treasure card
	state.deck[nextPlayer][0] = silver;											// set next player's 2nd deck card to a treasure card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = 4;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][copper]++;
	exp_counts.discard[nextPlayer][silver]++;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][copper]--;
	exp_counts.deck[nextPlayer][silver]--;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 2 cards (Victory) to reveal (from deck)
	printf(TEST, "next player has 2 cards (Victory) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = duchy;											// set next player's 1st deck card to a victory card
	state.deck[nextPlayer][0] = province;										// set next player's 2nd deck card to a victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][duchy]++;
	exp_counts.discard[nextPlayer][province]++;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][duchy]--;
	exp_counts.deck[nextPlayer][province]--;
	exp_state.handCount[player] += 4;
	exp_counts.hand[player][copper] += 4;
	exp_state.deckCount[player] -=4;
	exp_counts.deck[player][copper] -= 4;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 2 cards (1 Action + 1 Treasure) to reveal (from deck)
	printf(TEST, "next player has 2 cards (1 Action + 1 Treasure) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = ambassador;										// set next player's 1st deck card to an action card
	state.deck[nextPlayer][0] = gold;											// set next player's 2nd deck card to a treasure card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = 2;
	exp_state.numActions += 2;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][ambassador]++;
	exp_counts.discard[nextPlayer][gold]++;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][ambassador]--;
	exp_counts.deck[nextPlayer][gold]--;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 2 cards (1 Action + 1 Victory) to reveal (from deck)
	printf(TEST, "next player has 2 cards (1 Action + 1 Victory) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = mine;											// set next player's 1st deck card to an action card
	state.deck[nextPlayer][0] = province;										// set next player's 2nd deck card to a victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 2;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][mine]++;
	exp_counts.discard[nextPlayer][province]++;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][mine]--;
	exp_counts.deck[nextPlayer][province]--;
	exp_state.handCount[player] += 2;
	exp_counts.hand[player][copper] += 2;
	exp_state.deckCount[player] -= 2;
	exp_counts.deck[player][copper] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has 2 cards (1 Treasure + 1 Victory) to reveal (from deck)
	printf(TEST, "next player has 2 cards (1 Treasure + 1 Victory) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = silver;											// set next player's 1st deck card to a treasure card
	state.deck[nextPlayer][0] = estate;											// set next player's 2nd deck card to a victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = 2;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][silver]++;
	exp_counts.discard[nextPlayer][estate]++;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][silver]--;
	exp_counts.deck[nextPlayer][estate]--;
	exp_state.handCount[player] += 2;
	exp_counts.hand[player][copper] += 2;
	exp_state.deckCount[player] -= 2;
	exp_counts.deck[player][copper] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has duplicate cards (Actions) to reveal (from deck)
	printf(TEST, "next player has duplicate cards (Actions) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = smithy;											// set next player's 1st deck card to an action card
	state.deck[nextPlayer][0] = smithy;											// set next player's 2nd deck card to same action card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.numActions += 2;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][smithy] += 2;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][smithy] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has duplicate cards (Treasures) to reveal (from deck)
	printf(TEST, "next player has duplicate cards (Treasures) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = silver;											// set next player's 1st deck card to a treasure card
	state.deck[nextPlayer][0] = silver;											// set next player's 2nd deck card to same treasure card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = 2;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][silver] += 2;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][silver] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	
	// next player has duplicate cards (Victory) to reveal (from deck)
	printf(TEST, "next player has duplicate cards (Victory) to reveal (from deck)");
	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);						// initialize game/state
	bonus = 0;																	// set bonus to 0
	state.handCount[player] = handCount;										// set player's hand count
	memcpy(state.hand[player], hand, sizeof(int) * handCount);					// set player's hand
	displayCards(player, "hand", state.hand[player], state.handCount[player]);	// display player's hand
	state.deckCount[player] = deckCount;										// set player's deck count
	memcpy(state.deck[player], deck, sizeof(int) * deckCount);					// set player's deck (to know which card is drawn, if any)
	state.deckCount[nextPlayer] = 2;											// set next player's deck count to 2
	state.deck[nextPlayer][1] = duchy;											// set next player's 1st deck card to a victory card
	state.deck[nextPlayer][0] = duchy;											// set next player's 2nd deck card to same victory card
	state.discardCount[nextPlayer] = 0;											// empty next player's discard pile
	
	memcpy(&exp_state, &state, sizeof(struct gameState));						// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);									// save players' initial cards
	
	exp_state.playedCardCount++;												// set expectations
	exp_counts.played[tribute]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][tribute]--;
	exp_bonus = bonus;
	exp_state.discardCount[nextPlayer] += 2;
	exp_counts.discard[nextPlayer][duchy] += 2;
	exp_state.deckCount[nextPlayer] -= 2;
	exp_counts.deck[nextPlayer][duchy] -= 2;
	exp_state.handCount[player] += 2;
	exp_counts.hand[player][copper] += 2;
	exp_state.deckCount[player] -= 2;
	exp_counts.deck[player][copper] -= 2;
	
	callTribute(player, nextPlayer, &state);
	//tributeEffect(&state, handPos, &bonus, player);								// call tributeEffect()
	
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
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	
	
	return 0;
}
