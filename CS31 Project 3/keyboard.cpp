//
//  main.cpp
//  keyboard
//
//  Created by Maeneka Grewal on 10/22/17.
//  Copyright © 2017 Maeneka Grewal. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

//Checks to see if the character is an acceptable piano letter.
bool isLetter(char a)
{
    return (a == 'A' || a == 'B' || a == 'C' || a == 'D' || a == 'E' || a == 'F' || a == 'G');
}

//Checks to see if the character is either a sharp or a flat.
bool isSign(char a)
{
    return (a == '#' || a == 'b');
}

//This function accepts an argument 'beat' passed by the evaluateSong function. If the beat is empty or simply a space, this function returns true. It also returns true if the beat is syntatically correct, meaning that signs can only come after a letter, and digits can only come after a letter or a sign. If these conditions are not met, the function returns false.
bool evaluateBeat(string beat)
{
    //If the beat is empty
    if (beat == "")
        return true;
    //If the beat is a space
    if (beat == " ")
        return true;
    
    //A for loop to evaluate each character of the beat and the characters before and after it so that the order is correct
    for (int i = 0; i < beat.size(); i++)
    {
        //If the character isn't a valid letter, digit, or sign, it is false
        if (!(isdigit(beat[i])) && !(isLetter(beat[i])) && !(isSign(beat[i])))
            return false;
        
        //If the sign is the first character or the character before it is not a letter, it is false
        if (isSign(beat[i]))
        {
            if (i == 0)
                return false;
            if (!(isLetter(beat[i-1])))
                return false;
        }
        
        //If the digit is the first character or the character before it is also a digit, it is false
        if (isdigit(beat[i]))
        {
            if (i == 0)
                return false;
            if(isdigit(beat[i-1]))
                return false;
        }
    }
    return true;
}

//This function returns true if the song is syntatically correct, and false if it is not. It does so by breaking down the song into a series of beats, and sending them to the evaluateBeat function.
bool hasCorrectSyntax(string song)
{
    //If the song is empty, it is true
    if (song == "")
        return true;
    //If the song is an empty beat, it is true
    if (song == "/")
        return true;
    //If the song does not end in a /, it is false
    if (song[song.size() -1] != '/')
        return false;
    
    //The new variable sub is set to an empty string so that characters can be added. Characters are added when it is not an /. If it is an /, this is the end of the beat and the beat can be sent to be evaluated. The sub is reset to empty.
    string sub = "";
    for (int k = 0; k < song.size(); k++)
    {
        if (song[k] != '/')
            sub += song[k];
        else
        {
            if ((evaluateBeat(sub)))
                sub = "";
            else
                return false;
        }
    }
    return true;
}

//This function returns true if the note is playable, and false if it is not. It also alters the variables oct, let, and sign through pass-by-reference arugments. Essentially, it evaluates the note, maximum possible length of 3, and assigns the appropriate octave number, piano letter, and sign character to the note.
bool evaluateNote(string note, int& oct, char& let, char& sign)
{
    //If there is not an octave digit attached to the letter, 4 is assigned and the letter is the letter given.
    if (note.size() == 1)
    {
        oct = 4;
        let = note[0];
        return true;
    }
    //If there is a sign and no octave digit attached, 4 is assigned and the sign is the sign given and the letter is the letter given.
    if (note.size() == 2)
    {
        if (isSign(note[1]))
        {
            oct = 4;
            let = note[0];
            sign = note[1];
            return true;
        }
        //If there is an octave digit attached and it is in the valid octave range, the octave is set to that digit and the letter is the letter given.
        if (isdigit(note[1]))
        {
            if (note[1] == '2' || note[1] == '3' || note[1] == '4' || note[1] == '5')
            {
                oct = note[1] - '0';
                let = note[0];
                return true;
            }
            //If it the special case of 'C6' is is set to those values and it is ok.
            if (note[1] == '6' && note[0] == 'C')
            {
                oct = 6;
                let = 'C';
                return true;
            }
        }
    }
    //If there is a sign, octave digit that is valid, and letter given, they are all assigned to their respective variables.
    if (note.size() == 3)
    {
        //These two ifs account for special cases.
        if (note[0] == 'C' && note[1] == 'b' && note[2] == '2')
            return false;
        if (note[0] == 'C' && note[1] == 'b' && note[2] == '6')
        {
            oct = 5;
            let = 'B';
            return true;
        }
        //This if accounts for a special case.
        if (note[0] == 'B' && note[1] == '#' && note[2] == '1')
        {
            oct = 2;
            let = 'C';
            return true;
        }
        //Checking to see if each octave digit is valid and assiging each variable to its respective character or value.
        if (note[2] == '2' || note[2] == '3' || note[2] == '4' || note[2] == '5')
        {
            oct = note[2] - '0';
            let = note[0];
            sign = note[1];
            return true;
        }
    }
    return false;
}

//This function accepts a song, first checks to see whether the song has any syntactical errors or not. If it is syntactically incorrect, neither instructions nor badBeat is altered and it just returns 1. Otherwise, it begins to break down the song into a series of beats, and then notes to encode each note into the proper new character. If a note is not playable, it resets instructions to the original string, sets badBeat to the number beat that is unplayable, and returns 2. If the entire song is playable, it continues to change instructions to the string of new characters and returns 0.
int encodeSong(string song, string& instructions, int& badBeat)
{
    string original = instructions;
    //If the song has a syntax error, returns 1.
    if (!(hasCorrectSyntax(song)))
        return 1;
    //Resetting instructions, note, beat, and newNote.
    instructions = "";
    string note = "";
    string beat = "";
    string newNote = "";
    //beatCount variable used to keep track of the beat number that the function is on.
    int beatCount = 0;
    //For loop used to run through each character of the song.
    for (int i = 0; i < song.size(); i++)
    {
        //If the character is not a /, the character is added to the beat.
        if (song[i] != '/')
            beat += song[i];
        //If the character is a /, the beat is complete.
        else
        {
            //newNote is reset again and beatCount is incremented.
            newNote = "";
            beatCount++;
            //If beat is empty, a space is added to instructions.
            if (beat == "")
                instructions += " ";
            //If beat is a space, a double space is added to instructions and beat is reset.
            if (beat == " ")
            {
                instructions += "  ";
                beat = "";
            }
            //For loop to run through each character of the beat.
            for (int j = 0; j < beat.size(); j++)
            {
                //If the note is still empty and the character is a letter, it is added to note.
                if ((note == "") && (isLetter(beat[j])))
                    note += beat[j];
                //If it is not a letter, it is attached to note.
                if (!(isLetter(beat[j])))
                    note += beat[j];
                //If the loop is not on the last character of the beat and the next character of the beat is a letter, then the note is over.
                if ((j == beat.size()-1) || (isLetter(beat[j+1])))
                {
                    //Initial values set for oct, let, and sign that will be changed in evaluateNote function.
                    int oct = 4; char let = ' '; char sign = ' ';
                    //If evaluateNote is true, meaning it is playable, the oct, let, and sign are changed and passed to encodeNote, so the new character is added to newNote and note is reset.
                    if (evaluateNote(note, oct, let, sign))
                    {
                        newNote += encodeNote(oct, let, sign);
                        note = "";
                    }
                    //If evaluateNote is false, meaning it is not playable, badBeat is set to beatCount, instructions is reset to the original string, and 2 is returned.
                    else
                    {
                        badBeat = beatCount;
                        instructions = original;
                        return 2;
                    }
                }
            }
            //If the beat contained multiple notes, it is added to instructions with brackets.
            if (newNote.size() > 1)
            {
                instructions += "[";
                instructions += newNote;
                instructions += "]";
            }
            //If the beat contained a single note, it is simply added to instructions.
            else
            {
                instructions += newNote;
            }
            //Beat is reset.
            beat = "";
        }
    }
    return 0;
}

int main()
{
}


