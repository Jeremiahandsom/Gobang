#include "Chess.h"
#include "ChessGame.h"
#include<math.h>
#include<mmsystem.h>;
#include<conio.h>
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
    initgraph(672, 672);    //创建游戏窗口
    loadimage(0, "res/棋盘4.png");   //显示棋盘图片
    mciSendString("play res/start.wav", 0, 0, 0);   //播放开始提示音

    //加载按键
    button(40, 634, 80, 35, "悔棋");
    button(270, 634, 80, 35, "认输");
    button(502, 634, 150, 35, "返回主菜单");

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

    exitFlag = false;
    admitDefeat = false;

    manLastPos.row = -1;
    manLastPos.col = -1;
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

    //超出棋盘边界时无效
    if (x > (gradeSize - 1) * chessSize + margin_x + offset || y > (gradeSize - 1) * chessSize + margin_y + offset)
        return false;

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
    mciSendString("play res/down7.wav", 0, 0, 0);   //落子声音

    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;  // 棋子左上角坐标
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == Chess_White)
    {
        putimagePNG(x, y, &chessWhiteImg);
    }
    else 
    {
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
    if (checkWin())
    {
        Sleep(1500);
        if (playerFlag == false)    //刚才下棋的是黑棋 赢
        {
            initgraph(897, 895);
            mciSendString("play res/不错.mp3", 0, 0, 0);
            loadimage(0, "res/胜利.jpg");
        }
        else
        {
            initgraph(897, 895);
            mciSendString("play res/失败.mp3", 0, 0, 0);
            loadimage(0, "res/失败.jpg");
        }
        _getch();   //暂停

        return true;
    }
    return false;
}

bool Chess::getPlayerFlag()
{
    return playerFlag;
}

bool Chess::getExitFlag()
{
    return exitFlag;
}

void Chess::exitToMenu()
{
    exitFlag = !exitFlag;
}

void Chess::updateMap(ChessPos* pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? Chess_Black : Chess_White;
    playerFlag = !playerFlag;   //黑白方交换
}

void Chess::buttonDown(int x, int y, int w, int h, const char* str)
{
    setbkmode(TRANSPARENT);     //文字背景透明
    setfillcolor(BLACK);
    fillroundrect(x, y, x + w, y + h, 10, 10);      //绘制按钮

    settextstyle(25, 0, "黑体");

    //文字居中
    int tx = x + (w - textwidth(str)) / 2;
    int ty = y + (h - textheight(str)) / 2;
    outtextxy(tx, ty, str);
}

bool Chess::getAdmitDefeat()
{
    return admitDefeat;
}

void Chess::selfDefeat()
{
    admitDefeat = !admitDefeat;
}

void Chess::updateManLastPos(ChessPos pos)
{
    manLastPos = pos;
}

void Chess::regret()
{
    IMAGE img;
    loadimage(&img, "res/棋盘4.png");

    if (manLastPos.row == -1 && manLastPos.col == -1)
    {
        HWND window = GetHWnd();	//获取窗口句柄
        MessageBox(window, "您还未下棋，不可悔棋", "警告", MB_OK);
    }

    else if (manLastPos.row == lastPos.row&&manLastPos.col==lastPos.col)
    {
        chessMap[manLastPos.row][manLastPos.col] = 0;
        int x = margin_x + chessSize * manLastPos.col - 0.5 * chessSize;  // 棋子左上角坐标
        int y = margin_y + chessSize * manLastPos.row - 0.5 * chessSize;
        putimage(x, y, chessSize, chessSize, &img, x, y, SRCCOPY);
        playerFlag = !playerFlag;
    }

    else
    {
        chessMap[manLastPos.row][manLastPos.col] = 0;
        chessMap[lastPos.row][lastPos.col] = 0;
        int x = margin_x + chessSize * manLastPos.col - 0.5 * chessSize;  // 棋子左上角坐标
        int y = margin_y + chessSize * manLastPos.row - 0.5 * chessSize;
        int x1 = margin_x + chessSize * lastPos.col - 0.5 * chessSize; 
        int y1 = margin_y + chessSize * lastPos.row - 0.5 * chessSize;
        putimage(x, y, chessSize, chessSize, &img, x, y, SRCCOPY);
        putimage(x1, y1, chessSize, chessSize, &img, x1, y1, SRCCOPY);
    }
}

bool Chess::checkWin()
{
    //最近落子点的位置
    int row = lastPos.row;
    int col = lastPos.col;

    //落子点的水平方向
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row][col - i] == chessMap[row][col - i + 1] && chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] && chessMap[row][col - i] == chessMap[row][col - i + 4])
        {
            return true;
        }
    }

    //垂直方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize &&
            chessMap[row - i][col] == chessMap[row - i + 1][col] && chessMap[row - i][col] == chessMap[row - i + 2][col] &&
            chessMap[row - i][col] == chessMap[row - i + 3][col] && chessMap[row - i][col] == chessMap[row - i + 4][col])
        {
            return true;
        }
    }

    //左下方向
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize && row + i < gradeSize && row + i - 4 >= 0 &&
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] && chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] && chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
        {
            return true;
        }
    }

    //左上方向
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize && row - i >= 0 && row - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] && chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
            chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] && chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
        {
            return true;
        }
    }

    return false;
}

void Chess::button(int x, int y, int w, int h, const char* str)
{
    setbkmode(TRANSPARENT);     //文字背景透明
    setfillcolor(BROWN);        
    fillroundrect(x, y, x + w, y + h, 10, 10);      //绘制按钮

    settextstyle(25, 0, "黑体");

    //文字居中
    int tx = x + (w - textwidth(str)) / 2;
    int ty = y + (h - textheight(str)) / 2;
    outtextxy(tx, ty, str);
}

