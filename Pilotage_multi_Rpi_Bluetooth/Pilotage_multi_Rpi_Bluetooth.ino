/*
 * decodage des touches télécommande bande de leds
 * Lib: https://github.com/z3t0/Arduino-IRremote
 */

#include <IRremote.h>
#include <SoftwareSerial.h>

//################
//# DÉCLARATIONS #
//################
//——— Prototypes Fonctions ———//
void arcade(void);
void decodage_touche(void);

//——— Pins ———//
int RECV_PIN = 12;
#define pinBluetooth_rx 7 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define pinBluetooth_tx 8 // Broche 10 en tant que TX, à raccorder sur RX du HC-05
SoftwareSerial SerialBluetooth(pinBluetooth_rx, pinBluetooth_tx);

//——— Lib ———//
IRrecv irrecv(RECV_PIN);
decode_results results;

//#########
//# SETUP #
//#########
void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  Serial.println("Enabled IRin");
  
  // INITIALISATION PORT SERIAL BLUETOOTH
  pinMode(pinBluetooth_rx, INPUT);
  pinMode(pinBluetooth_tx, OUTPUT);
  SerialBluetooth.begin(9600);
  SerialBluetooth.println("Hello Viewer");
  
}

//#############
//# FONCTIONS #
//#############
void arcade() {
  switch (results.value) {
    case 0xF730CF:  // Vol-
      Serial.println("R2 — Vol-");
      SerialBluetooth.println("R2"); // mot envoyé pour commande en bluetooth
      results.value =0;           // empéche la répétition de touche
      break;
      
    case 0xF7B04F:  // Vol+
      Serial.println("G2 — Vol+");
      SerialBluetooth.println("G2"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;
      
    case 0xF7708F:  // Lum-
      Serial.println("B2 — Lum-");
      SerialBluetooth.println("B2"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;
      
    case 0xF7F00F:  // Lum+
      Serial.println("STROBE — Lum+");
      SerialBluetooth.println("STROBE"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;  
      
    case 0xF708F7:  // <<
      Serial.println("R3 — <<");
      SerialBluetooth.println("R3"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;
      
    case 0xF78877:  // >>
      Serial.println("G3 — >>");
      SerialBluetooth.println("G3"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;

    case 0xF748B7:  // Précédent
      Serial.println("B3 — Précédent");
      SerialBluetooth.println("B3"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;   

    case 0xF7C837:  // Suivant
      Serial.println("Fade — Suivant");
      SerialBluetooth.println("FADE"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;
          
    case 0xF728D7:  // Play/pause
      Serial.println("R4 — Play/pause");
      SerialBluetooth.println("R4"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;  

    case 0xF7A857:  // Stop
      Serial.println("G4 — Stop");
      SerialBluetooth.println("G4"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;  
      
    case 0xF7E817:  // Power
      Serial.println("Smooth — Power");
      SerialBluetooth.println("SMOOTH"); // mot envoyé pour commande en bluetooth
      results.value =0;
      break;  
         
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
  
}
// Mapping télécommande :
//                  ON      OFF
//F700FF  F7807F  F740BF  F7C03F
//  R0      G0      B0      W
//F720DF  F7A05F  F7609F  F7E01F
//  R1      G1      B1     Flash
//F710EF  F7906F  F750AF  F7D02F
//  R2      G2      B2     Strobe
//F730CF  F7B04F  F7708F  F7F00F
//  R3      G3      B3     Fade
//F708F7  F78877  F748B7  F7C837
//  R4      G4      B4     Smooth
//F728D7  F7A857  F76897  F7E817


void decodage_touche() {
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

//#############
//# PROGRAMME #
//#############
void loop() {
//  decodage_touche();  // pour récupérer le code des touches
  arcade();
  delay(100);
}
