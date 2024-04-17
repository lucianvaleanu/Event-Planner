#pragma once
#include "Observer.h"
#include "Domain.h"
#include <sstream>
#include <fstream>
#include <algorithm>

class Controller :public Subject
{
private:
	std::vector<Event> events;
	std::vector<Person> persons;
	std::string eventsFile, personsFile;
public:
	Controller(const std::string& f1, const std::string& f2) :eventsFile(f1), personsFile(f2)
	{
		readEvents();
		readPersons();
	}

	std::vector<Event> getEvents()const { return events; }
	std::vector<Person> getPersons()const { return persons; }
	std::vector<Event> getEventsByRadius(const Location& pLoc)const;

	void addEvent(const Event& event) {
		events.push_back(event);
		saveEvents();
		notify();
	}

	Event& getEvent(const std::string& name);

	bool isEvent(const std::string& name, const Location& loc);

	void readEvents();
	void readPersons();
	void saveEvents();

};

