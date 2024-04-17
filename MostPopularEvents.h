#pragma once

#include <QMainWindow>
#include "Controller.h"
#include "ui_MostPopularEvents.h"

class MostPopularEvents : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	MostPopularEvents(Controller& controller, QWidget *parent = nullptr);
	~MostPopularEvents();
	void populateList();
	void update();

private:
	Ui::MostPopularEventsClass ui;
	Controller& controller;
};
