#include <GL/gl.h>
#include <GL/glut.h>

GLfloat width = 800, height = 600, x_0 = 470, y_0 = 0;
int mainWindow;


void resize(int w, int h){
    width=w;
    height=h;
}

void draw(void){
    glEnable(GL_SCISSOR_TEST);
    glClearDepth(1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    GLfloat color[4] = {1.0, 0.0, 0.0, 1.0};

    /*
     *           * LEFT VIEW PORT
     *                     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (float)width/2 , height);
    gluPerspective(45, ((float)width/2)/(float)height, 1, 2000);
    gluLookAt( 0.0, 0.0, 50.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0 );
    glMatrixMode(GL_MODELVIEW);
    glScissor(0, 0, (float)width , height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); 
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glRotatef(-20.0f, 1.0f, 0.0f, 0.0f );
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f );
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f );
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-8.0, -8.0);
        glVertex2f(-8.0, 8.0);
        glVertex2f(8.0, 8.0);
        glVertex2f(8.0, -8.0);
    glEnd();
    //glutSolidSphere(10.0, 20, 40);
    glPopMatrix();
    glPopAttrib();

    /*
     *           * THE SECOND VIEW PORT
     *                     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport((float)width/2, 0, width/2 , height);
    gluPerspective(45, ((float)width)/2/((float)height), 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glScissor(((float)width/2), 0, width , height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt( 0.0, 0.0, 50.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0 );
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); 
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    //glutSolidSphere(10.0, 20, 40);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-8.0, -8.0);
        glVertex2f(-8.0, 8.0);
        glVertex2f(8.0, 8.0);
        glVertex2f(8.0, -8.0);
    glEnd();
    glPopMatrix();
    glPopAttrib();

    glDisable(GL_SCISSOR_TEST);
    glFlush();
    glutSwapBuffers();
}

void glutAppInitialize(void){
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(x_0, y_0);
    glutInitWindowSize(width ,height);
    glutAppInitialize();
    mainWindow = glutCreateWindow("Tori App");
    glutDisplayFunc(draw);  
    glutReshapeFunc(resize);
    glutMainLoop();
    return(0);
}
