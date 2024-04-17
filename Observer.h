#pragma once
#include <vector>

class Observer {
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};

class Subject {
private:
	std::vector<Observer*> observers;
public:
	virtual ~Subject() {}
	void registerObserver(Observer* observer)
	{
		observers.push_back(observer);
	}
	void unregisterObserver(Observer* observer)
	{
		this->observers.erase(std::find(this->observers.begin(), this->observers.end(), observer));
	}
	void notify()
	{
		for (auto observer : observers)
			observer->update();
	}
};