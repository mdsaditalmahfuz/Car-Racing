#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include<mmsystem.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")


///angle of tree
float angle = 0.0f;
float rotationSpeed = 1.0f; // speed of rotation
float timeToRotate = 0.0f; // time in seconds until rotation occurs

/// Score
int score = 0,s;

///Distance
float distance = 0.0f,d;

///Road_line
float position_line = -0.0f;
float speed_line = 0.015f;

///tree
float position_tree=2.0f;
float speed_tree =0.01f;

float position_tree2=2.0f;




/// width and height of rectangles
float width = 0.18;
float height = 0.38;

///tree height
float twidth = 0.15;
float theight = 0.30;
///game over dect
int gameover=0;
bool check_collision =true;
void diplay();

// car positions and velocities
///my car 1
float car1X = 0.0, car1Y = -0.8, car1VX = 0.00, car1VY = 0.00;

///opponent Car
//car 2
float car2X = 0.0, car2Y = 2.0, car2VX = 0.00, car2VY = -0.005;

//car 3
float car3X = 0.30, car3Y = 1.0, car3VX = 0.00, car3VY = -0.005;

//car 4
float car4X = -0.30, car4Y = 3.0, car4VX = 0.00, car4VY = -0.005;

//tree
float treeX = -0.50, treeY = 1.0, treeVX = 0.00, treeVY = -0.01;

///function to check collision between two Car
bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return (x1 - w1/2.20 < x2 + w2/2.20 && x1 + w1/2.20 > x2 - w2/2.20 && y1 - h1/2.20 < y2 + h2/2.20 && y1 + h1/2.20 > y2 - h2/2.20);
}

/// Function to draw text
void drawText(char *text, float x, float y) {
    glRasterPos2f(x, y);

    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void drawText1(char *text, float x, float y) {
    glRasterPos2f(x, y);

    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

///Draw text with RGB
float red, green, blue;  // current RGB color values
float time1 = 0;  // current time value

void updateColorWave(int value) {
    // update time value
    time1 += 0.05;

    // calculate new color values using sine waves
    red = (sinf(time1) + 1) / 2;    // values will range from 0 to 1
    green = (sinf(time1 + 2) + 1) / 2;
    blue = (sinf(time1 + 4) + 1) / 2;

    // redraw text with new color
    glutPostRedisplay();

    // set timer for next update
    glutTimerFunc(30, updateColorWave, 0);
}

void drawText3(const char *text, float x, float y) {
    // set color to current RGB values
    glColor3f(red, green, blue);

    // set position for text
    glRasterPos2f(x, y);

    // draw text using glutBitmapCharacter
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text++);
    }
}

// Function to draw score board
void drawScoreBoard() {

glPushMatrix();
  glTranslatef(-0.70,0.78,0.0);
  glScalef(0.56,0.35,0.0);

  glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // white color with 50% opacity
  glBegin(GL_QUADS);
  glVertex2f(-0.45f, -0.45f);
  glColor4f(1.0f, 0.0f, 1.0f, 0.5f); // magenta color with 50% opacity
  glVertex2f(0.45f, -0.45f);
  glColor4f(0.0f, 0.0f, 1.0f, 0.5f); // blue color with 50% opacity
  glVertex2f(0.45f, 0.45f);
  glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // black color with 50% opacity
  glVertex2f(-0.45f, 0.45f);
  glEnd();

  glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // white color with 50% opacity
  glBegin(GL_QUADS);
  glVertex2f(-0.4f, -0.4f);
  glVertex2f(0.4f, -0.4f);
  glVertex2f(0.4f, 0.4f);
  glVertex2f(-0.4f, 0.4f);
  glEnd();
glPopMatrix();
    // Score
    glPushMatrix();
    char scoreText[10];
    sprintf(scoreText,"Score:%d", score);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawText(scoreText,-0.92f, 0.8f);

    // Distance
    char distanceText[20];
    sprintf(distanceText, "Distance: %.1f KM", distance);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawText(distanceText, -0.92f, 0.7f);
    glPopMatrix();
}
///field
void field()
{
    glBegin(GL_POLYGON);
    glColor3f (0.319f, 0.650f, 0.352f);
      glVertex2f(-1.10f,-1.0f);
      glVertex2f(-1.10f, 1.0f);
      glVertex2f(1.10f, 1.0f);
      glVertex2f(1.10f,-1.0f);
    glEnd();

}
///Buiding
void buildingline1()
{   //rooftop lining
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.31161, 0.59309);
    glVertex2f(0.51815, 0.71769);
    glVertex2f(0.73248, 0.59414);
    glVertex2f(0.51921, 0.47098);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.23126, 0.56843);
    glVertex2f(0.51804, 0.39976);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.51804, 0.39976);
    glVertex2f(0.80268, 0.57189);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.51804, 0.39976);
    glVertex2f(0.5133, -0.6239);
    glEnd();

    //window lines vertical
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.30113, 0.48244);
    glVertex2f(0.30077, -0.3496);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.39826, 0.42651);
    glVertex2f(0.39804, -0.38055);
    glEnd();

    //window lines horizontal
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25308, 0.41938);
    glVertex2f(0.47877, 0.29056);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25431, 0.31764);
    glVertex2f(0.47773, 0.19252);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25723, 0.21494);
    glVertex2f(0.4792, 0.10128);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25257, 0.12816);
    glVertex2f(0.48214, 0.02034);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25366, 0.03558);
    glVertex2f(0.47773, -0.06796);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25019, -0.05238);
    glVertex2f(0.48214, -0.15185);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.25019, -0.15095);
    glVertex2f(0.47773, -0.24309);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.24874, -0.23213);
    glVertex2f(0.4792, -0.33139);
    glEnd();

    //window line verical of right side
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.60033, 0.39171);
    glVertex2f(0.60018, -0.37533);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.7, 0.45);
    glVertex2f(0.70033, -0.32611);
    glEnd();

    //window line horizontal of the right side part
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55339, 0.26926);
    glVertex2f(0.75651, 0.38764);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55555, 0.17059);
    glVertex2f(0.75918, 0.28071);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.5544, 0.05689);
    glVertex2f(0.75615, 0.16326);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55513, -0.05652);
    glVertex2f(0.75909, 0.04875);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55638, -0.15034);
    glVertex2f(0.75968, -0.05037);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55601, -0.23324);
    glVertex2f(0.7588, -0.13164);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.55704, -0.31918);
    glVertex2f(0.7588, -0.20923);
    glEnd();
    glPopMatrix();

}

void buildingline()
{
///Building mid join line top

glPushMatrix();
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.7622543681771, 0.2627385323485);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.6396143133619, 0.2618101921158);
        glEnd();
    glPopMatrix();
///Building mid separation line

glPushMatrix();
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.7012910743704, 0.1286319701816);
        glEnd();
    glPopMatrix();
///Building separation line
glPushMatrix();
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.7622827671272, 0.2549267653875);
        glVertex2f(-0.7013684400418, 0.2203113175562);
        glVertex2f(-0.7013684400418, 0.2203113175562);
        glVertex2f(-0.6386219650649, 0.2551139871988);
        glEnd();
    glPopMatrix();
//2
glPushMatrix();
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.7622827671272, 0.2549267653875-0.02);
glVertex2f(-0.7013684400418, 0.2203113175562-0.02);
glVertex2f(-0.7013684400418, 0.2203113175562-0.02);
glVertex2f(-0.6396219650649, 0.2551139871988-0.02);
glEnd();
glPopMatrix();
//3
glPushMatrix();
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.7622827671272, 0.2549267653875-0.04);
glVertex2f(-0.7013684400418, 0.2203113175562-0.04);
glVertex2f(-0.7013684400418, 0.2203113175562-0.04);
glVertex2f(-0.6396219650649, 0.2551139871988-0.04);
glEnd();
glPopMatrix();
//4
glPushMatrix();
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.7622827671272, 0.2549267653875-0.06);
glVertex2f(-0.7013684400418, 0.2203113175562-0.06);
glVertex2f(-0.7013684400418, 0.2203113175562-0.06);
glVertex2f(-0.6396219650649, 0.2551139871988-0.06);
glEnd();
glPopMatrix();
//5
glPushMatrix();
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.7622827671272, 0.2549267653875-0.092);
glVertex2f(-0.7013684400418, 0.2203113175562-0.092);
glVertex2f(-0.7013684400418, 0.2203113175562-0.092);
glVertex2f(-0.6396219650649, 0.2551139871988-0.092);
glEnd();
glPopMatrix();
}
void windows1()
{
  ///Windows Left
  glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.634, 0.786, 0.880);
    glVertex2f(-0.6911159546702, 0.2196767086464);
    glVertex2f(-0.6912918486039, 0.2095580887889);
    glVertex2f(-0.6779755277809, 0.2173823483959);
    glVertex2f(-0.6779808282831, 0.2271342265823);

    glVertex2f(-0.6760900657306, 0.2285888643319);
    glVertex2f(-0.67, 0.232);
    glVertex2f(-0.67, 0.222);
    glVertex2f(-0.6759157535877, 0.2185223380819);
    glEnd();
    glPopMatrix();

    ///Windows Left2
  glPushMatrix();
   glTranslatef(0.025f,0.014f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.634, 0.786, 0.880);
    glVertex2f(-0.6911159546702, 0.2196767086464);
    glVertex2f(-0.6912918486039, 0.2095580887889);
    glVertex2f(-0.6779755277809, 0.2173823483959);
    glVertex2f(-0.6779808282831, 0.2271342265823);

    glVertex2f(-0.6760900657306, 0.2285888643319);
    glVertex2f(-0.67, 0.232);
    glVertex2f(-0.67, 0.222);
    glVertex2f(-0.6759157535877, 0.2185223380819);
    glEnd();
    glPopMatrix();
//lines
     ///Windows Left
  glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6911159546702, 0.2196767086464);
    glVertex2f(-0.6912918486039, 0.2095580887889);
    glVertex2f(-0.6779755277809, 0.2173823483959);
    glVertex2f(-0.6779808282831, 0.2271342265823);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6760900657306, 0.2285888643319);
    glVertex2f(-0.67, 0.232);
    glVertex2f(-0.67, 0.222);
    glVertex2f(-0.6759157535877, 0.2185223380819);
    glEnd();
    glPopMatrix();

    ///Windows Left2
  glPushMatrix();
  glTranslatef(0.025f,0.014f,0.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6911159546702, 0.2196767086464);
    glVertex2f(-0.6912918486039, 0.2095580887889);
    glVertex2f(-0.6779755277809, 0.2173823483959);
    glVertex2f(-0.6779808282831, 0.2271342265823);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6760900657306, 0.2285888643319);
    glVertex2f(-0.67, 0.232);
    glVertex2f(-0.67, 0.222);
    glVertex2f(-0.6759157535877, 0.2185223380819);
    glEnd();
    glPopMatrix();

}

void windows2()
{
///Windows Right
  glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.634, 0.786, 0.880);
    glVertex2f(-0.7239036818032, 0.2273667058993);
    glVertex2f(-0.7105588764195, 0.2195305120403);
    glVertex2f(-0.7105976694584, 0.2095994940803);
    glVertex2f(-0.7241364400366, 0.2170865505892);

    glVertex2f(-0.7318977470798, 0.2319760557677);
    glVertex2f(-0.7261494913007, 0.2286536693999);
    glVertex2f(-0.7263604364669, 0.2190556643377);
    glVertex2f(-0.7319504833713, 0.2219034240814);
    glEnd();
    glPopMatrix();

///Windows Right2
  glPushMatrix();
  glTranslatef(-0.025f,0.014f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.634, 0.786, 0.880);
    glVertex2f(-0.7239036818032, 0.2273667058993);
    glVertex2f(-0.7105588764195, 0.2195305120403);
    glVertex2f(-0.7105976694584, 0.2095994940803);
    glVertex2f(-0.7241364400366, 0.2170865505892);

    glVertex2f(-0.7318977470798, 0.2319760557677);
    glVertex2f(-0.7261494913007, 0.2286536693999);
    glVertex2f(-0.7263604364669, 0.2190556643377);
    glVertex2f(-0.7319504833713, 0.2219034240814);
    glEnd();
    glPopMatrix();

//lines
///Windows Right
  glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.7239036818032, 0.2273667058993);
    glVertex2f(-0.7105588764195, 0.2195305120403);
    glVertex2f(-0.7105976694584, 0.2095994940803);
    glVertex2f(-0.7241364400366, 0.2170865505892);
     glEnd();


    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7318977470798, 0.2319760557677);
    glVertex2f(-0.7261494913007, 0.2286536693999);
    glVertex2f(-0.7263604364669, 0.2190556643377);
    glVertex2f(-0.7319504833713, 0.2219034240814);
    glEnd();
    glPopMatrix();

    ///Windows Right2
  glPushMatrix();
  glTranslatef(-0.025f,0.014f,0.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.7239036818032, 0.2273667058993);
    glVertex2f(-0.7105588764195, 0.2195305120403);
    glVertex2f(-0.7105976694584, 0.2095994940803);
    glVertex2f(-0.7241364400366, 0.2170865505892);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7318977470798, 0.2319760557677);
    glVertex2f(-0.7261494913007, 0.2286536693999);
    glVertex2f(-0.7263604364669, 0.2190556643377);
    glVertex2f(-0.7319504833713, 0.2219034240814);
    glEnd();
    glPopMatrix();


}

void building()
{
///VSTUR
glPushMatrix();
glScalef(1.80f,2.50f,0.0f);
glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.920, 0.913, 0.837);
        glVertex2f(-0.7413848503055, 0.2741324611712);
        glVertex2f(-0.7622543681771, 0.2627385323485);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.6396143133619, 0.2618101921158);
        glVertex2f(-0.66, 0.274);
        glEnd();
    glPopMatrix();

///TUZW
glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.670, 0.668, 0.650);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.6396143133619, 0.2618101921158);
        glVertex2f(-0.6396406403053, 0.1637211409775);
        glVertex2f(-0.7012910743704, 0.1286319701816);
        glEnd();
    glPopMatrix();
///TWA1S
glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.956, 0.941, 0.960);
        glVertex2f(-0.7013616933633, 0.226804777264);
        glVertex2f(-0.7012910743704, 0.1286319701816);
        glVertex2f(-0.7621536284236, 0.1636209540082);
        glVertex2f(-0.7622543681771, 0.2627385323485);
        glEnd();
    glPopMatrix();

///NMLJK (Second top)
    glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.300, 0.234, 0.320);
        glVertex2f(-0.67600225, 0.286769217);
        glVertex2f(-0.6599800309097, 0.2772402839973);
        glVertex2f(-0.7012637988685, 0.2532645185129);
        glVertex2f(-0.7413766946969, 0.2775200773794);
        glVertex2f(-0.7259182161594, 0.2864199996639);
        glEnd();
    glPopMatrix();

///LMQP
    glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.370, 0.272, 0.400);
        glVertex2f(-0.7012637988685, 0.2532645185129);
        glVertex2f(-0.6599800309097, 0.2772402839973);
        glVertex2f(-0.6600543876247, 0.2606163400757);
        glVertex2f(-0.7012637988685, 0.2371911110163);
        glEnd();
    glPopMatrix();
///JLPO
    glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.364, 0.213, 0.410);
        glVertex2f(-0.7413766946969, 0.2775200773794);
        glVertex2f(-0.7012637988685, 0.2532645185129);
        glVertex2f(-0.7012637988685, 0.2371911110163);
        glVertex2f(-0.7415012552189, 0.2602764076892);
        glEnd();
    glPopMatrix();

///CDFE(Top of building)
   glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.920, 0.909, 0.791);
    glVertex2f(-0.7258525989199f, 0.2890771142638f);
    glVertex2f(-0.7008346654357f, 0.3034295076837f);
    glVertex2f(-0.6760185098031f, 0.2891339874463f);
    glVertex2f(-0.7012296854381f, 0.2747247208439f);
    glEnd();
    glPopMatrix();


///FEGH
   glPushMatrix();
     glBegin(GL_QUADS);
    glColor3f(0.840, 0.823, 0.823);
    glVertex2f(-0.7012296854381f, 0.2747247208439f);
    glVertex2f(-0.6760185098031f, 0.2891339874463f);
    glVertex2f(-0.6759484052857, 0.278938267536);
    glVertex2f(-0.7009663387699, 0.2639275074455);
    glEnd();
     glPopMatrix();

///KFHI
   glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.956, 0.941, 0.960);
    glVertex2f(-0.7258525989199, 0.2890771142638);
    glVertex2f(-0.7012296854381, 0.2747247208439);
    glVertex2f(-0.7009663387699, 0.2639275074455);
    glVertex2f(-0.7261159455882, 0.2784115741995);
    glEnd();
    glPopMatrix();
///Buildings windows
//1
glPushMatrix();
     windows1();
     windows2();
glPopMatrix();
//2
glPushMatrix();
glTranslatef(0.0f,-0.02f,0.0f);
     windows1();
     windows2();
glPopMatrix();

//3
glPushMatrix();
glTranslatef(0.0f,-0.04f,0.0f);
     windows1();
     windows2();
glPopMatrix();

//4
glPushMatrix();
glTranslatef(0.0f,-0.063f,0.0f);
     windows1();
     windows2();
glPopMatrix();

buildingline();
glPopMatrix();
}
void building1()
{
    glPushMatrix();
    glScalef(0.3f, 0.4f, 0.0f);

    //layer 1 top
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.23126, 0.56843);
    glVertex2f(0.51804, 0.39976);
    glVertex2f(0.80268, 0.57189);
    glVertex2f(0.51817, 0.73987);
    glEnd();

    //layer 2 left side
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.23126, 0.56843);
    glVertex2f(0.51804, 0.39976);
    glVertex2f(0.5133, -0.6239);
    glVertex2f(0.21774, -0.47148);
    glEnd();

    //layer3 right side
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.51804, 0.39976);
    glVertex2f(0.80268, 0.57189);
    glVertex2f(0.78939, -0.4686);
    glVertex2f(0.5133, -0.6239);
    glEnd();

    //windows from left
    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(0.25693, 0.50264);
    glVertex2f(0.48865, 0.37199);
    glVertex2f(0.48618, -0.42176);
    glVertex2f(0.252, -0.32809);
    glEnd();

    //door of left side
    glBegin(GL_QUADS);
    glColor3f(0.2196f, 0.10196f, 0.13725f);
    glVertex2f(0.3198, -0.39453);
    glVertex2f(0.39854, -0.42554);
    glVertex2f(0.40037, -0.56353);
    glVertex2f(0.32008, -0.52179);
    glEnd();
    //windows from right side
    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(0.55028, 0.36953);
    glVertex2f(0.77213, 0.50511);
    glVertex2f(0.76259, -0.29639);
    glVertex2f(0.55274, -0.40697);
    glEnd();
    buildingline1();
    glPopMatrix();

}

void building2()
{
    glPushMatrix();
    glScalef(0.3f, 0.4f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.94874, 0.64346);
    glVertex2f(-0.12938, 0.6397);
    glVertex2f(-0.13181, 0.27081);
    glVertex2f(-0.95294, 0.27381);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.95294, 0.27381);
    glVertex2f(-0.13181, 0.27081);
    glVertex2f(0.13403, 0.07077);
    glVertex2f(-0.41912, 0.05705);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.12938, 0.6397);
    glVertex2f(0.13299, 0.4296);
    glVertex2f(0.13403, 0.07077);
    glVertex2f(-0.13181, 0.27081);
    glEnd();

    //2nd joint building rooftop
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.32102, 0.19288);
    glVertex2f(-0.32464, -0.10051);
    glVertex2f(-0.56194, -0.10001);
    glVertex2f(-0.56501, 0.19036);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.32102, 0.19288);
    glVertex2f(-0.20353, 0.0971);
    glVertex2f(-0.20298, -0.10001);
    glVertex2f(-0.32464, -0.10051);
    glEnd();

    //3rd joined building rooftop
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.92335, -0.10115);
    glVertex2f(-0.09106, -0.09932);
    glVertex2f(-0.08949, -0.48824);
    glVertex2f(-0.92653, -0.48089);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.92653, -0.48089);
    glVertex2f(-0.08949, -0.48824);
    glVertex2f(0.10552, -0.58922);
    glVertex2f(-0.56642, -0.59223);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.09106, -0.09932);
    glVertex2f(0.10382, -0.2985);
    glVertex2f(0.10552, -0.58922);
    glVertex2f(-0.08949, -0.48824);
    glEnd();
    //windows
    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(-0.73667, 0.24084);
    glVertex2f(-0.16034, 0.23813);
    glVertex2f(0.039, 0.09303);
    glVertex2f(-0.43332, 0.08715);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(-0.1037, 0.57931);
    glVertex2f(-0.10316, 0.28252);
    glVertex2f(0.1063, 0.11801);
    glVertex2f(0.10643, 0.42089);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(-0.31008, -0.09036);
    glVertex2f(-0.30954, 0.15871);
    glVertex2f(-0.21993, 0.09456);
    glVertex2f(-0.22005, -0.09094);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(-0.76713, -0.50836);
    glVertex2f(-0.10241, -0.51653);
    glVertex2f(0.00761, -0.57236);
    glVertex2f(-0.56432, -0.5751);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.573f, 0.722f, 0.8196f);
    glVertex2f(-0.06, -0.46);
    glVertex2f(-0.0596, -0.18102);
    glVertex2f(0.07676, -0.31447);
    glVertex2f(0.07335, -0.53719);
    glEnd();

   glPopMatrix();
}

///Road
void road()
{
    glPushMatrix();
     glBegin(GL_POLYGON);
      glColor3f (0.02f, 0.01f, 0.04f);
      glVertex2f(-0.45f,-1.0f);
      glVertex2f(-0.45f,1.0f);
      glVertex2f(0.45f, 1.0f);
      glVertex2f(0.45f,-1.0f);
    glEnd();
    glPopMatrix();


}
///Road border
void line()
{
    glPushMatrix();
    glTranslatef(-0.08f,0.0f,0.0f);
    glColor3f (1.0f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.37f,1.0f);
    glVertex2f(-0.33f,1.0f);
    glVertex2f(-0.33f,-1.0f);
    glVertex2f(-0.37f,-1.0f);
    glEnd();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(0.8f,0.0f,0.0f);
    glColor3f (1.0f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.37f,1.0f);
    glVertex2f(-0.33f,1.0f);
    glVertex2f(-0.33f,-1.0f);
    glVertex2f(-0.37f,-1.0f);
    glEnd();
    glPopMatrix();
}

///Chicken
void drawCircle(GLfloat x, GLfloat y, GLfloat radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= 360; i++) {
        glVertex2f(x + radius * cos(i * 3.14159 / 180), y + radius * sin(i * 3.14159 / 180));
    }
    glEnd();
}


void drawChicken() {
   // Draw chicken body
    glColor3f(0.7, 0.0, 0.0); // dark red color
    drawCircle(0.0, 0.0, 0.5); // body
    drawCircle(-0.4, 0.2, 0.2); // left wing
    drawCircle(0.4, 0.2, 0.2); // right wing
    drawCircle(0.0, -0.6, 0.2); // lower body

    // Draw chicken eyes
    glColor3f(1.0, 0.0, 0.0); // red color
    drawCircle(-0.15, 0.1, 0.05); // left eye
    drawCircle(0.15, 0.1, 0.05); // right eye
    glColor3f(1.0, 1.0, 0.0); // glowing yellow color
    drawCircle(-0.12, 0.13, 0.02); // left pupil
    drawCircle(0.12, 0.13, 0.02); // right pupil

    // Draw chicken beak with fangs
    glColor3f(1.0, 0.5, 0.0); // orange color
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.05);
    glVertex2f(-0.1, -0.05);
    glVertex2f(0.1, -0.05);
    glEnd();
    glColor3f(1.0, 1.0, 1.0); // white color
    drawCircle(-0.05, -0.05, 0.02); // left fang
    drawCircle(0.05, -0.05, 0.02); // right fang

    // Draw chicken feathers
    glColor3f(0.3, 0.0, 0.0); // dark red color
    drawCircle(-0.35, 0.35, 0.08); // left feather
    drawCircle(0.35, 0.35, 0.08); // right feather
    drawCircle(-0.2, 0.4, 0.05); // top left feather
    drawCircle(0.2, 0.4, 0.05); // top right feather

    // Draw chicken wounds
    glColor3f(0.5, 0.0, 0.0); // dark red color
    drawCircle(0.1, -0.35, 0.05); // left wound
    drawCircle(-0.1, -0.45, 0.06); // right wound
    drawCircle(0.0, -0.25, 0.03); // bottom wound

    // Draw chicken legs
    glColor3f(1.0, 0.5, 0.0); // orange color
    glBegin(GL_LINES);
    glVertex2f(-0.2, -0.7);
    glVertex2f(-0.1, -0.6);
    glVertex2f(0.2, -0.7);
    glVertex2f(0.1, -0.6);
    glEnd();

}

///treee
void treeSphere(){
	// Draw trunk
    glPushMatrix();
    glTranslated(0.13f,-.2f,0);
    glBegin(GL_POLYGON);
    glColor3f(0.3019f,0.2509f,0.1960f);
    glVertex2f(.1f,.0f);
    glVertex2f(.2f,0);
    glVertex2f(.2f,.4f);
    glVertex2f(.1f,.4f);
    glEnd();
    glPopMatrix();

    // Draw foliage
    glColor3f(0.2078f,0.32156f,0.17647f);
    glPushMatrix();
    glTranslated(.2,.3,0);
    glutSolidSphere(.15,20,20);
    glPopMatrix();

    glColor3f(0.2078f,0.32156f,0.17647f);
    glPushMatrix();
    glTranslated(.35,.3,0);
    glutSolidSphere(.15,20,20);
    glPopMatrix();

    glColor3f(0.2078f,0.32156f,0.17647f);
    glPushMatrix();
    glTranslated(.3,.35,0);
    glutSolidSphere(.15,20,20);
    glPopMatrix();

    // Draw branches
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.3f, 0.2f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.23f, 0.25f);
    glVertex2f(0.3f, 0.35f);
    glVertex2f(0.27f, 0.28f);
    glVertex2f(0.35f, 0.35f);
    glEnd();

    // Draw leaves
    glBegin(GL_POINTS);
    glColor3f(0.3f, 0.6f, 0.3f);
    glVertex2f(0.18f, 0.25f);
    glVertex2f(0.22f, 0.3f);
    glVertex2f(0.24f, 0.32f);
    glVertex2f(0.28f, 0.35f);
    glVertex2f(0.33f, 0.36f);
    glVertex2f(0.38f, 0.35f);
    glEnd();
}
///tree1
void tree()
{
glPushMatrix();
glTranslatef(-0.03f,-0.1f,0.0f);
      glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.3019f,0.2509f,0.1960f);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.05f,0.0f);
	glVertex2f(0.05f,0.1f);
	glVertex2f(0.0f,0.1f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1090f,0.4f,0.0156f);
	glVertex2f(-.15f,.1f);
	glVertex2f(.2f,.1f);
	glVertex2f(0.025f,.2f);
	glEnd();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.0f,.05f,0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1490f,0.3f,0.0156f);
	glVertex2f(-.1f,.1f);
	glVertex2f(.15f,.1f);
	glVertex2f(0.025f,.2f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,.1f,0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.2490f,0.2f,0.0156f);
	glVertex2f(-.05f,.1f);
	glVertex2f(.1f,.1f);
	glVertex2f(0.025f,.2f);
	glEnd();
	glPopMatrix();
glPopMatrix();
}

void update1(int value)
{

    if(position_tree <-12.2)
        position_tree =1.2f;

    position_tree -= speed_tree;

	glutPostRedisplay();

	glutTimerFunc(5, update1, 0);
}

void all_tree()
{
    glPushMatrix();
    glTranslatef(-0.8f,position_tree+0.78, 0.0f);
    glScalef(0.5f,1.0f,0.0f);
    tree();
    glPopMatrix();


    ///moving Building
    glPushMatrix();
    glTranslatef(0.6f,position_tree+0.3, 0.0f);
    building1();
    glPushMatrix();
    glScalef(0.5f,1.0f,0.0f);
    tree();
    glPopMatrix();
    building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.88f,position_tree+0.4, 0.0f);
    glScalef(0.5f,1.0f,0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.72f,position_tree+0.5, 0.0f);
     glScalef(0.5f,1.0f,0.0f);
    tree();
    glPopMatrix();

///moving Building
    glPushMatrix();
    glTranslatef(0.7f,position_tree+2.5, 0.0f);
    building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9f,position_tree+2.7, 0.0f);
    glScalef(0.5f,1.0f,0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.78f,position_tree+2.90, 0.0f);
     glScalef(0.5f,1.0f,0.0f);
     building2();
     tree();
    glPopMatrix();

///moving Building

    glPushMatrix();
    glTranslatef(0.4f,position_tree+2.2, 0.0f);
    building();
    glPopMatrix();



///moving Building


    glPushMatrix();
    glTranslatef(0.7f,position_tree+1.8, 0.0f);
    building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.78f,position_tree+1.60, 0.0f);
     glScalef(0.5f,1.0f,0.0f);
    tree();
     glPushMatrix();
     glScalef(0.5f,0.5f,0.0f);
    treeSphere();
     glPopMatrix();
    glPopMatrix();

 glPushMatrix();
    glTranslatef(-0.9f,position_tree+1.5, 0.0f);
    glScalef(0.5f,1.0f,0.0f);
    tree();
    glPushMatrix();
    glTranslatef(0.0f,-0.5f, 0.0f);
    building2();
    glPopMatrix();
    building1();
 glPopMatrix();

}

///Road_line
void update(int value)
{

    if(position_line <-1.90)
        position_line =-1.0f;

    position_line -= speed_line;

	glutPostRedisplay();

	glutTimerFunc(5, update, 0);
}

void road_line()
{

    glPushMatrix();
    glTranslatef(0.0f,2.1f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f,1.8f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
  glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f,1.5f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f,1.2f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.90f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.60f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.30f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();


     glPushMatrix();
    glTranslatef(0.0f,-0.30f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(0.0f,-0.60f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();


     glPushMatrix();
    glTranslatef(0.0f,-0.90f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(0.0f,-1.2f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();


     glPushMatrix();
    glTranslatef(0.0f,-1.5f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();

      glPushMatrix();
    glTranslatef(0.0f,-1.8f, 0.0f);
    glBegin(GL_POLYGON);
      glColor3f (1.0f, 1.0f,0.0f);
      glVertex2f(-0.01f,1.0f);
      glVertex2f(0.01f,1.0f);
      glVertex2f(0.01f,0.81f);
      glVertex2f(-0.01f,0.81f);
    glEnd();
    glPopMatrix();
}
void all_road_line()
{
     glPushMatrix();
     glTranslatef(-0.15f,position_line, 0.0f);
    road_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f,position_line, 0.0f);
    road_line();
    glPopMatrix();
}


///Car

void car()
{
    glPushMatrix();
    glTranslatef(-0.17f, -0.27f, 0.0f);

    // ===== Shadow =====
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.11f, 0.08f);
        glVertex2f(0.23f, 0.08f);
        glVertex2f(0.25f, 0.10f);
        glVertex2f(0.25f, 0.42f);
        glVertex2f(0.23f, 0.45f);
        glVertex2f(0.11f, 0.45f);
        glVertex2f(0.09f, 0.42f);
        glVertex2f(0.09f, 0.10f);
    glEnd();

    // ===== Wheels =====
    glColor3f(0.05f, 0.05f, 0.05f);
    drawCircle(0.095f, 0.15f, 0.018f);
    drawCircle(0.245f, 0.15f, 0.018f);
    drawCircle(0.095f, 0.38f, 0.018f);
    drawCircle(0.245f, 0.38f, 0.018f);

    // wheel rim
    glColor3f(0.75f, 0.75f, 0.75f);
    drawCircle(0.095f, 0.15f, 0.008f);
    drawCircle(0.245f, 0.15f, 0.008f);
    drawCircle(0.095f, 0.38f, 0.008f);
    drawCircle(0.245f, 0.38f, 0.008f);

    // ===== Main Lamborghini Body =====
    glColor3f(0.70f, 0.95f, 0.15f);   // Lambo pink
    glBegin(GL_POLYGON);
        glVertex2f(0.17f, 0.47f);   // nose
        glVertex2f(0.21f, 0.45f);
        glVertex2f(0.24f, 0.40f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(0.25f, 0.13f);
        glVertex2f(0.23f, 0.10f);
        glVertex2f(0.20f, 0.08f);
        glVertex2f(0.14f, 0.08f);
        glVertex2f(0.11f, 0.10f);
        glVertex2f(0.09f, 0.13f);
        glVertex2f(0.09f, 0.33f);
        glVertex2f(0.10f, 0.40f);
        glVertex2f(0.13f, 0.45f);
    glEnd();

    // ===== inner body =====
    glColor3f(0.58f, 0.83f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(0.17f, 0.44f);
        glVertex2f(0.20f, 0.42f);
        glVertex2f(0.22f, 0.38f);
        glVertex2f(0.23f, 0.32f);
        glVertex2f(0.23f, 0.15f);
        glVertex2f(0.21f, 0.12f);
        glVertex2f(0.19f, 0.11f);
        glVertex2f(0.15f, 0.11f);
        glVertex2f(0.13f, 0.12f);
        glVertex2f(0.11f, 0.15f);
        glVertex2f(0.11f, 0.32f);
        glVertex2f(0.12f, 0.38f);
        glVertex2f(0.14f, 0.42f);
    glEnd();

    // ===== windshield =====
    glColor3f(0.08f, 0.12f, 0.18f);
    glBegin(GL_POLYGON);
        glVertex2f(0.14f, 0.36f);
        glVertex2f(0.20f, 0.36f);
        glVertex2f(0.19f, 0.27f);
        glVertex2f(0.15f, 0.27f);
    glEnd();

    // ===== rear glass / engine cover =====
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.14f, 0.23f);
        glVertex2f(0.20f, 0.23f);
        glVertex2f(0.19f, 0.14f);
        glVertex2f(0.15f, 0.14f);
    glEnd();

    // ===== center line =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.17f, 0.12f);
        glVertex2f(0.17f, 0.44f);
    glEnd();

    // ===== side vent left =====
    glBegin(GL_POLYGON);
        glVertex2f(0.11f, 0.22f);
        glVertex2f(0.12f, 0.19f);
        glVertex2f(0.12f, 0.28f);
        glVertex2f(0.11f, 0.26f);
    glEnd();

    // ===== side vent right =====
    glBegin(GL_POLYGON);
        glVertex2f(0.22f, 0.19f);
        glVertex2f(0.23f, 0.22f);
        glVertex2f(0.23f, 0.26f);
        glVertex2f(0.22f, 0.28f);
    glEnd();

    // ===== headlights =====
    glColor3f(1.0f, 1.0f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.14f, 0.41f);
        glVertex2f(0.12f, 0.42f);
        glVertex2f(0.145f, 0.44f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.20f, 0.41f);
        glVertex2f(0.22f, 0.42f);
        glVertex2f(0.195f, 0.44f);
    glEnd();

    // ===== tail lights =====
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.13f, 0.095f);
        glVertex2f(0.15f, 0.095f);
        glVertex2f(0.15f, 0.11f);
        glVertex2f(0.13f, 0.11f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.19f, 0.095f);
        glVertex2f(0.21f, 0.095f);
        glVertex2f(0.21f, 0.11f);
        glVertex2f(0.19f, 0.11f);
    glEnd();

    // ===== roof small highlight =====
    glColor3f(0.85f, 1.0f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(0.155f, 0.35f);
        glVertex2f(0.185f, 0.35f);
        glVertex2f(0.18f, 0.30f);
        glVertex2f(0.16f, 0.30f);
    glEnd();

    // ===== border =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.17f, 0.47f);
        glVertex2f(0.21f, 0.45f);
        glVertex2f(0.24f, 0.40f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(0.25f, 0.13f);
        glVertex2f(0.23f, 0.10f);
        glVertex2f(0.20f, 0.08f);
        glVertex2f(0.14f, 0.08f);
        glVertex2f(0.11f, 0.10f);
        glVertex2f(0.09f, 0.13f);
        glVertex2f(0.09f, 0.33f);
        glVertex2f(0.10f, 0.40f);
        glVertex2f(0.13f, 0.45f);
    glEnd();

    glPopMatrix();
}

void car1()
{
//down body
glPushMatrix();

glRotatef(180,0.0f,0.0f,0.0f);
glTranslatef(-0.17f,-0.27f, 0.0f);
glBegin(GL_POLYGON);
      glColor3f(1.0f,1.9f,0.42f);
      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.25f,0.08f);
      glVertex2f(0.09f,0.08f);
 glEnd();
//mid body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
glEnd();
//uper body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.09f,0.46f);
      glVertex2f(0.25f,0.46f);
 glEnd();
//windows
glBegin(GL_POLYGON);
//1 back
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.11f,0.14f);
      glVertex2f(0.23f,0.14f);
      glVertex2f(0.24f,0.12f);
      glVertex2f(0.22f,0.11f);
      glVertex2f(0.123f,0.11f);
      glVertex2f(0.10f,0.12f);
 glEnd();

 glBegin(GL_POLYGON);
//2 back right small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.14f);
      glVertex2f(0.25f,0.19f);
      glVertex2f(0.23f,0.19f);
      glVertex2f(0.23f,0.16f);

 glEnd();
 glBegin(GL_POLYGON);
//3 back left small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.14f);
      glVertex2f(0.09f,0.19f);
      glVertex2f(0.11f,0.19f);
      glVertex2f(0.11f,0.16f);

 glEnd();

 glEnd();
 glBegin(GL_POLYGON);
//4 back left big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.21f);
      glVertex2f(0.09f,0.33f);
      glVertex2f(0.11f,0.29f);
      glVertex2f(0.11f,0.21f);

 glEnd();

 glBegin(GL_POLYGON);
//4 back Right big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.21f);
      glVertex2f(0.25f,0.33f);
      glVertex2f(0.23f,0.29f);
      glVertex2f(0.23f,0.21f);
 glEnd();

 glBegin(GL_POLYGON);
//5 Fornt
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.33f);
      glVertex2f(0.11f,0.33f);
      glVertex2f(0.10f,0.34f);
       glVertex2f(0.09f,0.38f);
       glVertex2f(0.25f,0.38f);
       glVertex2f(0.24f,0.34f);
 glEnd();

  glBegin(GL_POLYGON);
//6  Right light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.43f);
      glVertex2f(0.25f,0.43f);
      glVertex2f(0.23f,0.45f);

 glEnd();

 glBegin(GL_POLYGON);
//7 left light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.12f,0.43f);
      glVertex2f(0.10f,0.43f);
      glVertex2f(0.12f,0.45f);
 glEnd();
 glPopMatrix();
}


void car2()
{
//down body
glPushMatrix();

glRotatef(180,0.0f,0.0f,0.0f);
glTranslatef(-0.17f,-0.27f, 0.0f);
glBegin(GL_POLYGON);
     glColor3f(1.92f,0.14f,0.260f);

      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.25f,0.08f);
      glVertex2f(0.09f,0.08f);
 glEnd();
//mid body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
glEnd();
//uper body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.09f,0.46f);
      glVertex2f(0.25f,0.46f);
 glEnd();
//windows
glBegin(GL_POLYGON);
//1 back
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.11f,0.14f);
      glVertex2f(0.23f,0.14f);
      glVertex2f(0.24f,0.12f);
      glVertex2f(0.22f,0.11f);
      glVertex2f(0.123f,0.11f);
      glVertex2f(0.10f,0.12f);
 glEnd();

 glBegin(GL_POLYGON);
//2 back right small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.14f);
      glVertex2f(0.25f,0.19f);
      glVertex2f(0.23f,0.19f);
      glVertex2f(0.23f,0.16f);

 glEnd();
 glBegin(GL_POLYGON);
//3 back left small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.14f);
      glVertex2f(0.09f,0.19f);
      glVertex2f(0.11f,0.19f);
      glVertex2f(0.11f,0.16f);

 glEnd();

 glEnd();
 glBegin(GL_POLYGON);
//4 back left big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.21f);
      glVertex2f(0.09f,0.33f);
      glVertex2f(0.11f,0.29f);
      glVertex2f(0.11f,0.21f);

 glEnd();

 glBegin(GL_POLYGON);
//4 back Right big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.21f);
      glVertex2f(0.25f,0.33f);
      glVertex2f(0.23f,0.29f);
      glVertex2f(0.23f,0.21f);
 glEnd();

 glBegin(GL_POLYGON);
//5 Fornt
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.33f);
      glVertex2f(0.11f,0.33f);
      glVertex2f(0.10f,0.34f);
       glVertex2f(0.09f,0.38f);
       glVertex2f(0.25f,0.38f);
       glVertex2f(0.24f,0.34f);
 glEnd();

  glBegin(GL_POLYGON);
//6  Right light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.43f);
      glVertex2f(0.25f,0.43f);
      glVertex2f(0.23f,0.45f);

 glEnd();

 glBegin(GL_POLYGON);
//7 left light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.12f,0.43f);
      glVertex2f(0.10f,0.43f);
      glVertex2f(0.12f,0.45f);
 glEnd();
 glPopMatrix();
}

void car3()
{
//down body
glPushMatrix();

glRotatef(180,0.0f,0.0f,0.0f);
glTranslatef(-0.17f,-0.27f, 0.0f);
glBegin(GL_POLYGON);
      //glColor3f(0.58f,0.42f,0.27f);

      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.25f,0.08f);
      glVertex2f(0.09f,0.08f);
 glEnd();
//mid body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.10f);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.08f,0.10f);
      glVertex2f(0.09f,0.09f);
      glVertex2f(0.25f,0.09f);
glEnd();
//uper body
glBegin(GL_POLYGON);
      glVertex2f(0.26f,0.44f);
      glVertex2f(0.25f,0.45f);
      glVertex2f(0.09f,0.45f);
      glVertex2f(0.08f,0.44f);
      glVertex2f(0.09f,0.46f);
      glVertex2f(0.25f,0.46f);
 glEnd();
//windows
glBegin(GL_POLYGON);
//1 back
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.11f,0.14f);
      glVertex2f(0.23f,0.14f);
      glVertex2f(0.24f,0.12f);
      glVertex2f(0.22f,0.11f);
      glVertex2f(0.123f,0.11f);
      glVertex2f(0.10f,0.12f);
 glEnd();

 glBegin(GL_POLYGON);
//2 back right small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.14f);
      glVertex2f(0.25f,0.19f);
      glVertex2f(0.23f,0.19f);
      glVertex2f(0.23f,0.16f);

 glEnd();
 glBegin(GL_POLYGON);
//3 back left small
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.14f);
      glVertex2f(0.09f,0.19f);
      glVertex2f(0.11f,0.19f);
      glVertex2f(0.11f,0.16f);

 glEnd();

 glEnd();
 glBegin(GL_POLYGON);
//4 back left big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.09f,0.21f);
      glVertex2f(0.09f,0.33f);
      glVertex2f(0.11f,0.29f);
      glVertex2f(0.11f,0.21f);

 glEnd();

 glBegin(GL_POLYGON);
//4 back Right big
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.25f,0.21f);
      glVertex2f(0.25f,0.33f);
      glVertex2f(0.23f,0.29f);
      glVertex2f(0.23f,0.21f);
 glEnd();

 glBegin(GL_POLYGON);
//5 Fornt
      glColor3f (0.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.33f);
      glVertex2f(0.11f,0.33f);
      glVertex2f(0.10f,0.34f);
       glVertex2f(0.09f,0.38f);
       glVertex2f(0.25f,0.38f);
       glVertex2f(0.24f,0.34f);
 glEnd();

  glBegin(GL_POLYGON);
//6  Right light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.23f,0.43f);
      glVertex2f(0.25f,0.43f);
      glVertex2f(0.23f,0.45f);

 glEnd();

 glBegin(GL_POLYGON);
//7 left light
      glColor3f (1.0f, 1.0f,1.0f);
      glVertex2f(0.12f,0.43f);
      glVertex2f(0.10f,0.43f);
      glVertex2f(0.12f,0.45f);
 glEnd();
 glPopMatrix();
}

///My car and oppnent car

void cars()
{

    // draw car 1
    glPushMatrix();
     //glColor3f(1.0, 0.0, 0.0);
    glTranslatef(car1X, car1Y, 0.0);
    //glRectf(-width/2.0, -height/2.0, width/2.0, height/2.0);
     car();
    glPopMatrix();

    // draw car 2
    glPushMatrix();
    //glColor3f(0.0, 1.0, 0.0);
    glTranslatef(car2X, car2Y, 0.0);
    //glRectf(-width/2.0, -height/2.0, width/2.0, height/2.0);
    car1();
    glPopMatrix();

     // draw car 3
    glPushMatrix();
    //glColor3f(1.0, 0.0, 0.0);
    glTranslatef(car3X, car3Y, 0.0);
    //glRectf(-width/2.0, -height/2.0, width/2.0, height/2.0);
    car2();
    glPopMatrix();

     // draw car 4
    glPushMatrix();
    //glColor3f(1.0, 1.0, 0.0);
    glTranslatef(car4X, car4Y, 0.0);
    //glRectf(-width/2.0, -height/2.0, width/2.0, height/2.0);
    car3();
    glPopMatrix();

 // draw chicken
glPushMatrix();
     // Rotate the rectangle if time is up
    if (glutGet(GLUT_ELAPSED_TIME) / 1000.0f >= timeToRotate) {
               treeX+=0.2*((float)rand() / RAND_MAX);
               if(treeX>0.6)
               {
                  treeX=-0.6;
               }

        timeToRotate = glutGet(GLUT_ELAPSED_TIME) / 1000.0f + rand() % 5 + 1; // random time between 1 and 5 seconds

    }

    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(treeX, treeY,0.0);
    //glRectf(-twidth/2.0, -theight/2.0, twidth/2.0, theight/2.0);
    glScalef(0.2f,0.2f,0.0f);
    drawChicken();
glPopMatrix();


}

void display();
void restartGame()
{
    score = 0;
    distance = 0.0f;

    gameover = 0;
    check_collision = true;

    // player car reset
    car1X = 0.0f;
    car1Y = -0.8f;

    // opponent car reset
    car2Y = 2.0f;
    car3Y = 1.0f;
    car4Y = 3.0f;

    // chicken reset
    treeY = 1.0f;

    // speed reset
    car2VY = -0.01f;
    car3VY = -0.01f;
    car4VY = -0.01f;
    treeVY = -0.01f;

    glutDisplayFunc(display);
    glutPostRedisplay();
}
///game over
void gameoverPage()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ===== Background gradient =====
    glBegin(GL_QUADS);
        glColor3f(0.03f, 0.04f, 0.10f); // dark blue
        glVertex2f(-1.0f, -1.0f);

        glColor3f(0.08f, 0.10f, 0.20f); // blue
        glVertex2f(-1.0f, 1.0f);

        glColor3f(0.12f, 0.06f, 0.18f); // purple-blue
        glVertex2f(1.0f, 1.0f);

        glColor3f(0.02f, 0.02f, 0.07f); // darker bottom
        glVertex2f(1.0f, -1.0f);
    glEnd();

    // ===== Side glow strips =====
    glBegin(GL_QUADS);
        glColor4f(0.6f, 0.1f, 0.8f, 0.18f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(-0.82f, -1.0f);
        glVertex2f(-0.82f, 1.0f);
        glVertex2f(-1.0f, 1.0f);

        glVertex2f(0.82f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.82f, 1.0f);
    glEnd();

    // ===== Center glass panel =====
    glBegin(GL_QUADS);
        glColor4f(0.05f, 0.08f, 0.14f, 0.82f);
        glVertex2f(-0.68f, -0.82f);
        glVertex2f( 0.68f, -0.82f);
        glVertex2f( 0.68f,  0.86f);
        glVertex2f(-0.68f,  0.86f);
    glEnd();

    // panel border
    glColor3f(0.2f, 0.8f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.68f, -0.82f);
        glVertex2f( 0.68f, -0.82f);
        glVertex2f( 0.68f,  0.86f);
        glVertex2f(-0.68f,  0.86f);
    glEnd();

    // top highlight line
    glColor3f(0.8f, 0.3f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.60f, 0.74f);
        glVertex2f( 0.60f, 0.74f);
    glEnd();

    // ===== Title =====
    glColor3f(1.0f, 0.25f, 0.25f);
    drawText("GAME OVER", -0.18f, 0.72f);

    // ===== Score Section =====
    glColor3f(1.0f, 0.85f, 0.25f);
    drawText("YOUR SCORE", -0.20f, 0.44f);

    char scoreText[30];
    sprintf(scoreText, "%d", score);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(scoreText, -0.05f, 0.30f);

    // divider
    glColor3f(0.3f, 0.9f, 1.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-0.42f, 0.20f);
        glVertex2f( 0.42f, 0.20f);
    glEnd();

    // ===== Distance Section =====
    glColor3f(1.0f, 0.85f, 0.25f);
    drawText("DISTANCE TRAVELED", -0.33f, 0.05f);

    char distanceText[30];
    sprintf(distanceText, "%.2f KM", distance);
    glColor3f(0.95f, 0.95f, 0.95f);
    drawText(distanceText, -0.10f, -0.10f);

    // ===== Replay button =====
    glBegin(GL_QUADS);
        glColor4f(0.15f, 0.55f, 0.20f, 0.85f);
        glVertex2f(-0.30f, -0.38f);
        glVertex2f( 0.30f, -0.38f);
        glVertex2f( 0.30f, -0.28f);
        glVertex2f(-0.30f, -0.28f);
    glEnd();

    glColor3f(0.85f, 1.0f, 0.85f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.30f, -0.38f);
        glVertex2f( 0.30f, -0.38f);
        glVertex2f( 0.30f, -0.28f);
        glVertex2f(-0.30f, -0.28f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("PRESS R TO REPLAY", -0.24f, -0.35f);

    // ===== Exit button =====
    glBegin(GL_QUADS);
        glColor4f(0.55f, 0.12f, 0.12f, 0.85f);
        glVertex2f(-0.30f, -0.55f);
        glVertex2f( 0.30f, -0.55f);
        glVertex2f( 0.30f, -0.45f);
        glVertex2f(-0.30f, -0.45f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.85f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.30f, -0.55f);
        glVertex2f( 0.30f, -0.55f);
        glVertex2f( 0.30f, -0.45f);
        glVertex2f(-0.30f, -0.45f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("PRESS ESC TO EXIT", -0.23f, -0.52f);

    glDisable(GL_BLEND);

    glutSwapBuffers();
}


///collision


void collision()
    {
        // update car ,tree
        ///my car
        //car1Y += car1VY;
        //
        ///oppnent car
         car2Y += car2VY;
         car3Y += car3VY;
         car4Y += car4VY;
        ///chicken
        treeY+=treeVY;


         ///random position select
     // If a rectangle has gone off the screen, reset its position and size
        if (car2Y < -1.1f) {
            car2Y =((float)rand() / RAND_MAX) * 0.5f + 5.05f;;
        }
        if (car3Y < -1.1f) {
            car3Y = ((float)rand() / RAND_MAX) * 0.3f + 4.05f;
        }
        if (car4Y < -1.1f) {
           car4Y =((float)rand() / RAND_MAX) * 0.7f + 5.05f;
        }
       if(treeY<-1.0f)
       {
        treeY =((float)rand() / RAND_MAX) * 0.7f + 5.03f;
       }

    /// check for collision

        if (checkCollision(car1X, car1Y, width, height, car2X, car2Y, width, height)) {
                check_collision=false;


        }
        // check for collision 2
       else if (checkCollision(car1X, car1Y, width, height, car3X, car3Y, width, height)) {
            check_collision=false;


        }

        // check for collision 3
       else if (checkCollision(car1X, car1Y, width, height, car4X, car4Y, width, height)) {
                check_collision=false;


        }
      //check for collision 4 for man
       else if (checkCollision(car1X, car1Y, width, height, treeX, treeY, twidth,theight)) {
                check_collision=false;
        }

         if(check_collision==false)
         {
              glClear(GL_COLOR_BUFFER_BIT);
               glutDisplayFunc(gameoverPage);
               glutPostRedisplay();
               gameover=1;

         }
         ///Score and distance
         score+=s+1.0f;
         distance+=d+0.001f;


}
/// initialization function
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
/// display function
void display() {
glClear(GL_COLOR_BUFFER_BIT);
field();
road();
line();
all_road_line();
cars();

///Moving tree and building
glPushMatrix();
all_tree();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f,5.50f, 0.0f);
all_tree();
glPopMatrix();

glPushMatrix();
glTranslatef(1.50f,3.50f, 0.0f);
all_tree();
glPopMatrix();

glPushMatrix();
glTranslatef(1.50f,7.50f, 0.0f);
all_tree();
glPopMatrix();

///collision and score
drawScoreBoard();
collision();

glutSwapBuffers();
}

///first intructions page

void firstPage()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 1.0f);
    drawText("INSTRUCTIONS", -0.5f,0.03f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText1("Press 'Enter' To Start", -0.5f,-0.01f);
    drawText1("Press 'w' for speed", -0.5f,-0.05f);
    drawText1("Press key 'UP,DOWN,LEFT,RIGHT' to move Your Car", -0.5f,-0.09f);
    glPopMatrix();
    glutSwapBuffers();

}
///Our Info
void coverPage()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.2235f,.5176f,0.5686274509803922f);
    drawText3("American International University, Bangladesh (AIUB)", -0.8f,.8f);
    glColor3f(0.2156862745098039f,0.403921568627451f,0.5490196078431373f);
    drawText("FACULTY OF SCIENCE AND TECHNOLOGY",-0.8f,.65f);
    glColor3f(0.32156f,0.1333f,0.1411764705882353f);
    drawText("PROJECT ON : RETRO CAR RACING(GAME)",-0.8f,.5f);
    glColor3f(0.1764f,0.1764f,0.3803921568627451f);
    drawText("COURSE NAME : COMPUTER GRAPHICS",-0.8f,.35f);
    drawText("COURSE SUPERVISOR : MAHFUJUR RAHMAN",-0.8f,.22f);
    glColor3f(0.7686274509803922f,0.0784313725490196f,0.0784313725490196f);
    drawText("MEMBERS:",-0.2f,.05f);
    glColor3f(0.7686274509803922f,0.0784313725490196f,0.0784313725490196f);
    drawText3("1.   MD.SADIT AL MAHFUZ                       (ID:24-58971-2)",-0.7f,-.2f);
    drawText3("2.   MST.NUSRAT JAHAN          (ID:24-55943-1)",-0.7f,-.3f);
    drawText3("3.   SAMIN YASIR                                   (ID:18-39121-3)",-0.7f,-.4f);
    drawText3("4.   FAISAL HOSSAIN                             (ID:21-45107-2)",-0.7f,-.5f);
    drawText3("5.   MD. TAHSIN TASNIM AURIN           (ID:21-45213-2)",-0.7f,-.6f);
    glPopMatrix();

    glPushMatrix();
    int flash = glutGet(GLUT_ELAPSED_TIME) / 500 % 2;
    if (flash) {
        glColor3f(0.0f, 1.0f, 1.0f); // Light gray
    } else {
        glColor3f(1.0f, 0.0f, 0.0f); // White
    }
   drawText("Press 'N' to go Next",0.4f,-0.89f);
    glPopMatrix();
    glutSwapBuffers();

}


// timer function
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}


//clliping
void reshape(GLsizei width, GLsizei height)
{

   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);


   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (width >= height) {

      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {

     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}


///controls
void SpecialInput(int key, int x, int y)
{
switch(key)
    {
    case GLUT_KEY_RIGHT:
    if(car1X<=0.2)
     car1X += 0.3;
    break;

    case GLUT_KEY_LEFT:
        if(car1X>=-0.2)
        car1X -= 0.3;
    break;

    case GLUT_KEY_UP:
        if(car1Y<0.8)
        car1Y +=0.01;
    break;

    case GLUT_KEY_DOWN:
        if(car1Y>-0.8)
        car1Y -= 0.01;
    break;
    }
}
///control-2
bool fullscreen = false;
void keyboardInput(unsigned char key, int x, int y) {
    switch(key) {
    case 'w':
        if(car2VY<0.001)
        {
         car2VY -= 0.001;
         car3VY -= 0.001;
         car4VY -= 0.001;
         treeVY+=0.0001;
         s++;
         d+=0.0002;
        }
        position_line -= speed_line;
        position_tree -= speed_tree;
    break;
      case 'r':
case 'R':

    if(gameover==1)
    {
        restartGame();
    }

break;
    case 27://esc button
        if(gameover==1)
            exit(0);


    break;

     case 13: //Enter
         if(gameover==0)
        glutDisplayFunc(display);

        glutPostRedisplay();
     break;

     case 'n': //Enter
        glutDisplayFunc(firstPage);
        glutPostRedisplay();
     break;
    }
}

// main function
int main(int argc, char** argv) {
    PlaySound(TEXT("C:\\Users\\Mahfuz\\Downloads\\Car Racing\\Car Racing\\engine.wav"),
    NULL,
    SND_FILENAME | SND_ASYNC | SND_LOOP);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(500,0);
    glutCreateWindow("Car Racing");
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(keyboardInput);
    glutReshapeFunc(reshape);
     glutFullScreen();

    glutDisplayFunc(coverPage);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, update, 0);
    glutTimerFunc(0, update1, 0);
    glutTimerFunc(30, updateColorWave, 0);

    init();

    glutMainLoop();

    return 0;
}
