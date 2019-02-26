#pragma once

Vec playerPosition;

void calcLightMatrices() {
	float squeeze = pow( 1 + 30 * playerPosition.Length2(), 0.3f );	// magic const's
	mapSideNear[0] = BASE_NEAR * squeeze;
	mapSideNear[2] = BASE_NEAR / squeeze;

	float texelSize = 2 * BASE_NEAR / fboShadows.viewPort.w;
	float angleStep = atan2( texelSize, mapSideNear[0] );
	float movingAngle = atan2( playerPosition.y, playerPosition.x ) + (float)M_PI / 2;
	if ( !keyStates[GLFW_KEY_S] ) {
		int steps = (int)(movingAngle / angleStep);
		movingAngle = steps * angleStep;
	}

	for ( int side = 0; side < 4; side++ ) {
		mapViewMatrix[side].rotateToNorm( movingAngle + side * (float)M_PI / 2 );

		Mat viewInv;
		gluInvertMatrix( mapViewMatrix[side].elements, viewInv.elements );

		int leftSide = (side /* -1 */ + 3) % 4, rightSide = (side + 1) % 4;
		Vec leftCorner( -mapSideNear[leftSide], mapSideNear[side] ), rightCorner( mapSideNear[rightSide], mapSideNear[side] );
		mapCorners[side] = viewInv * leftCorner;
		mapCorners[rightSide] = viewInv * rightCorner;

		float zNear = mapSideNear[side];
		mapProjectionMatrix[side].projectionFor( leftCorner.x, rightCorner.x, zNear, -zNear, zNear );
	}
}

