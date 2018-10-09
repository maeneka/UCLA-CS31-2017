//
//  main.cpp
//  stars
//
//  Created by Maeneka Grewal on 11/8/17.
//  Copyright © 2017 Maeneka Grewal. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <cctype>
#include <iostream>
#include <cstring>
using namespace std;

int runOneRound(const char words[][7], int nWords, int wordnum);
int starsPlanets(char guess[7], char target[7], int& stars, int& planets);
bool checkLetters(char yeet[7]);
const char WORDFILENAME[] = "/Users/maenekagrewal/Documents/words.txt";

int main()
{
    //fills wordList with Smallberg's list of words
    char wordList[9000][7];
    int numWords = getWords(wordList, 9000, WORDFILENAME);
    
    //if the number of words is less than 1, or too big for the error, print error message
    if (numWords < 1 || numWords > 9000)
        cout << "No words were loaded, so I can't play the game." << endl;
    
    //ask for user input for how many rounds to play, store in variable
    int rounds2Play;
    cout << "How many rounds do you want to play? ";
    cin >> rounds2Play;
    cin.ignore(10000, '\n');
    
    //check to see if input was negative, display error message if less than 1
    if (rounds2Play <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    int totScore = 0;
    double ave = 0;
    int min = 10000;
    int max = -10000;
    
    //for loop for each round
    for (int i = 1; i <= rounds2Play; i++)
    {
        //find random number, and then random word in wordList that will be the secret word
        cout << endl;
        
        cout << "Round " << i << endl;
        int rando = randInt(0, numWords-1);
    
        char secret[7];
        strcpy(secret, wordList[rando]);
        //cout << secret << endl;
        
        //display length of secret word to user
        int secretLen = strlen(secret);
        cout << "The secret word is " << secretLen << " letters long." << endl;
    
        //send the wordList, secret word, and number of words to runOneRound
        int score = runOneRound(wordList, numWords, rando);
        
        //appropriate messages for if the score is 1 vs if the score is greater than 1
        if (score == 1)
        {
            cout << "You got it in 1 try." << endl;
        }
        else
            cout << "You got it in " << score << " tries." << endl;
        
        //caculates the average score after each round using a total score variable, also calculates max and min scores and sets precision
        totScore += score;
        ave = (double)totScore/i;
        cout.setf(ios::fixed);
        cout.precision(2);
        if (score < min)
            min = score;
        if (score > max)
            max = score;
        
        //displays average, min, and max after each round
        cout << "Average: " << ave << ", minimum: " << min << ", maximum: " << max << endl;
    }
}

//used to make sure each letter in the probe word is a valid lower case letter, returns false if not
bool checkLetters(char yeet[7])
{
    for (int i = 0; i < strlen(yeet); i++)
    {
        if (!(islower(yeet[i])))
            return false;
    }
    return true;
}

int runOneRound(const char words[][7], int nWords, int wordnum)
{
    //if the array size is not correct or if the random number isn't in the array element range
    if (nWords < 0)
        return -1;
    if (wordnum < 0 || wordnum >= nWords)
        return -1;
    
    //assigning the secret words just like it did in the main
    char secret[7];
    strcpy(secret, words[wordnum]);
    
    //asking for user input for the first probe word
    char probe[7];
    cout << "Probe word: ";
    cin.getline(probe, 100);
    //the score is automatically 1 at this point
    int score = 1;
    
    //if the probe word and secret word do not match, keep looping
    while (strcmp(probe, secret) != 0)
    {
        //checks if the probe word is the proper length
        if (strlen(probe) < 4 || strlen(probe) > 6)
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            cout << "Probe word: ";
            cin.getline(probe, 100);
            continue;
        }
        
        //checks if the probe word contains only lower case letters
        if (!(checkLetters(probe)))
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            cout << "Probe word: ";
            cin.getline(probe, 100);
            continue;
        }
        
        //checks if the probe word is in the wordList
        bool found = false;
        for (int i = 0; i < nWords; i++)
        {
            if (strcmp(probe, words[i]) == 0)
                found = true;
        }
        if (!found)
        {
            cout << "I don't know that word." << endl;
            cout << "Probe word: ";
            cin.getline(probe, 100);
            continue;
        }
        
        //if all of the above tests passed, sends probe word, target word, stars, and planets to new function
        int stars = 0;
        int planets = 0;
        starsPlanets(probe, secret, stars, planets);
        
        //prints the number of stars and planets
        cout << "Stars: " << stars << ", Planets: " << planets << endl;
        
        //if the probe word doesn't match the target word, asks for a probe word again
        if (stars != strlen(secret))
        {
            cout << "Probe word: ";
            cin.getline(probe, 100);
            score++;
        }
    }
    return score;
}

int starsPlanets(char guess[7], char target[7], int& stars, int& planets)
{
    //creates two new char arrays, and copies the probe word and secret word into them
    stars = 0;
    planets = 0;
    char notStarTarget[7];
    strcpy(notStarTarget, target);
    char notStarGuess[7];
    strcpy(notStarGuess, guess);
    
    //if the probe word is longer, loops through the target word
    if (strlen(guess) >= strlen(target))
    {
        for (int i = 0; target[i] != '\0'; i++)
        {
            
            //if the characters are equal, increment star and replace the character with a space in the new char arrays
            if (guess[i] == target[i])
            {
                stars++;
                notStarTarget[i] = ' ';
                notStarGuess[i] = ' ';
            }
        }
    }
    
    //if the target word is longer, loop through the guess word
    else
    {
        for (int i = 0; guess[i] != '\0'; i++)
        {
            
            //if the characters are equal, increment star and replace the character with a a space in the new char arrays
            if (guess[i] == target[i])
            {
                stars++;
                notStarGuess[i] = ' ';
                notStarTarget[i] = ' ';
            }
        }
    }
    
    //these were used for debugging, prints the new arrays
    //cout << notStarTarget << endl;
    //cout << notStarGuess << endl;
    
    //new array to track which characters are already planets
    char alreadyPlanet[7];
    
    //if the probe word wasn't the exact match to the secret word, stars won't equal length of the target
    if (stars != strlen(target))
    {
        //double for loop to loop through both the target and guess word and check for matching characters in different positions
        for (int i = 0; notStarTarget[i] != '\0'; i++)
        {
            for (int j = 0; notStarGuess[j] != '\0'; j++)
            {
                //checks to see if chars in different positions are equal and can't be a space character! spaces were stars
                if ((notStarTarget[i] == notStarGuess[j]) && (notStarTarget[i] != ' '))
                {
                    //if chars match, they cannot already be a planet so loop through planet array and check
                    bool unique = true;
                    for (int k = 0; alreadyPlanet[k] != '\0'; k++)
                    {
                        if (notStarTarget[i] == alreadyPlanet[k])
                            unique = false;
                    }
                    
                    //if not already a planet, increment planet and add it to alreadyPlanet array
                    if (unique)
                    {
                        alreadyPlanet[planets] = notStarTarget[i];
                        planets++;
                        //cout << alreadyPlanet << endl;
                    }
                }
            }
        }
    }
    return 0;
}

