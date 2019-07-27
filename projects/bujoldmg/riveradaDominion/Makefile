CFLAGS= -Wall -fpic -coverage -lm -std=c99 -g

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe



baron:
	gcc -o testBaron cardtest1.c dominion_testing.c dominion.c rngs.c $(CFLAGS)
	./testBaron > testBaron.out
	gcov dominion.c -bf >> testBaron.out

baronR:
	gcc -o randomtestBaron randomtestcard1.c dominion_testing_random.c dominion.c rngs.c $(CFLAGS)
	./randomtestBaron > randomtestBaron.out
	gcov dominion.c -bf >> randomtestBaron.out

minion:
	gcc -o testMinion cardtest2.c dominion_testing.c dominion.c rngs.c $(CFLAGS)
	./testMinion > testMinion.out
	gcov dominion.c -bf >> testMinion.out

minionR:
	gcc -o randomtestMinion randomtestcard2.c dominion_testing_random.c dominion.c rngs.c $(CFLAGS)
	./randomtestMinion > randomtestMinion.out
	gcov dominion.c -bf >> randomtestMinion.out

tribute:
	gcc -o testTribute cardtest4.c dominion_testing.c dominion.c rngs.c $(CFLAGS)
	./testTribute > testTribute.out
	gcov dominion.c -bf >> testTribute.out

tributeR:
	gcc -o randomtestTribute randomtestcard3.c dominion_testing_random.c dominion.c rngs.c $(CFLAGS)
	./randomtestTribute > randomtestTribute.out
	gcov dominion.c -bf >> randomtestTribute.out

