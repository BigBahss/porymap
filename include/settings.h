#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include "mousecontrol.h"
#include <QCursor>


class Settings
{
public:
    Settings() noexcept;
    MouseControl smartPathsControl;
    MouseControl smartFillControl;
    MouseControl straightPathsControl;
    MouseControl paint_magicFillControl;
    MouseControl fill_magicFillControl;
    QCursor mapCursor;
    bool betterCursors;
    bool smartPathsEnabled;
    bool playerViewRectEnabled;
    bool cursorTileRectEnabled;
};

#endif // SETTINGS_H
