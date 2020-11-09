#ifndef SETTINGS_H
#define SETTINGS_H

#include <QCursor>

class Settings
{
public:
    Settings();

    bool smartPathsEnabled;
    bool betterCursors;
    QCursor mapCursor;
    bool playerViewRectEnabled;
    bool cursorTileRectEnabled;
    Qt::KeyboardModifiers smartPathsModifiers;
    Qt::KeyboardModifiers straightPathsModifiers;
    Qt::KeyboardModifiers magicFillModifiers;
};

#endif // SETTINGS_H
