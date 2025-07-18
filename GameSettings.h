#pragma once
#include <U8g2lib.h>

//HARDWARE I2C
#define SCL 6
#define SDA 5

#define ROTATION U8G2_R0 //CAMBIA CON  U8G2_R2  PER RUOTARE LO SCHERMO DI 180 GRADI

//HARDWARE BUTTON
#define BUTTON_PIN 9

//SCREEN DIMENSIONS
#define SCREEN_WIDTH 72
#define SCREEN_HEIGHT 40

//GAME SETTINGS
#define PIPE_WIDTH 6
#define PIPE_GAP 18
#define TOP_BOTTOM_PADDING 2        //minima lunghezza pipe dal bordo schermo
#define INITIAL_PIPE_VELOCITY 1.0f  //px per frame
#define Ts 17                       //ms per frame

#define BIRD_RADIUS 2
#define BIRD_INITIAL_X 2
#define BIRD_INITIAL_Y 20


#define JUMPING_VELOCITY -1.6f
#define GRAVITY_FORCE 0.15f

// Stato del giocatore
struct {
  uint8_t X;
  int8_t Y;
  float Y_Velocity;
  bool jumping = false;
} Bird;

// Stato del Pipe
struct {
  int8_t X;
  uint8_t UpperY;
  float Pipe_Velocity;
} Pipe;

// Stato del Gioco
struct {
  uint8_t score = 0;
  bool welcome = true;
  char* welcome_message = "HELLO USER!";
  bool game_over = false;
  char* game_over_message = "Game Over!";
} GameStatus;