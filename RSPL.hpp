#ifndef RSGL
#include <RSGL/RSGL.hpp>
#endif

namespace RSGL{
    enum enitytype{ platform, object };
    struct enity{
        enitytype et;
        Shape shape;
	bool water=false; int Float=0;
        enity(RSGL::rect rect,enitytype type ){ et=type; r=rect; shape=RECT; }
        enity(RSGL::circle circle,enitytype type ){ et=type; c=circle; shape=CIRCLE; }
        enity(RSGL::triangle triangle,enitytype type ){ et=type; t=triangle; shape=TRIANGLE; }
        enity(std::array<RSGL::point, 2> line,enitytype type ){ et=type; l=line; shape=LINE; }
        bool collide(std::vector<enity> es, RSGL::point dir={0,0});
	bool Collide(std::vector<enity> es, RSGL::point dir={0,0});

	bool fall(std::vector<enity> es){
  	    if (jumping && !jFall) return false;
            if (et == platform) return false;
            bool collide=false;
	    static int counter=0;
            for (int i=0; i < es.size(); i++){
                if (collide) return false;
                switch(shape){
                            case RECT: 
                                if (es.at(i).shape == RECT){ collide = RSGL::RectCollideRect({r.x+1,r.y+r.length-1,r.width-1,1},es.at(i).r);}
                                else if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollideRect(es.at(i).c,{r.x+1,r.y+r.length-1,r.width-1,1});
                                else if (es.at(i).shape == TRIANGLE){} 
                                else{} break;
                            case CIRCLE: 
                                if (es.at(i).shape == RECT) collide = RSGL::CircleCollideRect({c.x+1,c.y+c.radius-1,c.radius-1},es.at(i).r);
                                else if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollide(es.at(i).c,{c.x+1,c.y+c.radius-1,c.radius-1});
                                else if (es.at(i).shape == TRIANGLE){} 
                                else collide = RSGL::CircleCollideLine({c.x+1,c.y+c.radius-1,c.radius-1},l.at(0),l.at(1)); break;
                            case TRIANGLE:
                                break;
                            case LINE:
                                if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollideLine(es.at(i).c,l.at(0),l.at(1));
                            default: break;
                }
                if ((!es.at(i).water && collide) || jumping) counter=0;
                if (Float == 1 && es.at(i).water && collide && !counter){ counter = RSGL::timer(5); return counter; }
                if (!Float && es.at(i).water) collide=false;
      	    }
            return !collide;
         }
	void jump(int vertexY,int jumpLimit=1){
		static int jump=0;
		if (!jumping) jump=0;
		if (jump < jumpLimit) { jFall=false; jump++; jVertexY=vertexY; jumping=true; }
	}
	bool jump(std::vector<enity> es){
		if (!jumping) return false;
		static int y=0;
		if (y == jVertexY){ jFall=true; y=0; }
		if (jFall && !fall(es)){ jumping=false; jFall=false; } 
		if (jFall) return false;
		y++;
		return true;
	}
	int ifCollide(std::vector<enity> es, RSGL::point dir,int val){ return collide(es,dir) ? 0 : val; }
	bool jumping=false,jFall=false; int jVertexY;
        RSGL::rect r;
        RSGL::circle c;
        RSGL::triangle t;
        std::array<RSGL::point, 2> l;
    };
};

bool RSGL::enity::collide(std::vector<RSGL::enity> es, RSGL::point dir){
    bool collide=false;
        for (int i=0; i < es.size(); i++){
    if (collide) return true;
    switch(shape){
        case RECT:
                if (es.at(i).shape == RECT){ collide = RSGL::RectCollideRect({r.x+dir.x,r.y+dir.y,r.width,r.length},es.at(i).r);}
                else if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollideRect(es.at(i).c,{r.x+dir.x,r.y+dir.y,r.width,r.length});
                else if (es.at(i).shape == TRIANGLE){}
                else{} break;
            case CIRCLE:
                if (es.at(i).shape == RECT) collide = RSGL::CircleCollideRect({c.x+dir.x,c.y+dir.y,c.radius},es.at(i).r);
                else if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollide(es.at(i).c,{c.x+dir.x,c.y+dir.y,c.radius});
                else if (es.at(i).shape == TRIANGLE){}
                else collide = RSGL::CircleCollideLine({c.x+dir.x,c.y+dir.y,c.radius},l.at(0),l.at(1)); break;
            case TRIANGLE:
                break;
            case LINE:
                if (es.at(i).shape == CIRCLE) collide = RSGL::CircleCollideLine(es.at(i).c,l.at(0),l.at(1));
            default: break;
            }
    if (!fall({es.at(i)}) && !jumping) collide=false;
    }
        return collide;
}

bool RSGL::enity::Collide(std::vector<RSGL::enity> es, RSGL::point dir){ collide(es,dir); }