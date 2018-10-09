//
//  main.cpp
//  array
//
//  Created by Maeneka Grewal on 10/31/17.
//  Copyright © 2017 Maeneka Grewal. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++)
    {
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1;
    string max = a[0];
    int position = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
            position = i;
        }
    }
    return position;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0)
        return -1;
    string original = a[pos];
    for (int i = pos; i < n-1; i++)
    {
        a[i] = a[i+1];
    }
    a[n-1] = original;
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int counter = 1;
    for (int i = 0; i < n-1; i++)
    {
        if (a[i] != a[i+1])
            counter++;
    }
    return counter;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n/2; i++)
    {
        string temp = a[i];
        a[i] = a[n-1-i];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    if (n1 >= n2)
    {
        for (int i = 0; i < n2; i++)
        {
            if (a1[i] != a2[i])
                return i;
        }
        return n2;
    }
    for (int i = 0; i < n1; i++)
    {
        if (a1[i] != a2[i])
            return i;
    }
    return n1;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    if (n2 == 0)
        return 0;
    for (int i = 0; i < n1; i++)
    {
       if (a1[i] == a2[0])
       {
           if ((i+n2 <= n1))
           {
               for (int j = 0; j < n2; j++)
               {
                   if (a2[j] != a1[i+j])
                       return -1;
               }
               return i;
           }
       }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j])
                return i;
        }
    }
    return -1;
}

int split(string a[], int n, string splitter)
{
    if (n < 0)
        return -1;
    string x[1000];
    int counterLess = 0;
    int counterGreater = 1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < splitter)
        {
            x[counterLess] = a[i];
            counterLess++;
        }
        else
        {
            x[n-counterGreater] = a[i];
            counterGreater++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = x[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= splitter)
            return i;
    }
    return n;
}

int main()
{
}
