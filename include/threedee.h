#include "vex.h"

/*
    Based on ThreeDee by Ben Ryves (http://benryves.com/projects/threedee)
    You can run that engine on anything (I've run it fairly well on a 75mHz Pentium machine)
    so it should (and does) run well on a 666mHz ARM
*/

#ifndef THREEDEE_H
#define THREEDEE_H

#define SCR_WIDTH 480
#define SCR_HEIGHT 272
#define SCR_XCENTER 240
#define SCR_YCENTER 136

#ifndef NEAR_CLIPPING_PLANE
#define NEAR_CLIPPING_PLANE 10
#endif

#ifndef DRAW_DISTANCE
#define DRAW_DISTANCE 600
#endif

#undef CULLING

#define ZBUFFER_SIZE 1024

class threedee {
    private:
        uint32_t zBuffer[ZBUFFER_SIZE][8];
        uint32_t scrBuffer[SCR_WIDTH * SCR_HEIGHT];

        int camX;
        int camY;
        int camZ;

        int xRot;
        int yRot;
        int r_xRot;
        int r_yRot;

        int dzCenter = 0;
        int zBufferIndex;

        int xCenter;
        int yCenter;
        int zCenter;
        
        void quicksort(uint32_t a[][8], int lo, int hi);
        void drawTriangle2D(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
        void drawLine(int ax, int ay, int bx, int by, uint32_t color);
        uint32_t getPolygonColor(int distance, uint32_t color);
        int fontLine(int c, int row);
    public:
        threedee();
        void drawTriangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, uint32_t color);
        void drawModel(int32_t model[][10], int modelSize, int xPos, int yPos, int zPos, int rX, int rY);
        void draw(vex::brain::lcd lcd);
        void reset();
        void move(int dx, int dy, int dxRot, int dyRot);
        void setCam(int x, int y, int z, int xRot, int yRot);
        void drawText(int px, int py, int size, uint32_t color, const char *message);
};

#endif