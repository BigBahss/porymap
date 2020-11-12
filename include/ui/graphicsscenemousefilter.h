#ifndef GRAPHICSSCENEMOUSEFILTER_H
#define GRAPHICSSCENEMOUSEFILTER_H

#include <QObject>

class QGraphicsSceneMouseEvent;


class GraphicsSceneMouseFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)

public:
    GraphicsSceneMouseFilter(QObject *parent = nullptr);
    ~GraphicsSceneMouseFilter();

    bool eventFilter(QObject *, QEvent *event) override;

    bool accepts(QGraphicsSceneMouseEvent *event) const;

    void setAcceptedMouseButtons(Qt::MouseButtons buttons);
    Qt::MouseButtons acceptedMouseButtons() const;
    void setAcceptedKeyboardModifiers(Qt::KeyboardModifiers modifiers);
    Qt::KeyboardModifiers acceptedKeyboardModifiers() const;

    void setWhatsThis(const QString &text);
    QString whatsThis() const;
    void setEnabled(bool enable);
    bool isEnabled() const;

private:
    Qt::MouseButtons mouse_buttons;
    Qt::KeyboardModifiers keyboard_modifiers;
    QString whats_this;
    bool enabled;
};


#endif // GRAPHICSSCENEMOUSEFILTER_H