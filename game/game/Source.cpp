#include <glut.h>
#include <iostream>
#include <fstream>


int checkTest = 0;
const int xMax = 9, xMin = 0, yMax = 9, yMin = 0;
bool checkSolve = true, checkPressNumber = true, checkDemo = true;
unsigned char s[9][9], test_s[9][9], keyboardPress;
unsigned char pr[9][9];
int posClick_x, posClick_y;

using namespace std;

void Initialize();
void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4);
void keyboard(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void preDraw();
void test();
void clearBoard();
void display();
void printText(int x, int y, string str);
void printText2(int x, int y, string str);
void printNumber(unsigned char s, GLint x, GLint y);
void printNumber2(unsigned char s, GLint x, GLint y);
void inputBoard();

bool checkBoard(unsigned char c_check, unsigned char pr_check);

int main(int agrc, char** argv)
{
    glutInit(&agrc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SUDOKU");
    Initialize();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

void Initialize()
{
    glClearColor((220.0 / 255), (220.0 / 255), (220.0 / 255), 0); //240, 255, 240
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
    for (int i = 0; i < xMax; i++)
        for (int j = 0; j < yMax; j++)
        {
            s[i][j] = '0';
            test_s[i][j] = '0';
        }

}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
    {
        keyboardPress = key;
        break;
    }
    case '2':
    {
        keyboardPress = key;
        break;
    }
    case '3':
    {
        keyboardPress = key;
        break;
    }
    case '4':
    {
        keyboardPress = key;
        break;
    }
    case '5':
    {
        keyboardPress = key;
        break;
    }
    case '6':
    {
        keyboardPress = key;
        break;
    }
    case '7':
    {
        keyboardPress = key;
        break;
    }
    case '8':
    {
        keyboardPress = key;
        break;
    }
    case '9':
    {
        keyboardPress = key;
        break;
    }
    default:
    {
        break;
    }
    }
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        posClick_x = x;
        posClick_y = 600 - y;
    }
    glutPostRedisplay();
}

void preDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f((192.0 / 255), (192.0 / 255), (192.0 / 255)); //240, 255, 240
    GLint x, y;
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            drawSquare(x, y + 60, x + 60, y + 60, x + 60, y, x, y);
        }
    }
    glLineWidth(5);
    glPushAttrib(GL_CURRENT_BIT);
    glColor3d((192.0 / 255), (192.0 / 255), (192.0 / 255));//240, 255, 240

    //draw square of "Load"
    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 570);
    glVertex2i(765, 470);
    glVertex2i(600, 470);
    glVertex2i(600, 570);
    glEnd();

    //draw square of "Check"
    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 370);
    glVertex2i(765, 270);
    glVertex2i(600, 270);
    glVertex2i(600, 370);
    glEnd();



    //draw square of "Clear Board"
    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 130);
    glVertex2i(765, 30);
    glVertex2i(600, 30);
    glVertex2i(600, 130);
    glEnd();


    glPopAttrib();

    printText(650, 515, "LOAD");
    if (checkTest == 0)
        printText2(125, 583, "Click on \"Load\" to open Sudoku board or input number from keyboard");
    else if (checkTest == 1) {
        glClearColor((0.0 / 255), (100.0 / 255), (0.0 / 255), 0); //0, 250, 154
       
        printText2(225, 583, "YOU DID IT");
    }
    else if (checkTest == -1) {
        glClearColor((139.0 / 255), (0.0 / 255), (0.0 / 255), 0); //220, 20, 60
        printText2(225, 583, "TRY AGAIN. THATS WRONG ");
    }
    else printText2(225, 583, "Get number from your keyboard");
    printText(640, 310, "CHECK");

    printText(640, 70, "CLEAR");

    //Slipt Sudoku Board into 9 parts
    glPushAttrib(GL_CURRENT_BIT);
    glColor3d((192.0 / 255), (192.0 / 255), (192.0 / 255));
    glLineWidth(10);

    glBegin(GL_LINE_LOOP);
    glVertex2i(30, 570);
    glVertex2i(570, 570);
    glVertex2i(570, 30);
    glVertex2i(30, 30);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(210, 572);
    glVertex2i(210, 29);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(390, 572);
    glVertex2i(390, 29);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(30, 390);
    glVertex2i(570, 390);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(30, 210);
    glVertex2i(570, 210);
    glEnd();

    glPopAttrib();
}

void test()
{
    
    if (checkPressNumber == true)
    {
        for (int i = 0; i < xMax; i++)
            for (int j = 0; j < yMax; j++)
                if (checkBoard(s[i][j], pr[i][j]) == false)
                {
                    
                    checkTest = -1;
                    return;
                }
    }
    checkTest = 1;
}

void clearBoard()
{
    checkTest = 0;
   
    for (int i = 0; i < xMax; i++)
        for (int j = 0; j < yMax; j++)
        {
            s[i][j] = '0';
            test_s[i][j] = '0';
        }
}

void display()
{
    preDraw();
    //Click on "Load"
    if (posClick_x >= 600 && posClick_x <= 765 && posClick_y <= 570 && posClick_y >= 470)
    {
        inputBoard();
        checkPressNumber = true;
        checkSolve = true;
        checkTest = -2;
    }



    //Click on "Check"
    if (posClick_x >= 600 && posClick_x <= 765 && posClick_y <= 430 && posClick_y >= 330)
    {
        checkSolve = true;
        test();
        checkDemo = false;
    }

    //Click on "Clear Board"
    if (posClick_x >= 600 && posClick_x <= 765 && posClick_y <= 130 && posClick_y >= 30)
    {
        clearBoard();
        checkSolve = true;
        checkPressNumber = true;
    }

    if (30 <= posClick_x && 570 >= posClick_x && 30 <= posClick_y && 570 >= posClick_y)
    {
        checkTest = -2;
        int j = 8 - (posClick_x - 30) / 60;
        int i = (posClick_y - 30) / 60;
        if (test_s[i][j] == '0')s[i][j] = keyboardPress;
        keyboardPress = test_s[i][j];
        posClick_x = 0;
        posClick_y = 0;
    }

    GLint x, y;
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            if (s[y / 60][8 - x / 60] != '0')
            {
                glPushAttrib(GL_CURRENT_BIT);
                if (test_s[y / 60][8 - x / 60] == '0')
                    printNumber(s[y / 60][8 - x / 60], x + 25, y + 20);
                else printNumber2(s[y / 60][8 - x / 60], x + 25, y + 20);
                glPopAttrib();
            }
        }
    }
    glFlush();
}

void printText(int x, int y, string str)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(188.0 / 255, 143.0 / 255, 143.0 / 255);
    glRasterPos2f(x, y);
    int n = str.size();
    for (int i = 0; i < n; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
    glPopAttrib();
}

void printText2(int x, int y, string str)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(188.0 / 255, 143.0 / 255, 143.0 / 255); //255, 240, 245
    
    glRasterPos2f(x, y);
    int n = str.size();
    for (int i = 0; i < n; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    }
    glPopAttrib();
}

void printNumber(unsigned char s, GLint x, GLint y)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(105.0 / 255, 105.0 / 255, 105.0 / 255); // 186, 85, 211
    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s);
    glPopAttrib();
}

void printNumber2(unsigned char s, GLint x, GLint y)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(169.0/255, 169.0/255, 169.0/255);
    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s);
    glPopAttrib();
}

void inputBoard()
{


    ifstream file("input1.txt");
    if (file.is_open())
        while (!file.eof())
        {
            for (int i = xMax - 1; i >= xMin; i--)
                for (int j = yMax - 1; j >= yMin; j--)
                {
                    file >> s[i][j];
                    test_s[i][j] = s[i][j];
                }
        }
    ifstream fin("p1.txt");
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            for (int i = xMax - 1; i >= xMin; i--)
                for (int j = yMax - 1; j >= yMin; j--)
                {
                    fin >> pr[i][j];
                }
        }

    }
    else {
        cout << "aaaaa" << endl;
    }

    file.close();

}


bool checkBoard( unsigned char c_check, unsigned char pr_check)
{
    
    if (c_check == pr_check) {
        
        return true;
    }
    else {
        return false;
    }
}