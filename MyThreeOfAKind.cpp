/**
* Author: Ashish Karki
* Date: 5/3/2013
* Added comment on 4/30/2014 for github testing
*/

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void IsThreeOfAKind(int pokerHands[]);

int main(){
	// array to represent card hands with two digit decimals
	int hands[5];
	
	/*
	* The input from the user would in in x0AB format,
	* where A = represents the suit and ranges from 1-4 and
	* B = represents the card rank (values 1-13) and ranges from 0-9 and A-D/a-d	 	
	*/
	cout << "Please note the hands entered should be in 0xAB format," << endl;
	cout << "where A = represents the suit and ranges from 1-4 and " << endl;
	cout << "B = represents the card rank and ranges from 0-9 and A-D/a-d" << endl;
	// Get the hands
	for (int hand = 0; hand < 5; hand++) {
		cout << "Enter card hand:"<<endl;
		cin >> hex >> hands[hand];
		fflush(stdin);
	}
	
	// Check if the user entered same card (same suit and rank) more than once erroneously
	int suitI = -1;
	int rankI = -1;
	int suitJ = -1;
	int rankJ = -1;
	for (int handI = 0; handI < 5; handI++) {
		suitI = (int)(0xF0) & (hands[handI]);
		rankI = (int)(0x0F) & (hands[handI]);
		for (int handJ = handI + 1; handJ < 5; handJ++) {
			suitJ = (int)(0xF0) & (hands[handJ]);
			rankJ = (int)(0x0F) & (hands[handJ]);
			
			if(suitI == suitJ && rankI == rankJ){
				// if at least one erroneous entry found, then quit the program
				cout << "Erroneous entry. More than one input with same suit and rank made!!!!!!" << endl;
				
				// wait for user to terminate
				cout << "Press Enter to quit!!" << endl;
				getchar();
				return 0;
			}
		}
	}
	// Now, determine if 3 of hand occurs with IsThreeOfAKind function
	IsThreeOfAKind(hands);
	
	// wait for user to terminate
	cout << "Press Enter to quit!!" << endl;
	getchar();
	
	return 0;
}

/**
* Function: 
* argument: array of hands passed from the main function
* This function uses the rank part of the card hand to determine if 3 of a kind poker exists.
* Essential condition for Three of a Kind::
* ::::::::::::::::::::::::::::::::::::::::
* The collection of hands contains three cards of the same rank, 
* plus two cards which are not of this rank nor the same as each other
* source: http://en.wikipedia.org/wiki/List_of_poker_hands
* ::::::::::::::::::::::::::::::::::::::::
*/
void IsThreeOfAKind(int pokerHands[]){
	// Declare variables first
	
	// stores the rank portion (B) of the hand information entered (0xAB)
	int rankofHands[5];
	// the rank that constitutes the 3 of a kind
	int rankOfThree;
	// cummulative count for each of the individual ranks from 1-13
	int cardRankCount[13] = {0};
	// boolean to indicate that we found three of a kind
	bool foundThreeOfAKind = false;
	// the rank hand (in integer format) of current hand
	int curRankHand = -1;
	
	for (int hand = 0; hand < 5; hand++) {
		// obtain the rank portion of input hands
		rankofHands[hand] = (0x0F) & (pokerHands[hand]);
		curRankHand = (int) rankofHands[hand]; 
		cardRankCount[curRankHand] += 1; 
		
		// check to see if the current rank hand satisfies 3 of kind
		if (cardRankCount[curRankHand] == 3) { 
			foundThreeOfAKind = true; 
			rankOfThree = curRankHand; 
		} 
		// check to see if the matching is more than 3 of kind
		else if (foundThreeOfAKind && (rankofHands[hand] == rankOfThree)) { 
			  foundThreeOfAKind = false; 
		}
	}
	
	/* 
	* Following logic check to see if the two remaining hands (called kickers),
	* are not of the same rank which violates the condition for 3 of a kind
	*/
	bool first = false;
	bool second = false;
	int kicker1Rank = -1;
	int kicker2Rank = -1;
	for(int rank = 0; rank < 13; rank++){
		if(cardRankCount[rank]==1){
			if(!first){
				kicker1Rank = rank;	
			} else if(first && !second){
				kicker2Rank = rank;
			}
		}
	}
	// if the two kickers have same rank, then not a 3 of a kind
	if(kicker1Rank == kicker2Rank){
		foundThreeOfAKind = false;
	}
	
	// Print the output
	if (foundThreeOfAKind) {
		cout << "This is a 3 of a Kind" << endl; 
	} else {
		cout << "This is NOT a 3 of a Kind" << endl; 
	}
}
