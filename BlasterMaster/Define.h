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
#define OBJECT_TYPE_BULLET		774
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_BACKROUND	2
#define OBJECT_TYPE_LADYBIRD	30
#define OBJECT_TYPE_BOOM	31
#define OBJECT_TYPE_EYELET	32
#define OBJECT_TYPE_BALLCARRY	33
#define OBJECT_TYPE_BALLBOT	34
#define OBJECT_TYPE_GX680	35

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

// QUAD TREE
#define MIN_WIDTH_OF_QUADTREE 256 
#define MAX_WIDTH_OF_QUADTREE 960 
#define MAX_QUAD_LINE 1024
#define QUAD_SECTION_UNKNOWN -1
#define QUAD_SECTION_OBJECTS	1
#define QUAD_SECTION_SIZE	2
#define QUAD_MIN_LEVEL	1

//BOOM

#define BOOM_BBOX_WIDTH 16
#define BOOM_BBOX_HEIGHT 15
#define BOOM_BBOX_HEIGHT_DIE 0

#define BOOM_STATE_ALIVE 100
#define BOOM_STATE_DIE 200

#define BOOM_ANI_ALIVE 0
#define BOOM_ANI_DIE 1

//EYELET

#define EYELET_WALKING_SPEED 0.05;
#define EYELET_FLYING_UP_SPEED 0.05;

#define EYELET_BBOX_WIDTH 16
#define EYELET_BBOX_HEIGHT 16
#define EYELET_BBOX_HEIGHT_DIE 9

#define EYELET_STATE_WALKING_LEFT 100
#define EYELET_STATE_WALKING_RIGHT 101
#define EYELET_STATE_UNACTIVE 102
#define EYELET_STATE_COIN 103
#define EYELET_STATE_DIE 200


#define EYELET_ANI_WALKING_LEFT 0
#define EYELET_ANI_WALKING_RIGHT 1
#define EYELET_ANI_DIE 2
#define EYELET_ANI_COIN 3

//LADYBIRD

#define LADYBIRD_WALKING_SPEED 0.05f;
#define LADYBIRD_FLYING_UP_SPEED 0.05*0.4*2;
#define LADYBIRD_FLYING_DOWN_SPEED -0.05*0.4*2;

#define LADYBIRD_BBOX_WIDTH 16
#define LADYBIRD_BBOX_HEIGHT 16
#define LADYBIRD_BBOX_HEIGHT_DIE 9

#define LADYBIRD_STATE_WALKING_LEFT 100
#define LADYBIRD_STATE_WALKING_RIGHT 101
#define LADYBIRD_STATE_WALKING_UP 110
#define LADYBIRD_STATE_WALKING_DOWN 111
#define LADYBIRD_STATE_COIN 112
#define LADYBIRD_STATE_DIE 200

#define LADYBIRD_ANI_WALKING_LEFT 0
#define LADYBIRD_ANI_WALKING_RIGHT 1
#define LADYBIRD_ANI_DIE 2
#define LADYBIRD_ANI_COIN 3

//BALLCARRY

#define BALLCARRY_WALKING_SPEED 0.05;
#define BALLCARRY_FLYING_UP_SPEED 0.05*0.4*2;

#define BALLCARRY_BBOX_WIDTH 16
#define BALLCARRY_BBOX_HEIGHT 16
#define BALLCARRY_BBOX_HEIGHT_DIE 9

#define BALLCARRY_STATE_WALKING_LEFT 100
#define BALLCARRY_STATE_WALKING_RIGHT -100
#define BALLCARRY_STATE_UNACTIVE 102
#define BALLCARRY_STATE_COIN 103
#define BALLCARRY_STATE_FIRE 104
#define BALLCARRY_STATE_DIE 200

#define BALLCARRY_ANI_SLEEP 0
#define BALLCARRY_ANI_WALKING_LEFT 1
#define BALLCARRY_ANI_WALKING_RIGHT 2
#define BALLCARRY_ANI_FIRE 3
#define BALLCARRY_ANI_DIE 4
#define BALLCARRY_ANI_COIN 5

#define BALLCARRY_RANGE 50

//BALLBOT

#define BALLBOT_WALKING_SPEED	0.05;
#define BALLBOT_FLYING_UP_SPEED 0.05*0.4*2;

#define BALLBOT_BBOX_WIDTH		16
#define BALLBOT_BBOX_HEIGHT		16
#define BALLBOT_BBOX_HEIGHT_DIE	9

#define BALLBOT_STATE_UNACTIVE	102
#define BALLBOT_STATE_ACTIVE	103
#define BALLBOT_STATE_FLY		104
#define BALLBOT_STATE_DIE		200

#define BALLBOT_ANI_LEFT		0
#define BALLBOT_ANI_RIGHT		1
#define BALLBOT_ANI_DIE			2
#define BALLBOT_ANI_COIN		3

#define BALLBOT_RANGE			50

//GX680
#define GX680_WALKING_SPEED		0.05;
#define GX680_FLYING_UP_SPEED	0.05*0.4*2;

#define GX680_BBOX_WIDTH		16
#define GX680_BBOX_HEIGHT		16
#define GX680_BBOX_HEIGHT_DIE	9

#define GX680_STATE_UNACTIVE	102
#define GX680_STATE_ACTIVE		103
#define GX680_STATE_DIE			200

#define GX680_ANI_IDLE			0
#define GX680_ANI_WALK_lEFT		1
#define GX680_ANI_WALK_RIGHT	2
#define GX680_ANI_DIE			3

#define GX680_RANGE				100

//background
#pragma region backround
#define BACKGROUND_BBOX_WIDTH	16
#define BACKGROUND_BBOX_HEIGHT	16

#pragma endregion

//Brick 
#define BRICK_BBOX_WIDTH		48
#define BRICK_BBOX_HEIGHT		16
#define BRICK_BBOX_TYPE1_WIDTH  16
#define BRICK_BBOX_TYPE1_HEIGHT 48

//BULLET

#define BULLET_BBOX_WIDTH_VERTICAL  8
#define BULLET_BBOX_HEIGHT_VERTICAL 8
#define BULLET_BBOX_WIDTH_HORIZONTAL  8
#define BULLET_BBOX_HEIGHT_HORIZONTAL 8

#define BULLET_STATE_NOT_FIRE	100
#define BULLET_STATE_FIRE_LEFT	-200
#define BULLET_STATE_FIRE_RIGHT	200
#define BULLET_STATE_FIRE_UP	400
#define BULLET_STATE_DIE		500

#define BULLET_ANI_SMALL_LEFT		0
#define BULLET_ANI_SMALL_UP			1
#define BULLET_ANI_BIG_LEFT			2
#define BULLET_ANI_BIG_UP			3
#define BULLET_ANI_SMALL_RIGHT		4
#define BULLET_ANI_BIG_RIGHT		5
#define BULLET_ANI_NOT_FIRE			6
#define BULLET_ANI_DIE				7

#define BULLET_VX 0.15
#define BULLET_VY 0.15

#define BULLET_RANGE				120

//BIG FROG 

#define FROG_WALKING_SPEED		0.15f 
#define FROG_JUMP_SPEED_Y		0.5f
#define FROG_JUMP_DEFLECT_SPEED 0.2f
#define FROG_GRAVITY			-0.002f

#define FROG_STATE_IDLE			100
#define FROG_STATE_WALKING_RIGHT	200
#define FROG_STATE_WALKING_LEFT	300
#define FROG_STATE_JUMP			400
#define FROG_STATE_JUMPING_UP	500
#define FROG_STATE_FALLING_DOWN	600
#define FROG_STATE_FIRE			700
#define FROG_STATE_FIRE_UP		701
#define FROG_STATE_UP_LEFT		800
#define FROG_STATE_UP_RIGHT		900

#define PRINCE_STATE_WALKING_DOWN	1000
#define PRINCE_STATE_WALKING_UP	1100
#define PRINCE_STATE_FIRE_LEFT	1200
#define PRINCE_STATE_FIRE_UP	1300
#define PRINCE_STATE_FIRE_RIGHT	1400
#define PRINCE_STATE_FIRE_DOWN	1500
#define FROG_STATE_DIE				9000

#define	FROG_LEVEL	1
#define	PRINCE_LEVEL	2
#define	LITTLE_PRINCE_LEVEL	3

#define FROG_BBOX_WIDTH  26
#define FROG_BBOX_HEIGHT 16
#define PRINCE_BBOX_WIDTH  20
#define PRINCE_BBOX_HEIGHT 30

#define PRINCE_ANI_IDLE_RIGHT		1
#define PRINCE_ANI_IDLE_LEFT		2
#define PRINCE_ANI_WALKING_RIGHT	3
#define PRINCE_ANI_WALKING_LEFT		4
#define PRINCE_ANI_IDLE_DOWN		5
#define PRINCE_ANI_IDLE_UP			6
#define PRINCE_ANI_WALKING_DOWN		7
#define PRINCE_ANI_WALKING_UP		8

#define LITTLE_PRINCE_ANI_IDLE_LEFT		9
#define LITTLE_PRINCE_ANI_IDLE_RIGHT		10
#define LITTLE_PRINCE_ANI_WALKING_LEFT		11
#define LITTLE_PRINCE_ANI_WALKING_RIGHT 12
#define FROG_UNTOUCHABLE_TIME 5000

#define MAX_BULLET 7
//FROG BODY 


#define FROG_BODY_UP_BBOX_WIDTH  16
#define FROG_BODY_UP_BBOX_HEIGHT 8
#define FROG_BODY_DOWN_BBOX_WIDTH  7
#define FROG_BODY_DOWN_BBOX_HEIGHT 7

#define FROG_BODY_TYPE_UP	1
#define FROG_BODY_TYPE_DOWN	2

#define FROG_BODY_UP_STATE_LEFT_UP 100
#define FROG_BODY_UP_STATE_RIGHT_UP 200
#define FROG_BODY_UP_STATE_LEFT 300
#define FROG_BODY_UP_STATE_RIGHT 400
#define FROG_BODY_UP_STATE_UP_LEFT  4001
#define FROG_BODY_UP_STATE_UP_RIGHT 4002

#define FROG_BODY_DOWN_STATE_LEFT_RIGHT 500
#define FROG_BODY_DOWN_STATE_TOP_BOT	600
#define FROG_BODY_DOWN_STATE_TOP_LEFT	700
#define FROG_BODY_DOWN_STATE_BOT_RIGHT	800
#define FROG_BODY_DOWN_STATE_UP_LEFT	900
#define FROG_BODY_DOWN_STATE_UP_RIGHT	1000

#define FROG_BODY_UP_ANI_LEFT_UP 0
#define FROG_BODY_UP_ANI_RIGHT_UP 1
#define FROG_BODY_UP_ANI_UP 1
#define FROG_BODY_UP_ANI_LEFT 2
#define FROG_BODY_UP_ANI_RIGHT 3

#define FROG_BODY_DOWN_ANI_LEFT_RIGHT 4
#define FROG_BODY_DOWN_ANI_TOP_BOT	5
#define FROG_BODY_DOWN_ANI_TOP_LEFT	6
#define FROG_BODY_DOWN_ANI_BOT_RIGHT	7
#define FROG_BODY_DOWN_ANI_HIDE	8

#define DISTANCE_FROM_FROG_TOP_RIGHT_X_UP	10
#define DISTANCE_FROM_FROG_BOT_LEFT_X_UP	10
#define DISTANCE_FROM_FROG_STATIC_LEFT_X_UP 10
#define DISTANCE_FROM_FROG_TOP_RIGHT_Y_UP	10
#define DISTANCE_FROM_FROG_BOT_LEFT_Y_UP	10
#define DISTANCE_FROM_FROG_STATIC_LEFT_Y_UP 10

//THIS IS THE WHEEL UNDER THE BODY
#define DISTANCE_FROM_FROG_LEFT_RIGHT_X_DOWN	10
#define DISTANCE_FROM_FROG_TOP_BOT_X_DOWN	10
#define DISTANCE_FROM_FROG_TOP_LEFT_X_DOWN	10
#define DISTANCE_FROM_FROG_BOT_RIGHT_X_DOWN	10
#define DISTANCE_FROM_FROG_LEFT_RIGHT_Y_DOWN	10
#define DISTANCE_FROM_FROG_TOP_BOT_Y_DOWN	10
#define DISTANCE_FROM_FROG_TOP_LEFT_Y_DOWN	10
#define DISTANCE_FROM_FROG_BOT_RIGHT_Y_DOWN	10

//FROG GUN

#define FROG_GUN_BBOX_WIDTH  7
#define FROG_GUN_BBOX_HEIGHT 7

#define FROG_GUN_STATE_LEFT 100
#define FROG_GUN_STATE_RIGHT 200
#define FROG_GUN_STATE_UP 300
#define FROG_GUN_STATE_LEFT_UP 400
#define FROG_GUN_STATE_RIGHT_UP 401

#define FROG_GUN_ANI_RIGHT_UP 0
#define FROG_GUN_ANI_LEFT 1
#define FROG_GUN_ANI_RIGHT 1
#define FROG_GUN_ANI_LEFT_UP 2
#define FROG_GUN_ANI_UP 3
#define FROG_GUN_ANI_HIDE 4

//FROG WHEEL

#define FROG_WHEEL_BBOX_WIDTH  7
#define FROG_WHEEL_BBOX_HEIGHT 7

#define FROG_WHEEL_TYPE_LEFT	10
#define FROG_WHEEL_TYPE_RIGHT	20

#define FROG_WHEEL_STATE_UP_RIGHT 100
#define FROG_WHEEL_STATE_LEFT  200
#define FROG_WHEEL_STATE_RIGHT  500
#define FROG_WHEEL_STATE_UP_LEFT  300
#define FROG_WHEEL_STATE_UP  400

#define FROG_WHEEL_ANI_UP_RIGHT 0
#define FROG_WHEEL_ANI_LEFT  1
#define FROG_WHEEL_ANI_UP_LEFT  2
#define FROG_WHEEL_ANI_UP  3
#define FROG_WHEEL_ANI_HIDE  4

//BALL CARRY

#define BALL_CARRY_WALKING_SPEED 0.05*0.5;

#define BALL_CARRY_BBOX_WIDTH 16
#define BALL_CARRY_BBOX_HEIGHT 16
#define BALL_CARRY_BBOX_HEIGHT_DIE 0

#define BALL_CARRY_STATE_WALKING_LEFT 100
#define BALL_CARRY_STATE_WALKING_RIGHT 101
#define BALL_CARRY_STATE_UNACTIVE 102
#define BALL_CARRY_STATE_FIRE 103
#define BALL_CARRY_STATE_DIE 200

#define BALL_CARRY_ANI_SLEEP		0
#define BALL_CARRY_ANI_RUN_LEFT		1
#define BALL_CARRY_ANI_RUN_RIGHT	2
#define BALL_CARRY_ANI_FIRE			3
#define BALL_CARRY_ANI_DIE			4