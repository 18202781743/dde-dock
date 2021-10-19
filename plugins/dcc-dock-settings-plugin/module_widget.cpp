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
#include "module_widget.h"
#include "gsetting_watcher.h"

#include <widgets/comboxwidget.h>
#include <widgets/titledslideritem.h>
#include <widgets/dccslider.h>
#include <widgets/titlelabel.h>

#include <DSlider>
#include <DListView>
#include <DTipLabel>

#include <QLabel>
#include <QVBoxLayout>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusError>
#include <QMap>
#include <QScrollArea>
#include <QScroller>
#include <QComboBox>

DWIDGET_USE_NAMESPACE

enum DisplayMode {
    Fashion     = 0,
    Efficient   = 1,
};

enum HideMode {
    KeepShowing     = 0,
    KeepHidden      = 1,
    SmartHide       = 3,
};

enum Position {
    Top         = 0,
    Right       = 1,
    Bottom      = 2,
    Left        = 3,
};

ModuleWidget::ModuleWidget(QWidget *parent)
    : QScrollArea(parent)
    , m_modeComboxWidget(new ComboxWidget)
    , m_positionComboxWidget(new ComboxWidget)
    , m_stateComboxWidget(new ComboxWidget)
    , m_sizeSlider(new TitledSliderItem(tr("Size")))
    , m_screenSettingTitle(new TitleLabel(tr("Multiple Displays")))
    , m_screenSettingComboxWidget(new ComboxWidget)
    , m_pluginAreaTitle(new TitleLabel(tr("Plugin Area")))
    , m_pluginTips(new DTipLabel(tr("Select which icons appear in the Dock")))
    , m_pluginView(new DListView(this))
    , m_pluginModel(new QStandardItemModel(this))
    , m_daemonDockInter(new DBusDock("com.deepin.dde.daemon.Dock", "/com/deepin/dde/daemon/Dock", QDBusConnection::sessionBus(), this))
    , m_dockInter(new DBusInter("com.deepin.dde.Dock", "/com/deepin/dde/Dock", QDBusConnection::sessionBus(), this))
    , m_gsettingsWatcher(new GSettingWatcher("com.deepin.dde.control-center", "personalization", this))
{
    initUI();

    connect(m_dockInter, &DBusInter::pluginVisibleChanged, this, &ModuleWidget::updateItemCheckStatus);
}

ModuleWidget::~ModuleWidget()
{
    delete m_modeComboxWidget;
    delete m_positionComboxWidget;
    delete m_stateComboxWidget;
    delete m_sizeSlider;
    delete m_screenSettingTitle;
    delete m_screenSettingComboxWidget;
    delete m_pluginAreaTitle;
    delete m_pluginTips;
}

void ModuleWidget::initUI()
{
    setFrameShape(QFrame::NoFrame);
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    static QMap<QString, int> g_modeMap = {{tr("Fashion mode"), Fashion}
                                           , {tr("Efficient mode"), Efficient}};
    // 模式
    m_modeComboxWidget->setTitle(tr("Mode"));
    m_modeComboxWidget->addBackground();
    m_modeComboxWidget->setComboxOption(QStringList() << tr("Fashion mode") << tr("Efficient mode"));
    m_modeComboxWidget->setCurrentText(g_modeMap.key(m_daemonDockInter->displayMode()));
    connect(m_modeComboxWidget, &ComboxWidget::onSelectChanged, this, [ = ] (const QString &text) {
        m_daemonDockInter->setDisplayMode(g_modeMap.value(text));
    });
    connect(m_daemonDockInter, &DBusDock::DisplayModeChanged, this, [ = ] (int value) {
        DisplayMode mode = static_cast<DisplayMode>(value);
        if (g_modeMap.key(mode) == m_modeComboxWidget->comboBox()->currentText())
            return;

        m_modeComboxWidget->setCurrentText(g_modeMap.key(mode));
    });
    layout->addWidget(m_modeComboxWidget);
    m_gsettingsWatcher->bind("displayMode", m_modeComboxWidget);// 转换settingName?

    static QMap<QString, int> g_positionMap = {{tr("Top"), Top}
                                               , {tr("Bottom"), Bottom}
                                               , {tr("Left"), Left}
                                               , {tr("Right"), Right}};
    // 位置
    m_positionComboxWidget->setTitle(tr("Location"));
    m_positionComboxWidget->addBackground();
    m_positionComboxWidget->setComboxOption(QStringList() << tr("Top") << tr("Bottom") << tr("Left") << tr("Right"));
    m_positionComboxWidget->setCurrentText(g_positionMap.key(m_daemonDockInter->position()));
    connect(m_positionComboxWidget, &ComboxWidget::onSelectChanged, this, [ = ] (const QString &text) {
        m_daemonDockInter->setPosition(g_positionMap.value(text));
    });
    connect(m_daemonDockInter, &DBusDock::PositionChanged, this, [ = ] (int position) {
        Position pos = static_cast<Position>(position);
        if (g_positionMap.key(pos) == m_positionComboxWidget->comboBox()->currentText())
            return;

        m_positionComboxWidget->setCurrentText(g_positionMap.key(pos));
    });
    layout->addWidget(m_positionComboxWidget);
    m_gsettingsWatcher->bind("position", m_positionComboxWidget);

    static QMap<QString, int> g_stateMap = {{tr("Keep shown"), KeepShowing}
                                            , {tr("Keep hidden"), KeepHidden}
                                            , {tr("Smart hide"), SmartHide}};
    // 状态
    m_stateComboxWidget->setTitle(tr("Status"));
    m_stateComboxWidget->addBackground();
    m_stateComboxWidget->setComboxOption(QStringList() << tr("Keep shown") << tr("Keep hidden") << tr("Smart hide"));
    m_stateComboxWidget->setCurrentText(g_stateMap.key(m_daemonDockInter->hideMode()));
    connect(m_stateComboxWidget, &ComboxWidget::onSelectChanged, this, [ = ] (const QString &text) {
        m_daemonDockInter->setHideMode(g_stateMap.value(text));
    });
    connect(m_daemonDockInter, &DBusDock::HideModeChanged, this, [ = ] (int value) {
        HideMode mode = static_cast<HideMode>(value);
        if (g_stateMap.key(mode) == m_stateComboxWidget->comboBox()->currentText())
            return;

        m_stateComboxWidget->setCurrentText(g_stateMap.key(mode));
    });
    layout->addWidget(m_stateComboxWidget);
    m_gsettingsWatcher->bind("hideMode", m_stateComboxWidget);

    // 高度调整控件
    m_sizeSlider->addBackground();
    m_sizeSlider->slider()->setRange(40, 100);
    QStringList ranges;
    ranges << tr("Small") << "" << tr("Large");
    m_sizeSlider->setAnnotations(ranges);
    connect(m_daemonDockInter, &DBusDock::DisplayModeChanged, this, &ModuleWidget::updateSliderValue);
    connect(m_daemonDockInter, &DBusDock::WindowSizeFashionChanged, this, &ModuleWidget::updateSliderValue);
    connect(m_daemonDockInter, &DBusDock::WindowSizeEfficientChanged, this, &ModuleWidget::updateSliderValue);
    connect(m_sizeSlider->slider(), &DSlider::valueChanged, m_sizeSlider->slider(), &DSlider::sliderMoved);
    connect(m_sizeSlider->slider(), &DSlider::sliderMoved, this, [ = ] (int value) {
        int lastValue = 0;
        if (m_daemonDockInter->displayMode() == DisplayMode::Fashion) {
            lastValue = int(m_daemonDockInter->windowSizeFashion());
        } else if (m_daemonDockInter->displayMode() == DisplayMode::Efficient) {
            lastValue = int(m_daemonDockInter->windowSizeEfficient());
        } else {
            Q_ASSERT_X(false, __FILE__, "not supported");
        }

        // 得到绝对偏移值
        int offset = value - lastValue;

        m_dockInter->resizeDock(offset);
    });

    updateSliderValue();
    m_gsettingsWatcher->bind("sizeSlider", m_sizeSlider);

    layout->addWidget(m_sizeSlider);

    // 多屏显示设置
    if (QDBusConnection::sessionBus().interface()->isServiceRegistered("com.deepin.dde.Dock")) {
        static QMap<QString, bool> g_screenSettingMap = {{tr("Follow the mouse"), false}
                                                         , {tr("Only show in primary"), true}};

        layout->addSpacing(10);
        layout->addWidget(m_screenSettingTitle);
        m_screenSettingComboxWidget->setTitle(tr("Show Dock"));
        m_screenSettingComboxWidget->addBackground();
        m_screenSettingComboxWidget->setComboxOption(QStringList() << tr("On screen where the cursor is") << tr("Only on main screen"));
        m_screenSettingComboxWidget->setCurrentText(g_screenSettingMap.key(m_dockInter->showInPrimary()));
        connect(m_screenSettingComboxWidget, &ComboxWidget::onSelectChanged, this, [ = ] (const QString &text) {
            m_dockInter->setShowInPrimary(g_screenSettingMap.value(text));
        });
        // 这里不会生效，但实际场景中也不存在有其他可配置的地方，可以不用处理
        connect(m_dockInter, &DBusInter::ShowInPrimaryChanged, this, [ = ] (bool showInPrimary) {
            if (m_screenSettingComboxWidget->comboBox()->currentText() == g_screenSettingMap.key(showInPrimary))
                return;

            m_screenSettingComboxWidget->blockSignals(true);
            m_screenSettingComboxWidget->setCurrentText(g_screenSettingMap.key(showInPrimary));
            m_screenSettingComboxWidget->blockSignals(false);
        });
        layout->addWidget(m_screenSettingComboxWidget);
        m_gsettingsWatcher->bind("multiScreenArea", m_screenSettingTitle);
        m_gsettingsWatcher->bind("multiScreenArea", m_screenSettingComboxWidget);
    }

    // 插件区域
    QDBusPendingReply<QStringList> reply = m_dockInter->GetLoadedPlugins();
    QStringList plugins = reply.value();
    if (reply.error().type() != QDBusError::ErrorType::NoError) {
        qWarning() << "dbus call failed, method: 'GetLoadedPlugins()'";
    } else {
        const QMap<QString, QString> &pluginIconMap = {{"assistant",        ":/icons/plugins/assistant.svg"}
                                                       , {"show-desktop",   ":/icons/plugins/desktop.svg"}
                                                       , {"onboard",        ":/icons/plugins/keyboard.svg"}
                                                       , {"notifications",  ":/icons/plugins/notify.svg"}
                                                       , {"shutdown",       ":/icons/plugins/power.svg"}
                                                       , {"multitasking",   ":/icons/plugins/task.svg"}
                                                       , {"datetime",       ":/icons/plugins/time.svg"}
                                                       , {"trash",          ":/icons/plugins/trash.svg"}};
        if (plugins.size() != 0) {
            layout->addSpacing(10);
            layout->addWidget(m_pluginAreaTitle);
            m_gsettingsWatcher->bind("pluginArea", m_pluginAreaTitle);

            DFontSizeManager::instance()->bind(m_pluginTips, DFontSizeManager::T8);
            m_pluginTips->adjustSize();
            m_pluginTips->setWordWrap(true);
            m_pluginTips->setContentsMargins(10, 5, 10, 5);
            m_pluginTips->setAlignment(Qt::AlignLeft);
            layout->addWidget(m_pluginTips);

            m_pluginView->setAccessibleName("pluginList");
            m_pluginView->setBackgroundType(DStyledItemDelegate::BackgroundType::ClipCornerBackground);
            m_pluginView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_pluginView->setSelectionMode(QListView::SelectionMode::NoSelection);
            m_pluginView->setEditTriggers(DListView::NoEditTriggers);
            m_pluginView->setFrameShape(DListView::NoFrame);
            m_pluginView->setViewportMargins(0, 0, 0, 0);
            m_pluginView->setItemSpacing(1);

            QMargins itemMargins(m_pluginView->itemMargins());
            itemMargins.setLeft(14);
            m_pluginView->setItemMargins(itemMargins);

            m_pluginView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
            QScroller *scroller = QScroller::scroller(m_pluginView->viewport());
            QScrollerProperties sp;
            sp.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
            scroller->setScrollerProperties(sp);

            m_pluginView->setModel(m_pluginModel);

            layout->addWidget(m_pluginView);
            m_gsettingsWatcher->bind("pluginArea", m_pluginView);
            for (auto name : plugins) {
                DStandardItem *item = new DStandardItem(name);
                item->setFontSize(DFontSizeManager::T8);
                QSize size(16, 16);

                // 插件图标
                auto leftAction = new DViewItemAction(Qt::AlignVCenter, size, size, true);
                leftAction->setIcon(QIcon::fromTheme(pluginIconMap.value(m_dockInter->getPluginKey(name), ":/icons/plugins/plug-in2.svg")));
                item->setActionList(Qt::Edge::LeftEdge, {leftAction});

                auto rightAction = new DViewItemAction(Qt::AlignVCenter, size, size, true);
                bool visible = m_dockInter->getPluginVisible(name);
                auto checkstatus = visible ? DStyle::SP_IndicatorChecked : DStyle::SP_IndicatorUnchecked ;
                auto checkIcon = qobject_cast<DStyle *>(style())->standardIcon(checkstatus);
                rightAction->setIcon(checkIcon);
                item->setActionList(Qt::Edge::RightEdge, {rightAction});
                m_pluginModel->appendRow(item);

                connect(rightAction, &DViewItemAction::triggered, this, [ = ] {
                    bool checked = m_dockInter->getPluginVisible(name);
                    m_dockInter->setPluginVisible(name, !checked);
                    updateItemCheckStatus(name, !checked);
                });
            }
            // 固定大小,防止滚动
            int lineHeight = m_pluginView->visualRect(m_pluginView->indexAt(QPoint(0, 0))).height();
            m_pluginView->setMinimumHeight(lineHeight * plugins.size() + 10);
        }
    }

    // 保持内容正常铺满
    layout->addStretch();

    // 界面内容过多时可滚动查看
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setWidget(widget);
}

void ModuleWidget::updateSliderValue()
{
    auto displayMode = m_daemonDockInter->displayMode();

    m_sizeSlider->slider()->blockSignals(true);
    if (displayMode == DisplayMode::Fashion) {
        if (int(m_daemonDockInter->windowSizeFashion()) != m_sizeSlider->slider()->value())
            m_sizeSlider->slider()->setValue(int(m_daemonDockInter->windowSizeFashion()));
    } else if (displayMode == DisplayMode::Efficient) {
        if (int(m_daemonDockInter->windowSizeEfficient()) != m_sizeSlider->slider()->value())
            m_sizeSlider->slider()->setValue(int(m_daemonDockInter->windowSizeEfficient()));
    } else {
        Q_ASSERT_X(false, __FILE__, "not supported");
    }
    m_sizeSlider->slider()->blockSignals(false);
}

void ModuleWidget::updateItemCheckStatus(const QString &name, bool visible)
{
    for (int i = 0; i < m_pluginModel->rowCount(); ++i) {
        auto item = static_cast<DStandardItem *>(m_pluginModel->item(i));
        if (item->text() != name || item->actionList(Qt::Edge::RightEdge).size() < 1)
            continue;

        auto action = item->actionList(Qt::Edge::RightEdge).first();
        auto checkstatus = visible ? DStyle::SP_IndicatorChecked : DStyle::SP_IndicatorUnchecked ;
        auto icon = qobject_cast<DStyle *>(style())->standardIcon(checkstatus);
        action->setIcon(icon);
        m_pluginView->update(item->index());
        break;
    }
}
