#ifndef MATLABengine
#define MATLABengine

/*
 *	engdemo.cpp
 *
 *	A simple program to illustrate how to call MATLAB
 *	Engine functions from a C++ program.
 *
 * Copyright 1984-2011 The MathWorks, Inc.
 * All rights reserved
 */
#include "engine.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void ObjectTrack(void)
{
	Engine *ep;
	ep = engOpen("Null");
	
	double position_c=9;	
	mxArray *position = mxCreateDoubleMatrix(1,1,mxREAL);
	engEvalString(ep,"position = sqrt(9);");
	position = engGetVariable(ep,"position");
	memcpy(&position_c,(void *)(mxGetPr(position)),sizeof(double));
	engClose(ep);
	return(position_c);
}

#endif