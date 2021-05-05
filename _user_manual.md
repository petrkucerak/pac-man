# Uživatelský manuál

## Natavení hry

V první části hry si je možnost nakongihurovat hru na míru. Je možné zvolit z následujcích parametrů.

- počet životů (možnost zvolit od 1 po 4)
- typ mapy (v tuto chvíli je na výběr ze 3 možností)
- počet duchů (možnost zvolit od 1 po 4)

### Herní mapy

#### Concentric_circles

Zcela první mapa, jenž je charakteristická dlouhými chodbami, kde se dá zažít divoká honička s duchem.

![Concentric_circles](https://raw.githubusercontent.com/petrkucerak/library/main/asstes/share/apo_man/game_04.png)

#### Star_map

Původně se mělo jednat o mapu připomínající tvar hvězdy, nakonec z této mapku ale vzniklo takové bludiště, kde je třeba počítat s každým zákrutem, protože tam může čekat nebezpečný duch.

![Star_map](https://raw.githubusercontent.com/petrkucerak/library/main/asstes/share/apo_man/game_02.png)

#### Connch_snail

Poslení mapka připomíná tvar ulity. Je v ní několik tajných chodem, která zdánlivě narušují její pravidelný tvar zlatého řezu.

![connch_snail](https://raw.githubusercontent.com/petrkucerak/library/main/asstes/share/apo_man/game_03.png)

## Průběh hry

### Ovládání hry

Hra se ovládá pomocí klávesnic `wasd`. Hru je možné pauznout pomocí stiknutí klávesy `p`.

### Popis hrací plochy

Na ploše je vidět několik typů předmětů:

- packman (pokud se pohybuje, máotevřenou pusu)
- duchové (mají různé barvy a pozor, občas jich může být více na sobě)
- normální coiny (barva červená)
- super coiny (barva fialová)

### Mód pojídání duchů

Pokud Pac-Man sní super coin, aktivuje se režim pojídání duchů. V něm může Pac-Man pojídat a oni mu neuberou život.

### Signály během hry

Stav hry je signalizován okolními periferiemi:

- výstupní řádka led indikuje počet životů pacmana
- RGB led svítí zeleně jasem vypočítaným z počtu snězených kostiček, v případě režimu, kdy jsou duchové zranitelní bliká modře


## Konec hry

Hra končí několika způsoby:

- spuštěním pauzy (talčítko `p`) a následného vypnutí hry
- ubráním všech Pac-Manových životů
- sežráním všech dostupných penízků

Po sklonční hry přípravek vypíše finální skóre a statistiky na terminál a uživatel má možnot buďto program celkově ukončit nebo spusti hru znovu.