/*******************************************************************************
/*  {
    "serial_rx": 3,
    "serial_tx": 1,
    "radio_dio0": 4,
    "radio_dio1": 5,
    "radio_miso": 12,
    "radio_mosi": 13,
    "radio_nss": 15,
    "radio_rst": 2,
    "radio_sck": 14,
    "power_min": 0,
    "power_high": 2,
    "power_max": 2,
    "power_default": 2,
    "power_control": 0,
    "power_values": [120,124,127],
    "led": 16,
    "button": 0
}
*
 *  File:         bsf_nodemcuv2.h
 * 
 *  Function:     Board Support File for BetaFPV ELRS NanoRX 868Mhz
 * 
 *  Copyright:    Copyright (c) 2025 der-Frickler.net
 * 
 *  License:      MIT License. See accompanying LICENSE file.
 * 
 *  Author:       der-Frickler.net
 * 
 *  Description:  This board is a very small and cheap ELRS Radio Receiver 
 *                containing an ESP8285 and an sx1276 LoRa tranceiver.
 *                only GND 5v RX and TX pins are available
 *                
 * 
 *                CONNECTIONS AND PIN DEFINITIONS:
 *                
                        "serial_rx": 3,
                        "serial_tx": 1,
                        "radio_dio0": 4,
                        "radio_dio1": 5,
                        "radio_miso": 12,
                        "radio_mosi": 13,
                        "radio_nss": 15,
                        "radio_rst": 2,
                        "radio_sck": 14,
                        "power_min": 0,
                        "power_high": 2,
                        "power_max": 2,
                        "power_default": 2,
                        "power_control": 0,
                        "power_values": [120,124,127],
                        "led": 16,
                        "button": 0
 *
 *  Identifiers:  LMIC-node
 *                    board:         betafpvnanorx
 *                PlatformIO
 *                    board:         esp8285
 *                    platform:      espressif8266
 * 
 ******************************************************************************/

#pragma once

#ifndef BSF_BETAFPV_NANORX_H_
#define BSF_BETAFPV_NANORX_H_

#include <ESP8266WiFi.h>
#include "LMIC-node.h"

#define DEVICEID_DEFAULT "betafpvnanorx"  // Default deviceid value

// Wait for Serial
// Can be useful for boards with MCU with integrated USB support.
// #define WAITFOR_SERIAL_SECONDS_DEFAULT 10   // -1 waits indefinitely  

// LMIC Clock Error
// This is only needed for slower 8-bit MCUs (e.g. 8MHz ATmega328 and ATmega32u4).
// Value is defined in parts per million (of MAX_CLOCK_ERROR).
// #ifndef LMIC_CLOCK_ERROR_PPM
//     #define LMIC_CLOCK_ERROR_PPM 0
// #endif   

// Pin mappings for LoRa tranceiver
const lmic_pinmap lmic_pins = {
    .nss = 15,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 2,
    .dio = { /*dio0*/ 5, /*dio1*/ 4, /*dio2*/ LMIC_UNUSED_PIN }
#ifdef MCCI_LMIC
    ,
    .rxtx_rx_active = 0,
    .rssi_cal = 10,
    .spi_freq = 1000000     /* 1 MHz */
#endif    
};

#define LORA_NSS      15  //D8
#define LORA_RST      LMIC_UNUSED_PIN
#define LORA_DIO0      4  //D1
#define LORA_DIO1      5  //D2
#define LORA_DIO2     LMIC_UNUSED_PIN
#define LORA_RXTX     LMIC_UNUSED_PIN

#ifdef USE_SERIAL
    HardwareSerial& serial = Serial;
#endif   

#ifdef USE_LED
    EasyLed led(16, EasyLed::ActiveLevel::Low);
#endif

#ifdef USE_DISPLAY
    #error "Invalid option: USE_DISPLAY. I2C and display are not supported due to shortage of available GPIO pins."
#endif


bool boardInit(InitType initType)
{
    // This function is used to perform board specific initializations.
    // Required as part of standard template.

    // InitType::Hardware        Must be called at start of setup() before anything else.
    // InitType::PostInitSerial  Must be called after initSerial() before other initializations.    

    bool success = true;
    switch (initType)
    {
        case InitType::Hardware:
            // Note: Serial port and display are not yet initialized and cannot be used use here.
            // No actions required for this board.
            break;

        case InitType::PostInitSerial:
            // Note: If enabled Serial port and display are already initialized here.
            // No actions required for this board.
            break;           
    }
    return success;
}


#endif  // BSF_NODEMCU_V2_H_