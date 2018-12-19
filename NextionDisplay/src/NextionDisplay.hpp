#ifndef NEXTIONDISPLAY_H_
#define NEXTIONDISPLAY_H_

#include <Nextion.h>    // Libreria per lo schermo Nextion

// Costanti
#define RX_NEXTION_PIN		0				// PIN a cui è collegato il cavo che riceve dati seriali dallo schermo Nextion (Blu)
#define TX_NEXTION_PIN		1 				// PIN a cui è collegato il cavo che invia dati seriali allo schermo Nextion (Giallo)
#define ACCESS_PWD			"Morriz_1971"	// Password di accesso - momentaneamente cablata

// Variabili
extern int nInitialized;			// Indica se sono state eseguite tutte le operazioni di inizializzazione una-tantum. Se vale 1, l'inizializzazione � stata gi� eseguita
extern int nCurrentPage;			// Pagina del display attualmente visualizzata (0 � la prima)
extern char strBuffer[ 100 ]; 		// Buffer utilizzato per leggere del testo da un oggetto sulle pagine del display Nextion

// Dichiarazione di tutti gli oggetti sulle pagine del display con cui devo interagire
// Formato: <tipo dell'oggetto> <nome dell'oggetto> = <tipo dell'oggetto>(<id di pagina>, <id di oggetto>, "<nome dell'oggetto>");
/* Tipi di oggetti:
 * NexButton - Pulsante
 * NexDSButton - Pulsante a due stati
 * NexHotspot - Hotspot, un pulsante invisibile
 * NexCheckbox - Checkbox
 * NexRadio - "Radio" button
 * NexSlider - Slider
 * NexGauge - Gauge
 * NexProgressBar - Progress Bar
 * NexText - Box di testo
 * NexScrolltext - Box con testo scorrevole
 * NexNumber - Box numerico
 * NexVariable - Variabile interna al display
 * NexPage - Evento touch sulla pagina
 * NexGpio - Per usare la scheda di espansione del display
 * NexRtc - Per usare il real time clock
 */
extern NexText objNexTextVersion;			// Oggetto testo che visualizza la vesrione del software
extern NexText objNexTextSecretCode;		// Oggetto testo che contiene la password segreta digitata sulla tastiera della pagina di Login
extern NexButton objNexButtonSendCode;		// Oggetto pulsante "Invio" della tastiera sulla pagina di inserimeno del codice di accesso
//extern NexVariable objVarLoginStatus = NexVariable( 1, 55, "varLoginStatus" );	// Variabile che indica un login non riuscito (0) o un accesso valido (1)

// Dichiarazione delle pagine caricate sul display
// Formato: <tipo dell'oggetto> <nome dell'oggetto> = <tipo dell'oggetto>(<id di pagina>, <id di oggetto>, "<nome dell'oggetto>");
// Inviare dati ad un oggetto che non esiste ulla pagina corrente genera un codice di errore inviato dal display
// Qualsiasi errore inviato dal display crea un lag nel loop di Arduino perch� arduino cerca di leggerlo pensando che sia un evento touch
// Per permettere ad Arduino di sapere qual'� la pagina attualmente caricata sul display, creiamo un evento touch per ogni pagina
// Sul progetto del display, ogni pagina deve inviare un evento simulato touch nella sezione "Preinitialize Event" cos� da poter registrarlo come il caricamento di una nuova pagina
extern NexPage objSplashPage;
extern NexPage objLoginPage;
extern NexPage objHomePage;
extern NexPage objFANSStatusPage;
extern NexPage objSettingsPage;
extern NexPage objSetScreenPage;
extern NexPage objSetLEDStripPage;
extern NexPage objSetFANSPage;

// Dichiarazione di tutti gli oggetti sulle pagine e le pagine stesse che inviano eventi di "pressione/rilascio"
// Formato: &<nome_oggetto>,
extern NexTouch *objTouchEventList[];

// Definizione delle funzioni
// Non è necessaria nel file .ino al posto di .cpp

// Funzioni che reagiscono agli eventi push sulle pagine
void pageSplashPushCallback( void *ptrEvent );
void pageLoginPushCallback( void *ptrEvent );
void pageHomePushCallback( void *ptrEvent );
void pageFANSStatusPushCallback( void *ptrEvent );
void pageSettingsPushCallback( void *ptrEvent );
void pageSetScreenPushCallback( void *ptrEvent );
void pageSetLEDStripPushCallback( void *ptrEvent );
void pageSetFANSPushCallback( void *ptrEvent );

// Funzioni che reagiscono agli eventi push sugli oggetti delle pagine
void butSendCodePushCallBack( void *ptrEvent );

// Funzione che inizializza il display Nextion
void InitializeDisplay();

// Imposta la versione del firmware nel display
void SetFirmwareVersion( int nVersion = 0, int nRevision = 0 );

#endif
