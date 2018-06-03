#include "imdb.h"
#include <iostream>
#include "functions.h"
using namespace std;

IMDB::IMDB()
= default;

void IMDB::insert_an_actor(string actorName, set<string> movieTitles) const
{ actors_db.insert(std::make_pair(actorName, movieTitles)); }

void IMDB::insert_a_movie(string movieTitle, set<string> actorNames) const
{ movies_db.insert(std::make_pair(movieTitle, actorNames)); }

bool IMDB::isExistingMovie(const string& movieTitle) const
{ 	
	// Using count to find if a movie exists
	const short size = movies_db.count(toLower(movieTitle)); 
	return (size >= 1);
}

bool IMDB::isExistingActor(string actorName) const
{ return actors_db.count(toLower(actorName)); } 

set<string> IMDB::find_movies_for_an_actor(const string& actorName) const
{
	const auto search = actors_db.find(toLower(actorName)); // Declare iterator to search for the actor name
	if(search != actors_db.end()) // Check if the iterator "search" ran off the end of the map
	{
		// Actor found, return the set associated with the actor
		return search->second; // Pointer to value associated with the actorName
	}
	// Should not happen if the input was checked properly
	set<string> empty;
	return empty;
}

set<string> IMDB::find_actors_in_a_movie(const string& movieTitle) const
{
	const auto search = movies_db.find(toLower(movieTitle));
	if(search != movies_db.end())
	{
		// Movie found, return the set associated with the movie
		return search->second; // Pointer to the set of actors in given movie
	}
	// Should Not Happen if the input was checked properly
	set<string> empty;
	return empty; 
}
 
void IMDB::printCoActors(const string& actorName) const
{
	set<string> actorMovies = find_movies_for_an_actor(actorName);
	string movieName;

	// For every movie in set of movies, print the movies that the actor was in
	for (auto const& movie : actorMovies)
	{
		cout << "The co-actors of " << capitalize(actorName) << " in the movie \"" << capitalize(movie) << "\" are:" << endl;
		set<string> actorsInMovieSet = find_actors_in_a_movie(movie);
		
		// Print the associated actors and not the actor as defined by actorName
		for (auto const& actor : actorsInMovieSet)
		{
			if (actorName != actor)
				cout << capitalize(actor) << endl;
		}
		cout << "***********************************" << endl;
	}
}

void IMDB::printSet(const set<basic_string<char>>& set) const
{
	for (auto const& item : set)
		cout << capitalize(item) << endl;
}

void IMDB::printAllActors(const string& movieOne, const string& movieTwo) const
{
	// Get the actors in movie one and two
	set<string> actorSetOne = find_actors_in_a_movie(movieOne);
	set<string> actorSetTwo = find_actors_in_a_movie(movieTwo);

	// Join the two sets which makes no duplicates
	actorSetOne.insert(actorSetTwo.begin(), actorSetTwo.end());
	
	cout << "All actors in either of the two movies:" << endl;
	printSet(actorSetOne);
}

void IMDB::printCommonActors(const string& movieOne, const string& movieTwo) const
{
	// Get the actors in movie one and two
	set<string> actorSetOne = find_actors_in_a_movie(movieOne);
	set<string> actorSetTwo = find_actors_in_a_movie(movieTwo);
	set<string> commonSet;	// Set common actors in both movies

	for (auto const& actor : actorSetOne)
		for (auto const& comparedActor : actorSetTwo)
		{
			// If actor is in both sets, add actor to new set
			if (actor == comparedActor)
				commonSet.insert(actor);
		}
	cout << "Common actors in both movies:" << endl;
	printSet(commonSet);
}

void IMDB::printExclusiveActors(const string& movieOne, const string& movieTwo) const
{
	// Get the actors in movie one and two
	set<string> actorSetOne = find_actors_in_a_movie(movieOne);
	set<string> actorSetTwo = find_actors_in_a_movie(movieTwo);
	set<string> exclusiveSet = find_actors_in_a_movie(movieOne);	// In order  to delete from while comparing the two other sets

	exclusiveSet.insert(actorSetTwo.begin(), actorSetTwo.end());	// Set common actors in both movies

	for (auto const& actor : actorSetOne)
		for (auto const& comparedActor : actorSetTwo)
		{
			// If actor in both of the sets, delete the actor from exclusive set
			if (actor == comparedActor)
				exclusiveSet.erase(actor);
		}

	cout << "Actors only in one of two movies:" << endl;
	printSet(exclusiveSet);
}

void IMDB::fillMoviesSet() const
{
	IMDB temp = *this;

	// Iterate through the actors_db set
	for(auto const& i : actors_db )
	{
		// assigns the actor name to the new variable
		const string actorName = i.first;
		set<string> actor_names_set; // New set of actor names
		
		// Iterate through the set of movies 
		for (auto const& movieName : i.second)
		{
			// Inserts a pair containing the current movie and only the current actor to the set
			// For initialization of the movies set
			actor_names_set.insert(actorName);
			pair <string, set<string>> && newPair = make_pair(movieName, actor_names_set);
			temp.movies_db.insert(newPair);
		}
	}
	this->movies_db = temp.movies_db;

	// movies_db MUST BE INTIALIZED FIRST 
	// Iterate through the actors_db
	for(auto const& actor : actors_db)
		// Iterate through movies associated with actors
		for(auto const& movieName : actor.second)
		{
			// Iterator to get the map of the movie in movies_db
			const auto search = movies_db.find(movieName);
			// Insert the actor into the movie
			search->second.insert(actor.first);
		}
}
