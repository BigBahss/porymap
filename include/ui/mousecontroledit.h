#ifndef MOUSECONTROLEDIT_H
#define MOUSECONTROLEDIT_H

#include "mousecontrol.h"
#include <QWidget>

class QLineEdit;
class QLabel;
class QMenu;


// This class is analogous to QKeySequenceEdit, but for MouseControl's.
class MouseControlEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(MouseControl mouseControl READ mouseControl WRITE setMouseControl NOTIFY mouseControlChanged USER true)

public:
    explicit MouseControlEdit(QWidget *parent = nullptr);
    explicit MouseControlEdit(const MouseControl &mouseControl, QWidget *parent = nullptr);
    ~MouseControlEdit() { }

    bool eventFilter(QObject *watched, QEvent *event) override;

    MouseControl mouseControl() const noexcept { return m_mouseControl; }

    // The amount of time (in milliseconds) that the widget will listen for mouse/wheel events.
    int inputTimeout() const noexcept { return m_inputTimeout; }
    // Default timeout is 8000ms. Setting to a non-positive value will disable the timeout.
    void setInputTimeout(int milliseconds) noexcept { m_inputTimeout = milliseconds; }

public slots:
    void setMouseControl(const MouseControl &mouseControl);
    void clear() { setMouseControl(MouseControl()); }

signals:
    void mouseControlChanged(const MouseControl &mouseControl);
    void editingFinished();

protected:
    void mousePressEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void contextMenuEvent(QContextMenuEvent *) override;
    void timerEvent(QTimerEvent *) override;

private:
    MouseControl m_mouseControl;
    QLineEdit *m_lineEdit;
    QLabel *m_prompt;
    QMenu *m_contextMenu;
    int m_inputTimeout;
    int m_releaseTimer;
    bool m_ignoreContextMenuEvent;

    void startEditing();
    void finishEditing();

    Q_DISABLE_COPY(MouseControlEdit)
};

#endif // MOUSECONTROLEDIT_H
