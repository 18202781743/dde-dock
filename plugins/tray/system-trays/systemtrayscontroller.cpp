/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "systemtrayscontroller.h"
#include "pluginsiteminterface.h"
#include "utils.h"

#include <com_deepin_daemon_airplanemode.h>

#include <QDebug>
#include <QDir>

using DBusAirplaneMode = com::deepin::daemon::AirplaneMode;

SystemTraysController::SystemTraysController(QObject *parent)
    : AbstractPluginsController(parent)
{
    setObjectName("SystemTray");
}

void SystemTraysController::itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    QMap<PluginsItemInterface *, QMap<QString, QObject *>> &mPluginsMap = pluginsMap();

    SystemTrayItem *item = nullptr;

    // check if same item added
    if (mPluginsMap.contains(itemInter))
        if (mPluginsMap[itemInter].contains(itemKey)) {
            if (itemKey != "airplane-mode-key")
                return;

            item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
        }

    if (!item)
        item = new SystemTrayItem(itemInter, itemKey);

    connect(item, &SystemTrayItem::itemVisibleChanged, this, [=] (bool visible){
        if (visible) {
            emit pluginItemAdded(itemKey, item);
        }
        else {
            emit pluginItemRemoved(itemKey, item);
        }
    }, Qt::QueuedConnection);

    mPluginsMap[itemInter][itemKey] = item;

    if (itemInter->pluginName() == "airplane-mode") {
        // 飞行模式显示条件： gsettings为true且飞行模式已开启
        DBusAirplaneMode airplaneBus("com.deepin.daemon.AirplaneMode",
                                                   "/com/deepin/daemon/AirplaneMode",
                                                   QDBusConnection::systemBus(),
                                                   this);
        if (!Utils::SettingValue(QString("com.deepin.dde.dock.module.airplane-mode"), QByteArray(), "enable", true).toBool() || !airplaneBus.enabled()) {
            emit pluginItemRemoved(itemKey, item);
            return;
        }
    }

    // 隐藏的插件不加入到布局中
    if (Utils::SettingValue(QString("com.deepin.dde.dock.module.") + itemInter->pluginName(), QByteArray(), "enable", true).toBool()) {
        emit pluginItemAdded(itemKey, item);
    }
}

void SystemTraysController::itemUpdate(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    SystemTrayItem *item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
    if (!item)
        return;

    item->update();

    emit pluginItemUpdated(itemKey, item);
}

void SystemTraysController::itemRemoved(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    SystemTrayItem *item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
    if (!item)
        return;

    item->detachPluginWidget();

    emit pluginItemRemoved(itemKey, item);

    QMap<PluginsItemInterface *, QMap<QString, QObject *>> &mPluginsMap = pluginsMap();
    mPluginsMap[itemInter].remove(itemKey);

    // do not delete the itemWidget object(specified in the plugin interface)
    item->centralWidget()->setParent(nullptr);

    // just delete our wrapper object(PluginsItem)
    item->deleteLater();
}

void SystemTraysController::requestWindowAutoHide(PluginsItemInterface * const itemInter, const QString &itemKey, const bool autoHide)
{
    SystemTrayItem *item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
    if (!item)
        return;

    Q_EMIT item->requestWindowAutoHide(autoHide);
}

void SystemTraysController::requestRefreshWindowVisible(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    SystemTrayItem *item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
    if (!item)
        return;

    Q_EMIT item->requestRefershWindowVisible();
}

void SystemTraysController::requestSetAppletVisible(PluginsItemInterface * const itemInter, const QString &itemKey, const bool visible)
{
    SystemTrayItem *item = static_cast<SystemTrayItem *>(pluginItemAt(itemInter, itemKey));
    if (!item)
        return;

    if (visible) {
        item->showPopupApplet(itemInter->itemPopupApplet(itemKey));
    } else {
        item->hidePopup();
    }
}

int SystemTraysController::systemTrayItemSortKey(const QString &itemKey)
{
    auto inter = pluginInterAt(itemKey);

    if (!inter) {
        return -1;
    }

    return inter->itemSortKey(itemKey);
}

void SystemTraysController::setSystemTrayItemSortKey(const QString &itemKey, const int order)
{
    auto inter = pluginInterAt(itemKey);

    if (!inter) {
        return;
    }

    inter->setSortKey(itemKey, order);
}

const QVariant SystemTraysController::getValueSystemTrayItem(const QString &itemKey, const QString &key, const QVariant &fallback)
{
    auto inter = pluginInterAt(itemKey);

    if (!inter) {
        return QVariant();
    }

    return getValue(inter, key, fallback);
}

void SystemTraysController::saveValueSystemTrayItem(const QString &itemKey, const QString &key, const QVariant &value)
{
    auto inter = pluginInterAt(itemKey);

    if (!inter) {
        return;
    }

    saveValue(inter, key, value);
}

void SystemTraysController::startLoader()
{
    QString pluginsDir("../plugins/system-trays");
    if (!QDir(pluginsDir).exists()) {
        pluginsDir = "/usr/lib/dde-dock/plugins/system-trays";
    }
    qDebug() << "using system tray plugins dir:" << pluginsDir;

    AbstractPluginsController::startLoader(new PluginLoader(pluginsDir, this));
}
