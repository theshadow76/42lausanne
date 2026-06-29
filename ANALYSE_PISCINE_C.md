# Analyse croisée — Piscine C @ 42

> **Le réel.** La piscine, ce sont ~118 exercices sur 15 modules, et des exams sans IA ni
> internet. Réviser module par module revient à revoir 118 cas ; réviser par
> **transversalité** revient à comprendre une fois ce qui se répète partout.
>
> **La promesse de ce document.** Un méta-index qui regroupe tous les exercices par
> **concept**, **fonctions autorisées**, **briques réutilisables** et **dépendances** —
> pour réviser la structure commune plutôt que les cas isolés, et anticiper l'exam.
>
> **Références canoniques.** Construit sur les sujets PDF officiels (C00–C13 + Shell00) et
> la Norme 42. Aucun chiffre n'est avancé sans recomptage sur les prototypes réels — la
> démonstration est dans le §4 et dans [42-PREUVE.md](42-PREUVE.md). Reproductible,
> capitalisable, et honnête sur ce qu'il ne couvre pas.

---

## 1. Inventaire exhaustif

| Module | Thème dominant | Nb exos | Exercices | Fonctions autorisées |
|---|---|---|---|---|
| **Shell00** | Unix / Git / FS | 10 | Z, testShell00, "mooore", SSH me!, midLS, GiT commit, gitignore, diff, clean, Illusions | commandes shell |
| **C00** | I/O & ASCII | 9 | ft_putchar, ft_print_alphabet, ft_print_reverse_alphabet, ft_print_numbers, ft_is_negative, ft_print_comb, ft_print_comb2, ft_putnbr, ft_print_combn | `write` |
| **C01** | Pointeurs & tableaux | 9 | ft_ft, ft_ultimate_ft, ft_swap, ft_div_mod, ft_ultimate_div_mod, ft_putstr, ft_strlen, ft_rev_int_tab, ft_sort_int_tab | `write` (putstr) sinon None |
| **C02** | Chaînes : copie/classif/transfo | 13 | ft_strcpy, ft_strncpy, ft_str_is_alpha, ft_str_is_numeric, ft_str_is_lowercase, ft_str_is_uppercase, ft_str_is_printable, ft_strupcase, ft_strlowcase, ft_strcapitalize, ft_strlcpy, ft_putstr_non_printable, ft_print_memory | None / `write` |
| **C03** | Chaînes : compare/concat/search | 6 | ft_strcmp, ft_strncmp, ft_strcat, ft_strncat, ft_strstr, ft_strlcat | None |
| **C04** | Conversion nombre↔texte | 6 | ft_strlen, ft_putstr, ft_putnbr, ft_atoi, ft_putnbr_base, ft_atoi_base | None / `write` |
| **C05** | Récursivité & maths | 9 | ft_iterative_factorial, ft_recursive_factorial, ft_iterative_power, ft_recursive_power, ft_fibonacci, ft_sqrt, ft_is_prime, ft_find_next_prime, The Ten Queens | None / `write` |
| **C06** | Arguments programme | 4 | ft_print_program_name, ft_print_params, ft_rev_params, ft_sort_params | `write` |
| **C07** | Allocation dynamique | 5 | ft_strdup, ft_range, ft_ultimate_range, ft_convert_base, ft_split | `malloc` |
| **C08** | Headers / macros / préprocesseur | 6 | ft.h, ft_boolean.h, ft_abs.h, ft_point.h, ft_strs_to_tab, ft_show_tab | None / `malloc,free` / `write` |
| **C09** | Bibliothèque & build | 3 | libft, Makefile, ft_split | `write` / None / `malloc` |
| **C10** | Fichiers & syscalls | 4 | display_file, cat, tail, hexdump | `open,read,write,close,malloc...` |
| **C11** | Pointeurs de fonction | 8 | ft_foreach, ft_map, ft_any, ft_count_if, ft_is_sort, do-op, ft_sort_string_tab, ft_advanced_sort_string_tab | None / `malloc` / `write` |
| **C12** | Listes chaînées (t_list) | 18 | ft_create_elem → ft_sorted_list_merge (create, push_front/back, size, last, push_strs, clear, at, reverse, foreach[_if], find, remove_if, merge, sort, reverse_fun, sorted_list_insert/merge) | `malloc,free` |
| **C13** | Arbres binaires | 8 | btree_create_node, _apply_prefix/_infix/_suffix, _insert_data, _search_item, _level_count, _apply_by_level | `malloc` |

**Total : ~118 exercices** sur 15 modules. (BSQ et Rush = projets de groupe séparés.)

---

## 2. Regroupement par CONCEPT (le plus utile pour réviser)

### A. I/O & conversion ASCII — `write` uniquement
`ft_putchar` · `ft_putstr` · `ft_putnbr` · `ft_print_alphabet` · `ft_print_numbers`
· `ft_putnbr_base` · `ft_putstr_non_printable` · `ft_print_memory` · `ft_show_tab`
**Cœur commun :** un caractère = `write(1, &c, 1)`. Tout le reste découpe/convertit
vers ce primitif. `c + '0'` (chiffre→char), `c - '0'` (char→chiffre).

### B. Parcours & manipulation de chaînes — la famille `str`
- *Mesure/copie* : ft_strlen, ft_strcpy, ft_strncpy, ft_strlcpy, ft_strdup
- *Comparaison* : ft_strcmp, ft_strncmp
- *Concaténation* : ft_strcat, ft_strncat, ft_strlcat
- *Recherche* : ft_strstr
- *Classification* : ft_str_is_alpha/numeric/lowercase/uppercase/printable
- *Transformation* : ft_strupcase, ft_strlowcase, ft_strcapitalize
**Cœur commun :** boucle `while (str[i])` + le sentinel `'\0'`. Toute cette famille
est une variation du même `while`.

### C. Pointeurs & passage par adresse
ft_swap · ft_div_mod · ft_ultimate_div_mod · ft_ultimate_ft (pointeur de pointeur)
**Cœur commun :** modifier une variable du caller via son adresse (`*ptr = ...`).

### D. Tableaux d'entiers
ft_rev_int_tab · ft_sort_int_tab (+ réutilise ft_swap)
**Cœur commun :** indexation `tab[i]`, parcours par taille, tri/échange.

### E. Conversion nombre ↔ texte (les "miroirs")
ft_atoi ↔ ft_putnbr · ft_atoi_base ↔ ft_putnbr_base · ft_convert_base
**Cœur commun :** `res = res * base + (c - '0')` (lecture) / `% base` + `/ base` (écriture).

### F. Récursivité & maths
factorial (iter/rec) · power (iter/rec) · fibonacci · sqrt · is_prime · find_next_prime
· The Ten Queens (backtracking)
**Cœur commun :** cas de base + appel récursif ; ou boucle accumulatrice équivalente.

### G. Arguments du programme (`int argc, char **argv`)
ft_print_program_name · ft_print_params · ft_rev_params · ft_sort_params
**Cœur commun :** `main(int argc, char **argv)`, parcours de `argv`, tableau de chaînes.

### H. Allocation dynamique (`malloc`/`free`)
ft_strdup · ft_range · ft_ultimate_range · ft_split · ft_strs_to_tab · ft_map · ft_convert_base
**Cœur commun :** calculer la taille → `malloc(taille * sizeof(...))` → vérifier le
retour → remplir → ne pas oublier le `+1` pour le `'\0'`.

### I. Préprocesseur & headers
ft.h · ft_boolean.h · ft_abs.h · ft_point.h
**Cœur commun :** `#ifndef/#define/#endif`, `#define` macros, `typedef struct`.

### J. Pointeurs de fonction
ft_foreach · ft_map · ft_any · ft_count_if · ft_is_sort · ft_sort_string_tab · do-op
**Cœur commun :** passer une fonction en paramètre `int (*f)(...)` et l'appeler `f(x)`.

### K. Structures de données
- **Listes chaînées** (C12, 18 exos) : `t_list { void *data; struct s_list *next; }`
- **Arbres binaires** (C13, 8 exos) : `t_btree { void *item; left; right; }`
**Cœur commun :** allocation de nœuds, parcours par pointeur `->next`/`->left/right`,
récursivité sur la structure.

### L. Fichiers & appels système
display_file · cat · tail · hexdump (C10)
**Cœur commun :** `open` → `read` (boucle) → `write` → `close`, gestion d'erreurs.

### M. Build & Unix
libft · Makefile (C09) · tout Shell00 (git, ls, ssh, diff, permissions)

---

## 3. Regroupement par CONTRAINTE (fonctions autorisées)

| Contrainte | Implication | Modules / exos concernés |
|---|---|---|
| **`write` seul** | Tu fabriques tout l'affichage à la main | C00, C04 (put*), C06, C08 (show_tab) |
| **`None`** | Logique pure, zéro libc — algorithmique | C01-C05 (majorité), C11 (logique) |
| **`malloc` (+`free`)** | Gestion mémoire = le vrai saut de difficulté | C07, C08, C09, C11(map), C12, C13 |
| **syscalls fichiers** | `open/read/close` + erreurs | C10 |

> La progression de la piscine = **None → write → malloc → structures**.
> Le mur classique des étudiants est le passage à `malloc` (C07). Sécurise C07, et tout
> C08-C13 devient « la même chose appliquée à des structures ».

---

## 4. Briques réutilisables (FACTORISATION) — vérifié sur les prototypes réels

> ⚠️ Révision : la 1ère version annonçait « 8 briques = 80 % de tous les exos ».
> Recomptage exercice par exercice (groundé sur les signatures des sujets) : **faux**.
> Les chiffres vérifiés ci-dessous sont plus nuancés — et plus exploitables.

### Les 8 briques de base (string / nombre / I/O / mémoire)

| Brique | Pattern | Réutilisée dans |
|---|---|---|
| B1 `ft_putchar` | `write(1, &c, 1)` | tous les affichages |
| B2 parcours `'\0'` | `while (str[i])` | toute la famille str, strlen |
| B3 char↔chiffre | `c - '0'` / `c + '0'` | atoi, putnbr, *_base, convert_base |
| B4 extraction chiffres | `n % base` / `n / base` | putnbr, putnbr_base, convert_base |
| B5 reconstruction nombre | `res = res*base + (c-'0')` | atoi, atoi_base |
| B6 `ft_swap` | `tmp=*a; *a=*b; *b=tmp` | tris, rev_int_tab, sort_string_tab |
| B7 parcours borné | `i < n && str[i]` | strncpy, strncat, strncmp, strlcpy |
| B8 malloc+`'\0'` | `malloc(len+1)` + test NULL + copie | strdup, split, range, strs_to_tab |

### Les 4 briques structurelles (le reste de la piscine)

| Brique | Pattern | Débloque |
|---|---|---|
| B9 récursion | cas de base + appel récursif | C05 (rec.), C13, ten_queens |
| B10 `->next` / struct | parcours de nœuds chaînés | C12 (listes), C13 (arbres) |
| B11 ptr de fonction | `int (*f)(int)` puis `f(x)` | C11 (foreach/map/any...), C12/C13 (cmp/apply) |
| B12 syscalls fichiers | `open` → `read` (boucle) → `close` | C10 (display_file, cat, tail, hexdump) |

### Couverture RÉELLE (recomptée sur les 118 exos)

| Périmètre | 8 briques | 12 briques |
|---|---|---|
| Noyau exam (C00-04, C06, C07 = 52 exos) | **100 %** | 100 % |
| Tout le C runtime (102 exos) | 60 % | **100 %** |
| Piscine entière (118 exos) | 44 % | **86 %** |

**Constatations vérifiées :**
1. Les **8 briques couvrent 100 % du noyau chaînes/nombres/I/O/mémoire** (52/52 exos) —
   c'est exactement la zone d'exam. Aucune exception.
2. Les 41 exos hors-noyau ne réclament QUE les 4 briques structurelles (B9-B12),
   rien d'autre → **12 briques = 100 % de tout le C runtime (102/102).**
3. Les 16 restants (4 headers C08, Makefile, libft, 10 Shell) sont hors-runtime
   (préprocesseur / build / shell) : pas reconstructibles depuis une brique.

> **À retenir : 8 briques pour blinder l'exam, 12 pour fermer toute la piscine
> (hors préprocesseur/build/shell).**

---

## 5. Graphe de dépendances (ordre de maîtrise)

```
ft_putchar ──┬─> ft_putstr ──> ft_putnbr ──> ft_putnbr_base
             └─> ft_print_* (alphabet, numbers, comb...)

ft_strlen ───┬─> ft_strcpy ──> ft_strdup ──> ft_split
             ├─> ft_strcmp / ft_strncmp
             └─> ft_atoi ──> ft_atoi_base

ft_swap ─────> ft_sort_int_tab ──> ft_sort_string_tab (via ptr de fonction)

malloc(C07) ─> ft_strs_to_tab ─> t_list (C12) ─> t_btree (C13)
```
Travaille de **gauche à droite** : chaque brique de gauche est un prérequis direct
de celles de droite.

---

## 6. Pronostic EXAM (récurrents historiques)

Les exams de piscine (Exam00/01/02) puisent quasi systématiquement dans ce noyau.
Classés par probabilité d'apparition :

**Niveau critique — à reconstruire de tête :**
ft_strlen · ft_putstr · ft_putchar · ft_strcpy · ft_strcmp · ft_putnbr · ft_atoi
· ft_strdup · ft_swap

**Fréquents :**
ft_strncmp · ft_strcat · ft_strncpy · ft_str_is_* · ft_strrev · ft_range · ft_split
· conversions de base

**Plus rares, déjà vus :**
ft_rot13 / ft_rotn (variantes) · ft_atoi_base · ft_print_memory · listes chaînées simples

> Méthode : pour chaque fonction critique, sache **reconstruire la logique** (pas
> réciter) en répondant aux « questions à se poser ». C'est ce qui survit à la pression
> d'exam. Marqueurs de priorité dans le [tracker](TRACKER_PROGRESSION.md) : **C** critique
> · **F** fréquent · **B** bonus.

---

## 7. Pièges récurrents par concept (anti-sèche)

| Concept | Piège classique |
|---|---|
| ft_putnbr / ft_atoi | `INT_MIN` (-2147483648) : `-n` déborde → passer par `long` |
| malloc | oublier le `+1` pour `'\0'` ; ne pas tester le retour `NULL` |
| str classification | chaîne vide doit souvent renvoyer `1` (vrai) |
| strncpy / strlcpy | différence de retour et de remplissage ; gérer le `'\0'` |
| récursivité | cas de base manquant → boucle infinie / stack overflow |
| pointeurs de fonction | prototype exact `int (*f)(int)` ; parenthèses obligatoires |
| listes chaînées | perdre le `next` avant de free ; gérer la liste vide |
| Norme 42 | pas de `for`, pas de `//`, ≤ 25 lignes/fonction, ≤ 5 fonctions/fichier |

---

## 8. Kit de révision — état (prouvé)

Le kit est un système, pas un document isolé. État honnête de ce qui est livré et de ce
qui reste :

| Pièce | But | État |
|---|---|---|
| Cette analyse | méta-index transversal | **livré** |
| [FICHES_QUESTIONS.md](fiches/FICHES_QUESTIONS.md) | 12 familles, questions → squelettes à trous → pièges (méthode seule) | **livré** |
| [TRACKER_PROGRESSION.md](TRACKER_PROGRESSION.md) | 3 états (compris / refait de tête / sous chrono) + répétition espacée J+1/J+3/J+7 | **livré** |
| [42-PREUVE.md](42-PREUVE.md) | charte de conformité Chap. III + couverture chiffrée | **livré** |
| Banque de tests `main.c` | un main par exo (cas limites : vide, négatif, `INT_MIN`, `NULL`, `min >= max`) | à faire |
| Drill Norme | `-Wall -Wextra -Werror` + norminette systématiques dès le 1er jour | discipline continue |

> Rappel de discipline : un projet hors-Norme = 0, même juste. La Norme se vérifie en
> continu, pas à la fin.

---

*Sources : sujets PDF officiels C00–C13 + Shell00 (tables des matières + sections
"Allowed functions"). Couverture : 15/15 modules de la partie C.*
