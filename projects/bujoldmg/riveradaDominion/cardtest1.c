#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include "dominion.h"			// enum CARD, struct gameState, initializeGame(), callBaron()
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
	int choice1, hand;
	
	
	// define different hands with different Baron card position
	// and different number and position of Estate cards
	int handCount = 5;
	int handsCount = 5;
	int hands[5][5] = {
		{ baron, copper, copper, copper, copper },	// [0] -> 0 Estate
		{ estate, baron, estate, estate, estate },	// [1] -> 4 Estate
		{ copper, estate, baron, estate, copper },	// [2] -> 2 Estate
		{ copper, copper, copper, baron, estate },	// [3] -> 1 Estate (after Baron)
		{ copper, copper, copper, estate, baron }	// [4] -> 1 Estate (before Baron)
	};												// note: defined so that hand index == Baron card index in hand

	
	printf(TESTING, "callBaron()");


	// gain an Estate card
	printf(CHOICE, "gain an Estate card");
	choice1 = 0;													// set choice to gain an Estate

	memset(&state, 0, sizeof(struct gameState));
	initializeGame(numPlayers, kingdomCards, seed, &state);			// initialize game/state
	bonus = 0;														// set bonus to 0
	state.handCount[player] = handCount;							// set player's hand count
	memcpy(state.hand[player], hands[2], sizeof(int) * handCount);	// set player's hand
	displayCards(player, "hand", hands[2], handCount);				// display player's hand
	
	memcpy(&exp_state, &state, sizeof(struct gameState));			// save initial state
	
	saveCards(numPlayers, &state, &exp_counts);						// save players' initial cards
	
	exp_state.playedCardCount++;									// set expectations
	exp_counts.played[baron]++;
	exp_state.handCount[player]--;
	exp_counts.hand[player][baron]--;
	exp_state.numBuys++;
	exp_bonus = bonus;
	exp_state.discardCount[player]++;
	exp_counts.discard[player][estate]++;
	exp_state.supplyCount[estate]--;
	
	callBaron(choice1, player, &state);
	//baronEffect(choice1, &state, 2, &bonus, player);				// call baronEffect()
	
	saveCards(numPlayers, &state, &counts);							// save players' resulting cards
	
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
	printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
	printf(TEST_SUPPLY, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
	printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
	printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
	printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
	printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);



	// discard Estate card, +4 coins
	printf(CHOICE, "discard an Estate card and gain 4 coins");
	choice1 = 1;															// set choice to discard Estate and gain 4 coins
	for (hand = 0; hand < handsCount; hand++)
	{		
		memset(&state, 0, sizeof(struct gameState));
		initializeGame(numPlayers, kingdomCards, seed, &state);				// initialize game/state
		bonus = 0;															// set bonus to 0
		state.handCount[player] = handCount;								// set player's hand count
		memcpy(state.hand[player], hands[hand], sizeof(int) * handCount);	// set player's hand
		displayCards(player, "hand", hands[hand], handCount);				// display player's hand
		
		memcpy(&exp_state, &state, sizeof(struct gameState));				// save initial state
		
		saveCards(numPlayers, &state, &exp_counts);							// save players' initial cards
		
		if (hand == 0)														// set expectations
		{
			exp_state.supplyCount[estate]--;
			exp_bonus = bonus;
		}
		else
		{
			exp_state.handCount[player]--;
			exp_counts.hand[player][estate]--;
			exp_bonus = 4;
		}
		exp_state.playedCardCount++;
		exp_counts.played[baron]++;
		exp_state.handCount[player]--;
		exp_counts.hand[player][baron]--;
		exp_state.numBuys++;
		exp_state.discardCount[player]++;
		exp_counts.discard[player][estate]++;
		
		callBaron(choice1, player, &state);
		//baronEffect(choice1, &state, hand, &bonus, player);					// call baronEffect()
		
		saveCards(numPlayers, &state, &counts);								// save players' resulting cards
		
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
		printf(TEST_DECK_SAME, checkCardCounts((int*)&counts.deck[player], (int*)&exp_counts.deck[player]) ? "PASS" : "FAIL");
		printf(TEST_SUPPLY, checkCardCounts(state.supplyCount, exp_state.supplyCount) ? "PASS" : "FAIL");
		printf(TEST_HANDCOUNT_PLAYER, state.handCount[nextPlayer] == exp_state.handCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.handCount[nextPlayer], exp_state.handCount[nextPlayer]);
		printf(TEST_HAND_PLAYER_SAME, checkCardCounts((int*)&counts.hand[nextPlayer], (int*)&exp_counts.hand[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
		printf(TEST_DISCARDCOUNT_PLAYER, state.discardCount[nextPlayer] == exp_state.discardCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.discardCount[nextPlayer], exp_state.discardCount[nextPlayer]);
		printf(TEST_DISCARD_PLAYER_SAME, checkCardCounts((int*)&counts.discard[nextPlayer], (int*)&exp_counts.discard[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
		printf(TEST_DECKCOUNT_PLAYER, state.deckCount[nextPlayer] == exp_state.deckCount[nextPlayer] ? "PASS" : "FAIL", nextPlayer, state.deckCount[nextPlayer], exp_state.deckCount[nextPlayer]);
		printf(TEST_DECK_PLAYER_SAME, checkCardCounts((int*)&counts.deck[nextPlayer], (int*)&exp_counts.deck[nextPlayer]) ? "PASS" : "FAIL", nextPlayer);
	}
	
	
	return 0;
}
