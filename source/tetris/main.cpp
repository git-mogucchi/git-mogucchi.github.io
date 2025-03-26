#include "xy.h"
#include "mino.h"
#include <GL/freeglut.h>
#include <vector>
#include <algorithm> 
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

int minotype;
int fcount = 0;
bool gameover = false;

// 当たり判定用

void draw_block(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + TILE_WIDTH, y);
    glVertex2i(x + TILE_WIDTH, y + TILE_HEIGHT);
    glVertex2i(x, y + TILE_HEIGHT);
    glEnd();
}

int draw_blocks(int n) {
    int errorcode = 0;
    glColor4f(1.0, 1.0, 1.0, 1.0);
    for (int h = 0; h < 20; h++) {
        for (int w = 0; w < 14; w++) {
            if (display_data[h][w]) draw_block(w * TILE_WIDTH, h * TILE_HEIGHT);
        }
    }
    if (n > mino.size()) return 1; // 即終了
    glColor4f(mino_color.r, mino_color.g, mino_color.b, mino_color.a);
    for (int i = 0; i < mino[n].size(); i++) {
        if (mino[n][i].x * TILE_WIDTH + x > WIDTH-1) return 3;
        if (mino[n][i].x * TILE_WIDTH + x < 0) return 4;
        if (fly_mino(mino[n][i].x + x / TILE_WIDTH, mino[n][i].y + y / TILE_HEIGHT)) errorcode = 2;
        draw_block(mino[n][i].x * TILE_WIDTH + x, mino[n][i].y * TILE_HEIGHT + y);
    }
    return errorcode;
}

void text() {
    int i;
    string str = "score" + to_string(score);
    if (gameover) {
        str = "Game Over..";
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glRasterPos2f(150, 300);
        for (i = 0; i < strlen(str.c_str()); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        }
        str = "Score " + to_string(score);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glRasterPos2f(170, 350);
        for (i = 0; i < strlen(str.c_str()); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        }
    }
    else {
        
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glRasterPos2f(10, 20);
        for (i = 0; i < strlen(str.c_str()); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
        }
    }
}

void draw() {
    int returncode = draw_blocks(minotype); // 戻り値を取得
    if (returncode == 2) {
        if(y <3)gameover = true;
        flymino_block(minotype);
        minotype = reset();
    }
    if (returncode == 3) {
        x -= TILE_WIDTH;
        glutPostRedisplay();
    }
    if (returncode == 4) {
        x += TILE_WIDTH;
        glutPostRedisplay();
    }
    tetris();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!gameover) {
        block_fly();
        draw();
    }
    text();
    glFlush();
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
}

void idle() {
    display();
    if (fcount == 30) {
        fcount = 0;
        y += TILE_HEIGHT;
        display();
    }
    Sleep(16.67);
    fcount++;
}

// 矢印キーの入力を処理するコールバック関数
void specialKeys(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:
        x -= TILE_WIDTH;
        break;
    case GLUT_KEY_RIGHT:
        x += TILE_WIDTH;
        break;
    case GLUT_KEY_DOWN:
        y += TILE_HEIGHT;
        break;
    case GLUT_KEY_UP:
        rotation += 1;
        rotation_mino(rotation, minotype);
        break;
    }
    rotation %= 4;
    glutPostRedisplay(); // 画面を再描画
}

int main(int argc, char* argv[]) {
    FreeConsole();
    srand((unsigned)time(NULL));
    minotype = rand() % mino.size();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tetris GUI!");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeys); // 矢印キーのコールバック関数を登録
    Init();
    glutMainLoop();
    return 0;
}