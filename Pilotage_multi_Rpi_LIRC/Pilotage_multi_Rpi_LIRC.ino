/* Pilotage IR MiniGameCenter
 * Gestion du power on/off */

#include <IRremote.h>
#include <SoftwareSerial.h>

//################
//# DÉCLARATIONS #
//################
//——— Prototypes Fonctions ———//
void arcade(void);
void decodage_touche(void);
void Power(void);

//——— Pins ———//
#define RPi02   2
#define RPi03   3
#define RPi04   4
#define RPi05   5
#define RPi06   6
#define RPi07   7
#define RPi08   8
#define RPi09   9
#define RPi10   10
#define RPi01   11
int RECV_PIN = 12;

//——— Variables ———//
int Activation = 0;

//——— Lib ———//
IRrecv irrecv(RECV_PIN);
decode_results results;

//#########
//# SETUP #
//#########
void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  Serial.println("Enabled IRin");
  
  pinMode(RPi01, OUTPUT);
  pinMode(RPi02, OUTPUT);
  pinMode(RPi03, OUTPUT);
  pinMode(RPi04, OUTPUT);
  pinMode(RPi05, OUTPUT);
  pinMode(RPi06, OUTPUT);
  pinMode(RPi07, OUTPUT); 
  pinMode(RPi08, OUTPUT);
  pinMode(RPi09, OUTPUT);
  pinMode(RPi10, OUTPUT);  

  digitalWrite(RPi01, HIGH);
  digitalWrite(RPi02, HIGH);
  digitalWrite(RPi03, HIGH);
  digitalWrite(RPi04, HIGH);
  digitalWrite(RPi05, HIGH);
  digitalWrite(RPi06, HIGH);
  digitalWrite(RPi07, HIGH);
  digitalWrite(RPi08, HIGH);
  digitalWrite(RPi09, HIGH);
  digitalWrite(RPi10, HIGH);              
}

//#############
//# FONCTIONS #
//#############
void decodage_touche() {
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

void Selection() {
  switch (results.value) {

    case 0x1CF:  // Pinnacle PCTV_800i touche 1 (elle répond à deux codes, 1CF et 9CF)
      Serial.println("Selection Rpi N°1");
      results.value = 0;           // empéche la répétition de touche
      Activation = 1;
      break;
    case 0x9CF:  // Pinnacle PCTV_800i touche 1 (elle répond à deux codes, 1CF et 9CF)
      Serial.println("Selection Rpi N°1");
      results.value = 0;           // empéche la répétition de touche
      Activation = 1;
      break;

    case 0x1D5:  // Pinnacle PCTV_800i touche 2 (elle répond à deux codes, 1D5 et 9D5)
      Serial.println("Selection Rpi N°2");
      results.value = 0;           // empéche la répétition de touche
      Activation = 2;
      break;
    case 0x9D5:  // Pinnacle PCTV_800i touche 2 (elle répond à deux codes, 1D5 et 9D5)
      Serial.println("Selection Rpi N°2");
      results.value = 0;           // empéche la répétition de touche
      Activation = 2;
      break;

    case 0x1D0:  // Pinnacle PCTV_800i touche 3)
      Serial.println("Selection Rpi N°3");
      results.value = 0;           // empéche la répétition de touche
      Activation = 3;
      break;
    case 0x9D0:  // Pinnacle PCTV_800i touche 3
      Serial.println("Selection Rpi N°3");
      results.value = 0;           // empéche la répétition de touche
      Activation = 3;
      break;

    case 0x1D8:  // Pinnacle PCTV_800i touche 4)
      Serial.println("Selection Rpi N°4");
      results.value = 0;           // empéche la répétition de touche
      Activation = 4;
      break;
    case 0x9D8:  // Pinnacle PCTV_800i touche 4
      Serial.println("Selection Rpi N°4");
      results.value = 0;           // empéche la répétition de touche
      Activation = 4;
      break;

    case 0x1DB:  // Pinnacle PCTV_800i touche 5)
      Serial.println("Selection Rpi N°5");
      results.value = 0;           // empéche la répétition de touche
      Activation = 5;
      break;
    case 0x9DB:  // Pinnacle PCTV_800i touche 5)
      Serial.println("Selection Rpi N°5");
      results.value = 0;           // empéche la répétition de touche
      Activation = 5;
      break;

    case 0x1DE:  // Pinnacle PCTV_800i touche 6)
      Serial.println("Selection Rpi N°6");
      results.value = 0;           // empéche la répétition de touche
      Activation = 6;
      break;
    case 0x9DE:  // Pinnacle PCTV_800i touche 6)
      Serial.println("Selection Rpi N°6");
      results.value = 0;           // empéche la répétition de touche
      Activation = 6;
      break;

    case 0x1D1:  // Pinnacle PCTV_800i touche 7)
      Serial.println("Selection Rpi N°7");
      results.value = 0;           // empéche la répétition de touche
      Activation = 7;
      break;
    case 0x9D1:  // Pinnacle PCTV_800i touche 7)
      Serial.println("Selection Rpi N°7");
      results.value = 0;           // empéche la répétition de touche
      Activation = 7;
      break;

    case 0x1E1:  // Pinnacle PCTV_800i touche 8)
      Serial.println("Selection Rpi N°8");
      results.value = 0;           // empéche la répétition de touche
      Activation = 8;
      break;
    case 0x9E1:  // Pinnacle PCTV_800i touche 8)
      Serial.println("Selection Rpi N°8");
      results.value = 0;           // empéche la répétition de touche
      Activation = 8;
      break;

    case 0x1D2:  // Pinnacle PCTV_800i touche 9)
      Serial.println("Selection Rpi N°9");
      results.value = 0;           // empéche la répétition de touche
      Activation = 9;
      break;
    case 0x9D2:  // Pinnacle PCTV_800i touche 9)
      Serial.println("Selection Rpi N°9");
      results.value = 0;           // empéche la répétition de touche
      Activation = 9;
      break;

    case 0x1E7:  // Pinnacle PCTV_800i touche 0)
      Serial.println("Selection Rpi N°10");
      results.value = 0;           // empéche la répétition de touche
      Activation = 10;
      break;
    case 0x9E7:  // Pinnacle PCTV_800i touche 0)
      Serial.println("Selection Rpi N°10");
      results.value = 0;           // empéche la répétition de touche
      Activation = 10;
      break;

    case 0x1C1:  // Pinnacle PCTV_800i touche menu
      Serial.println("Selection de tous les Rpi !");
      results.value = 0;           // empéche la répétition de touche
      Activation = 11;
      break;
    case 0x9C1:  // Pinnacle PCTV_800i touche menu
      Serial.println("Selection de tous les Rpi !");
      results.value = 0;           // empéche la répétition de touche
      Activation = 11;
      break;
        
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}

void PowerONOFF(){
  if ((Activation == 1) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°1");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi01, LOW);   // Power ON Rpi N°1
    delay(300);                 // simule un appuie court
    digitalWrite(RPi01, HIGH);
  }
  else if ((Activation == 2) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°2");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi02, LOW);   // Power ON Rpi N°2
    delay(300);                 // simule un appuie court
    digitalWrite(RPi02, HIGH);
  }
  else if ((Activation == 3) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°3");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi03, LOW);   // Power ON Rpi N°3
    delay(300);                 // simule un appuie court
    digitalWrite(RPi03, HIGH);
  }
  else if ((Activation == 4) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°4");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi04, LOW);   // Power ON Rpi N°4
    delay(300);                 // simule un appuie court
    digitalWrite(RPi04, HIGH);
  }
  else if ((Activation == 5) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°5");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi05, LOW);   // Power ON Rpi N°5
    delay(300);                 // simule un appuie court
    digitalWrite(RPi05, HIGH);
  }
  else if ((Activation == 6) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°6");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi06, LOW);   // Power ON Rpi N°6
    delay(300);                 // simule un appuie court
    digitalWrite(RPi06, HIGH);
  }
  else if ((Activation == 7) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°7");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi07, LOW);   // Power ON Rpi N°7
    delay(300);                 // simule un appuie court
    digitalWrite(RPi07, HIGH);
  }
  else if ((Activation == 8) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°8");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi08, LOW);   // Power ON Rpi N°8
    delay(300);                 // simule un appuie court
    digitalWrite(RPi08, HIGH);
  }
  else if ((Activation == 9) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°9");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi09, LOW);   // Power ON Rpi N°9
    delay(300);                 // simule un appuie court
    digitalWrite(RPi09, HIGH);
  }
  else if ((Activation == 10) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF Rpi N°10");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi10, LOW);   // Power ON Rpi N°10
    delay(300);                 // simule un appuie court
    digitalWrite(RPi10, HIGH);
  }
  else if ((Activation == 11) && ((results.value == 0x1F9) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Power ON/OFF de tous les Rpi !");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi01, LOW);   // Power ON Rpi N°1   
    digitalWrite(RPi02, LOW);   // Power ON Rpi N°2
    digitalWrite(RPi03, LOW);   // Power ON Rpi N°3
    digitalWrite(RPi04, LOW);   // Power ON Rpi N°4   
    digitalWrite(RPi05, LOW);   // Power ON Rpi N°5
    digitalWrite(RPi06, LOW);   // Power ON Rpi N°6
    digitalWrite(RPi07, LOW);   // Power ON Rpi N°7   
    digitalWrite(RPi08, LOW);   // Power ON Rpi N°8
    digitalWrite(RPi09, LOW);   // Power ON Rpi N°9
    digitalWrite(RPi10, LOW);   // Power ON Rpi N°10
    delay(300);                 // simule un appuie court
    digitalWrite(RPi01, HIGH);    
    digitalWrite(RPi02, HIGH);
    digitalWrite(RPi03, HIGH);
    digitalWrite(RPi04, HIGH);    
    digitalWrite(RPi05, HIGH);
    digitalWrite(RPi06, HIGH);
    digitalWrite(RPi07, HIGH);    
    digitalWrite(RPi08, HIGH);
    digitalWrite(RPi09, HIGH);    
    digitalWrite(RPi10, HIGH); 
  }
}

void ForcePowerOFF(){
  if ((Activation == 1) && ((results.value == 0x1F6) || (results.value == 0x9F9))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°1");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi01, LOW);   // Force Power OFF Rpi N°1
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi01, HIGH);
  }
  else if ((Activation == 2) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°2");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi02, LOW);   // Force Power OFF Rpi N°2
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi02, HIGH);
  }
  else if ((Activation == 3) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°3");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi03, LOW);   // Force Power OFF Rpi N°3
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi03, HIGH);
  }
  else if ((Activation == 4) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°4");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi04, LOW);   // Force Power OFF Rpi N°4
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi04, HIGH);
  }
  else if ((Activation == 5) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°5");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi05, LOW);   // Force Power OFF Rpi N°5
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi05, HIGH);
  }
  else if ((Activation == 6) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°6");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi06, LOW);   // Force Power OFF Rpi N°6
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi06, HIGH);
  }
  else if ((Activation == 7) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°7");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi07, LOW);   // Force Power OFF Rpi N°7
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi07, HIGH);
  }
  else if ((Activation == 8) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°8");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi08, LOW);   // Force Power OFF Rpi N°8
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi08, HIGH);
  }
  else if ((Activation == 9) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°9");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi09, LOW);   // Force Power OFF Rpi N°9
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi09, HIGH);
  }
  else if ((Activation == 10) && ((results.value == 0x1F6) || (results.value == 0x9F6))) {
    Activation = 0;
    Serial.println("Force Power OFF Rpi N°10");
    results.value = 0;          // empéche la répétition de touche
    digitalWrite(RPi10, LOW);   // Force Power OFF Rpi N°10
    delay(3000);                 // simule un appuie long
    digitalWrite(RPi10, HIGH);
  }
}

//#############
//# PROGRAMME #
//#############
void loop() {
  decodage_touche();  // pour récupérer le code des touches
  Selection();        // sélectionne le Rpi à opérer
  PowerONOFF();       // appelle le script de powerOff, seulement si le Rpi a été sélectionné avant
  ForcePowerOFF();    // Coupe l'alim du Rpi brutalement, seulement si le Rpi a été sélectionné avant
  delay(100);
}
