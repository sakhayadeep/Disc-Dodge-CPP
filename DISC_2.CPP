#include<conio.h>
#include<fstream.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>

int i=0,j=0,pnt=0,s=0;
int c1x=1,c1y=2,c2x=2,c2y=2,c3x=2,c3y=1;
	struct coord{	int x;
			int y;
			}ball,item,ob1,ob2,ob3;
int trans,gmmode,nxtlvl;

void main();
void change();
void obj_colour();
void obj_move(int &x,int &y,int &cx,int &cy);
void obj_gameover(int &gx,int &gy);
void obj_inside(int &x,int &y);
void obj_outside(int pat,int col,int &x,int &y);
void obj_t();

void main()
{	clrscr();
	time_t strt,end=0;
	s=pnt=i=j=0;
	trans=2;
	gmmode=0;
	nxtlvl=0;
	////////////declarations///////////////////
	int gd=DETECT,gm=0;
	ball.x=ball.y=item.x=item.y=ob1.x=ob1.y=ob2.x=ob2.y=ob3.x=ob3.y=0;

	long int k=0;

	char ch='\0',exitq='\0';
	int col=1;
	////////////graphic initialisation////////
	initgraph(&gd,&gm,"c:\\TurboC3\\BGI");
	////////////welcome screen////////////////
	while(!kbhit())
	{       cleardevice();
		settextstyle(1,0,7);
		setcolor(col);
		outtextxy((getmaxx()/2)-170,(getmaxy()/2)-50,"DISC DODGE");
		settextstyle(0,0,1);
		setcolor(WHITE);
		outtextxy((getmaxx()/2)-90,(getmaxy()/2)+50,"press any key to continue");
		outtextxy((getmaxx()/2)-90,(getmaxy()/2)+70,"SAKHAYADEEP NATH");
		outtextxy((getmaxx()/2)-30,10,"StepWISE");
		delay(500);
		col++;
		if(col>15)
			col=1;
	}
	exitq=getch();
	if(exitq==27)
		exit(0);
	/////////////////////////////////////////



	////////////level selection//////////////
	restorecrtmode();
	_setcursortype(_NOCURSOR);
	cout<<"\n\nSELECT YOUR GAME MODE:";
	cout<<"\n(1).FREE PLAY\n(2).SERIES\nENTER YOUR CHOICE:";
	cin>>gmmode;
	if(gmmode==2)
		s=1;

	if(gmmode==1)
	{
	speed:
	clrscr();
	cout<<"\n\nSELECT YOUR LEVEL(1-10):";
	cin>>s;
	if(s<1||s>10)
	goto speed;
	}


	////////////game starts///////////////////
	setgraphmode(getgraphmode());
	////////////coordinates of balls//////////
	ball.x=getmaxx()/2;
	ball.y=getmaxy()/2;
	item.x=rand()%getmaxx();
	item.y=rand()%getmaxy();
	::ob1.x=100;  ::ob2.x=450;  ::ob3.x=120;
	::ob1.y=100;  ::ob2.y=450;  ::ob3.y=300;
	setbkcolor(8);
	////////////main loop/////////////////////
	strt=time(NULL);
	while(1)

	{
		if(gmmode==2)
			if(nxtlvl==5)
			{	s++;
				nxtlvl=0;
			}


	////////////points display////////////////
	outtextxy(463,20,"POINT=");
	gotoxy(65,2);
	cout<<pnt;
	////////////TIME ELAPSED//////////////////

	outtextxy(463,36,"LEVEL=");
	gotoxy(65,3);
	cout<<s;

	////////////main circle///////////////////
	setfillstyle(LINE_FILL,15);
	circle(ball.x,ball.y,10);
	floodfill(ball.x,ball.y,getmaxx());

	////////////our object////////////////////
	setfillstyle(11,13);
	if(k%5==0)
		circle(item.x,item.y,8);
	else if(k%3==0)
		circle(item.x,item.y,9);
	else
		circle(item.x,item.y,10);
	k+=7;
	if(k>1000)k=1;
	floodfill(item.x,item.y,getmaxx());
	///////change of coordinates of object////
	change();

	////////////obstacle 1////////////////////
	obj_outside(2,14,ob1.x,ob1.y);
	obj_move(ob1.x,ob1.y,c1x,c1y);
	obj_gameover(ob1.x,ob1.y);
	////////////obstacle 2////////////////////
	obj_outside(7,4,ob2.x,ob2.y);
	obj_move(ob2.x,ob2.y,c2x,c2y);
	obj_gameover(ob2.x,ob2.y);
	////////////obstacle 3////////////////////
	obj_outside(9,3,ob3.x,ob3.y);
	obj_move(ob3.x,ob3.y,c3x,c3y);
	obj_gameover(ob3.x,ob3.y);




	////////////playing///////////////////////
	if(kbhit())
	{       ch=getch();
		if(ch==72)
		{	i=0;
			j=-10;
		}
		else if(ch==75)
		{	i=-10;
			j=0;
		}
		else if(ch==77)
		{	i=10;
			j=0;
		}
		else if(ch==80)
		{	i=0;
			j=10;
		}
		else if(ch==27)
		{
			closegraph();
			main();
		}
		else if(ch=='a'||ch=='A')
		{	if(trans==1)
			{	trans=2;
				i=j=0;
			}
			else if(trans==2)
				trans=1;
		}
		if(trans==1)
			obj_t();
	}
	if(trans==2)
		obj_t();


	delay(25);
	cleardevice();

	//////////////////////////////////////////////////////////////////////
	///////////////////////////INSTRUCTIONS/////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	{rectangle(1,getmaxy()-39,getmaxx(),getmaxy());
	outtextxy(3,getmaxy()-30,"Esc= EXIT");
	outtextxy(3,getmaxy()-15,"A= MANUAL/AUTO");
	outtextxy(200,getmaxy()-30,"MOVEMENT KEYS: \030(UP) \031(DOWN) \032(LEFT) \033(RIGHT)");
	}
	end=time(NULL);

	}

}

void change()
{
	if((ball.x-10<=item.x+8&&ball.x+10>=item.x-8)&&(ball.y-10<=item.y+8&&ball.y+10>=item.y-8))
		{
		item.x=random(getmaxx()-70);
		item.y=random(getmaxy()-70);
			{	pnt+=s;
				nxtlvl++;
			}         //to increase the points
		}
}

void obj_outside(int pat,int col,int &x,int &y)
{      	setfillstyle(pat,col);
	circle(x,y,18);
	floodfill(x,y,getmaxx());
	obj_inside(x,y);
}
void obj_inside(int &x,int &y)
	{      static int colin=1;
	       static int c=0;

		if(colin==1)
		{	c++;
			if(c%30==0)
			colin=4;
		}
		else if(colin==4)
		{	c++;
			if(c%30==0)
			colin=1;
		}


		setfillstyle(1,colin);
		circle(x,y,6);
		floodfill(x,y,getmaxx());

	}

void obj_move(int &x,int &y,int &cx,int &cy)
{

	if(cx==1)
	{	x+=::s+3;
		if(x>=getmaxx())
			cx=2;
	}
	else if(cx==2)
	{	x-=::s+3;
		if(x<=18)
			cx=1;
	}
	if(cy==1)
	{	y+=::s+3;
		if(y>=getmaxy()-58)
			cy=2;
	}
	else if(cy==2)
	{	y-=::s+3;


		if(y<=18)
			cy=1;
	}
}

void obj_gameover(int &gx,int &gy)
{	if((ball.x-10<=gx+17&&ball.x+10>=gx-17)&&(ball.y-10<=gy+17&&ball.y+10>=gy-17))
	{
		cleardevice();
		outtextxy((getmaxx()/2)-30,(getmaxy()/2)-9,"GAME OVER");
		outtextxy((getmaxx()/2)-27,(getmaxy()/2)+4,"POINT:");
		gotoxy(44,16);
		cout<<::pnt;
		getch();
		//////////////////////////////////////////////////////////////////
		{
		struct score{	int pnt;
				char name[20];
				}player,history;
		player.pnt=pnt;
		//////////////////////////////////////////////////////////////////
		if(gmmode==1)
		{
		fstream hscore("FHIGHSCO.DAT",ios::in|ios::out|ios::binary);
		hscore.read((char*)&history,sizeof(history));
		///////////////////////////////////////////////////////////////////
		if(history.pnt<player.pnt)
		{       restorecrtmode();
			cout<<"\n\nENTER YOUR NAME(max=20 characters):";
			gets(player.name);
			hscore.write((char*)&player,sizeof(player));
			hscore.close();
			setgraphmode(getgraphmode());
		}
		else
		{       outtextxy((getmaxx()/2)-27,(getmaxy()/2)+20,"HIGHSCORE");
			outtextxy((getmaxx()/2)-27,(getmaxy()/2)+34,history.name);
			gotoxy(43,18);
			cout<<history.pnt;

		}
	       ///////////////////////////////////////////////////////////////////////////
		}
		else if(gmmode==2)
		{	 fstream hscore("SHIGHSCO.DAT",ios::in|ios::out|ios::binary);
			hscore.read((char*)&history,sizeof(history));
		/////////////////////////////////////////////////////////////////////////
		if(history.pnt<player.pnt)
		{       restorecrtmode();
			cout<<"\n\nENTER YOUR NAME (max=20 characters):";
			gets(player.name);
			hscore.write((char*)&player,22);
			hscore.close();
			setgraphmode(getgraphmode());
		}
		else
		{    	outtextxy((getmaxx()/2)-27,(getmaxy()/2)+20,"HIGHSCORE");
			outtextxy((getmaxx()/2)-27,(getmaxy()/2)+34,history.name);
			gotoxy(43,18);
			cout<<history.pnt;


		}
		///
		}
		//////
		}
		////////
		delay(1000);
		getch();
		closegraph();
		main();
	}
}
void obj_t()
{       ////////////changing the coordinates//////
		{	ball.x+=i;
			if(ball.x>=getmaxx())
				ball.x=10;
			else if(ball.x<=9)
				ball.x=getmaxx();
	////////////changing the coordinates//////
			ball.y+=j;
			if(ball.y>=getmaxy()-50)
				ball.y=1;
			else if(ball.y<=1)
				ball.y=getmaxy()-50;
		}
}
