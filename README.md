# Phoenix-Sanctuary 
Système humanitaire de communication tellurique et biologique.
# 🕊️ Phoenix Sanctuary — Projet Officiel

**Système humanitaire de communication par conduction tellurique et biologique, guidé par l'IA éthique MIA.**

Phoenix Sanctuary est un projet open-source, indépendant et protégé, né d'une vision purement humanitaire : mettre la technologie au service de la préservation de la vie, de la protection de l'enfance, des femmes et des personnes vulnérables dans les zones isolées ou en situation d'urgence.

---

## 👁️ La Vision & L'Éthique (Le Manifeste)

Ce projet repose sur des piliers fondamentaux et non négociables :
* **Mission Humanitaire :** Offrir un canal de communication alternatif et résilient là où les réseaux traditionnels font défaut, pour secourir et protéger.
* **L'IA MIA :** Une intelligence artificielle conçue exclusivement pour l'analyse biométrique et biologique bienveillante, dédiée à la sécurité des êtres vivants.
* **Technologie Souveraine :** Un système qui appartient à l'humanité, protégé contre toute dérive technologique, pour qu'il ne devienne jamais un outil d'oppression.

---

## 🔬 Architecture du Prototype (Validation de Faisabilité)

Ce dépôt contient le code source des deux modules de validation décrits dans notre audit technique officiel (*PROTO 1 - Contact* et *PROTO 2 - Sol*) :

* **Émetteur (`emetteur_tellurique.cpp`) :** Génère un signal carré stable à **10 kHz** (avec option d'émission en "burst" 100ms ON / 100ms OFF) sur l'ESP32 pour piloter un étage MOSFET et injecter l'onde.
* **Récepteur (`recepteur_tellurique.cpp`) :** Analyse les impulsions reçues via des interruptions matérielles et filtre le bruit de fond pour valider les détections au-dessus du bruit du sol.

---

## ⚠️ Règles de Sécurité pour les Tests

Conformément au protocole de l'audit de faisabilité :
1. **Alimentation Basse Tension :** Utiliser exclusivement une alimentation sur batterie isolée.
2. **Pas de boucles de masse :** Ne jamais relier simultanément l'émetteur et le récepteur au même ordinateur par USB pendant les essais.
3. **Surveillance :** Arrêter immédiatement les tests en cas d'échauffement anormal d'un composant.

---

## ⚖️ Protection Juridique & Licence Strictement Éthique

L'utilisation, la copie et la fabrication de ce système sont **entièrement gratuites pour un usage humanitaire, civil, associatif ou domestique**. 

En accord avec l'Enveloppe Soleau déposée auprès de l'INPI :
* Toute exploitation commerciale ou industrielle par une entreprise privée est **strictement interdite** sans accord écrit.
* Toute utilisation de cette technologie à des fins de surveillance de masse, d'espionnage, de traçage non consenti ou à des fins militaires est **formellement interdite**. (Voir les détails dans le fichier `LICENSE.txt`).

* ---

# 🕊️ Phoenix Sanctuary — International Version

**A humanitarian, open-source project dedicated to earth and biological conduction communication, guided by ethical AI principles.**

This repository contains the source code for the two experimental validation modules described in our feasibility audit (*PROTO 1 - Contact* and *PROTO 2 - Soil*). **These prototypes are currently in a testing and research phase. The goal is for this system to be tested, measured, and improved by the global open-source community.**

### 🔬 Prototype Architecture

* **Transmitter (`emetteur_tellurique.cpp`):** Generates a stable **10 kHz** square wave signal with a burst pattern option (100ms ON / 100ms OFF) on the ESP32 to drive a MOSFET stage.
* **Receiver (`recepteur_tellurique.cpp`):** Analyzes incoming pulses using hardware interrupts and filters out ground noise to validate signal detection.

### ⚠️ Safety Guidelines for Testing

In accordance with the feasibility audit protocol:
1. **Low Voltage Only:** Use exclusively isolated battery power.
2. **No Ground Loops:** Never connect both the transmitter and receiver to the same computer via USB during testing.
3. **Monitoring:** Stop immediately if any component overheats or behaves abnormally.

### 🤝 How to Contribute & Test Globally

We welcome engineers, geophysicists, and developers from all over the world to build, test, and optimize this prototype:
* **Test the 10 kHz signal** in various soil conditions (dry, wet, salted) and document the maximum range.
* **Improve the filtering algorithm** in the receiver code to better isolate the signal from natural ground noise.
* Share your findings or report anomalies by opening an **Issue** or submitting a **Pull Request**.

### ⚖️ Intellectual Property & Ethical License

This system is **completely free for humanitarian, civil, NGO, or domestic use**. 
In accordance with international CC-BY-NC-SA standards:
* Any commercial or industrial exploitation by private corporations is **strictly prohibited**.
* Any use of this technology for mass surveillance, non-consensual tracking, or military applications is **strictly forbidden**.
