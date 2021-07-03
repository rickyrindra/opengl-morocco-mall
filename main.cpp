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

