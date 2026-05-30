C++




/*
 * PHOENIX SANCTUARY - Module Émetteur v1.1
 * Usage strictement humanitaire et non-commercial (Licence CC-BY-NC-SA)
 * Description : Génération d'une onde carrée avec option d'émission en "burst".
 * Optimisation v1.1 : Changement de broche pour éviter les conflits d'écriture de l'ESP32.
 */

#include <Arduino.h>

// Broches modifiées pour l'ESP32 standard
const int PIN_SIGNAL_OUT = 12; // GPIO 12 (évite la PIN 3 réservée à la communication PC)
const int PIN_LED_STATUS = 2;  // LED interne classique de l'ESP32

// Configuration de la fréquence
// -> Pour du sub-acoustique (sol/talon) : utiliser 10 Hz
// -> Pour les tests de laboratoire (audio) : utiliser 10000 Hz (10 kHz)
const int FREQUENCE_CIBLE = 10; 

// Calcul automatique de la demi-période en microsecondes
const unsigned long DEMI_PERIODE_MICROS = 1000000 / (FREQUENCE_CIBLE * 2); 

// Variables de timing (Onde carrée)
unsigned long dernierChangementMicros = 0;
bool etatSignal = LOW;

// Variables de timing (Mode Burst : 100ms ON / 100ms OFF)
unsigned long dernierChangementBurstMillis = 0;
bool burstActif = true;
const unsigned long TEMPS_BURST_MS = 100; 

void setup() {
    pinMode(PIN_SIGNAL_OUT, OUTPUT);
    pinMode(PIN_LED_STATUS, OUTPUT);
    
    // Flash de démarrage pour valider le statut de la carte
    digitalWrite(PIN_LED_STATUS, HIGH); 
}

void loop() {
    unsigned long tempsActuelMillis = millis();
    unsigned long tempsActuelMicros = micros();

    // Gestion du motif "Burst" 
    if (tempsActuelMillis - dernierChangementBurstMillis >= TEMPS_BURST_MS) {
        burstActif = !burstActif;
        dernierChangementBurstMillis = tempsActuelMillis;
        
        if (!burstActif) {
            digitalWrite(PIN_SIGNAL_OUT, LOW);
            digitalWrite(PIN_LED_STATUS, LOW); // La LED clignote au rythme du burst
        }
    }

    // Génération de l'onde si le burst est actif
    if (burstActif) {
        digitalWrite(PIN_LED_STATUS, HIGH);
        if (tempsActuelMicros - dernierChangementMicros >= DEMI_PERIODE_MICROS) {
            etatSignal = !etatSignal;
            digitalWrite(PIN_SIGNAL_OUT, etatSignal);
            dernierChangementMicros = tempsActuelMicros;
        }
    }
}
