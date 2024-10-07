int red1 = A0;          // تعريف دبوس الطريق الأول الذي يتحكم بلون الإشارة الحمراء
int yellow1 = A1;       // تعريف دبوس الطريق الأول الذي يتحكم بلون الإشارة الصفراء
int yellow2 = A4;       // تعريف دبوس الطريق الثاني الذي يتحكم بلون الإشارة الصفراء
int green2 = A5;        // تعريف دبوس الطريق الثاني الذي يتحكم بلون الإشارة الخضراء
int road1_button = A2;  // تعريف دبوس زر الطريق الأول
int road2_button = A3;  // تعريف دبوس زر الطريق الثاني
int road1_busy = 0;     // حالة الطريق الأول - غير مزدحم
int road2_busy = 0;     // حالة الطريق الثاني - غير مزدحم
int yellowTime = 0;     // وقت الإشارة الصفراء
int TransfireTime = 3;  // وقت الانتقال بين الإشارات
int flag = 0;           // علامة لتتبع الحالة الحالية للعرض

void setup() {
  // تهيئة جميع الدبابيس كمخرج
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }

  // تهيئة الدبابيس المستخدمة في تحكم الإشارات
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(road1_button, INPUT_PULLUP);  // تعيين الدبوس كمدخل مع مقاومة Pull-up
  pinMode(road2_button, INPUT_PULLUP);  // تعيين الدبوس كمدخل مع مقاومة Pull-up

  // إيقاف تشغيل جميع الإشارات
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}

// مصفوفة تحتوي على الأرقام المتناظرة مع الأشكال المعروضة على شاشة العرض السبعية
const int number[10] = { 0b1000000, 0b1111001, 0b100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000 };

void loop() {
  // فحص حالة الأزرار
  checkButtons();

  // التحكم في الإشارات المرورية استنادًا إلى ازدحام الطرق
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

// تحقق من حالة الأزرار
void checkButtons() {
  if (digitalRead(road1_button) == LOW) {
    road1_busy = 1;  // الطريق الأول مزدحم
    delay(100);
  } else {
    road1_busy = 0;
  }

  if (digitalRead(road2_button) == LOW) {
    road2_busy = 1;  // الطريق الثاني مزدحم
    delay(100);
  } else {
    road2_busy = 0;
  }
}

// إظهار الأرقام على الشاشة
void display(const int from) {
  flag = from;
  for (int tens = from; tens >= 0; tens--) {
    display_tens(tens);
  }
}

// عرض العشرات على الشاشة
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
    delay(1000);  // تأخير لثانية واحدة
  }
}

// عرض الواحدات على الشاشة
void display_ones(const int x) {
  int pin2, b;
  for (pin2 = 0, b = 0; pin2 <= 6; pin2++, b++) {
    digitalWrite(pin2, bitRead(number[x], b));
  }
}

// عرض الأرقام للعداد الثاني
void display2(const int from) {
  for (int tens = from; tens >= 0; tens--) {
    display_tens2(tens);
  }
}

// عرض العشرات للعداد الثاني
void display_tens2(const int tens) {
  int pin1, a, ones;
  for (pin1 = 7, a = 0; pin1 < 14; pin1++, a++) {
    digitalWrite(pin1, bitRead(number[tens], a));
  }
  for (ones = 5; ones >= 0; ones--) {
    display_ones2(ones);
    delay(1000);  // تأخير لثانية واحدة
  }
}

// عرض الواحدات للعداد الثاني
void display_ones2(const int x) {
  int pin2, b;
  for (pin2 = 0, b = 0; pin2 <= 6; pin2++, b++) {
    digitalWrite(pin2, bitRead(number[x], b));
  }
}

// إظهار الإشارة الحمراء
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

// إظهار الإشارة الخضراء
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
