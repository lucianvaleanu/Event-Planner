#include "EventPlanner.h"

EventPlanner::EventPlanner(Controller& controller, Person person, QWidget* parent)
    : QMainWindow(parent), controller(controller), person(person)
{
    ui.setupUi(this);
    this->controller.registerObserver(this);
    this->ui.personLocation->setText(QString::fromStdString("Latitude " + std::to_string(person.getLoc().latitude) +
        ", Longitude " + std::to_string(person.getLoc().longitude)));
    this->setWindowTitle(QString::fromStdString(person.getName()));
    this->ui.partyDescriptionLabel->setText("");
    populateList();
    this->ui.goingButton->hide();
    if (!person.getOrganiser())
    {
        this->ui.inputDay->hide();
        this->ui.inputDescription->hide();
        this->ui.inputMonth->hide();
        this->ui.inputLatitude->hide();
        this->ui.inputLongitude->hide();
        this->ui.inputName->hide();
        this->ui.inputYear->hide();
        this->ui.addEventButton->hide();
        this->ui.descLabe->hide();
        this->ui.dLabel->hide();
        this->ui.latLabel->hide();
        this->ui.longLabel->hide();
        this->ui.mLabel->hide();
        this->ui.nameLabel->hide();
        this->ui.yLabel->hide();
        this->ui.listOfInvited->hide();
    }
    else
    {
        this->ui.listOfInvited->hide();
    }
}

EventPlanner::~EventPlanner()
{
    this->controller.unregisterObserver(this);
}

void EventPlanner::update()
{
    populateList();
}

void EventPlanner::populateList()
{
    this->ui.eventsList->clear();
    std::vector<Event> events = controller.getEvents();
    std::sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
        return(e1.getDate() < e2.getDate());
        });
    for (const auto& e : events)
    {
        std::string loc = std::to_string(e.getLoc().latitude) + "," + std::to_string(e.getLoc().latitude);
        std::string date = std::to_string(e.getDate().d) + "-" + std::to_string(e.getDate().m) + "-" + std::to_string(e.getDate().y);
        std::string text = e.getName() + "|" + loc + "|" + date;
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(e.getOrganiser() + "|" + text) };
        if (person.getOrganiser())
            if (e.getOrganiser() == person.getName())
            {
                QBrush color{ Qt::green };
                item->setBackground(color);
            }
        this->ui.eventsList->addItem(item);
    }
}

void EventPlanner::populateInvited()
{
    std::stringstream ss(this->ui.eventsList->currentItem()->text().toStdString());
    std::string name, lat, longit;
    std::getline(ss, name, '|');
    std::getline(ss, name, '|');
    std::getline(ss, lat, ',');
    std::getline(ss, longit, '|');
    Location loc{ std::stoi(lat),std::stoi(longit) };
    Event& ev = controller.getEvent(name);
    this->ui.partyDescriptionLabel->setText(QString::fromStdString(ev.getDesc()));
    this->ui.listOfInvited->show();
    std::vector<std::string> invited = ev.getInvited();
    this->ui.listOfInvited->clear();
    for (const auto& i : invited)
    {
        this->ui.listOfInvited->addItem(QString::fromStdString(i));
    }
}

void EventPlanner::checkBoxList()
{
    if (this->ui.checkBox->isChecked())
    {
        std::vector<Event> events = controller.getEventsByRadius(person.getLoc());
        std::sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
            return(e1.getDate() < e2.getDate());
            });
        this->ui.eventsList->clear();
        for (const auto& e : events)
        {
            std::string loc = std::to_string(e.getLoc().latitude) + "," + std::to_string(e.getLoc().latitude);
            std::string date = std::to_string(e.getDate().d) + "-" + std::to_string(e.getDate().m) + "-" + std::to_string(e.getDate().y);
            std::string text = e.getName() + "|" + loc + "|" + date;
            QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(e.getOrganiser() + "|" + text) };
            if (person.getOrganiser())
                if (e.getOrganiser() == person.getName())
                {
                    QBrush color{ Qt::green };
                    item->setBackground(color);
                }
            this->ui.eventsList->addItem(item);
        }
    }
    else {
        populateList();
    }

}

void EventPlanner::listClickEvent()
{
    if (person.getOrganiser())
    {
        std::stringstream ss(this->ui.eventsList->currentItem()->text().toStdString());
        std::string name, lat, longit;
        std::getline(ss, name, '|');
        std::getline(ss, name, '|');
        std::getline(ss, lat, ',');
        std::getline(ss, longit, '|');
        Location loc{ std::stoi(lat),std::stoi(longit) };
        Event& ev = controller.getEvent(name);
        this->ui.partyDescriptionLabel->setText(QString::fromStdString(ev.getDesc()));
        this->ui.listOfInvited->show();
        std::vector<std::string> invited = ev.getInvited();
        this->ui.listOfInvited->clear();
        for (const auto& i : invited)
        {
            this->ui.listOfInvited->addItem(QString::fromStdString(i));
        }

    }
    else
    {
        std::stringstream ss(this->ui.eventsList->currentItem()->text().toStdString());
        std::string name;
        std::getline(ss, name, '|');
        std::getline(ss, name, '|');
        Event& ev = controller.getEvent(name);
        this->ui.partyDescriptionLabel->setText(QString::fromStdString(ev.getDesc()));
        if (!ev.isPersonAttending(person.getName()))
            this->ui.goingButton->show();
    }
}

void EventPlanner::goingEvent()
{
    std::stringstream ss(this->ui.eventsList->currentItem()->text().toStdString());
    std::string name;
    std::getline(ss, name, '|');
    std::getline(ss, name, '|');
    Event& ev = controller.getEvent(name);
    ev.invite(person.getName());
    controller.notify();
    controller.saveEvents();
    this->ui.goingButton->hide();
}

void EventPlanner::addEvent()
{
    std::string name = this->ui.inputName->text().toStdString();
    std::string desc = this->ui.inputDescription->text().toStdString();
    std::string lat = this->ui.inputLatitude->text().toStdString();
    std::string longit = this->ui.inputLongitude->text().toStdString();
    std::string d = this->ui.inputDay->text().toStdString();
    std::string m = this->ui.inputMonth->text().toStdString();
    std::string y = this->ui.inputYear->text().toStdString();
    if (name.empty() || lat.empty() || longit.empty() || d.empty() || m.empty() || y.empty())
    {
        this->ui.inputName->clear();
        this->ui.inputDescription->clear();
        this->ui.inputLatitude->clear();
        this->ui.inputLongitude->clear();
        this->ui.inputDay->clear();
        this->ui.inputMonth->clear();
        this->ui.inputYear->clear();
        QMessageBox::critical(this, "Error", "Fields cannot be empty!");
        return;
    }

    Location loc{ std::stoi(lat),std::stoi(longit) };
    Date date{ std::stoi(d) ,std::stoi(m) ,std::stoi(y) };

    if (controller.isEvent(name, loc))
    {
        Event event{ person.getName(),name,desc,date,loc };
        controller.addEvent(event);
    }
    else {
        this->ui.inputName->clear();
        this->ui.inputDescription->clear();
        this->ui.inputLatitude->clear();
        this->ui.inputLongitude->clear();
        this->ui.inputDay->clear();
        this->ui.inputMonth->clear();
        this->ui.inputYear->clear();
        QMessageBox::critical(this, "Error!", "Event already exists!");
        return;
    }

    this->ui.inputName->clear();
    this->ui.inputDescription->clear();
    this->ui.inputLatitude->clear();
    this->ui.inputLongitude->clear();
    this->ui.inputDay->clear();
    this->ui.inputMonth->clear();
    this->ui.inputYear->clear();
}