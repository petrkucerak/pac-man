# Semestrální práce na APO

## Introdukce
Cílem této semstrální práce je vytvořit hru Pac-Man, kterou bude možné hrát na desce MzAPO a ovládat pomocí okolních periferií.

Průběh naší práce je možné sledovat v repozitáři: https://gitlab.fel.cvut.cz/kucerp28/apo\_semestralka

## Použité periferie a jejich funkce

- Výstupní řádka led bude při spuštěné hře indikovat počet životů pacmana
- RGB led budou svítit zeleně jasem vypočítaným z počtu snězených kostiček, v případě režimu, kdy jsou duchové zranitelní bude blikat modře.
- Vstupem hry bude terminál v raw režimu,  který bude ovládat směr pacmana, respektive navigaci v textovém menu.
- Po sklonční hry přípravek vypíše finální skóre a statistiky na terminál
## Stavy

### Inicializace hry

Po spuštění hry se objeví textové menu, které bude možné ovládat pomocí kláves wsad ze sériového portu. Bude zde možnost vybrat mapu z nabídky, nastavit počet duchů a počet životů, se kterými pacman začíná.

### Průběh hry

Samotná hra se bude ovládat pomocí znaků wsad, stejně jako textové menu. Pacman pobíhá po desce s cílem sníst co nejvíce "penízků" a zároveň se nenechat sežrat duchy. Pokud sní speciální peníz, spustí se na určitou dobu mód, v kterém bude moci požírat duchy, za což získá další body.

V průběhu hry je možno sledovat mód, ve kterém se hra nachází na tvaru duchů a stavu RGB LED. Počet zbývajících životů je indikován na výstupní led řádce jako počet shluků svítících led.

### Závěr hry

Hra může být ukončena 3 způsoby:
- Výhrou Pacmana. V takovém případě se vypíše skóre hry na terminál a otevře se menu nastavení
- Prohrou Pacmana. Ta vyvolá stejný proces jako výhra.
- Přerušením hry pomocí stisknutí klávesy q. To hráče odkáže do spouštěcího menu.