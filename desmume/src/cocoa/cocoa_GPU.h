/*
	Copyright (C) 2013 DeSmuME team

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#import <Foundation/Foundation.h>
#include <pthread.h>
#include <libkern/OSAtomic.h>


@interface CocoaDSGPU : NSObject
{
	UInt32 gpuStateFlags;
	OSSpinLock spinlockGpuState;
	
	BOOL gpuStateMainGPU;
	BOOL gpuStateMainBG0;
	BOOL gpuStateMainBG1;
	BOOL gpuStateMainBG2;
	BOOL gpuStateMainBG3;
	BOOL gpuStateMainOBJ;
	BOOL gpuStateSubGPU;
	BOOL gpuStateSubBG0;
	BOOL gpuStateSubBG1;
	BOOL gpuStateSubBG2;
	BOOL gpuStateSubBG3;
	BOOL gpuStateSubOBJ;
	
	BOOL isCPUCoreCountAuto;
	
	pthread_mutex_t *mutexProducer;
}

@property (assign) UInt32 gpuStateFlags;
@property (assign) pthread_mutex_t *mutexProducer;

@property (assign) NSInteger render3DRenderingEngine;
@property (assign) BOOL render3DHighPrecisionColorInterpolation;
@property (assign) BOOL render3DEdgeMarking;
@property (assign) BOOL render3DFog;
@property (assign) BOOL render3DTextures;
@property (assign) NSUInteger render3DDepthComparisonThreshold;
@property (assign) NSUInteger render3DThreads;
@property (assign) BOOL render3DLineHack;
@property (assign) BOOL render3DMultisample;

- (BOOL) gpuStateByBit:(const UInt32)stateBit;
- (BOOL) isGPUTypeDisplayed:(const NSInteger)theGpuType;
- (void) hideGPUType:(const NSInteger)theGpuType;
- (void) showGPUType:(const NSInteger)theGpuType;

@end

#ifdef __cplusplus
extern "C"
{
#endif

void SetGPULayerState(const int gpuType, const unsigned int i, const bool state);
bool GetGPULayerState(const int gpuType, const unsigned int i);
void SetGPUDisplayState(const int gpuType, const bool state);
bool GetGPUDisplayState(const int gpuType);

bool OSXOpenGLRendererInit();
bool OSXOpenGLRendererBegin();
void OSXOpenGLRendererEnd();

bool CreateOpenGLRenderer();
void DestroyOpenGLRenderer();
void RequestOpenGLRenderer_3_2(bool request_3_2);
void SetOpenGLRendererFunctions(bool (*initFunction)(),
								bool (*beginOGLFunction)(),
								void (*endOGLFunction)());

#ifdef __cplusplus
}
#endif
