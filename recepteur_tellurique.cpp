C++




/*
 * PHOENIX SANCTUARY - Module Récepteur v1.1
 * Usage strictement humanitaire et non-commercial (Licence CC-BY-NC-SA)
 * Description : Lecture du signal reçu sur l'ESP32 avec calcul de seuil dynamique.
 * Optimisation v1.1 : Correction de la broche LED et synchronisation des fréquences.
 */

#include <Arduino.h>

// Définition des broches de l'ESP32 Récepteur
const int PIN_SIGNAL_IN = 4;   // Entrée du signal (GPIO 4, parfait pour les interruptions)
const int PIN_LED_DETECT = 2;  // LED interne de l'ESP32 (évite la PIN 8 conflictuelle)

// Configuration de la fréquence (Doit être la MÊME que l'émetteur)
// -> Mode Terrain / Sub-acoustique : 10 Hz
// -> Mode Labo / Audio : 10000 Hz (10 kHz)
const int FREQUENCE_CIBLE = 10; 

// Fenêtre d'analyse (en ms) adaptative selon la fréquence
const unsigned long FENETRE_ANALYSE_MS = (FREQUENCE_CIBLE == 10) ? 1000 : 100; 

// Variables de comptage globales
volatile unsigned long compteurFronts = 0;
unsigned long dernierCalculMillis = 0;

// Fonction d'interruption ultra-rapide
void IRAM_ATTR detecterImpulsion() {
    compteurFronts++;
}

void setup() {
    Serial.begin(115200);
    
    pinMode(PIN_SIGNAL_IN, INPUT);
    pinMode(PIN_LED_DETECT, OUTPUT);
    
    // Attacher l'interruption sur la broche pour compter les fronts montants
    attachInterrupt(digitalPinToInterrupt(PIN_SIGNAL_IN), detecterImpulsion, RISING);
    
    Serial.println("--- PHOENIX RECEIVER READY ---");
    Serial.print("Mode fréquence configuré sur : ");
    Serial.concat(FREQUENCE_CIBLE);
    Serial.println(" Hz");
}

void loop() {
    unsigned long tempsActuelMillis = millis();

    // Analyse périodique du signal
    if (tempsActuelMillis - dernierCalculMillis >= FENETRE_ANALYSE_MS) {
        
        // Section Atomique : On bloque les interruptions le temps de copier la valeur
        noInterrupts();
        unsigned long frontsCaptes = compteurFronts;
        compteurFronts = 0; 
        interrupts();

        // Calcul du seuil de validation dynamique
        // On s'attend à recevoir théoriquement : (Fréquence * Fenêtre en secondes)
        unsigned long frontsTheoriques = (FREQUENCE_CIBLE * FENETRE_ANALYSE_MS) / 1000;
        
        // On fixe le seuil de tolérance à 30% du signal théorique pour filtrer le bruit de fond
        unsigned long seuilMinimal = frontsTheoriques * 0.30;
        if (seuilMinimal < 1) seuilMinimal = 1; // Sécurité pour les basses fréquences

        // Validation du signal Phoenix
        if (frontsCaptes >= seuilMinimal && frontsCaptes > 0) {
            digitalWrite(PIN_LED_DETECT, HIGH); // Signal valide détecté !
            Serial.print("[Phoenix ALERT] Signal validé ! Fronts reçus : ");
            Serial.print(frontsCaptes);
            Serial.print(" / Attendus : ");
            Serial.println(frontsTheoriques);
        } else {
            digitalWrite(PIN_LED_DETECT, LOW);  // Uniquement du bruit ou émetteur coupé
        }

        dernierCalculMillis = tempsActuelMillis;
    }
}
