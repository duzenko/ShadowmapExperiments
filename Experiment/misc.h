#pragma once

const int MAX_KEY = 512; // ?
bool keyStates[MAX_KEY];

void glCheck() {
	auto error = glGetError();
	if ( error != GL_NO_ERROR )
		Beep( 99, 99 );
}