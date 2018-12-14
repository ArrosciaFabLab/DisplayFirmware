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
	InitializeDisplay();
}

// Loop standard di Arduino
void loop()
{
    // Ricevo qualsiasi evento touch (pressione o rilascio) proveniente dal display Nextion
	nexLoop( objTouchEventList );
}
