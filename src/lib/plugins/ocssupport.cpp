/* ============================================================
* Falkon - Qt web browser
* Copyright (C) 2019 David Rosca <nowrep@gmail.com>
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
#include "ocssupport.h"
#include "pluginproxy.h"
#include "datapaths.h"
#include "networkmanager.h"
#include "desktopfile.h"
#include "desktopnotificationsfactory.h"
#include "mainapplication.h"

#include <QDir>
#include <QBuffer>
#include <QByteArray>
#include <QUrlQuery>
#include <QNetworkReply>


Q_GLOBAL_STATIC(OcsSupport, qz_ocs_support)

OcsSupport::OcsSupport(QObject *parent)
    : QObject(parent)
{
}

bool OcsSupport::handleUrl(const QUrl &url)
{
    return true;
}

// static
OcsSupport *OcsSupport::instance()
{
    return qz_ocs_support();
}
