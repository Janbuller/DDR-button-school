#include "ControllerReader.h"

ControllerReader::ControllerReader(std::string SerialPortPath)
    : m_SerialPortPath{SerialPortPath} {

  for(auto& Key : m_KeyPressed) {
    Key = false;
  }
  m_SPFD = open("/dev/ttyUSB0", O_RDONLY);

  if (m_SPFD < 0) {
    fprintf(stderr, "Failed to open serial port, error %i: %s\n", errno,
            strerror(errno));
  }

  struct termios flags;
  if (tcgetattr(m_SPFD, &flags) != 0) {
    fprintf(stderr, "Failed to get termios attributes, error %i: %s\n", errno,
            strerror(errno));
  }

  flags.c_cflag &= ~PARENB;
  flags.c_cflag &= ~CSTOPB;
  flags.c_cflag &= ~CSIZE;
  flags.c_cflag |= CS8;
  flags.c_cflag &= ~CRTSCTS;
  flags.c_cflag |= CREAD | CLOCAL;

  flags.c_lflag &= ~ICANON;
  flags.c_lflag &= ~ECHO;
  flags.c_lflag &= ~ECHOE;
  flags.c_lflag &= ~ECHONL;
  flags.c_lflag &= ~ISIG;

  flags.c_iflag &= ~(IXON | IXOFF | IXANY);
  flags.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

  flags.c_oflag &= ~OPOST;
  flags.c_oflag &= ~ONLCR;

  flags.c_cc[VTIME] = 1;
  flags.c_cc[VMIN] = 0;

  cfsetspeed(&flags, B9600);

  if (tcsetattr(m_SPFD, TCSANOW, &flags) != 0) {
    fprintf(stderr, "Failed to set termios attributes, error %i: %s\n", errno,
            strerror(errno));
  }
}

ControllerReader::~ControllerReader() { close(m_SPFD); }

void ControllerReader::PressKey(Keys key) {
  if(m_NextRelease)
      m_KeyPressed[key] = false;
  else
      m_KeyPressed[key] = true;
  m_NextRelease = false;
}

void ControllerReader::Update() {

  memset(&m_ReadBuffer, 0, sizeof(m_ReadBuffer));

  int n = read(m_SPFD, &m_ReadBuffer, sizeof(m_ReadBuffer));

  for (int i = 0; i < 256; i++) {
    switch (m_ReadBuffer[i]) {
    case '-': {
      m_NextRelease = true;
      break;
    }
    case 'l': {
      PressKey(K_LEFT);
      break;
    }
    case 'r': {
      PressKey(K_RIGHT);
      break;
    }
    case 'u': {
      PressKey(K_UP);
      break;
    }
    case 'd': {
      PressKey(K_DOWN);
      break;
    }
    }
  }
}
