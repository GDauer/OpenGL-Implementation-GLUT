/**
 * @author Gustavo Vicente Dauer <gustavo.dauer@hotmail.com>.
 * @name main.cpp
 * @date 06/06/2020
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#define SPHERE_RADIUS_MAX_SIZE 1.12
#define SPHERE_RADIUS_MIN_SIZE 0.42
#define SPHERE_ANIMATION_SPEED 0.001

/* Flag to sphere resize animation */
bool flagReachMaxSize = false;

/* Global diffuse material RGBA values */
GLfloat diffuseMaterial[4] = {0.0, 0.0, 0.0, 1.0};

/* Sphere radius scale */
GLfloat sphereRadius = 1.0;

/**
 * Create Lighting and color diffuse.
 *
 * @return void
 */
void createLightingAndColorDiffuse()
{
    // Lighting initialize!
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);

    /* glMaterials values */
    float glMaterialFParamsValue = 25.0;
    GLfloat matrixRGBASpecular[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightRGBAPosition[4] = {1.0, 1.0, 1.0, 0.0};

    // Creating materials, lighting and diffuse!
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrixRGBASpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, glMaterialFParamsValue);
    glLightfv(GL_LIGHT0, GL_POSITION, lightRGBAPosition);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

/**
 * Create solid sphere.
 *
 * @return void
 */
void createSolidSphere()
{
    // Clear buffer!
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Create solid sphere
    glutSolidSphere(sphereRadius, 42, 42);
    glFlush ();
}

/**
 * Sphere reshape method fo glutReshapeFunc.
 *
 * @param int width  Window width size
 * @param int height Window height size
 *
 * @return void
 */
void sphereReshape (int width, int height)
{
    // Sphere viewport position, should change this method if the window size changed!
    glViewport (0, -100, (GLsizei) width, (GLsizei) width);

    // Sphere projection type and coordinates initialization!
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    // Avoid division by zero!
    if (height == 0) {
        height = 1;
    }

    // Avoid division by zero!
    if (width == 0) {
        width = 1;
    }

    /* glOrtho value, use negative value for top/right positions */
    GLfloat orthoValue = -1.5 * (GLfloat) height / (GLfloat) width;

    /** Transformation that produces a parallel projection. **/
    if (width <= height) {
        glOrtho(-1.5,1.5, orthoValue, - orthoValue, -10.0, 10.0);
    } else {
        glOrtho(orthoValue, - orthoValue, -1.5, 1.5, -10.0, 10.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Change diffuse color intensity on the Red spectrum.
 *
 * If the key 'shift + R' is pressed then the sphere red spectrum will become stronger.
 * If the key 'R' is pressed then the sphere red spectrum will become weaker.
 * If the value of diffuse reach a value bigger than 1.5 or smaller than 0 the diffuse will be reseated.
 *
 * @param char key
 *
 * @return void
 */
void controlDiffuseRedColor(unsigned char key)
{
    if (key == 'r') {
        diffuseMaterial[0] -= 0.1;
    } else if (key == GLFW_KEY_R) {
        diffuseMaterial[0] += 0.1;
    }

    // Reset Red diffuse!
    if (diffuseMaterial[0] > 1.5 || diffuseMaterial[0] < 0.0) {
        diffuseMaterial[0] = 0.0;
    }
}

/**
 * Change diffuse color intensity on the Green spectrum.
 *
 * If the key 'shift + G' is pressed then the sphere's green spectrum will become stronger.
 * If the key 'G' is pressed then the sphere's green spectrum will become weaker.
 * If the value of diffuse reach a value bigger than 1.5 or smaller than 0 the diffuse will be reseated.
 *
 * @param char key
 *
 * @return void
 */
void controlDiffuseGreenColor(unsigned char key)
{
    if (key == 'g') {
        diffuseMaterial[1] -= 0.1;
    } else if (key == GLFW_KEY_G) {
        diffuseMaterial[1] += 0.1;
    }

    // Reset diffuse!
    if (diffuseMaterial[1] > 1.5 || diffuseMaterial[1] < 0.0) {
        diffuseMaterial[1] = 0.0;
    }
}

/**
 * Change diffuse color intensity on the Blue spectrum.
 *
 * If the key 'shift + B' is pressed then the sphere's blue spectrum will become stronger.
 * If the key 'B' is pressed then the sphere's blue spectrum will become weaker.
 * If the value of diffuse reach a value bigger than 1.5 or smaller than 0 the diffuse will be reseated.
 *
 * @param char key
 *
 * @return void
 */
void controlDiffuseBlueColor(unsigned char key)
{
    if (key == 'b') {
        diffuseMaterial[2] -= 0.1;
    } else if (key == GLFW_KEY_B) {
        diffuseMaterial[2] += 0.1;
    }

    // Reset diffuse!
    if (diffuseMaterial[2] > 1.5 || diffuseMaterial[2] < 0.0) {
        diffuseMaterial[2] = 0.0;
    }
}

/**
 * Update sphere radius to create the animation effect.
 *
 * @param int value
 *
 * @return void
 */
void updateSphereRadius(int value)
{
    if (sphereRadius <= SPHERE_RADIUS_MAX_SIZE && !flagReachMaxSize) {
        // If the sphere don't have reached the max size then increase the radius!
        sphereRadius += SPHERE_ANIMATION_SPEED;
    } else if (sphereRadius >= SPHERE_RADIUS_MIN_SIZE && flagReachMaxSize) {
        // If the sphere don't have reached the min size then decrease the radius!
        sphereRadius -= SPHERE_ANIMATION_SPEED;
    } else if (sphereRadius > SPHERE_RADIUS_MAX_SIZE) {
        flagReachMaxSize = true;
    } else if (sphereRadius < SPHERE_RADIUS_MIN_SIZE) {
        flagReachMaxSize = false;
    }

    glutPostRedisplay();
    glutTimerFunc(42, updateSphereRadius, value);
}

/**
 * KeyPressed method for glutKeyboardFunc.
 *
 * @param char key Keyboard's pressed key
 * @param int  x   Coordinate X
 * @param int  y   Coordinate Y
 */
void keyPressed (unsigned char key, int x, int y) {
    controlDiffuseRedColor(key);
    controlDiffuseGreenColor(key);
    controlDiffuseBlueColor(key);

    glColor4fv(diffuseMaterial);
    glutPostRedisplay();
}

/**
 * Execute main method.
 *
 * @param int    argc
 * @param char** argv
 *
 * @return int
 */
int main(int argc, char** argv)
{
    // Glut initialize!
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    // Window creation with glut!
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Fmu - Computação Gráfica (Projeto Final)");

    // Creating light and diffuse!
    createLightingAndColorDiffuse();

    // Creating solid sphere!
    glutDisplayFunc(createSolidSphere);
    glutReshapeFunc(sphereReshape);

    // Glut Timer callback function!
    glutTimerFunc(42, updateSphereRadius, 1);

    // Diffuse control action!
    glutKeyboardFunc(keyPressed);

    // openGL loop method with glut!
    glutMainLoop();

    return 0;
}
