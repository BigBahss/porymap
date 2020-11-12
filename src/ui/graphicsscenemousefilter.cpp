#include "graphicsscenemousefilter.h"

#include <QtEvents>
#include <QGraphicsSceneEvent>


GraphicsSceneMouseFilter::GraphicsSceneMouseFilter(QObject *parent) :
    QObject(parent),
    mouse_buttons(Qt::NoButton),
    keyboard_modifiers(Qt::NoModifier),
    whats_this(QString()),
    enabled(true)
{
    
}

GraphicsSceneMouseFilter::~GraphicsSceneMouseFilter()
{

}

bool GraphicsSceneMouseFilter::eventFilter(QObject *, QEvent *event) {

}

bool GraphicsSceneMouseFilter::accepts(QGraphicsSceneMouseEvent *event) const {
    return event->buttons() & mouse_buttons && event->modifiers() & keyboard_modifiers;
}

void GraphicsSceneMouseFilter::setAcceptedMouseButtons(Qt::MouseButtons buttons) {

}

Qt::MouseButtons GraphicsSceneMouseFilter::acceptedMouseButtons() const {

}

void GraphicsSceneMouseFilter::setAcceptedKeyboardModifiers(Qt::KeyboardModifiers modifiers) {

}

Qt::KeyboardModifiers GraphicsSceneMouseFilter::acceptedKeyboardModifiers() const {

}

void GraphicsSceneMouseFilter::setWhatsThis(const QString &text) {

}

QString GraphicsSceneMouseFilter::whatsThis() const {

}

void GraphicsSceneMouseFilter::setEnabled(bool enable) {

}

bool GraphicsSceneMouseFilter::isEnabled() const {

}
