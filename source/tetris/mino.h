#pragma once
#include "xy.h"
#include <vector>

using namespace std;

//テトリミノを定義
vector<MINO> I = { {0,1},{1,1},{2,1},{3,1} };
vector<MINO> O = { {1,0},{1,1},{2,0},{2,1} };
vector<MINO> S = { {0,1},{1,1},{1,0},{2,0} };
vector<MINO> Z = { {1,0},{2,0},{2,1},{3,1} };
vector<MINO> J = { {0,0},{0,1},{1,1},{2,1} };
vector<MINO> L = { {1,1},{2,1},{3,1},{3,0} };
vector<MINO> T = { {0,1},{1,1},{1,0},{2,1} };
//ミノの種類はI,O,S,Z,J,L,T
//ミノをまとめる
vector<vector<MINO>> mino ={ I,O,S,Z,J,L,T };
vector<MINO> noflymino;
//ディスプレイバッファ
vector<vector<bool>> display_data(20, vector<bool>(14, false));
COLOR no_mino = { 0.0f,0.0f,0.0f,0.0f };
COLOR mino_color = {1.0f,0.2f,0.2f,1.0f };



int x = 0;
int y = 0;
int rotation = 0;
int score = 0;


// 当たり判定
bool fly_mino(int x, int y) {
    if (y == 19) return true;
    if (display_data[y + 1][x]) return true;
    else return false;
}

void tetris() {
    float scoreboost = 1.0;
    for (int h = 0; h < 20; h++) {
        int i = 0;
        for (int w = 0; w < 14; w++) {
            if (display_data[h][w]) i++;
        }
        if (i == 14) {
            for (int w = 0; w < 14; w++) {
                display_data[h][w] = false;
                
            }
            score += round(50 * scoreboost);
            scoreboost += 0.25;
            
        }
    }
}

void rotation_mino(int r,int type) {
    for (int i = 0; i < mino[type].size(); i++) {
        int temp = mino[type][i].x;
        mino[type][i].x = mino[type][i].y;
        mino[type][i].y = temp;
        switch (r) {
        case 2:
            mino[type][i].x = 3 - mino[type][i].x;
            break;
        }
    }
}

void block_fly() {
    for (int h = 0; h < 19; h++) {
        int i = 0;
        for (int w = 0; w < 14; w++) {
            if (!display_data[h+1][w]) i++;
        }
        if (i == 14) {
            for (int w = 0; w < 14; w++) {
                if (display_data[h][w]) {
                    display_data[h + 1][w] = true;
                    display_data[h][w] = false;
                }
            }
          
        }
    }
}


void randomcolor() {
    float color[3] = { mino_color.r,mino_color.g,mino_color.b };
    if (color[0] == color[1]) {
        mino_color.r = 1.0f;
        mino_color.g = 0.2f;
        mino_color.b = 1.0f;
        return;
    }
    mino_color.r = color[rand() % 3];
    mino_color.g = color[rand() % 3];
    mino_color.b = color[rand() % 3];
   
}
//落下したブロックをblock_xyに追加
void flymino_block(int n) {
    for (int i = 0; i < mino[n].size(); i++) {
        display_data[mino[n][i].y + y / TILE_HEIGHT][mino[n][i].x + x / TILE_WIDTH] = true;
    }
}

int reset() {
    randomcolor();
    x = y = 0;
    int type = rand() % mino.size();
    return type;
}
