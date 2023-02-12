#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <array>
#include <string>

class ControllerReader {
public:
  enum Keys {
    K_LEFT,
    K_RIGHT,
    K_UP,
    K_DOWN,

    K_NONE,
  };

private:
  std::string m_SerialPortPath = "";
  int m_SPFD;

  char m_ReadBuffer[256];

  bool m_NextRelease = false;


public:
  std::array<bool, K_NONE> m_KeyPressed;

  ControllerReader(std::string SerialPortPath);
  ~ControllerReader();


private:
  void PressKey(Keys key);
public:
  void Update();
};
