#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "Controller.h"
#include "ui_EventPlanner.h"

class EventPlanner : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    EventPlanner(Controller& controller, Person person, QWidget* parent = nullptr);
    ~EventPlanner();

    void update();

    void populateList();

    void populateInvited();

public slots:
    void addEvent();
    void checkBoxList();
    void listClickEvent();
    void goingEvent();

private:
    Ui::EventPlannerClass ui;
    Controller& controller;
    Person person;
};
