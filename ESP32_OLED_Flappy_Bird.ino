#include "GameSettings.h"

// OLED 72x40 I2C Display
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(ROTATION, U8X8_PIN_NONE, SCL, SDA);


unsigned long lastUpdate = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);

  WriteText(SCREEN_WIDTH / 2 - strlen(GameStatus.welcome_message) * 3, SCREEN_HEIGHT / 2 + 5, GameStatus.welcome_message);

  while (!IsButtonPressed()) {
    ;  //attendi che venga premuto il tasto
  }

  InitGame();
}

void loop() {
  unsigned long now = millis();

  //contolla se bisogna saltare
  if (IsButtonPressed()) {
    if (!Bird.jumping) {
      Bird.Y_Velocity = JUMPING_VELOCITY;
      Bird.jumping = true;
    }
  } else {
    Bird.jumping = false;
  }

  //controlla se bisogna aggiornare
  if (now - lastUpdate >= Ts) {
    lastUpdate = now;
    updateGame();
    drawGame();
  }
}

void updateGame() {

  if (!GameStatus.game_over) {
    Bird.Y_Velocity += GRAVITY_FORCE;  //aumenta velocità per via della gravità
    Bird.Y += Bird.Y_Velocity;         //integra velocità per ricavare posizione

    // Movimento Pipe
    //Pipe.Pipe_Velocity = INITIAL_PIPE_VELOCITY + ((float)GameStatus.score) * 0.00002f;
    Pipe.X -= Pipe.Pipe_Velocity;

    // Collisione ?
    if (Pipe.X < Bird.X && Bird.X < (Pipe.X + PIPE_WIDTH)) {
      if (!((Pipe.UpperY + BIRD_RADIUS) < Bird.Y && Bird.Y < (Pipe.UpperY + PIPE_GAP - BIRD_RADIUS))) {
        GameStatus.game_over = true;
        return;
      }
    }
    // Fuori Dai bordi?
    if (Bird.Y < -BIRD_RADIUS || Bird.Y > (SCREEN_HEIGHT + BIRD_RADIUS + 1)) {
      GameStatus.game_over = true;
      return;
    }

    //devi generare un nuovo pipe?
    if (Pipe.X <= -PIPE_WIDTH) {
      GeneraNuovoPipe();
      GameStatus.score++;
    }
  } else {
    if (ButtonRisingEdge()) {
      InitGame();
    }
  }
}

void drawGame() {
  if (!GameStatus.game_over) {
    u8g2.clearBuffer();
    DrawPipe();
    u8g2.drawDisc(Bird.X, Bird.Y, BIRD_RADIUS);
    WriteValue(SCREEN_WIDTH - 12, 10, GameStatus.score);
  } else {
    WriteText(SCREEN_WIDTH / 2 - strlen(GameStatus.game_over_message) * 3, SCREEN_HEIGHT / 2 + 5, GameStatus.game_over_message);
  }

  u8g2.sendBuffer();
}

void GeneraNuovoPipe() {
  Pipe.X = SCREEN_WIDTH;
  Pipe.UpperY = random(TOP_BOTTOM_PADDING, SCREEN_HEIGHT - PIPE_GAP - TOP_BOTTOM_PADDING);
}

void InitGame() {
  GameStatus.welcome = false;
  GameStatus.score = 0;
  GameStatus.game_over = false;

  Bird.X = BIRD_INITIAL_X;
  Bird.Y = BIRD_INITIAL_Y;
  Bird.Y_Velocity = 0;
  Bird.jumping = false;

  Pipe.Pipe_Velocity = INITIAL_PIPE_VELOCITY;
  GeneraNuovoPipe();
}

bool IsButtonPressed() {
  return !digitalRead(BUTTON_PIN);
}

bool ButtonRisingEdge() {
  static bool last_press = false;

  bool pressed_cpy;
  bool result = false;

  if (pressed_cpy = IsButtonPressed()) {
    if (!last_press) {
      result = true;
    }
  }
  last_press = pressed_cpy;
  return result;
}

void WriteText(uint8_t CursorX, uint8_t CursorY, char* message) {
  u8g2.setCursor(CursorX, CursorY);
  u8g2.print(message);
  u8g2.sendBuffer();
}

void WriteValue(uint8_t CursorX, uint8_t CursorY, uint8_t value) {
  u8g2.setCursor(CursorX, CursorY);
  u8g2.print(value);
  u8g2.sendBuffer();
}

void DrawPipe() {
  u8g2.drawBox(Pipe.X, 0, PIPE_WIDTH, Pipe.UpperY);
  u8g2.drawBox(Pipe.X, Pipe.UpperY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - PIPE_GAP - Pipe.UpperY);
}

