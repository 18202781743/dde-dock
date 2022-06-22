/*
 * Copyright (C) 2011 ~ 2021 Uniontech Technology Co., Ltd.
 *
 * Author:     fanpengcheng <fanpengcheng@uniontech.com>
 *
 * Maintainer: fanpengcheng <fanpengcheng@uniontech.com>
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
#ifndef MODULE_WIDGET_H
#define MODULE_WIDGET_H

#ifdef USE_AM
#include "dockinterface.h"
#else
#include <com_deepin_dde_daemon_dock.h>
#endif

#include <QScrollArea>

#include <dtkwidget_global.h>

#include "com_deepin_dde_dock.h"
#include "config_watcher.h"

namespace dcc {
namespace widgets {
class ComboxWidget;
class TitledSliderItem;
}
}

DWIDGET_BEGIN_NAMESPACE
class DListView;
class DTipLabel;
DWIDGET_END_NAMESPACE

class TitleLabel;
class QStandardItemModel;

using namespace dcc::widgets;
using namespace dcc_dock_plugin;

#ifdef USE_AM
using DBusDock = org::deepin::dde::daemon::DdeDock;
#else
using DBusDock = com::deepin::dde::daemon::Dock;
#endif

using DBusInter = com::deepin::dde::Dock;

class ModuleWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ModuleWidget(QWidget *parent = nullptr);
    ~ ModuleWidget();

private:
    void initUI();
    bool isCopyMode();

private Q_SLOTS:
    void updateSliderValue();
    void updateItemCheckStatus(const QString &name, bool visible);

private:
    ComboxWidget *m_modeComboxWidget;
    ComboxWidget *m_positionComboxWidget;
    ComboxWidget *m_stateComboxWidget;

    TitledSliderItem *m_sizeSlider;

    TitleLabel *m_screenSettingTitle;
    ComboxWidget *m_screenSettingComboxWidget;

    TitleLabel *m_pluginAreaTitle;
    DTK_WIDGET_NAMESPACE::DTipLabel *m_pluginTips;
    DTK_WIDGET_NAMESPACE::DListView *m_pluginView;
    QStandardItemModel *m_pluginModel;

    DBusDock *m_daemonDockInter;
    DBusInter *m_dockInter;
    ConfigWatcher *m_dconfigWatcher;

    bool m_sliderPressed;
};

#endif // MODULE_WIDGET_H
