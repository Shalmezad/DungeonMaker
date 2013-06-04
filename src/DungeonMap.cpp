#include "../include/DungeonMap.h"
#include <iostream>

using namespace std;

DungeonMap::DungeonMap()
{
    //ctor
    for(int x=0; x<DUNGEON_WIDTH; x++){
        for(int y=0; y<DUNGEON_HEIGHT; y++){
            dungeon[x][y] = SOLIDWALL;
        }
    }
    digRect(5,5,5,5);
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
