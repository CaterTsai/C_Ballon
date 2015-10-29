#ifndef BALL_GROUP
#define BALL_GROUp

#include "BallBoid.h"

class BallGroup{
private:

	float* arr_center_x;
	float* arr_center_y;
	float* arr_center_rad;
	float* arr_color;
	
	ofShader shader_metaball;
	vector<BallBoid> arr_bd;
	
	ofVec3f bd_force;
	bool is_shrinking;

	ofVec3f ball_color;
	void setForce(ofVec3f set_force){
		
		for(auto& bd:arr_bd){
			bd.setForce(set_force);
		}
		bd_force=set_force;
		cout<<bd_force<<endl;
	}
	float getPositionColor(float x,float y){
		
		float weight_sum=0;
		int mboid=MIN(arr_bd.size(),150);
		for(int i=0;i<mboid;++i){
			float dist=sqrt((x-arr_center_x[i])*(x-arr_center_x[i])+
							(y-arr_center_y[i])*(y-arr_center_y[i]));		
		
			float w=(dist<arr_center_rad[i])?1.0:pow(arr_center_rad[i],DEGREE)/pow(dist,DEGREE);
	
			weight_sum+=w;
		
		}
		return weight_sum;

	}

public:
	static float THRES;
	static int M_GROUP;
	static int MAX_BALL_COUNT;
	static float DEGREE;

	bool draw_by_shader;
	
	int GRID_X;
	int GRID_Y;

	int BALL_RAD;

	BallGroup(){		
		arr_center_x=new float[MAX_BALL_COUNT];
		arr_center_y=new float[MAX_BALL_COUNT];
		arr_center_rad=new float[MAX_BALL_COUNT];
		arr_color=new float[MAX_BALL_COUNT];

		bd_force=ofVec3f(.3,.3,.3);

		is_shrinking=false;
		draw_by_shader=false;

		GRID_X=20;
		GRID_Y=10;

		BALL_RAD=20;
	}
	~BallGroup()
	{
		delete [] arr_center_x;
		delete [] arr_center_y;
		delete [] arr_center_rad;
		delete [] arr_color;
	}
	
	void setup(){
		
		shader_metaball.load("metaball");
		////shader_metaball.load("shader/test");

		/*shader_metaball.begin();
		shader_metaball.setUniform1f("width",ofGetWidth());
		shader_metaball.setUniform1f("height",ofGetHeight());
		shader_metaball.setUniform1f("mlayer",12.0);

		shader_metaball.setUniform1f("threshold",THRES);

		shader_metaball.end();*/
	}
	void draw(){
		
		ofSetColor(0);
		//ball_color=ofVec3f(abs(255.0*sin(p+PI/3)),abs(255.0*cos(p))+200,abs(155.0*sin(p+PI*1.3)+100));

		if(draw_by_shader){
			shader_metaball.begin();
			/*shader_metaball.setUniform1f("width",ofGetWidth());
			shader_metaball.setUniform1f("height",ofGetHeight());*/
			shader_metaball.setUniform1f("mlayer",12.0);

			shader_metaball.setUniform1f("dist_thres",THRES);
			shader_metaball.setUniform1f("dist_degree",DEGREE);
			shader_metaball.setUniform1f("mgroup",M_GROUP);
		

			shader_metaball.setUniform1fv("balls_x",arr_center_x,MAX_BALL_COUNT);
			shader_metaball.setUniform1fv("balls_y",arr_center_y,MAX_BALL_COUNT);
			shader_metaball.setUniform1fv("balls_rad",arr_center_rad,MAX_BALL_COUNT);
			shader_metaball.setUniform1fv("balls_color",arr_color,MAX_BALL_COUNT);

			shader_metaball.setUniform1f("mballs",arr_bd.size());
		
			
			shader_metaball.setUniform3f("ball_color",ball_color.x,ball_color.y,ball_color.z);
		
			ofRect(0,0,cCANVAS_WIDTH,cCANVAS_HEIGHT);


			shader_metaball.end();
		}else{
			float ex=cCANVAS_WIDTH/(float)GRID_X;
			float ey=cCANVAS_HEIGHT/(float)GRID_Y;

			for(int i=0;i<GRID_X;++i){
				for(int j=0;j<GRID_Y;++j){
					float weight=getPositionColor((i+.5)*ex,(j+.5)*ey);
					
					if(weight<THRES) continue;
					
					ofSetColor(ball_color.x,ball_color.y,ball_color.z,ofMap(weight,0,1.0,.65,1.0)*255.0);
					ofFill();
					ofRect(i*ex,j*ey,ex,ey);
				}

			}
		}
		
		
		/*int mboid=arr_bd.size();
		for(int i=0;i<mboid;++i){
			arr_bd[i].draw();
		}*/

	}
	void update(){

	
		for(auto& bd:arr_bd){
			bd.flock(arr_bd);
			bd.update();
		}

		for(int i=0;i<arr_bd.size();++i){		
			arr_center_x[i]=arr_bd[i].location.x;
			arr_center_y[i]=arr_bd[i].location.y;
			
		}

	}

	inline void setBallColor(ofColor color)
	{
		ball_color.set(color.r, color.g, color.b);
	}

	void addBall(float x,float y){
		
		if(arr_bd.size()>=MAX_BALL_COUNT) return;
		
		int index=arr_bd.size();
		arr_center_x[index]=x;
		arr_center_y[index]=cCANVAS_HEIGHT-y;
		// int len=center_info.length;
		// center_info[len][0]=x;
		// center_info[len][1]=x;


		float rad=ofRandom(1,BALL_RAD);
		arr_center_rad[index]=rad;
		// center_info[len][2]=rad;
	
		//center_color.append(random(2)<1?1:0);
		// vel.add(new PVector(random(-2,2),random(-2,2)));

		int igroup=(int)ofRandom(M_GROUP);
		arr_color[index]=igroup;

		BallBoid b=BallBoid(x,cCANVAS_HEIGHT-y,rad,igroup);
		b.setForce(bd_force);
		arr_bd.push_back(b);

	}

	void reset(int init_count){
		arr_bd.clear();

		for(int i=0;i<init_count;++i){
			addBall(ofRandom(cCANVAS_WIDTH),ofRandom(cCANVAS_HEIGHT));
		}
	}

	void addSepForce(){
		setForce(ofVec3f(bd_force.x+.1,bd_force.y,bd_force.z));
	}
	void subSepForce(){
		setForce(ofVec3f(bd_force.x-.1,bd_force.y,bd_force.z));
	}

	void addAliForce(){
		setForce(ofVec3f(bd_force.x,bd_force.y+.1,bd_force.z));
	}
	void subAliForce(){
		setForce(ofVec3f(bd_force.x,bd_force.y-.1,bd_force.z));
	}
	void addCohForce(){
		setForce(ofVec3f(bd_force.x,bd_force.y,bd_force.z+.1));
	}
	void subCohForce(){
		setForce(ofVec3f(bd_force.x,bd_force.y,bd_force.z-.1));
	}

	void toggleShrink(){
		is_shrinking=!is_shrinking;
		for(auto& bd:arr_bd){
			bd.setShrinking(is_shrinking);
		}
		
		ofLog()<<"shrink: "<<is_shrinking<<endl;
	}

};


#endif