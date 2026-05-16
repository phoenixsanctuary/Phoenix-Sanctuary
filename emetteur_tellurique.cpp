/*
 * PHOENIX SANCTUARY - Module Émetteur v1.0 (Officiel)
 * Usage strictement humanitaire et non-commercial (Licence CC-BY-NC-SA)
 * * Description : Génération du signal carré à 10 kHz recommandé par l'audit.
 * Configuration pour ESP32 avec option d'émission en "burst" (motif ON/OFF).
 */

#include <Arduino.h>

// Définition de la broche de sortie de l'ESP32 vers le MOSFET (Étape 2 du protocole)
const int PIN_SIGNAL_OUT = 3;  // Broche reliée à la grille (gate) du MOSFET
const int PIN_LED_STATUS = 8;  // LED de validation de la carte

// Configuration de la fréquence recommandée par l'audit : 10 kHz (10000 Hz)
const int FREQUENCE_CIBLE = 10000; 
// Une période à 10 kHz dure 100 microsecondes, donc la demi-période est de 50 microsecondes
const unsigned long DEMI_PERIODE_MICROS = 1000000 / (FREQUENCE_CIBLE * 2); 

// Variables pour la génération de l'onde carrée
unsigned long dernierChangementMicros = 0;
bool etatSignal = LOW;

// Variables pour l'option recommandée : Émission en Burst (100ms ON / 100ms OFF)
unsigned long dernierChangementBurstMillis = 0;
bool burstActif = true;
const unsigned long TEMPS_BURST_MS = 100; // Fenêtre de 100 ms

void setup() {
    // Configuration des broches (Étape 1 du protocole de réalisation)
    pinMode(PIN_SIGNAL_OUT, OUTPUT);
    pinMode(PIN_LED_STATUS, OUTPUT);
    
    // Allumer la LED pour valider que l'ESP32 fonctionne
    digitalWrite(PIN_LED_STATUS, HIGH); 
}

void loop() {
    unsigned long tempsActuelMillis = millis();
    unsigned long tempsActuelMicros = micros();

    // Gestion du motif "Burst" (100 ms activé / 100 ms désactivé) pour augmenter la détection
    if (tempsActuelMillis - dernierChangementBurstMillis >= TEMPS_BURST_MS) {
        burstActif = !burstActif;
        dernierChangementBurstMillis = tempsActuelMillis;
        
        // Si on passe en mode OFF, on coupe immédiatement le signal
        if (!burstActif) {
            digitalWrite(PIN_SIGNAL_OUT, LOW);
        }
    }

    // Si le burst est actif, on génère l'onde carrée pure à 10 kHz
    if (burstActif) {
        if (tempsActuelMicros - dernierChangementMicros >= DEMI_PERIODE_MICROS) {
            etatSignal = !etatSignal;
            digitalWrite(PIN_SIGNAL_OUT, etatSignal);
            dernierChangementMicros = tempsActuelMicros;
        }
    }
}
