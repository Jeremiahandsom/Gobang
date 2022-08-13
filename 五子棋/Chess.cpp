#include "Chess.h"
#include<math.h>
#include<mmsystem.h>;
#pragma comment(lib,"winmm.lib")    //音乐播放

//渲染透明背景的putimage
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    // 变量初始化
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;

    playerFlag = Chess_Black;

    for (int i = 0; i < gradeSize; i++)
    {
        vector<int>row;
        for (int j = 0; j < gradeSize; j++)
        {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}

void Chess::init()
{
    initgraph(672, 672, EW_SHOWCONSOLE);    //创建游戏窗口
    loadimage(0, "res/棋盘4.png");   //显示棋盘图片
    mciSendString("play res/start.wav", 0, 0, 0);   //播放开始提示音

    //加载棋子
    loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
    loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true); 

    //棋盘清零
    for (int i = 0; i < gradeSize; i++)
    {
        for (int j = 0; j < gradeSize; j++)
        {
            chessMap[i][j] = 0;
        }
    }

    playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    int col = (x - margin_x) / chessSize;   //落子左上角列数
    int row = (y - margin_y) / chessSize;   //落子左上角行数
    int LeftTopPosX = margin_x + col * chessSize;   //落子左上角横坐标
    int LeftTopPosY = margin_y + row * chessSize;   //落子左上角纵坐标
    int offset = chessSize * 0.4;       //落子阈值（鼠标点击在此范围内即可落子）

    int len;
    bool ret = false;

    do {
        //左上角的判断
        len = sqrt((x - LeftTopPosX) * (x - LeftTopPosX) + (y - LeftTopPosY) * (y - LeftTopPosY));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //右上角的判断
        int x2 = LeftTopPosX + chessSize;
        int y2 = LeftTopPosY;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //左下角的判断
        x2 = LeftTopPosX;
        y2 = LeftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //右下角的判断
        x2 = LeftTopPosX + chessSize;
        y2 = LeftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }
    } while (0);
    
    return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;  // 棋子左上角坐标
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == Chess_White)
    {
        putimagePNG(x, y, &chessWhiteImg);
    }
    else {
        putimagePNG(x, y, &chessBlackImg);
    }

    updateMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
    return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
    return chessMap[row][col];
}

bool Chess::checkOver()
{
    return false;
}

void Chess::updateMap(ChessPos* pos)
{
    chessMap[pos->row][pos->col] = playerFlag ? Chess_Black : Chess_White;
    playerFlag = !playerFlag;   //黑白方交换
}

