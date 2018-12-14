#include "NextionDisplay.hpp"   // Libreria di gestione delle ventole
#include <Arduino.h>    // Su un file .ino non è necessario

/*
Schetch di test per lo schermo lcd touch Nextion
*/

// Costanti
#define SOFTWARE_VERISION	"1"				// Versione attuale del software
#define SOFTWARE_REVISION	"1"				// Revisione attuale del software
#define RX_NEXTION_PIN		0				// PIN a cui è collegato il cavo che riceve dati seriali dallo schermo Nextion (Blu)
#define TX_NEXTION_PIN		1 				// PIN a cui è collegato il cavo che invia dati seriali allo schermo Nextion (Giallo)
#define ACCESS_PWD			"Morriz_1971"	// Password di accesso - momentaneamente cablata

// La dichiarazione delle funzioni non è necessaria nel file .ino

// Setup inizale di Arduino
void setup()
{
   // Inizializzo il display touch Nextion
	nexInit();

	// Associo tutti gli eventi di callBack (pressione e/o rilascio) su oggetti presenti sulle
	// pagine del display o sulle pagine stesse e le rispettive funzioni che eseguono le azioni conseguenti
	objSplashPage.attachPush( pageSplashPushCallback );
	objLoginPage.attachPush( pageLoginPushCallback );
	objHomePage.attachPush( pageHomePushCallback );
	objFANSStatusPage.attachPush( pageFANSStatusPushCallback );
	objSettingsPage.attachPush( pageSettingsPushCallback );
	objSetScreenPage.attachPush( pageSetScreenPushCallback );
	objSetLEDStripPage.attachPush( pageSetLEDStripPushCallback );
	objSetFANSPage.attachPush( pageSetFANSPushCallback );

	objNexButtonSendCode.attachPush( butSendCodePushCallBack );

	// Se è la prima volta che inizializzo lo schermo e mi trovo sulla schermata di Splash screen
	if( ( nInitialized == 0 ) && ( nCurrentPage == 0 ) )
	{

		// Imposto la versione attuale del software
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
		dbSerialPrintln( "Attuale versione impostata: " + String( strVersion ) );
	}
}

// Loop standard di Arduino
void loop()
{
    // Ricevo qualsiasi evento touch (pressione o rilascio) proveniente dal display Nextion
	nexLoop( objTouchEventList );
}
