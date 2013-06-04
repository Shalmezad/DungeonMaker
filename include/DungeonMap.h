#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H


const int DUNGEON_WIDTH = 80;
const int DUNGEON_HEIGHT = 40;


class DungeonMap
{

    public:
        DungeonMap();
        virtual ~DungeonMap();
    protected:
    private:
        int dungeon[DUNGEON_WIDTH][DUNGEON_HEIGHT];
};

#endif // DUNGEONMAP_H
