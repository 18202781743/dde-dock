/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp ./dde-dock/frame/dbusinterface/xml/org.deepin.dde.kwayland.PlasmaWindow.xml -a ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.PlasmaWindowAdaptor -i ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.PlasmaWindow.h
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef ORG_DEEPIN_DDE_KWAYLAND_PLASMAWINDOWADAPTOR_H
#define ORG_DEEPIN_DDE_KWAYLAND_PLASMAWINDOWADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.PlasmaWindow.h"
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface org.deepin.dde.KWayland1.PlasmaWindow
 */
class PlasmaWindowAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.deepin.dde.KWayland1.PlasmaWindow")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.deepin.dde.KWayland1.PlasmaWindow\">\n"
"    <signal name=\"ActiveChanged\"/>\n"
"    <signal name=\"AppIdChanged\"/>\n"
"    <signal name=\"CloseableChanged\"/>\n"
"    <signal name=\"DemandsAttentionChanged\"/>\n"
"    <signal name=\"FullscreenableChanged\"/>\n"
"    <signal name=\"FullscreenChanged\"/>\n"
"    <signal name=\"GeometryChanged\"/>\n"
"    <signal name=\"IconChanged\"/>\n"
"    <signal name=\"KeepAboveChanged\"/>\n"
"    <signal name=\"KeepBelowChanged\"/>\n"
"    <signal name=\"MaximizeableChanged\"/>\n"
"    <signal name=\"MaximizedChanged\"/>\n"
"    <signal name=\"MinimizeableChanged\"/>\n"
"    <signal name=\"MinimizedChanged\"/>\n"
"    <signal name=\"MovableChanged\"/>\n"
"    <signal name=\"OnAllDesktopsChanged\"/>\n"
"    <signal name=\"ParentWindowChanged\"/>\n"
"    <signal name=\"PlasmaVirtualDesktopEntered\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"id\"/>\n"
"    </signal>\n"
"    <signal name=\"PlasmaVirtualDesktopLeft\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"id\"/>\n"
"    </signal>\n"
"    <signal name=\"ResizableChanged\"/>\n"
"    <signal name=\"ShadeableChanged\"/>\n"
"    <signal name=\"ShadedChanged\"/>\n"
"    <signal name=\"SkipSwitcherChanged\"/>\n"
"    <signal name=\"SkipTaskbarChanged\"/>\n"
"    <signal name=\"TitleChanged\"/>\n"
"    <signal name=\"Unmapped\"/>\n"
"    <signal name=\"VirtualDesktopChangeableChanged\"/>\n"
"    <signal name=\"VirtualDesktopChanged\"/>\n"
"    <method name=\"AppId\">\n"
"      <arg direction=\"out\" type=\"s\"/>\n"
"    </method>\n"
"    <method name=\"Destroy\"/>\n"
"    <method name=\"Geometry\">\n"
"      <arg direction=\"out\" type=\"(iiii)\"/>\n"
"      <annotation value=\"DockRect\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
"    </method>\n"
"    <method name=\"Icon\">\n"
"      <arg direction=\"out\" type=\"s\"/>\n"
"    </method>\n"
"    <method name=\"InternalId\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"    </method>\n"
"    <method name=\"IsActive\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsCloseable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsDemandingAttention\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsFullscreen\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsFullscreenable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsKeepAbove\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsKeepBelow\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsMaximizeable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsMaximized\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsMinimizeable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsMinimized\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsMovable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsOnAllDesktops\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsResizable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsShadeable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsShaded\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsValid\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsVirtualDesktopChangeable\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"Pid\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"    </method>\n"
"    <method name=\"PlasmaVirtualDesktops\">\n"
"      <arg direction=\"out\" type=\"as\"/>\n"
"    </method>\n"
"    <method name=\"Release\"/>\n"
"    <method name=\"RequestActivate\"/>\n"
"    <method name=\"RequestClose\"/>\n"
"    <method name=\"RequestEnterNewVirtualDesktop\"/>\n"
"    <method name=\"RequestEnterVirtualDesktop\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"id\"/>\n"
"    </method>\n"
"    <method name=\"RequestLeaveVirtualDesktop\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"id\"/>\n"
"    </method>\n"
"    <method name=\"RequestMove\"/>\n"
"    <method name=\"RequestResize\"/>\n"
"    <method name=\"RequestToggleKeepAbove\"/>\n"
"    <method name=\"RequestToggleKeepBelow\"/>\n"
"    <method name=\"RequestToggleMaximized\"/>\n"
"    <method name=\"RequestToggleMinimized\"/>\n"
"    <method name=\"RequestToggleShaded\"/>\n"
"    <method name=\"RequestVirtualDesktop\">\n"
"      <arg direction=\"in\" type=\"u\" name=\"desktop\"/>\n"
"    </method>\n"
"    <method name=\"SkipSwitcher\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"SkipTaskbar\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"Title\">\n"
"      <arg direction=\"out\" type=\"s\"/>\n"
"    </method>\n"
"    <method name=\"VirtualDesktop\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"    </method>\n"
"    <method name=\"WindowId\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"    </method>\n"
"    <method name=\"uuid\">\n"
"      <arg direction=\"out\" type=\"ay\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    PlasmaWindowAdaptor(QObject *parent);
    virtual ~PlasmaWindowAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    QString AppId();
    void Destroy();
    DockRect Geometry();
    QString Icon();
    uint InternalId();
    bool IsActive();
    bool IsCloseable();
    bool IsDemandingAttention();
    bool IsFullscreen();
    bool IsFullscreenable();
    bool IsKeepAbove();
    bool IsKeepBelow();
    bool IsMaximizeable();
    bool IsMaximized();
    bool IsMinimizeable();
    bool IsMinimized();
    bool IsMovable();
    bool IsOnAllDesktops();
    bool IsResizable();
    bool IsShadeable();
    bool IsShaded();
    bool IsValid();
    bool IsVirtualDesktopChangeable();
    uint Pid();
    QStringList PlasmaVirtualDesktops();
    void Release();
    void RequestActivate();
    void RequestClose();
    void RequestEnterNewVirtualDesktop();
    void RequestEnterVirtualDesktop(const QString &id);
    void RequestLeaveVirtualDesktop(const QString &id);
    void RequestMove();
    void RequestResize();
    void RequestToggleKeepAbove();
    void RequestToggleKeepBelow();
    void RequestToggleMaximized();
    void RequestToggleMinimized();
    void RequestToggleShaded();
    void RequestVirtualDesktop(uint desktop);
    bool SkipSwitcher();
    bool SkipTaskbar();
    QString Title();
    uint VirtualDesktop();
    uint WindowId();
    QByteArray uuid();
Q_SIGNALS: // SIGNALS
    void ActiveChanged();
    void AppIdChanged();
    void CloseableChanged();
    void DemandsAttentionChanged();
    void FullscreenChanged();
    void FullscreenableChanged();
    void GeometryChanged();
    void IconChanged();
    void KeepAboveChanged();
    void KeepBelowChanged();
    void MaximizeableChanged();
    void MaximizedChanged();
    void MinimizeableChanged();
    void MinimizedChanged();
    void MovableChanged();
    void OnAllDesktopsChanged();
    void ParentWindowChanged();
    void PlasmaVirtualDesktopEntered(const QString &id);
    void PlasmaVirtualDesktopLeft(const QString &id);
    void ResizableChanged();
    void ShadeableChanged();
    void ShadedChanged();
    void SkipSwitcherChanged();
    void SkipTaskbarChanged();
    void TitleChanged();
    void Unmapped();
    void VirtualDesktopChangeableChanged();
    void VirtualDesktopChanged();
};

#endif
