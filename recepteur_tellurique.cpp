/*
 * PHOENIX SANCTUARY - Module Récepteur v1.0 (Officiel)
 * Usage strictement humanitaire et non-commercial (Licence CC-BY-NC-SA)
 * * Description : Lecture du signal reçu sur l'ESP32.
 * Compte les fronts du signal à 10 kHz pour valider la détection (Étape 2 & 4).
 */

#include <Arduino.h>

// Définition des broches de l'ESP32 Récepteur
const int PIN_SIGNAL_IN = 4;   // Entrée du signal (après protection Zener / Préampli)
const int PIN_LED_DETECT = 8;  // LED qui s'allume quand le signal Phoenix est capté

// Variables de comptage pour l'analyse du signal
volatile unsigned long compteurFronts = 0;
unsigned long dernierCalculMillis = 0;
const unsigned long FENETRE_ANALYSE_MS = 100; // Analyse toutes les 100 ms (calqué sur le Burst)

// Fonction d'interruption (s'exécute à chaque impulsion reçue)
void IRAM_ATTR detecterImpulsion() {
    compteurFronts++;
}

void setup() {
    Serial.begin(115200);
    
    pinMode(PIN_SIGNAL_IN, INPUT);
    pinMode(PIN_LED_DETECT, OUTPUT);
    
    // Attacher l'interruption sur la broche pour compter les fronts montants
    attachInterrupt(digitalPinToInterrupt(PIN_SIGNAL_IN), detecterImpulsion, RISING);
}

void loop() {
    unsigned long tempsActuelMillis = millis();

    // Toutes les 100 ms, on regarde combien d'impulsions on a reçu
    if (tempsActuelMillis - dernierCalculMillis >= FENETRE_ANALYSE_MS) {
        // Désactiver temporairement les interruptions pour lire la valeur proprement
        noInterrupts();
        unsigned long frontsCaptes = compteurFronts;
        compteurFronts = 0; // Réinitialisation pour la prochaine fenêtre
        interrupts();

        // À 10 kHz, sur une fenêtre de 100 ms, on attend théoriquement environ 1000 fronts si le signal est pur.
        // On met un seuil de détection (ex: supérieur à 200 fronts) pour filtrer le bruit du sol.
        if (frontsCaptes > 200) {
            digitalWrite(PIN_LED_DETECT, HIGH); // Signal détecté !
            Serial.print(" Phoenix Activé - Fronts captés : ");
            Serial.println(frontsCaptes);
        } else {
            digitalWrite(PIN_LED_DETECT, LOW);  // Uniquement du bruit ou émetteur OFF
        }

        dernierCalculMillis = tempsActuelMillis;
    }
}
