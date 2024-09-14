# Flappy Bird su ESP8266 con Display OLED e Salvataggio Punteggio su EEPROM

## Descrizione del Progetto
Questo progetto implementa una versione del popolare gioco "Flappy Bird" utilizzando un ESP8266 e un display OLED SSD1306. L'obiettivo del gioco è evitare gli ostacoli muovendo l'uccellino in verticale e superando i tubi che si avvicinano da destra. La difficoltà aumenta gradualmente nel tempo, rendendo il gioco più veloce e i tubi più stretti. Il miglior punteggio viene salvato nella memoria EEPROM, in modo che venga mantenuto anche quando il dispositivo viene spento o riavviato.

## Componenti Hardware Necessari
1. **ESP8266** - Il microcontrollore che esegue il gioco.
2. **Display OLED SSD1306 (128x64)** - Utilizzato per mostrare il gioco.
3. **Pulsante** - Utilizzato per controllare il salto dell'uccellino.
4. **EEPROM** - Memorizza il miglior punteggio.

## Librerie Richieste
Prima di caricare il codice, è necessario installare le seguenti librerie nell'IDE Arduino:
- **Adafruit GFX Library** - Per la gestione della grafica.
- **Adafruit SSD1306 Library** - Per il controllo del display OLED.
- **EEPROM Library** - Per gestire la memoria EEPROM dell'ESP8266.
- **Wire Library** - Per la comunicazione I2C (integrata nell'IDE Arduino).

## Come Funziona il Gioco
- Il gioco inizia quando l'utente preme un pulsante collegato all'ESP8266.
- L'uccellino cade a causa della gravità, ma l'utente può farlo saltare premendo il pulsante.
- Il punteggio aumenta ogni volta che l'uccellino supera un tubo.
- La difficoltà aumenta gradualmente, rendendo i tubi più veloci e riducendo la distanza tra loro.
- Se l'uccellino colpisce un tubo o tocca il bordo inferiore dello schermo, il gioco termina.
- Il punteggio massimo viene salvato nella EEPROM e visualizzato sullo schermo.
- Premendo nuovamente il pulsante, il gioco viene riavviato.

## Schema dei Collegamenti
1. **OLED Display**:
   - **SDA** → GPIO0
   - **SCL** → GPIO2
   - **VCC** → 3.3V
   - **GND** → GND
2. **Pulsante**:
   - Un lato del pulsante collegato a **GPIO14** (D5).
   - L'altro lato collegato a **GND**.

## Configurazione del Codice
### Variabili Principali:
- `birdY`: La posizione verticale dell'uccellino.
- `birdVelocity`: La velocità verticale dell'uccellino (aumenta con la gravità).
- `pipeX`: La posizione orizzontale del tubo.
- `pipeGap`: Lo spazio tra i tubi superiore e inferiore.
- `score`: Il punteggio corrente del giocatore.
- `highScore`: Il miglior punteggio salvato nella EEPROM.

### Logica del Gioco:
- La gravità influisce continuamente sull'uccellino, facendolo cadere verso il basso.
- Quando il pulsante viene premuto, l'uccellino "salta" verso l'alto con una velocità negativa.
- Gli ostacoli si muovono da destra a sinistra, e se l'uccellino li supera, il punteggio aumenta.
- Se l'uccellino tocca un ostacolo o il bordo inferiore dello schermo, il gioco termina e viene visualizzato il messaggio "Game Over".

### EEPROM:
- Il miglior punteggio viene salvato in EEPROM per essere recuperato alla prossima esecuzione del gioco.
- Il punteggio massimo viene caricato all'inizio del gioco dalla funzione `readHighScoreFromEEPROM()`.
- Se il giocatore batte il record, il nuovo punteggio massimo viene salvato usando la funzione `saveHighScoreToEEPROM()`.

## Come Caricare il Progetto
1. **Installazione delle librerie**: Assicurati di avere installato le librerie `Adafruit_GFX`, `Adafruit_SSD1306` e `EEPROM` nell'IDE Arduino.
2. **Connessioni Hardware**: Collega l'OLED Display e il pulsante come descritto sopra.
3. **Caricamento del Codice**: Collega l'ESP8266 al computer tramite USB e carica il codice utilizzando l'IDE Arduino.
4. **Gioca**: Una volta caricato, il gioco verrà visualizzato sul display OLED. Premi il pulsante per iniziare e controllare l'uccellino.

## Personalizzazioni Possibili
- **Velocità e Gravità**: Puoi modificare i parametri `gravity`, `jumpStrength` e `pipeSpeed` per cambiare la difficoltà del gioco.
- **Grafica**: Aggiungi elementi grafici aggiuntivi o modifiche utilizzando le funzioni della libreria Adafruit GFX.
- **Difficoltà Incrementale**: I parametri come `maxPipeSpeed` e `minPipeGap` possono essere modificati per regolare la velocità massima e lo spazio minimo tra i tubi.

## Debug e Monitor Serial
Durante il caricamento e l'esecuzione del codice, è possibile utilizzare il **Monitor Seriale** nell'IDE Arduino per vedere messaggi di debug e verificare il funzionamento corretto.

## Note
- **Memoria EEPROM**: La EEPROM ha un numero limitato di cicli di scrittura (circa 100.000). Non salvare il punteggio massimo troppo frequentemente.
- **Ottimizzazione del Gioco**: Questo codice è ottimizzato per funzionare su un ESP8266, ma può essere adattato ad altre piattaforme come Arduino con le modifiche appropriate alle librerie e alle funzioni di gestione della memoria.

Divertiti a giocare con il tuo progetto Flappy Bird!
