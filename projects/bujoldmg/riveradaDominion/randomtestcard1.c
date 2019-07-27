#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include <math.h>				// floor()
#include "dominion.h"			// enum CARD, struct gameState, callBaron(), MAX_HAND, MAX_PLAYERS
#include "rngs.h"
#include "dominion_testing_random.h"

void report(struct gameState* exp, struct gameState* post, struct cardsState* exp_counts, struct cardsState* post_counts, int exp_bonus, int bonus)
{
	int i;
	
	if (exp->numActions != post->numActions)
		printf(TEST_NUMACTIONS, "", post->numActions, exp->numActions);
	
	if (exp->numBuys != post->numBuys)
		printf(TEST_NUMBUYS, "", post->numBuys, exp->numBuys);
	
	if (exp_bonus != bonus)
		printf(TEST_BONUS, "", bonus, exp_bonus);
	
	if (!checkCardCounts(exp->supplyCount, post->supplyCount))
		printf(TEST_SUPPLY, "");
	
	if (exp->playedCardCount != post->playedCardCount)
		printf(TEST_PLAYEDCOUNT, "", post->playedCardCount, exp->playedCardCount);
	
	if (!checkCardCounts(exp_counts->played, post_counts->played))
		printf(TEST_PLAYED, "");
	
	for (i = 0; i < exp->numPlayers; i++)
	{
		if (exp->handCount[i] != post->handCount[i])
			printf(TEST_HANDCOUNT_PLAYER, "", i, post->handCount[i], exp->handCount[i]);
		
		if (!checkCardCounts((int*)&exp_counts->hand[i], (int*)&post_counts->hand[i]))
			printf(TEST_HAND_PLAYER, "", i);
		
		if (exp->deckCount[i] != post->deckCount[i])
			printf(TEST_DECKCOUNT_PLAYER, "", i, post->deckCount[i], exp->deckCount[i]);
		
		if (!checkCardCounts((int*)&exp_counts->deck[i], (int*)&post_counts->deck[i]))
			printf(TEST_DECK_PLAYER, "", i);
		
		if (exp->discardCount[i] != post->discardCount[i])
			printf(TEST_DISCARDCOUNT_PLAYER, "", i, post->discardCount[i], exp->discardCount[i]);
		
		if (!checkCardCounts((int*)&exp_counts->discard[i], (int*)&post_counts->discard[i]))
			printf(TEST_DISCARD_PLAYER, "", i);
	}
}

int asserttrue(struct gameState* exp, struct gameState* post, struct cardsState* exp_counts, struct cardsState* post_counts, int exp_bonus, int bonus)
{	
	int i;
	
	if (exp->numActions != post->numActions ||
		exp->numBuys != post->numBuys ||
		exp_bonus != bonus ||
		!checkCardCounts(exp->supplyCount, post->supplyCount) ||
		exp->playedCardCount != post->playedCardCount ||
		!checkCardCounts(exp_counts->played, post_counts->played))
		return 0;
	
	for (i = 0; i < exp->numPlayers; i++)
	{
		if (exp->handCount[i] != post->handCount[i] ||
			!checkCardCounts((int*)&exp_counts->hand[i], (int*)&post_counts->hand[i]) ||
			exp->deckCount[i] != post->deckCount[i] ||
			!checkCardCounts((int*)&exp_counts->deck[i], (int*)&post_counts->deck[i]) ||
			exp->discardCount[i] != post->discardCount[i] ||
			!checkCardCounts((int*)&exp_counts->discard[i], (int*)&post_counts->discard[i]))
			return 0;
	}
	
	return 1;	
}

void checkBaronEffect(int choice, struct gameState* post, int handPos, int* bonus, int player)
{
	int exp_bonus;
	struct cardsState exp_counts, post_counts;
	
	struct gameState pre, exp;
	memcpy (&pre, post, sizeof(struct gameState));
	memcpy (&exp, post, sizeof(struct gameState));
	
	exp_bonus = *bonus;
	
	saveCards(pre.numPlayers, &pre, &exp_counts);
	
	callBaron(choice, player, post);
	//baronEffect(choice, post, handPos, bonus, player);
	
	saveCards(pre.numPlayers, post, &post_counts);
	
	if (choice == 1 && exp_counts.hand[player][estate])
	{
		exp.handCount[player]--;
		exp_counts.hand[player][estate]--;
		exp_bonus += 4;
	}
	else
	{
		exp.supplyCount[estate]--;
	}
	exp.playedCardCount++;
	exp_counts.played[pre.hand[player][handPos]]++;
	exp.handCount[player]--;
	exp_counts.hand[player][pre.hand[player][handPos]]--;
	exp.numBuys++;
	exp.discardCount[player]++;
	exp_counts.discard[player][estate]++;
	
	if (asserttrue(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus))
	{
		printf(" PASS\n");
	}
	else
	{
		printf(" FAIL\n");
		printf(" Choice: %d, number of players = %d, current player = %d\n", choice, exp.numPlayers, exp.whoseTurn);
		report(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus);
	}
}

int main()
{
	int n, i, j, choice, handPos, bonus, player;
	struct gameState state;
	
	SelectStream(2);
	PutSeed(3);
	
	printf("\n*****Testing callBaron()*****\n");
	
	for (n = 0; n < 500; n++)
	{
		state.numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 2;		// 2 to MAX_PLAYERS
		player = floor(Random() * state.numPlayers);					// 0 to numPlayers-1
		
		for (i = 0; i <= treasure_map; i++)
		{
			state.supplyCount[i] = floor(Random() * MAX_DECK) + 1;		// have at least 1 card in supply
		}
		
		state.whoseTurn = player;
		state.phase = 0;
		state.numActions = floor(Random() * 500);						// 0 to 499
		state.numBuys = floor(Random() * 500);							// 0 to 499
		state.coins = floor(Random() * 500);							// 0 to 499
		state.playedCardCount = floor(Random() * (MAX_DECK - 1));		// leave at least 1 space for played card
		
		for (i = 0; i < state.numPlayers; i++)
		{
			if (i == player)
			{
				state.handCount[i] = floor(Random() * MAX_HAND) / 3 + 1;// at least one card to play
			}
			else
			{
				state.handCount[i] = floor(Random() * MAX_HAND) / 3;
			}
			
			state.deckCount[i] = floor(Random() * MAX_DECK) / 3;
			state.discardCount[i] = floor(Random() * MAX_DECK) / 3;		// (space to gain or discard an Estate card for current player)	
			
			for (j = 0; j < state.handCount[i]; j++)
			{
				state.hand[i][j] = floor(Random() * (treasure_map+1));
			}
		
			for (j = 0; j < state.deckCount[i]; j++)
			{
				state.deck[i][j] = floor(Random() * (treasure_map+1));
			}
		
			for (j = 0; j < state.discardCount[i]; j++)
			{
				state.discard[player][i] = floor(Random() * (treasure_map+1));
			}
		}
		
		choice = floor(Random() * 2);									// choice 0 or 1
		handPos = floor(Random() * state.handCount[player]);			// 0 to player's handCount-1
		bonus = floor(Random() * 500);									// 0 to 499
		
		state.hand[player][handPos] = baron;							// set played card to Baron
		
		printf("\nTest %d: ", n);
		checkBaronEffect(choice, &state, handPos, &bonus, player);
	}
	
	printf("\n**Testing callBaron() done**\n");
	
	return 0;
}