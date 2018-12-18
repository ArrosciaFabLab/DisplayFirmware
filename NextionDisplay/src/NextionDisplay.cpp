#include "NextionDisplay.hpp"

// La dichiarazione delle funzioni non è necessaria nel file .ino

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

		// Se la password � corretta
		if ( strcmp( ACCESS_PWD, strBuffer ) == 0 )
		{
			dbSerialPrintln( "La password è corretta!" );
			objVarLoginStatus.setValue( 1 );
		}
		else
		{
			dbSerialPrintln( "La password é errata!" );
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
}

void SetFirmwareVersion( int nVersion, int nRevision )
{
	// Se è la prima volta che inizializzo lo schermo e mi trovo sulla schermata dello splash screen
	if( ( nInitialized == 0 ) && ( nCurrentPage == 0 ) )
	{

		// Imposto l'attuale versione del firmware
		char strVersion[ 10 ] =  { 0 };
		memset( strVersion, 0, sizeof( strVersion ) );
		strcat( strVersion, String( nVersion ).c_str() );
		strcat( strVersion, "." );
		strcat( strVersion, String( nRevision ).c_str() );
		objNexTextVersion.setText( strVersion );
		Serial.write( 0xff );
		Serial.write( 0xff );
		Serial.write( 0xff );

		nInitialized = 1;
	}
}
