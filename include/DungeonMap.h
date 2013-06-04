#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H


const int DUNGEON_WIDTH = 76;
const int DUNGEON_HEIGHT = 40;

enum WallTypes
{
    OPENSPACE = 0,
    SOLIDWALL = 1
};

class DungeonMap
{

    public:
        DungeonMap();
        virtual ~DungeonMap();
        void printMap();
    protected:
    private:
        WallTypes dungeon[DUNGEON_WIDTH][DUNGEON_HEIGHT];
        void digRect(int,int,int,int);
};

#endif // DUNGEONMAP_H
