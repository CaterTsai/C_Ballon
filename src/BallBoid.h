#ifndef BALL_BOID
#define BALL_BOID


#include "ofMain.h"

class BallBoid{

public:
	
	static float REFLECT;
	ofVec2f location;

	BallBoid(float x_,float y_,float rad_,int tag_){
		location=ofVec2f(x_,y_);
		
		
		acc=ofVec2f(0,0);
		maxSpeed=12.0;
		maxForce=5.0;
		
		shrinking=false;
		dest_shrink=1;

		vel=ofVec2f(maxSpeed,0);
		vel.rotate(ofRandom(TWO_PI));

		tag=tag_;
		radius=rad_;
	}

	void flock(vector<BallBoid> &boids){
		
		ofVec2f sep_sum=ofVec2f(0);
		ofVec2f ali_sum=ofVec2f(0);
		ofVec2f coh_sum=ofVec2f(0);

		int sep_count=0,ali_count=0,coh_count=0;;

		
		int mboid=boids.size();


		for(int i=0;i<mboid;++i){
			BallBoid other=boids[i];
		
			ofVec2f sep=separate(other);
			ofVec2f ali=align(other);
			ofVec2f coh=cohesion(other);

			if(sep.length()>0){
				sep_sum+=sep;
				sep_count++;
			}

			if(ali.length()>0){
				ali_sum+=ali;
				ali_count++;
			}

			if(coh.length()>0){
				coh_sum+=coh;
				coh_count++;
			}

		}

		ofVec2f sep_steer=ofVec2f(0);
		if(sep_count>0){
			sep_sum/=sep_count;
			//sep_sum.scale(maxForce);

			sep_steer=sep_sum-vel;
			sep_steer.limit(maxForce);
		}		

		ofVec2f ali_steer=ofVec2f(0);
		if(ali_count>0){
			ali_sum/=sep_count;
			//ali_sum.scale(maxForce);

			ali_steer=ali_sum-vel;
			ali_steer.limit(maxForce);
		}

		ofVec2f coh_steer=ofVec2f(0);
		if(coh_count>0){
			coh_sum/=coh_count;
			//coh_sum.scale(maxForce);

			coh_steer=coh_sum-vel;
			coh_steer.limit(maxForce);
		}		


		sep_steer*=force_com.x;
		ali_steer*=force_com.y;
		coh_steer*=force_com.z;

		applyForce(sep_steer);
		applyForce(ali_steer);
		applyForce(coh_steer);

	}
	void update(){
		// println(acc);
		
		

		if(location.x<0) acc.x+=REFLECT;
		if(location.x>cCANVAS_WIDTH) acc.x-=REFLECT;

		if(location.y<0) acc.y+=REFLECT;
		if(location.y>cCANVAS_HEIGHT) acc.y-=REFLECT;
		
			ofVec2f center=ofVec2f(cCANVAS_WIDTH/2,cCANVAS_HEIGHT/2);
			/*if(to_center.length()>orig_shrink*dest_shrink) location=center+to_center*ofRandom(.8,1);
			else shrinking=false;*/
		if(shrinking){
			ofVec2f to_center=center-location;
			to_center.scale(maxForce*dest_shrink);
			acc+=to_center;
			if(dest_shrink<1) dest_shrink+=.05;

		}else{
			if(dest_shrink<1){
				ofVec2f out_center=location-center;
				out_center.scale(maxForce*(1-dest_shrink));
				acc+=out_center;
				dest_shrink+=.02;
			}
		}

		vel+=acc;
		vel.limit(maxSpeed);
		acc*=0;
		
		location+=vel;
	}

	void draw(){
		ofSetColor(0,0,255);
		ofFill();
		ofEllipse(location.x,location.y,radius,radius);

	}

	void setForce(ofVec3f set_force){
		force_com=set_force;
	}

	void setShrinking(bool set_shrink){
		
		shrinking=set_shrink;
		dest_shrink=ofRandom(0.01,0.1);
		//orig_shrink=location.distance(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));

		
	}

private:
	
	

	
	ofVec2f vel;
	ofVec2f acc;

	float maxSpeed;
	float maxForce;
	vector<int> nbs;
	float dest_shrink;//=random(0.1,0.8);
	bool shrinking;//=false;
	float orig_shrink;

	ofVec3f force_com;//=new PVector(0.1,0.1,0.1);

	int tag;
	float radius;

	
	
	
	void applyForce(ofVec2f force){
		acc+=force;
	}
	

	ofVec2f separate(BallBoid& other){
		
		
		float d=location.distance(other.location);
		 	
		if(d>60) return ofVec2f(0);

		ofVec2f diff=location-other.location;
		diff.normalize();
		// diff.div(d);

		return diff;

	}
	ofVec2f cohesion(BallBoid& other){

		
		float d=location.distance(other.location);
		if(other.tag!=tag) d*=.2;
		 	
		if(d<200) return ofVec2f(0);

		ofVec2f diff=other.location-location;
		diff.normalize();
		
		return diff;

	}
	ofVec2f align(BallBoid& other){

			
		if(other.tag!=tag) return ofVec2f(0);

		float d=location.distance(other.location);
		if(other.tag!=tag) d*=.5;

		if(d>150) return ofVec2f(0);

		return other.vel;
			
	}


};


#endif