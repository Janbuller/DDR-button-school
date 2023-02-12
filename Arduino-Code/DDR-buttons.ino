struct Button {
  int Pin = 0;
  char Name = 'u';
  long long Timeout = 0;
  bool Released = true;

  long long ResendTimeout = 120;

  Button(int Pin, char Name)
    : Pin{Pin},
      Name{Name} {

  }
};

Button btns[4] = {
  Button{4,  'd'},
  Button{16, 'u'},
  Button{5,  'r'},
  Button{18, 'l'},
};
const int buttonCount = 4;

const unsigned long DebounceTime = 15;
const unsigned long ResendTime = 500;

unsigned long curTime;
unsigned long oldTime;

void setup() {
  for (auto btn : btns)
    pinMode(btn.Pin, INPUT_PULLDOWN);

  curTime = millis();
  oldTime = millis();

  Serial.begin(9600);
}


void loop() {
  curTime = millis();
  unsigned long deltaTime = curTime - oldTime;
  oldTime = millis();

  for (int i = 0; i < buttonCount; i++) {
    auto& btn = btns[i];

    auto buttonPin = btn.Pin;

    int buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
      if (btn.Timeout <= 0) {
        btn.Released = false;
        Serial.print(btn.Name);
      }
      btn.Timeout = DebounceTime;
    } else {
      if (!btn.Released && btn.Timeout <= 0) {
        btn.Released = true;
        Serial.print("-" + String(btn.Name));
      }
    }

    btn.Timeout -= deltaTime;
    if (btn.Timeout < 0)
      btn.Timeout = 0;


    btn.ResendTimeout -= deltaTime;
    if (btn.ResendTimeout < 0) {
      btn.ResendTimeout = ResendTime;
      if (buttonState == LOW)
        Serial.print("-");
      Serial.print(btn.Name);
    }
  }
}

void loop() {
  for (int i = 0; i < buttonCount; i++) {
    auto& btn = btns[i];

    int buttonState = digitalRead(btn.Pin);

    if (buttonState == HIGH) {
      if (btn.Timeout <= 0) {
        btn.Released = false;
        Serial.print(btn.Name);
      }
      btn.Timeout = DebounceTime;
    } else {
      if (!btn.Released && btn.Timeout <= 0) {
        btn.Released = true;
        Serial.print("-" + String(btn.Name));
      }
    }

    btn.Timeout -= deltaTime;
    if (btn.Timeout < 0)
      btn.Timeout = 0;
  }
}
