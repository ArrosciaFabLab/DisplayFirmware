#include "NextionDisplay.hpp"   // Libreria di gestione del display Nextion
#include <Arduino.h>    		// Su un file .ino non è necessario

/*
Schetch di test per lo schermo lcd touch Nextion
*/

// *** Costanti ***
#define SOFTWARE_VERISION	1				// Versione attuale del software
#define SOFTWARE_REVISION	1				// Revisione attuale del software

// *** Setup inizale di Arduino ***
void setup()
{
	InitializeDisplay();
	SetFirmwareVersion( SOFTWARE_VERISION, SOFTWARE_REVISION );
}

// *** Loop standard di Arduino ***
void loop()
{
    // Ricevo qualsiasi evento touch (pressione o rilascio) proveniente dal display Nextion
	nexLoop( objTouchEventList );
}
