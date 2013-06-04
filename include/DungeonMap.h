#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H


const int DUNGEON_WIDTH = 76;
const int DUNGEON_HEIGHT = 40;

struct Point
{
    int x;
    int y;
};

enum WallTypes
{
    OPENSPACE = 0,
    SOLIDWALL = 1,
    MIXEDTYPE
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
        WallTypes rectType(int,int,int,int);
        bool rectContains(WallTypes, int, int, int, int);
        Point findRoomWall();
        bool rectInBounds(int, int, int, int);
        void addCorridor();
        void addRoom();
};

#endif // DUNGEONMAP_H
