/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp ./dde-dock/plugins/keyboard-layout/dbusinterface/xml/org.deepin.dde.InputDevice1.Keyboard.xml -a ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.InputDevice1.KeyboardAdaptor -i ./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.InputDevice1.Keyboard.h
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "./dde-dock/toolGenerate/qdbusxml2cpp/org.deepin.dde.InputDevice1.KeyboardAdaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class KeyboardAdaptor
 */

KeyboardAdaptor::KeyboardAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

KeyboardAdaptor::~KeyboardAdaptor()
{
    // destructor
}

bool KeyboardAdaptor::capslockToggle() const
{
    // get the value of property CapslockToggle
    return qvariant_cast< bool >(parent()->property("CapslockToggle"));
}

void KeyboardAdaptor::setCapslockToggle(bool value)
{
    // set the value of property CapslockToggle
    parent()->setProperty("CapslockToggle", QVariant::fromValue(value));
}

QString KeyboardAdaptor::currentLayout() const
{
    // get the value of property CurrentLayout
    return qvariant_cast< QString >(parent()->property("CurrentLayout"));
}

void KeyboardAdaptor::setCurrentLayout(const QString &value)
{
    // set the value of property CurrentLayout
    parent()->setProperty("CurrentLayout", QVariant::fromValue(value));
}

int KeyboardAdaptor::cursorBlink() const
{
    // get the value of property CursorBlink
    return qvariant_cast< int >(parent()->property("CursorBlink"));
}

void KeyboardAdaptor::setCursorBlink(int value)
{
    // set the value of property CursorBlink
    parent()->setProperty("CursorBlink", QVariant::fromValue(value));
}

int KeyboardAdaptor::layoutScope() const
{
    // get the value of property LayoutScope
    return qvariant_cast< int >(parent()->property("LayoutScope"));
}

void KeyboardAdaptor::setLayoutScope(int value)
{
    // set the value of property LayoutScope
    parent()->setProperty("LayoutScope", QVariant::fromValue(value));
}

uint KeyboardAdaptor::repeatDelay() const
{
    // get the value of property RepeatDelay
    return qvariant_cast< uint >(parent()->property("RepeatDelay"));
}

void KeyboardAdaptor::setRepeatDelay(uint value)
{
    // set the value of property RepeatDelay
    parent()->setProperty("RepeatDelay", QVariant::fromValue(value));
}

bool KeyboardAdaptor::repeatEnabled() const
{
    // get the value of property RepeatEnabled
    return qvariant_cast< bool >(parent()->property("RepeatEnabled"));
}

void KeyboardAdaptor::setRepeatEnabled(bool value)
{
    // set the value of property RepeatEnabled
    parent()->setProperty("RepeatEnabled", QVariant::fromValue(value));
}

uint KeyboardAdaptor::repeatInterval() const
{
    // get the value of property RepeatInterval
    return qvariant_cast< uint >(parent()->property("RepeatInterval"));
}

void KeyboardAdaptor::setRepeatInterval(uint value)
{
    // set the value of property RepeatInterval
    parent()->setProperty("RepeatInterval", QVariant::fromValue(value));
}

QStringList KeyboardAdaptor::userLayoutList() const
{
    // get the value of property UserLayoutList
    return qvariant_cast< QStringList >(parent()->property("UserLayoutList"));
}

QStringList KeyboardAdaptor::userOptionList() const
{
    // get the value of property UserOptionList
    return qvariant_cast< QStringList >(parent()->property("UserOptionList"));
}

void KeyboardAdaptor::AddLayoutOption(const QString &in0)
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.AddLayoutOption
    QMetaObject::invokeMethod(parent(), "AddLayoutOption", Q_ARG(QString, in0));
}

void KeyboardAdaptor::AddUserLayout(const QString &in0)
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.AddUserLayout
    QMetaObject::invokeMethod(parent(), "AddUserLayout", Q_ARG(QString, in0));
}

void KeyboardAdaptor::ClearLayoutOption()
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.ClearLayoutOption
    QMetaObject::invokeMethod(parent(), "ClearLayoutOption");
}

void KeyboardAdaptor::DeleteLayoutOption(const QString &in0)
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.DeleteLayoutOption
    QMetaObject::invokeMethod(parent(), "DeleteLayoutOption", Q_ARG(QString, in0));
}

void KeyboardAdaptor::DeleteUserLayout(const QString &in0)
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.DeleteUserLayout
    QMetaObject::invokeMethod(parent(), "DeleteUserLayout", Q_ARG(QString, in0));
}

QString KeyboardAdaptor::GetLayoutDesc(const QString &in0)
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.GetLayoutDesc
    QString out0;
    QMetaObject::invokeMethod(parent(), "GetLayoutDesc", Q_RETURN_ARG(QString, out0), Q_ARG(QString, in0));
    return out0;
}

KeyboardLayoutList KeyboardAdaptor::LayoutList()
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.LayoutList
    KeyboardLayoutList out0;
    QMetaObject::invokeMethod(parent(), "LayoutList", Q_RETURN_ARG(KeyboardLayoutList, out0));
    return out0;
}

void KeyboardAdaptor::Reset()
{
    // handle method call org.deepin.dde.InputDevice1.Keyboard.Reset
    QMetaObject::invokeMethod(parent(), "Reset");
}

