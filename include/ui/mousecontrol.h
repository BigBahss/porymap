#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

#include <QString>

class QMouseEvent;
class QWheelEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneWheelEvent;


namespace pory {
    enum MouseWheel { NoWheel, WheelDown, WheelUp, WheelRight, WheelLeft };
}

// This class is analogous to QKeySequence, in order to provide user-definable mouse controls.
// Use the accepts() member function in event handlers to to decide what action to take.
class MouseControl
{
public:
    constexpr MouseControl() noexcept;
    constexpr MouseControl(Qt::MouseButton button,
                           Qt::KeyboardModifiers modifiers = Qt::NoModifier) noexcept;
    constexpr MouseControl(pory::MouseWheel wheel,
                           Qt::KeyboardModifiers modifiers = Qt::NoModifier) noexcept;

    static MouseControl fromEvent(const QMouseEvent *event);
    static MouseControl fromEvent(const QWheelEvent *event);
    static MouseControl fromEvent(const QGraphicsSceneMouseEvent *event);
    static MouseControl fromEvent(const QGraphicsSceneWheelEvent *event);

    static MouseControl fromString(const QString &str);
    QString toString() const;

    bool accepts(const QMouseEvent *event) const;
    bool accepts(const QWheelEvent *event) const;
    bool accepts(const QGraphicsSceneMouseEvent *event) const;
    bool accepts(const QGraphicsSceneWheelEvent *event) const;

    constexpr Qt::MouseButton button() const noexcept { return m_button; }
    constexpr void setButton(Qt::MouseButton button) noexcept;

    constexpr pory::MouseWheel wheel() const noexcept { return m_wheel; }
    constexpr void setWheel(pory::MouseWheel wheel) noexcept;

    constexpr Qt::KeyboardModifiers modifiers() const noexcept { return m_modifiers; }
    constexpr Qt::KeyboardModifiers &rmodifiers() noexcept { return m_modifiers; }
    constexpr void setModifiers(Qt::KeyboardModifiers modifiers) noexcept;

    bool operator==(const MouseControl &other) const noexcept;
    bool operator!=(const MouseControl &other) const noexcept { return !operator==(other); }

private:
    Qt::MouseButton m_button;
    pory::MouseWheel m_wheel;
    Qt::KeyboardModifiers m_modifiers;
};

constexpr MouseControl::MouseControl() noexcept
: m_button(Qt::NoButton), m_wheel(pory::NoWheel), m_modifiers(Qt::NoModifier)
{ }

constexpr MouseControl::MouseControl(Qt::MouseButton button,
                                     Qt::KeyboardModifiers modifiers) noexcept
: m_button(button), m_wheel(pory::NoWheel), m_modifiers(modifiers)
{ }

constexpr MouseControl::MouseControl(pory::MouseWheel wheel,
                                     Qt::KeyboardModifiers modifiers) noexcept
: m_button(Qt::NoButton), m_wheel(wheel), m_modifiers(modifiers)
{ }

constexpr void MouseControl::setButton(Qt::MouseButton button) noexcept
{ m_button = button; m_wheel = pory::NoWheel; }

constexpr void MouseControl::setWheel(pory::MouseWheel wheel) noexcept
{ m_wheel = wheel; m_button = Qt::NoButton; }

constexpr void MouseControl::setModifiers(Qt::KeyboardModifiers modifiers) noexcept
{ m_modifiers = modifiers; }

#endif // MOUSECONTROL_H
