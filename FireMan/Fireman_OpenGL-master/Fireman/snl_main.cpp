#include<GL/glut.h>
#include<iostream>
#include"snl_game.h"
#include<string>
#include<bits/stdc++.h> 

void init();
void display_callback();
void reshape_callback(int w, int h);
void keyPressed(unsigned char, int, int);
void timer_callback(int);
void restart();
void display();
void mouse(int,int,int,int);
void myinit();
void createMenu();
void reshape(int w,int h);
void menu(int);
void printb(char c[], int x, int y);
std::string msg("Press 1,2,3,4 or 5 to move the respective distance");
int player_position = 0;
int turn = 0;
int dice_val;
int rolling = 1;
int victory = 0;
int value=0;
bool gameoverflag=true;
void GameOver();
int menu_id;
int window=0;
int height=600,width=800;
int fire_enable=1;
int fire_index=0;
int fire_extinguish[100]={0};
int fire_pointer=0;
int jump=0;
void printb(char c[], int x, int y)
{
    glRasterPos2i(x, y);
    //glColor3f(0.0, 0.0, 0.0);
    for(int i=0;i<strlen(c);i++)
    	{ 
  		  	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,c[i]);
  		  
    	}
    glFlush();
}

int main(int argc, char**argv)
{
	init_snakes_ladders();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Fire fight");
	glutDisplayFunc(display);	
	glutMouseFunc(mouse);
	myinit();	
	glutMainLoop();
	return 0;	
}

void reshape(int w,int h)	
{
	glViewport(0,0, w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();    
    gluOrtho2D(0.0, 2.0, 0.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0,1.0,1.0);
}

void myinit()
{
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,2000.0,0.0,1600.0);
}

void mouse(int button,int state,int x,int y){
   if(button==GLUT_LEFT_BUTTON && state==GLUT_UP ) {
    glClear(GL_COLOR_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("CG_project");	
	glutCreateWindow("BURNING BUILDING");
	createMenu();
	glutDisplayFunc(display_callback);
	glutKeyboardFunc(keyPressed);
	glutTimerFunc(10, timer_callback, 0);
	init();
	glFlush();	
  }
  else if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP ) {
    {
    	glutDestroyWindow(1);
    }
  }
 } 	

void display()
{
	glutReshapeFunc(reshape);
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(600.0, 1500.0);
	glVertex2f(1300.0, 1500.0);
	glVertex2f(1300.0, 250.0);
	glVertex2f(600.0, 250.0);
	glEnd();
	printb("  FIRE FIGHTER",800,1200);
	printb("  Computer Graphics Miniproject", 710, 1400);
	printb("Lab Incharges: Vani K S and Varalakshmi B D ", 650, 700);
	printb(" Vivek Krishnan V and Shreet Memani  ", 700, 1000);
	printb(" 1AY17CS120           1AY17CS091", 700, 900);
	printb("Left Click to start", 750, 300);
	glFlush();
	glutSwapBuffers();
	glutMouseFunc(mouse);
}

void createMenu()
{
	menu_id= glutCreateMenu(menu);
	glutAddMenuEntry("Quit",0);
	glutAddMenuEntry("Rain",2);	
	glutAddMenuEntry("Stop Rain",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int num)
{
	if(num==0)
	{
		exit(0);
	}
	else 
		value=num;
}

void restart()
{
	player_position=1;
	plot_player(player_position);
}
void init()
{
	glClearColor(0.6, 0.6, 0.8, 0.0);
}

void display_callback()
{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		road();
		switch(value)
		{
			case 1: break;
			case 2: fire_enable=0; 
					rain();
					break;
			case 3: break;
					
		}
		display_message(msg.c_str(), msg.length());
		render_board();
		glutSwapBuffers();
	
}

void render_text()
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			std::cout<<"nothing";
		}
	}
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLfloat)(w), GLfloat(h+10));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 10, 0.0, 10, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyPressed(unsigned char key, int x, int y)
{
	if(rolling)
	{
		if(victory)
		msg= "Press 1,2,3,4 or 5 to move the respective distance!!";
	    switch(key)
	    {			
			case '1': dice_val=1;break;
			case '2': dice_val=2;break;
			case '3': dice_val=3;break;
			case '4': dice_val=4;break;
			case '5': dice_val=5;break;
			case 'j': exit(0); break;
			case 32: 	if((player_position==4&&!fire_extinguish[0])||(player_position==6&&!fire_extinguish[1])||(player_position==12&&!fire_extinguish[2])||(player_position==18&&!fire_extinguish[3])||(player_position==32&&!fire_extinguish[4])||(player_position==37&&!fire_extinguish[5])||(player_position==44&&!fire_extinguish[6])||(player_position==50&&!fire_extinguish[7])||(player_position==58&&!fire_extinguish[8]))
					  	{	fire_extinguish[fire_pointer]=1; fire_pointer++;
					  		fire_index=1;
							break;
					  	}
						else
						{
							msg="Move closer to fire"; 
							return;	
							break;
						}
			default:  msg= "Wrong input!!"; return;
			
	    }
	    
	    rolling = 0;
	}
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer_callback, 0);
}
