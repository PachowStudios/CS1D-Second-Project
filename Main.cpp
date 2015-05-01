#include "StadiumTripPlanner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	(new StadiumTripPlanner)->show();

	return app.exec();
}
