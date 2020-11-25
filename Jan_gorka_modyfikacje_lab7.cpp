//-------------------------------------------------------------------------------


// doda�em obr�t woko� wszystkich osi 
//kazda z wlasn� predkoscia

/* System */
#include<windows.h>
#include<stdio.h>
#include<math.h>
/* G��wna bibloteka OpenGL */
#include<GL/gl.h>
/* Biblioteka GLUT */
#include<glut.h>


/* Deklaracje funkcji narz�dziowych */

/* Funkcja do rysowania */
void DrawScene(void);
/* Prototyp fukcji rysuj�cej osie uk��du */
void DrawSceneAxes(void);

/* Funkcja do inicjacji OpenGLa */
void InitOpenGL(void);

/* Funkcja wywo�ywana w momentach zmiany rozmiar�w okna */
void ReshapeWindow(int width, int height);

/* Funkcja obs�uguj�ca klawiatur�
*/

/* Deklaracja globalnych zmiennych */
/* K�ty obrotu wok� osi X i Y */
GLfloat x_angle;
GLfloat y_angle;
GLfloat z_angle;
GLfloat xv_angle;
GLfloat yv_angle;
GLfloat zv_angle; 

void KeyboardFunc(unsigned char key, int x, int y)
{
switch(key)
{
case 27: // Wci�ni�cie klawisza ESC spowoduje wyj�cie zprogramu exit(0);
	case 'w': // Wci�ni�cie klawisza w spowoduje inkrementacj� zmiennej
	xv_angle += 0.05f;
	break;
	case 'r': // Wci�ni�cie klawisza r spowoduje dekrementacj� zmiennej
	xv_angle -= 0.05f;
	break;
	case 's':
	yv_angle += 0.05f;
	break;
	case 'f':
	yv_angle -= 0.05f;
	break;
	case 'x':
	zv_angle += 0.05f;
	break;
	case 'v':
	zv_angle -= 0.05f;
	break;
}
glutPostRedisplay();
} 


void Timer_Func()
{
	x_angle += xv_angle;
	y_angle += yv_angle;
	z_angle += zv_angle;
	glutPostRedisplay();
}

/* Pozycja obserwatora */
GLfloat viewer_pos[] = { 0.0, 0.0, 10.0 };

/* Globalny identyfikator g��wnego okna programu */
int mainWindow;

/* Funkcja main */
int main(int argc, char **argv)
{
	// Inicjujemy bibliotek� GLUT
	glutInit(&argc, argv);
	// Inicjujemy: format koloru, dwa bufoy ramki
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Ustawiamy pocz�tkowe wymiary okna
    glutInitWindowSize(800, 600);
	// Ustawiamy pozycj� okna - lewy g�rny naro�nik
	glutInitWindowPosition(150,150);
	// Tworzymy g��wne okno programu
    mainWindow = glutCreateWindow("Transformacje czajnikowe");

	// Sprawdzamy powodzenie operacji
	if(mainWindow == 0){
		puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
		exit(-1);
	}
	// Czynimy aktywnym okno g��wne programu
	glutSetWindow(mainWindow);

	// Tutaj rejestrujemy funkcje narz�dziowe - tzw. callbacks
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(ReshapeWindow);
	glutKeyboardFunc(KeyboardFunc); 
	
	// Ustawienia pocz�tkowe
	InitOpenGL();

	// W��czamy mechanizm usuwania niewidocznych powierzchni
	glEnable(GL_DEPTH_TEST);

	// Wej�cie do p�tli programu
	glutMainLoop();
	
	return(0);
}

/* W tej funkcji okre�lamy to co ma byc narysowane na ekranie.
 * Jest wywo�ywana zawsze wtedy, gdy trzeba przerysowa� ekran - bufor ramki.
 */
void DrawScene(void)
{
	// Czy�cimy okno aktualnym (domy�lnym) kolorem oraz resetujemy bufor g��bi 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Resetujemy bie��c� macierz
	glLoadIdentity();

	// Definiujemy po�o�enie obserwatora
	gluLookAt(viewer_pos[0],viewer_pos[1],viewer_pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Rysujemy osie uk�adu
	DrawSceneAxes();	

	// Zamieniamy bufory ramki
	glutSwapBuffers();
	
	Timer_Func();

}

/* Ta funkcja jest wywo�ywana przez funkcj� DrawScene.
 * Jej zadaniem jest rysowanie konkretnych obiekt�w osi uk�adu 
 * wsp�rz�dnych.
 */
void DrawSceneAxes(void)
{
	// Definiujemy nowy typ jako tablic� 3-elementow�
	typedef float pt3d[3];

	// Pocz�tek i koniec osi X
	pt3d x_beg = { -10.0f, 0.0f, 0.0f };
	pt3d x_end = {  10.0f, 0.0f, 0.0f };

	// Poczatek i koniec osi Y
	pt3d y_beg = { 0.0f, -10.0f, 0.0f };
	pt3d y_end = { 0.0f,  10.0f, 0.0f };

	// Pocz�tek i koniec osi Z
	pt3d z_beg = { 0.0f, 0.0f, -10.0f };
	pt3d z_end = { 0.0f, 0.0f,  10.0f };

	// Rysujemy osie
	glBegin(GL_LINES);
		// Czerwony kolor dla osi X
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(x_beg);
		glVertex3fv(x_end);

		// Zielony kolor dla osi Y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(y_beg);
		glVertex3fv(y_end);

		// Niebieski kolor dla osi Z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(z_beg);
		glVertex3fv(z_end);
	glEnd();
	
	glRotatef(x_angle, 1.0f, 0.0f, 0.0f); 
	glRotatef(y_angle,0.0f, 1.0f, 0.0f);
	glRotatef(z_angle,0.0f, 0.0f, 1.0f); 
	
	glColor3f(0.5f, 0.5f, 0.5f);
	glutWireTeapot(4.0);
}

/* Ta funkcja s�u�y do wst�pnej konfiguracji OpenGLa.
 * Zanim co� narysujemy musimy wywo�a� t� funkcj�.
 */
void InitOpenGL(void)
{
	// Ustawiamy domy�lny, czarny kolor t�a okna - bufor ramki malujemy na czarno
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/*Ta funkcja ustawia perspektyw� - jej odpowiednikiem w starszych implementacjach openGL jest gluPerspective
*/
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

/* T� funkcj� wywo�uje system w momencie gdy u�ytkownik zmieni mysz�
 * rozmiar g��wnego okna. jej zadaniem jest zachowanie proporcji wymiar�w
 * rysowanych obiekt�w niezale�nie od wymiar�w okna.
 */ 
void ReshapeWindow(int width, int height)
{
	
	// Ustawiamy uk�ad wsp�rz�dnych obserwatora
    glMatrixMode(GL_PROJECTION); 

	// Resetujemy macierz projkecji 
    glLoadIdentity();

	// Ustawiamy perspektyw�
	perspectiveGL(70.0, 1.0, 1.0, 20.0);
    
	// Korekta  
    if(width <= height)
		glViewport(0, (height - width)/2, width, width);  
     else
		glViewport((width - height)/2, 0, height, height); 
 
	// Ustawiamy macierz modelu
    glMatrixMode(GL_MODELVIEW);
    
	// Resetujemy macierz modelu
    glLoadIdentity();
	
}

