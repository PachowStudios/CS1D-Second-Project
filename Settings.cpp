#include "Settings.h"

Settings AppSettings;

Settings::Settings()
	: qSettings("ScrumShot", "StadiumTripPlanner")
{
	dataFile = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DataLocation)
		     + DataFilePath;
}

bool Settings::LoadCredentials()
{
	if (qSettings.contains(UsernamePath) &&
		qSettings.contains(PasswordPath))
	{
		adminLogin.SetUsername(qSettings.value(UsernamePath).toString());
		adminLogin.SetPassword(qSettings.value(PasswordPath).toString());
	}
	else
		return false;

	return true;
}

void Settings::SaveCredentials()
{
	qSettings.setValue(UsernamePath, adminLogin.username);
	qSettings.setValue(PasswordPath, adminLogin.passwordHash);
}