# 42-PREUVE — pourquoi ce kit peut tourner en piscine

> **Le réel.** L'IA peut résoudre n'importe quel exo de la piscine. Le sujet le dit
> noir sur blanc (Chapitre III), et c'est précisément le problème : un exo résolu par
> l'IA ne prouve rien, ne se défend pas en évaluation, et s'effondre à l'exam — où il
> n'y a *ni IA ni internet*. Faire circuler des solutions toutes faites, c'est armer ses
> camarades pour échouer.
>
> **La promesse.** Ce kit est conçu pour l'effet inverse. Il ne contient **aucune
> solution livrable** : il enseigne à **reconstruire, pas à copier**. C'est ce qui le
> rend partageable sans court-circuiter la doctrine 42 ni la Moulinette. Ce document le
> **prouve** — sur deux plans : la conformité au sujet, et la couverture chiffrée.

---

## 1. Références canoniques — ce que le sujet impose (Chap. III)

Le Chapitre III « AI Instructions » du sujet Rush00 fixe les règles. Citations directes :

- *« You should apply reasoning to your assigned tasks, especially before turning to AI. »*
- *« You should not ask for direct answers to the AI. »*
- *« Keep in mind that during exams, AI is not available — no internet, no smartphones. »*
- **Bonne pratique** (citée) : demander à un pair, discuter 10 min, *« and suddenly it clicks »*.
- **Mauvaise pratique** (citée) : copier du code IA, ne rien savoir expliquer en éval →
  échec ; puis exam sans IA → échec de nouveau.

La grille de lecture est claire : **le raisonnement avant l'outil, jamais la réponse
directe, et la preuve par la capacité à expliquer.**

---

## 2. La méthode appliquée — conformité point par point

Chaque règle du sujet est tenue par une décision de conception du kit. Pas une intention :
une décision vérifiable dans les fichiers.

| Règle du Chapitre III | Comment le kit la respecte | Vérifiable dans |
|---|---|---|
| Pas de réponse directe | **Méthode seule** : aucune fonction complète. Squelettes à trous, lignes-clés masquées. | [fiches/FICHES_QUESTIONS.md](fiches/FICHES_QUESTIONS.md) |
| Raisonner avant l'outil | Le contenu **est** le raisonnement : « questions à se poser » dans l'ordre, puis trace, puis trou à combler. | les 12 familles des fiches |
| Peer-learning | Le format se travaille à deux : l'un pose les questions, l'autre reconstruit. Rien à recopier ensemble. | section « drill » des fiches |
| Défendable en évaluation | Reconstruire = savoir expliquer. Le KPI du tracker est « refaite de tête », pas « lue ». | [TRACKER_PROGRESSION.md](TRACKER_PROGRESSION.md) |
| Survivre à l'exam (sans IA) | L'objet entier vise la reconstruction sous chrono, de mémoire. | colonne *Sous chrono* du tracker |
| Norme 42 | Squelettes conformes (pas de `for`, pas de `//`, ≤ 25 lignes, déclarations en haut). | en-tête des fiches |

> **La phrase qui résume :** une solution copiée ne se défend pas en évaluation — une
> méthode, si. Le kit ne distribue que de la méthode.

---

## 3. L'état prouvé — la couverture chiffrée

### 3.1 La méthode de comptage (reproductible)

On a pris les ~118 exercices de la piscine (Shell00 + C00→C13) et, pour chacun, on l'a
**décomposé en briques**. Un exo est « couvert » s'il se reconstruit à partir des briques
+ la colle (boucles, `if`, définition de fonction) ; il est « non couvert » s'il exige un
concept **hors** des briques. Pas d'estimation : un recomptage prototype par prototype.

### 3.2 Les 12 briques

**8 briques de noyau** (chaîne / nombre / I/O / mémoire) :
B1 `write(1,&c,1)` · B2 parcours `'\0'` · B3 `c ± '0'` · B4 `% / /` · B5 `res*base+chiffre`
· B6 swap · B7 parcours borné · B8 `malloc(+1)`.

**4 briques structurelles** (le reste du runtime) :
B9 récursion · B10 `->next` / struct · B11 pointeur de fonction · B12 `open/read/close`.

### 3.3 Le résultat (recompté sur 118 exos)

| Périmètre | 8 briques | 12 briques |
|---|---|---|
| Noyau exam (C00-04, C06, C07 = 52 exos) | **100 %** | 100 % |
| Tout le C runtime (102 exos) | 60 % | **100 %** |
| Piscine entière (118 exos) | 44 % | **86 %** |

**Trois constats vérifiés :**
1. Les **8 briques couvrent 100 % du noyau chaînes/nombres/I/O/mémoire** (52/52) — la
   zone d'exam exacte. Aucune exception.
2. Les 41 exos hors-noyau ne réclament **que** les 4 briques structurelles (B9-B12) →
   **12 briques = 100 % de tout le C runtime** (102/102).
3. Les 16 restants (4 headers C08, Makefile, libft, 10 Shell) sont **hors-runtime**
   (préprocesseur / build / shell) : non reconstructibles depuis une brique. On ne les
   compte donc pas comme « couverts » — les compter serait gonfler le chiffre.

> **À retenir : 8 briques pour blinder l'exam, 12 pour fermer toute la piscine
> (hors préprocesseur / build / shell).**

### 3.4 La preuve qu'on s'applique notre propre exigence

La première version de cette analyse annonçait « 8 briques = 80 % de *tous* les exos ».
Le recomptage l'a **réfuté** : c'était 44 %. Le chiffre a été corrigé, pas défendu. C'est
la règle : *un claim sans donnée vaut moins que pas de claim.* Le détail de l'inventaire
et des regroupements est dans [ANALYSE_PISCINE_C.md](ANALYSE_PISCINE_C.md) §1, §2, §4.

---

## 4. Charte d'usage — pour le faire tourner proprement

À diffuser avec le kit. Ce qui le garde « 42-proof » entre les mains de tous :

**À faire**
- Lire **seulement les questions**, cacher le squelette, écrire de tête, comparer après.
- Travailler à deux : poser les questions à voix haute, l'autre reconstruit.
- Compiler systématiquement `-Wall -Wextra -Werror` + norminette, dès le premier jour.
- Reporter honnêtement son état dans le tracker (Compris → Refait de tête → Sous chrono).

**À ne pas faire**
- Re-remplir les trous dans le document partagé pour en faire une banque de solutions.
  (Ça le transforme en triche, et casse la chaîne pour les suivants.)
- L'utiliser pendant un exo *à la place* de réfléchir : il sert à s'entraîner **avant**.
- Copier un squelette sans pouvoir l'expliquer : ce qui ne se défend pas ne sert à rien.

---

## 5. Composition du kit

| Fichier | Rôle |
|---|---|
| [ANALYSE_PISCINE_C.md](ANALYSE_PISCINE_C.md) | méta-index transversal : inventaire, regroupements, briques, dépendances, pronostic exam |
| [fiches/FICHES_QUESTIONS.md](fiches/FICHES_QUESTIONS.md) | 12 familles, méthode de reconstruction (questions → squelette à trous → pièges) |
| [TRACKER_PROGRESSION.md](TRACKER_PROGRESSION.md) | suivi 3 états + répétition espacée J+1 / J+3 / J+7 |
| **42-PREUVE.md** (ce document) | charte de conformité Chap. III + couverture chiffrée |

---

*Reproductible, capitalisable, honnête sur ce qu'il ne couvre pas. Aucune « vibe » : une
méthode bornée, des règles, des preuves.*
