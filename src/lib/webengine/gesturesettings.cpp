#include "gesturesettings.h"
void GestureSettings::loadSettings()
{
    Settings settings;
    settings.beginGroup("Web-Browser-Settings");
    mouseDelay = settings.value("mouseDelay",210).toInt();
    tapZoomMax = settings.value("tapZoomMax",200).toInt();
    mouseThreshold = settings.value("mouseThreshold",20).toInt();
    enableFingerScrolling = settings.value("enableFingerScrolling",true).toBool();
    scrollPageOnly = settings.value("scrollPageOnly",true).toBool();
    contextMenuOnLongPress = settings.value("contextMenuOnLongPress",true).toBool();
    doubleTapZoom = settings.value("doubleTapZoom",true).toBool();
    settings.endGroup();
}