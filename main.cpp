#include "EventPlanner.h"
#include "MostPopularEvents.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller{ "events.txt","persons.txt" };
    std::vector<Person> persons = controller.getPersons();
    for (const auto& p : persons)
    {
        EventPlanner* w = new EventPlanner{ controller,p };
        w->show();
    }
    MostPopularEvents w{ controller };
    w.show();
    return a.exec();
}
