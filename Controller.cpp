#include "Controller.h"

std::vector<Event> Controller::getEventsByRadius(const Location& pLoc) const
{
    std::vector<Event> outEvents;
    for (const auto& e : events)
    {
        int distance = sqrt((pLoc.latitude - e.getLoc().latitude) * (pLoc.latitude - e.getLoc().latitude) +
            (pLoc.longitude - e.getLoc().longitude) * (pLoc.longitude - e.getLoc().longitude));
        if (distance <= 5)
            outEvents.push_back(e);
    }
    return outEvents;
}

Event& Controller::getEvent(const std::string& name)
{
    for (auto& e : events)
        if (e.getName() == name)
            return e;
    return events[0];
}

bool Controller::isEvent(const std::string& name, const Location& loc)
{
    for (const auto& e : events)
        if (e.getName() == name && e.getLoc() == loc)
            return false;
    return true;
}

void Controller::readEvents()
{
    std::ifstream file(eventsFile);
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string organiser, name, desc, lat, longit, d, m, y, inv;
        std::getline(ss, organiser, '|');
        std::getline(ss, name, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, lat, ',');
        std::getline(ss, longit, '|');
        std::getline(ss, d, '-');
        std::getline(ss, m, '-');
        std::getline(ss, y, '|');
        std::getline(ss, inv);
        Location loc{ std::stoi(lat),std::stoi(longit) };
        Date date{ std::stoi(d),std::stoi(m) ,std::stoi(y) };
        Event event{ organiser,name,desc,date,loc };
        std::stringstream ssInv(inv);
        std::string person;
        while (std::getline(ssInv, person,','))
            event.invite(person);

        events.push_back(event);
    }
    file.close();
}

void Controller::readPersons()
{
    std::ifstream file(personsFile);
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, lat, longit;
        bool organiser;
        std::getline(ss, name, '|');
        std::getline(ss, lat, ',');
        std::getline(ss, longit, '|');
        ss >> organiser;
        Location loc{ std::stoi(lat),std::stoi(longit) };
        Person person{ name,loc,organiser };
        persons.push_back(person);
    }
}

void Controller::saveEvents()
{
    std::ofstream file(eventsFile);
    for (const auto& e : events)
    {
        file << e.getOrganiser() << "|" << e.getName() << "|" << e.getDesc() << "|" << e.getLoc().latitude << "," << e.getLoc().longitude << "|" <<
            e.getDate().d << "-" << e.getDate().m << "-" << e.getDate().y<<"|";
        if (e.getInvited().size() > 0)
        {
            std::vector<std::string> invited = e.getInvited();
            for (int i = 0; i < invited.size() - 1; ++i)
                file << invited[i] << ",";
          if(invited.size()>0)
                file << invited[invited.size() - 1];
        }
        file << "\n";
    }
    file.close();
}
