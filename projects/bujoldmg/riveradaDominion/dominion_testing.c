#include <stdio.h>				// printf()
#include <string.h>				// memset()
#include "dominion.h"			// enum CARD, struct gameState
#include "dominion_testing.h"	// struct cardsState


const char* CARD_NAMES[] = 
{ 
	"Curse", "Estate", "Duchy", "Province", "Copper", "Silver", "Gold", 
	"Adventurer", "Council room", "Feast", "Gardens", "Mine", "Remodel", 
	"Smithy", "Village", "Baron", "Great hall", "Minion", "Steward", 
	"Tribute", "Ambassador", "Cutpurse", "Embargo", "Outpost", "Salvager", 
	"Sea hag", "Treasure map" 
};

/*
 * cards  = input  = hand[player][] || discard[player][] || deck[player][]
 * counts = output = handCounts[] || discardCounts[] || deckCounts[] = array[treasure_map+1] = {0};
 * numCards = number of cards in cards array
 */
void getCardCounts(int* cards, int numCards, int* counts)
{
	int i;
	for (i = 0; i < numCards; i++)
	{
		if (cards[i] >= curse && cards[i] <= treasure_map)
		{
			counts[cards[i]]++;
		}
	}
}

void addCardCounts(int player, struct cardsState* counts, int* totalCounts, int playedFlag)
{	
	memset(totalCounts, 0, sizeof(int) * (treasure_map+1));
	
	int i;
	for (i = 0; i < treasure_map + 1; i++)
	{
		totalCounts[i] = counts->hand[player][i] + counts->discard[player][i] + counts->deck[player][i];
	}
	
	if (playedFlag)
	{
		for (i = 0; i < treasure_map + 1; i++)
		{
			totalCounts[i] += counts->played[i];
		}
	}
}

int checkCardCounts(int* set1, int* set2)
{
	int i;
	for (i = 0; i < treasure_map + 1; i++)
	{
		if (set1[i] != set2[i])
			return 0;
	}
	return 1;
}

void displayCards(int player, char* location, int* cards, int cardCount)
{
	printf("Player %d, %s -> ", player, location);
	
	int i;
	for (i = 0; i < cardCount; i++)
	{
		printf("%s ", CARD_NAMES[cards[i]]);
	}
	printf("\n");
}

void saveCards(int numPlayers, struct gameState* state, struct cardsState* counts)
{
	memset(counts, 0, sizeof(struct cardsState));								// clear arrays
	
	int i;
	for (i = 0; i < numPlayers; i++)											// for each player
	{
		getCardCounts((int*)&state->hand[i], state->handCount[i], (int*)&counts->hand[i]);			// save hand
		getCardCounts((int*)&state->discard[i], state->discardCount[i], (int*)&counts->discard[i]);	// save discard pile
		getCardCounts((int*)&state->deck[i], state->deckCount[i], (int*)&counts->deck[i]);			// save deck
	}
	getCardCounts(state->playedCards, state->playedCardCount, counts->played);	// save played cards
}