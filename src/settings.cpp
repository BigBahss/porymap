#include "settings.h"


Settings::Settings() noexcept :
    smartPathsControl(Qt::LeftButton, Qt::ShiftModifier),
    smartFillControl(Qt::LeftButton, Qt::ShiftModifier),
    straightPathsControl(Qt::LeftButton, Qt::ControlModifier),
    paint_magicFillControl(Qt::MiddleButton, Qt::ControlModifier),
    fill_magicFillControl(Qt::LeftButton, Qt::ControlModifier),
    mapCursor(),
    betterCursors(true),
    smartPathsEnabled(false),
    playerViewRectEnabled(false),
    cursorTileRectEnabled(true)
{  }
