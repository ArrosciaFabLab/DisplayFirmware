#include "NextionFirmware.hpp"

// La dichiarazione delle funzioni non è necessaria nel file .ino

// Variabili
int nInitialized = 0;			// Indica se sono state eseguite tutte le operazioni di inizializzazione una-tantum. Se vale 1, l'inizializzazione è stata già eseguita
int nCurrentPage = 0;			// Pagina del display attualmente visualizzata (0 è la prima)
char strBuffer[ 100 ] =  { 0 }; // Buffer utilizzato per leggere del testo da un oggetto sulle pagine del display Nextion

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
NexText objNexTextVersion = NexText( 0, 3, "txtVersion" );				// Oggetto testo che visualizza la vesrione del software
NexText objNexTextSecretCode = NexText( 1, 1, "txtSecretCode" );		// Oggetto testo che contiene la password segreta digitata sulla tastiera della pagina di Login
NexButton objNexButtonSendCode = NexButton( 1, 50, "butSendCode" );		// Oggetto pulsante "Invio" della tastiera sulla pagina di inserimeno del codice di accesso
NexVariable objVarLoginStatus = NexVariable( 1, 55, "varLoginStatus" );	// Variabile che indica un login non riuscito (0) o un accesso valido (1)

// Dichiarazione delle pagine caricate sul display
// Formato: <tipo dell'oggetto> <nome dell'oggetto> = <tipo dell'oggetto>(<id di pagina>, <id di oggetto>, "<nome dell'oggetto>");
// Inviare dati ad un oggetto che non esiste ulla pagina corrente genera un codice di errore inviato dal display
// Qualsiasi errore inviato dal display crea un lag nel loop di Arduino perchè arduino cerca di leggerlo pensando che sia un evento touch
// Per permettere ad Arduino di sapere qual'è la pagina attualmente caricata sul display, creiamo un evento touch per ogni pagina
// Sul progetto del display, ogni pagina deve inviare un evento simulato touch nella sezione "Preinitialize Event" così da poter registrarlo come il caricamento di una nuova pagina
NexPage objSplashPage = NexPage( 0, 0, "SplashScreen" );
NexPage objLoginPage = NexPage( 1, 0, "LoginScreen" );
NexPage objHomePage = NexPage( 2, 0, "Home" );
NexPage objFANSStatusPage = NexPage( 3, 0, "FANSStatus" );
NexPage objSettingsPage = NexPage( 4, 0, "Settings" );
NexPage objSetScreenPage = NexPage( 5, 0, "SetScreen" );
NexPage objSetLEDStripPage = NexPage( 6, 0, "SetLEDStrip" );
NexPage objSetFANSPage = NexPage( 7, 0, "SetFANS" );

// Dichiarazione di tutti gli oggetti sulle pagine e le pagine stesse che inviano eventi di "pressione/rilascio"
// Formato: &<nome_oggetto>,
NexTouch *objTouchEventList[] =
{
	&objNexButtonSendCode,	// Pulsante di Invio sulla tastiera della pagina di Login

	&objSplashPage,			// Pagina dello splash screen
	&objLoginPage,			// Pagina di Login
	&objHomePage,			// Pagina principale
	&objFANSStatusPage,		// Pagina dello stato delle ventole
	&objSettingsPage,		// Pagina delle impostazioni
	&objSetScreenPage,		// Pagina delle impostazioni dello schermo
	&objSetLEDStripPage,	// Pagina delle impostazioni della striscia di led
 	&objSetFANSPage,		// Pagina delle impostazioni delle ventole

	NULL					// Fine stringa eventi
};

// Touch sulla pagina dello Splash screen
void pageSplashPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sullo SplashScreen" );
	nCurrentPage = 0;
}

// Touch sulla pagina di Login
void pageLoginPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata di Login" );
	nCurrentPage = 1;
}

// Touch sulla pagina principale
void pageHomePushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata principale" );
	nCurrentPage = 2;
}

// Touch sulla pagina dello stato delle ventole
void pageFANSStatusPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata di stato delle ventole" );
	nCurrentPage = 3;
}

// Touch sulla pagina delle impostazioni
void pageSettingsPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata delle impostazioni" );
	nCurrentPage = 4;
}

// Touch sulla pagina delle impostazioni dello schermo
void pageSetScreenPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata delle impostazioni dello schermo" );
	nCurrentPage = 5;
}

// Touch sulla pagina delle impostazioni della striscia di LED
void pageSetLEDStripPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata delle impostazioni della striscia di LED" );
	nCurrentPage = 6;
}

// Touch sulla pagina delle impostazioni delle ventole
void pageSetFANSPushCallback( void *ptrEvent )
{
	dbSerialPrintln( "Sono sulla schermata delle impostazioni delle ventole" );
	nCurrentPage = 7;
}

// Release sul pulsante "Invio" della tastiera della pagina di Login
void butSendCodePushCallBack( void *ptrEvent )
{

	// Se mi trovo nella pagina di Login
	if( nCurrentPage == 1 )
	{
		memset( strBuffer, 0, sizeof( strBuffer ) );

		// Ricavo la password di accesso digitata sulla pagina di Login
		objNexTextSecretCode.getText( strBuffer, sizeof( strBuffer ) );

		dbSerialPrintln( "La password digitata sulla pagina di Login è: " + String( strBuffer ) );

		// Se la password è corretta
		if ( strcmp( ACCESS_PWD, strBuffer ) == 0 )
		{
			dbSerialPrintln( "La password è corretta!" );
			objVarLoginStatus.setValue( 1 );
		}
		else
		{
			dbSerialPrintln( "La password è errata!" );
			objVarLoginStatus.setValue( 0 );
		}
	}
}

// Funzione che inizializza il display Nextion
void InitializeDisplay()
{
	// Inizializzo il display touch Nextion
	nexInit();

	// Associo tutti gli eventi di callBack (pressione e/o rilascio) su oggetti presenti sulle
	// pagine del display o sulle pagine stesse e le rispettive funzioni che eseguono le azioni conseguenti
	
	// Pagine
	objSplashPage.attachPush( pageSplashPushCallback );
	objLoginPage.attachPush( pageLoginPushCallback );
	objHomePage.attachPush( pageHomePushCallback );
	objFANSStatusPage.attachPush( pageFANSStatusPushCallback );
	objSettingsPage.attachPush( pageSettingsPushCallback );
	objSetScreenPage.attachPush( pageSetScreenPushCallback );
	objSetLEDStripPage.attachPush( pageSetLEDStripPushCallback );
	objSetFANSPage.attachPush( pageSetFANSPushCallback );
	
	// Oggetti
	objNexButtonSendCode.attachPush( butSendCodePushCallBack );
	
	// Se è la prima volta che inizializzo lo schermo e mi trovo sulla schermata di Splash screen
	if( ( nInitialized == 0 ) && ( nCurrentPage == 0 ) )
	{

		// Imposto l'attuale versione del firmware
		char strVersion[ 10 ] =  { 0 };
		memset( strVersion, 0, sizeof( strVersion ) );
		strcat( strVersion, SOFTWARE_VERISION );
		strcat( strVersion, "." );
		strcat( strVersion, SOFTWARE_REVISION );
		objNexTextVersion.setText( strVersion );
		Serial.write( 0xff );
		Serial.write( 0xff );
		Serial.write( 0xff );

		nInitialized = 1;
	}
}
