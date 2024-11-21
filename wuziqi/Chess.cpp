#include "Chess.h"
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
Chess::Chess(int gradesize, int margin_x, int margin_y, int chess_size)
{
	m_gradesize = gradesize;
	m_margin_x = margin_x;
	m_margin_y = margin_y;
	m_chess_size = chess_size;
	m_chees_kind = CHESS_BLACK;
	for (int i = 0; i < gradesize; i++) {
		vector<int> row;
		for (int j = 0; j < gradesize; j++) {
			row.push_back(0);
		}
		m_chess_map.push_back(row);
	}
}

void Chess::init()
{
	//创建游戏窗口
	initgraph(950,950);
	//显示棋盘
	loadimage(0, "D:/Users/xia/Desktop/workplace/wuziqi/res/broad.png");
	//加载黑白棋棋子图片
	loadimage(&m_chessBlackImg, "D:/Users/xia/Desktop/workplace/wuziqi/black.png",m_chess_size, m_chess_size,true);
	loadimage(&m_chessWhiteImg, "D:/Users/xia/Desktop/workplace/wuziqi/white.png",m_chess_size, m_chess_size, true);
	//数据清理
	for (int i = 0; i < m_gradesize; i++) {
		for (int j = 0; j < m_gradesize; j++) {
			m_chess_map[i][j] = 0;
		}
	}
	m_chees_kind = true;
}

bool Chess::clickBoard(int x, int y, ChessPos * pos)
{
	int clo = (x - m_margin_x) % m_chess_size;
	int row = (y - m_margin_y) % m_chess_size;
	int offset = m_chess_size * 0.4;
	bool ret = false;
	do {
		//左上角判断
		int len = sqrt(clo*clo + row * row);
		if (len < offset) {
			pos->col = (x - m_margin_x) / m_chess_size;
			pos->row = (y - m_margin_y) / m_chess_size;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//右上角判断
		len = sqrt((clo-m_chess_size)*(clo - m_chess_size) + row * row);
		if (len < offset) {
			pos->col = ((x - m_margin_x) / m_chess_size)+1;
			pos->row = (y - m_margin_y) / m_chess_size;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//左下角判断
		len = sqrt(clo *clo  + (row-m_chess_size) * (row-m_chess_size));
		if (len < offset) {
			pos->col = (x - m_margin_x) / m_chess_size ;
			pos->row = ((y - m_margin_y) / m_chess_size)+1;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//右下角判断
		len = sqrt((clo - m_chess_size)*(clo - m_chess_size) + (row - m_chess_size) * (row - m_chess_size));
		if (len < offset) {
			pos->col = ((x - m_margin_x) / m_chess_size) + 1;
			pos->row = ((y - m_margin_y) / m_chess_size) + 1;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
	} while (0);
	
	return ret;
}

void Chess::chessDown(ChessPos * pos, chess_kind_t kind)
{
	int x = (pos->col-0.5) * m_chess_size + m_margin_x;
	int y = (pos->row-0.5) * m_chess_size + m_margin_y;
	if (kind == CHESS_WHITE) {
		putimagePNG(x,y,&m_chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &m_chessBlackImg);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return m_gradesize;
}

bool Chess::checkOver()
{
	return false;
}

int Chess::getChessData(ChessPos * pos)
{
	return 0;
}

void Chess::updateGameMap(ChessPos * pos)
{
	m_chess_map[pos->col][pos->row] = m_chees_kind ? CHESS_BLACK : CHESS_WHITE;

}
