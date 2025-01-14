/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp ./dde-dock/frame/dbusinterface/xml/org.deepin.dde.kwayland.WindowManager.xml -a ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.WindowManagerAdaptor -i ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.WindowManager.h
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef ORG_DEEPIN_DDE_KWAYLAND_WINDOWMANAGERADAPTOR_H
#define ORG_DEEPIN_DDE_KWAYLAND_WINDOWMANAGERADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.kwayland.WindowManager.h"
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface org.deepin.dde.KWayland1.WindowManager
 */
class WindowManagerAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.deepin.dde.KWayland1.WindowManager")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.deepin.dde.KWayland1.WindowManager\">\n"
"    <signal name=\"InterfaceAboutToBeReleased\"/>\n"
"    <signal name=\"InterfaceAboutToBeDestroyed\"/>\n"
"    <signal name=\"ShowingDesktopChanged\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </signal>\n"
"    <signal name=\"WindowCreated\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"dbus\"/>\n"
"    </signal>\n"
"    <signal name=\"WindowRemove\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"dbus\"/>\n"
"    </signal>\n"
"    <signal name=\"ActiveWindowChanged\"/>\n"
"    <method name=\"IsValid\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"IsShowingDesktop\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"    </method>\n"
"    <method name=\"SetShowingDesktop\">\n"
"      <arg direction=\"in\" type=\"b\" name=\"show\"/>\n"
"    </method>\n"
"    <method name=\"ShowDesktop\"/>\n"
"    <method name=\"HideDesktop\"/>\n"
"    <method name=\"Windows\">\n"
"      <arg direction=\"out\" type=\"av\"/>\n"
"    </method>\n"
"    <method name=\"ActiveWindow\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    WindowManagerAdaptor(QObject *parent);
    virtual ~WindowManagerAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    uint ActiveWindow();
    void HideDesktop();
    bool IsShowingDesktop();
    bool IsValid();
    void SetShowingDesktop(bool show);
    void ShowDesktop();
    QVariantList Windows();
Q_SIGNALS: // SIGNALS
    void ActiveWindowChanged();
    void InterfaceAboutToBeDestroyed();
    void InterfaceAboutToBeReleased();
    void ShowingDesktopChanged(bool in0);
    void WindowCreated(const QString &dbus);
    void WindowRemove(const QString &dbus);
};

#endif
