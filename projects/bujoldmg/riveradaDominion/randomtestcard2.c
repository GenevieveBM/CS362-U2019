#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include <math.h>				// floor()
#include "dominion.h"			// enum CARD, struct gameState, callMinion(), MAX_HAND, MAX_PLAYERS
#include "rngs.h"
#include "dominion_testing_random.h"

void report(struct gameState* exp, struct gameState* post, struct cardsState* exp_counts, struct cardsState* post_counts, int exp_bonus, int bonus)
{
	int i;
	int post_totalCounts[treasure_map+1], exp_totalCounts[treasure_map+1];
	
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
		addCardCounts(i, exp_counts, exp_totalCounts, i == exp->whoseTurn ? 1 : 0);	// get total card counts for player (if current player count played cards)
		addCardCounts(i, post_counts, post_totalCounts, i == exp->whoseTurn ? 1 : 0);
		
		if (exp->handCount[i] != post->handCount[i])
			printf(TEST_HANDCOUNT_PLAYER, "", i, post->handCount[i], exp->handCount[i]);
		
		if (!checkCardCounts(exp_totalCounts, post_totalCounts))
			printf(TEST_ALLCARDS_PLAYER, "", i);
	}
}

int asserttrue(struct gameState* exp, struct gameState* post, struct cardsState* exp_counts, struct cardsState* post_counts, int exp_bonus, int bonus)
{	
	int i;
	int post_totalCounts[treasure_map+1], exp_totalCounts[treasure_map+1];
	
	if (exp->numActions != post->numActions ||
		exp->numBuys != post->numBuys ||
		exp_bonus != bonus ||
		!checkCardCounts(exp->supplyCount, post->supplyCount) ||
		exp->playedCardCount != post->playedCardCount ||
		!checkCardCounts(exp_counts->played, post_counts->played))
		return 0;
	
	for (i = 0; i < exp->numPlayers; i++)
	{
		addCardCounts(i, exp_counts, exp_totalCounts, i == exp->whoseTurn ? 1 : 0);	// get total card counts for player (if current player count played cards)
		addCardCounts(i, post_counts, post_totalCounts, i == exp->whoseTurn ? 1 : 0);
		
		if (exp->handCount[i] != post->handCount[i] ||
			!checkCardCounts(exp_totalCounts, post_totalCounts))
			return 0;
	}
	
	return 1;
}

void checkMinionEffect(int choice1, int choice2, struct gameState* post, int handPos, int* bonus, int player)
{
	int i, exp_bonus;
	struct cardsState exp_counts, post_counts;
	
	struct gameState pre, exp;
	memcpy (&pre, post, sizeof(struct gameState));
	memcpy (&exp, post, sizeof(struct gameState));
	
	exp_bonus = *bonus;
	
	saveCards(pre.numPlayers, &pre, &exp_counts);
	
	callMinion(player, choice1, choice2, post, handPos);
	//minionEffect(choice1, choice2, post, handPos, bonus, player);
	
	saveCards(pre.numPlayers, post, &post_counts);
	
	if (choice1 == 1)
	{
		exp.numActions++;
		exp_bonus += 2;
		exp.playedCardCount++;
		exp_counts.played[pre.hand[player][handPos]]++;
		exp.handCount[player]--;
		exp_counts.hand[player][pre.hand[player][handPos]]--;
	}
	else if (choice2 == 1)
	{
		exp.numActions++;
		exp.playedCardCount++;
		exp_counts.played[pre.hand[player][handPos]]++;
		exp_counts.hand[player][pre.hand[player][handPos]]--;
		
		if ((pre.handCount[player] + pre.deckCount[player] + pre.discardCount[player] - 1) < 4) 					// total player card count < 4 (-1 for played card)
		{
			exp.handCount[player] = pre.handCount[player] + pre.deckCount[player] + pre.discardCount[player] - 1;
		}
		else
		{
			exp.handCount[player] = 4;
		}
		
		for (i = 0; i < pre.numPlayers; i++)
		{
			if (i != player && pre.handCount[i] >= 5)
			{
				exp.handCount[i] = 4;
			}
		}
	}
	
	
	if (asserttrue(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus))
	{
		printf(" PASS\n");
		printf(" Choice1 = %d, choice2 = %d, number of players = %d, current player = %d\n", choice1, choice2, pre.numPlayers, pre.whoseTurn);
	}
	else
	{
		printf(" FAIL\n");
		printf(" Choice1 = %d, choice2 = %d, number of players = %d, current player = %d\n", choice1, choice2, pre.numPlayers, pre.whoseTurn);
		for (i = 0; i < pre.numPlayers; i++)
		{
			printf(" Player %d initial handCount = %d\n", i, pre.handCount[i]);
		}
		report(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus);
	}
}

int main()
{
	int n, i, j, choice1, choice2, handPos, bonus, player;
	struct gameState state;
	
	SelectStream(2);
	PutSeed(3);
	
	printf("\n*****Testing callMinion()*****\n");
	
	for (n = 0; n < 500; n++)
	{
		state.numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 2;		// 2 to MAX_PLAYERS
		player = floor(Random() * state.numPlayers);					// 0 to numPlayers-1
		
		for (i = 0; i <= treasure_map; i++)
		{
			state.supplyCount[i] = floor(Random() * MAX_DECK);			// 0 to MAX_DECK-1
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
				state.handCount[i] = floor(Random() * MAX_HAND) / 3 + 1;// don't overwhelm discard pile when hand discarded, at least one card to play
			}
			else
			{
				state.handCount[i] = floor(Random() * MAX_HAND) / 3;	// don't overwhelm discard pile when hand discarded	
			}
			
			state.deckCount[i] = floor(Random() * MAX_DECK) / 3;		// if deck 0-4 can fit all player's cards from hand + discard, else enough card to draw
			state.discardCount[i] = floor(Random() * MAX_DECK) / 3;		// leave space to discard hand
			
			for (j = 0; j < state.handCount[i]; j++)
			{
				state.hand[i][j] = floor(Random() * (treasure_map+1));			// random valid card
			}
		
			for (j = 0; j < state.deckCount[i]; j++)
			{
				state.deck[i][j] = floor(Random() * (treasure_map+1));			// random valid card
			}
		
			for (j = 0; j < state.discardCount[i]; j++)
			{
				state.discard[player][i] = floor(Random() * (treasure_map+1));	// random valid card
			}
		}
		
		choice1 = floor(Random() * 2);									// choice1 0 or 1
		choice2 = floor(Random() * 2);									// choice2 0 or 1
		handPos = floor(Random() * state.handCount[player]);			// 0 to player's handCount-1
		bonus = floor(Random() * 500);									// 0 to 499
		
		printf("\nTest %d: ", n);
		checkMinionEffect(choice1, choice2, &state, handPos, &bonus, player);
	}
	
	printf("\n**Testing callMinion() done**\n");
	
	return 0;
}