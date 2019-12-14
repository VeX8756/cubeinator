#include "vex.h"
#include "threedee.h"

int trigTable[256];

#define _sin(a) (trigTable[(a) & 0xFF])
#define _cos(a) (trigTable[((a) + 64) & 0xFF])

void generateLUT() {
    trigTable[0]=0;
    trigTable[1]=6;
    trigTable[2]=12;
    trigTable[3]=18;
    trigTable[4]=25;
    trigTable[5]=31;
    trigTable[6]=37;
    trigTable[7]=43;
    trigTable[8]=49;
    trigTable[9]=56;
    trigTable[10]=62;
    trigTable[11]=68;
    trigTable[12]=74;
    trigTable[13]=80;
    trigTable[14]=86;
    trigTable[15]=92;
    trigTable[16]=97;
    trigTable[17]=103;
    trigTable[18]=109;
    trigTable[19]=115;
    trigTable[20]=120;
    trigTable[21]=126;
    trigTable[22]=131;
    trigTable[23]=136;
    trigTable[24]=142;
    trigTable[25]=147;
    trigTable[26]=152;
    trigTable[27]=157;
    trigTable[28]=162;
    trigTable[29]=167;
    trigTable[30]=171;
    trigTable[31]=176;
    trigTable[32]=181;
    trigTable[33]=185;
    trigTable[34]=189;
    trigTable[35]=193;
    trigTable[36]=197;
    trigTable[37]=201;
    trigTable[38]=205;
    trigTable[39]=209;
    trigTable[40]=212;
    trigTable[41]=216;
    trigTable[42]=219;
    trigTable[43]=222;
    trigTable[44]=225;
    trigTable[45]=228;
    trigTable[46]=231;
    trigTable[47]=234;
    trigTable[48]=236;
    trigTable[49]=238;
    trigTable[50]=241;
    trigTable[51]=243;
    trigTable[52]=244;
    trigTable[53]=246;
    trigTable[54]=248;
    trigTable[55]=249;
    trigTable[56]=251;
    trigTable[57]=252;
    trigTable[58]=253;
    trigTable[59]=254;
    trigTable[60]=254;
    trigTable[61]=255;
    trigTable[62]=255;
    trigTable[63]=255;
    trigTable[64]=256;
    trigTable[65]=255;
    trigTable[66]=255;
    trigTable[67]=255;
    trigTable[68]=254;
    trigTable[69]=254;
    trigTable[70]=253;
    trigTable[71]=252;
    trigTable[72]=251;
    trigTable[73]=249;
    trigTable[74]=248;
    trigTable[75]=246;
    trigTable[76]=244;
    trigTable[77]=243;
    trigTable[78]=241;
    trigTable[79]=238;
    trigTable[80]=236;
    trigTable[81]=234;
    trigTable[82]=231;
    trigTable[83]=228;
    trigTable[84]=225;
    trigTable[85]=222;
    trigTable[86]=219;
    trigTable[87]=216;
    trigTable[88]=212;
    trigTable[89]=209;
    trigTable[90]=205;
    trigTable[91]=201;
    trigTable[92]=197;
    trigTable[93]=193;
    trigTable[94]=189;
    trigTable[95]=185;
    trigTable[96]=181;
    trigTable[97]=176;
    trigTable[98]=171;
    trigTable[99]=167;
    trigTable[100]=162;
    trigTable[101]=157;
    trigTable[102]=152;
    trigTable[103]=147;
    trigTable[104]=142;
    trigTable[105]=136;
    trigTable[106]=131;
    trigTable[107]=126;
    trigTable[108]=120;
    trigTable[109]=115;
    trigTable[110]=109;
    trigTable[111]=103;
    trigTable[112]=97;
    trigTable[113]=92;
    trigTable[114]=86;
    trigTable[115]=80;
    trigTable[116]=74;
    trigTable[117]=68;
    trigTable[118]=62;
    trigTable[119]=56;
    trigTable[120]=49;
    trigTable[121]=43;
    trigTable[122]=37;
    trigTable[123]=31;
    trigTable[124]=25;
    trigTable[125]=18;
    trigTable[126]=12;
    trigTable[127]=6;
    trigTable[128]=0;
    trigTable[129]=-7;
    trigTable[130]=-13;
    trigTable[131]=-19;
    trigTable[132]=-26;
    trigTable[133]=-32;
    trigTable[134]=-38;
    trigTable[135]=-44;
    trigTable[136]=-50;
    trigTable[137]=-57;
    trigTable[138]=-63;
    trigTable[139]=-69;
    trigTable[140]=-75;
    trigTable[141]=-81;
    trigTable[142]=-87;
    trigTable[143]=-93;
    trigTable[144]=-98;
    trigTable[145]=-104;
    trigTable[146]=-110;
    trigTable[147]=-116;
    trigTable[148]=-121;
    trigTable[149]=-127;
    trigTable[150]=-132;
    trigTable[151]=-137;
    trigTable[152]=-143;
    trigTable[153]=-148;
    trigTable[154]=-153;
    trigTable[155]=-158;
    trigTable[156]=-163;
    trigTable[157]=-168;
    trigTable[158]=-172;
    trigTable[159]=-177;
    trigTable[160]=-182;
    trigTable[161]=-186;
    trigTable[162]=-190;
    trigTable[163]=-194;
    trigTable[164]=-198;
    trigTable[165]=-202;
    trigTable[166]=-206;
    trigTable[167]=-210;
    trigTable[168]=-213;
    trigTable[169]=-217;
    trigTable[170]=-220;
    trigTable[171]=-223;
    trigTable[172]=-226;
    trigTable[173]=-229;
    trigTable[174]=-232;
    trigTable[175]=-235;
    trigTable[176]=-237;
    trigTable[177]=-239;
    trigTable[178]=-242;
    trigTable[179]=-244;
    trigTable[180]=-245;
    trigTable[181]=-247;
    trigTable[182]=-249;
    trigTable[183]=-250;
    trigTable[184]=-252;
    trigTable[185]=-253;
    trigTable[186]=-254;
    trigTable[187]=-255;
    trigTable[188]=-255;
    trigTable[189]=-256;
    trigTable[190]=-256;
    trigTable[191]=-256;
    trigTable[192]=-256;
    trigTable[193]=-256;
    trigTable[194]=-256;
    trigTable[195]=-256;
    trigTable[196]=-255;
    trigTable[197]=-255;
    trigTable[198]=-254;
    trigTable[199]=-253;
    trigTable[200]=-252;
    trigTable[201]=-250;
    trigTable[202]=-249;
    trigTable[203]=-247;
    trigTable[204]=-245;
    trigTable[205]=-244;
    trigTable[206]=-242;
    trigTable[207]=-239;
    trigTable[208]=-237;
    trigTable[209]=-235;
    trigTable[210]=-232;
    trigTable[211]=-229;
    trigTable[212]=-226;
    trigTable[213]=-223;
    trigTable[214]=-220;
    trigTable[215]=-217;
    trigTable[216]=-213;
    trigTable[217]=-210;
    trigTable[218]=-206;
    trigTable[219]=-202;
    trigTable[220]=-198;
    trigTable[221]=-194;
    trigTable[222]=-190;
    trigTable[223]=-186;
    trigTable[224]=-182;
    trigTable[225]=-177;
    trigTable[226]=-172;
    trigTable[227]=-168;
    trigTable[228]=-163;
    trigTable[229]=-158;
    trigTable[230]=-153;
    trigTable[231]=-148;
    trigTable[232]=-143;
    trigTable[233]=-137;
    trigTable[234]=-132;
    trigTable[235]=-127;
    trigTable[236]=-121;
    trigTable[237]=-116;
    trigTable[238]=-110;
    trigTable[239]=-104;
    trigTable[240]=-98;
    trigTable[241]=-93;
    trigTable[242]=-87;
    trigTable[243]=-81;
    trigTable[244]=-75;
    trigTable[245]=-69;
    trigTable[246]=-63;
    trigTable[247]=-57;
    trigTable[248]=-50;
    trigTable[249]=-44;
    trigTable[250]=-38;
    trigTable[251]=-32;
    trigTable[252]=-26;
    trigTable[253]=-19;
    trigTable[254]=-13;
    trigTable[255]=-7;
}

threedee::threedee() {
    this->camX = -100;
    this->camY = 0;
    this->camZ = 10;
    this->xRot = 0;
    this->yRot = 0;
    this->r_xRot = this->xRot;
    this->r_yRot = this->yRot;

    generateLUT();
}

#define getRotatedX(x, y, z) (((-(x) * _sin(this->r_xRot)) + ((y) * _cos(this->r_xRot))) >> 8)
#define getRotatedY(x, y, z) (((-(x) * _cos(this->r_xRot) * _sin(this->r_yRot)) - ((y) * _sin(this->r_xRot) * _sin(this->r_yRot))) / 65536 - ((z) * _cos(this->r_yRot)) / 256)
#define getRotatedZ(x, y, z) (((-(x) * _cos(this->r_xRot) * _cos(this->r_yRot)) - ((y) * _sin(this->r_xRot) * _cos(this->r_yRot))) / 65536 + ((z) * _sin(this->r_yRot)) / 256)

/*if ((x) >= 0 && (x) < SCR_WIDTH && (y) >= 0 && (y) < SCR_HEIGHT)*/ 
#define setPixel(x, y, color) this->scrBuffer[(y) * SCR_WIDTH + (x)] = color
//#define setPixel(x, y, color) *(this->scrBuffer + (y) * SCR_WIDTH + (x)) = color

#define hLine(x, y, len, color) for (int i = 0; i < (len); i ++) setPixel((x) + i, (y), (color))

void threedee::drawTriangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, uint32_t color) {
    int rotX1 = getRotatedX(x1, y1, z1);
    int rotY1 = getRotatedY(x1, y1, z1);
    int rotZ1 = getRotatedZ(x1, y1, z1);
    int rotX2 = getRotatedX(x2, y2, z2);
    int rotY2 = getRotatedY(x2, y2, z2);
    int rotZ2 = getRotatedZ(x2, y2, z2);
    int rotX3 = getRotatedX(x3, y3, z3);
    int rotY3 = getRotatedY(x3, y3, z3);
    int rotZ3 = getRotatedZ(x3, y3, z3);
    int realNearClippingPlane = NEAR_CLIPPING_PLANE - this->zCenter;
    int realDrawDistance = DRAW_DISTANCE - this->zCenter;
    if (rotZ1 > realNearClippingPlane && rotZ2 > realNearClippingPlane && rotZ3 > realNearClippingPlane &&
        rotZ1 < realDrawDistance && rotZ2 < realDrawDistance && rotZ3 < realDrawDistance) {
        int scrX1 = (256 * (rotX1+this->xCenter)) / (rotZ1+this->zCenter) + SCR_XCENTER;
        int scrY1 = (256 * (rotY1+this->yCenter)) / (rotZ1+this->zCenter) + SCR_YCENTER;
        int scrX2 = (256 * (rotX2+this->xCenter)) / (rotZ2+this->zCenter) + SCR_XCENTER;
        int scrY2 = (256 * (rotY2+this->yCenter)) / (rotZ2+this->zCenter) + SCR_YCENTER;
        int scrX3 = (256 * (rotX3+this->xCenter)) / (rotZ3+this->zCenter) + SCR_XCENTER;
        int scrY3 = (256 * (rotY3+this->yCenter)) / (rotZ3+this->zCenter) + SCR_YCENTER;
        if (
            (scrX1 > 0 || scrX2 > 0 || scrX3 > 0) &&
            (scrX1 < SCR_WIDTH || scrX2 < SCR_WIDTH || scrX3 < SCR_WIDTH) &&
            (scrY1 > 0 || scrY2 > 0 || scrY3 > 0) &&
                (scrY1 < SCR_HEIGHT || scrY2 < SCR_HEIGHT || scrY3 < SCR_HEIGHT)
        ) {
            this->zBuffer[this->zBufferIndex][0] = scrX1;
            this->zBuffer[this->zBufferIndex][1] = scrY1;
            this->zBuffer[this->zBufferIndex][2] = scrX2;
            this->zBuffer[this->zBufferIndex][3] = scrY2;
            this->zBuffer[this->zBufferIndex][4] = scrX3;
            this->zBuffer[this->zBufferIndex][5] = scrY3;
            this->zBuffer[this->zBufferIndex][6] = getPolygonColor(rotZ1 + rotZ2 + rotZ3 + zCenter * 3, color);
            this->zBuffer[this->zBufferIndex][7] = rotZ1 + rotZ2 + rotZ3 + zCenter * 3;
            this->zBufferIndex ++;
        }
    }
}

void threedee::drawModel(int32_t model[][10], int modelSize, int xPos, int yPos, int zPos, int rX, int rY) {
    int objXPos = this->camX-xPos;
    int objYPos = this->camY-yPos;
    int objZPos = -this->camZ+zPos;
    int i;
    
    this->r_xRot = this->xRot;
    this->r_yRot = this->yRot;

    this->xCenter = getRotatedX(objXPos, objYPos, objZPos);
    this->yCenter = getRotatedY(objXPos, objYPos, objZPos);
    this->zCenter = getRotatedZ(objXPos, objYPos, objZPos);
	
    this->r_xRot = rX + this->xRot;
    this->r_yRot = rY + this->yRot;

    for (i = 0; i < modelSize; i ++) {
        this->drawTriangle(
            model[i][0], model[i][1], model[i][2],
            model[i][3], model[i][4], model[i][5],
            model[i][6], model[i][7], model[i][8],
            model[i][9]);
    }
}

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

int16_t a, b, y, last;

void threedee::drawTriangle2D(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    
    if (y0 == y2) {
        a = b = x0;
        if (x1 < a)
            a = x1;
        else if (x1 > b)
            b = x1;
        if (x2 < a)
            a = x2;
        else if (x2 > b)
            b = x2;
        hLine(a, y0, b - a + 1, color);
        return;
    }

    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;
    int32_t sa = 0;
    int32_t sb = 0;

    if (y1 == y2)
        last = y1;
    else
        last = y1 - 1;

    for(y = y0; y <= last; y ++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if(a > b) _swap_int16_t(a, b);
        hLine(a, y, b - a + 1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y <= y2; y ++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if(a > b) _swap_int16_t(a, b);
        hLine(a, y, b - a + 1, color);
    }

    this->drawLine(x0, y0, x1, y1, 0);
    this->drawLine(x1, y1, x2, y2, 0);
    this->drawLine(x2, y2, x0, y0, 0);
}

void threedee::drawLine(int ax, int ay, int bx, int by, uint32_t color) {
    int dx = abs(bx - ax), sx = ax < bx ? 1 : -1;
    int dy = abs(by - ay), sy = ay < by ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    for(;;) {
        setPixel(ax, ay, color);
        if (ax == bx && ay == by)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            ax += sx;
        }
        if (e2 < dy) {
            err += dx;
            ay += sy;
        }
    }
}

void threedee::quicksort(uint32_t a[][8], int lo, int hi) {
    int i = lo, j = hi, h;
    int x = a[(lo + hi) / 2][7];
    do {
        while (a[i][7] < x) i ++; 
        while (a[j][7] > x) j --;
        if (i <= j) {
            for (int s = 0; s <= 7; s ++) {
                h = a[i][s];
                a[i][s] = a[j][s];
                a[j][s] = h;
            }
            i ++;
            j --;
        }
    } while (i <= j);
    if (lo < j) quicksort(a, lo, j);
    if (i < hi) quicksort(a, i, hi);
}

// Render contents of z buffer
void threedee::draw(vex::brain::lcd lcd) {
    if (this->zBufferIndex > 0) {
        this->quicksort(this->zBuffer, 0, this->zBufferIndex - 1);
    }

    for (int i = this->zBufferIndex - 1; i >= 0; i --) {
        drawTriangle2D(
            this->zBuffer[i][0], this->zBuffer[i][1],
            this->zBuffer[i][2], this->zBuffer[i][3],
            this->zBuffer[i][4], this->zBuffer[i][5],
            this->zBuffer[i][6]);
    }

    lcd.drawImageFromBuffer(this->scrBuffer, 0, 0, 480, 272);
}

// Reset z buffer and clear screen buffer
void threedee::reset() {
    this->zBufferIndex = 0;
    memset(this->scrBuffer, 0, 480 * 272 * sizeof(uint32_t));
}

// Move camera relatively
void threedee::move(int dx, int dy, int dxRot, int dyRot) {
    this->xRot += dxRot;
    this->yRot += dyRot;
    this->camY += (_sin(xRot) * dy) / 256;
    this->camX += (_cos(xRot) * dy) / 256;
    this->camY += (_sin(xRot + 70) * dx) / 256;
    this->camX += (_cos(xRot + 70) * dx) / 256;
}

// Set camera position
void threedee::setCam(int x, int y, int z, int xRot, int yRot) {
    this->camX = x;
    this->camY = y;
    this->camZ = z;
    this->xRot = xRot;
    this->yRot = yRot;
}

// Basic shading
// (for the record, this is 100% original code)
uint32_t threedee::getPolygonColor(int distance, uint32_t color) {
    int red = (color & 0xFF0000) >> 16;
    int green = (color & 0x00FF00) >> 8;
    int blue = (color & 0x0000FF);
    int newdistance = (int) (distance / 1.25f);
    int distsub = 64;
    int cr = red + (distsub - newdistance);
    int cg = green + (distsub - newdistance);
    int cb = blue + (distsub - newdistance);
    int maxr = red + 16;
    int maxg = green + 16;
    int maxb = blue + 16;
    int minr = (int) (red / 2.5f);
    int ming = (int) (green / 2.5f);
    int minb = (int) (blue / 2.5f);
    if (maxr > 255) maxr = 255;
    if (maxg > 255) maxg = 255;
    if (maxb > 255) maxb = 255;
    if (minr < 0) minr = 0;
    if (ming < 0) ming = 0;
    if (minb < 0) minb = 0;
    if (cr > maxr) cr = maxr;
    if (cg > maxg) cg = maxg;
    if (cb > maxb) cb = maxb;
    if (cr < minr) cr = minr;
    if (cg < ming) cg = ming;
    if (cb < minb) cb = minb;
    return ((cr & 0xff) << 16) + ((cg & 0xff) << 8) + (cb & 0xff);
}

// Letters are 7 pixels tall and 5 pixels wide.

// http://redd.it/2ba3g3
static const char LINES[]   = "BCDEIKOPQRSTUVYZ\\_`";
static const char LETTERS[] =
    "DFJSJJJRJJRJJRGJIIIJGRJJJJJRSIIRIISSIIRIIIHIILJJHJJJSJJJGDDDD"
    "DGAAAAAJHJKMOMKJIIIIIISJQNJJJJJJPNLJJGJJJJJGRJJRIIIGJJJNGCRJJ"
    "RMKJGJIGAJGSDDDDDDJJJJJJGJJJJJFDJJJNQJJJJFDFJJJJFDDDDSABDEIS";

int threedee::fontLine(int c, int row) {
    return c == ' ' ? 0 : LINES[LETTERS[(c - 'A') * 7 + row] - 'A'] - 'A';
}

void threedee::drawText(int px, int py, int size, uint32_t color, const char *message) {
    size ++;
    for (int y = 0; y < 7; y ++) {
        for (int x = 0; message[x]; x ++) {
            int c = message[x];
            int line = this->fontLine(c, y);
            for (int i = 0; i < 5; i++) {
                if ((line >> i) & 0x01) {
                    int dx = px + (x * 6 + (4 - i)) * size;
                    int dy = py + y * size;
                    if (size == 1)
                        setPixel(dx, dy, color);
                    else
                        for (int x2 = 0; x2 < size; x2 ++)
                            for (int y2 = 0; y2 < size; y2 ++)
                                setPixel(dx + x2, dy + y2, color);
                }
            }
        }
    }
}