# Fiches « questions à se poser » — méthode de reconstruction

> **Le réel.** En exam (Exam00/01/02), pas d'IA, pas d'internet. Ce qui survit à la
> pression, ce n'est pas le code récité — c'est la **logique reconstruite**.
>
> **La promesse.** Ce document ne donne pas de solutions. Il donne les **questions** qui
> régénèrent le code, dans l'ordre, pour chaque famille de fonctions. Tu te poses les
> questions, tu écris, tu compares.
>
> **La méthode (assumée « 42-proof »).** Aucune fonction n'est livrée complète — seulement
> des **squelettes à trous** : la structure et la ligne-clé sont annotées, les décisions
> restent à reconstruire. C'est ce qui rend ce kit partageable en piscine sans
> court-circuiter le Chapitre III du sujet ni la Moulinette : il apprend à **reconstruire,
> pas à copier**. Une solution copiée ne se défend pas en évaluation — une méthode, si.
> (Détail et preuve : voir [42-PREUVE.md](../42-PREUVE.md).)
>
> **Pour chaque fonction :** les questions → le raisonnement → un squelette à trous → le
> piège et son pourquoi. Cache le squelette, écris de tête, puis compare.
>
> Convention 42 : pas de `for`, pas de `//`, ≤ 25 lignes/fonction, variables déclarées en
> haut. Les squelettes respectent cette logique.

Sommaire :
- [Famille 1 — STR](#famille-1--str) *(C02/C03)*
- [Famille 2 — CONVERSION](#famille-2--conversion) *(C04)*
- [Famille 3 — MALLOC](#famille-3--malloc) *(C07)*
- [Famille 4 — AFFICHAGE & ASCII](#famille-4--affichage--ascii) *(C00)*
- [Famille 5 — POINTEURS & PASSAGE PAR ADRESSE](#famille-5--pointeurs--passage-par-adresse) *(C01)*
- [Famille 6 — TABLEAUX D'ENTIERS](#famille-6--tableaux-dentiers) *(C01)*
- [Famille 7 — RÉCURSIVITÉ & MATHS](#famille-7--récursivité--maths) *(C05)*
- [Famille 8 — ARGUMENTS PROGRAMME](#famille-8--arguments-programme) *(C06)*
- [Famille 9 — POINTEURS DE FONCTION](#famille-9--pointeurs-de-fonction) *(C11)*
- [Famille 10 — LISTES CHAÎNÉES](#famille-10--listes-chaînées) *(C12)*
- [Famille 11 — ARBRES BINAIRES](#famille-11--arbres-binaires) *(C13)*
- [Famille 12 — FICHIERS & SYSCALLS](#famille-12--fichiers--syscalls) *(C10)*
- [Appendice — PRÉPROCESSEUR / HEADERS](#appendice--préprocesseur--headers) *(C08)*

---

# FAMILLE 1 — STR

**Brique dominante : B2** (parcourir jusqu'au `'\0'`) **et B7** (parcours borné par `n`).

**Le réflexe de la famille :** *un seul `while`, le `'\0'` comme panneau « stop ».
Toutes ces fonctions sont la même boucle — seule l'action à l'intérieur change.*

## Les 4 questions universelles (à se poser pour TOUTE fonction `str`)

1. **Je lis ou je modifie ?**
   Lecture → je renvoie une *information* (`int` : longueur, résultat de comparaison…).
   Modification → je renvoie en général **`dest`** (le pointeur reçu), pour pouvoir chaîner.
2. **Jusqu'où je vais ?**
   Jusqu'au `'\0'` (**B2**, `while (str[i])`) ou borné par une taille `n` (**B7**,
   `while (i < n && str[i])`) ?
3. **Que fais-je à chaque caractère ?**
   Copier ? comparer ? classer (alpha/num) ? transformer (maj/min) ?
4. **Je renvoie quoi exactement ?**
   Un `int` ? un `char *` ? Lequel — `dest`, `src`, un index, une différence ?

## Le squelette commun

```c
type	ft_xxx(char *str ...)
{
	int	i;

	i = 0;
	while (str[i] /* Q2 : '\0' seul, ou (i < n && str[i]) */)
	{
		/* Q3 : action sur str[i] */
		i++;
	}
	return (/* Q4 */);
}
```

---

## Exemple intégralement déroulé — `ft_strlen` (le modèle à imiter)

**Prototype :** `int ft_strlen(char *str);`

**Q1 — lis/modifie ?** Je lis → je renverrai un `int`.
**Q2 — jusqu'où ?** Jusqu'au `'\0'` (B2).
**Q3 — action ?** Juste compter.
**Q4 — renvoie ?** Le compteur `i`.

**Trace mentale sur `"abc"`** (rappel : `"abc"` = `'a' 'b' 'c' '\0'`) :
```
i=0 : str[0]='a' ≠ '\0' → i=1
i=1 : str[1]='b' ≠ '\0' → i=2
i=2 : str[2]='c' ≠ '\0' → i=3
i=3 : str[3]='\0'       → STOP
return 3
```

**Squelette à trous :**
```c
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (/* Q2 : tant qu'on n'est PAS sur le '\0' */)
		i++;
	return (/* Q4 : le compteur */);
}
```

**Piège & pourquoi :** le `'\0'` n'est **pas** compté — c'est un marqueur de fin, pas
un caractère du mot. C'est voulu : `"abc"` mesure 3, pas 4.

> Voilà le moule. Toutes les fonctions ci-dessous se traitent **exactement** ainsi :
> 4 questions → trace → squelette → piège.

---

## Les fonctions de la famille

### `ft_strcpy` — `char *ft_strcpy(char *dest, char *src);`
- **Questions :** je modifie (`dest`) ; je vais jusqu'au `'\0'` de `src` **inclus** ;
  action = recopier ; je renvoie `dest`.
- **Ligne-clé :** `dest[i] = src[i];` puis, **après** la boucle, `dest[i] = '\0';`
- **Piège & pourquoi :** si tu t'arrêtes *avant* de copier le `'\0'`, `dest` n'est pas
  terminée → toute lecture future part en vrille. Le `'\0'` final est obligatoire.

### `ft_strncpy` — `char *ft_strncpy(char *dest, char *src, unsigned int n);`
- **Questions :** parcours **borné** par `n` (B7) ; action = copier *ou* compléter.
- **Comportement exact :** copie au plus `n` caractères ; **si `src` est plus courte
  que `n`, on remplit le reste de `dest` avec des `'\0'`**.
- **Piège & pourquoi :** le *padding* de zéros. `strncpy` ne garantit PAS un `'\0'` si
  `src` ≥ `n` (comportement standard) — c'est la différence majeure avec `strlcpy`.

### `ft_strcmp` — `int ft_strcmp(char *s1, char *s2);`
- **Questions :** je lis (un `int`) ; je m'arrête au 1er écart **ou** au `'\0'`.
- **Raisonnement :** j'avance tant que les caractères sont égaux ET non-nuls ; je
  renvoie la **différence** au point de divergence.
- **Ligne-clé :** `while (s1[i] && s1[i] == s2[i]) i++;` puis `return (s1[i] - s2[i]);`
- **Piège & pourquoi :** comparer aussi le `'\0'`. Si les deux chaînes sont égales, la
  boucle s'arrête sur le `'\0'` commun et `s1[i]-s2[i] = 0` → c'est exactement le bon
  résultat. Ne sors pas de la boucle « un cran trop tôt ».

### `ft_strncmp` — `int ft_strncmp(char *s1, char *s2, unsigned int n);`
- **Questions :** comme `strcmp` mais **borné par `n`** (B7).
- **Ligne-clé :** `while (i < n - 1 && s1[i] && s1[i] == s2[i]) i++;` → `return (s1[i]-s2[i]);`
- **Piège & pourquoi :** `i < n` testé **avant** `s1[i]` (sinon tu lis hors-borne).
  Et attention au comptage : on compare jusqu'à `n` caractères, pas `n-1`.

### `ft_strcat` — `char *ft_strcat(char *dest, char *src);`
- **Questions :** je modifie (`dest`) ; deux temps : (1) trouver la fin de `dest`,
  (2) y coller `src`.
- **Raisonnement :** d'abord avancer jusqu'au `'\0'` de `dest`, **puis** copier `src`
  à partir de là (`'\0'` inclus).
- **Piège & pourquoi :** le collage repart de l'index du `'\0'` de `dest`, pas de 0.
  Si tu repars de 0 tu écrases `dest`.

### `ft_strncat` — `char *ft_strncat(char *dest, char *src, unsigned int nb);`
- **Questions :** comme `strcat`, mais on colle **au plus `nb`** caractères de `src`.
- **Piège & pourquoi :** après avoir collé ≤ `nb` caractères, **re-terminer** par
  `'\0'` à la main (les `nb` chars n'incluent pas forcément le `'\0'` de `src`).

### `ft_strstr` — `char *ft_strstr(char *str, char *to_find);`
- **Questions :** je lis (renvoie un `char *`) ; double parcours (chaque position de
  `str` × chaque caractère de `to_find`).
- **Raisonnement :** pour chaque position `i` de `str`, vérifier si `to_find` matche
  à partir de là ; si oui renvoyer `&str[i]`.
- **Piège & pourquoi :** **`to_find` vide → renvoyer `str`** (cas limite imposé). Et
  renvoyer un **pointeur** sur la position trouvée, pas un index.

### `ft_str_is_alpha / numeric / lowercase / uppercase / printable` — `int ...(char *str);`
- **Questions :** je lis (renvoie 0 ou 1) ; parcours jusqu'au `'\0'` ; action = tester
  la classe du caractère.
- **Raisonnement :** dès qu'**un** caractère sort de la classe → `return 0`. Si on
  atteint le `'\0'` sans échec → `return 1`.
- **Piège & pourquoi :** la **chaîne vide doit renvoyer 1** (vrai). C'est contre-
  intuitif mais c'est la convention : « aucun caractère ne viole la règle ».
- **Bornes ASCII utiles :** `'a'..'z'`, `'A'..'Z'`, `'0'..'9'`, imprimable = `32..126`.

### `ft_strupcase` / `ft_strlowcase` — `char *...(char *str);`
- **Questions :** je modifie (`str` en place) ; parcours `'\0'` ; action = décaler.
- **Ligne-clé :** si `str[i]` ∈ `'a'..'z'` alors `str[i] -= 32;` (et l'inverse `+= 32`).
- **Piège & pourquoi :** `'a' - 'A' == 32`. Ne décale **que** si le caractère est
  effectivement dans la bonne plage, sinon tu corromps chiffres/symboles.

### `ft_strcapitalize` — `char *ft_strcapitalize(char *str);`
- **Questions :** je modifie ; parcours `'\0'` ; action = majuscule en **début de mot**,
  minuscule ailleurs.
- **Raisonnement :** un caractère est « début de mot » s'il est précédé d'un
  **séparateur** (non alphanumérique : espace, ponctuation…) ou s'il est le 1er.
- **Piège & pourquoi :** gérer le tout 1er caractère (pas de précédent) et bien
  remettre en minuscule les lettres qui ne sont pas en début de mot.

### `ft_strlcpy` / `ft_strlcat` — versions « sécurisées » (renvoient une taille)
- **`strlcpy(dst, src, size)` :** copie au plus `size-1` caractères, **termine
  toujours** par `'\0'` (si `size > 0`), et **renvoie `ft_strlen(src)`**.
- **`strlcat(dst, src, size)` :** renvoie `longueur_initiale_dst (plafonnée à size) +
  strlen(src)`.
- **Piège & pourquoi :** la valeur de retour est la **longueur qu'on aurait voulu
  écrire**, pas le nombre réellement écrit → c'est ce qui permet de détecter une
  troncature. Différence-clé avec `strncpy`.

## Récap pièges — famille STR
| Piège | Pourquoi |
|---|---|
| `'\0'` non copié (strcpy/cat) | chaîne non terminée → lectures suivantes corrompues |
| sortir un cran trop tôt (strcmp) | rate le cas « égales » qui se résout sur le `'\0'` |
| `i < n` testé après `str[i]` | lecture hors-borne (B7 : borne d'abord) |
| chaîne vide → 0 (str_is_*) | non : convention = **1** |
| décaler hors plage (upcase) | corrompt chiffres et symboles |
| `to_find` vide oublié (strstr) | doit renvoyer `str` |

---

# FAMILLE 2 — CONVERSION

**Briques dominantes : B3** (`c ± '0'`), **B4** (`% base`, `/ base`), **B5** (`res = res*base + chiffre`).

**Le réflexe de la famille :** *extraire = `%` et `/` ; reconstruire = `× base + chiffre`.
La base 10 n'est qu'un cas particulier de la base N.*

## Les 4 questions universelles

1. **Quel sens ?**
   Nombre → texte : j'**extrais** les chiffres (`%`/`/`) et j'**affiche**.
   Texte → nombre : j'**accumule** (`res = res*base + chiffre`).
2. **Base 10 ou base quelconque ?**
   En base N, le « 10 » devient `ft_strlen(base)`, et le caractère d'un chiffre devient
   `base[chiffre]` (au lieu de `chiffre + '0'`).
3. **Y a-t-il des négatifs ?**
   Si oui → **piège `INT_MIN`** (`-2147483648`) : `-n` déborde en `int` → passer par `long`.
4. **La base est-elle valide ?** (pour les fonctions `_base`)
   Longueur ≥ 2 ? aucun caractère en double ? pas de `+`, `-`, ni espace ?

## Les deux moteurs (miroirs l'un de l'autre)

```c
/* SENS 1 — nombre -> texte (putnbr) : extraire */
n % base   /* dernier chiffre        (735 % 10 = 5) */
n / base   /* enlève le dernier      (735 / 10 = 73) */
/* -> récursion sur (n / base), PUIS afficher le chiffre courant */

/* SENS 2 — texte -> nombre (atoi) : accumuler */
res = res * base + valeur_du_caractere   /* "42" : 0*10+4=4, 4*10+2=42 */
```

---

## Exemple intégralement déroulé — `ft_putnbr` (le modèle)

**Prototype :** `void ft_putnbr(int n);`

**Q1 — sens ?** nombre → texte : extraire puis afficher.
**Q2 — base ?** 10.
**Q3 — négatif ?** oui → `long` obligatoire (sinon `INT_MIN` casse).
**Q4 — caractère ?** `chiffre + '0'`.

**Le problème de l'ordre :** `% 10` donne les chiffres **à l'envers** (5, 3, 7 pour 735).
Pour afficher 7-3-5, il faut traiter la gauche **avant** d'afficher son propre chiffre →
c'est exactement ce que fait la récursion.

**Squelette à trous :**
```c
void	ft_putnbr(int n)
{
	long	nb;

	nb = n;                 /* long : pour survivre à INT_MIN */
	if (nb < 0)
	{
		/* afficher le '-' ... puis rendre nb positif (sûr en long) */
	}
	if (/* reste-t-il des chiffres à gauche ? */)
		ft_putnbr(/* se rapprocher : quel argument ? */);
	/* afficher le chiffre courant : nb % 10 -> caractère */
}
```

**Piège & pourquoi :** `INT_MIN = -2147483648`, mais `INT_MAX = 2147483647`. Donc
`-INT_MIN` n'existe pas en `int` → `nb = -nb` déborde. Le `long` (plus grand) encaisse
`2147483648` sans broncher. C'est LE piège classique des conversions.

---

## Les fonctions de la famille

### `ft_atoi` — `int ft_atoi(char *str);`
- **Questions :** sens texte→nombre (accumuler) ; base 10 ; gérer signe.
- **L'ordre est sacré :** (1) sauter les espaces blancs → (2) lire le(s) signe(s) →
  (3) accumuler les chiffres → s'arrêter au 1er non-chiffre.
- **Pseudocode (à traduire toi-même en C) :**
  1. avancer tant que le caractère est un blanc (`' '` ou code 9 à 13) ;
  2. avancer sur les signes : **chaque `'-'` inverse le signe** (une boucle, pas un `if`) ;
  3. tant que c'est un chiffre : `res = res * 10 + (chiffre)` — la brique B5.
- **Pièges & pourquoi :**
  - **signes multiples** : `"--42"` → `+42` → d'où `sign = -sign` (et un `while`, pas un `if`).
  - chaque étape se fait **une seule fois et dans l'ordre** : un espace *après* le signe
    (`"- 42"`) ne doit plus être sauté → renvoie 0.

### `ft_putnbr_base` — `void ft_putnbr_base(int nbr, char *base);`
- **Questions :** comme `ft_putnbr`, mais « 10 » → `ft_strlen(base)`, et le chiffre →
  `base[nb % len]` au lieu de `+ '0'`.
- **Raisonnement :** récursion identique ; seul change le « combien de symboles ».
- **Pièges & pourquoi :** valider la base **avant** (cf. plus bas) ; `INT_MIN` toujours
  via `long` ; afficher le `-` une seule fois (uniquement en base où ça a un sens).

### `ft_atoi_base` — `int ft_atoi_base(char *str, char *base);`
- **Questions :** comme `ft_atoi`, mais la valeur d'un caractère = son **index dans
  `base`** (et non `c - '0'`).
- **Raisonnement :** pour chaque caractère, chercher sa position dans `base` ; tant
  qu'on en trouve une, `res = res * len + index`.
- **Pièges & pourquoi :** **base invalide → renvoyer 0** sans rien lire ; gérer les
  espaces/signes en tête comme `atoi`.

### `ft_convert_base` — `char *ft_convert_base(char *nbr, char *base_from, char *base_to);`
- **La vraie question :** « ce n'est pas simplement `atoi_base(nbr, base_from)` **puis**
  `putnbr_base(résultat, base_to)` ? » → **si**, c'est une composition des deux moteurs.
- **Piège & pourquoi :** ici on **renvoie une chaîne** (allocation) → ça touche aussi la
  famille MALLOC (B8). Penser à la taille + `'\0'`.

## Valider une base (commun à `*_base`)
Trois tests, sinon base invalide :
1. **longueur ≥ 2** (une base d'un seul symbole n'a pas de sens) ;
2. **aucun caractère en double** (double boucle de comparaison) ;
3. **aucun `+`, `-` ni espace** (ils servent au signe / au parsing).

## Récap pièges — famille CONVERSION
| Piège | Pourquoi |
|---|---|
| `INT_MIN` avec `-n` en `int` | dépassement : `-INT_MIN` n'existe pas → utiliser `long` |
| `if` au lieu de `while` sur le signe (atoi) | rate les signes multiples `--` → `+` |
| sauter les espaces après le signe | l'ordre est figé : espaces → signe → chiffres |
| base non validée | doublon/signe dans la base fausse tout le calcul |
| oublier `'\0'`/alloc (convert_base) | la sortie est une chaîne allouée, pas un affichage |

---

# FAMILLE 3 — MALLOC

**Brique dominante : B8** (`malloc(taille + 1)` + test `NULL` + remplissage + terminaison).

**Le réflexe de la famille :** *compter d'abord, allouer ensuite (`+1`), tester `NULL`,
terminer.* C'est le vrai saut de difficulté de la piscine (module C07) — sécurise-le et
tout C08→C13 devient « la même chose appliquée à des structures ».

## Les 5 questions universelles (l'ordre est vital)

1. **Combien d'éléments dois-je stocker ?**
   → souvent un **premier parcours** juste pour compter (longueur, nombre de mots…).
2. **`malloc` de quoi, et combien ?**
   → `malloc(sizeof(type) * (nombre))`, **`+ 1`** si c'est une chaîne (pour le `'\0'`)
   ou un tableau de pointeurs (pour le `NULL` final).
3. **Le retour est-il `NULL` ?**
   → **toujours** tester. `malloc` peut échouer ; ne pas tester = segfault garanti à la défense.
4. **Qui termine la structure ?**
   → `'\0'` pour une chaîne ; **pointeur `NULL`** comme dernière case d'un tableau de `char *`.
5. **Et en cas d'échec partiel ?**
   → si une allocation interne (un mot dans `split`) rate, faut-il `free` ce qui précède
   pour ne pas fuir ?

## Le squelette commun

```c
char	*ft_xxx(char *src ...)
{
	char	*dst;
	int		i;

	/* Q1 : calculer la taille (ex : un ft_strlen) */
	dst = malloc(sizeof(char) * (taille + 1));   /* Q2 : +1 */
	if (!dst)                                     /* Q3 : NULL */
		return (NULL);
	i = 0;
	while (...)              /* remplir */
		i++;
	dst[taille] = '\0';      /* Q4 : terminer */
	return (dst);
}
```

---

## Exemple intégralement déroulé — `ft_strdup` (le modèle)

**Prototype :** `char *ft_strdup(char *src);`

**Q1 — combien ?** `ft_strlen(src)` caractères.
**Q2 — malloc de quoi ?** `malloc(sizeof(char) * (len + 1))` — le `+1` pour le `'\0'`.
**Q3 — NULL ?** oui, tester.
**Q4 — qui termine ?** un `'\0'` final.

**Squelette à trous :**
```c
char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(src);
	dst = malloc(/* Q2 : combien d'octets ? n'oublie pas le +1 */);
	if (/* Q3 : échec d'allocation ? */)
		return (NULL);
	i = 0;
	while (/* parcourir src */)
	{
		/* recopier le caractère courant */
		i++;
	}
	/* Q4 : terminer dst */
	return (dst);
}
```

**Piège & pourquoi :** le `+ 1`. Si tu allous juste `len`, il n'y a pas de place pour le
`'\0'` → écriture hors-bloc + chaîne non terminée. C'est l'erreur n°1 sur malloc.

---

## Les fonctions de la famille

### `ft_range` — `int *ft_range(int min, int max);`
- **Questions :** combien d'entiers ? → `max - min`. malloc de `int`. Remplir `min, min+1, …`.
- **Piège & pourquoi :** **cas limite `min >= max`** → renvoyer `NULL` (ou tableau vide
  selon l'énoncé) ; ne pas faire `malloc` d'une taille nulle/négative.

### `ft_ultimate_range` — `int ft_ultimate_range(int **range, int min, int max);`
- **Questions :** comme `ft_range`, mais on **remplit via `int **`** et on **renvoie la
  taille** (un `int`).
- **Piège & pourquoi :** bien déréférencer (`*range = malloc(...)`) ; renvoyer la taille
  (souvent `0` si `min >= max`, `-1` si malloc échoue — vérifier l'énoncé).

### `ft_split` — `char **ft_split(char *str, char *charset);` (le plus dur de C07)
Décomposé en 4 temps — chacun réutilise B2 + B8 :
1. **Compter les mots** : un mot = suite de caractères qui ne sont PAS dans `charset`.
   → donne `nb_mots`.
2. **Allouer le tableau** : `malloc((nb_mots + 1) * sizeof(char *))` — le `+1` pour le
   `NULL` final.
3. **Pour chaque mot** : mesurer sa longueur → `malloc(len + 1)` → copier → `'\0'`.
4. **Terminer** : `tab[nb_mots] = NULL;`
- **Pièges & pourquoi :**
  - un séparateur peut être **n'importe quel caractère de `charset`**, pas juste l'espace.
  - le `NULL` final permet à l'appelant de parcourir sans connaître `nb_mots`.
  - séparateurs consécutifs / en début / en fin → ne pas créer de mots vides.

### `ft_strs_to_tab` — tableau de **structures**
- **Questions :** pour chaque chaîne, je remplis une `struct` `{ size; str; copy }` →
  `size = strlen`, `str` = la chaîne d'origine, `copy` = un `strdup`.
- **Piège & pourquoi :** allouer **et** le tableau de structs **et** la `copy` de chaque
  chaîne ; terminer le tableau par une struct « vide » (selon l'énoncé).

## Récap pièges — famille MALLOC
| Piège | Pourquoi |
|---|---|
| oublier le `+ 1` | pas de place pour `'\0'`/`NULL` → écriture hors-bloc |
| ne pas tester `malloc` | retour `NULL` non géré → segfault |
| pas de `NULL` final (split) | l'appelant ne sait plus où s'arrête le tableau |
| compter après avoir alloué | il faut connaître la taille **avant** le malloc |
| fuite sur échec partiel | un malloc interne rate → free le déjà-alloué |

---

# FAMILLE 4 — AFFICHAGE & ASCII

**Briques dominantes : B1** (`write(1,&c,1)`), **B3** (`chiffre + '0'`), + boucles imbriquées (colle).

**Le réflexe de la famille :** *tout affichage = un `write` d'un caractère à la fois ;
un chiffre se montre via `+ '0'` ; une « combinaison » = des boucles imbriquées
strictement croissantes.*

## Les 4 questions universelles
1. **Qu'est-ce que j'affiche exactement ?** un caractère brut, une lettre, un chiffre ?
2. **Comment transformer un nombre en caractère ?** → `n + '0'` (B3).
3. **Y a-t-il une contrainte d'ordre/combinaison ?** (souvent : chiffres strictement croissants).
4. **Où placent les séparateurs ?** (virgule/espace partout **sauf après le dernier**).

---

## Exemple déroulé — `ft_print_comb` (le morceau qui pique)

**But :** afficher toutes les combinaisons de **3 chiffres différents, en ordre croissant** :
`012, 013, ... , 789`.

**Q1 — j'affiche ?** trois chiffres.
**Q3 — contrainte ?** strictement croissant → `i < j < k`.
**Q4 — séparateur ?** `", "` partout **sauf après `789`**.

**Raisonnement :** trois boucles imbriquées où chaque niveau démarre **après** le
précédent (`j` commence à `i+1`, `k` à `j+1`) garantit l'ordre croissant sans doublon.

```c
i = 0;
while (i <= 7)
{
	j = i + 1;
	while (j <= 8)
	{
		k = j + 1;
		while (k <= 9)
		{
			/* afficher i, j, k (chacun via chiffre + '0') */
			if (/* sauf le dernier triplet 7,8,9 */)
				write(1, ", ", 2);
			k++;
		}
		j++;
	}
	i++;
}
```

**Piège & pourquoi :** la virgule s'affiche **après chaque combinaison sauf la dernière**
(`789`). Si tu la mets systématiquement, tu finis par `789, ` → faux. D'où le test du
dernier triplet.

---

## Les fonctions de la famille
| Fonction | Question-clé | Piège |
|---|---|---|
| `ft_putchar(char c)` | « comment sortir 1 octet ? » → `write(1,&c,1)` | la brique de base |
| `ft_print_alphabet` | « de `'a'` à `'z'` ? » → boucle `c='a'; c<='z'` | afficher le char, pas son code |
| `ft_print_reverse_alphabet` | « de `'z'` à `'a'` » | décrémenter |
| `ft_print_numbers` | « de `'0'` à `'9'` » | ce sont des **caractères** |
| `ft_is_negative(int n)` | « signe → `'N'` ou `'P'` » | `0` compte comme positif |
| `ft_print_comb` | 3 chiffres croissants `i<j<k` | virgule sauf après `789` |
| `ft_print_comb2` | 2 nombres à 2 chiffres, 1er < 2e | padding 2 chiffres + séparateur |
| `ft_print_combn(int n)` | `n` chiffres croissants (généralisation) | gérer `n` variable (tableau d'indices) |

## Récap pièges — famille AFFICHAGE
| Piège | Pourquoi |
|---|---|
| afficher le code au lieu du caractère | il faut `+ '0'` pour un chiffre |
| séparateur après le dernier élément | sortie mal formée (`789, `) |
| boucles imbriquées qui repartent de 0 | crée des doublons / ordre non croissant |

---

# FAMILLE 5 — POINTEURS & PASSAGE PAR ADRESSE

**Brique dominante : B6** (swap) + déréférencement (colle).

**Le réflexe de la famille :** *pour modifier une variable du `main` appelant, je reçois
son **adresse** et j'écris à travers (`*ptr = ...`). Le pointeur dit « où », l'étoile dit
« la valeur là-bas ».*

## Les 3 questions universelles
1. **La fonction doit-elle modifier une variable de l'appelant ?** → si oui, elle reçoit
   un **pointeur** (`int *`), pas une copie.
2. **Combien de niveaux d'indirection ?** `int *` = adresse d'un `int` ; `int **` =
   adresse d'un pointeur ; etc.
3. **Je lis (`*p`) ou j'écris (`*p = ...`) ?**

---

## Exemple déroulé — `ft_swap` (le modèle)

**Prototype :** `void ft_swap(int *a, int *b);`

**Q1 — modifie l'appelant ?** oui → reçoit deux adresses.
**Q3 — lire et écrire ?** les deux.

```c
void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;    /* sauvegarder AVANT d'écraser — c'est tout le piège */
	/* écrire la valeur pointée par b dans *a, puis tmp dans *b */
}
```

**Piège & pourquoi :** sans `tmp`, `*a = *b` **écrase** la valeur de `*a` avant qu'on
ait pu la donner à `*b` → les deux finissent égaux. Le `tmp` sauvegarde avant l'écrasement.

---

## Les fonctions de la famille
| Fonction | Question-clé | Piège |
|---|---|---|
| `ft_ft(int *nbr)` | « écrire 42 dans la case pointée » → `*nbr = 42;` | comprendre `*` = la valeur |
| `ft_ultimate_ft(int *********nbr)` | « 9 étoiles → 9 déréférencements » → `*********nbr = 42;` | compter les niveaux |
| `ft_swap(int *a, int *b)` | swap via `tmp` | écraser avant de sauvegarder |
| `ft_div_mod(int a, int b, int *div, int *mod)` | « deux sorties → deux pointeurs » → `*div=a/b; *mod=a%b;` | sortie multiple par pointeur |
| `ft_ultimate_div_mod(int *a, int *b)` | « modifier `a` et `b` en place » | **sauver** `*a` avant de l'écraser |

## Récap pièges — famille POINTEURS
| Piège | Pourquoi |
|---|---|
| confondre `p` et `*p` | `p` = adresse, `*p` = valeur |
| écraser avant d'utiliser (swap, div_mod) | besoin d'un `tmp` |
| oublier le `*` à l'écriture | tu modifies l'adresse locale, pas la valeur de l'appelant |

---

# FAMILLE 6 — TABLEAUX D'ENTIERS

**Brique dominante : B6** (swap) + indexation (colle).

**Le réflexe de la famille :** *un tableau = une base + un index. Sa fin est connue par
sa **taille** (`size`), PAS par un `'\0'` (ça, c'est pour les chaînes).*

## Les 3 questions universelles
1. **Comment je connais la fin ?** → par `size`. (Ne cherche pas de terminateur sur des `int`.)
2. **J'échange ou je compare des cases ?** → souvent B6 (swap).
3. **Un double parcours est-il nécessaire ?** (tri = comparer des paires en boucle).

## Les fonctions de la famille

### `ft_rev_int_tab(int *tab, int size)`
- **Questions :** inverser en place ; deux index aux extrémités qui convergent.
- **Ligne-clé :** `i = 0; j = size - 1; while (i < j) { swap(&tab[i],&tab[j]); i++; j--; }`
- **Piège & pourquoi :** s'arrêter quand `i >= j` (au milieu) ; sinon tu ré-inverses tout.

### `ft_sort_int_tab(int *tab, int size)`
- **Questions :** trier croissant ; comparer les cases adjacentes, échanger si désordre.
- **Raisonnement (tri à bulles) :** double boucle ; tant qu'on a fait au moins un échange,
  on recommence.
- **Piège & pourquoi :** la borne `size - 1` quand tu compares `tab[i]` et `tab[i + 1]`
  (sinon lecture hors-tableau).

## Récap pièges — famille TABLEAUX
| Piège | Pourquoi |
|---|---|
| chercher un `'\0'` | les `int` n'ont pas de terminateur → utiliser `size` |
| comparer `tab[i+1]` jusqu'à `size` | hors-borne → boucler jusqu'à `size-1` |
| `rev` qui ne s'arrête pas au milieu | ré-inverse et annule le travail |

---

# FAMILLE 7 — RÉCURSIVITÉ & MATHS

**Brique dominante : B9** (récursion).

**Le réflexe de la famille :** *toute récursion = un **cas de base** (qui arrête) + un
**appel** qui se rapproche de ce cas de base. Pas de cas de base = boucle infinie /
stack overflow.*

## Les 3 questions universelles
1. **Quel est le CAS DE BASE ?** la plus petite entrée dont je connais la réponse directe.
2. **Comment je me RAPPROCHE du cas de base ?** (`n-1`, `n/10`, `power-1`…).
3. **Quelles entrées sont invalides ?** (négatif, overflow) → souvent `return 0`.

---

## Exemple déroulé — `ft_recursive_factorial` (le modèle)

**Prototype :** `int ft_recursive_factorial(int nb);`

**Q1 — cas de base ?** `nb <= 1` → `1` (car 0! = 1! = 1).
**Q2 — rapprochement ?** `nb * factorial(nb - 1)`.
**Q3 — invalide ?** `nb < 0` → `0`.

```c
int	ft_recursive_factorial(int nb)
{
	if (/* entrée invalide (négatif) ? */)
		return (0);
	if (/* CAS DE BASE : plus petite entrée à réponse directe */)
		return (1);
	return (/* se rapprocher du cas de base : nb * fact(?) */);
}
```

**Piège & pourquoi :** sans le `nb <= 1`, la récursion descend à l'infini (`-1, -2…`) →
crash. Le cas de base est ce qui **termine** la chaîne d'appels.

---

## Les fonctions de la famille
| Fonction | Cas de base / question-clé | Piège |
|---|---|---|
| `ft_iterative_factorial` | boucle `res *= i` de 2 à nb | nb<0 → 0 |
| `ft_recursive_factorial` | `nb<=1 → 1` | cas de base manquant |
| `ft_iterative_power` | boucle `res *= nb`, `power` fois | `power == 0 → 1` |
| `ft_recursive_power` | `power==0 → 1` ; `power<0 → 0` | exposant négatif |
| `ft_fibonacci(int index)` | `fib(0)=0, fib(1)=1` ; sinon `fib(n-1)+fib(n-2)` | `index < 0 → -1` |
| `ft_sqrt(int nb)` | monter `i` tant que `i*i < nb` ; renvoyer `i` si `i*i==nb` sinon 0 | overflow `i*i` (comparer prudemment) ; racine non entière → 0 |
| `ft_is_prime(int nb)` | `nb<=1 → 0` ; tester diviseurs `i*i <= nb` | borne `sqrt` pour l'efficacité ; 2 est premier |
| `ft_find_next_prime(int nb)` | incrémenter jusqu'à `is_prime` | réutilise `is_prime` |
| `ft_ten_queens_puzzle` | backtracking : 1 reine/colonne + vérif conflits + récursion | validation diagonale/ligne, défaire le coup (backtrack) |

## Récap pièges — famille RÉCURSIVITÉ
| Piège | Pourquoi |
|---|---|
| cas de base oublié | récursion infinie → stack overflow |
| négatifs non gérés | factorial/power/fibo attendent souvent `0`/`-1` |
| `i*i` qui déborde (sqrt/is_prime) | borner ou comparer sans calculer trop grand |

---

# FAMILLE 8 — ARGUMENTS PROGRAMME

**Briques : B1** (write), **B2** (parcours) + `argv` (colle).

**Le réflexe de la famille :** *`main(int argc, char **argv)`. `argv[0]` = le nom du
programme ; `argv[1]` à `argv[argc-1]` = les vrais arguments. `argv` est un tableau de
chaînes (terminé par `NULL`).*

## Les 3 questions universelles
1. **`argc` compte quoi ?** → le nombre total, **y compris** le nom du programme (`argv[0]`).
2. **Quels indices je parcours ?** `0` = nom ; `1..argc-1` = arguments.
3. **Trier/inverser ?** → ce sont des `char *` : tri = `ft_strcmp` + swap de **pointeurs**.

## Les fonctions de la famille
| Fonction | Question-clé | Piège |
|---|---|---|
| `ft_print_program_name` | afficher `argv[0]` + `'\n'` | c'est l'indice **0** |
| `ft_print_params` | afficher `argv[1..argc-1]`, un par ligne | commencer à **1** |
| `ft_rev_params` | afficher de `argv[argc-1]` à `argv[1]` | sens inverse, toujours s'arrêter à 1 |
| `ft_sort_params` | trier `argv[1..]` (ASCII) puis afficher | tri = swap de `char *` + `strcmp` |

## Récap pièges — famille ARGUMENTS
| Piège | Pourquoi |
|---|---|
| inclure `argv[0]` dans les "vrais" args | c'est le nom du programme |
| trier les chaînes elles-mêmes | on échange des **pointeurs**, pas le contenu |

---

# FAMILLE 9 — POINTEURS DE FONCTION

**Brique dominante : B11.**

**Le réflexe de la famille :** *une fonction passée en paramètre s'écrit
`type (*f)(args)`. On l'appelle `f(x)`. C'est « appliquer un comportement qu'on me
donne » sans le coder en dur — la généralisation des tris/parcours.*

## Les 3 questions universelles
1. **Quelle est la signature de la fonction reçue ?** `int(*f)(int)` ? `void(*f)(int)` ?
   `int(*cmp)(char*,char*)` ?
2. **J'applique** `f` à chaque élément (foreach/map) **ou je teste/accumule** (any/count_if) ?
3. **Je modifie en place** (foreach) **ou je renvoie un nouveau tableau** (map → B8 malloc) ?

---

## Exemple déroulé — `ft_foreach` (le modèle)

**Prototype :** `void ft_foreach(int *tab, int length, void (*f)(int));`

**Q1 — signature ?** `f` prend un `int`, ne renvoie rien.
**Q2 — appliquer ?** oui, à chaque case.

```c
void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < length)
	{
		/* appeler la fonction reçue sur l'élément courant : f(...) */
		i++;
	}
}
```

**Piège & pourquoi :** les parenthèses `(*f)` dans le prototype sont obligatoires :
`void *f(int)` (sans parenthèses) déclarerait une fonction renvoyant un pointeur, pas un
pointeur de fonction.

---

## Les fonctions de la famille
| Fonction | Question-clé | Piège |
|---|---|---|
| `ft_foreach` | appliquer `f` à chaque case | syntaxe `(*f)` |
| `ft_map` | renvoyer un **nouveau** tableau `f(tab[i])` | malloc(length) + tester NULL |
| `ft_any` | `1` si **au moins un** `f(elem) != 0` | parcourir un `char **` |
| `ft_count_if` | **compter** les `f(elem) != 0` | renvoie un compteur |
| `ft_is_sort` | trié selon `cmp(a,b)` ? | gérer croissant ET décroissant cohérents |
| `ft_sort_string_tab(char **tab)` | tri ASCII (strcmp interne) + swap pointeurs | pas de ptr de fonction ici |
| `ft_advanced_sort_string_tab(... cmp)` | idem mais `cmp` fourni | réutilise le tri, comparateur générique |
| `do-op` | calculatrice : `argv` + **table de fonctions** (add/sub/mul/div/mod) | division par zéro, parsing d'argv |

## Récap pièges — famille POINTEURS DE FONCTION
| Piège | Pourquoi |
|---|---|
| oublier les parenthèses `(*f)` | change complètement le type déclaré |
| `ft_map` sans malloc | il **renvoie** un nouveau tableau |
| `do-op` : division/modulo par zéro | crash → gérer le cas explicitement |

---

# FAMILLE 10 — LISTES CHAÎNÉES

**Briques : B10** (`->next`), **B8** (malloc des maillons), **B11** (cmp/apply), **B6** (reverse/sort).

**Le réflexe de la famille :** *une liste = des maillons reliés par `->next` ; le dernier
pointe sur `NULL`. Pour modifier la **tête**, on reçoit `t_list **` (un pointeur sur le
pointeur de tête).*

```c
typedef struct s_list {
	void           *data;
	struct s_list  *next;
}   t_list;
```

## Les 4 questions universelles
1. **Je modifie la tête** (push/clear/reverse) ? → `t_list **begin`.
   **Je lis seulement** (size/last/at) ? → `t_list *begin`.
2. **Comment je parcours ?** → `while (ptr) ptr = ptr->next;`
3. **J'alloue un maillon ?** → via `ft_create_elem` (malloc + `data` + `next = NULL`).
4. **Est-ce que je risque de perdre `->next`** avant de le réassigner / `free` ?

---

## Exemples déroulés — `ft_list_size` & `ft_list_push_front`

```c
/* LECTURE simple : t_list * suffit */
int	ft_list_size(t_list *begin_list)
{
	int	i;

	i = 0;
	while (/* tant qu'on n'est pas au bout (NULL) */)
	{
		i++;
		/* avancer au maillon suivant (->next) */
	}
	return (i);
}

/* MODIFICATION de la tête : t_list ** obligatoire */
void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*new;

	new = ft_create_elem(data);
	if (!new)
		return ;
	/* ORDRE : raccrocher `new` sur l'ancienne tête (*begin_list), */
	/* PUIS faire pointer la tête sur `new`. L'inverse perd la liste. */
}
```

**Piège & pourquoi :** l'ordre des 2 lignes du push. Si tu fais `*begin_list = new`
**avant** `new->next = *begin_list`, tu perds l'ancienne liste. On raccroche d'abord, on
déplace la tête ensuite.

---

## Les fonctions de la famille (par pattern)
| Fonction | Question-clé | Brique | Piège |
|---|---|---|---|
| `ft_create_elem` | malloc + `data` + `next=NULL` | B8 | tester NULL |
| `ft_list_push_front` | raccrocher puis déplacer la tête | B10 | ordre des 2 lignes |
| `ft_list_size` | compter en parcourant | B10 | liste vide → 0 |
| `ft_list_last` | avancer jusqu'à `->next == NULL` | B10 | liste vide |
| `ft_list_push_back` | aller au dernier puis accrocher | B10 | cas liste vide (`*begin=new`) |
| `ft_list_clear` | sauver `next`, `free_fct(data)`, `free(node)` | B10 B11 | sauvegarder `next` **avant** le free |
| `ft_list_at` | avancer `nbr` fois | B10 | dépassement → NULL |
| `ft_list_reverse` | ré-aiguiller via `prev/cur/next` | B10 | garder 3 pointeurs |
| `ft_list_foreach` | `f(ptr->data)` sur chacun | B11 | — |
| `ft_list_find` | 1er dont `cmp(data,ref)` matche | B11 | renvoyer le maillon |
| `ft_list_remove_if` | supprimer les maillons matchés | B10 B11 | recoller `->next`, free |
| `ft_list_sort` / `merge` / `sorted_insert` | combinaisons des précédents | B6 B11 | comparateur + ré-aiguillage |

## Récap pièges — famille LISTES
| Piège | Pourquoi |
|---|---|
| perdre `->next` avant réassignation | sauvegarder dans un `tmp` |
| `t_list *` au lieu de `t_list **` | impossible de modifier la tête depuis la fonction |
| ne pas gérer la liste vide (`NULL`) | parcours/accès qui segfault |
| free dans le mauvais ordre | free `data` puis le maillon, après avoir sauvé `next` |

---

# FAMILLE 11 — ARBRES BINAIRES

**Briques : B10** (`->left`/`->right`), **B9** (récursion), **B11** (applyf/cmpf).

**Le réflexe de la famille :** *un arbre = un nœud avec deux sous-arbres. Tout se fait
par **récursion** : gauche, le nœud, droite — l'**ordre** de ces trois définit
prefix/infix/suffix.*

```c
typedef struct s_btree {
	struct s_btree  *left;
	struct s_btree  *right;
	void            *item;
}   t_btree;
```

## Les 3 questions universelles
1. **Cas de base ?** → `if (!root) return ;` (arbre/sous-arbre vide).
2. **Dans quel ordre je visite ?**
   prefix = nœud → G → D · infix = G → nœud → D · suffix = G → D → nœud.
3. **Où va une nouvelle donnée (insert) ?** → comparer avec `cmpf`, descendre à gauche
   si « plus petit », à droite sinon.

---

## Exemple déroulé — `btree_apply_infix` (le modèle)

```c
void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (!root)              /* cas de base : sous-arbre vide */
		return ;
	/* INFIX = gauche -> nœud -> droite. Écris les 3 lignes DANS CET ORDRE : */
	/*   récursion à gauche ; applyf(root->item) ; récursion à droite        */
}
```

**Piège & pourquoi :** l'**ordre des 3 lignes** EST la définition. Déplace `applyf` avant
les deux récursions → c'est du prefix ; après les deux → du suffix. Sur un arbre binaire
de recherche, l'infix sort les éléments **triés**.

---

## Les fonctions de la famille
| Fonction | Question-clé | Piège |
|---|---|---|
| `btree_create_node(item)` | malloc + `item` + `left=right=NULL` | tester NULL |
| `btree_apply_prefix` | nœud → G → D | ordre des appels |
| `btree_apply_infix` | G → nœud → D | donne l'ordre trié (BST) |
| `btree_apply_suffix` | G → D → nœud | ordre des appels |
| `btree_insert_data(root, item, cmpf)` | `cmpf<=0` → gauche, sinon droite (récursif) | reçoit `t_btree **` ; créer si vide |
| `btree_search_item` | descendre selon `cmpf` | renvoyer l'item, pas le nœud |
| `btree_level_count` | `1 + max(left, right)` | arbre vide → 0 |
| `btree_apply_by_level` | parcours **par niveau** (largeur/BFS) | nécessite une file — le plus dur |

## Récap pièges — famille ARBRES
| Piège | Pourquoi |
|---|---|
| cas de base `!root` oublié | déréférencement de `NULL` → crash |
| mauvais ordre des 3 appels | change prefix/infix/suffix |
| insert sans `t_btree **` | impossible de créer la racine |

---

# FAMILLE 12 — FICHIERS & SYSCALLS

**Brique dominante : B12** (`open` / `read` / `close`).

**Le réflexe de la famille :** *lire un fichier = `open` → **boucle** `read` dans un
buffer → traiter/`write` → `close`. Toujours gérer les erreurs (fd < 0, read < 0).*

## Les 4 questions universelles
1. **D'où vient l'entrée ?** un fichier (`open`) ou l'entrée standard (fd `0`) ?
2. **Comment je lis ?** → `while ((ret = read(fd, buf, SIZE)) > 0) write(1, buf, ret);`
3. **Quelles erreurs ?** `fd == -1` (open échoue), mauvais nombre d'arguments, `read < 0`.
4. **Ai-je bien `close` à la fin ?**

---

## Exemple déroulé — boucle de lecture (cœur de `display_file`)

```c
int	fd;
int	ret;
char	buf[4096];

fd = open(argv[1], O_RDONLY);
if (/* échec d'ouverture ? */)
	/* message d'erreur sur fd 2, puis sortir */ ;
while ((ret = read(fd, buf, 4096)) > 0)
	write(1, buf, /* combien d'octets ? PAS la taille du buffer */);
close(fd);
```

**Piège & pourquoi :** `read` renvoie le **nombre d'octets réellement lus** (`ret`), qui
peut être < taille du buffer. Si tu fais `write(1, buf, 4096)` tu écris des octets
parasites. On écrit toujours `ret`, jamais la taille du buffer.

---

## Les fonctions de la famille
| Programme | Question-clé | Piège |
|---|---|---|
| `display_file` | 1 fichier en argument → l'afficher | gérer 0 / >1 args, fichier introuvable |
| `cat` | reproduire `cat` (plusieurs fichiers, ou stdin) | options `-e -t -n` (bonus), stdin si 0 arg |
| `tail` | afficher les `n` derniers octets (`-c`) | bufferiser / repositionner |
| `hexdump` | reproduire `hexdump -C` (offset + hex + ascii) | alignement des colonnes, derniers octets |

## Récap pièges — famille FICHIERS
| Piège | Pourquoi |
|---|---|
| `write(1, buf, SIZE)` au lieu de `ret` | écrit des octets non lus → sortie corrompue |
| ne pas tester `fd < 0` | fichier absent → comportement indéfini |
| oublier `close` | fuite de descripteurs |
| erreurs sur fd 1 | les messages d'erreur vont sur fd **2** (stderr) |

---

# APPENDICE — PRÉPROCESSEUR / HEADERS

Pas une brique « runtime », mais ça tombe en C08. Deux réflexes :

### Header guard (obligatoire dans tout `.h`)
```c
#ifndef FT_H
# define FT_H
/* prototypes / typedefs / macros */
#endif
```
**Pourquoi :** empêche la double inclusion du même header (erreurs de redéfinition).

### Macros — parenthèses partout
```c
# define ABS(x) /* ternaire : si (x) < 0 alors -(x), sinon (x) */
```
**Règle absolue :** parenthèse **chaque** occurrence de l'argument **et** toute
l'expression.
**Piège & pourquoi :** sans ces parenthèses, `ABS(a + b)` se développe en
`a + b < 0 ? ...` → priorité d'opérateurs cassée. C'est la seule difficulté de l'exo.

### Typedefs utiles
```c
typedef int t_bool;                              /* ft_boolean.h */
typedef struct s_point { int x; int y; } t_point;/* ft_point.h */
```

| Exo | À retenir |
|---|---|
| `ft.h` | header guard + tous les prototypes |
| `ft_boolean.h` | `#define TRUE/FALSE`, `t_bool`, macros `EVEN`/`ODD` |
| `ft_abs.h` | macro `ABS` **parenthésée** |
| `ft_point.h` | `typedef struct s_point` |

---

# Comment utiliser ces fiches (le drill)

1. **Cache le squelette.** Lis uniquement les **questions**.
2. Réponds-y **à voix haute**, puis écris la fonction **de tête**.
3. **Compile** : `cc -Wall -Wextra -Werror` + teste les cas limites
   (chaîne vide, négatif, `INT_MIN`, `NULL`, `min >= max`, séparateurs multiples).
4. Compare à ton squelette **seulement après** avoir écrit.
5. Reporte ton état dans [`TRACKER_PROGRESSION.md`](../TRACKER_PROGRESSION.md)
   (Compris → Refait de tête → Sous chrono) et planifie J+1 / J+3 / J+7.

> Tu sauras que c'est acquis quand tu peux **réciter les questions** sans regarder, et
> que le code tombe sans effort. C'est ça qui survit à la pression de l'exam.
