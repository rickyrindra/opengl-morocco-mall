#include <windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <vector>
#include <cmath>

void init(void);
void tampil(void);
void ukuran(int, int);

// mouse
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

// keyboard
void keyboard(unsigned char, int, int);

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(250,80);
    glutCreateWindow("MOROCCO MALL");
    init();

    // transparan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(tampil);
    glutReshapeFunc(ukuran);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(62/255.f,185/255.f,255/255.f,1.0);
    glMatrixMode(GL_PROJECTION);

    // lighting
    // glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    is_depth=1;

    glMatrixMode(GL_MODELVIEW);
}

void tampil(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // mouse
    glPushMatrix();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    //pondasi
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glVertex3f(-350, -50, -140);
        glVertex3f(350, -50, -140);
        glVertex3f(350, -50, 100);
        glVertex3f(-350, -50, 100);
    glEnd();

    //dinding deva
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(120, -50, 50);
        glVertex3f(220, -50, 25);
        glVertex3f(220, 70, 25);
        glVertex3f(120, 70, 50);
    glEnd();
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-30, -50, 55);
        glVertex3f(120, -50, 50);
        glVertex3f(120, 70, 50);
        glVertex3f(-30, 70, 55);
    glEnd();
        glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-280, -50, -60);
        glVertex3f(-190, -50, -60);
        glVertex3f(-190, 70, -60);
        glVertex3f(-280, 70, -60);
    glEnd();
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-170, -50, -60);
        glVertex3f(-130, -50, -60);
        glVertex3f(-130, 70, -60);
        glVertex3f(-170, 70, -60);
    glEnd();

    // dinding pele
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-280, -50, 40);
        glVertex3f(-200, -50, 55);
        glVertex3f(-200, 70, 55);
        glVertex3f(-280, 70, 40);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-180, -50, 55);
        glVertex3f(-50, -50, 55);
        glVertex3f(-50, 70, 55);
        glVertex3f(-180, 70, 55);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-280, -50, 40);
        glVertex3f(-280, -50, -60);
        glVertex3f(-280, 70, -60);
        glVertex3f(-280, 70, 40);
    glEnd();

    // dinding jek
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
        glVertex3f(220, -50, -30);
        glVertex3f(120, -50, -50);
        glVertex3f(120, 70, -50);
        glVertex3f(220, 70, -30);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
        glVertex3f(120, -50, -50);
        glVertex3f(-30, -50, -50);
        glVertex3f(-30, 70, -50);
        glVertex3f(120, 70, -50);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
        glVertex3f(-50, -50, -50);
        glVertex3f(-130, -50, -60);
        glVertex3f(-130, 70, -60);
        glVertex3f(-50, 70, -50);
    glEnd();

    // atap
    glColor3f(0.85,0.85,0.85);
    glBegin(GL_POLYGON);
        glVertex3d(220, 70, 25);
        glVertex3d(120, 70, 50);
        glVertex3d(-30, 70, 55);
        glVertex3d(-50, 70, 55);
        glVertex3d(-180, 70, 55);
        glVertex3d(-200, 70, 55);
        glVertex3d(-280, 70, 40);
        glVertex3d(-280, 70, -60);
        glVertex3d(-130, 70, -60);
        glVertex3d(-50, 70, -50);
        glVertex3d(120, 70, -50);
        glVertex3d(220, 70, -30);
    glEnd();

    // lantai
    glColor3f(0.85,0.85,0.85);
    glBegin(GL_POLYGON);
        glVertex3f(220, -49.8, 25);
        glVertex3f(120, -49.8, 50);
        glVertex3f(-30, -49.8, 55);
        glVertex3f(-50, -49.8, 55);
        glVertex3f(-180, -49.8, 55);
        glVertex3f(-200, -49.8, 55);
        glVertex3f(-280, -49.8, 40);
        glVertex3f(-280, -49.8, -60);
        glVertex3f(-130, -49.8, -60);
        glVertex3f(-50, -49.8, -50);
        glVertex3f(120, -49.8, -50);
        glVertex3f(220, -49.8, -30);
    glEnd();

    // trotoar
    glColor3f(229/255.f, 148/255.f, 148/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-280,-49.9,-80);
        glVertex3f(220,-49.9,-80);
        glVertex3f(220,-49.9,75);
        glVertex3f(-280,-49.9,75);
    glEnd();

    // rumput
    glColor3f(15/255.f, 154/255.f, 3/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-280,-49.9,-140);
        glVertex3f(220,-49.9,-140);
        glVertex3f(220,-49.9,-80);
        glVertex3f(-280,-49.9,-80);
    glEnd();

    // kolam
    glColor3f(22/255.f, 111/255.f, 194/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-120, -49.8, -110);
        glVertex3f(-75, -49.8, -125);
        glVertex3f(-30, -49.8, -130);
        glVertex3f(30, -49.8, -130);
        glVertex3f(75, -49.8, -125);
        glVertex3f(120, -49.8, -110);
        glVertex3f(75, -49.8, -95);
        glVertex3f(30, -49.8, -90);
        glVertex3f(-30, -49.8, -90);
        glVertex3f(-75, -49.8, -95);
    glEnd();

    //KACA KIRI KOLAM RENANG
    for(int i= -50;i< -30;i+=4)
    {
        for(int j= -20;j<70;j+=10)
        {
            int x = i+4;
            int y = j+10;
            int z = -50;
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(i,y,z);
            glVertex3f(x,y,z);
            glVertex3f(x,j,z);
            glVertex3f(i,j,z);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(i,y,z);
            glVertex3f(i,j,z);
            glVertex3f(x,j,z);
            glVertex3f(x,y,z);
        glEnd();
        }
    }

    //KACA KANAN KOLAM RENANG
    for(int i= -190;i< -170;i+=4)
    {
        for(int j= -20;j<70;j+=10)
        {
            int x = i+4;
            int y = j+10;
            int z = -60;
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(i,y,z);
            glVertex3f(x,y,z);
            glVertex3f(x,j,z);
            glVertex3f(i,j,z);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(i,y,z);
            glVertex3f(i,j,z);
            glVertex3f(x,j,z);
            glVertex3f(x,y,z);
        glEnd();
        }
    }

    //KACA KANAN
    for(int i= -50;i< -30;i+=4)
    {
        for(int j= -20;j<70;j+=10)
        {
            int x = i+4;
            int y = j+10;
            int z = 55;
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(i,y,z);
            glVertex3f(x,y,z);
            glVertex3f(x,j,z);
            glVertex3f(i,j,z);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(i,y,z);
            glVertex3f(i,j,z);
            glVertex3f(x,j,z);
            glVertex3f(x,y,z);
        glEnd();
        }
    }

    //KACA KIRI
    for(int i= -200;i< -180;i+=4)
    {
        for(int j= -20;j<70;j+=10)
        {
            int x = i+4;
            int y = j+10;
            int z = 55;
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(i,y,z);
            glVertex3f(x,y,z);
            glVertex3f(x,j,z);
            glVertex3f(i,j,z);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(i,y,z);
            glVertex3f(i,j,z);
            glVertex3f(x,j,z);
            glVertex3f(x,y,z);
        glEnd();
        }
    }

    //matahari
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslated(0,300,0);
        glutSolidSphere(15,20,20);
    glPopMatrix();
    
    //papan iklan
    for(int i=0; i<2; i++){
        glColor3f(221/255.f, 208/255.f, 141/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(20+(i*40),-30,55);
            glColor3f(214/255.f,21/255.f,15/255.f);
            glVertex3f(50+(i*40),-30,55);
            glColor3f(21/255.f,24/255.f,0/255.f);
            glVertex3f(50+(i*40),40,55);
            glColor3f(231/255.f,24/255.f,536/255.f);
            glVertex3f(20+(i*40),40,55);
        glEnd();
        glColor3f(255/255.f, 255/255.f, 255/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(20+(i*40),-30,55);
            glVertex3f(20+(i*40),-30,53);
            glVertex3f(20+(i*40),40,53);
            glVertex3f(20+(i*40),40,55);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(50+(i*40),-30,55);
            glVertex3f(50+(i*40),-30,53);
            glVertex3f(50+(i*40),40,53);
            glVertex3f(50+(i*40),40,55);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(20+(i*40),40,55);
            glVertex3f(20+(i*40),40,53);
            glVertex3f(50+(i*40),40,53);
            glVertex3f(50+(i*40),40,55);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(20+(i*40),-30,55);
            glVertex3f(20+(i*40),-30,53);
            glVertex3f(50+(i*40),-30,53);
            glVertex3f(50+(i*40),-30,55);
        glEnd();
    }
    for(int i=0; i<3; i++){
        glColor3f(221/255.f, 208/255.f, 141/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(-170+(i*40),-30,58);
            glColor3f(25/255.f,21/255.f,15/255.f);
            glVertex3f(-140+(i*40),-30,58);
            glColor3f(21/255.f,24/255.f,0/255.f);
            glVertex3f(-140+(i*40),40,58);
            glColor3f(341/255.f,24/255.f,12/255.f);
            glVertex3f(-170+(i*40),40,58);
        glEnd();
        glColor3f(255/255.f, 255/255.f, 255/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(-170+(i*40),-30,58);
            glVertex3f(-170+(i*40),-30,56);
            glVertex3f(-170+(i*40),40,58);
            glVertex3f(-170+(i*40),40,56);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(-140+(i*40),-30,58);
            glVertex3f(-140+(i*40),-30,56);
            glVertex3f(-140+(i*40),40,56);
            glVertex3f(-140+(i*40),40,58);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(-170+(i*40),40,58);
            glVertex3f(-170+(i*40),40,56);
            glVertex3f(-140+(i*40),40,56);
            glVertex3f(-140+(i*40),40,58);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(-170+(i*40),-30,58);
            glVertex3f(-170+(i*40),-30,56);
            glVertex3f(-140+(i*40),-30,56);
            glVertex3f(-140+(i*40),-30,58);
        glEnd();
    }

    // Cafe
    for(int i=0; i<3; i++){
        glColor3f(0.9,0.9,0.9);
        glBegin(GL_QUADS); // dinding
            glVertex3f(-10+(i*40),-50,-50.1);
            glVertex3f(20+(i*40),-50,-50.1);
            glVertex3f(20+(i*40),-20,-50.1);
            glVertex3f(-10+(i*40),-20,-50.1);
        glEnd();
        glColor3f(0.5,0.5,0.5);
        glBegin(GL_QUADS); // kanopi
            glVertex3f(-10+(i*40),-20,-50.1);
            glVertex3f(20+(i*40),-20,-50.1);
            glVertex3f(20+(i*40),-23,-70);
            glVertex3f(-10+(i*40),-23,-70);
        glEnd();
        glBegin(GL_QUADS); // tiang kanopi
            glVertex3f(-10+(i*40),-50,-70);
            glVertex3f(-8+(i*40),-50,-70);
            glVertex3f(-8+(i*40),-23,-70);
            glVertex3f(-10+(i*40),-23,-70);
        glEnd();
        glBegin(GL_QUADS); // tiang kanopi
            glVertex3f(18+(i*40),-50,-70);
            glVertex3f(20+(i*40),-50,-70);
            glVertex3f(20+(i*40),-23,-70);
            glVertex3f(18+(i*40),-23,-70);
        glEnd();
        glColor3f(80/255.f, 80/255.f, 80/255.f);
        glBegin(GL_QUADS); // pintu
            glVertex3f(2+(i*40),-50,-50.2);
            glVertex3f(8+(i*40),-50,-50.2);
            glVertex3f(8+(i*40),-30,-50.2);
            glVertex3f(2+(i*40),-30,-50.2);
        glEnd();
        glColor3f(215/255.f, 255/255.f, 253/255.f);
        glBegin(GL_QUADS); // jendela 1
            glVertex3f(-8+(i*40),-48,-50.2);
            glVertex3f(1+(i*40),-48,-50.2);
            glVertex3f(1+(i*40),-32,-50.2);
            glVertex3f(-8+(i*40),-32,-50.2);
        glEnd();
        glBegin(GL_QUADS); // jendela 2
            glVertex3f(9+(i*40),-48,-50.2);
            glVertex3f(18+(i*40),-48,-50.2);
            glVertex3f(18+(i*40),-32,-50.2);
            glVertex3f(9+(i*40),-32,-50.2);
        glEnd();
        glColor3f(230/255.f, 230/255.f, 230/255.f);
        glBegin(GL_QUADS); // papan iklan bawah
            glVertex3f(-12+(i*40),-20,-55);
            glVertex3f(22+(i*40),-20,-55);
            glVertex3f(22+(i*40),-10,-55);
            glVertex3f(-12+(i*40),-10,-55);
        glEnd();
        glBegin(GL_QUADS); // papan iklan bawah
            glVertex3f(-12+(i*40),-10,-55);
            glVertex3f(-12+(i*40),-10,-50);
            glVertex3f(22+(i*40),-10,-50);
            glVertex3f(22+(i*40),-10,-55);
        glEnd();
        glColor3f(220/255.f, 220/255.f, 220/255.f);
        glBegin(GL_QUADS); // papan iklan bawah
            glVertex3f(-12+(i*40),-20,-55);
            glVertex3f(-12+(i*40),-20,-50);
            glVertex3f(-12+(i*40),-10,-50);
            glVertex3f(-12+(i*40),-10,-55);
        glEnd();
        glBegin(GL_QUADS); // papan iklan bawah
            glVertex3f(22+(i*40),-20,-55);
            glVertex3f(22+(i*40),-20,-50);
            glVertex3f(22+(i*40),-10,-50);
            glVertex3f(22+(i*40),-10,-55);
        glEnd();
        glColor3f(221/255.f, 208/255.f, 141/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(-10+(i*40),-20,-52);
            glVertex3f(20+(i*40),-20,-52);
            glVertex3f(20+(i*40),30,-52);
            glVertex3f(-10+(i*40),30,-52);
        glEnd();
        glColor3f(202/255.f, 189/255.f, 124/255.f);
        glBegin(GL_QUADS); // banner
            glVertex3f(-10+(i*40),-20,-52);
            glVertex3f(-10+(i*40),-20,-50);
            glVertex3f(-10+(i*40),30,-50);
            glVertex3f(-10+(i*40),30,-52);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(20+(i*40),-20,-52);
            glVertex3f(20+(i*40),-20,-50);
            glVertex3f(20+(i*40),30,-50);
            glVertex3f(20+(i*40),30,-52);
        glEnd();
        glBegin(GL_QUADS); // banner
            glVertex3f(-10+(i*40),30,-52);
            glVertex3f(-10+(i*40),30,-50);
            glVertex3f(20+(i*40),30,-50);
            glVertex3f(20+(i*40),30,-52);
        glEnd();
    }

    // balkon lurus kiri
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-10,-60);
        glVertex3f(-140,-10,-60);
        glVertex3f(-140,-10,-70);
        glVertex3f(-160,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-12,-60);
        glVertex3f(-140,-12,-60);
        glVertex3f(-140,-12,-70);
        glVertex3f(-160,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-10,-70);
        glVertex3f(-140,-10,-70);
        glVertex3f(-140,-12,-70);
        glVertex3f(-160,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-12,-70);
        glVertex3f(-160,-12,-60);
        glVertex3f(-160,-10,-60);
        glVertex3f(-160,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-140,-12,-70);
        glVertex3f(-140,-12,-60);
        glVertex3f(-140,-10,-60);
        glVertex3f(-140,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,30,-60);
        glVertex3f(-140,30,-60);
        glVertex3f(-140,30,-70);
        glVertex3f(-160,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,28,-60);
        glVertex3f(-140,28,-60);
        glVertex3f(-140,28,-70);
        glVertex3f(-160,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,30,-70);
        glVertex3f(-140,30,-70);
        glVertex3f(-140,28,-70);
        glVertex3f(-160,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,28,-70);
        glVertex3f(-160,28,-60);
        glVertex3f(-160,30,-60);
        glVertex3f(-160,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-140,28,-70);
        glVertex3f(-140,28,-60);
        glVertex3f(-140,30,-60);
        glVertex3f(-140,30,-70);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-160,-10,-70);
        glVertex3f(-159,-10,-70);
        glVertex3f(-159,5,-70);
        glVertex3f(-160,5,-70);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-141,-10,-70);
        glVertex3f(-140,-10,-70);
        glVertex3f(-140,5,-70);
        glVertex3f(-141,5,-70);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    glBegin(GL_QUADS); // pintu
        glVertex3f(-155,-10,-60.1);
        glVertex3f(-145,-10,-60.1);
        glVertex3f(-145,10,-60.1);
        glVertex3f(-155,10,-60.1);
    glEnd();
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-159,-9,-70);
        glVertex3f(-141,-9,-70);
        glVertex3f(-141,4,-70);
        glVertex3f(-159,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-160,-9,-70);
        glVertex3f(-160,-9,-60);
        glVertex3f(-160,4,-60);
        glVertex3f(-160,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-140,-9,-70);
        glVertex3f(-140,-9,-60);
        glVertex3f(-140,4,-60);
        glVertex3f(-140,4,-70);
    glEnd();

    // balkon lurus kanan
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-10,-60);
        glVertex3f(-200,-10,-60);
        glVertex3f(-200,-10,-70);
        glVertex3f(-270,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-12,-60);
        glVertex3f(-200,-12,-60);
        glVertex3f(-200,-12,-70);
        glVertex3f(-270,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-10,-70);
        glVertex3f(-200,-10,-70);
        glVertex3f(-200,-12,-70);
        glVertex3f(-270,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-12,-70);
        glVertex3f(-270,-12,-60);
        glVertex3f(-270,-10,-60);
        glVertex3f(-270,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-200,-12,-70);
        glVertex3f(-200,-12,-60);
        glVertex3f(-200,-10,-60);
        glVertex3f(-200,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,30,-60);
        glVertex3f(-200,30,-60);
        glVertex3f(-200,30,-70);
        glVertex3f(-270,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,28,-60);
        glVertex3f(-200,28,-60);
        glVertex3f(-200,28,-70);
        glVertex3f(-270,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,30,-70);
        glVertex3f(-200,30,-70);
        glVertex3f(-200,28,-70);
        glVertex3f(-270,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,28,-70);
        glVertex3f(-270,28,-60);
        glVertex3f(-270,30,-60);
        glVertex3f(-270,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-200,28,-70);
        glVertex3f(-200,28,-60);
        glVertex3f(-200,30,-60);
        glVertex3f(-200,30,-70);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-270,-10,-70);
        glVertex3f(-269,-10,-70);
        glVertex3f(-269,5,-70);
        glVertex3f(-270,5,-70);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-201,-10,-70);
        glVertex3f(-200,-10,-70);
        glVertex3f(-200,5,-70);
        glVertex3f(-201,5,-70);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    for(int i=0; i<3; i++){
        glBegin(GL_QUADS); // pintu
            glVertex3f(-260+(i*20),-10,-60.1);
            glVertex3f(-250+(i*20),-10,-60.1);
            glVertex3f(-250+(i*20),10,-60.1);
            glVertex3f(-260+(i*20),10,-60.1);
        glEnd();
    }
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-269,-9,-70);
        glVertex3f(-201,-9,-70);
        glVertex3f(-201,4,-70);
        glVertex3f(-269,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-270,-9,-70);
        glVertex3f(-270,-9,-60);
        glVertex3f(-270,4,-60);
        glVertex3f(-270,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-200,-9,-70);
        glVertex3f(-200,-9,-60);
        glVertex3f(-200,4,-60);
        glVertex3f(-200,4,-70);
    glEnd();

    // balkon miring
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-10,-58.75);
        glVertex3f(-60,-10,-51.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-120,-10,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-12,-58.75);
        glVertex3f(-60,-12,-51.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-120,-12,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-120,-12,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-12,-58.75);
        glVertex3f(-120,-12,-68.75);
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-120,-10,-58.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-60,-12,-51.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,-10,-51.25);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,30,-58.75);
        glVertex3f(-60,30,-51.25);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-120,30,-68.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,28,-58.75);
        glVertex3f(-60,28,-51.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-120,28,-68.75);
    glEnd();
        glBegin(GL_QUADS); // atap
        glVertex3f(-120,30,-68.75);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-120,28,-68.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,28,-58.75);
        glVertex3f(-120,28,-68.75);
        glVertex3f(-120,30,-68.75);
        glVertex3f(-120,30,-58.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-60,28,-51.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-60,30,-51.25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-119,-10,-68.75);
        glVertex3f(-119,5,-68.75);
        glVertex3f(-120,5,-68.75);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-61,-10,-61.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,5,-61.25);
        glVertex3f(-61,5,-61.25);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    glBegin(GL_QUADS); // pintu
        glVertex3f(-80,-10,-53.76);
        glVertex3f(-70,-10,-52.51);
        glVertex3f(-70,10,-52.51);
        glVertex3f(-80,10,-53.76);
    glEnd();
    glBegin(GL_QUADS); // pintu
        glVertex3f(-95,-10,-55.76);
        glVertex3f(-85,-10,-54.51);
        glVertex3f(-85,10,-54.51);
        glVertex3f(-95,10,-55.76);
    glEnd();
    glBegin(GL_QUADS); // pintu
        glVertex3f(-110,-10,-57.51);
        glVertex3f(-100,-10,-56.26);
        glVertex3f(-100,10,-56.26);
        glVertex3f(-110,10,-57.51);
    glEnd();
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-119,-9,-68.75);
        glVertex3f(-61,-9,-61.25);
        glVertex3f(-61,4,-61.25);
        glVertex3f(-119,4,-68.75);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-120,-9,-58.75);
        glVertex3f(-120,-9,-68.75);
        glVertex3f(-120,4,-68.75);
        glVertex3f(-120,4,-58.75);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-60,-9,-51.25);
        glVertex3f(-60,-9,-61.25);
        glVertex3f(-60,4,-61.25);
        glVertex3f(-60,4,-51.25);
    glEnd();
    
    // balkon lurus kiri
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-10,-60);
        glVertex3f(-140,-10,-60);
        glVertex3f(-140,-10,-70);
        glVertex3f(-160,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-12,-60);
        glVertex3f(-140,-12,-60);
        glVertex3f(-140,-12,-70);
        glVertex3f(-160,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-10,-70);
        glVertex3f(-140,-10,-70);
        glVertex3f(-140,-12,-70);
        glVertex3f(-160,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-160,-12,-70);
        glVertex3f(-160,-12,-60);
        glVertex3f(-160,-10,-60);
        glVertex3f(-160,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-140,-12,-70);
        glVertex3f(-140,-12,-60);
        glVertex3f(-140,-10,-60);
        glVertex3f(-140,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,30,-60);
        glVertex3f(-140,30,-60);
        glVertex3f(-140,30,-70);
        glVertex3f(-160,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,28,-60);
        glVertex3f(-140,28,-60);
        glVertex3f(-140,28,-70);
        glVertex3f(-160,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,30,-70);
        glVertex3f(-140,30,-70);
        glVertex3f(-140,28,-70);
        glVertex3f(-160,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-160,28,-70);
        glVertex3f(-160,28,-60);
        glVertex3f(-160,30,-60);
        glVertex3f(-160,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-140,28,-70);
        glVertex3f(-140,28,-60);
        glVertex3f(-140,30,-60);
        glVertex3f(-140,30,-70);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-160,-10,-70);
        glVertex3f(-159,-10,-70);
        glVertex3f(-159,5,-70);
        glVertex3f(-160,5,-70);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-141,-10,-70);
        glVertex3f(-140,-10,-70);
        glVertex3f(-140,5,-70);
        glVertex3f(-141,5,-70);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    glBegin(GL_QUADS); // pintu
        glVertex3f(-155,-10,-60.1);
        glVertex3f(-145,-10,-60.1);
        glVertex3f(-145,10,-60.1);
        glVertex3f(-155,10,-60.1);
    glEnd();
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-159,-9,-70);
        glVertex3f(-141,-9,-70);
        glVertex3f(-141,4,-70);
        glVertex3f(-159,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-160,-9,-70);
        glVertex3f(-160,-9,-60);
        glVertex3f(-160,4,-60);
        glVertex3f(-160,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-140,-9,-70);
        glVertex3f(-140,-9,-60);
        glVertex3f(-140,4,-60);
        glVertex3f(-140,4,-70);
    glEnd();

    // balkon lurus kanan
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-10,-60);
        glVertex3f(-200,-10,-60);
        glVertex3f(-200,-10,-70);
        glVertex3f(-270,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-12,-60);
        glVertex3f(-200,-12,-60);
        glVertex3f(-200,-12,-70);
        glVertex3f(-270,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-10,-70);
        glVertex3f(-200,-10,-70);
        glVertex3f(-200,-12,-70);
        glVertex3f(-270,-12,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-270,-12,-70);
        glVertex3f(-270,-12,-60);
        glVertex3f(-270,-10,-60);
        glVertex3f(-270,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-200,-12,-70);
        glVertex3f(-200,-12,-60);
        glVertex3f(-200,-10,-60);
        glVertex3f(-200,-10,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,30,-60);
        glVertex3f(-200,30,-60);
        glVertex3f(-200,30,-70);
        glVertex3f(-270,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,28,-60);
        glVertex3f(-200,28,-60);
        glVertex3f(-200,28,-70);
        glVertex3f(-270,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,30,-70);
        glVertex3f(-200,30,-70);
        glVertex3f(-200,28,-70);
        glVertex3f(-270,28,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-270,28,-70);
        glVertex3f(-270,28,-60);
        glVertex3f(-270,30,-60);
        glVertex3f(-270,30,-70);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-200,28,-70);
        glVertex3f(-200,28,-60);
        glVertex3f(-200,30,-60);
        glVertex3f(-200,30,-70);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-270,-10,-70);
        glVertex3f(-269,-10,-70);
        glVertex3f(-269,5,-70);
        glVertex3f(-270,5,-70);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-201,-10,-70);
        glVertex3f(-200,-10,-70);
        glVertex3f(-200,5,-70);
        glVertex3f(-201,5,-70);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    for(int i=0; i<3; i++){
        glBegin(GL_QUADS); // pintu
            glVertex3f(-260+(i*20),-10,-60.1);
            glVertex3f(-250+(i*20),-10,-60.1);
            glVertex3f(-250+(i*20),10,-60.1);
            glVertex3f(-260+(i*20),10,-60.1);
        glEnd();
    }
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-269,-9,-70);
        glVertex3f(-201,-9,-70);
        glVertex3f(-201,4,-70);
        glVertex3f(-269,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-270,-9,-70);
        glVertex3f(-270,-9,-60);
        glVertex3f(-270,4,-60);
        glVertex3f(-270,4,-70);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-200,-9,-70);
        glVertex3f(-200,-9,-60);
        glVertex3f(-200,4,-60);
        glVertex3f(-200,4,-70);
    glEnd();

    // balkon miring
    glColor3f(180/255.f, 180/255.f, 180/255.f);
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-10,-58.75);
        glVertex3f(-60,-10,-51.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-120,-10,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-12,-58.75);
        glVertex3f(-60,-12,-51.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-120,-12,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-120,-12,-68.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-120,-12,-58.75);
        glVertex3f(-120,-12,-68.75);
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-120,-10,-58.75);
    glEnd();
    glBegin(GL_QUADS); // lantai
        glVertex3f(-60,-12,-51.25);
        glVertex3f(-60,-12,-61.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,-10,-51.25);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,30,-58.75);
        glVertex3f(-60,30,-51.25);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-120,30,-68.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,28,-58.75);
        glVertex3f(-60,28,-51.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-120,28,-68.75);
    glEnd();
        glBegin(GL_QUADS); // atap
        glVertex3f(-120,30,-68.75);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-120,28,-68.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-120,28,-58.75);
        glVertex3f(-120,28,-68.75);
        glVertex3f(-120,30,-68.75);
        glVertex3f(-120,30,-58.75);
    glEnd();
    glBegin(GL_QUADS); // atap
        glVertex3f(-60,28,-51.25);
        glVertex3f(-60,28,-61.25);
        glVertex3f(-60,30,-61.25);
        glVertex3f(-60,30,-51.25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-120,-10,-68.75);
        glVertex3f(-119,-10,-68.75);
        glVertex3f(-119,5,-68.75);
        glVertex3f(-120,5,-68.75);
    glEnd();
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-61,-10,-61.25);
        glVertex3f(-60,-10,-61.25);
        glVertex3f(-60,5,-61.25);
        glVertex3f(-61,5,-61.25);
    glEnd();
    glColor3f(80/255.f, 80/255.f, 80/255.f);
    glBegin(GL_QUADS); // pintu
        glVertex3f(-80,-10,-53.76);
        glVertex3f(-70,-10,-52.51);
        glVertex3f(-70,10,-52.51);
        glVertex3f(-80,10,-53.76);
    glEnd();
    glBegin(GL_QUADS); // pintu
        glVertex3f(-95,-10,-55.76);
        glVertex3f(-85,-10,-54.51);
        glVertex3f(-85,10,-54.51);
        glVertex3f(-95,10,-55.76);
    glEnd();
    glBegin(GL_QUADS); // pintu
        glVertex3f(-110,-10,-57.51);
        glVertex3f(-100,-10,-56.26);
        glVertex3f(-100,10,-56.26);
        glVertex3f(-110,10,-57.51);
    glEnd();
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-119,-9,-68.75);
        glVertex3f(-61,-9,-61.25);
        glVertex3f(-61,4,-61.25);
        glVertex3f(-119,4,-68.75);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-120,-9,-58.75);
        glVertex3f(-120,-9,-68.75);
        glVertex3f(-120,4,-68.75);
        glVertex3f(-120,4,-58.75);
    glEnd();
    glBegin(GL_QUADS); // kaca
        glVertex3f(-60,-9,-51.25);
        glVertex3f(-60,-9,-61.25);
        glVertex3f(-60,4,-61.25);
        glVertex3f(-60,4,-51.25);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void idle(){
    if(!mouseDown){
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'w':
        case 'W':
            glTranslatef(0.0,0.0,3.0);
            break;
        case 'd':
        case 'D':
            glTranslatef(3.0,0.0,0.0);
            break;
        case 's':
        case 'S':
            glTranslatef(0.0,0.0,-3.0);
            break;
        case 'a':
        case 'A':
            glTranslatef(-3.0,0.0,0.0);
            break;
        case '7':
            glTranslatef(0.0,3.0,0.0);
            break;
        case '9':
            glTranslatef(0.0,-3.0,0.0);
            break;
        case '2':
            glRotatef(2.0,1.0,0.0,0.0);
            break;
        case '8':
            glRotatef(-2.0,1.0,0.0,0.0);
            break;
        case '6':
            glRotatef(2.0,0.0,1.0,0.0);
            break;
        case '4':
            glRotatef(-2.0,0.0,1.0,0.0);
            break;
        case '1':
            glRotatef(2.0,0.0,0.0,1.0);
            break;
        case '3':
            glRotatef(-2.0,0.0,0.0,1.0);
            break;
        case '5':
            if(is_depth){
                is_depth=0;
                glDisable(GL_DEPTH_TEST);
            } else{
                is_depth=1;
                glEnable(GL_DEPTH_TEST);
            }
    }
    tampil();
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseDown = true;
        xdiff = x-yrot;
        ydiff = -y + xrot;
    } else{
        mouseDown = false;
    }
}

void mouseMotion(int x, int y){
    if(mouseDown){
        yrot = x-xdiff;
        xrot = y+ydiff;

        glutPostRedisplay();
    }
}

void ukuran(int lebar, int tinggi){
    if(tinggi == 0) tinggi = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130.0, lebar/tinggi,5.0,1000.0);
    glTranslatef(0.0,-5.0,-150.0);
    glMatrixMode(GL_MODELVIEW);
}

