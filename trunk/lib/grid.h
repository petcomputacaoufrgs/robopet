#ifndef __GRID_H__
#define __GRID_H__

#define GRID_SIZE_X 5
#define GRID_SIZE_Y 5

enum flags
{
    OPEN_BIT = 1,
    NEW_BIT = 2
};

typedef unsigned char byte;

class Grid
{
    private:
        byte tags; //Flags enumeradas acima

        byte sizeX; //tamanho da grade, para o sistema do RoboPET
        byte sizeY;

    public:
        Grid(int sx = GRID_SIZE_X, int sy = GRID_SIZE_Y){sizeX=sx, sizeY=sy, tags=NEW_BIT;}
        ~Grid(){ };

        inline bool isOpen(){ return (tags & OPEN_BIT) && !(tags & NEW_BIT); } 
        inline bool isClosed(){ return !(tags & OPEN_BIT) && !(tags & NEW_BIT); }
        inline bool isNew(){ return (tags & NEW_BIT); } 

        inline void setOpen(){ tags = (tags | OPEN_BIT) - (tags & NEW_BIT); }
        inline void setClosed(){ tags = tags - (tags & OPEN_BIT) - (tags & NEW_BIT); }

};

#endif
