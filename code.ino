//                     https://alfadex.com/2015/03/bird-timer-switch-v-2/

const byte ledFade = 9;                   // pin για ρύθμηση φωτεινότητας λάμπας πυρακτώσεως
const byte buttonPin = 2;                 // εντολή απο το μετρητή - ρολοι
int val = 0;                              // variable for reading the pin status
static unsigned int count;                // variable for fading
const byte relayFthoriou = 8;             // ρελές για λαμπα φθορίου
const byte relaynight = 3;                // ρελές για λαμπα μεσάνυχτα
const byte LedMorning = 7;                // led πρωινο
const byte LedDay = 5;                    // led ημέρας για λαμπα φθορίου
const byte Lednyxtoma = 6;                // led όταν βραδιαζει
const byte Lednight = 4;                  // led για μεσάνυχτα
int buttonState = 0;
int timer;

int kshmeroma() {                         // εδω ξεκινάει να αναβει η λάμπα πυρακτώσεως για κάποια λετπά
  digitalWrite(relaynight, LOW);          // σβήνει το relay για τη λάμπα νυκτός
  while (count > 2) {                     // ξεκινάει απο το 255(σβηστή)έως το 2 που είναι τερμα αναμένη
    count--;
    analogWrite(ledFade,        count);
    delay(4900);                          //καθε step απο τα 250,έχει 4,9sec καθυστέρηση 4,9x250=1225sec / 60 = 20.4 λεπτά
    Serial.println(count);
    digitalWrite(LedMorning,    HIGH);    // ανάβει το led morning
    digitalWrite(LedDay,        LOW);     // σβήνει το led day
    digitalWrite(Lednyxtoma,    LOW);     // σβήνει το led nightfall
    digitalWrite(Lednight,      LOW);     // σβήνει το led night
  }
  //εδω έχει περάσει ο χρόνος σβησίματος, οπότε σβήνει η πυρακτώσεως και ανάβει η φθορίου
  analogWrite(ledFade,        255);       // εδώ κρατάω τέρμα σβηστή τη λάμπα πυρακτώσεως
  digitalWrite(LedMorning,    LOW);       // σβήνει το led morning
  digitalWrite(LedDay,        HIGH);      // ανάβει το led day
  digitalWrite(Lednyxtoma,    LOW);       // σβήνει το led nightfall
  digitalWrite(Lednight,      LOW);       // σβήνει το led night
  digitalWrite(relayFthoriou, HIGH);      // ενεργοποιείται το ρελε για τη λαμπα φθορίου
}

int nyxtoma() {                           // εδω ξεκιναει να σβήνει η πυρακτώσεως για καποια λεπτά.Η count είναι 1
  while ( count < 254) {                  // ξεκινάει απο το 1(τέρμα αναμένη) έως το 253 που είναι σβηστή
    count++;
    analogWrite(ledFade,        count);
    delay(4900);                          //καθε step απο τα 250,έχει 4,9sec καθυστέρηση 4,9x250=1225sec / 60 = 20.4 λεπτά
    digitalWrite(relayFthoriou, LOW);     // σβήνει το ρελε για τη λαμπα φθορίου
    digitalWrite(LedDay,        LOW);     // σβήνει το led day
    digitalWrite(Lednyxtoma,    HIGH);    // ανάβει το led nightfall
    Serial.println(count);
  }
  //εδω έχει περάσει ο χρόνος σβησίματος, οπότε σβήνει η πυρακτώσεως και ανάβει το φως νυκτός
  analogWrite(ledFade,          255);     // εδώ κρατάω τέρμα σβηστή τη λάμπα πυρακτώσεως
  digitalWrite(LedMorning,      LOW);     // σβήνει το led morning
  digitalWrite(LedDay,          LOW);     // σβήνει το led day
  digitalWrite(Lednyxtoma,      LOW);     // σβήνει το led nightfall
  digitalWrite(Lednight,        HIGH);    // ανάβει το led night
  digitalWrite(relaynight,      HIGH);    // ενεργοποιείται το ρελε για λάμπα νυκτός
}

void setup() {

  count = 255;                            // μεταβλητή για πυρακτώσεως. 255=σβηστή  0=αναμένη
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);              // διακόπτης απο timer.Όταν ανάβει το led του timer, έχω buttonStatelow αλλιώς high
  pinMode(ledFade, OUTPUT);               // έξοδος που ρυθμήζεις την ένταση της πυρακτώσεως αλλάζοντας τη count
  pinMode(LedMorning, OUTPUT);            // led για ειδοποίηση λάμπας πυρακτώσεως  (morning)
  pinMode(LedDay, OUTPUT);                // led για ειδοποίηση λαμπας φθορίου      (day)
  pinMode(Lednyxtoma, OUTPUT);            // led για ειδοποιήση λάμπας φθορίου      (nightfall)
  pinMode(Lednight, OUTPUT);              // led για ειδοποιήση λάμπας νυκτός       (night)
  pinMode(relayFthoriou, OUTPUT);         // ρελές για να ανάψει η λάμπα φθορίου
  pinMode(relaynight, OUTPUT);            // ρελές για να ανάψει το λαμπάκι νυκτός

                                          // αρχικοποίηση όλα σε LOW
  digitalWrite(ledFade, LOW);      
  digitalWrite(relayFthoriou, LOW);   
  digitalWrite(relaynight, LOW);
  digitalWrite(LedMorning, LOW);
  digitalWrite(Lednyxtoma, LOW);
  digitalWrite(LedDay, LOW);
  analogWrite(ledFade, count);
}

void  loop() {
  buttonState = digitalRead(buttonPin);
  //  if (buttonState != lastButtonState) {

  if (buttonState == HIGH) {
    nyxtoma();
    //Serial.println("buttonStatehigh");
  } else {
    //Serial.println("buttonStatelow");
    kshmeroma();
  }
}
