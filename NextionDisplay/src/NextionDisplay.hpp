#ifndef NEXTIONDISPLAY_H_
#define NEXTIONDISPLAY_H_

#include <Nextion.h>    // Libreria per lo schermo Nextion

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

#endif
