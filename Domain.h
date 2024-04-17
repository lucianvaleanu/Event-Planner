#pragma once
#include <string>
#include <vector>

typedef struct Location {
	int latitude, longitude;
	bool operator==(const Location& other)
	{
		return(latitude == other.latitude && longitude == other.longitude);
	}
}Location;

typedef struct Date {
	int d, m, y;
	bool operator<(const Date& other)
	{
		if (y < other.y)
			return true;
		else if (y > other.y)
			return false;

		if (m < other.m)
			return true;
		else if (m > other.m)
			return false;

		if (d < other.d)
			return true;
		else if (d > other.d)
			return false;

		return false;
	}
}Date;

class Event {
private:
	std::string organiser, name, description;
	Date date;
	Location location;
	std::vector<std::string> invited;
public:
	Event(const std::string& _org, const std::string& _name, const std::string& _desc, const Date& date, const Location& loc)
		:organiser(_org), name(_name), description(_desc), date(date), location(loc) {}

	std::string getOrganiser()const { return organiser; }
	std::string getName()const { return name; }
	std::string getDesc()const { return description; }
	Date getDate()const { return date; }
	Location getLoc()const { return location; }
	void invite(const std::string& person) { invited.push_back(person); }
	std::vector<std::string> getInvited()const { return invited; }
	bool isPersonAttending(const std::string& person)
	{
		for (const auto& i : invited)
			if (i == person)
				return true;
		return false;
	}

};

class Person {
private:
	std::string name;
	Location location;
	bool organiser;
public:
	Person(const std::string& name, const Location& loc, const bool org) : name(name), location(loc), organiser(org) {}
	std::string getName()const { return name; }
	Location getLoc()const { return location; }
	bool getOrganiser()const { return organiser; }

};