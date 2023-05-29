#ifndef __GESTURE_SETTINGS_H
#define __GESTURE_SETTINGS_H
#include "settings.h"

class FALKON_EXPORT GestureSettings
{
 public:
 void loadSettings();
 int mouseDelay;
 int mouseThreshold;
 bool enableFingerScrolling;
 bool scrollPageOnly;
 bool contextMenuOnLongPress;
};

#define gestureSettings mApp->_gestureSettings()

#endif