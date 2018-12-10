/**
 * RemoteControl.h - Library to read commands from remote control
 * Created by David Murillo, Sep 2, 2018
 * Released into the public domain.
 */
#ifndef RemoteControl_h
#define RemoteControl_h

#include "Arduino.h"
#include "IRremote.h"

class RemoteControl {

  public:
    // Primary codes for each key of remote control
    static const unsigned long UP = 16736925;
    static const unsigned long RIGHT = 16761405;
    static const unsigned long LEFT = 16720605;
    static const unsigned long DOWN = 16754775;
    static const unsigned long OK = 16712445;
    static const unsigned long ONE = 16738455;
    static const unsigned long TWO = 16750695;
    static const unsigned long THREE = 16756815;
    static const unsigned long FOUR = 16724175;
    static const unsigned long FIVE = 16718055;
    static const unsigned long SIX = 16743045;
    static const unsigned long SEVEN = 16716015;
    static const unsigned long EIGHT = 16726215;
    static const unsigned long NINE = 16734885;
    static const unsigned long ZERO = 16730805;
    static const unsigned long ASTERISK = 16728765;
    static const unsigned long NUMBER_SIGN = 16732845;

    // Used to return this value when the receiver didn't read any button
    static const unsigned long NOTHING = 0;

    RemoteControl();

    /**
     * Returns true if any button of remote control was pressed
     * returns false if none button was pressed
     */
    bool buttonPressed();

    unsigned long readButton();

    /**
     * Returns 1 if buttonKey is Up button,
     * otherwise returns 0
     */
    bool isUpButton(unsigned long buttonKey);
    
    /**
     * Prepare the receiver to make next reading.
     * Needs to be called after 
     */
    void resumeForNextReading();
    
  private:
    static const int _RECV_PIN = 12;
    // codes for keys of remote control
    // This codes are received when the signal from remote control comes from
    // the front and a bit to the left of the car
    static const unsigned long _LONG_PRESSED_KEY = 4294967295;
    static const unsigned long _UP2 = 5316027;
    static const unsigned long _RIGHT2 = 553536955;
    static const unsigned long _LEFT2 = 1386468383;
    static const unsigned long _DOWN2 = 2747854299;
    static const unsigned long _OK2 = 3622325019;
    static const unsigned long _ONE2 = 3238126971;
    static const unsigned long _TWO2 = 2538093563;
    static const unsigned long _THREE2 = 4039382595;
    static const unsigned long _FOUR2 = 2534850111;
    static const unsigned long _FIVE2 = 1033561079;
    static const unsigned long _SIX2 = 1635910171;
    static const unsigned long _SEVEN2 = 2351064443;
    static const unsigned long _EIGHT2 = 1217346747;
    static const unsigned long _NINE2 = 71952287;
    static const unsigned long _ZERO2 = 465573243;
    static const unsigned long _ASTERISK2 = 851901943;
    static const unsigned long _NUMBER_SIGN2 = 1053031451;

    IRrecv _irrecv(_RECV_PIN);
    decode_results _results;
};

#endif

