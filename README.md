# 🎮 Quiz Game en C

## 📌 Description

> Ce projet a été réalisé dans le cadre de mes études en Business Intelligence.
> Il s'agit d'un **jeu de quiz** développé en langage **C** sous forme d'application console.

Le joueur doit répondre à des questions de culture générale choisies **aléatoirement** depuis une base de données contenant plusieurs questions de différents niveaux.

Le jeu devient progressivement **plus difficile** à chaque niveau :

| Niveau | Difficulté |
|--------|-----------|
| 🟢 Niveau 1 | Questions **faciles** |
| 🟡 Niveau 2 | Questions **moyennes** |
| 🔴 Niveau 3 | Questions **difficiles** |

Le joueur gagne un **montant d'argent virtuel** après chaque bonne réponse.

## ⚙️ Fonctionnement du Jeu

Le quiz est divisé en **3 niveaux** :

### 🔹 Niveau 1 — Facile
- 3 questions faciles sont proposées
- Le joueur doit répondre correctement à **au moins 1 question sur 3** pour passer au niveau suivant

### 🔹 Niveau 2 — Moyen
- 3 questions de difficulté moyenne
- Il faut obtenir **au moins 2 bonnes réponses sur 3**

### 🔹 Niveau 3 — Difficile
- 3 questions difficiles
- Le joueur doit répondre correctement aux **3 questions** pour gagner complètement le jeu

> 💡 Si le joueur échoue, il **garde simplement l'argent virtuel** gagné pendant la partie.

## 💰 Système de Score

Le score augmente selon le **niveau de difficulté** :

| 🏆 Niveau | 💵 Gain par bonne réponse |
|-----------|--------------------------|
| 🟢 Facile  | **100 000 $** |
| 🟡 Moyen   | **150 000 $** |
| 🔴 Difficile | **200 000 $** |

> 🥇 Le **meilleur score** est sauvegardé pendant l'exécution du programme.

## 🛠️ Fonctionnalités

- Questions choisies **aléatoirement**
- Plusieurs **niveaux de difficulté**
- **Système de score**
- Sauvegarde du **meilleur score**
- **Réinitialisation** du score
- **Menu d'aide**
- **Interface console** interactive
- Effets sonores et **messages colorés**

## 🧩 Fonctions Principales

| **Fonction** | **Description** |
|---|---|
| `menu()` | Affiche le menu principal |
| `start()` | Lance une nouvelle partie |
| `passed()` | Vérifie si le joueur passe au niveau suivant |
| `edit_score()` | Met à jour le score |
| `show_score()` | Affiche le meilleur score |
| `reset_score()` | Réinitialise le score |
| `help()` | Affiche les règles du jeu |
| `base_donnees()` | Contient toutes les questions |

## 🖥️ Technologies Utilisées

- **Langage :** C
- **Bibliothèques standards :**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
```

## 📄 Rapport du Projet

Le dépôt contient également un fichier **PDF** expliquant :

- L'organisation du programme
- Les différentes fonctions
- Le déroulement du projet
