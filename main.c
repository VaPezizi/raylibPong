#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


const int width = 800;
const int height  = 600;
const Vector2 ballStart = {(float) width / 2, (float) height / 2};

const Vector2 player1Start = {(float) width * 0.1, (float) height * 0.5};
const Vector2 player2Start = {(float) width * 0.9, (float) height * 0.5};

//const Vector2 ballStartVelocity = {6, 0};

typedef struct{
	Vector2 position;
	float size;
	Vector2 velocity;
} Ball;

typedef struct{
	Vector2 position;
	Vector2 size;
} Square;

//Returns a positive or a negative float between a certain range
float float_rand(float min, float max)
{
	float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
	if(rand() % 2 == 1){
		return min + scale * (max - min);
	}
	return -(min + scale * ( max - min ));      /* [min, max] */
}
	 //ball.position.y >= window_height - ball.size;

void resetGame(Ball* ball, Rectangle* player1, Rectangle* player2){
	ball -> position = ballStart;
	
	Vector2 randVel = {float_rand(2, 5), float_rand(2, 5)};

	ball -> velocity = randVel;

	player1 -> x = player1Start.x;
	player1 -> y = player1Start.y;

	player2 -> x = player2Start.x;
	player2 -> y = player2Start.y;

}

int main(){


	Ball ball ={
		//.position = {(float) width/2, (float) height/2},
		.position = {ballStart.x, ballStart.y},	
		.size = 20,
		.velocity = {float_rand(2, 5), float_rand(2, 5)}};
	//float ball_velocity_y = 4;
	Rectangle player1 ={
		.x = (float) width * 0.1,
	       	.y = (float) height * 0.5 ,
		.width = 25,
		.height = 150
	};
	Rectangle player2 ={
		.x = (float) width * 0.9,
	       	.y = (float) height * 0.5 ,
		.width = 25,
		.height = 150
	};

	//Width	Height
	//Vector2 ball_position = {(float) width/2, (float) height/2};
	//int ball_x = 400;
	//int ball_y = 300;
	
	InitWindow( width, height, "Trollface PONG");	
	SetTargetFPS( 60 );


	Texture2D trollFace = LoadTexture("resources/trollface-symbol.png");	
	
	int player1Speed = 0;
	int player2Speed = 0;

	//Scores
	int player1Score = 0;
	int player2Score = 0;

	Ball *ballPtr = &ball;
	Rectangle *player1Ptr = &player1;
	Rectangle *player2Ptr = &player2;

	//Main game loop
	while(!WindowShouldClose()) {
		BeginDrawing();
		
		//float ball_bottom = ball.position.y + ball_size;
		
		//Stops the ball when on ground	
		if(ball.position.y >= height - ball.size){
			ball.velocity.y =-ball.velocity.y;
			//ball.velocity_y = 0;
			//ball.position.y = height - ball_size;
		}
		//Stops ball on top of screen
		if(ball.position.y <= 0 + ball.size){
			ball.velocity.y = fabs(ball.velocity.y);
		}
		
		//Score handling
		if(ball.position.x > width){ 
			player1Score += 1;
			resetGame(ballPtr, player1Ptr, player2Ptr);
		}
		if(ball.position.x < 0){
		       	player2Score += 1;
			resetGame(ballPtr, player1Ptr, player2Ptr);
		}
		//Check collision of left side player
		if(CheckCollisionCircleRec(ball.position, ball.size + 5, player1)){
		       	ball.velocity.x = fabs(ball.velocity.x * 1.05);
			ball.velocity.y = ball.velocity.y + player1Speed;
		}
		//Check collision of right side player
		if(CheckCollisionCircleRec(ball.position, ball.size + 5, player2)){
		       	ball.velocity.x = -ball.velocity.x * 1.05;	
			ball.velocity.y = ball.velocity.y + player2Speed; 
		}
		
		//Keybindings
		if(IsKeyPressed(KEY_ENTER)){
			resetGame(ballPtr, player1Ptr, player2Ptr);
		}

		if(IsKeyDown(KEY_W) && player1.y > 0){
			player1.y += -6;
			player1Speed = -1;

		}
		else if(IsKeyDown(KEY_S) && player1.y < height - player1.height){
			player1.y += 6;
			player1Speed = 1;
	
		}
		if(IsKeyDown(KEY_UP) && player2.y > 0){
			player2Speed = -1;
			player2.y += -6;

		}
		else if(IsKeyDown(KEY_DOWN) && player2.y < height - player1.height){
			player2.y += 6;
			player2Speed = 1;
		
		}else{ player1Speed = 0; player2Speed = 0;}
		//Jump if space is pressed and ball is on the ground
			//ball.position.y += 2;
		
		ball.position.y += ball.velocity.y;
		ball.position.x += ball.velocity.x;
		

		ClearBackground(WHITE);
		//Piirto koordinaatit X, Y
		
		/*DrawRectangle(
			platform1.position.x,
			platform1.position.y,
			platform1.size.x,
			platform1.size.y,
			BLACK
		);*/
		//int count = 4;	
		DrawRectangleRec(player1, BLACK);
		DrawRectangleRec(player2, BLACK);
		DrawCircle(ball.position.x, ball.position.y, ball.size, BLACK);

		Vector2 trollPosition = {ball.position.x - ball.size, ball.position.y -ball.size};	
		DrawTextureEx(trollFace, trollPosition, 0, .12, WHITE);

		char str1[20];
		char str2[20];
		sprintf(str1, "%d", player1Score);
		sprintf(str2, "%d", player2Score);
		//Text drawings
		DrawFPS(30, 30);		
		DrawText(str1, (width * .2), 50, 100, BLACK);	
		DrawText(str2, (width * .8), 50, 100, BLACK);	

		EndDrawing();
	}
	
	return 0;
}

