#include "Chess.h"
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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
	//������Ϸ����
	initgraph(950,950);
	//��ʾ����
	loadimage(0, "D:/Users/xia/Desktop/workplace/wuziqi/res/broad.png");
	//���غڰ�������ͼƬ
	loadimage(&m_chessBlackImg, "D:/Users/xia/Desktop/workplace/wuziqi/black.png",m_chess_size, m_chess_size,true);
	loadimage(&m_chessWhiteImg, "D:/Users/xia/Desktop/workplace/wuziqi/white.png",m_chess_size, m_chess_size, true);
	//��������
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
		//���Ͻ��ж�
		int len = sqrt(clo*clo + row * row);
		if (len < offset) {
			pos->col = (x - m_margin_x) / m_chess_size;
			pos->row = (y - m_margin_y) / m_chess_size;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//���Ͻ��ж�
		len = sqrt((clo-m_chess_size)*(clo - m_chess_size) + row * row);
		if (len < offset) {
			pos->col = ((x - m_margin_x) / m_chess_size)+1;
			pos->row = (y - m_margin_y) / m_chess_size;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
		len = sqrt(clo *clo  + (row-m_chess_size) * (row-m_chess_size));
		if (len < offset) {
			pos->col = (x - m_margin_x) / m_chess_size ;
			pos->row = ((y - m_margin_y) / m_chess_size)+1;
			if (m_chess_map[pos->col][pos->row] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
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
