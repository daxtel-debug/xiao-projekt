# xiao-projekt
Code fore Seeed Xiao nRF52840 use on instalation with Android platform

# Seeed XIAO nRF52840 – 433 MHz DHT22 Sensor Transmitter (with TPL5110)

Trådlös temperatur- och luftfuktighetssändare byggd på **Seeed Studio XIAO nRF52840**, **DHT22**, en **433 MHz RF-sändare (RadioHead `RH_ASK`)** och en **TPL5110 nano-power timer** för extremt låg strömförbrukning.

*Wireless temperature and humidity transmitter built on **Seeed Studio XIAO nRF52840**, **DHT22**, a **433 MHz RF transmitter (RadioHead `RH_ASK`)**, and a **TPL5110 nano-power timer** for ultra-low battery consumption.*

---

## Funktioner / Features
* **RadioHead (`RH_ASK`) på nRF52840:** Inkluderar en anpassad hårdvarutimer-patch (`TIMER2`) i `lib/RadioHead/RH_ASK.cpp` så att standardprotokollet RadioHead (2000 bps) fungerar direkt på nRF52840.
* **Ultralåg strömförbrukning:** När mätningen av DHT22 är klar och paketet har skickats via 433 MHz sätts `DONE`-pinnen hög till **TPL5110**, som bryter strömmen helt tills nästa mätcykel.
* **Färdig `.uf2`-fil ingår:** Ladda ner `klar_kod.uf2` och dra direkt till kortet i bootloader-läge utan att behöva kompilera själv.

---

## Hårdvara & Koppling / Hardware & Wiring

> **Viktigt / Important:** Seeed XIAO nRF52840 använder **3.3V-logik**. Mata aldrig GPIO-stiften med 5V.

| Komponent / Component | Signal | Seeed XIAO nRF52840 | Kommentar / Notes |
| :--- | :--- | :--- | :--- |
| **DHT22** | VCC | `3V3` | Strömförsörjning (3.3V) |
| **DHT22** | GND | `GND` | Jord |
| **DHT22** | DATA | **`D2`** (Pin 2) | Använd 4.7k–10k pull-up motstånd till `3V3` |
| **433 MHz TX** | VCC | `3V3` | Strömförsörjning (3.3V) |
| **433 MHz TX** | GND | `GND` | Jord |
| **433 MHz TX** | DATA | **`D3`** (Pin 3) | Löd gärna en 17.3 cm tråd på `ANT` för bäst räckvidd |
| **TPL5110** | DRV | `3V3` (eller `VIN`) | Styr strömmen till XIAO-kortet |
| **TPL5110** | DONE | **`D4`** (Pin 4) | Bryter strömmen när sändningen är klar |
| **TPL5110** | GND | `GND` | Gemensam jord |

*(Dubbelkolla ordningen på `D2`, `D3` och `D4` i toppen av `src/main.cpp` så att de matchar din inkoppling).*

---

## Snabbinstallation (utan att kompilera) / Quick Flash (`.uf2`)

1. Ladda ner filen **`klar_kod.uf2`** från detta arkiv.
2. Koppla in ditt **Seeed XIAO nRF52840** via USB-C.
3. **Dubbelklicka snabbt** på den lilla **RST-knappen** bredvid USB-C-kontakten så att lysdioden börjar pulsera och kortet dyker upp som en USB-enhet (`XIAO-SENSE` / `XIAO-nRF52`).
4. Kopiera **`klar_kod.uf2`** direkt till USB-enheten. Kortet startar om automatiskt och kör koden.

---

## Kompilera själv med PlatformIO / Build from Source

Projektet är konfigurerat för **PlatformIO** (och fungerar även direkt i GitHub Codespaces):

1. Klona arkivet:
   ```bash
   git clone https://github.com
   cd xiao-projekt
   ```
2. Ändra eventuella pin-nummer i `src/main.cpp`.
3. Kompilera med PlatformIO:
   ```bash
   pio run
   ```
4. Konvertera `.hex` till `.uf2` vid behov:
   ```bash
   python3 ~/.platformio/packages/framework-arduinoadafruitnrf52/tools/uf2conv/uf2conv.py .pio/build/xiaoble/firmware.hex -c -f 0xADA52840 -o klar_kod.uf2
   ```
