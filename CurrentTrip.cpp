#include "CurrentTrip.h"

CurrentTrip::CurrentTrip(StadiumList trip, QWidget *parent)
	: trip(trip), QDialog(parent)
{
	ui.setupUi(this);
}