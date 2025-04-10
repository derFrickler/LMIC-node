/*******************************************************************************
 *
 *  File:         lmic-node-uplink-formatters.js
 * 
 *  Function:     LMIC-node uplink payload formatter JavaScript function(s).
 * 
 *  Author:       Leonel Lopes Parente
 * 
 *  Description:  These function(s) are for use with The Things Network V3. 
 *                 
 ******************************************************************************/

function decodeUplink(input) {
    var data = {};
    var warnings = [];

    if (input.fPort == 10) {
        data.counter = (input.bytes[0] << 8) + input.bytes[1];
    }
    else {
        warnings.push("Unsupported fPort");
    }
    return {
        data: data,
        warnings: warnings
    };
}


function decodeUplink(input) {
    // Check if the payload has the correct length
    if (input.bytes.length !== 9) {
      return {
        data: {},
        errors: ["Invalid payload length"],
        warnings: []
      };
    }
  
    // Extract latitude (24 bits)
    const lat = ((input.bytes[0] << 16) | (input.bytes[1] << 8) | input.bytes[2]) / 16777215.0 * 180.0 - 90.0;
    
    // Extract longitude (24 bits)
    const lng = ((input.bytes[3] << 16) | (input.bytes[4] << 8) | input.bytes[5]) / 16777215.0 * 360.0 - 180.0;
    
    // Extract altitude (16 bits)
    const alt = (input.bytes[6] << 8) | input.bytes[7];
    
    // Extract HDOP (8 bits) and multiply by 0.1 to get the actual value
    const hdop = input.bytes[8] * 0.1;
  
    return {
      data: {
        latitude: Number(lat.toFixed(6)),
        longitude: Number(lng.toFixed(6)),
        altitude: alt,
        hdop: Number(hdop.toFixed(1))
      },
      warnings: [],
      errors: []
    };
  }