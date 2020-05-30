#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h> 

void draw_numbers();
void display_message(const char *text, int length);
void draw_text(const char *text, int length, double x, double y);
void draw_grid();
void draw_grid_backside();
void draw_text_head(float, float, char *);
void draw_billboard();
void render_ladders(float, float);
void render_fire(int, int);
void render_board();
void render_hole(int, int);
void draw_player(float cx, float cy);
void plot_player(int position);
int roll_dice();
void rain();
void road();
void truck();
void windows(float, float);
//void jump();

double x, y, x_increment = 0.16666, y_increment = 0.1625, x_pos, y_pos;
int dead=0;
void remove_fire();
void update_piece();
void init_snakes_ladders();
float displacement=0.10;
float fire_point=7.0;
int count=0;
extern int player_position;
extern int fire_index;
extern std::string msg;
extern int turn;
extern int dice_val;
extern int rolling;
GLfloat color1[][3]={{1.0,0.0,0.0},{0.0,0.6,1.0}};
float rotatehose[3]={3.14,90*3.14/180,0.0};
int hose_point=1;
extern int victory;
extern int fire_enable;
extern int fire_extinguish[];
extern int fire_pointer;
float move_fire=0.005;
int * snakes= new int[100];
int * ladders;
extern int jump;

void draw_building_background()
{
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.96);
		glVertex2f(-0.5,0.667);
		glVertex2f(-0.45,0.72);
		glVertex2f(0.55,0.72);
		glVertex2f(0.55,-0.9);
		glVertex2f(0.5,-0.96);
	glEnd();
}

void draw_billboard()
{
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.3,0.668);
		glVertex2f(-0.3,0.8);
		glVertex2f(0.3,0.8);
		glVertex2f(0.3,0.668);
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.3,0.668);
		glVertex2f(-0.3,0.8);
		glVertex2f(0.3,0.8);
		glVertex2f(0.3,0.668);
	glEnd();
	glLineWidth(4.0);
	draw_text_head(-0.15,0.7335,"GENERAL OFFICE");
	glBegin(GL_LINES);
		glVertex2f(0.3,0.7335); glVertex2f(0.35,0.675);
	glEnd();
}
void draw_text_head(float x,float y,char *s)
{
	int i;
	glRasterPos2f(x,y);
	glColor3f(0.0,0.0,0.0);
	for(i=0;i<s[i]!='\0';i++)
  		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
}

void render_board()
{

	draw_building_background();
	draw_grid();
	draw_grid_backside();
	draw_billboard();
	truck();
	windows(-0.263,-0.87);
	//windows(-0.263,-0.7034);
	windows(-0.263,-0.544);
	//windows(-0.263,-0.3702);
	windows(-0.263,-0.218);
	//windows(-0.263,-0.037);
	windows(-0.263,0.108);
	//windows(-0.263,0.2962);
	windows(-0.263,0.434);
	
	windows(0.2369998,-0.707);
	windows(0.2369998,-0.381);
	windows(0.2369998,-0.055);
	windows(0.2369998,0.271);
	windows(0.2369998,0.597);
	
	render_ladders(.458, -.85);
	render_ladders(-.408,-.68);
	render_ladders(.458,-.53);
	render_ladders(-.408,-.36);
	render_ladders(.458,-.20);
	render_ladders(-.408,-.03);
	render_ladders(.458,.12);
	render_ladders(-.408,.28);
	render_ladders(.458,.45);
	
	if(move_fire==0.005f)
	{
		move_fire=0.0;
		fire_point=9.0;
	}
	else
	{
		move_fire=0.005;
		fire_point=7.0;
	}
	usleep(40000);
	if(!fire_extinguish[0])
		render_fire(4,0);
	else if(fire_pointer==1)
	{
		snakes[5]=0;
		render_hole(4,0);
	}	
	else 
		render_hole(4,0);
	if(!fire_extinguish[1])
		render_fire(5,1);
	else if(fire_pointer==2)
	{
		snakes[7]=0;
		render_hole(5,1);
	}
	else 
		render_hole(5,1);
	if(!fire_extinguish[2])
		render_fire(0,2);
	else if(fire_pointer==3)
	{	
		snakes[13]=0;
		render_hole(0,2);
	}
	else 
		render_hole(0,2);
	if(!fire_extinguish[3])
		render_fire(5,3);
	else if(fire_pointer==4)
	{	
		snakes[19]=0;
		render_hole(5,3);
	}
	else 
		render_hole(5,3);
	if(!fire_extinguish[4])
		render_fire(3,5);
	else if(fire_pointer==5)
	{	
		snakes[33]=0;
		render_hole(3,5);
	}
	else 
		render_hole(3,5);
	if(!fire_extinguish[5])		
		render_fire(1,6);
	else if(fire_pointer==6)	
	{
		snakes[38]=0;
		render_hole(1,6);
	}
	else 
		render_hole(1,6);
	if(!fire_extinguish[6])
		render_fire(3,7);
	else if(fire_pointer==7)
	{	
		snakes[45]=0;
		render_hole(3,7);
	}
	else
		render_hole(3,7);
	if(!fire_extinguish[7])	
		render_fire(2,8);
	else if(fire_pointer==8)
	{
		snakes[51]=0;
		render_hole(2,8);
	}
	else 
		render_hole(2,8);
	if(!fire_extinguish[8])
		render_fire(1,9);
	else if(fire_pointer==9)
	{
		snakes[59]=0;
		render_hole(1,9);
	}
	else
		render_hole(1,9);
	if(((player_position+dice_val)>60) && turn == 0)
	{
		dice_val = 0;
		
	}
	else if((player_position == 60) && !victory)
	{
		victory = 1;
		plot_player(player_position);
		usleep(500000);		
	}
	else if(victory==1)
	{	
		plot_player(player_position);
		msg = "Fireman Saves the Day!! Now Press J to escape building!";
		//jump();
		update_piece();
	}
	else
	{
		update_piece();
	}

	draw_numbers();
}

/*void jump()
{
	for(int i=0;i<20;i++)
	{	
		plot_player(player_position+i);
	}
}*/

void draw_grid()
{
    glColor3f(0.5,0.2,0.1);
    glLineWidth(3.0);
    for(float y = 0.667; y>=-1; y = y-0.163)
    {
	    glBegin(GL_LINES);
	        glVertex2f(-0.5, y); glVertex2f(0.50, y);
	    glEnd();
	}
	for(float x = -0.5; x<=0.5; x = x+0.1666666 )
    {
	    glBegin(GL_LINES);
	        glVertex2f(x, 0.667); glVertex2f(x, -0.96);
	    glEnd();
	    
	}
}
void windows(float x, float y)
{
	glColor3f(0.0,0.7,0.7);

	glBegin(GL_POLYGON);
		glVertex2f(x+0.07,y+0.04);
		glVertex2f(x+0.07,y-0.05);
		glVertex2f(x-0.05,y-0.05);
		glVertex2f(x-0.05,y+0.04);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x+0.07,y+0.04);
		glVertex2f(x+0.07,y-0.05);
		glVertex2f(x-0.05,y-0.05);
		glVertex2f(x-0.05,y+0.04);
	glEnd();
}

void draw_grid_backside()
{
	glColor3f(0.5,0.2,0.1);
	float x1=0.5, x2=0.55, y1=0.667, y2=0.72;
	int i=0;
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex2f(-0.5,0.667); glVertex2f(-0.45,0.72);
		//glVertex2f(0.5,0.667); glVertex2f(0.55,0.72);
		glVertex2f(-0.45,0.72); glVertex2f(0.55,0.72);
		glVertex2f(0.55,0.72); glVertex2f(0.55,-0.9);
		//glVertex2f(0.5,-0.961); glVertex2f(0.55,-0.9);
	glEnd();
	for(i=0;i<=10;i++)
	{
		glBegin(GL_LINES);
			glVertex2f(x1,y1); glVertex2f(x2,y2);
		glEnd();
		y1-=0.163;
		y2-=0.1615;
	}
}
void render_hole(int x, int y)
{	
	float r = 0.03;
	int num_segments = 360;
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float cx = r * cosf(theta);//calculate the x component
        float cy = r * sinf(theta);//calculate the y component

        glVertex2f(-0.428+ cx + x*0.16666, -0.895+cy + y*0.1625);//output vertex

    }
    glEnd();
}
void rain()
{
	remove_fire();
	glColor3f(0.0,1.0,1.0);
	glLineWidth(1.0);
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(10,0xCCCC);
	glEnable(GL_LINE_STIPPLE);
	for(float x=-2; x<=2;x+=0.07)
	{
		glBegin(GL_LINES);
		glVertex2f(x,2-displacement);
		glVertex2f(x-0.1,-2-displacement);
		glEnd();
	}
	glPopAttrib();
	displacement+=0.03;
	if(displacement==0.28f)
		displacement=0.10;
	usleep(100000);
}
void road()
{
	glColor3f(0.35,0.35,0.35);
	glBegin(GL_POLYGON);
		glVertex2f(1.0,-1.0);
		glVertex2f(-1.0,-1.0);
		glVertex2f(-1.0,-0.75);
		glVertex2f(1.0,-0.75);
	glEnd();
}

void draw_numbers()
{
	double x = -0.55;
	double y = -0.88;
	int num = 1, length=2;
	for(int i = 0; i < 10; i++)
	{
		std::string text = std::to_string(num);
		draw_text(text.c_str(), text.length(), x, y);
		num++;
		y = y+0.162;
	}
}
void display_message(const char *text, int length)
{
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2f(-0.4,0.87);
		glVertex2f(-0.4,0.97);
		glVertex2f(0.4,0.97);
		glVertex2f(0.4,0.87);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.4,0.87);
		glVertex2f(-0.4,0.97);
		glVertex2f(0.4,0.97);
		glVertex2f(0.4,0.87);
	glEnd();
	glColor3f(0, 0, 0);
	double x_pos = length/56.0;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(-0.3, .9);
	for(int i=0; i<length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void draw_text(const char *text, int length, double x, double y)
{
	glColor3f(0, 0, 0);
	double x_pos = length/56.0;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	//glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x, y);
	for(int i=0; i<length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}


void render_ladders(float x1, float y1)
{
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
		glVertex2f(x1-0.06,y1-0.05);
		glVertex2f(x1-0.06,y1);
		glVertex2f(x1+0.02,y1);
		glVertex2f(x1+0.02,y1-0.05);
		glVertex2f(x1-0.05,y1);
		glVertex2f(x1+0.01,y1);
		glVertex2f(x1+0.01,y1+0.05);
		glVertex2f(x1-0.05,y1+0.05);
		glVertex2f(x1-0.04,y1+0.05);
		glVertex2f(x1,y1+0.05);
		glVertex2f(x1,y1+0.1);
		glVertex2f(x1-0.04,y1+0.1);
	glEnd();
	glLineWidth(3.0);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1-0.06,y1-0.05);
		glVertex2f(x1-0.06,y1);
		glVertex2f(x1+0.02,y1);
		glVertex2f(x1+0.02,y1-0.05);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1-0.05,y1);
		glVertex2f(x1-0.05,y1+0.05);
		glVertex2f(x1+0.01,y1+0.05);
		glVertex2f(x1+0.01,y1);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1-0.04,y1+0.05);
		glVertex2f(x1-0.04,y1+0.1);
		glVertex2f(x1,y1+0.1);
		glVertex2f(x1,y1+0.05);
	glEnd();
}

void render_fire(int x, int y)
{

	if(fire_enable!=0)
	{
		glPointSize(fire_point);
		glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslatef(move_fire,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(-0.428+x*0.16666,-0.83+y*0.1625);
			glVertex2f(-0.428+x*0.16666,-0.84+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.84+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.84+y*0.1625);
			glVertex2f(-0.428+x*0.16666,-0.855+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.855+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.855+y*0.1625);
			glVertex2f(-0.413+x*0.16666,-0.855+y*0.1625);
			glVertex2f(-0.443+x*0.16666,-0.855+y*0.1625);
		glEnd();
		glPopMatrix();
		glColor3f(1, 0.8, 0.1);
		glPushMatrix();
		glTranslatef(move_fire,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(-0.428+x*0.16666,-0.875+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.875+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.875+y*0.1625);
			glVertex2f(-0.428+x*0.16666,-0.88+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.88+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.88+y*0.1625);
			glVertex2f(-0.428+x*0.16666,-0.87+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.87+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.87+y*0.1625);
			glVertex2f(-0.413+x*0.16666,-0.88+y*0.1625);
			glVertex2f(-0.443+x*0.16666,-0.88+y*0.1625);
			glVertex2f(-0.413+x*0.16666,-0.87+y*0.1625);
			glVertex2f(-0.443+x*0.16666,-0.87+y*0.1625);
		glEnd();
		glPopMatrix();
		glColor3f(1.0, 0.3, 0.1);
		glPushMatrix();
		glTranslatef(move_fire,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(-0.428+x*0.16666,-0.905+y*0.1625);
			glVertex2f(-0.433+x*0.16666,-0.90+y*0.1625);
			glVertex2f(-0.423+x*0.16666,-0.90+y*0.1625);
			glVertex2f(-0.428+x*0.16666,-0.895+y*0.1625);
			glVertex2f(-0.433+x*0.16666,-0.895+y*0.1625);
			glVertex2f(-0.423+x*0.16666,-0.895+y*0.1625);
			glVertex2f(-0.438+x*0.16666,-0.895+y*0.1625);
			glVertex2f(-0.418+x*0.16666,-0.895+y*0.1625);
		glEnd();
		glPopMatrix();
	}
	else return;
}

void update_piece()
{
	if(jump)
	{	
		
		for(int i=0;i<20;i++)
		{
		glTranslatef(-0.5-i*0.025,0.6-0.1*i,0.0);
		draw_player(-0.5,0.6);
		}
		return;
	}
	
	for(int i=0;i<dice_val;i++)
	{
		if(snakes[player_position+i]==1)
		{
			plot_player(player_position);
			dice_val=0;
			msg="Extinguish fire boi! Wanna get burnt?";
			return;
		}
	}
	
	if(dice_val>0)
	{		
		player_position++;
		dice_val--;			
		usleep(20000);
	}
	else
	{	
		if(snakes[player_position])
		{	
			dead=1;
			plot_player(player_position);
			player_position = snakes[player_position];
			msg = "Fireman gets burnt to a crisp!!";
			usleep(400000);	
			}
	}
	rolling = 1;	
	plot_player(player_position);
}
void truck()
{
	//Truck Body
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex2f(-0.99,-0.9);
		glVertex2f(-0.99,-0.8);
		glVertex2f(-0.85,-0.8);
		glVertex2f(-0.85,-0.9);
	glEnd();
	//Truck Front
	glBegin(GL_POLYGON);
		glVertex2f(-0.85,-0.9);
		glVertex2f(-0.85,-0.83);
		glVertex2f(-0.8,-0.83);
		glVertex2f(-0.8,-0.9);
	glEnd();
	//Borders, Windows and Tyres
	glColor3f(0,0,0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.99,-0.9);
		glVertex2f(-0.99,-0.8);
		glVertex2f(-0.85,-0.8);
		glVertex2f(-0.85,-0.9);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.85,-0.9);
		glVertex2f(-0.85,-0.83);
		glVertex2f(-0.8,-0.83);
		glVertex2f(-0.8,-0.9);
	glEnd();
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2f(-0.835,-0.845);
		glVertex2f(-0.835,-0.86);
		glVertex2f(-0.815,-0.86);
		glVertex2f(-0.815,-0.845);
	glEnd();	
	//Rear Tyres
	glColor3f(0,0,0);
	x=-3.1; y=0;
	float r = 0.02;
	int num_segments = 360;
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float cx = r * cosf(theta);//calculate the x component
        float cy = r * sinf(theta);//calculate the y component

        glVertex2f(-0.428+ cx + x*0.16666, -0.895+cy + y*0.1625);//output vertex

    }
    glEnd();
    x=-2.6; y=0;
	
	//Front tyres
	
	glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float cx = r * cosf(theta);//calculate the x component
        float cy = r * sinf(theta);//calculate the y component

        glVertex2f(-0.428+ cx + x*0.16666, -0.895+cy + y*0.1625);//output vertex

    }
    glEnd();
}

void draw_player(float cx, float cy)
{
	if(dead==1)
    {
    	glColor3f(0.0,0.0,0.0);
    	glBegin(GL_LINES);
    		glVertex2f(cx-0.05,cy+0.05);
    		glVertex2f(cx+0.05,cy-0.05);
    		glVertex2f(cx-0.05,cy-0.05);
    		glVertex2f(cx+0.05,cy+0.05);
    	glEnd();	
    }
	glLineWidth(3);
	if(!dead)
    	glColor3f(1.0,1.0,0.0);
    else
    	glColor3f(0.0,0.0,0.0);
    //HANDS OF FIREMAN
    glBegin(GL_QUADS);
    	glVertex2f(cx-0.01,cy-0.015); glVertex2f(cx-0.01,cy+0.015);
    	glVertex2f(cx-0.01,cy+0.015); glVertex2f(cx+0.015,cy+0.015);
    	glVertex2f(cx+0.015,cy+0.015); glVertex2f(cx+0.015,cy-0.015);
    	glVertex2f(cx+0.015,cy-0.015); glVertex2f(cx-0.01,cy-0.015);    	
    glEnd();
    //SHIRT OF FIREMAN
    if(!dead)
    glColor3f(1.0,0.0,0.0);
    else
    	glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    	glVertex2f(cx-0.01,cy-0.03); glVertex2f(cx-0.01,cy+0.02);
    	glVertex2f(cx-0.01,cy+0.02); glVertex2f(cx+0.01,cy+0.02);
    	glVertex2f(cx+0.01,cy+0.02); glVertex2f(cx+0.01,cy-0.03);
    	glVertex2f(cx+0.01,cy-0.03); glVertex2f(cx-0.01,cy-0.03);    	
    glEnd();
    if(!dead)
    	glColor3f(1,1,1);
    else
    	glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    	glVertex2f(cx+0.02,cy-0.002); glVertex2f(cx+0.02,cy+0.002);
    glEnd();
    //SKEWED HAND
    if(!dead)
    glColor3f(1,1,0);
    else
    	glColor3f(0.0,0.0,0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    	glVertex2f(cx-0.015,cy+0.015);
    	glVertex2f(cx+0.015,cy-0.015);
 	glEnd();
    //HEAD OF FIREMAN
    if(!dead)
    glColor3f(1.0,1.0,1.0);
    else
    	glColor3f(0.0,0.0,0.0);
    glPointSize(9.0);
    glBegin(GL_POINTS);
    	glVertex2f(cx,cy+0.03);
    glEnd();
    //HAT OF FIREMAN
    if(!dead)
    glColor3f(1.0,0.0,0.0);
    else
    	glColor3f(0.0,0.0,0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    	glVertex2f(cx,cy+0.04);
    glEnd();
    //LEGS OF FIREMAN
    if(!dead)
    glColor3f(1.0,1.0,0.0);
    else
    	glColor3f(0.0,0.0,0.0);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    	glVertex2f(cx-0.006,cy-0.04);glVertex2f(cx-0.006,cy-0.02);
    	glVertex2f(cx+0.004,cy-0.04);glVertex2f(cx+0.004,cy-0.02);
    glEnd();
    //SHOES OF FIREMAN
    if(!dead)
    glColor3f(0.0,0.0,0.0);
    else
    	glColor3f(0.0,0.0,0.0);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    	glVertex2f(cx-0.006,cy-0.05);glVertex2f(cx-0.006,cy-0.04);
    	glVertex2f(cx+0.004,cy-0.05);glVertex2f(cx+0.004,cy-0.04);
    glEnd();
    //FIRE-EX HEAD
    dead=0;
    glPushMatrix();
    glLoadIdentity();
	glColor3fv(color1[fire_index]);
	if(hose_point==1)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f(cx+0.01,cy+0.02);
			glVertex2f(cx+0.04,cy+0.04);
			glVertex2f(cx+0.04,cy);
		glEnd();
		 //FIRE EXTINGUISHER
		glLineWidth(10.0);
		glBegin(GL_LINES);
			glVertex2f(cx+0.02,cy-0.015);
			glVertex2f(cx+0.02,cy+0.015);
		glEnd();
	}
	else if(hose_point==2)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f(cx-0.01,cy+0.02);
			glVertex2f(cx-0.04,cy+0.04);
			glVertex2f(cx-0.04,cy);
		glEnd();
		 //FIRE EXTINGUISHER
		glLineWidth(10.0);
		glBegin(GL_LINES);
			glVertex2f(cx-0.02,cy-0.015);
			glVertex2f(cx-0.02,cy+0.015);
		glEnd();
	}
	else if(hose_point==3)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f(cx-0.01,cy+0.02);
			glVertex2f(cx-0.02,cy+0.06);
			glVertex2f(cx,cy+0.06);
		glEnd();
		 //FIRE EXTINGUISHER
		glLineWidth(10.0);
		glBegin(GL_LINES);
			glVertex2f(cx+0.02,cy-0.015);
			glVertex2f(cx+0.02,cy+0.015);
		glEnd();
	}
	glPopMatrix();
	
	if(fire_index)
	{	fire_index=0;
		usleep(100000);
	}
}


void plot_player(int position)
{
	
	//double x, y, x_increment = 0.16666, y_increment = 0.1625, x_pos, y_pos;
	
	if(y_pos<=0.667)
	{
		
			glColor3f(0.3, 0, 0);
			x = -0.42;
			y = -0.86;
		
		int units_place = position%6;
		int tens_place = position/6;


		if((tens_place%2 == 0) && (units_place != 0))
		{
			x_pos = x+x_increment*(units_place-1);
			y_pos = y+y_increment*tens_place;
			hose_point=1;
		}
		else if((tens_place%2 != 0) && (units_place == 0))
		{
			x_pos = x+x_increment*5;
			y_pos = y+y_increment*(tens_place-1);
			hose_point=3;
			
			
		}
		else if(units_place != 0)
		{
			x_pos = x+x_increment*(6-(units_place));
			y_pos = y+y_increment*tens_place;
			hose_point=2;
		}
		else
		{
			x_pos = x;
			y_pos = y+y_increment*(tens_place-1);
			hose_point=3;
		}
		if(count==0)
		{
			draw_player(x_pos-0.42,y_pos+0.1625);
			
		}
		else
		{
			draw_player(x_pos, y_pos);
			
		}
		count++;
	}
	else
		y_pos=0.667;
}

void init_snakes_ladders()
{	
	snakes[5] = 1;
	snakes[7] = 1;
	snakes[13] = 1;
	snakes[19] = 1;
	snakes[33] = 1;
	snakes[38] = 1;
	snakes[45] = 1;
	snakes[51] = 1;
	snakes[59] = 1;
}

void remove_fire()
{
	if(!fire_enable)
	{
		for(int i=0;i<60;i++)
		{
			snakes[i]=0;
		}
	}
}
