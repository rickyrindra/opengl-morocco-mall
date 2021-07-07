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

// variabel untuk animasi
float y_pos = 0.0f;
float x_pos = 0.0f;
float x_awan = 0.0f;
float x_pintu_kanan = 0.0f;
float x_pintu_kiri = 0.0f;

// delta : perubahan per frame
float delta = 0.5f;
float delta_pintu = 0.2f;
float delta_mobil = 3.0f;
float delta_awan = 1.5f;

bool is_naik = true;
bool is_kiri = true;
bool is_kanan = true;
bool is_pintu_buka = true;

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/30,timer,0);

    // lift
    if(y_pos < 80 && is_naik) y_pos +=delta;
    else is_naik = false;

    if (y_pos > 0 && !is_naik) y_pos-=delta;
    else is_naik = true;

    // mobil
    if (x_pos > -550 && is_kiri) x_pos-=delta_mobil;
    else is_kiri = false;

    if (!is_kiri) x_pos=0.0f; is_kiri=true;

    // awan
    if(x_awan < 160 && is_kanan) x_awan+=delta_awan;
    else is_kanan = false;

    if(x_awan > -160 && !is_kanan) x_awan-=delta_awan;
    else is_kanan=true;

    // pintu kanan
    if(x_pintu_kanan < 10 && is_pintu_buka) x_pintu_kanan +=delta_pintu;
    else is_pintu_buka = false;

    if (x_pintu_kanan > 0 && !is_pintu_buka) x_pintu_kanan-=delta_pintu;
    else is_pintu_buka = true;

    // pintu kiri
    if(x_pintu_kiri > -10 && is_pintu_buka) x_pintu_kiri -=delta_pintu;
    else is_pintu_buka = false;

    if (x_pintu_kiri < 0 && !is_pintu_buka) x_pintu_kiri+=delta_pintu;
    else is_pintu_buka = true;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(250,80);
    glutCreateWindow("MOROCCO MALL");
    init();

    // animasi
    glutTimerFunc(0,timer,0);

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

    glLineWidth(6.0);

    glMatrixMode(GL_MODELVIEW);
}

void awan(float x1,float x2, float y1, float y2, float z){
    float batas = x1+20;
    for(float i = x1; i<=batas;i+=10){
        glPushMatrix();
            glColor3f(1.0,1.0,1.0);
            glTranslated(i,y1,z);
            glutSolidSphere(10,20,20);
        glPopMatrix();
    }
    glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslated(x2,y2,z);
        glutSolidSphere(10,20,20);
    glPopMatrix();
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

void lingkaran(float x, float y,float z,float r){
    float theta;
    for(int i = 0; i < 360; i++){
        theta = i* 3.14285714/180;
        glVertex3f(x+r*cos(theta), y+r*sin(theta),z);
    }
}

void mobil(float x1, float x2){
            //MOBIL
            //BODY SAMPING DEKET
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1,-43,133);
                glVertex3f(x2,-43,133);
                glVertex3f(x2,-33,133);
                glVertex3f(x1,-33,133);
            glEnd();

            //BODY SAMPING JAUH
            glColor3f(134/255.f,3/255.f,3/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1,-43,123);
                glVertex3f(x2,-43,123);
                glVertex3f(x2,-33,123);
                glVertex3f(x1,-33,123);
            glEnd();

            //BODY DEPAN
            glColor3f(186/255.f,14/255.f,14/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1,-33,133);
                glVertex3f(x1,-43,133);
                glVertex3f(x1,-43,123);
                glVertex3f(x1,-33,123);
            glEnd();

            //BODY BELAKANG
            glColor3f(186/255.f,14/255.f,14/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x2,-33,133);
                glVertex3f(x2,-43,133);
                glVertex3f(x2,-43,123);
                glVertex3f(x2,-33,123);
            glEnd();

            //BODY ATAS
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1+15.0,-23,133);
                glVertex3f(x2-8.0,-23,133);
                glVertex3f(x2-8.0,-23,123);
                glVertex3f(x1+15.0,-23,123);
            glEnd();

            //KAP MOBIL DEPAN
            glColor3f(186/255.f,14/255.f,14/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1,-33,133);
                glVertex3f(x1+7,-33,133);
                glVertex3f(x1+7,-33,123);
                glVertex3f(x1,-33,123);
            glEnd();

            //BODY KACA DEPAN
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1+7,-33,133);
                glVertex3f(x1+15,-23,133);
                glVertex3f(x1+15,-23,123);
                glVertex3f(x1+7,-33,123);
            glEnd();

            //KACA BELAKANG
            glBegin(GL_QUADS);
            glColor3f(134/255.f,232/255.f,238/255.f);
                glVertex3f(x2-8,-23,133);
                glVertex3f(x2-8,-23,123);
                glColor3f(255/255.f,255/255.f,255/255.f);
                glVertex3f(x2,-33,123);
                glVertex3f(x2,-33,133);


            glEnd();

            //BODY KACA SAMPING DEKET
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1+7,-33,133);
                glVertex3f(x2,-33,133);
                glVertex3f(x2-8,-23,133);
                glVertex3f(x1+15,-23,133);
            glEnd();

            //BODY KACA SAMPING JAUH
            glColor3f(134/255.f,3/255.f,3/255.f);
            glBegin(GL_QUADS);
                glVertex3f(x1+7,-33,123);
                glVertex3f(x2,-33,123);
                glVertex3f(x2-8,-23,123);
                glVertex3f(x1+15,-23,123);
            glEnd();

            //KACA DEPAN
            glBegin(GL_QUADS);
                glColor3f(134/255.f,232/255.f,238/255.f);
                glVertex3f(x1+14,-24,132.5);
                glVertex3f(x1+14,-24,123.5);
                glColor3f(255/255.f,255/255.f,255/255.f);
                glVertex3f(x1+7.5,-32,123.5);
                glVertex3f(x1+7.5,-32,132.5);
            glEnd();

            //KACA SAMPING DEKET
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glColor3f(255/255.f,255/255.f,255/255.f);
                glVertex3f(x1+8,-32.5,133.1);
                glVertex3f(x2-1,-32.5,133.1);
                glColor3f(134/255.f,232/255.f,238/255.f);
                glVertex3f(x2-9,-23.5,133.1);
                glVertex3f(x1+16,-23.5,133.1);
            glEnd();

            //KACA SAMPING JAUH
            glColor3f(232/255.f,21/255.f,21/255.f);
            glBegin(GL_QUADS);
                glColor3f(255/255.f,255/255.f,255/255.f);
                glVertex3f(x1+8,-32.5,122.9);
                glVertex3f(x2-1,-32.5,122.9);
                glColor3f(134/255.f,232/255.f,238/255.f);
                glVertex3f(x2-9,-23.5,122.9);
                glVertex3f(x1+16,-23.5,122.9);
            glEnd();

            //BAN DEPAN DEKET
            glColor3f(14/255.f,13/255.f,13/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x1+8,-44,133.1,5);
            glEnd();

            //BAN BELAKANG DEKET
            glColor3f(14/255.f,13/255.f,13/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x2-8,-44,133.1,5);
            glEnd();

            //BAN DEPAN JAUH
            glColor3f(14/255.f,13/255.f,13/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x1+8,-44,122.9,5);
            glEnd();

            //BAN BELAKANG JAUH
            glColor3f(14/255.f,13/255.f,13/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x2-8,-44,122.9,5);
            glEnd();

            //BAN KECIL DEPAN DEKET
            glColor3f(134/255.f,125/255.f,125/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x1+8,-44,133.2,3);
            glEnd();

            //BAN KECIL BELAKANG DEKET
            glColor3f(134/255.f,125/255.f,125/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x2-8,-44,133.2,3);
            glEnd();

            //BAN KECIL DEPAN JAUH
            glColor3f(134/255.f,125/255.f,125/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x1+8,-44,122.8,3);
            glEnd();

            //BAN KECIL BELAKANG JAUH
            glColor3f(134/255.f,125/255.f,125/255.f);
            glBegin(GL_POLYGON);
                lingkaran(x2-8,-44,122.8,3);
            glEnd();
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

void lift(){
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            // list lift
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_QUADS); // depan kiri
                glVertex3f(90-(i*20),-49.7,-19.9+(j*50));
                glVertex3f(91-(i*20),-49.7,-19.9+(j*50));
                glVertex3f(91-(i*20),-20,-19.9+(j*50));
                glVertex3f(90-(i*20),-20,-19.9+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang kiri
                glVertex3f(90-(i*20),-49.7,-30.1+(j*50));
                glVertex3f(91-(i*20),-49.7,-30.1+(j*50));
                glVertex3f(91-(i*20),-20,-30.1+(j*50));
                glVertex3f(90-(i*20),-20,-30.1+(j*50));
            glEnd();
            glBegin(GL_QUADS); // depan kanan
                glVertex3f(99-(i*20),-49.7,-19.9+(j*50));
                glVertex3f(100-(i*20),-49.7,-19.9+(j*50));
                glVertex3f(100-(i*20),-20,-19.9+(j*50));
                glVertex3f(99-(i*20),-20,-19.9+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang kanan
                glVertex3f(99-(i*20),-49.7,-30.1+(j*50));
                glVertex3f(100-(i*20),-49.7,-30.1+(j*50));
                glVertex3f(100-(i*20),-20,-30.1+(j*50));
                glVertex3f(99-(i*20),-20,-30.1+(j*50));
            glEnd();

            // LIFT
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_QUADS); // alas
                glVertex3f(90-(i*20),-49.7,-30+(j*50));
                glVertex3f(100-(i*20),-49.7,-30+(j*50));
                glVertex3f(100-(i*20),-49.7,-20+(j*50));
                glVertex3f(90-(i*20),-49.7,-20+(j*50));
            glEnd();
            glBegin(GL_QUADS); // atap
                glVertex3f(90-(i*20),-20,-30+(j*50));
                glVertex3f(100-(i*20),-20,-30+(j*50));
                glVertex3f(100-(i*20),-20,-20+(j*50));
                glVertex3f(90-(i*20),-20,-20+(j*50));
            glEnd();
            glColor4f(0.7,0.7,0.7,0.4);
            glBegin(GL_QUADS); // depan
                glVertex3f(90-(i*20),-49.7,-20+(j*50));
                glVertex3f(100-(i*20),-49.7,-20+(j*50));
                glVertex3f(100-(i*20),-20,-20+(j*50));
                glVertex3f(90-(i*20),-20,-20+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang
                glVertex3f(90-(i*20),-49.7,-30+(j*50));
                glVertex3f(100-(i*20),-49.7,-30+(j*50));
                glVertex3f(100-(i*20),-20,-30+(j*50));
                glVertex3f(90-(i*20),-20,-30+(j*50));
            glEnd();
            glBegin(GL_QUADS); // kiri
                glVertex3f(90-(i*20),-49.7,-30+(j*50));
                glVertex3f(90-(i*20),-49.7,-20+(j*50));
                glVertex3f(90-(i*20),-20,-20+(j*50));
                glVertex3f(90-(i*20),-20,-30+(j*50));
            glEnd();
            glBegin(GL_QUADS); // kanan
                glVertex3f(100-(i*20),-49.7,-30+(j*50));
                glVertex3f(100-(i*20),-49.7,-20+(j*50));
                glVertex3f(100-(i*20),-20,-20+(j*50));
                glVertex3f(100-(i*20),-20,-30+(j*50));
            glEnd();

        }
    }

}

void luar_lift(){
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            // list luar lift
            glColor3f(0.5,0.5,0.5);
            glBegin(GL_QUADS); // depan kiri
                glVertex3f(88-(i*20),-49.7,-17.9+(j*50));
                glVertex3f(89-(i*20),-49.7,-17.9+(j*50));
                glVertex3f(89-(i*20),61,-17.9+(j*50));
                glVertex3f(88-(i*20),61,-17.9+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang kiri
                glVertex3f(88-(i*20),-49.7,-32.1+(j*50));
                glVertex3f(89-(i*20),-49.7,-32.1+(j*50));
                glVertex3f(89-(i*20),61,-32.1+(j*50));
                glVertex3f(88-(i*20),61,-32.1+(j*50));
            glEnd();
            glBegin(GL_QUADS); // depan kanan
                glVertex3f(101-(i*20),-49.7,-17.9+(j*50));
                glVertex3f(102-(i*20),-49.7,-17.9+(j*50));
                glVertex3f(102-(i*20),61,-17.9+(j*50));
                glVertex3f(101-(i*20),61,-17.9+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang kanan
                glVertex3f(101-(i*20),-49.7,-32.1+(j*50));
                glVertex3f(102-(i*20),-49.7,-32.1+(j*50));
                glVertex3f(102-(i*20),61,-32.1+(j*50));
                glVertex3f(101-(i*20),61,-32.1+(j*50));
            glEnd();

            // LUAR LIFT
            glColor3f(0.45,0.45,0.45);
            glBegin(GL_QUADS); // atap
                glVertex3f(88-(i*20),61,-32+(j*50));
                glVertex3f(102-(i*20),61,-32+(j*50));
                glVertex3f(102-(i*20),61,-18+(j*50));
                glVertex3f(88-(i*20),61,-18+(j*50));
            glEnd();
            glBegin(GL_QUADS); // alas
                glVertex3f(88-(i*20),-49.7,-32+(j*50));
                glVertex3f(102-(i*20),-49.7,-32+(j*50));
                glVertex3f(102-(i*20),-49.7,-18+(j*50));
                glVertex3f(88-(i*20),-49.7,-18+(j*50));
            glEnd();
            glColor4f(215/255.f, 255/255.f, 253/255.f, 0.2);
            glBegin(GL_QUADS); // depan
                glVertex3f(88-(i*20),-49.7,-18+(j*50));
                glVertex3f(102-(i*20),-49.7,-18+(j*50));
                glVertex3f(102-(i*20),61,-18+(j*50));
                glVertex3f(88-(i*20),61,-18+(j*50));
            glEnd();
            glBegin(GL_QUADS); // belakang
                glVertex3f(88-(i*20),-49.7,-32+(j*50));
                glVertex3f(102-(i*20),-49.7,-32+(j*50));
                glVertex3f(102-(i*20),61,-32+(j*50));
                glVertex3f(88-(i*20),61,-32+(j*50));
            glEnd();
            glBegin(GL_QUADS); // kiri
                glVertex3f(88-(i*20),-49.7,-32+(j*50));
                glVertex3f(88-(i*20),-49.7,-18+(j*50));
                glVertex3f(88-(i*20),61,-18+(j*50));
                glVertex3f(88-(i*20),61,-32+(j*50));
            glEnd();
            glBegin(GL_QUADS); // kanan
                glVertex3f(102-(i*20),-49.7,-32+(j*50));
                glVertex3f(102-(i*20),-49.7,-18+(j*50));
                glVertex3f(102-(i*20),61,-18+(j*50));
                glVertex3f(102-(i*20),61,-32+(j*50));
            glEnd();
        }
    }
}

void bangkuDepan(float x1, float x2,float z1, float z2){
    //SISI KANAN LUAR
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z1);
    glVertex3f(x1,-50,z2);
    glVertex3f(x1,-40,z2);
    glVertex3f(x1,-40,z1);
    glEnd();
    //SISI KANAN DALAM
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1-2,-50,z1);
    glVertex3f(x1-2,-50,z2);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1-2,-40,z1);
    glEnd();
    //SISI KANAN HADEP DEPAN
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z1);
    glVertex3f(x1-2,-50,z1);
    glVertex3f(x1-2,-40,z1);
    glVertex3f(x1,-40,z1);
    glEnd();
    //SISI KANAN HADEP BELAKANG
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z2);
    glVertex3f(x1-2,-50,z2);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1,-40,z2);
    glEnd();
    //SISI KANAN HADEP ATAS
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-40,z1);
    glVertex3f(x1-2,-40,z1);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1,-40,z2);
    glEnd();

    //SISI KIRI DALEM
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z1);
    glVertex3f(x2+2,-50,z2);
    glVertex3f(x2+2,-40,z2);
    glVertex3f(x2+2,-40,z1);
    glEnd();
    //SISI KIRI LUAR
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2,-50,z1);
    glVertex3f(x2,-50,z2);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2,-40,z1);
    glEnd();
    //SISI KIRI HADEP DEPAN
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z1);
    glVertex3f(x2,-50,z1);
    glVertex3f(x2,-40,z1);
    glVertex3f(x2+2,-40,z1);
    glEnd();
    //SISI KIRI HADEP BELAKANG
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z2);
    glVertex3f(x2,-50,z2);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2+2,-40,z2);
    glEnd();
    //SISI KIRI HADEP ATAS
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-40,z1);
    glVertex3f(x2,-40,z1);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2+2,-40,z2);
    glEnd();

    //ALAS DUDUK
    glColor3f(94/255.f,44/255.f,6/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z1);
    glVertex3f(x2,-40,z1);

    glVertex3f(x1,-40,z1-2);
    glVertex3f(x2,-40,z1-2);

    glVertex3f(x1,-40,z1-4);
    glVertex3f(x2,-40,z1-4);

    glVertex3f(x1,-40,z1-6);
    glVertex3f(x2,-40,z1-6);

    glVertex3f(x1,-40,z2);
    glVertex3f(x2,-40,z2);
    glEnd();

    //SENDERAN KANAN & KIRI
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z1);
    glVertex3f(x1,-32,z1);

    glVertex3f(x2,-40,z1);
    glVertex3f(x2,-32,z1);
    glEnd();

    //SENDERAN
    glColor3f(148/255.f,96/255.f,56/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z1);
    glVertex3f(x2,-40,z1);

    glVertex3f(x1,-38,z1);
    glVertex3f(x2,-38,z1);

    glVertex3f(x1,-36,z1);
    glVertex3f(x2,-36,z1);

    glVertex3f(x1,-36,z1);
    glVertex3f(x2,-36,z1);

    glVertex3f(x1,-34,z1);
    glVertex3f(x2,-34,z1);

    glVertex3f(x1,-32,z1);
    glVertex3f(x2,-32,z1);
    glEnd();
}

void bangkuBelakang(float x1, float x2,float z1, float z2){
    //SISI KANAN LUAR
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z1);
    glVertex3f(x1,-50,z2);
    glVertex3f(x1,-40,z2);
    glVertex3f(x1,-40,z1);
    glEnd();
    //SISI KANAN DALAM
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1-2,-50,z1);
    glVertex3f(x1-2,-50,z2);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1-2,-40,z1);
    glEnd();
    //SISI KANAN HADEP DEPAN
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z1);
    glVertex3f(x1-2,-50,z1);
    glVertex3f(x1-2,-40,z1);
    glVertex3f(x1,-40,z1);
    glEnd();
    //SISI KANAN HADEP BELAKANG
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-50,z2);
    glVertex3f(x1-2,-50,z2);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1,-40,z2);
    glEnd();
    //SISI KANAN HADEP ATAS
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x1,-40,z1);
    glVertex3f(x1-2,-40,z1);
    glVertex3f(x1-2,-40,z2);
    glVertex3f(x1,-40,z2);
    glEnd();

    //SISI KIRI DALEM
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z1);
    glVertex3f(x2+2,-50,z2);
    glVertex3f(x2+2,-40,z2);
    glVertex3f(x2+2,-40,z1);
    glEnd();
    //SISI KIRI LUAR
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2,-50,z1);
    glVertex3f(x2,-50,z2);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2,-40,z1);
    glEnd();
    //SISI KIRI HADEP DEPAN
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z1);
    glVertex3f(x2,-50,z1);
    glVertex3f(x2,-40,z1);
    glVertex3f(x2+2,-40,z1);
    glEnd();
    //SISI KIRI HADEP BELAKANG
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-50,z2);
    glVertex3f(x2,-50,z2);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2+2,-40,z2);
    glEnd();
    //SISI KIRI HADEP ATAS
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_POLYGON);
    glVertex3f(x2+2,-40,z1);
    glVertex3f(x2,-40,z1);
    glVertex3f(x2,-40,z2);
    glVertex3f(x2+2,-40,z2);
    glEnd();

    //ALAS DUDUK
    glColor3f(94/255.f,44/255.f,6/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z1);
    glVertex3f(x2,-40,z1);

    glVertex3f(x1,-40,z1-2);
    glVertex3f(x2,-40,z1-2);

    glVertex3f(x1,-40,z1-4);
    glVertex3f(x2,-40,z1-4);

    glVertex3f(x1,-40,z1-6);
    glVertex3f(x2,-40,z1-6);

    glVertex3f(x1,-40,z2);
    glVertex3f(x2,-40,z2);
    glEnd();

    //SENDERAN KANAN & KIRI
    glColor3f(139/255.f,85/255.f,83/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z2);
    glVertex3f(x1,-32,z2);

    glVertex3f(x2,-40,z2);
    glVertex3f(x2,-32,z2);
    glEnd();

    //SENDERAN
    glColor3f(148/255.f,96/255.f,56/255.f);
    glBegin(GL_LINES);
    glVertex3f(x1,-40,z2);
    glVertex3f(x2,-40,z2);

    glVertex3f(x1,-38,z2);
    glVertex3f(x2,-38,z2);

    glVertex3f(x1,-36,z2);
    glVertex3f(x2,-36,z2);

    glVertex3f(x1,-36,z2);
    glVertex3f(x2,-36,z2);

    glVertex3f(x1,-34,z2);
    glVertex3f(x2,-34,z2);

    glVertex3f(x1,-32,z2);
    glVertex3f(x2,-32,z2);
    glEnd();
}

void pot(float x, float y, float z)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z+4);
    glVertex3f(x+4,y,z+4);
    glVertex3f(x+2.5,y-9.7,z+2.5);
    glVertex3f(x-2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z-4);
    glVertex3f(x+4,y,z-4);
    glVertex3f(x+2.5,y-9.7,z-2.5);
    glVertex3f(x-2.5,y-9.7,z-2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z+4);
    glVertex3f(x-4,y,z-4);
    glVertex3f(x-2.5,y-9.7,z-2.5);
    glVertex3f(x-2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x+4,y,z+4);
    glVertex3f(x+4,y,z-4);
    glVertex3f(x+2.5,y-9.7,z-2.5);
    glVertex3f(x+2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(48/255.f,30/255.f,10/255.f);
    glVertex3f(x-3.5,y-3.0,z-3.5);
    glVertex3f(x+3.5,y-3.0,z-3.5);
    glVertex3f(x+3.5,y-3.0,z+3.5);
    glVertex3f(x-3.5,y-3.0,z+3.5);
    glEnd();

    //batang
    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z-2);
    glVertex3f(x+1,y+4,z-2);
    glVertex3f(x+1,y-5,z-2);
    glVertex3f(x-1,y-5,z-2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z+2);
    glVertex3f(x+1,y+4,z+2);
    glVertex3f(x+1,y-5,z+2);
    glVertex3f(x-1,y-5,z+2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x+1,y+4,z+2);
    glVertex3f(x+1,y+4,z-2);
    glVertex3f(x+1,y-5,z-2);
    glVertex3f(x+1,y-5,z+2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z+2);
    glVertex3f(x-1,y+4,z-2);
    glVertex3f(x-1,y-5,z-2);
    glVertex3f(x-1,y-5,z+2);
    glEnd();

    //dahan
    glBegin(GL_TRIANGLES);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-5,y+3.5,z+2);
    glVertex3f(x,y+25,z+2);
    glVertex3f(x+5,y+3.5,z+2);

    glVertex3f(x-5,y+3.5,z-2);
    glVertex3f(x,y+25,z-2);
    glVertex3f(x+5,y+3.5,z-2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-5,y+3.5,z-2);
    glVertex3f(x-5,y+3.5,z+2);
    glVertex3f(x+5,y+3.5,z+2);
    glVertex3f(x+5,y+3.5,z-2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-5,y+3.5,z-2);
    glVertex3f(x-5,y+3.5,z+2);
    glVertex3f(x,y+25,z+2);
    glVertex3f(x,y+25,z-2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x+5,y+3.5,z-2);
    glVertex3f(x+5,y+3.5,z+2);
    glVertex3f(x,y+25,z+2);
    glVertex3f(x,y+25,z-2);
    glEnd();

    glPushMatrix();
    glColor3f(209/255.f,34/255.f,10/255.f);
    glTranslatef(x+3,y+3,z);
    glutSolidSphere(1.5,10,10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(209/255.f,34/255.f,10/255.f);
    glTranslatef(x-3,y+3,z);
    glutSolidSphere(1.5,10,10);
    glPopMatrix();

    glPopMatrix();
}

void pohon(float x, float y, float z){

        glBegin(GL_QUADS);
        glColor3f(66/255.f,42/255.f,10/255.f);
        glVertex3f(x-2.5,y,z-2.5);
        glVertex3f(x+2.5,y,z-2.5);
        glVertex3f(x+2.5,y+49.7,z-2.5);
        glVertex3f(x-2.5,y+49.7,z-2.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(66/255.f,42/255.f,10/255.f);
        glVertex3f(x-2.5,y,z+2.5);
        glVertex3f(x+2.5,y,z+2.5);
        glVertex3f(x+2.5,y+49.7,z+2.5);
        glVertex3f(x-2.5,y+49.7,z+2.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(66/255.f,42/255.f,10/255.f);
        glVertex3f(x-2.5,y,z+2.5);
        glVertex3f(x-2.5,y,z-2.5);
        glVertex3f(x-2.5,y+49.7,z-2.5);
        glVertex3f(x-2.5,y+49.7,z+2.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(66/255.f,42/255.f,10/255.f);
        glVertex3f(x+2.5,y,z+2.5);
        glVertex3f(x+2.5,y,z-2.5);
        glVertex3f(x+2.5,y+49.7,z-2.5);
        glVertex3f(x+2.5,y+49.7,z+2.5);
        glEnd();

        for(int i=0;i<2;i++)
        {
            int awal = x-7.5;
            int batas = x+7.5;
            for (int j=awal;j<=batas;j+=15)
            {
                int l=z;
                int k=y+49.7;
                glPushMatrix();
                glTranslatef(j,k,l);
                glColor3f(0.3,0.7,0.3);
                glutSolidSphere(10,20,20);
                glPopMatrix();
            }
        }
        //single
        glPushMatrix();
        glTranslatef(x,y+64.7,z);
        glColor3f(0.3,0.7,0.3);
        glutSolidSphere(10,20,20);
        glPopMatrix();
}

void pot2(float x, float y, float z)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z+4);
    glVertex3f(x+4,y,z+4);
    glVertex3f(x+2.5,y-9.7,z+2.5);
    glVertex3f(x-2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z-4);
    glVertex3f(x+4,y,z-4);
    glVertex3f(x+2.5,y-9.7,z-2.5);
    glVertex3f(x-2.5,y-9.7,z-2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x-4,y,z+4);
    glVertex3f(x-4,y,z-4);
    glVertex3f(x-2.5,y-9.7,z-2.5);
    glVertex3f(x-2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,74/255.f,9/255.f);
    glVertex3f(x+4,y,z+4);
    glVertex3f(x+4,y,z-4);
    glVertex3f(x+2.5,y-9.7,z-2.5);
    glVertex3f(x+2.5,y-9.7,z+2.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(48/255.f,30/255.f,10/255.f);
    glVertex3f(x-3.5,y-3.0,z-3.5);
    glVertex3f(x+3.5,y-3.0,z-3.5);
    glVertex3f(x+3.5,y-3.0,z+3.5);
    glVertex3f(x-3.5,y-3.0,z+3.5);
    glEnd();

    //batang
    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z-2);
    glVertex3f(x+1,y+4,z-2);
    glVertex3f(x+1,y-5,z-2);
    glVertex3f(x-1,y-5,z-2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z+2);
    glVertex3f(x+1,y+4,z+2);
    glVertex3f(x+1,y-5,z+2);
    glVertex3f(x-1,y-5,z+2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x+1,y+4,z+2);
    glVertex3f(x+1,y+4,z-2);
    glVertex3f(x+1,y-5,z-2);
    glVertex3f(x+1,y-5,z+2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(85/255.f,54/255.f,18/255.f);
    glVertex3f(x-1,y+4,z+2);
    glVertex3f(x-1,y+4,z-2);
    glVertex3f(x-1,y-5,z-2);
    glVertex3f(x-1,y-5,z+2);
    glEnd();

    //dahan
    glBegin(GL_TRIANGLES);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x+2,y+3.5,z-5);
    glVertex3f(x+2,y+25,z);
    glVertex3f(x+2,y+3.5,z+5);

    glVertex3f(x-2,y+3.5,z-5);
    glVertex3f(x-2,y+25,z);
    glVertex3f(x-2,y+3.5,z+5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-2,y+3.5,z-2);
    glVertex3f(x+2,y+3.5,z-2);
    glVertex3f(x+2,y+3.5,z+2);
    glVertex3f(x-2,y+3.5,z+2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-2,y+3.5,z-5);
    glVertex3f(x+2,y+3.5,z-5);
    glVertex3f(x+2,y+25,z);
    glVertex3f(x-2,y+25,z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(17/255.f,84/255.f,19/255.f);
    glVertex3f(x-2,y+3.5,z+5);
    glVertex3f(x+2,y+3.5,z+5);
    glVertex3f(x+2,y+25,z);
    glVertex3f(x-2,y+25,z);
    glEnd();

    glPushMatrix();
    glColor3f(209/255.f,34/255.f,10/255.f);
    glTranslatef(x,y+3,z+3);
    glutSolidSphere(1.5,10,10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(209/255.f,34/255.f,10/255.f);
    glTranslatef(x,y+3,z-3);
    glutSolidSphere(1.5,10,10);
    glPopMatrix();

    glPopMatrix();
}

void vending_depan(void)
{
    glBegin(GL_QUADS);
    glColor3f(28/255.f,21/255.f,20/255.f);
    glVertex3f(-15,-49.7,50);
    glVertex3f(0,-49.7,50);
    glVertex3f(0,-49.7,40);
    glVertex3f(-15,-49.7,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,50);
    glVertex3f(0,-19.7,50);
    glVertex3f(0,-19.7,40);
    glVertex3f(-15,-19.7,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,50);
    glVertex3f(-15,-19.7,40);
    glVertex3f(-15,-49.7,40);
    glVertex3f(-15,-49.7,50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(0,-19.7,50);
    glVertex3f(0,-19.7,40);
    glVertex3f(0,-49.7,40);
    glVertex3f(0,-49.7,50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,50);
    glVertex3f(0,-19.7,50);
    glVertex3f(0,-49.7,50);
    glVertex3f(-15,-49.7,50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,40);
    glVertex3f(0,-19.7,40);
    glVertex3f(0,-22,40);
    glVertex3f(-15,-22,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-49.7,40);
    glVertex3f(0,-49.7,40);
    glVertex3f(0,-46,40);
    glVertex3f(-15,-46,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-40,40);
    glVertex3f(0,-40,40);
    glVertex3f(0,-42,40);
    glVertex3f(-15,-42,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-2,-46,40);
    glVertex3f(0,-46,40);
    glVertex3f(0,-22,40);
    glVertex3f(-2,-22,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-13,-46,40);
    glVertex3f(-15,-46,40);
    glVertex3f(-15,-22,40);
    glVertex3f(-13,-22,40);
    glEnd();

    tabung(-5,-35,42,0.5,0.7,0.5,56,56,56,1);
    tabung(-10,-35,42,0.5,0.7,0.5,56,56,56,1);

    glBegin(GL_QUADS);
    glColor4f(201/255.f,201/255.f,201/255.f,0.45);
    glVertex3f(-13,-22,40);
    glVertex3f(-2,-22,40);
    glVertex3f(-2,-40,40);
    glVertex3f(-13,-40,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(184/255.f,184/255.f,184/255.f);
    glVertex3f(-13,-46,40);
    glVertex3f(-2,-46,40);
    glVertex3f(-2,-42,40);
    glVertex3f(-13,-42,40);
    glEnd();
}

void vending_belakang(void)
{
    glBegin(GL_QUADS);
    glColor3f(28/255.f,21/255.f,20/255.f);
    glVertex3f(-15,-49.7,-50);
    glVertex3f(0,-49.7,-50);
    glVertex3f(0,-49.7,-40);
    glVertex3f(-15,-49.7,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,-50);
    glVertex3f(0,-19.7,-50);
    glVertex3f(0,-19.7,-40);
    glVertex3f(-15,-19.7,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,-50);
    glVertex3f(-15,-19.7,-40);
    glVertex3f(-15,-49.7,-40);
    glVertex3f(-15,-49.7,-50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(0,-19.7,-50);
    glVertex3f(0,-19.7,-40);
    glVertex3f(0,-49.7,-40);
    glVertex3f(0,-49.7,-50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,-49.9);
    glVertex3f(0,-19.7,-49.9);
    glVertex3f(0,-49.7,-49.9);
    glVertex3f(-15,-49.7,-49.9);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-19.7,-40);
    glVertex3f(0,-19.7,-40);
    glVertex3f(0,-22,-40);
    glVertex3f(-15,-22,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-49.7,-40);
    glVertex3f(0,-49.7,-40);
    glVertex3f(0,-46,-40);
    glVertex3f(-15,-46,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-15,-40,-40);
    glVertex3f(0,-40,-40);
    glVertex3f(0,-42,-40);
    glVertex3f(-15,-42,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-2,-46,-40);
    glVertex3f(0,-46,-40);
    glVertex3f(0,-22,-40);
    glVertex3f(-2,-22,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(179/255.f,30/255.f,16/255.f);
    glVertex3f(-13,-46,-40);
    glVertex3f(-15,-46,-40);
    glVertex3f(-15,-22,-40);
    glVertex3f(-13,-22,-40);
    glEnd();

    tabung(-5,-35,-42,0.5,0.7,0.5,56,56,56,1);
    tabung(-10,-35,-42,0.5,0.7,0.5,56,56,56,1);

    glBegin(GL_QUADS);
    glColor4f(201/255.f,201/255.f,201/255.f,0.45);
    glVertex3f(-13,-22,-40);
    glVertex3f(-2,-22,-40);
    glVertex3f(-2,-40,-40);
    glVertex3f(-13,-40,-40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(184/255.f,184/255.f,184/255.f);
    glVertex3f(-13,-46,-40);
    glVertex3f(-2,-46,-40);
    glVertex3f(-2,-42,-40);
    glVertex3f(-13,-42,-40);
    glEnd();
}

void dinding_pintu_depan(void){
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

        //kanopi
        glBegin(GL_QUADS);
        glColor3f(0.8,0.8,0.8);
        glVertex3f(237.5,-20,7.5);
        glVertex3f(237.5,-20,-12.5);
        glVertex3f(220,-20,-12.5);
        glVertex3f(220,-20,7.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(163/255.f,23/255.f,23/255.f);
        glVertex3f(237.5,-19.1,7.5);
        glVertex3f(237.5,-19.1,-12.5);
        glVertex3f(220,-19.1,-12.5);
        glVertex3f(220,-19.1,7.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(163/255.f,23/255.f,23/255.f);
        glVertex3f(237.5,-20,7.5);
        glVertex3f(237.5,-20,-12.5);
        glVertex3f(237.5,-19.1,-12.5);
        glVertex3f(237.5,-19.1,7.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.8,0.8,0.8);
        glVertex3f(237.5,-20,7.5);
        glVertex3f(220,-20,7.5);
        glVertex3f(220,-19.1,7.5);
        glVertex3f(237.5,-19.1,7.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.8,0.8,0.8);
        glVertex3f(237.5,-20,-12.5);
        glVertex3f(220,-20,-12.5);
        glVertex3f(220,-19.1,-12.5);
        glVertex3f(237.5,-19.1,-12.5);
        glEnd();

        //garis
        glBegin(GL_LINES);
        glColor4f(15/255.f,15/255.f,15/255.f,0.8);
        glVertex3f(235,-20,-12);
        glVertex3f(235,-49.9,-12);

        glVertex3f(235,-20,7);
        glVertex3f(235,-49.9,7);
        glEnd();

        //karpet
        glBegin(GL_QUADS);
        glColor3f(215/255.f,25/255.f,25/255.f);
        glVertex3f(237.5,-49.8,7.5);
        glVertex3f(220,-49.8,7.5);
        glVertex3f(220,-49.8,-12.5);
        glVertex3f(237.5,-49.8,-12.5);
        glEnd();

        //kaca
        glBegin(GL_QUADS);
        glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
        glVertex3f(220.1,-49.9,-2.5);
        glVertex3f(220.1,-49.9,-12.5);
        glVertex3f(220.1,-20,-12.5);
        glVertex3f(220.1,-20,-2.5);
        glEnd();

        //kaca
        glBegin(GL_QUADS);
        glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
        glVertex3f(220.1,-49.9,-2.5);
        glVertex3f(220.1,-49.9,7.5);
        glVertex3f(220.1,-20,7.5);
        glVertex3f(220.1,-20,-2.5);
        glEnd();
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

    // pondasi bawah
    glColor3f(86/255.f, 46/255.f, 0/255.f);
    glBegin(GL_QUADS);
        glVertex3f(-350, -70, -140);
        glVertex3f(350, -70, -140);
        glVertex3f(350, -70, 150);
        glVertex3f(-350, -70, 150);
    glEnd();

    // pondasi tepi
    glColor3f(115/255.f, 62/255.f, 0/255.f);
    glBegin(GL_QUADS); // depan
        glVertex3f(-350, -50, 150);
        glVertex3f(350, -50, 150);
        glVertex3f(350, -70, 150);
        glVertex3f(-350, -70, 150);
    glEnd();
    glBegin(GL_QUADS); // belakang
        glVertex3f(-350, -50, -140);
        glVertex3f(350, -50, -140);
        glVertex3f(350, -70, -140);
        glVertex3f(-350, -70, -140);
    glEnd();
    glColor3f(105/255.f, 55/255.f, 0/255.f);
    glBegin(GL_QUADS); // kiri
        glVertex3f(-350, -50, -140);
        glVertex3f(-350, -50, 150);
        glVertex3f(-350, -70, 150);
        glVertex3f(-350, -70, -140);
    glEnd();
    glBegin(GL_QUADS); // kanan
        glVertex3f(350, -50, -140);
        glVertex3f(350, -50, 150);
        glVertex3f(350, -70, 150);
        glVertex3f(350, -70, -140);
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
    //pagar lantai 2 1
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(209,-10,10);
        glVertex3f(160,-10,10);
        glVertex3f(160,0,10);
        glVertex3f(209,0,10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(159,-10,10);
        glVertex3f(160,-10,10);
        glVertex3f(160,0,10);
        glVertex3f(159,0,10);
        glVertex3f(210,-10,10);
        glVertex3f(209,-10,10);
        glVertex3f(209,0,10);
        glVertex3f(210,0,10);
    glEnd();

    //pagar lantai 2 2
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(160,-10,10);
        glVertex3f(100,-10,30);
        glVertex3f(100,0,30);
        glVertex3f(160,0,10);
        glVertex3f(90,0,30);
        glVertex3f(90,-10,30);
        glVertex3f(100,-10,30);
        glVertex3f(100,0,30);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(90,-10,30);
        glVertex3f(89,-10,30);
        glVertex3f(89,0,30);
        glVertex3f(90,0,30);
    glEnd();

    //pagar lantai 2 3
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(89,-10,30);
        glVertex3f(10,-10,10);
        glVertex3f(10,0,10);
        glVertex3f(89,0,30);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(10,-10,10);
        glVertex3f(9,-10,10);
        glVertex3f(9,0,10);
        glVertex3f(10,0,10);
    glEnd();

    //pagar lantai 2 4
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(9,-10,10);
        glVertex3f(-100,-10,30);
        glVertex3f(-100,0,30);
        glVertex3f(9,0,10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-100,-10,30);
        glVertex3f(-101,-10,30);
        glVertex3f(-101,0,30);
        glVertex3f(-100,0,30);
    glEnd();

    //pagar lantai 2 5
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-101,-10,30);
        glVertex3f(-160,-10,20);
        glVertex3f(-160,0,20);
        glVertex3f(-101,0,30);
        glVertex3f(-160,-10,20);
        glVertex3f(-160,0,20);
        glVertex3f(-189,0,20);
        glVertex3f(-189,-10,20);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-189,-10,20);
        glVertex3f(-190,-10,20);
        glVertex3f(-190,0,20);
        glVertex3f(-189,0,20);
    glEnd();

    //pagar lantai 2 6,7
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-190,-10,20);
        glVertex3f(-190,-10,-20);
        glVertex3f(-190,0,-20);
        glVertex3f(-190,0,20);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-189,-10,-20);
        glVertex3f(-190,-10,-20);
        glVertex3f(-190,0,-20);
        glVertex3f(-189,0,-20);

    //pagar lantai 2 8
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-189,-10,-20);
        glVertex3f(-140,-10,-20);
        glVertex3f(-140,0,-20);
        glVertex3f(-189,0,-20);
        glVertex3f(-140,-10,-20);
        glVertex3f(-115,-10,-25);
        glVertex3f(-115,0,-25);
        glVertex3f(-140,0,-20);
        glVertex3f(-114,-10,-25);
        glVertex3f(-50,-10,-30);
        glVertex3f(-50,0,-30);
        glVertex3f(-114,0,-25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-50,-10,-30);
        glVertex3f(-49,-10,-30);
        glVertex3f(-49,0,-30);
        glVertex3f(-50,0,-30);
        glVertex3f(-140,-10,-20);
        glVertex3f(-139,-10,-20);
        glVertex3f(-139,0,-20);
        glVertex3f(-140,0,-20);
        glVertex3f(-115,-10,-25);
        glVertex3f(-114,-10,-25);
        glVertex3f(-114,0,-25);
        glVertex3f(-115,0,-25);
    glEnd();

    //pagar lantai 2 9
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-49,-10,-30);
        glVertex3f(10,-10,-10);
        glVertex3f(10,0,-10);
        glVertex3f(-49,0,-30);
        glVertex3f(10,-10,-10);
        glVertex3f(75,-10,-25);
        glVertex3f(75,0,-25);
        glVertex3f(10,0,-10);
        glVertex3f(75,-10,-25);
        glVertex3f(119,-10,-25);
        glVertex3f(119,0,-25);
        glVertex3f(75,0,-25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(10,-10,-10);
        glVertex3f(9,-10,-10);
        glVertex3f(9,0,-10);
        glVertex3f(10,0,-10);
        glVertex3f(75,-10,-25);
        glVertex3f(76,-10,-25);
        glVertex3f(76,0,-25);
        glVertex3f(75,0,-25);
        glVertex3f(119,-10,-25);
        glVertex3f(120,-10,-25);
        glVertex3f(120,0,-25);
        glVertex3f(119,0,-25);
    glEnd();

    //pagar lantai 2 10
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(120,-10,-25);
        glVertex3f(170,-10,-10);
        glVertex3f(170,0,-10);
        glVertex3f(120,0,-25);
        glVertex3f(170,-10,-10);
        glVertex3f(199,-10,-10);
        glVertex3f(199,0,-10);
        glVertex3f(170,0,-10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(170,-10,-10);
        glVertex3f(171,-10,-10);
        glVertex3f(171,0,-10);
        glVertex3f(170,0,-10);
        glVertex3f(199,-10,-10);
        glVertex3f(200,-10,-10);
        glVertex3f(200,0,-10);
        glVertex3f(199,0,-10);
    glEnd();

//pagar lantai 3 1
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(209,30,10);
        glVertex3f(160,30,10);
        glVertex3f(160,40,10);
        glVertex3f(209,40,10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(159,30,10);
        glVertex3f(160,30,10);
        glVertex3f(160,40,10);
        glVertex3f(159,40,10);
        glVertex3f(210,30,10);
        glVertex3f(209,30,10);
        glVertex3f(209,40,10);
        glVertex3f(210,40,10);
    glEnd();

    //pagar lantai 3 2
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(160,30,10);
        glVertex3f(100,30,30);
        glVertex3f(100,40,30);
        glVertex3f(160,40,10);
        glVertex3f(90,40,30);
        glVertex3f(90,30,30);
        glVertex3f(100,30,30);
        glVertex3f(100,40,30);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(90,30,30);
        glVertex3f(89,30,30);
        glVertex3f(89,40,30);
        glVertex3f(90,40,30);
    glEnd();

    //pagar lantai 3 3
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(89,30,30);
        glVertex3f(10,30,10);
        glVertex3f(10,40,10);
        glVertex3f(89,40,30);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(10,30,10);
        glVertex3f(9,30,10);
        glVertex3f(9,40,10);
        glVertex3f(10,40,10);
    glEnd();

    //pagar lantai 3 4
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(9,30,10);
        glVertex3f(-100,30,30);
        glVertex3f(-100,40,30);
        glVertex3f(9,40,10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-100,30,30);
        glVertex3f(-101,30,30);
        glVertex3f(-101,40,30);
        glVertex3f(-100,40,30);
    glEnd();

    //pagar lantai 3 5
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-101,30,30);
        glVertex3f(-160,30,20);
        glVertex3f(-160,40,20);
        glVertex3f(-101,40,30);
        glVertex3f(-160,30,20);
        glVertex3f(-160,40,20);
        glVertex3f(-189,40,20);
        glVertex3f(-189,30,20);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-189,30,20);
        glVertex3f(-190,30,20);
        glVertex3f(-190,40,20);
        glVertex3f(-189,40,20);
    glEnd();

    //pagar lantai 3 6,7
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-190,30,20);
        glVertex3f(-190,30,-20);
        glVertex3f(-190,40,-20);
        glVertex3f(-190,40,20);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-189,30,-20);
        glVertex3f(-190,30,-20);
        glVertex3f(-190,40,-20);
        glVertex3f(-189,40,-20);

    //pagar lantai 3 8
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-189,30,-20);
        glVertex3f(-140,30,-20);
        glVertex3f(-140,40,-20);
        glVertex3f(-189,40,-20);
        glVertex3f(-140,30,-20);
        glVertex3f(-115,30,-25);
        glVertex3f(-115,40,-25);
        glVertex3f(-140,40,-20);
        glVertex3f(-114,30,-25);
        glVertex3f(-50,30,-30);
        glVertex3f(-50,40,-30);
        glVertex3f(-114,40,-25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(-50,30,-30);
        glVertex3f(-49,30,-30);
        glVertex3f(-49,40,-30);
        glVertex3f(-50,40,-30);
        glVertex3f(-140,30,-20);
        glVertex3f(-139,30,-20);
        glVertex3f(-139,40,-20);
        glVertex3f(-140,40,-20);
        glVertex3f(-115,30,-25);
        glVertex3f(-114,30,-25);
        glVertex3f(-114,40,-25);
        glVertex3f(-115,40,-25);
    glEnd();

    //pagar lantai 3 9
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(-49,30,-30);
        glVertex3f(10,30,-10);
        glVertex3f(10,40,-10);
        glVertex3f(-49,40,-30);
        glVertex3f(10,30,-10);
        glVertex3f(75,30,-25);
        glVertex3f(75,40,-25);
        glVertex3f(10,40,-10);
        glVertex3f(75,30,-25);
        glVertex3f(119,30,-25);
        glVertex3f(119,40,-25);
        glVertex3f(75,40,-25);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(10,30,-10);
        glVertex3f(9,30,-10);
        glVertex3f(9,40,-10);
        glVertex3f(10,40,-10);
        glVertex3f(75,30,-25);
        glVertex3f(76,30,-25);
        glVertex3f(76,40,-25);
        glVertex3f(75,40,-25);
        glVertex3f(119,30,-25);
        glVertex3f(120,30,-25);
        glVertex3f(120,40,-25);
        glVertex3f(119,40,-25);
    glEnd();

    //pagar lantai 3 10
    glColor4f(215/255.f, 255/255.f, 253/255.f, 0.3);
    glBegin(GL_QUADS); // kaca
        glVertex3f(120,30,-25);
        glVertex3f(170,30,-10);
        glVertex3f(170,40,-10);
        glVertex3f(120,40,-25);
        glVertex3f(170,30,-10);
        glVertex3f(199,30,-10);
        glVertex3f(199,40,-10);
        glVertex3f(170,40,-10);
    glEnd();
    glColor3f(228/255.f, 228/255.f, 228/255.f);
    glBegin(GL_QUADS); // tiang pagar
        glVertex3f(170,30,-10);
        glVertex3f(171,30,-10);
        glVertex3f(171,40,-10);
        glVertex3f(170,40,-10);
        glVertex3f(199,30,-10);
        glVertex3f(200,30,-10);
        glVertex3f(200,40,-10);
        glVertex3f(199,40,-10);
    glEnd();

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

    // animasi pintu
    glPushMatrix();
        glTranslated(x_pintu_kiri,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-200,-50,70);
            glVertex3f(-190,-50,70);
            glVertex3f(-190,-25,70);
            glVertex3f(-200,-25,70);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslated(x_pintu_kanan,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-190,-50,70);
            glVertex3f(-180,-50,70);
            glVertex3f(-180,-25,70);
            glVertex3f(-190,-25,70);
        glEnd();
    glPopMatrix();

    for(int i=0; i<3; i++){
        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(-200+(i*10),-50,70);
            glVertex3f(-200+(i*10),-25,70);
        glEnd();
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

    // animasi pintu
    glPushMatrix();
        glTranslated(x_pintu_kiri,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-50,-50,70);
            glVertex3f(-40,-50,70);
            glVertex3f(-40,-25,70);
            glVertex3f(-50,-25,70);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslated(x_pintu_kanan,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-40,-50,70);
            glVertex3f(-30,-50,70);
            glVertex3f(-30,-25,70);
            glVertex3f(-40,-25,70);
        glEnd();
    glPopMatrix();

    for(int i=0; i<3; i++){
        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(-50+(i*10),-50,70);
            glVertex3f(-50+(i*10),-25,70);
        glEnd();
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

    // animasi pintu
    glPushMatrix();
        glTranslated(x_pintu_kiri,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-190,-50,-75);
            glVertex3f(-180,-50,-75);
            glVertex3f(-180,-25,-75);
            glVertex3f(-190,-25,-75);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslated(x_pintu_kanan,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-180,-50,-75);
            glVertex3f(-170,-50,-75);
            glVertex3f(-170,-25,-75);
            glVertex3f(-180,-25,-75);
        glEnd();
    glPopMatrix();

    for(int i=0; i<3; i++){
        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(-190+(i*10),-50,-75);
            glVertex3f(-190+(i*10),-25,-75);
        glEnd();
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

    // animasi pintu
    glPushMatrix();
        glTranslated(x_pintu_kiri,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-50,-50,-65);
            glVertex3f(-40,-50,-65);
            glVertex3f(-40,-25,-65);
            glVertex3f(-50,-25,-65);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslated(x_pintu_kanan,0,0);
        glBegin(GL_QUADS);
        glColor4f(255/255.f,251/255.f,231/255.f,0.5);
            glVertex3f(-40,-50,-65);
            glVertex3f(-30,-50,-65);
            glVertex3f(-30,-25,-65);
            glVertex3f(-40,-25,-65);
        glEnd();
    glPopMatrix();

    for(int i=0; i<3; i++){
        glBegin(GL_LINE_STRIP);
        glColor4f(0/255.f,0/255.f,0/255.f,0.1);
            glVertex3f(-50+(i*10),-50,-65);
            glVertex3f(-50+(i*10),-25,-65);
        glEnd();
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

    tabung(210, -19, -2.5, 7, 14.8, 7, 82, 194, 212, 0.25);
    
    dinding_pintu_depan();
    
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

    // LIFT
    glPushMatrix();
        glTranslatef(0,y_pos,0);
        lift();
    glPopMatrix();
    luar_lift();

    //BANGKU DEPAN
    bangkuDepan(-55,-105,52,44);
    bangkuDepan(-125,-175,52,44);

    //BANGKU BELAKANG
    bangkuBelakang(-80,-130,-44,-52);
    bangkuBelakang(-185,-215,-110,-117.5);
    bangkuBelakang(215,175,-110,-117.5);

    float aLampu=-300;
    float bLampu=-295;

    while(aLampu<=300 && bLampu<=295){
        //LAMPU JALAN
        //ALAS SISI HADEP DEPAN
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu,-50,115);
        glVertex3f(bLampu,-50,115);
        glVertex3f(bLampu-1,-40,114);
        glVertex3f(aLampu+1,-40,114);
        glEnd();

        //ALAS SISI HADEP BELAKANG
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu,-50,110);
        glVertex3f(bLampu,-50,110);
        glVertex3f(bLampu-1,-40,111);
        glVertex3f(aLampu+1,-40,111);
        glEnd();

        //ALAS SISI HADEP KIRI
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu,-50,115);
        glVertex3f(aLampu,-50,110);
        glVertex3f(aLampu+1,-40,111);
        glVertex3f(aLampu+1,-40,114);
        glEnd();

        //ALAS SISI HADEP KIRI
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(bLampu,-50,115);
        glVertex3f(bLampu,-50,110);
        glVertex3f(bLampu-1,-40,111);
        glVertex3f(bLampu-1,-40,114);
        glEnd();

        //ALAS SISI HADEP ATAS
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu+1,-40,114);
        glVertex3f(bLampu-1,-40,114);
        glVertex3f(bLampu-1,-40,111);
        glVertex3f(aLampu+1,-40,111);
        glEnd();

        //TIANG TEGAK DEPAN
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu+2,-40,113);
        glVertex3f(bLampu-2,-40,113);
        glVertex3f(bLampu-2,0,113);
        glVertex3f(aLampu+2,0,113);
        glEnd();

        //TIANG TEGAK BELAKANG
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu+2,-40,112);
        glVertex3f(bLampu-2,-40,112);
        glVertex3f(bLampu-2,0,112);
        glVertex3f(aLampu+2,0,112);
        glEnd();

        //TIANG TEGAK KIRI
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(aLampu+2,-40,113);
        glVertex3f(aLampu+2,-40,112);
        glVertex3f(aLampu+2,0,112);
        glVertex3f(aLampu+2,0,113);
        glEnd();

        //TIANG TEGAK KANAN
        glBegin(GL_QUADS);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(bLampu-2,-40,113);
        glVertex3f(bLampu-2,-40,112);
        glVertex3f(bLampu-2,0,112);
        glVertex3f(bLampu-2,0,113);
        glEnd();

        //CAGAK LAMPU
        glBegin(GL_LINES);
        glColor3f(64/255.f,64/255.f,64/255.f);
        glVertex3f(bLampu-2.5,-2,112.5);
        glVertex3f(bLampu-2.5,3,116);

        glVertex3f(bLampu-2.5,-2,112.5);
        glVertex3f(bLampu-2.5,3,109);

        glVertex3f(bLampu-2.5,3,116);
        glVertex3f(bLampu-2.5,3,119);

        glVertex3f(bLampu-2.5,3,109);
        glVertex3f(bLampu-2.5,3,106);
        glEnd();

        //LAMPU JALAN
        glPushMatrix();
            glColor3f(1.0,1.0,0.0);
            glTranslated(bLampu-2.5,1,118);
            glutSolidSphere(2,10,10);
        glPopMatrix();

        glPushMatrix();
            glColor3f(1.0,1.0,0.0);
            glTranslated(bLampu-2.5,1,107);
            glutSolidSphere(2,10,10);
        glPopMatrix();

        aLampu+=70;
        bLampu+=70;
    }

    //MOBIL
    glPushMatrix();
        glTranslatef(x_pos,0,0);
        mobil(228,270);
    glPopMatrix();

    //AWAN
    glPushMatrix();
        glTranslatef(x_awan,0,0);
        awan(90,100,110,120,-60);
        awan(-170,-160,130,140,-90);
        awan(0,10,150,160,-80);
        awan(-10,0,140,150,80);
        awan(-200,-190,120,130,50);
        awan(150,160,140,150,0);
    glPopMatrix();

    //BANGJO
    //ALAS SISI HADEP DEPAN
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-320,-50,115);
    glVertex3f(-315,-50,115);
    glVertex3f(-316,-40,114);
    glVertex3f(-319,-40,114);
    glEnd();

    //ALAS SISI HADEP BELAKANG
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-320,-50,110);
    glVertex3f(-315,-50,110);
    glVertex3f(-316,-40,111);
    glVertex3f(-319,-40,111);
    glEnd();

    //ALAS SISI HADEP KIRI
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-320,-50,115);
    glVertex3f(-320,-50,110);
    glVertex3f(-319,-40,111);
    glVertex3f(-319,-40,114);
    glEnd();

    //ALAS SISI HADEP KIRI
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-315,-50,115);
    glVertex3f(-315,-50,110);
    glVertex3f(-316,-40,111);
    glVertex3f(-316,-40,114);
    glEnd();

    //ALAS SISI HADEP ATAS
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-319,-40,114);
    glVertex3f(-316,-40,114);
    glVertex3f(-316,-40,111);
    glVertex3f(-319,-40,111);
    glEnd();

    //TIANG TEGAK DEPAN
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-318,-40,113);
    glVertex3f(-317,-40,113);
    glVertex3f(-317,0,113);
    glVertex3f(-318,0,113);
    glEnd();

    //TIANG TEGAK BELAKANG
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-318,-40,112);
    glVertex3f(-317,-40,112);
    glVertex3f(-317,0,112);
    glVertex3f(-318,0,112);
    glEnd();

    //TIANG TEGAK KIRI
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-318,-40,113);
    glVertex3f(-318,-40,112);
    glVertex3f(-318,0,112);
    glVertex3f(-318,0,113);
    glEnd();

    //TIANG TEGAK KANAN
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-317,-40,113);
    glVertex3f(-317,-40,112);
    glVertex3f(-317,0,112);
    glVertex3f(-317,0,113);
    glEnd();

    //CAGAK BANGJO
    glBegin(GL_LINES);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-317.5,0,112.5);
    glVertex3f(-317.5,10,116);

    glVertex3f(-317.5,10,116);
    glVertex3f(-317.5,10,125);

    glVertex3f(-317.5,5,114.5);
    glVertex3f(-317.5,5,125);
    glEnd();

    //KOTAK JAUH BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-316,13,125);
    glVertex3f(-319,13,125);
    glVertex3f(-319,2,125);
    glVertex3f(-316,2,125);
    glEnd();

    //KOTAK DEKET BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-316,13,129);
    glVertex3f(-319,13,129);
    glVertex3f(-319,2,129);
    glVertex3f(-316,2,129);
    glEnd();

    //KOTAK BELAKANG BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-319,13,129);
    glVertex3f(-319,13,125);
    glVertex3f(-319,2,125);
    glVertex3f(-319,2,129);
    glEnd();

    //KOTAK DEPAN BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-316,13,129);
    glVertex3f(-316,13,125);
    glVertex3f(-316,2,125);
    glVertex3f(-316,2,129);
    glEnd();

    //KOTAK BAWAH BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-316,2,129);
    glVertex3f(-319,2,129);
    glVertex3f(-319,2,125);
    glVertex3f(-316,2,125);
    glEnd();

    //KOTAK BAWAH BANGJO
    glBegin(GL_QUADS);
    glColor3f(64/255.f,64/255.f,64/255.f);
    glVertex3f(-316,13,129);
    glVertex3f(-319,13,129);
    glVertex3f(-319,13,125);
    glVertex3f(-316,13,125);
    glEnd();

    //sofa lantai 2
    //pinggir kiri
    glBegin(GL_QUADS);
    glColor3ub(0,9,41);
    glVertex3f(-279,1,17.9);
    glColor3ub(0,19,87);
    glVertex3f(-279,-10,17.9);
    glVertex3f(-271,-10,17.9);
    glColor3ub(0,9,41);
    glVertex3f(-271,1,17.9);
    glEnd();
    //pinggir kanan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,-10,-30.1);
    glVertex3f(-271,1,-30.1);
    glVertex3f(-279,1,-30.1);
    glVertex3f(-279,-10,-30.1);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,-10,-30);
    glVertex3f(-271,-3,-30);
    glColor3ub(0,9,41);
    glVertex3f(-271,-3,18);
    glVertex3f(-271,-10,18);
    glEnd();
    //dudukan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,-3,-30);
    glColor3ub(88,117,224);
    glVertex3f(-277,-3,-30);
    glVertex3f(-277,-3,18);
    glColor3ub(0,5,23);
    glVertex3f(-271,-3,18);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-279,9,-30);
    glVertex3f(-279,-10,-30);
    glColor3ub(0,9,41);
    glVertex3f(-279,-10,18);
    glVertex3f(-279,9,18);
    glEnd();
    //senderan
    glBegin(GL_QUADS);
    glColor3ub(88,117,224);
    glVertex3f(-277,-3,-30);
    glColor3ub(0,5,23);
    glVertex3f(-279,9,-30);
    glVertex3f(-279,9,18);
    glColor3ub(88,117,224);
    glVertex3f(-277,-3,18);
    glEnd();
    //segitiga penutup kiri
    glBegin(GL_POLYGON);
    glColor3ub(88,117,224);
    glVertex3f(-277,-3,18);
    glVertex3f(-279,9,18);
    glVertex3f(-279,-3,18);
    glEnd();
    //segitiga penutup kanan
    glBegin(GL_POLYGON);
    glColor3ub(88,117,224);
    glVertex3f(-277,-3,-30);
    glVertex3f(-279,9,-30);
    glVertex3f(-279,-3,-30);
    glEnd();


    //sofa lantai 3
    //pinggir kiri
    glBegin(GL_QUADS);
    glColor3ub(0,9,41);
    glVertex3f(-279,41,17.9);
    glColor3ub(0,19,87);
    glVertex3f(-279,30,17.9);
    glVertex3f(-271,30,17.9);
    glColor3ub(0,9,41);
    glVertex3f(-271,41,17.9);
    glEnd();
    //pinggir kanan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,30,-30.1);
    glVertex3f(-271,41,-30.1);
    glVertex3f(-279,41,-30.1);
    glVertex3f(-279,30,-30.1);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,30,-30);
    glVertex3f(-271,37,-30);
    glColor3ub(0,9,41);
    glVertex3f(-271,37,18);
    glVertex3f(-271,30,18);
    glEnd();
    //dudukan
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-271,37,-30);
    glColor3ub(88,117,224);
    glVertex3f(-277,37,-30);
    glVertex3f(-277,37,18);
    glColor3ub(0,5,23);
    glVertex3f(-271,37,18);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3ub(0,5,23);
    glVertex3f(-279,49,-30);
    glVertex3f(-279,30,-30);
    glColor3ub(0,9,41);
    glVertex3f(-279,30,18);
    glVertex3f(-279,49,18);
    glEnd();
    //senderan
    glBegin(GL_QUADS);
    glColor3ub(88,117,224);
    glVertex3f(-277,37,-30);
    glColor3ub(0,5,23);
    glVertex3f(-279,49,-30);
    glVertex3f(-279,49,18);
    glColor3ub(88,117,224);
    glVertex3f(-277,37,18);
    glEnd();
    //segitiga penutup kiri
    glBegin(GL_POLYGON);
    glColor3ub(88,117,224);
    glVertex3f(-277,37,18);
    glVertex3f(-279,49,18);
    glVertex3f(-279,37,18);
    glEnd();
    //segitiga penutup kanan
    glBegin(GL_POLYGON);
    glColor3ub(88,117,224);
    glVertex3f(-277,37,-30);
    glVertex3f(-279,49,-30);
    glVertex3f(-279,37,-30);
    glEnd();

    //ABANG
    glPushMatrix();
        glColor3f(1.0,0.0,0.0);
        glTranslated(-317.5,10,127);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //KUNING
    glPushMatrix();
        glColor3f(1.0,1.0,0.0);
        glTranslated(-317.5,7,127);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //IJO
    glPushMatrix();
        glColor3f(0.0,1.0,0.0);
        glTranslated(-317.5,4,127);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //POT
    pot(-115,-40, 45);
    pot(-140,-40,-50);
    pot(-65,-40,-45);
    pot(115,0, 40);
    pot(125,0,-40);

    // pohon
    pohon(245,-49.7,-110);
    pohon(145,-49.7,-110);
    pohon(-155,-49.7,-110);
    pohon(-245,-49.7,-110);
    pot2(225,-40,-20);
    pot2(225,-40,20);

    //VENDING MACHINE
    vending_depan();
    vending_belakang();

    // AC
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            glColor3f(0.95,0.95,0.95);
            glBegin(GL_QUADS); // belakang
                glVertex3f(-270+(i*20),70,-40+(j*25));
                glVertex3f(-260+(i*20),70,-40+(j*25));
                glVertex3f(-260+(i*20),77,-40+(j*25));
                glVertex3f(-270+(i*20),77,-40+(j*25));
            glEnd();
            glBegin(GL_QUADS); // depan
                glVertex3f(-270+(i*20),70,-35+(j*25));
                glVertex3f(-260+(i*20),70,-35+(j*25));
                glVertex3f(-260+(i*20),77,-35+(j*25));
                glVertex3f(-270+(i*20),77,-35+(j*25));
            glEnd(); // kanan
            glColor3f(0.9,0.9,0.9);
            glBegin(GL_QUADS);
                glVertex3f(-270+(i*20),70,-40+(j*25));
                glVertex3f(-270+(i*20),70,-35+(j*25));
                glVertex3f(-270+(i*20),77,-35+(j*25));
                glVertex3f(-270+(i*20),77,-40+(j*25));
            glEnd(); // kiri
            glColor3f(0.98,0.98,0.98);
            glBegin(GL_QUADS);
                glVertex3f(-260+(i*20),70,-40+(j*25));
                glVertex3f(-260+(i*20),70,-35+(j*25));
                glVertex3f(-260+(i*20),77,-35+(j*25));
                glVertex3f(-260+(i*20),77,-40+(j*25));
            glEnd();// atas
            glBegin(GL_QUADS);
                glVertex3f(-260+(i*20),77,-40+(j*25));
                glVertex3f(-270+(i*20),77,-40+(j*25));
                glVertex3f(-270+(i*20),77,-35+(j*25));
                glVertex3f(-260+(i*20),77,-35+(j*25));
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_POLYGON);
                lingkaran(-263+(i*20),73.5,-34.9+(j*25),2);
            glEnd();
        }
    }

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

