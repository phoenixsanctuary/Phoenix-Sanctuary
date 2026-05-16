# 🤝 Contribuer au Projet Phoenix Sanctuary

Bienvenue ! Le projet Phoenix Sanctuary est une initiative humanitaire ouverte. Les prototypes actuels (Module Contact et Module Sol à 10 kHz) sont en **phase de test et de validation expérimentale**. 

Si vous avez des compétences en électronique, en programmation ou en géophysique, votre aide est précieuse pour tester, valider et améliorer ce système !

---

## 🧪 Comment nous aider à tester ?

Vous pouvez construire le prototype chez vous en suivant l'audit et le code fourni, puis nous partager vos retours sur les points suivants :

1. **Mesures de conductivité du sol :** Est-ce que le signal à 10 kHz passe bien chez vous ? Quelle est la distance maximale que vous avez pu atteindre entre l'émetteur et le récepteur ?
2. **Analyse du bruit :** Rencontrez-vous beaucoup de faux positifs (bruit de fond du sol ou interférences) lorsque l'émetteur est éteint ?
3. **Amélioration du filtre :** Le code actuel utilise un seuil simple pour compter les fronts. Si vous savez comment coder un filtre numérique plus performant sur l'ESP32, vos propositions sont les bienvenues.
4. **Optimisation électronique :** Toute suggestion pour améliorer le préamplificateur TL072 ou l'étage MOSFET afin d'augmenter la portée tout en restant en basse tension.

---

## 📢 Comment partager vos résultats ?

* **Ouvrir une "Issue" :** Si vous observez un problème, un échauffement de composant, ou si vous avez une idée d'amélioration, cliquez sur l'onglet **Issues** en haut de ce GitHub et décrivez votre observation.
* **Proposer une modification (Pull Request) :** Si vous avez corrigé le code ou optimisé les réglages, proposez directement vos modifications de fichiers.

Ensemble, améliorons ce système pour le rendre le plus fiable et sécurisé possible pour les populations vulnérables. Merci pour votre aide !
