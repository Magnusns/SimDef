# SimDef – Sanntidssystem for Trusseldeteksjon og Visualisering

**SimDef** er et egendefinert simuleringsprosjekt utviklet for å demonstrere ferdigheter innen objektorientert arkitektur, sanntidsdataflyt, trusselvurdering og interaktiv frontend-visualisering. Prosjektet er laget med tanke på stillinger innen forsvarsindustri og komplekse sanntidssystemer, som hos **Kongsberg Defence & Aerospace**.

---

## 🚀 Hva systemet gjør

- Simulerer objekter som beveger seg i 2D-rom
- Sender sanntidsdata til en WebSocket-server
- Vurderer hvert objekt som `normal`, `mistenkelig` eller `trussel`
- Logger trusler til fil
- Visualiserer objekter i sanntid med farge, retning og avstand til base

---

## 🧩 Systemarkitektur

```
+-------------------+        +----------------------+        +------------------+
| SensorSimulator   | --->   | Trusselvurdering     | --->   | WebSocket Server |
| (C++)             |        | (innebygget logikk)  |        | (C++)            |
+-------------------+        +----------------------+        +------------------+
                                                                |
                                                                v
                                                       +------------------+
                                                       | HTML/Canvas UI   |
                                                       | (JavaScript)     |
                                                       +------------------+
```

---

## 🔧 Teknologi og verktøy

| Komponent     | Teknologi                         |
| ------------- | --------------------------------- |
| Backend       | C++17, WebSocket++, nlohmann/json |
| Frontend      | HTML5, Canvas, JavaScript         |
| Visualisering | 2D Canvas med piler og fargekoder |
| Logging       | Tekstfil (trusler.log)            |

---

## 🔢 Trusselvurdering

Eksempler på kriterier:

- `mistenkelig`: Hastighet > 4.5 m/s
- `trussel`: Nær base **og** beveger seg **mot basen** (retning < 30° mot (0,0))
- Beregninger inkluderer vinkelanalyse og avstand

```cpp
if (dist < 30 && vinkelMotBase < 30 && hastighet > 4.0) {
    status = "trussel";
}
```

---

## 👁️ Frontend-funksjoner

- Viser objekter i sanntid
- Base tegnes i midten
- Piler viser retning
- Farger: Blå = normal, Oransje = mistenkelig, Rød = trussel
- Viser:
  - ID
  - Avstand til base
  - Vinkel mot base
- Logger nye trusler under kartet

---

## 📁 Katalogstruktur

```
SimDef/
├── backend/                  # C++ kildekode (SensorSimulator.cpp)
├── frontend/                 # HTML + JS (simdef-client.html)
├── data/                     # trusler.log med loggede hendelser
├── doc/                      # Screenshots og evt. video/gif
└── README.md
```

---

## 🔢 Kompilering og kjøring

### Backend (krever WebSocket++ og OpenSSL):

```bash
cd backend
g++ -std=c++11 SensorSimulator.cpp -o simulator -I/opt/homebrew/include -L/opt/homebrew/lib -lssl -lcrypto -lpthread
./simulator
```

### Frontend:

Åpne `frontend/simdef-client.html` i en nettleser (Chrome anbefales).

---

## 🌎 Demo og screenshots

**Kommer i ****`doc/`**:

- Terminal med sanntids-simulering
- Frontend med aktive objekter og trusler
- Eksempel på `trusler.log`

---

## 💼 Hva dette viser

Dette prosjektet viser at jeg kan:

- Bygge robuste og skalerbare sanntidssystemer i C++
- Modellere sikkerhetslogikk og trusselkriterier
- Lage sanntidsoverføring med WebSocket
- Visualisere komplekse data i en lettfattelig frontend
- Dokumentere, strukturere og presentere et prosjekt profesjonelt

---

## 🙌 Klar for produksjon?

Systemet er modulbasert og kan enkelt utvides med:

- Replay-modus
- Databaselagring
- Eksport til JSON/CSV
- Flere sensortyper
- Mer avansert AI-logikk for trusselklassifisering

---

> Dette prosjektet er utviklet som en del av min forberedelse til å søke utviklerstillinger hos Kongsberg Defence & Aerospace.

