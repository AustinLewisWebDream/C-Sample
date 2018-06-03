/* 
 * File:   functions.cpp
 * Course: CS216-00x
 * Purpose: provide the function implementation for some useful operations on strings
 */
#include <iostream> 
#include "functions.h"
#include <cctype>

/*
 Returns the string which transforms each character of the parameter into lower case
 @param original the original string:
 const call by reference (no copy is made for efficiency, safe to the argument)
 @return a new string which transforms each character of the parameter into lower case
 (algorithm header file is needed for the definition of transform function)
 */
string toLower(const string &original)
{
    string result = original;
    transform(original.begin(), original.end(), result.begin(), ::tolower);
    return result;
}

/*
 It is a recursive function.
 Returns the string which transforms each character of the parameter into upper case
 @param original the original string:
 const call by reference (no copy is made for e<fficiency, safe to the argument)
 @return a new string which transforms each character of the parameter into upper case
 */
string toUpper(const string &original)
{
    static int fcount = 0; // use a static variable to count the function calling
    fcount++;   // increase count by one while calling the function
    // Base case:
    if (original.length() == 0)
        return original;
    // Recursive case:
    string first = original.substr(0,1);
    const char* front = first.c_str();
    char upperFront[LEN];
    string result;
    upperFront[0] = toupper(front[0]);
    upperFront[1] = '\0';
    result = upperFront;
    return result + toUpper(original.substr(1, original.length()-1));
}

string capitalize(const string& original)
{
	string newString = original;	// The string that we will return capitalized
	for(auto i = 0; i < original.length(); i++)
	{
		// Capitalize the first character and characters after space
		if (i == 0 || original[i - 1] ==  ' ')
		{
			newString[i] = std::toupper(newString[i]);
		}
	}
	return newString;
}


