#include <stdio.h>				// printf()
#include <string.h>				// memset(), memcpy()
#include <math.h>				// floor()
#include "dominion.h"			// enum CARD, struct gameState, callTribute(), MAX_HAND, MAX_PLAYERS
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

void checkTributeEffect(struct gameState* post, int handPos, int* bonus, int player)
{
	int exp_bonus, nextPlayer, card, cards[2], i;
	struct cardsState pre_counts, exp_counts, post_counts;
	
	struct gameState pre, exp;
	memcpy (&pre, post, sizeof(struct gameState));
	memcpy (&exp, post, sizeof(struct gameState));
	
	exp_bonus = *bonus;
	nextPlayer = (pre.whoseTurn + 1) % pre.numPlayers;
	
	saveCards(pre.numPlayers, &pre, &pre_counts);
	saveCards(pre.numPlayers, &pre, &exp_counts);
	
	callTribute(player, nextPlayer, post);
	//tributeEffect(post, handPos, bonus, player);
	
	saveCards(pre.numPlayers, post, &post_counts);
	
	exp.playedCardCount++;
	exp_counts.played[pre.hand[player][handPos]]++;
	exp.handCount[player]--;
	exp_counts.hand[player][pre.hand[player][handPos]]--;
	
	if (pre.deckCount[nextPlayer] + pre.discardCount[nextPlayer] < 2) // if less than 2 cards in deck + discard
	{
		card = -1;									// get card (if any)
		if (pre.deckCount[nextPlayer])					// if card in deck
		{
			card = pre.deck[nextPlayer][0];
			exp.discardCount[nextPlayer]++;					// card from deck to discard pile
			exp_counts.discard[nextPlayer][card]++;
			exp.deckCount[nextPlayer]--;
			exp_counts.deck[nextPlayer][card]--;
		}
		else if (pre.discardCount[nextPlayer])			// if card in discard
		{
			card = pre.discard[nextPlayer][0];				// card from and to discard pile, no change
		}
		
													// process card bonus
		if (card >= adventurer && card <= treasure_map && card != gardens) 	// if Action card
		{
			exp.numActions += 2;
			
			if (card == great_hall)							// if Action-Victory card
			{
				exp.handCount[player] += 2;						// 2 cards from deck to hand
				exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 1]]++;
				exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 2]]++;
				exp.deckCount[player] -= 2;
				exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 1]]--;
				exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 2]]--;
			}
		}
		else if (card >= copper && card <= gold)							// if Treasure card
		{
			exp_bonus += 2;
		}
		else if ((card >= estate && card <= province) || card == gardens)		// if Victory card
		{
			exp.handCount[player] += 2;						// 2 cards from deck to hand
			exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 1]]++;
			exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 2]]++;
			exp.deckCount[player] -= 2;
			exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 1]]--;
			exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 2]]--;
		}
		
		if (asserttrue(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus))
		{
			printf(" PASS\n");
			printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
			printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
		}
		else
		{
			printf(" FAIL\n");
			printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
			printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
			report(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus);
		}

	}
	else															  // at least 2 cards in deck + discard
	{												// get 2 cards
		cards[0] = cards[1] = -1;
		
		if (pre.deckCount[nextPlayer] == 0)				// 0 in deck
		{
			if (post->discardCount[nextPlayer] != 2)			// then 2 cards should be in discard pile
			{
				printf(" FAIL\n");
				printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
				printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
				printf(TEST_DISCARDCOUNT_PLAYER, "", nextPlayer, post->discardCount[nextPlayer], 2);
				printf(TEST_DECKCOUNT_PLAYER, "", nextPlayer, post->deckCount[nextPlayer], pre.discardCount[nextPlayer] - 2);
				return;
			}
			else
			{
				cards[0] = post->discard[nextPlayer][0];
				cards[1] = post->discard[nextPlayer][1];
				
				exp.deckCount[nextPlayer] = pre.discardCount[nextPlayer] - 2;
				exp.discardCount[nextPlayer] = 2;
				for (i = 0; i <= treasure_map; i++)
				{
					exp_counts.deck[nextPlayer][i] = pre_counts.discard[nextPlayer][i];
					exp_counts.discard[nextPlayer][i] = 0;
				}
				exp_counts.deck[nextPlayer][cards[0]]--;
				exp_counts.deck[nextPlayer][cards[1]]--;
				exp_counts.discard[nextPlayer][cards[0]]++;
				exp_counts.discard[nextPlayer][cards[1]]++;
			}
		}
		else if (pre.deckCount[nextPlayer] == 1)		// 1 in deck
		{
			if (post->discardCount[nextPlayer] != 2)			// then 2 cards should be in discard pile
			{
				printf(" FAIL\n");
				printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
				printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
				printf(TEST_DISCARDCOUNT_PLAYER, "", nextPlayer, post->discardCount[nextPlayer], 2);
				printf(TEST_DECKCOUNT_PLAYER, "", nextPlayer, post->deckCount[nextPlayer], pre.discardCount[nextPlayer] - 1);
				return;
			}												// pre deckCount == 1 && post discardCount == 2, check pre deck card is one of discarded cards
			else if (pre.deck[nextPlayer][0] != post->discard[nextPlayer][0] && pre.deck[nextPlayer][0] != post->discard[nextPlayer][1])
			{
				printf(" FAIL\n");
				printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
				printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
				printf(TEST_DISCARD_PLAYER, "", nextPlayer);
				return;
			}
			else
			{
				cards[0] = post->discard[nextPlayer][0];
				cards[1] = post->discard[nextPlayer][1];
				
				exp.deckCount[nextPlayer] = pre.discardCount[nextPlayer] - 1;
				exp.discardCount[nextPlayer] = 2;
				for (i = 0; i <= treasure_map; i++)
				{
					exp_counts.deck[nextPlayer][i] += pre_counts.discard[nextPlayer][i];
					exp_counts.discard[nextPlayer][i] = 0;
				}
				exp_counts.deck[nextPlayer][cards[0]]--;
				exp_counts.deck[nextPlayer][cards[1]]--;
				exp_counts.discard[nextPlayer][cards[0]]++;
				exp_counts.discard[nextPlayer][cards[1]]++;
			}
		}
		else											// 2 or more in deck
		{
			if (post->discardCount[nextPlayer] != pre.discardCount[nextPlayer] + 2)
			{
				printf(" FAIL\n");
				printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
				printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
				printf(TEST_DISCARDCOUNT_PLAYER, "", nextPlayer, post->discardCount[nextPlayer], pre.discardCount[nextPlayer] + 2);
				return;
			}
			else
			{
				cards[0] = post->discard[nextPlayer][pre.discardCount[nextPlayer]];
				cards[1] = post->discard[nextPlayer][pre.discardCount[nextPlayer]+1];
				
				exp.deckCount[nextPlayer] -= 2;
				exp.discardCount[nextPlayer] += 2;
				
				exp_counts.deck[nextPlayer][cards[0]]--;
				exp_counts.deck[nextPlayer][cards[1]]--;
				exp_counts.discard[nextPlayer][cards[0]]++;
				exp_counts.discard[nextPlayer][cards[1]]++;
			}
		}
		
		
		if (cards[0] == cards[1] && cards[0] != -1)// check if cards are duplicates
		{
			cards[1] = -1;	// remove duplicate from revealed cards
		}
													// process card bonus
		for (i = 0; i < 2; i++)
		{
			if (cards[i] != -1)
			{
				if (cards[i] >= adventurer && cards[i] <= treasure_map && cards[i] != gardens) // if Action card
				{
					exp.numActions += 2;
			
					if (cards[i] == great_hall)													// if Action-Victory card
					{
						exp.handCount[player] += 2;						// 2 cards from deck to hand
						exp.deckCount[player] -= 2;
					
						if (i == 1 && ((cards[0] >= estate && cards[0] <= province) || cards[0] == gardens || cards[0] == great_hall))
						{
							exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 3]]++;
							exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 4]]++;
							exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 3]]--;
							exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 4]]--;
						}
						else
						{
							exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 1]]++;
							exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 2]]++;
							exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 1]]--;
							exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 2]]--;
						}
					}
				}
				else if (cards[i] >= copper && cards[i] <= gold)							// if Treasure card
				{
					exp_bonus += 2;
				}
				else if ((cards[i] >= estate && cards[i] <= province) || cards[i] == gardens)	// if Victory card
				{
					exp.handCount[player] += 2;						// 2 cards from deck to hand
					exp.deckCount[player] -= 2;
					
					if (i == 1 && ((cards[0] >= estate && cards[0] <= province) || cards[0] == gardens || cards[0] == great_hall))
					{
						exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 3]]++;
						exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 4]]++;
						exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 3]]--;
						exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 4]]--;
					}
					else
					{
						exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 1]]++;
						exp_counts.hand[player][pre.deck[player][pre.deckCount[player] - 2]]++;
						exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 1]]--;
						exp_counts.deck[player][pre.deck[player][pre.deckCount[player] - 2]]--;
					}
				}
			}
		}
		
		if (asserttrue(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus))
		{
			printf(" PASS\n");
			printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
			printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
		}
		else
		{
			printf(" FAIL\n");
			printf(" Number of players = %d, current player = %d\n", pre.numPlayers, pre.whoseTurn);
			printf(" Next player initial deckCount = %d, discardCount = %d\n", pre.deckCount[nextPlayer], pre.discardCount[nextPlayer]);
			report(&exp, post, &exp_counts, &post_counts, exp_bonus, *bonus);
		}
	}
}

int main()
{
	int n, i, j, handPos, bonus, player;
	struct gameState state;
	
	SelectStream(2);
	PutSeed(3);
	
	printf("\n*****Testing callTribute()*****\n");
	
	for (n = 0; n < 55000; n++)
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
				state.handCount[i] = floor(Random() * MAX_HAND) / 3 + 1;	// at least one card to play
				state.deckCount[i] = floor(Random() * MAX_DECK) / 3 + 4;	// at least 4 cards to draw
			}
			else
			{
				state.handCount[i] = floor(Random() * MAX_HAND) / 3;
				state.deckCount[i] = floor(Random() * MAX_DECK) / 3;
			}
			
			state.discardCount[i] = floor(Random() * MAX_DECK) / 3;
			
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
		
		handPos = floor(Random() * state.handCount[player]);			// 0 to player's handCount-1
		bonus = floor(Random() * 500);									// 0 to 499
		
		printf("\nTest %d: ", n);
		checkTributeEffect(&state, handPos, &bonus, player);
	}
	
	printf("\n**Testing callTribute() done**\n");
	
	return 0;
}