int red1 = A0;         
int yellow1 = A1;        
int yellow2 = A4;        
int green2 = A5;         
int road1_button = A2;   
int road2_button = A3;  
int road1_busy = 0;      
int road2_busy = 0;      
int yellowTime = 0;      
int TransfireTime = 3;  
int flag = 0;           

void setup() {
  
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }

  
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(road1_button, INPUT_PULLUP);  
  pinMode(road2_button, INPUT_PULLUP);  

     
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}


const int number[10] = { 0b1000000, 0b1111001, 0b100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000 };

void loop() {
   
  checkButtons();

  
  if (road1_busy == 0 && road2_busy == 1) {
    Red();
    checkButtons();
  } else if (road1_busy == 1 && road2_busy == 0) {
    Green();
    checkButtons();
    if ((road1_busy == 0 && road2_busy == 1) || (road1_busy == 1 && road2_busy == 0)) {
    } else {
      Red();
      checkButtons();
    }
  } else {
    Green();
    checkButtons();
    if ((road1_busy == 0 && road2_busy == 1) || (road1_busy == 1 && road2_busy == 0)) {
    } else {
      Red();
      checkButtons();
    }
  }
}


void checkButtons() {
  if (digitalRead(road1_button) == LOW) {
    road1_busy = 1;
    delay(100);
  } else {
    road1_busy = 0;
  }

  if (digitalRead(road2_button) == LOW) {
    road2_busy = 1;     
    delay(100);
  } else {
    road2_busy = 0;
  }
}

    
void display(const int from) {
  flag = from;
  for (int tens = from; tens >= 0; tens--) {
    display_tens(tens);
  }
}


void display_tens(const int tens) {
  int pin1, a, ones;
  for (pin1 = 7, a = 0; pin1 < 14; pin1++, a++) {
    digitalWrite(pin1, bitRead(number[tens], a));
  }
  for (ones = 9; ones >= 0; ones--) {
    if (tens == flag) {
      ones = 0;
    }
    if (tens == 0 && ones == 5) {
      delay(0);
      break;
    }

    display_ones(ones);
    delay(1000);     
  }
}


void display_ones(const int x) {
  int pin2, b;
  for (pin2 = 0, b = 0; pin2 <= 6; pin2++, b++) {
    digitalWrite(pin2, bitRead(number[x], b));
  }
}

void display2(const int from) {
  for (int tens = from; tens >= 0; tens--) {
    display_tens2(tens);
  }
}

void display_tens2(const int tens) {
  int pin1, a, ones;
  for (pin1 = 7, a = 0; pin1 < 14; pin1++, a++) {
    digitalWrite(pin1, bitRead(number[tens], a));
  }
  for (ones = 5; ones >= 0; ones--) {
    display_ones2(ones);
    delay(1000);   
  }
}

 
void display_ones2(const int x) {
  int pin2, b;
  for (pin2 = 0, b = 0; pin2 <= 6; pin2++, b++) {
    digitalWrite(pin2, bitRead(number[x], b));
  }
}

   
void Red() {
  digitalWrite(red1, HIGH);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, HIGH);
  display(TransfireTime);

  digitalWrite(red1, HIGH);
  digitalWrite(yellow2, HIGH);
  display2(yellowTime);

  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
}

void Green() {
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
  display(TransfireTime);

  digitalWrite(yellow1, HIGH);
  digitalWrite(green2, LOW);
  display2(yellowTime);

  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
}
