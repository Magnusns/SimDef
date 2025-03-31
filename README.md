# SimDef
Sanntidssystem for simulert trusseldeteksjon og respons, bygd med C++ og Qt

# SimDef

**Sanntidssystem for simulert trusseldeteksjon og respons**  
Bygd for å demonstrere ferdigheter innen objektorientert arkitektur, sanntidssystemer, datasikkerhet og grafisk visualisering – med tanke på stilling hos Kongsberg Defence & Aerospace.

---

## 🚀 Oversikt

SimDef er et simuleringssystem som overvåker virtuelle objekter i sanntid og vurderer om de utgjør en trussel. Sensorer simuleres og sender kontinuerlig data til et kontrollsenter som visualiserer situasjonen og håndterer varsler.

---

## 🧩 Systemarkitektur

- **SensorSimulator:** Genererer bevegelige objekter med posisjon og ID
- **TrusselAnalyseModul:** Vurderer risiko basert på bevegelsesmønster
- **Kontrollsenter:** Viser objekter, håndterer varsler, logger hendelser
- **GUI:** Interaktiv visning av systemstatus (bygges i Qt/JavaFX)

---

## 🛠️ Teknologi

- Språk: `C++` *(eller Java, hvis valgt)*
- GUI: `Qt` *(eller JavaFX)*
- Sanntidsdata: WebSocket
- Logging: JSON + lokal loggfil
- Autentisering: Enkel login/rollebasert tilgang

---

## ✅ Mål

- Demonstrere evne til å bygge robuste, objektorienterte sanntidssystemer
- Øke sannsynligheten for ansettelse i softwareutviklingsteamet hos Kongsberg Defence & Aerospace

---

## 🔧 Videre arbeid

- [ ] Implementere sensor-simulator
- [ ] Bygge analysemodul
- [ ] Utvikle GUI
- [ ] Legge til enkel brukerautentisering
- [ ] Dokumentasjon og demo

---

## 📷 Skjermbilder og demo

Kommer...

---

## 📁 Struktur