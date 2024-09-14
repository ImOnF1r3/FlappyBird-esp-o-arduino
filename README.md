# Gioco Flappy Bird su ESP8266 con Display OLED e EEPROM

## Descrizione del Progetto
Questo progetto implementa una versione semplificata del famoso gioco "Flappy Bird" utilizzando un microcontrollore ESP8266 e un display OLED basato sul driver SSD1306. Il gioco coinvolge il movimento verticale di un oggetto che deve evitare ostacoli in movimento orizzontale. La difficoltà aumenta progressivamente nel tempo. Inoltre, il miglior punteggio viene salvato nella memoria EEPROM del dispositivo, in modo che non venga perso tra un reset e l'altro.

## Componenti Hardware
1. **ESP8266** - Il microcontrollore utilizzato per eseguire il gioco.
2. **Display OLED (128x64)** - Utilizzato per mostrare l'oggetto, gli ostacoli, il punteggio e i messaggi di stato del gioco.
3. **Pulsante** - Utilizzato per saltare e controllare il movimento dell'oggetto nel gioco.
4. **EEPROM** - Utilizzata per memorizzare il punteggio massimo.

## Librerie Necessarie
Per eseguire correttamente questo progetto, avrai bisogno delle seguenti librerie:
1. **ESP8266WiFi** - Libreria per la gestione del WiFi (anche se in questo progetto non è utilizzata direttamente).
2. **Wire.h** - Libreria per la comunicazione I2C, utilizzata per il display OLED.
3. **Adafruit_GFX.h** - Libreria per la grafica, utilizzata per disegnare forme e testo sul display.
4. **Adafruit_SSD1306.h** - Libreria specifica per il controllo del display OLED SSD1306.
5. **EEPROM.h** - Libreria per gestire la memoria EEPROM e salvare il punteggio massimo.

## Come Funziona
- L'utente avvia il gioco premendo un pulsante.
- L'oggetto si muove verso il basso a causa della gravità e salta quando il pulsante viene premuto.
- Gli ostacoli si muovono da destra a sinistra e il giocatore deve evitare di colpire gli ostacoli.
- Il punteggio aumenta ogni volta che si supera un ostacolo.
- Se l'oggetto colpisce un ostacolo o il bordo inferiore dello schermo, il gioco termina.
- Il punteggio massimo viene salvato nella EEPROM e viene visualizzato sullo schermo.
- Premendo il pulsante dopo la fine del gioco, il gioco viene riavviato.

## Struttura del Codice
### setup()
- Inizializza il display OLED e la EEPROM.
- Attende che l'utente prema il pulsante per iniziare.

### loop()
- Controlla se il gioco è in corso o se è terminato.
- Se il gioco è in corso, aggiorna la logica del gioco e il display.
- Se il gioco è terminato, attende che l'utente prema il pulsante per riavviare.

### Funzioni Principali
1. **logicaGioco()** - Gestisce il movimento dell'oggetto, il movimento degli ostacoli e verifica le collisioni.
2. **aggiornaSchermo()** - Aggiorna la visualizzazione del gioco, disegnando l'oggetto, gli ostacoli e i punteggi.
3. **aumentaDifficolta()** - Aumenta progressivamente la velocità degli ostacoli e riduce la distanza tra di essi.
4. **resetGioco()** - Reimposta tutte le variabili del gioco quando l'utente decide di riprovare.
5. **controllaTasto()** - Gestisce l'input dell'utente, controllando il pulsante per far saltare l'oggetto.

## Come Caricare il Progetto
1. **Installazione delle librerie**: Assicurati di avere le librerie sopra elencate installate nell'IDE Arduino.
2. **Connessioni Hardware**: 
   - Collega il display OLED all'ESP8266 utilizzando i pin I2C (SDA a GPIO0, SCL a GPIO2).
   - Collega un pulsante tra il pin GPIO14 e GND.
3. **Caricamento del codice**: Collega l'ESP8266 al computer, carica lo sketch utilizzando l'IDE Arduino e carica il codice sul microcontrollore.
4. **Esecuzione del gioco**: Una volta caricato, il gioco si avvierà sul display OLED e potrai giocare premendo il pulsante collegato.

## Personalizzazioni
- **Modifica della difficoltà**: Puoi modificare la difficoltà del gioco variando i parametri come `gravita`, `forzaSalto`, `velocitaOstacolo`, `gapOstacolo` e le costanti che regolano la progressione della difficoltà.
- **Aggiunta di nuove funzionalità**: È possibile espandere il gioco aggiungendo funzionalità come suoni, più livelli di difficoltà, animazioni, ecc.

## Note
- **EEPROM**: La memoria EEPROM ha un numero limitato di cicli di scrittura (circa 100.000). Assicurati di non sovrascrivere la EEPROM troppo frequentemente.
- **Debugging**: Usa il monitor seriale per il debugging e per visualizzare messaggi di stato o errori.

Buon divertimento con il tuo gioco!
