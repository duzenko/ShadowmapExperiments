#pragma once

static std::default_random_engine random_engine;
static std::uniform_real_distribution<float> real_distribution( 0, 1 );

struct Vec {
	float x, y, z, w;
	Vec() : x( 0 ), y( 0 ), z( 0 ), w( 1 ) {};
	Vec( float x, float y ) : x( x ), y( y ), z( 0 ), w( 1 ) {};
	Vec( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {};
	float & operator [] (int i) {
		return (&x)[i];
	}
	Vec operator + ( Vec &a ) {
		return { x + a.x, y + a.y };
	}
	Vec operator + ( float a ) {
		return { x + a, y + a };
	}
	Vec operator * ( float a ) {
		return { x * a, y * a };
	}
	float operator * ( Vec &a ) {
		return x*a.x + y*a.y + z*a.z + w*a.w;
	}
	operator float * () {
		return &x;
	}
	void random() { // rage 0 - 1
		x = real_distribution( random_engine );
		y = real_distribution( random_engine );
	}
	float Length() {
		return sqrt( x * x + y * y );
	}
};