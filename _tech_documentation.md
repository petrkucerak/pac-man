# Technická dokumentace

## Architektura aplikace

Soubory programu jsou děleny dle funkčnosti. Podrobnjěí informace s popisem jednotlivých souborů, metod, funkcí, struktur, proměných a maker je možné dohledat v dokumentaci v sekci: [Files](files.html).

Aplikace je vytvořena pro MicroZed based MZ_APO board designed by Petr Porazil at [PiKRON](http://www.pikron.com/).

Aplikace vychází z šablony [mzapo_template](https://gitlab.fel.cvut.cz/b35apo/mzapo_template).

## Blokové schéma algoritmu

Blokové schéma popisuje fungování algoritmu hry Pac-Man.

![block-schema](https://raw.githubusercontent.com/petrkucerak/library/main/asstes/share/blok-schema.png)

Obecně si ho můžeme rozdělit do třech částí:

1. konfigurace dané hry (Main menu)
2. hra samotná (Game)
3. výpis skóre a pauza (Dispaly score, Pause)

## Popis kompilace a spuštění programu

Pro kompliaci programu je připravený Makefile i s předpřipraveným připojením přes *ProxyJump* do školní sítě a s možností se připojit rovnou na zařízení.

Makefile vychází z šablony [mzapo_template](https://gitlab.fel.cvut.cz/b35apo/mzapo_template).

### Nastavení Makefilu

Podrobné informace o způsobech připojení a detailního využití připraveného Makefilu je možné dohledat v dokumnetaci předmětu: https://cw.fel.cvut.cz/wiki/courses/b35apo/documentation/mz_apo-howto/start.

#### Flagy a podrobnosti kompilace

Program je kompilován gcc kompilátorem s následujícími flagy.

```Makefile
CC = arm-linux-gnueabihf-gcc
CXX = arm-linux-gnueabihf-g++

CPPFLAGS = -I .
CFLAGS =-g -std=gnu99 -O1 -Wall
CXXFLAGS = -g -std=gnu++11 -O1 -Wall
LDFLAGS = -lrt -lpthread -pthread
```

Ke kompilaci na Ubuntu/Debina systému je třeba mít naistalovaný křížový kompilátor.
```bash
sudo apt install crossbuild-essential-armhf
```

#### Zdrojové soubory

Pokud budete upravovat nějaký ze souborů nebo přidávat vlastní, je třeba mít přidané všechny soubory ke kompilaci.

```Makefile
SOURCES = apoman.c mzapo_phys.c mzapo_parlcd.c update_peripherals.c text_fb.c map_from_template.c map_to_fb.c draw_shapes.c
SOURCES += terminal_read.c pacman.c ghost.c
SOURCES += font_prop14x16.c font_rom8x16.c
SOURCES += map_circles.c map_conch.c map_star.c
SOURCES += menu_utilities.c
SOURCES += final_score.c
SOURCES += game.c
```

#### Cílový binární soubor

Název výsledného binárního souboru je definován tímto příkazem:
```Makefile
TARGET_EXE = apoman
```

#### Propojení se zařízením při kompilaci

Způsobů, jak pracovat se zařízením, je mnoho. My doporučujeme využít tzv. *ProxyJumpu*, který jsme během vývoje používali. Pojďme si představit jednotlivé doporučené přístupy.

Rád bych upozornil, že tato část je rychlým srhnutí poskytnuté dokumentace dostupné na stránkách předmětu (https://cw.fel.cvut.cz/wiki/courses/b35apo/documentation/mz_apo-howto/start).

##### 1. Propojení pomocí *ProxyJump*

Prvním způsobem je propojit se přes tzv. *ProxyJump*. Je vhodné rovnou do Makefilu vyplnit cílovou IP adresu zařízení
```Makefile
TARGET_IP ?= 192.168.202.xxx
```
 a vyplnit své uživatelské jméno s přístupem k ssh klíči (k školnímu serveru).
```Makefile
SSH_OPTIONS= -i ~/.ssh/mzapo-root-key -o 'ProxyJump=username@postel.felk.cvut.cz'
```
Předejte tak zbytečnému zablokování ze strany školního serveru při opakovaném a častém připojování. Přístup pro vás bude snazší.

##### 2. Využití SSH tunelu do lokální sítě laboratoře

Další možností připojení je využít trvalé SSH spojení na server `postel.felk.cvut.cz`. Tento způsob zaručí, že je menší riziko, aby naše připojení bylo vyhodnoceno ochranou serveru jako útok. Opětovaná připojování jsou tak tedy mnohem rychlejší.

Tunel vytvoříme příkazem
```bash
ssh -nNT ctu_login@postel.felk.cvut.cz -L 2222:192.168.202.xxx:22
```

A v Makefilu je třeba povolit řádku s následujícími příkazy:
```Makefile
TARGET_IP = 127.0.0.1
SSH_OPTIONS=-o "UserKnownHostsFile=/dev/null" -o "StrictHostKeyChecking=no" -o "Port=2222"
SSH_GDB_TUNNEL_REQUIRED=y
```

##### 3. Připojení se přes PC v laboratoři

Třetím možným způsobem je se připojit na školní PC, který je ve stejné síti jako používaný přípravek.

Zde stačí pouze zavolat příkaz, který nám kód zkompiluje a rovnou spustí na zařízení s danou IP adresou:
```bash
make TARGET_IP=192.168.202.xx run
```

### Důležité příkazy

Další částí Makefilu jsou příkazy, které lze při práci s aplikací využít. Pojďme si představit ty nejvíce elementární.

#### Kompilace

```bash
make
```

#### Vymazání objektových a zkompilovaných souborů

```bash
make clean
```

#### Kompilace a zároveň spuštění dle konfigurace Makefilu

```bash
make run
```