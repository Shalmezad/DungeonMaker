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
    for(int a=0; a<100; a++){
        addCorridor();
        addRoom();
    }
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
            if(dungeon[x][y] == OPENSPACE){
                cout<<" ";
            }
            else{
                cout<<"#";
            }
            //cout<<dungeon[x][y];
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

void DungeonMap::addCorridor()
{
    //find a wall.
    Point corStart = findRoomWall();
    //what are the dimmensions?
    Point corDim;
    if(rand()%2 == 1){
        //vertical
        corDim.x = 1;
        corDim.y = rand() % 6 + 1;
        //do we shift?
        if(rand()%2 == 1){
            corStart.y-=corDim.y-1;
        }
        //are we a legal rect?
        if(!rectInBounds(corStart.x-1,corStart.y,corDim.x+2, corDim.y)){
            return;
        }
        //we're legal. But can we dig?
        if(rectType(corStart.x-1,corStart.y,corDim.x+2, corDim.y) == MIXEDTYPE ||
           rectType(corStart.x-1,corStart.y,corDim.x+2, corDim.y) == OPENSPACE)
        {
            return;
        }
        //We're good.
        digRect(corStart.x,corStart.y,corDim.x, corDim.y);
    }
    else{
        //horizontal
        corDim.x = rand() % 6 + 1;
        corDim.y = 1;
        //do we shift?
        if(rand()%2 == 1){
            corStart.x-=corDim.x-1;
        }
        //are we a legal rect?
        if(!rectInBounds(corStart.x,corStart.y-1,corDim.x, corDim.y+2)){
            return;
        }
        //we're legal. But can we dig?
        if(rectType(corStart.x,corStart.y-1,corDim.x, corDim.y+2) == MIXEDTYPE ||
           rectType(corStart.x,corStart.y-1,corDim.x, corDim.y+2) == OPENSPACE)
        {
            return;
        }
        //We're good.
        digRect(corStart.x,corStart.y,corDim.x, corDim.y);
    }
}

void DungeonMap::addRoom()
{
    //find a wall.
    Point corStart = findRoomWall();
    //what are the dimmensions?
    Point corDim;
    corDim.x = rand() % 6 + 2;
    corDim.y = rand() % 6 + 2;

    if(rand()%2 == 1){
        //shift up.
        corStart.y -= corDim.y-1;
    }
    if(rand()%2 == 1){
        //shift left.
        corStart.x -= corDim.x-1;
    }

    //verify rect.
    if(!rectInBounds(corStart.x,corStart.y,corDim.x, corDim.y)){
        return;
    }
    //are we clear to dig?
    if(rectType(corStart.x,corStart.y,corDim.x, corDim.y) != SOLIDWALL){
        return;
    }
    //good to go. dig.
    digRect(corStart.x,corStart.y,corDim.x, corDim.y);
}
