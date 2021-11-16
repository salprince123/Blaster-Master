#pragma once
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_QUAD	7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_FROG	77
#define OBJECT_TYPE_FROG_GUN	771
#define OBJECT_TYPE_FROG_BODY	772
#define OBJECT_TYPE_FROG_WHEEL	773
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_BACKROUND	2
#define OBJECT_TYPE_LADYBIRD	30
#define OBJECT_TYPE_BOOM	31

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

// QUAD TREE
#define MIN_WIDTH_OF_QUADTREE 128 /*= 256/2 */
#define MAX_WIDTH_OF_QUADTREE 960 
#define MAX_QUAD_LINE 1024
#define QUAD_SECTION_UNKNOWN -1
#define QUAD_SECTION_OBJECTS	1
#define QUAD_MIN_LEVEL	1