#include "../include/DungeonMap.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

DungeonMap::DungeonMap()
{
    //ctor
    for(int x=0; x<DUNGEON_WIDTH; x++){
        for(int y=0; y<DUNGEON_HEIGHT; y++){
            dungeon[x][y] = SOLIDWALL;
        }
    }
    digRect(DUNGEON_WIDTH/2 - 5,DUNGEON_HEIGHT/2-5,10,10);
    srand (time(NULL));
    //dice = rand() % 6 + 1; //[1-6]
    Point room = findRoomWall();
    digRect(room.x, room.y,1,1);
    cout<<"Dungeon Map constructed!"<<endl;
}

DungeonMap::~DungeonMap()
{
    //dtor
}

void DungeonMap::printMap()
{
    for(int y=0; y<DUNGEON_HEIGHT; y++){
        for(int x=0; x<DUNGEON_WIDTH; x++){
            cout<<dungeon[x][y];
        }
        cout<<endl;
    }
}

void DungeonMap::digRect(int x, int y, int w, int h)
{
    for(int dx = x; dx < x + w; dx++){
        for(int dy = y; dy < y + h; dy++){
            dungeon[dx][dy] = OPENSPACE;
        }
    }
}

WallTypes DungeonMap::rectType(int x,int y,int w,int h)
{
    WallTypes startType = dungeon[x][y];
    for(int dx = x; dx < x + w; dx++){
        for(int dy = y; dy < y + h; dy++){
            if(dungeon[dx][dy] != startType){
                return MIXEDTYPE;
            }
        }
    }
    return startType;
}

bool DungeonMap::rectContains(WallTypes searchType, int x, int y, int w, int h)
{
    for(int dx = x; dx < x + w; dx++){
        for(int dy = y; dy < y + h; dy++)
        {
            if(dungeon[dx][dy] == searchType){
                return true;
            }
        }
    }
    return false;
}

Point DungeonMap::findRoomWall()
{
    Point wall;
    wall.x = -1;
    wall.y = -1;
    while(wall.x == -1){
        //pick a point.
        int x = rand() % (DUNGEON_WIDTH-2) + 1;
        int y = rand() % (DUNGEON_HEIGHT-2) + 1;
        if(dungeon[x][y] == SOLIDWALL){
            //is there a clear spot around it?
            if(dungeon[x-1][y] == OPENSPACE ||
               dungeon[x+1][y] == OPENSPACE ||
               dungeon[x][y-1] == OPENSPACE ||
               dungeon[x][y+1] == OPENSPACE)
            {
                wall.x = x;
                wall.y = y;
                return wall;
            }
        }
    }
}

bool DungeonMap::rectInBounds(int x, int y, int w, int h)
{
    //verify x
    if(x < 0 || x >= DUNGEON_WIDTH){
        return false;
    }
    //verify y
    if(y<0 || y >= DUNGEON_HEIGHT){
        return false;
    }
    //verify w
    if(x + w >= DUNGEON_WIDTH){
        return false;
    }
    //verify h
    if(y + h >= DUNGEON_HEIGHT){
        return false;
    }
    //at this point, it's passed.
    return true;
}
