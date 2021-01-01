#include "mousecontroledit.h"

#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QtEvents>
#include <QMenu>
#include <QAction>


MouseControlEdit::MouseControlEdit(QWidget *parent) :
    MouseControlEdit(MouseControl(), parent)
{  }

MouseControlEdit::MouseControlEdit(const MouseControl &mouseControl, QWidget *parent) :
    QWidget(parent),
    m_mouseControl(mouseControl),
    m_lineEdit(new QLineEdit(this)),
    m_prompt(new QLabel(this)),
    m_contextMenu(new QMenu(this)),
    m_inputTimeout(8000),
    m_releaseTimer(0),
    m_ignoreContextMenuEvent(false)
{
    setLayout(new QVBoxLayout(this));
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->addWidget(m_lineEdit);

    m_lineEdit->setFocusProxy(this);
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setClearButtonEnabled(true);
    m_lineEdit->setCursor(Qt::PointingHandCursor);
    m_lineEdit->setPlaceholderText("Not set");
    m_lineEdit->setText(m_mouseControl.toString());

    m_prompt->installEventFilter(this);
    m_prompt->setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint |
                             Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    m_prompt->setFrameShape(QFrame::Box);
    m_prompt->setMargin(9);
    m_prompt->setPalette(palette());
    m_prompt->setAlignment(Qt::AlignCenter);
    m_prompt->setTextFormat(Qt::PlainText);
    m_prompt->setText("Press a mouse button while\noptionally holding modifier keys.");
    QFont f = m_lineEdit->font();
    f.setPointSize(f.pointSize() + 4);
    m_prompt->setFont(f);
    m_prompt->adjustSize();

    QAction *clearAction = new QAction("Clear Control", m_contextMenu);
    connect(clearAction, &QAction::triggered, this, [&]() { clear(); });
    m_contextMenu->addAction(clearAction);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    setAttribute(Qt::WA_InputMethodEnabled, false);
}

bool MouseControlEdit::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != m_lineEdit && watched != m_prompt)
        return false;

    switch (event->type()) {
    case QEvent::MouseButtonPress:
        mousePressEvent((QMouseEvent *)event);
        break;
    case QEvent::Wheel:
        wheelEvent((QWheelEvent *)event);
        break;
    case QEvent::ContextMenu:
        contextMenuEvent((QContextMenuEvent *)event);
        break;
    default:
        return false;
    }

    return true;
}

void MouseControlEdit::setMouseControl(const MouseControl &mouseControl)
{
    m_mouseControl = mouseControl;
    m_lineEdit->setText(m_mouseControl.toString());

    emit mouseControlChanged(mouseControl);
}

void MouseControlEdit::mousePressEvent(QMouseEvent *event)
{
    if (QWidget::mouseGrabber() == this) {
        m_mouseControl = MouseControl::fromEvent(event);
        finishEditing();
        m_ignoreContextMenuEvent = event->button() == Qt::RightButton;
    } else if (event->button() != Qt::RightButton) {
        startEditing();
    }
    event->accept();
}

void MouseControlEdit::wheelEvent(QWheelEvent *event)
{
    if (QWidget::mouseGrabber() == this) {
        m_mouseControl = MouseControl::fromEvent(event);
        finishEditing();
    }
    event->accept();
}

void MouseControlEdit::keyPressEvent(QKeyEvent *event)
{
    if (QWidget::mouseGrabber() == this && event->key() == Qt::Key_Escape)
        finishEditing();
}

void MouseControlEdit::contextMenuEvent(QContextMenuEvent *event)
{
    if (contextMenuPolicy() == Qt::DefaultContextMenu && !m_ignoreContextMenuEvent) {
        m_contextMenu->exec(mapToGlobal(event->pos()));
        event->accept();
    }
    m_ignoreContextMenuEvent = false;
}

void MouseControlEdit::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_releaseTimer) {
        finishEditing();
        return;
    }

    QWidget::timerEvent(event);
}

void MouseControlEdit::startEditing()
{
    grabMouse(Qt::BlankCursor);
    grabKeyboard();
    const QSize shiftSize(m_prompt->size() / 2);
    m_prompt->move(cursor().pos() - QPoint(shiftSize.width(), shiftSize.height()));
    m_prompt->show();

    if (m_inputTimeout > 0)
        m_releaseTimer = startTimer(m_inputTimeout);
}

void MouseControlEdit::finishEditing()
{
    m_lineEdit->setText(m_mouseControl.toString());

    if (m_releaseTimer) {
        killTimer(m_releaseTimer);
        m_releaseTimer = 0;
    }

    m_prompt->hide();
    releaseKeyboard();
    releaseMouse();

    emit mouseControlChanged(m_mouseControl);
    emit editingFinished();
}
