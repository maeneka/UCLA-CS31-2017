//
//  main.cpp
//  fare
//
//  Created by Maeneka Grewal on 10/11/17.
//  Copyright © 2017 Maeneka Grewal. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    /*This block asks for the age of the rider and checks to see if it is valid input. If the age is negative, it ends the program.*/
    cout << "Age of rider: ";
    int age;
    cin >> age;
    cin.ignore(10000, '\n');
    if (age < 0)
    {
        cout << "---" << endl << "The age must not be negative" << endl;
        return 1;
    }
    
    /*This block asks for the student status of the rider, and checks to see if it is valid input. If anything other than y or n is inputted, it ends the program.*/
    cout << "Student? (y/n): ";
    string stuStatus;
    getline(cin, stuStatus);
    if ((stuStatus != "y") && (stuStatus != "n"))
    {
        cout << "---" << endl << "You must enter y or n" << endl;
        return 1;
    }

    /*This block asks for the destination of the rider, and checks to see if it is valid input. If anything nothing is entered, it ends the program.*/
    cout << "Destination: ";
    string destination;
    getline(cin, destination);
    if (destination == "")
    {
        cout << "---" << endl << "You must enter a destination" << endl;
        return 1;
    }
    
    /*This block asks for the number of zone boundaries, and checks to see if it is valid input. If a negative number is inputted, it ends the program.*/
    cout << "Number of zone boundaries crossed: ";
    int zones;
    cin >> zones;
    if (zones < 0)
    {
        cout << "---" << endl << "The number of zone boundaries crossed must not be negative" << endl;
        return 1;
    }

    /*This block sets the fare and boundary amount. Normal fare is 1.35 and the boundary fare is 0.55 per zone crossed. If the rider is a minor or a student AND they're crossing one boundary or less, the total fare is automatically 0.65. If the rider is a senior, the fare becomes 0.55. If the rider is a senior and the zones crossed is 0, the fare is 0.45.*/
    double total = 0;
    double fare = 1.35;
    double boundAmt = 0.55;
    if ((age < 18 || stuStatus == "y") && zones <= 1)
    {
        fare = 0.65;
        boundAmt = 0;
    }
    else if (age >= 65)
    {
        fare = 0.55;
        boundAmt = 0.25;
        if (zones == 0)
            fare = 0.45;
    }
    
    /*This block then totals the fare by adding the base 'fare' to the boundary fare multiplied by the number of zones crossed.*/
    total = fare + (boundAmt*zones);
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "---" << endl << "The fare to " << destination << " is $" << total << endl;
    
}
