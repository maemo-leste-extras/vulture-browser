/* ============================================================
* Vulture Browser - fork of Falkon
* Copyright (C) 2010-2018 David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
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