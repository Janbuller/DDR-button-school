#include "ControllerReader.h"

#include <raylib.h>

int main(int argc, char** argv) {
  ControllerReader Controller{"/dev/ttyUSB0"};

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Tegridy Dance");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
      Controller.Update();

      BeginDrawing();
      ClearBackground(RAYWHITE);


      DrawRectangle(screenWidth/4 - 25, screenHeight/2-25, 50, 50,      Color{130, 0,   0,   255});
      DrawRectangle(3 * screenWidth/4 - 25, screenHeight/2-25, 50, 50,  Color{130, 0,   130, 255});
      DrawRectangle(screenWidth/2-25, screenHeight/4 - 25, 50, 50,      Color{130, 130, 0,   255});
      DrawRectangle(screenWidth/2-25, 3 * screenHeight/4 + 25, 50, 50,  Color{0,   130, 0,   255});


      if(Controller.m_KeyPressed[ControllerReader::K_LEFT]) {
          DrawRectangle(screenWidth/4 - 25, screenHeight/2-25, 50, 50, RED);
      }
      if(Controller.m_KeyPressed[ControllerReader::K_RIGHT]) {
          DrawRectangle(3 * screenWidth/4 - 25, screenHeight/2-25, 50, 50, MAGENTA);
      }
      if(Controller.m_KeyPressed[ControllerReader::K_UP]) {
          DrawRectangle(screenWidth/2-25, screenHeight/4 - 25, 50, 50, YELLOW);
      }
      if(Controller.m_KeyPressed[ControllerReader::K_DOWN]) {
          DrawRectangle(screenWidth/2-25, 3 * screenHeight/4 + 25, 50, 50, GREEN);
      }

      EndDrawing();
  }
  return 1;
}
