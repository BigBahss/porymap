#ifndef LAYOUTEDITOR_H
#define LAYOUTEDITOR_H

#include "map.h"
#include "mappixmapitem.h"

#include <QObject>


class LayoutEditor : public QObject
{
    Q_OBJECT

public:
    explicit LayoutEditor(QObject *parent = nullptr);
    ~LayoutEditor();

public slots:
    void setMap(Map *map);
    void setMapItem(MapPixmapItem *mapItem);
    void setCollisionItem(CollisionPixmapItem *collisionItem);

private:
    Map *m_map;
    MapPixmapItem *m_mapItem;
    CollisionPixmapItem *m_collisionItem;
};

#endif // LAYOUTEDITOR_H
