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

void eskalator(float aDasar, float bDasar,float tinggiDasar,float aTegak,float bTegak,
               float tinggiTegak,float aMashok,float bMashok,int aCover,
               int bCover,int yCover,float z1, float z2){
    //ESKALATOR
    //PERULANGAN TANGGA ALAS

    while(aDasar>=-190 && tinggiDasar<=-10){
        glBegin(GL_QUADS);
        glColor3f(127/255.f,127/255.f,127/255.f);
        glVertex3f(aDasar,tinggiDasar,z1);
        glVertex3f(aDasar,tinggiDasar,z2);
        glVertex3f(bDasar,tinggiDasar,z2);
        glVertex3f(bDasar,tinggiDasar,z1);
        glEnd();
        aDasar-=5;
        bDasar-=5;
        tinggiDasar+=5;
    }

    //PERULANGAN TANGGA TEGAK/KOTAK
    while(aTegak<=-150 && aTegak>=-190){
        glBegin(GL_QUADS);
        glColor3f(89/255.f,89/255.f,89/255.f);
        glVertex3f(aTegak,tinggiTegak,z1);
        glVertex3f(bTegak,tinggiTegak,z1);
        glVertex3f(bTegak,tinggiTegak+5,z1);
        glVertex3f(aTegak,tinggiTegak+5,z1);
        glEnd();
        aTegak-=5;
        bTegak-=5;
        tinggiTegak+=5;
    }

    //PERULANGAN TANGGA TEGAK/KOTAK
    while(aTegak<=-150 && aTegak>=-190){
        glBegin(GL_QUADS);
        glColor3f(89/255.f,89/255.f,89/255.f);
        glVertex3f(aTegak,tinggiTegak,z2);
        glVertex3f(bTegak,tinggiTegak,z2);
        glVertex3f(bTegak,tinggiTegak+5,z2);
        glVertex3f(aTegak,tinggiTegak+5,z2);
        glEnd();
        aTegak-=5;
        bTegak-=5;
        tinggiTegak+=5;
    }

    //PERULANGAN TANGGA MASHOK
    while(aMashok>=-190 && bMashok<-10){
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aMashok,bMashok,z1);
        glVertex3f(aMashok,bMashok,z2);
        glVertex3f(aMashok,bMashok+5,z2);
        glVertex3f(aMashok,bMashok+5,z1);
        glEnd();
        aMashok-=5;
        bMashok+=5;
    }

    //COVER TANGGA DEPAN
    while(aCover>=-190 && yCover<-10){
       glBegin(GL_QUADS);
        glColor3f(89/255.f,89/255.f,89/255.f);
        glVertex3f(aCover,-50,z1);
        glVertex3f(bCover,-50,z1);
        glVertex3f(bCover,yCover,z1);
        glVertex3f(aCover,yCover,z1);
        glEnd();
        aCover-=5;
        bCover-=5;
        yCover+=5;
    }

    //COVER TANGGA BELAKANG
    while(aCover>=-190 && yCover<-10){
       glBegin(GL_QUADS);
        glColor3f(89/255.f,89/255.f,89/255.f);
        glVertex3f(aCover,-50,z2);
        glVertex3f(bCover,-50,z2);
        glVertex3f(bCover,yCover,z2);
        glVertex3f(aCover,yCover,z2);
        glEnd();
        aCover-=5;
        bCover-=5;
        yCover+=5;
    }
}

void tabung(float x, float y, float z, float scale_x, float scale_y, float scale_z, float color1, float color2, float color3, float alpha)
{
        glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(scale_x,scale_y,scale_z);

        glBegin( GL_TRIANGLE_FAN );
        glColor3f(0.85,0.85,0.85);
            //change y value here and in the vertex below to move the end up or
            // down to seal the top end of the cylinder
        glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,6.0f,0.0f);
        for(int i=0;i<=300;i++)
        {
            glVertex3f(2*cos(-i),6,2*sin(-i));
        }

        glEnd();
        // bottom end of cylinder
        glBegin( GL_TRIANGLE_FAN );
        glColor3f(0.85,0.85,0.85);
        glNormal3f(0.0f,-1.0f,0.0f);
            //change y value here and in the vertex below to move the end up or
            // down to seal the bottom end of the cylinder. Delete for a cone
        glVertex3f(0.0f,-0,0.0f);
        for(int i=0;i<=300;i++)
        {
            glVertex3f(2*cos(i),0,2*sin(i));
        }
        glEnd();

        //side of cylinder, y-values are used for the length of the cylinder
        //x and z values are used for the radius.
        // for a cone change y values to integers for the length.
        for(int j=0;j<=45;j++){

        glBegin(GL_QUAD_STRIP);
            for(int i=0;i<300;i++)
            {
                glNormal3f(2*cos(i), 0.0f, 2*sin(i));

        //  for a cone change the x and z values to 0 for a central cone or other integers for an offset cone
        // don't forget to delete the bottom end circle above.
                glColor4f(color1/255.f,color2/255.f,color3/255.f,alpha);
                glVertex3f(2*cos(i), (j)/7, 2*sin(i));
                glVertex3f(2*cos(i), (j+1)/7, 2*sin(i));
            }
        }
        glEnd();
        glPopMatrix();
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
        glVertex3f(350,-49.9,-80);
        glVertex3f(350,-49.9,75);
        glVertex3f(-280,-49.9,75);
    glEnd();

    // rumput
    glColor3f(15/255.f, 154/255.f, 3/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-280,-49.9,-140);
        glVertex3f(350,-49.9,-140);
        glVertex3f(350,-49.9,-80);
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

    //LANTAI 2 DEKET deva
    //LANTAI 2 1
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(210,-10,27);
        glVertex3f(210,-10,10);
        glVertex3f(160,-10,10);
        glVertex3f(160,-10,40);
    glEnd();

    //LANTAI 2 2
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(160,-10,40);
        glVertex3f(160,-10,10);
        glVertex3f(100,-10,30);
        glVertex3f(90,-10,30);
        glVertex3f(90,-10,50);
    glEnd();

    //LANTAI 2 3
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(90,-10,50);
        glVertex3f(90,-10,30);
        glVertex3f(10,-10,10);
        glVertex3f(10,-10,50);
    glEnd();

    //LANTAI 2 4
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(10,-10,50);
        glVertex3f(10,-10,10);
        glVertex3f(-100,-10,30);
        glVertex3f(-100,-10,55);
        glVertex3f(-50,-10,55);
        glVertex3f(-30,-10,50);
    glEnd();

    //LANTAI 2 5
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-100,-10,55);
        glVertex3f(-100,-10,30);
        glVertex3f(-160,-10,20);
        glVertex3f(-190,-10,20);
        glVertex3f(-190,-10,50);
    glEnd();

    //LANTAI 2 6
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-190,-10,50);
        glVertex3f(-190,-10,0);
        glVertex3f(-280,-10,0);
        glVertex3f(-280,-10,40);
    glEnd();

    //LANTAI 2 JAUH
    //LANTAI 2 7
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-280,-10,0);
        glVertex3f(-190,-10,0);
        glVertex3f(-190,-10,-60);
        glVertex3f(-280,-10,-60);
    glEnd();

    //LANTAI 2 8
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-190,-10,-20);
        glVertex3f(-140,-10,-20);
        glVertex3f(-90,-10,-30);
        glVertex3f(-50,-10,-30);
        glVertex3f(-50,-10,-50);
        glVertex3f(-130,-10,-60);
        glVertex3f(-190,-10,-60);
    glEnd();

    //LANTAI 2 9
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-50,-10,-30);
        glVertex3f(10,-10,-10);
        glVertex3f(90,-10,-30);
        glVertex3f(100,-10,-30);
        glVertex3f(120,-10,-25);
        glVertex3f(120,-10,-50);
        glVertex3f(-50,-10,-50);
    glEnd();

    //LANTAI 2 10
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(120,-10,-25);
        glVertex3f(170,-10,-10);
        glVertex3f(200,-10,-10);
        glVertex3f(200,-10,-30);
        glVertex3f(120,-10,-50);
    glEnd();

    //LANTAI 3 DEKET
    //LANTAI 3 1
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(210,30,27);
        glVertex3f(210,30,10);
        glVertex3f(160,30,10);
        glVertex3f(160,30,40);
    glEnd();

    //LANTAI 3 2
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(160,30,40);
        glVertex3f(160,30,10);
        glVertex3f(100,30,30);
        glVertex3f(90,30,30);
        glVertex3f(90,30,50);
    glEnd();

    //LANTAI 3 3
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(90,30,50);
        glVertex3f(90,30,30);
        glVertex3f(10,30,10);
        glVertex3f(10,30,50);
    glEnd();

    //LANTAI 3 4
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(10,30,50);
        glVertex3f(10,30,10);
        glVertex3f(-100,30,30);
        glVertex3f(-100,30,55);
        glVertex3f(-50,30,55);
        glVertex3f(-30,30,50);
    glEnd();

    //LANTAI 3 5
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-100,30,55);
        glVertex3f(-100,30,30);
        glVertex3f(-160,30,20);
        glVertex3f(-190,30,20);
        glVertex3f(-190,30,50);
    glEnd();

    //LANTAI 3 6
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-190,30,50);
        glVertex3f(-190,30,0);
        glVertex3f(-280,30,0);
        glVertex3f(-280,30,40);
    glEnd();

    //LANTAI 3 JAUH
    //LANTAI 3 7
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-280,30,0);
        glVertex3f(-190,30,0);
        glVertex3f(-190,30,-60);
        glVertex3f(-280,30,-60);
    glEnd();

    //LANTAI 3 8
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-190,30,-20);
        glVertex3f(-140,30,-20);
        glVertex3f(-90,30,-30);
        glVertex3f(-50,30,-30);
        glVertex3f(-50,30,-50);
        glVertex3f(-130,30,-60);
        glVertex3f(-190,30,-60);
    glEnd();

    //LANTAI 3 9
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-50,30,-30);
        glVertex3f(10,30,-10);
        glVertex3f(90,30,-30);
        glVertex3f(100,30,-30);
        glVertex3f(120,30,-25);
        glVertex3f(120,30,-50);
        glVertex3f(-50,30,-50);
    glEnd();

    //LANTAI 3 10
    glColor3f(255/255.f,251/255.f,231/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(120,30,-25);
        glVertex3f(170,30,-10);
        glVertex3f(200,30,-10);
        glVertex3f(200,30,-30);
        glVertex3f(120,30,-50);
    glEnd();

    // jalan raya
    glColor3f(100/255.f, 100/255.f, 100/255.f);
    glBegin(GL_QUADS);
        glVertex3d(-350,-49.9,75);
        glVertex3d(350,-49.9,75);
        glVertex3d(350,-49.9,150);
        glVertex3d(-350,-49.9,150);
    glEnd();
    // bahu jalan
    glColor3f(210/255.f,210/255.f,210/255.f);
    glBegin(GL_QUADS);
        glVertex3d(-350,-45,105);
        glVertex3d(350,-45,105);
        glVertex3d(350,-45,120);
        glVertex3d(-350,-45,120);
    glEnd();
    glColor3f(58/255.f,58/255.f,58/255.f);
    glBegin(GL_QUADS);
        glVertex3d(-350,-49.9,120);
        glVertex3d(350,-49.9,120);
        glVertex3d(350,-45,120);
        glVertex3d(-350,-45,120);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(-350,-49.9,105);
        glVertex3d(350,-49.9,105);
        glVertex3d(350,-45,105);
        glVertex3d(-350,-45,105);
    glEnd();
    glColor3f(0.95,0.95,0.95);
    for(int i=0; i<70; i++){
        glBegin(GL_QUADS);
            glVertex3d(-350+(i*10),-49.9,120.1);
            glVertex3d(-345+(i*10),-49.9,120.1);
            glVertex3d(-345+(i*10),-45,120.1);
            glVertex3d(-350+(i*10),-45,120.1);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3d(-350+(i*10),-49.9,104.9);
            glVertex3d(-345+(i*10),-49.9,104.9);
            glVertex3d(-345+(i*10),-45,104.9);
            glVertex3d(-350+(i*10),-45,104.9);
        glEnd();
    }
    glColor3f(1,1,1);
    for(int i=0; i<35; i++){
        glBegin(GL_QUADS);
            glVertex3d(-350+(i*20),-49.8,135.5);
            glVertex3d(-340+(i*20),-49.8,135.5);
            glVertex3d(-340+(i*20),-49.8,134.5);
            glVertex3d(-350+(i*20),-49.8,134.5);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3d(-350+(i*20),-49.8,90.5);
            glVertex3d(-340+(i*20),-49.8,90.5);
            glVertex3d(-340+(i*20),-49.8,89.5);
            glVertex3d(-350+(i*20),-49.8,89.5);
        glEnd();
    }

    // PARKIRAN
    glColor3f(100/255.f, 100/255.f, 100/255.f);
    glBegin(GL_QUADS);
        glVertex3f(-350,-49.9,-140);
        glVertex3f(-280,-49.9,-140);
        glVertex3f(-280,-49.9,75);
        glVertex3f(-350,-49.9,75);
    glEnd();
    // GARIS PUTIH
    glColor3f(1,1,1);
    for(int i=0; i<2; i++){
        glBegin(GL_QUADS); // kanan dan kiri
            glVertex3f(-349+(i*67),-49.8,-139);
            glVertex3f(-348+(i*67),-49.8,-139);
            glVertex3f(-348+(i*67),-49.8,41);
            glVertex3f(-349+(i*67),-49.8,41);
        glEnd();
    }
    glBegin(GL_QUADS); // belakang
        glVertex3f(-348,-49.8,-139);
        glVertex3f(-282,-49.8,-139);
        glVertex3f(-282,-49.8,-138);
        glVertex3f(-348,-49.8,-138);
    glEnd();
    glBegin(GL_QUADS); // depan
        glVertex3f(-348,-49.8,40);
        glVertex3f(-302,-49.8,40);
        glVertex3f(-302,-49.8,41);
        glVertex3f(-348,-49.8,41);
    glEnd();
    int jarak_parkir=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<11; j++){
            glBegin(GL_QUADS); // garis parkir
                glVertex3f(-348+(i*26),-49.8,-124+jarak_parkir);
                glVertex3f(-333+(i*26),-49.8,-124+jarak_parkir);
                glVertex3f(-333+(i*26),-49.8,-123+jarak_parkir);
                glVertex3f(-348+(i*26   ),-49.8,-123+jarak_parkir);
            glEnd();
            jarak_parkir+=14;
        }
        jarak_parkir=0;
    }

    // trotoar
    glColor3f(229/255.f, 148/255.f, 148/255.f);
    glBegin(GL_POLYGON);
        glVertex3f(-350,-49.8,42);
        glVertex3f(-302,-49.8,42);
        glVertex3f(-302,-49.8,75);
        glVertex3f(-350,-49.8,75);
    glEnd();

    // kartu masuk
    glColor3f(0/255.f, 99/255.f, 215/255.f);
    glBegin(GL_POLYGON); // atas
        glVertex3f(-285,-30,42);
        glVertex3f(-280,-30,42);
        glVertex3f(-280,-30,52);
        glVertex3f(-285,-30,52);
    glEnd();
    glColor3f(2/255.f, 97/255.f, 209/255.f);
    glBegin(GL_POLYGON); // depan
        glVertex3f(-285,-49.8,52);
        glVertex3f(-280,-49.8,52);
        glVertex3f(-280,-30,52);
        glVertex3f(-285,-30,52);
    glEnd();
    glBegin(GL_POLYGON); // belakang
        glVertex3f(-285,-49.8,42);
        glVertex3f(-280,-49.8,42);
        glVertex3f(-280,-30,42);
        glVertex3f(-285,-30,42);
    glEnd();
    glColor3f(1/255.f, 90/255.f, 195/255.f);
    glBegin(GL_POLYGON); // kanan
        glVertex3f(-280,-49.8,42);
        glVertex3f(-280,-49.8,52);
        glVertex3f(-280,-30,52);
        glVertex3f(-280,-30,42);
    glEnd();
    glBegin(GL_POLYGON); // kiri
        glVertex3f(-285,-49.8,42);
        glVertex3f(-285,-49.8,52);
        glVertex3f(-285,-30,52);
        glVertex3f(-285,-30,42);
    glEnd();

    //ESKALATOR
    eskalator(-150,-145,-50,-155,-150,-50,-150,-50,-155,-160,-45,15,0);
    eskalator(-150,-145,-50,-155,-150,-50,-150,-50,-155,-160,-45,-10,-25);

    //PINTU KIRI
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-200,-25,75);
    glVertex3f(-180,-25,75);
    glVertex3f(-180,-20,75);
    glVertex3f(-200,-20,75);
    glEnd();

    for(int i= -200;i< -180;i+=10)
    {
        for(int j= -50;j<-25;j+=25)
        {
            int x = i+10;
            int y = j+25;
            int z = 70;
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
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-200,-20,55);
    glVertex3f(-180,-20,55);
    glVertex3f(-180,-20,75);
    glVertex3f(-200,-20,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-200,-25,70);
    glVertex3f(-180,-25,70);
    glVertex3f(-180,-25,75);
    glVertex3f(-200,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-200,-25,55);
    glVertex3f(-200,-20,55);
    glVertex3f(-200,-20,75);
    glVertex3f(-200,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-180,-25,55);
    glVertex3f(-180,-20,55);
    glVertex3f(-180,-20,75);
    glVertex3f(-180,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-180,-25,55);
    glVertex3f(-180,-50,55);
    glVertex3f(-180,-50,70);
    glVertex3f(-180,-25,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-180,-25,55);
    glVertex3f(-180,-50,55);
    glVertex3f(-180,-50,70);
    glVertex3f(-180,-25,70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-200,-25,55);
    glVertex3f(-200,-50,55);
    glVertex3f(-200,-50,70);
    glVertex3f(-200,-25,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-200,-25,55);
    glVertex3f(-200,-50,55);
    glVertex3f(-200,-50,70);
    glVertex3f(-200,-25,70);
    glEnd();

    //PINTU KANAN
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,75);
    glVertex3f(-30,-25,75);
    glVertex3f(-30,-20,75);
    glVertex3f(-50,-20,75);
    glEnd();

    for(int i= -50;i< -30;i+=10)
    {
        for(int j= -50;j<-25;j+=25)
        {
            int x = i+10;
            int y = j+25;
            int z = 70;
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
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-20,55);
    glVertex3f(-30,-20,55);
    glVertex3f(-30,-20,75);
    glVertex3f(-50,-20,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,70);
    glVertex3f(-30,-25,70);
    glVertex3f(-30,-25,75);
    glVertex3f(-50,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,55);
    glVertex3f(-50,-20,55);
    glVertex3f(-50,-20,75);
    glVertex3f(-50,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-30,-25,55);
    glVertex3f(-30,-20,55);
    glVertex3f(-30,-20,75);
    glVertex3f(-30,-25,75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-30,-25,55);
    glVertex3f(-30,-50,55);
    glVertex3f(-30,-50,70);
    glVertex3f(-30,-25,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-30,-25,55);
    glVertex3f(-30,-50,55);
    glVertex3f(-30,-50,70);
    glVertex3f(-30,-25,70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-50,-25,55);
    glVertex3f(-50,-50,55);
    glVertex3f(-50,-50,70);
    glVertex3f(-50,-25,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-50,-25,55);
    glVertex3f(-50,-50,55);
    glVertex3f(-50,-50,70);
    glVertex3f(-50,-25,70);
    glEnd();

    //PINTU KANAN KOLAM
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-190,-25,-80);
    glVertex3f(-170,-25,-80);
    glVertex3f(-170,-20,-80);
    glVertex3f(-190,-20,-80);
    glEnd();

    for(int i= -190;i< -170;i+=10)
    {
        for(int j= -50;j<-25;j+=25)
        {
            int x = i+10;
            int y = j+25;
            int z = -75;
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
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-190,-20,-60);
    glVertex3f(-170,-20,-60);
    glVertex3f(-170,-20,-80);
    glVertex3f(-190,-20,-80);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-190,-25,-75);
    glVertex3f(-170,-25,-75);
    glVertex3f(-170,-25,-80);
    glVertex3f(-190,-25,-80);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-190,-25,-60);
    glVertex3f(-190,-20,-60);
    glVertex3f(-190,-20,-80);
    glVertex3f(-190,-25,-80);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-170,-25,-60);
    glVertex3f(-170,-20,-60);
    glVertex3f(-170,-20,-80);
    glVertex3f(-170,-25,-80);
    glEnd();

    // IMAX
    glPushMatrix();
        glColor3f(0.8,0.8,0.8);
        glTranslated(300,-10,-20);
        glutSolidSphere(55,20,20);
    glPopMatrix();

    // AQUARIUM
    glColor4f(36/255.f,117/255.f,182/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-50,-50,-10);
        glVertex3f(-40,-50,-4);
        glVertex3f(-40,70,-4);
        glVertex3f(-50,70,-10);
    glEnd();
    glColor4f(19/255.f,107/255.f,165/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-40,-50,-4);
        glVertex3f(-40,-50,4);
        glVertex3f(-40,70,4);
        glVertex3f(-40,70,-4);
    glEnd();
    glColor4f(36/255.f,117/255.f,182/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-50,-50,10);
        glVertex3f(-40,-50,4);
        glVertex3f(-40,70,4);
        glVertex3f(-50,70,10);
    glEnd();
    glColor4f(19/255.f,107/255.f,165/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-50,-50,10);
        glVertex3f(-60,-50,4);
        glVertex3f(-60,70,4);
        glVertex3f(-50,70,10);
    glEnd();
    glColor4f(36/255.f,117/255.f,182/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-60,-50,-4);
        glVertex3f(-60,-50,4);
        glVertex3f(-60,70,4);
        glVertex3f(-60,70,-4);
    glEnd();
    glColor4f(19/255.f,107/255.f,165/255.f,0.4);
    glBegin(GL_QUADS);
        glVertex3f(-50,-50,-10);
        glVertex3f(-60,-50,-4);
        glVertex3f(-60,70,-4);
        glVertex3f(-50,70,-10);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-170,-25,-60);
    glVertex3f(-170,-50,-60);
    glVertex3f(-170,-50,-75);
    glVertex3f(-170,-25,-75);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-170,-25,-60);
    glVertex3f(-170,-50,-60);
    glVertex3f(-170,-50,-75);
    glVertex3f(-170,-25,-75);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-190,-25,-60);
    glVertex3f(-190,-50,-60);
    glVertex3f(-190,-50,-75);
    glVertex3f(-190,-25,-75);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-190,-25,-60);
    glVertex3f(-190,-50,-60);
    glVertex3f(-190,-50,-75);
    glVertex3f(-190,-25,-75);
    glEnd();

    //PINTU KIRI KOLAM
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,-70);
    glVertex3f(-30,-25,-70);
    glVertex3f(-30,-20,-70);
    glVertex3f(-50,-20,-70);
    glEnd();

    for(int i= -50;i< -30;i+=10)
    {
        for(int j= -50;j<-25;j+=25)
        {
            int x = i+10;
            int y = j+25;
            int z = -65;
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
    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-20,-50);
    glVertex3f(-30,-20,-50);
    glVertex3f(-30,-20,-70);
    glVertex3f(-50,-20,-70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,-65);
    glVertex3f(-30,-25,-65);
    glVertex3f(-30,-25,-70);
    glVertex3f(-50,-25,-70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-50,-25,-50);
    glVertex3f(-50,-20,-50);
    glVertex3f(-50,-20,-70);
    glVertex3f(-50,-25,-70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(163/255.f,23/255.f,23/255.f,1);
    glVertex3f(-30,-25,-50);
    glVertex3f(-30,-20,-50);
    glVertex3f(-30,-20,-70);
    glVertex3f(-30,-25,-70);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-30,-25,-50);
    glVertex3f(-30,-50,-50);
    glVertex3f(-30,-50,-65);
    glVertex3f(-30,-25,-65);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-30,-25,-50);
    glVertex3f(-30,-50,-50);
    glVertex3f(-30,-50,-65);
    glVertex3f(-30,-25,-65);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(255/255.f,251/255.f,231/255.f,0.5);
    glVertex3f(-50,-25,-50);
    glVertex3f(-50,-50,-50);
    glVertex3f(-50,-50,-65);
    glVertex3f(-50,-25,-65);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor4f(0/255.f,0/255.f,0/255.f,0.1);
    glVertex3f(-50,-25,-50);
    glVertex3f(-50,-50,-50);
    glVertex3f(-50,-50,-65);
    glVertex3f(-50,-25,-65);
    glEnd();

    tabung(210, -50, -2.5, 7, 19.9, 7, 82, 194, 212, 0.25);
    //dinding
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(220,-49.9,25);
    glVertex3f(220,-49.9,7.5);
    glVertex3f(220,69.9,7.5);
    glVertex3f(220,69.9,25);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(220,-49.9,-30);
    glVertex3f(220,-49.9,-12.5);
    glVertex3f(220,69.9,-12.5);
    glVertex3f(220,69.9,-30);
    glEnd();

    // ATAP KIRI ATAS
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-140,80,-15);
        glVertex3f(-100,80,-25);
        glVertex3f(-100,80,-15);
        glVertex3f(-140,80,-5);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(-140,70,-5);
        glVertex3f(-140,70,-15);
        glVertex3f(-140,80,-15);
        glVertex3f(-140,80,-5);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(-100,70,-15);
        glVertex3f(-100,70,-25);
        glVertex3f(-100,80,-25);
        glVertex3f(-100,80,-15);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(-140,70,-15);
        glVertex3f(-100,70,-25);
        glVertex3f(-100,80,-25);
        glVertex3f(-140,80,-15);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(-140,70,-5);
        glVertex3f(-100,70,-15);
        glVertex3f(-100,80,-15);
        glVertex3f(-140,80,-5);
    glEnd();

    // ATAP KIRI BAWAH
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(-140,80,15);
        glVertex3f(-100,80,25);
        glVertex3f(-100,80,15);
        glVertex3f(-140,80,5);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(-140,70,5);
        glVertex3f(-140,70,15);
        glVertex3f(-140,80,15);
        glVertex3f(-140,80,5);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(-100,70,15);
        glVertex3f(-100,70,25);
        glVertex3f(-100,80,25);
        glVertex3f(-100,80,15);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(-140,70,15);
        glVertex3f(-100,70,25);
        glVertex3f(-100,80,25);
        glVertex3f(-140,80,15);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(-140,70,5);
        glVertex3f(-100,70,15);
        glVertex3f(-100,80,15);
        glVertex3f(-140,80,5);
    glEnd();

    // ATAP TENGAH
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex3d(-70,80,-25);
        glVertex3d(-30,80,-20);
        glVertex3d(-10,80,-10);
        glVertex3d(0,80,0);
        glVertex3d(-10,80,10);
        glVertex3d(-30,80,20);
        glVertex3d(-70,80,25);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(-70,70,-25);
        glVertex3f(-70,70,25);
        glVertex3f(-70,80,25);
        glVertex3f(-70,80,-25);
    glEnd(); //depan 1
    glBegin(GL_QUADS);
        glVertex3f(-70,70,25);
        glVertex3f(-30,70,20);
        glVertex3f(-30,80,20);
        glVertex3f(-70,80,25);
    glEnd(); //depan 2
    glBegin(GL_QUADS);
        glVertex3f(-30,70,20);
        glVertex3f(-10,70,10);
        glVertex3f(-10,80,10);
        glVertex3f(-30,80,20);
    glEnd(); //depan 3
    glBegin(GL_QUADS);
        glVertex3f(-10,70,10);
        glVertex3f(0,70,0);
        glVertex3f(0,80,0);
        glVertex3f(-10,80,10);
    glEnd(); //belakang 1
    glBegin(GL_QUADS);
        glVertex3f(-70,70,-25);
        glVertex3f(-30,70,-20);
        glVertex3f(-30,80,-20);
        glVertex3f(-70,80,-25);
    glEnd(); //belakang 2
    glBegin(GL_QUADS);
        glVertex3f(-30,70,-20);
        glVertex3f(-10,70,-10);
        glVertex3f(-10,80,-10);
        glVertex3f(-30,80,-20);
    glEnd(); //belakang 3
    glBegin(GL_QUADS);
        glVertex3f(-10,70,-10);
        glVertex3f(0,70,0);
        glVertex3f(0,80,0);
        glVertex3f(-10,80,-10);
    glEnd();

    // ATAP KANAN (ATAS KIRI)
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(40,80,-3);
        glVertex3f(80,80,-13);
        glVertex3f(80,80,-20);
        glVertex3f(40,80,-10);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(40,70,-3);
        glVertex3f(40,70,-10);
        glVertex3f(40,80,-10);
        glVertex3f(40,80,-3);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(80,70,-13);
        glVertex3f(80,70,-20);
        glVertex3f(80,80,-20);
        glVertex3f(80,80,-13);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(40,70,-3);
        glVertex3f(80,70,-13);
        glVertex3f(80,80,-13);
        glVertex3f(40,80,-3);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(40,70,-10);
        glVertex3f(80,70,-20);
        glVertex3f(80,80,-20);
        glVertex3f(40,80,-10);
    glEnd();

    // ATAP KANAN (BAWAH KIRI)
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(40,80,3);
        glVertex3f(80,80,13);
        glVertex3f(80,80,20);
        glVertex3f(40,80,10);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(40,70,3);
        glVertex3f(40,70,10);
        glVertex3f(40,80,10);
        glVertex3f(40,80,3);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(80,70,13);
        glVertex3f(80,70,20);
        glVertex3f(80,80,20);
        glVertex3f(80,80,13);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(40,70,3);
        glVertex3f(80,70,13);
        glVertex3f(80,80,13);
        glVertex3f(40,80,3);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(40,70,10);
        glVertex3f(80,70,20);
        glVertex3f(80,80,20);
        glVertex3f(40,80,10);
    glEnd();

    // ATAP KANAN (ATAS KANAN)
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(110,80,20);
        glVertex3f(150,80,10);
        glVertex3f(150,80,3);
        glVertex3f(110,80,13);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(110,70,13);
        glVertex3f(110,70,20);
        glVertex3f(110,80,20);
        glVertex3f(110,80,13);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(150,70,3);
        glVertex3f(150,70,10);
        glVertex3f(150,80,10);
        glVertex3f(150,80,3);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(110,70,13);
        glVertex3f(150,70,3);
        glVertex3f(150,80,3);
        glVertex3f(110,80,13);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(110,70,20);
        glVertex3f(150,70,10);
        glVertex3f(150,80,10);
        glVertex3f(110,80,20);
    glEnd();

    // ATAP KANAN (BAWAH KANAN)
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex3f(110,80,-20);
        glVertex3f(150,80,-10);
        glVertex3f(150,80,-3);
        glVertex3f(110,80,-13);
    glEnd(); // kiri
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(110,70,-13);
        glVertex3f(110,70,-20);
        glVertex3f(110,80,-20);
        glVertex3f(110,80,-13);
    glEnd(); // kanan
    glBegin(GL_QUADS);
        glVertex3f(150,70,-3);
        glVertex3f(150,70,-10);
        glVertex3f(150,80,-10);
        glVertex3f(150,80,-3);
    glEnd(); //depan
    glBegin(GL_QUADS);
        glVertex3f(110,70,-13);
        glVertex3f(150,70,-3);
        glVertex3f(150,80,-3);
        glVertex3f(110,80,-13);
    glEnd(); //belakang
    glBegin(GL_QUADS);
        glVertex3f(110,70,-20);
        glVertex3f(150,70,-10);
        glVertex3f(150,80,-10);
        glVertex3f(110,80,-20);
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

