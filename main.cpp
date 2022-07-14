#include "RSPL.hpp"
bool running = true;

RSGL::window win("name",{500,500,500,500},{255,255,255});


int jump=0; int jumpLimit=2;

RSGL::enity floor((RSGL::rect){0,400,win.r.width-180,100},RSGL::platform); 
RSGL::enity wall((RSGL::rect){160,380,20,20},RSGL::platform);
RSGL::enity top((RSGL::rect){300,340,20,20},RSGL::platform);
RSGL::enity guy((RSGL::rect){200,200,20,20}, RSGL::object);
RSGL::enity pool=floor, poolFloor=floor;

int main(){
    pool.water=true; pool.r.x=320; guy.Float=1;
    poolFloor.r.y+=80; poolFloor.r.x=320;
    RSGL::enity wall2 = wall; wall2.r.x+=80;
    while (running){
        win.checkEvents();
	switch (win.event.type){
            case RSGL::quit: running=false; break;
            case RSGL::KeyReleased:
		if (win.event.key == "Up" || win.event.key == "Space") guy.jump(20,jumpLimit);
            	else if (win.event.key == "Left") guy.r.x-=guy.ifCollide({wall,wall2,top,floor},{-5,0},5);
		else if (win.event.key == "Right") guy.r.x+=guy.ifCollide({wall,wall2,top,floor},{5,0},5);
		break;
	    default: break;
        }
        if (guy.fall({floor,wall,wall2,top,poolFloor,pool})) guy.r.y+=5;
	else if (guy.jump({floor,wall, wall2,top,pool,poolFloor})) guy.r.y-= guy.ifCollide({top},{0,-5},5);
	RSGL::drawRect(guy.r,{255,0,0});
        RSGL::drawRect(floor.r,{255,250,0});
	RSGL::drawRect(wall.r,{255,250,0});
	RSGL::drawRect(wall2.r,{255,250,0});
	RSGL::drawRect(top.r,{255,250,0});
        RSGL::drawRect(poolFloor.r,{255,250,0});
	RSGL::drawRect(pool.r,{0,50,255,125});
        
        win.clear();
    } win.close();
}