#include "mousecontrol.h"

#include <QtEvents>
#include <QGraphicsSceneEvent>
#include <QStringList>

static QString stringFromMouseButton(Qt::MouseButton button);
static Qt::MouseButton mouseButtonFromString(const QString &str);
static QString stringFromMouseWheel(pory::MouseWheel wheel);
static pory::MouseWheel mouseWheelFromString(const QString &str);
static QString stringFromKeyboardModifiers(Qt::KeyboardModifiers modifiers);
static Qt::KeyboardModifier keyboardModifiersFromString(const QString &str);


MouseControl MouseControl::fromEvent(const QMouseEvent *event)
{
    MouseControl mouseControl;
    mouseControl.m_button = event->button();
    mouseControl.m_modifiers = event->modifiers();
    return mouseControl;
}

MouseControl MouseControl::fromEvent(const QWheelEvent *event)
{
    MouseControl mouseControl;
    if (event->angleDelta().y() < 0)
        mouseControl.m_wheel = pory::WheelDown;
    else if (event->angleDelta().y() > 0)
        mouseControl.m_wheel = pory::WheelUp;
    else if (event->angleDelta().x() < 0)
        mouseControl.m_wheel = pory::WheelRight;
    else if (event->angleDelta().x() > 0)
        mouseControl.m_wheel = pory::WheelLeft;
    else
        return mouseControl;

    mouseControl.m_modifiers = event->modifiers();
    return mouseControl;
}

MouseControl MouseControl::fromEvent(const QGraphicsSceneMouseEvent *event)
{
    MouseControl mouseControl;
    mouseControl.m_button = event->button();
    mouseControl.m_modifiers = event->modifiers();
    return mouseControl;
}

MouseControl MouseControl::fromEvent(const QGraphicsSceneWheelEvent *event)
{
    MouseControl mouseControl;
    if (event->delta() < 0 && event->orientation() == Qt::Vertical)
        mouseControl.m_wheel = pory::WheelDown;
    else if (event->delta() > 0 && event->orientation() == Qt::Vertical)
        mouseControl.m_wheel = pory::WheelUp;
    else if (event->delta() < 0 && event->orientation() == Qt::Horizontal)
        mouseControl.m_wheel = pory::WheelRight;
    else if (event->delta() > 0 && event->orientation() == Qt::Horizontal)
        mouseControl.m_wheel = pory::WheelLeft;
    else
        return mouseControl;

    mouseControl.m_modifiers = event->modifiers();
    return mouseControl;
}

MouseControl MouseControl::fromString(const QString &str)
{
    MouseControl mouseControl;
    QStringList modifierNames = str.split('+');
    QString button_or_wheel = modifierNames.takeLast();
    mouseControl.m_button = mouseButtonFromString(button_or_wheel);
    mouseControl.m_wheel = mouseWheelFromString(button_or_wheel);
    if (mouseControl.m_button || mouseControl.m_wheel) {
        for (const auto &modifier : modifierNames)
            mouseControl.m_modifiers |= keyboardModifiersFromString(modifier);
    }
    return mouseControl;
}

QString MouseControl::toString() const
{
    if (!m_button && !m_wheel)
        return QString();
    QString str = (m_modifiers ? stringFromKeyboardModifiers(m_modifiers) + '+' : QString());
    return str + (m_button ? stringFromMouseButton(m_button) : stringFromMouseWheel(m_wheel));
}

bool MouseControl::accepts(const QMouseEvent *event) const
{
    return event->buttons() == m_button && event->modifiers() == m_modifiers;
}

bool MouseControl::accepts(const QWheelEvent *event) const
{
    if (event->angleDelta().y() < 0)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelDown;
    else if (event->angleDelta().y() > 0)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelUp;
    else if (event->angleDelta().x() < 0)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelRight;
    else if (event->angleDelta().x() > 0)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelLeft;

    return false;
}

bool MouseControl::accepts(const QGraphicsSceneMouseEvent *event) const
{
    return event->buttons() == m_button && event->modifiers() == m_modifiers;
}

bool MouseControl::accepts(const QGraphicsSceneWheelEvent *event) const
{
    if (event->delta() < 0 && event->orientation() == Qt::Vertical)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelDown;
    else if (event->delta() > 0 && event->orientation() == Qt::Vertical)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelUp;
    else if (event->delta() < 0 && event->orientation() == Qt::Horizontal)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelRight;
    else if (event->delta() > 0 && event->orientation() == Qt::Horizontal)
        return event->modifiers() == m_modifiers && m_wheel == pory::WheelLeft;

    return false;
}

bool MouseControl::operator==(const MouseControl &other) const noexcept
{
    return other.m_button == m_button
        && other.m_wheel == m_wheel
        && other.m_modifiers == m_modifiers;
}

static constexpr struct {
    Qt::MouseButton button;
    const char name[14];
} buttonName[] = {
    { Qt::LeftButton,       "LeftButton"    },
    { Qt::RightButton,      "RightButton"   },
    { Qt::MiddleButton,     "MiddleButton"  },
    { Qt::BackButton,       "BackButton"    },
    { Qt::ForwardButton,    "ForwardButton" },
    { Qt::ExtraButton3,     "ExtraButton3"  },
    { Qt::ExtraButton4,     "ExtraButton4"  },
    { Qt::ExtraButton5,     "ExtraButton5"  },
    { Qt::ExtraButton6,     "ExtraButton6"  },
    { Qt::ExtraButton7,     "ExtraButton7"  },
    { Qt::ExtraButton8,     "ExtraButton8"  },
    { Qt::ExtraButton9,     "ExtraButton9"  },
    { Qt::ExtraButton10,    "ExtraButton10" },
    { Qt::ExtraButton11,    "ExtraButton11" },
    { Qt::ExtraButton12,    "ExtraButton12" },
    { Qt::ExtraButton13,    "ExtraButton13" },
    { Qt::ExtraButton14,    "ExtraButton14" },
    { Qt::ExtraButton15,    "ExtraButton15" },
    { Qt::ExtraButton16,    "ExtraButton16" },
    { Qt::ExtraButton17,    "ExtraButton17" },
    { Qt::ExtraButton18,    "ExtraButton18" },
    { Qt::ExtraButton19,    "ExtraButton19" },
    { Qt::ExtraButton20,    "ExtraButton20" },
    { Qt::ExtraButton21,    "ExtraButton21" },
    { Qt::ExtraButton22,    "ExtraButton22" },
    { Qt::ExtraButton23,    "ExtraButton23" },
    { Qt::ExtraButton24,    "ExtraButton24" }
};
static constexpr int numButtonNames = sizeof(buttonName) / sizeof(*buttonName);

static QString stringFromMouseButton(Qt::MouseButton button)
{
    for (int i = 0; i < numButtonNames; ++i) {
        if (buttonName[i].button == button)
            return buttonName[i].name;
    }
    return QString();
}

static Qt::MouseButton mouseButtonFromString(const QString &str)
{
    for (int i = 0; i < numButtonNames; ++i) {
        if (buttonName[i].name == str)
            return buttonName[i].button;
    }
    return Qt::NoButton;
}

static constexpr struct {
    pory::MouseWheel wheel;
    const char name[11];
} wheelName[] = {
    { pory::WheelDown,    "WheelDown"  },
    { pory::WheelUp,      "WheelUp"    },
    { pory::WheelLeft,    "WheelLeft"  },
    { pory::WheelRight,   "WheelRight" }
};
static constexpr int numWheelNames = sizeof(wheelName) / sizeof(*wheelName);

static QString stringFromMouseWheel(pory::MouseWheel wheel)
{
    for (int i = 0; i < numWheelNames; ++i) {
        if (wheelName[i].wheel == wheel)
            return wheelName[i].name;
    }
    return QString();
}

static pory::MouseWheel mouseWheelFromString(const QString &str)
{
    for (int i = 0; i < numWheelNames; ++i) {
        if (wheelName[i].name == str)
            return wheelName[i].wheel;
    }
    return pory::NoWheel;
}

static constexpr struct {
    Qt::KeyboardModifier key;
    const char name[6];
} modifierName[] = {
    { Qt::ControlModifier,      "Ctrl"  },
    { Qt::ShiftModifier,        "Shift" },
    { Qt::AltModifier,          "Alt"   },
    { Qt::MetaModifier,         "Meta"  },
    { Qt::KeypadModifier,       "Num"   }
};
static constexpr int numModifierNames = sizeof(modifierName) / sizeof(*modifierName);

static QString stringFromKeyboardModifiers(Qt::KeyboardModifiers modifiers)
{
    modifiers &= ~Qt::GroupSwitchModifier;
    QString str;
    for (int i = 0; i < numModifierNames; ++i) {
        if (modifiers.testFlag(modifierName[i].key)) {
            str += modifierName[i].name;
            modifiers ^= modifierName[i].key;
            if (modifiers)
                str += '+';
            else
                break;
        }
    }
    return str;
}

static Qt::KeyboardModifier keyboardModifiersFromString(const QString &str)
{
    for (int i = 0; i < numModifierNames; ++i) {
        if (modifierName[i].name == str)
            return modifierName[i].key;
    }
    return Qt::NoModifier;
}
