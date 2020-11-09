#include "settings.h"

Settings::Settings() :
    smartPathsEnabled(false),
    betterCursors(true),
    mapCursor(QCursor()),
    playerViewRectEnabled(false),
    cursorTileRectEnabled(true),
    smartPathsModifiers(Qt::ShiftModifier),
    straightPathsModifiers(Qt::ControlModifier),
    magicFillModifiers(Qt::ControlModifier)
{  }
