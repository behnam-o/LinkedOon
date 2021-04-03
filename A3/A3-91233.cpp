#include "rsdl.h"
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <cstdlib>

const int SCREEN_HEIGHT=450;
const int SCREEN_WIDTH=900;
const int FPS=35;
const int INIT_SCORE=10;
const int V0=1000;
const int THIEF_X=300;


string int_to_str(int n)
{
	string str="";
	if (n==0)
	{
		str.push_back('0');
		return str;
	}

	while(n!=0)
	{
		str.insert(str.begin(),(char)(n%10+48));
		n/=10;
	}

	return str;
}

void draw_rockets(window& w,vector<int> locations,int state)
{
	string s=int_to_str(state);
	for (int i = 0; i < locations.size(); ++i)
	{
		if (locations[i]<900 && locations[i]>-100)
		{
			w.draw_transparent_bmp("images/rocket/"+s+".bmp",locations[i],330,WHITE);
		}
		
	}
}
void draw_coins(window& w,vector<int> locations_x,vector<int>locations_y,int state)
{
	string s=int_to_str(state);
	for (int i = 0; i < locations_x.size(); ++i)
	{
		w.draw_transparent_bmp("images/coin/"+s+".bmp",locations_x[i],locations_y[i],WHITE);
	}
}
void draw_coin(window& w,int x,int y,int state)
{
	string s=int_to_str(state);
	w.draw_transparent_bmp("images/coin/"+s+".bmp",x,y,WHITE);
}
void draw_background(window& w,int x)
{

	w.draw_bmp("images/GND/platform.bmp",x,0);
	w.draw_bmp("images/GND/platform.bmp",x+900,0);

}
void draw_ground(window& w,vector<int> pit_locations)
{
	

	for (int i = 0; i < pit_locations.size(); ++i)
		{
			w.draw_transparent_bmp("images/GND/gnd3.bmp",pit_locations[i]-115,400,WHITE);
			w.draw_transparent_bmp("images/GND/gnd2.bmp",pit_locations[i]+15,400,WHITE);
			if(i==0)
			{
				
				int k=pit_locations[0]-215;
				while(k>-500)
				{
					w.draw_transparent_bmp("images/GND/gnd1.bmp",k,400,WHITE);
					k-=100;
				}
			}
			else
			{
				int k=pit_locations[i]-215;
				while(k>pit_locations[i-1]+115)
				{
					w.draw_transparent_bmp("images/GND/gnd1.bmp",k,400,WHITE);
					k-=100;
				}
				w.draw_transparent_bmp("images/GND/gnd1.bmp",pit_locations[i-1]+115,400,WHITE);
			}
			if(i==pit_locations.size()-1)
			{
				if(pit_locations[i]<900)
				{
					int k=pit_locations[i]+115;
					while(k<900)
					{
						w.draw_transparent_bmp("images/GND/gnd1.bmp",k,400,WHITE);
						k+=100;
					}
				}

			}
		}	



}

void draw_thief(window& w,int mode,int state)
{
	string s=int_to_str(state);
	if (mode==0)
	{
		w.draw_transparent_bmp("images/character/run/"+s+".bmp",THIEF_X,250,WHITE);
	}
	else if (mode==1)
	{
		w.draw_transparent_bmp("images/character/jump/"+s+".bmp",THIEF_X,158,WHITE);
	}
	else if (mode==2)
	{
		w.draw_transparent_bmp("images/character/shooting/"+s+".bmp",THIEF_X-10,250,WHITE);
	}
}
void fill_location_vectors(vector<int>& rocket_locations,
							vector<int>& coin_locations_x,
							vector<int>& coin_locations_y,
							vector<int>& pit_locations)
{
	rocket_locations.clear();
	coin_locations_x.clear();
	coin_locations_y.clear();
	pit_locations.clear();

	ifstream myfile;
	myfile.open("elements.txt");
	string element;

	while(getline(myfile,element))
	{
		if(element.substr(0,6)=="Rocket")
		{
			element=element.substr(7);
			rocket_locations.push_back(50*atoi(element.c_str()));

		}
		else if(element.substr(0,4)=="Coin")
		{
			element=element.substr(5);
			coin_locations_x.push_back(50*atoi(element.substr(0,element.find(' ')).c_str()));
			element=element.substr(element.find(' '));
			coin_locations_y.push_back(450-50*atoi(element.c_str()));
		}
		else if(element.substr(0,3)=="Pit")
		{
			element=element.substr(4);
			pit_locations.push_back(50*atoi(element.c_str()));

		}
	}
	myfile.close();
}
void draw_score(window& w,int score,int x,int y)
{
	w.draw_transparent_bmp("images/numbers/score.bmp",x,y,WHITE);
	vector<int> vec;
	if(score==0)
		w.draw_transparent_bmp("images/numbers/0.bmp",x+150,y,WHITE);

	while(score!=0)
	{
		vec.push_back(score%10);
		score/=10;
	}

	int length=vec.size();

	for (int i = 0; i < length; ++i)
	{
		int n=vec[length-i-1];
		string s="0";
		s[0]=n+48;
		w.draw_transparent_bmp("images/numbers/"+s+".bmp",x+150+39*i,y,WHITE);
	}
}




//-------------------------------------------------MAIN---------------------------------------------

int main()
{

	window win(SCREEN_WIDTH,SCREEN_HEIGHT);
	vector<int> rocket_locations;
	vector<int> coin_locations_x;
	vector<int> coin_locations_y;
	vector<int> pit_locations;

	
	int thief_state=1;
	int  rocket_state=1;
	int  coin_state=1;
	int coin_state_counter=0;
	int thief_state_counter=0;
	double v=0;
	int mode=0;
	bool half_speed=false;
	int score_timer=0;
	fill_location_vectors(rocket_locations,
						  coin_locations_x,
						  coin_locations_y,
						  pit_locations);

	clock_t current_time=0;
	clock_t dc=0;
	clock_t last_time=0;
	double x=0;
	double dt=0;
	double bg_x=0;
	int score=INIT_SCORE;
	bool quit=false;
	bool game_over=false;
	bool game_start=true;
	bool pause=false;
	while(!quit)
	{
		current_time=clock();
		dc=current_time-last_time;
		last_time=current_time;
		dt=((double)dc/CLOCKS_PER_SEC);

		if (game_start)
		{
			draw_background(win,0);
			win.draw_transparent_bmp("images/GND/Start.bmp",0,0,WHITE);
			win.update_screen();
			HANDLE(
				QUIT(quit=true);
				KEY_PRESS(q,{
					quit=true;
				});
				KEY_PRESS(s,{
					game_start=false;		
				});
			)
			
		}

		else if(!game_over && !pause)
		{
			
			
			// Handling Inputs
			HANDLE(
				QUIT(quit=true);
				KEY_PRESS(q,{
					quit=true;
				});
				KEY_PRESS(SPACE,{
					if(mode!=1)
					{
						mode=1;
						thief_state=1;
					}
				});
				KEY_PRESS(s,{
					if(score >=3 && mode==0)
					{
						mode=2;
						thief_state=1;
					}
				});
				KEY_PRESS(p,{
					pause=true;
				});
				KEY_PRESS(LEFT,{
					if(score>=2 && !half_speed)
					{
						half_speed=true;
						score-=2;
						score_timer=0;
					}
				});
				KEY_RELEASE(LEFT,{
					half_speed=false;
				});
				KEY_PRESS(RIGHT,{
					half_speed=false;
				});
			)
		
			//Calculating events
			rocket_state++;
			thief_state_counter++;

			if(thief_state_counter>=( (mode!=2 && half_speed)?2:1))
			{
				thief_state_counter=0;
				thief_state++;
			}
			
			coin_state_counter++;
			if(coin_state_counter>=3)
			{
				coin_state_counter=0;
				coin_state++;
			}


			v=600*pow(1.15,(x/2700)-1);
			if(score<=0) half_speed=false;
			if(half_speed)
				v/=2;
			x+=v*dt;

			score_timer++;
			if(score_timer>=0.7*FPS && half_speed)
			{
				score-=2;
				score_timer=0;
			}

			bg_x-=0.3*v*dt;
			if (bg_x<=-900)
			{
				bg_x=0;
			}

			for (int i = 0; i < rocket_locations.size(); ++i)
			{
				rocket_locations[i]-=(v*dt*1.2);
			}
			for (int i = 0; i < pit_locations.size(); ++i)
			{
				pit_locations[i]-=v*dt;
			}
			for (int i = 0; i < coin_locations_x.size(); ++i)
			{
				coin_locations_x[i]-=v*dt;
			}

			if(rocket_state==4)
				rocket_state=1;
			if(coin_state==5)
				coin_state=1;
			if(mode==0 && thief_state==9)
				thief_state=1;
			if(mode==1 && thief_state==10)
			{
				thief_state=1;
				mode=0;
			}
			if(mode==2 && thief_state==7)
			{

				mode=0;
				thief_state=1;
				score-=3;
				if(!rocket_locations.empty() && rocket_locations[0]<900 && rocket_locations[0] >THIEF_X+50)
				{
					rocket_locations.erase(rocket_locations.begin(),rocket_locations.begin()+1);
					score+=4;
				}

			}

			if(rocket_locations.empty())
			{
				for (int i = 0; i < 5; ++i)
				{
					rocket_locations.push_back(900+400*i+rand()%400);
				}
			}

			if(pit_locations[0] <-100)
			{	
				pit_locations.erase(pit_locations.begin(),pit_locations.begin()+1);
			}
			if(pit_locations.empty())
			{
				for (int i = 0; i < 5; ++i)
				{
					pit_locations.push_back(900+1400*i+rand()%700);
				}
			}
			if(coin_locations_x.empty())
			{
				for (int i = 0; i < 5; ++i)
				{
					coin_locations_x.push_back(900+400*i+rand()%400);
					coin_locations_y.push_back(200+rand()%140);
				}
			}
			if(rocket_locations[0] < THIEF_X+50)
			{	
				rocket_locations.erase(rocket_locations.begin(),rocket_locations.begin()+1);
				game_over=true;
			}

			for (int i = 0; i < pit_locations.size(); ++i)
			{
				if(pit_locations[i]<=THIEF_X+75 && pit_locations[i]>=THIEF_X+50 && mode!=1)
					game_over=true;
			}
			
			
			for (int i = 0; i < coin_locations_x.size(); ++i)
			{
					if( coin_locations_x[i]<THIEF_X+50 && coin_locations_x[i]>THIEF_X-50 &&
					(
					(coin_locations_y[i]>230 && coin_locations_y[i]<400 && mode!=1) 
					||
					(coin_locations_y[i]>160 && coin_locations_y[i]<280 && mode==1)
				  	)
				  	)
						{
							coin_locations_x.erase(coin_locations_x.begin()+i,coin_locations_x.begin()+i+1);
							coin_locations_y.erase(coin_locations_y.begin()+i,coin_locations_y.begin()+i+1);
							score++;
						}
					if(coin_locations_x[i]<-100)
					{
						coin_locations_x.erase(coin_locations_x.begin()+i,coin_locations_x.begin()+i+1);
						coin_locations_y.erase(coin_locations_y.begin()+i,coin_locations_y.begin()+i+1);
					}
			}

			



			//Updating Screen
			DELAY(1000/FPS-(clock()-current_time)*1000/CLOCKS_PER_SEC);
			// while(clock()-current_time<(33*CLOCKS_PER_SEC/1000)){}
			draw_background(win,bg_x);
			draw_ground(win,pit_locations);
			draw_rockets(win,rocket_locations,rocket_state);	
			draw_coins(win,coin_locations_x,coin_locations_y,coin_state);
			draw_thief(win,mode,thief_state);
			draw_score(win,score,0,0);
			win.update_screen();

		}
		else if(game_over)
		{
			HANDLE(
				QUIT(quit=true);
				KEY_PRESS(q,{
					quit=true;
				});
				KEY_PRESS(r,{
					thief_state=1;
					rocket_state=1;
					coin_state=1;
					coin_state_counter=0;
					thief_state_counter=0;
					v=0;
					mode=0;
					half_speed=false;
					score_timer=0;
					fill_location_vectors(rocket_locations,
										  coin_locations_x,
										  coin_locations_y,
										  pit_locations);
					x=0;
					bg_x=0;
					score=INIT_SCORE;
					game_over=false;
				});
				
			)
			draw_background(win,0);
			win.draw_transparent_bmp("images/GND/Over.bmp",0,0,WHITE);
			draw_score(win,score,340,150);
			win.update_screen();
		}
		else if(pause)
		{
			HANDLE(
				QUIT(quit=true);
				KEY_PRESS(q,{
					quit=true;
				});
				KEY_PRESS(p,{
					pause=false;
					half_speed=false;
				});
				
			)
			win.fill_rect(425,100,20,60,WHITE);
			win.fill_rect(455,100,20,60,WHITE);
			win.update_screen();
		}


	
	}

	return 0;
}

