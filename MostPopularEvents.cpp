#include "MostPopularEvents.h"

MostPopularEvents::MostPopularEvents(Controller& controller, QWidget* parent)
	: QMainWindow(parent), controller(controller)
{
	ui.setupUi(this);
	this->controller.registerObserver(this);
	populateList();
}

MostPopularEvents::~MostPopularEvents()
{
	this->controller.unregisterObserver(this);
}

void MostPopularEvents::populateList()
{
	this->ui.listOfInvited->clear();
	std::vector<Event> events = controller.getEvents();
	std::sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
		return e1.getInvited().size() > e2.getInvited().size();
		});
	for (const auto& e : events)
	{
		std::string loc = std::to_string(e.getLoc().latitude) + "," + std::to_string(e.getLoc().latitude);
		std::string date = std::to_string(e.getDate().d) + "-" + std::to_string(e.getDate().m) + "-" + std::to_string(e.getDate().y);
		std::string text = e.getOrganiser() + "|" + e.getName() + "|" + loc + "|" + date + "|" + std::to_string(e.getInvited().size());
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(text)};
		this->ui.listOfInvited->addItem(item);
	}
}

void MostPopularEvents::update()
{
	populateList();
}
