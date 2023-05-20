#include "gesturesettings.h"
void GestureSettings::loadSettings()
{
    Settings settings;
    settings.beginGroup("Web-Browser-Settings");
    mouseDelay = settings.value("mouseDelay",210).toInt();
    mouseThreshold = settings.value("mouseThreshold",20).toInt();
    enableFingerScrolling = settings.value("enableFingerScrolling",true).toBool();
    settings.endGroup();
}