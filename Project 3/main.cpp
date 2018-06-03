//----------------------------------------------------------------------
// Course: CS216-001
// Project: 2
// Purpose: Read actor data from a file, take that data and provide the
//			user with information based on their choices of menu options
// Author: Austin Lewis
//----------------------------------------------------------------------

#include "imdb.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include "functions.h"

using namespace std;

const short CL_ARGUMENTS = 2;
const short INPUT_FILE_INDEX = 1;

int mainMenu()
{
	string userChoice;
	while (true)
	{
		cout << "This application stores information about Actors and their Movies," << endl;
		cout << "please choose your option (Enter Q or q to quit):" << endl;
		cout << "1. Actors in Movies" << endl;
		cout << "2. Actors and co-actors" << endl;
		cin.sync();
		getline(cin, userChoice);

		if (userChoice[0] == 'q' || userChoice[0] == 'Q')
			return -1;

		// Convert to integer
		int userInt = userChoice[0] - '0';
		
		// If input completely invalid, clear buffer and re-display menu
		if ((userChoice[0] != '1' && userChoice[0] != '2') || userChoice.length() > 1)
		{
			cout << "Invalid option!" << endl;
			continue;
		}
		return userInt;
	}
}

void actorsInMoviesMenu(const IMDB& fileData)
{
	string movieOne, movieTwo; // Movies that the user input
	cout << "Please input the first movie title: ";
	getline(cin, movieOne);
	cout << "Please input the second movie title: ";
	getline(cin, movieTwo);

	// If either input is invalid, return to the main menu
	if (!fileData.isExistingMovie(toLower(movieOne)) || !fileData.isExistingMovie(toLower(movieTwo)))
	{
		cout << "One of the movies you listed is not in the database." << endl;
		return;
	}
	cout << "Both movies are in the database, please continue..." << endl;

	// Returns to main menu when action chosen is performed
	while (true)
	{
		// Print sub menu
		cout << "A -- to print all the actors in either of the movies." << endl;
		cout << "C -- to print all the common actors in both of the movies." << endl;
		cout << "O -- to print all the actors who are in one movie, but not in both." << endl;

		string userChoice;
		cin.sync();
		getline(cin, userChoice);
		userChoice = toupper(userChoice[0]);

		switch (userChoice[0])
		{
		case 'A':
			fileData.printAllActors(movieOne, movieTwo);
			break;
		case 'C':
			fileData.printCommonActors(movieOne, movieTwo);
			break;
		case 'O':
			fileData.printExclusiveActors(movieOne, movieTwo);
			break;
		case 'Q':
			// User chose to go back to main menu
			return;
		default:
			cout << "Invalid option." << endl;
		}
	}
}

void actorsAndCoActors(const IMDB& fileData)
{
	// Get actor name input
	cout << "Finding the co-actors of the actor by typing his/her name: ";
	string actorName;
	getline(cin, actorName);

	// Return if the  actor is not in the database
	if (!fileData.isExistingActor(actorName))
	{
		cout << "The actor you entered is not in the database." << endl;
		cin.sync();
		return;
	}
	fileData.printCoActors(actorName);
}

int main(int argc, char* argv[])
{
	// Check if correct number of command line arguments
	if (argc != CL_ARGUMENTS)
	{
		cout << "Warning: need exactly one command line argument." << endl;
		cout << "Usage: " << argv[0] << "inputfile_name";
		return 2;
	}

	ifstream movieData; // Text file containing movie data	
	movieData.open(argv[INPUT_FILE_INDEX]);
	if (movieData.fail())
	{
		cout << "Warning: cannot open file named " << argv[INPUT_FILE_INDEX];
		return 2;
	}

	IMDB fileData; // Object that will store all information from input file

	while (!movieData.eof())
	{
		string line;
		getline(movieData, line);
		string name, movie;
		istringstream iss(line);
		getline(iss, name, ',');

		// Extract extra white space
		iss >> ws;

		// Create a new set of movies assocatiated with name
		set<string> movies;

		while (getline(iss, movie, ','))
		{
			movies.insert(toLower(movie));
			// extract white space 
			iss >> ws;
		}
		// insert to IMDB object: fileData
		fileData.insert_an_actor(toLower(name), movies);
	}
	// close the input file
	movieData.close();

	// Since Actor's set is now ready, fill the movies set
	fileData.fillMoviesSet();

	while (true)
	{
		// Main Menu
		const int choice = mainMenu();

		switch (choice)
		{
		case -1:
			// Quit program
			cout << "Thank you for using my program, bye..." << endl;
			return 0;
		case 1:
			actorsInMoviesMenu(fileData);
			break;
		case 2:
			actorsAndCoActors(fileData);
			break;
		default:
			// Should not happen
			return 0;
		}
	}
}
