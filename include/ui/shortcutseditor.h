#ifndef SHORTCUTSEDITOR_H
#define SHORTCUTSEDITOR_H

#include "shortcut.h"

#include <QMainWindow>
#include <QDialog>
#include <QMap>
#include <QHash>
#include <QAction>

class QFormLayout;
class MultiKeyEdit;
class QAbstractButton;
class QGroupBox;
class MouseModifier;
class QCheckBox;


namespace Ui {
class ShortcutsEditor;
}

class ShortcutsEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortcutsEditor(QWidget *parent = nullptr);
    explicit ShortcutsEditor(const QObjectList &shortcutableObjects, QWidget *parent = nullptr);
    ~ShortcutsEditor();

    void setShortcutableObjects(const QObjectList &shortcutableObjects);
    void setExtraModifierKeys(QList<MouseModifier> modifiers);

signals:
    void shortcutsSaved();

private:
    Ui::ShortcutsEditor *ui;
    QWidget *main_container;
    QGroupBox *modifiers_container;
    QFormLayout *modifiers_layout;
    QMultiMap<QString, const QObject *> labels_objects;
    QHash<QString, QFormLayout *> contexts_layouts;
    QHash<MultiKeyEdit *, const QObject *> multiKeyEdits_objects;
    QList<MouseModifier> m_modifiers;

    void parseObjectList(const QObjectList &objectList);
    QString getLabel(const QObject *object) const;
    bool stringPropertyIsNotEmpty(const QObject *object, const char *name) const;
    void populateMainContainer();
    QString getShortcutContext(const QObject *object) const;
    void addNewContextGroup(const QString &shortcutContext);
    void addNewMultiKeyEdit(const QObject *object, const QString &shortcutContext);
    QList<MultiKeyEdit *> siblings(MultiKeyEdit *multiKeyEdit) const;
    void promptUserOnDuplicateFound(MultiKeyEdit *current, MultiKeyEdit *sender);
    void removeKeySequence(const QKeySequence &keySequence, MultiKeyEdit *multiKeyEdit);
    void saveShortcuts();
    void resetShortcuts();

private slots:
    void checkForDuplicates(const QKeySequence &keySequence);
    void dialogButtonClicked(QAbstractButton *button);
};


class ModifierEdit : public QWidget
{
    Q_OBJECT

public:
    ModifierEdit(QWidget *parent = nullptr);
    ~ModifierEdit();

    void setKeyboardModifiers(Qt::KeyboardModifiers);
    Qt::KeyboardModifiers keyboardModifiers() const;

private:
    QCheckBox *checkBoxCtrl;
    QCheckBox *checkBoxShift;
    QCheckBox *checkBoxAlt;
};

#endif // SHORTCUTSEDITOR_H
