/*
 * ASCIITranslator.c
 *
 *  Created on: Jan 18, 2019
 *      Author: Dylan
 */

#include "ASCIITranslator.h"
#include <stdint.h>

uint8_t getByteZero(uint8_t key){
    if(key >= 65 && key <= 90){
        return (0x02);
    }else{
        return(0x00);
    }

}

uint8_t getByteTwo(uint8_t key){
    uint8_t ASCIItoKEY [128] = {
        0x00,             // NULL
        0x00,             // Start of Header
        0x00,             // Start of text
        0x00,             // End of Text
        0x00,             // End of Transmission
        0x00,             // Enquiry
        0x00,             // Acknowledgment
        0x00,             // BELL
        0x2a,             // Backspace
        0x2b,             // Tab
        0x28,             // Enter - Line feed
        0x00,             // Vertical Tab
        0x00,             // Form Feed
        0x00,             // Carriage return
        0x00,             // Shift Out
        0x00,             // Shift in
        0x00,             // Data Link Escape
        0x00,             // Device Control 1
        0x00,             // Device Control 2
        0x00,             // Device Control 3
        0x00,             // Device Control 4
        0x00,             // Negative Acknowledgment
        0x00,             // Sync. Idle
        0x00,             // End of Trans, Block
        0x00,             // Cancel
        0x00,             // End of Medium
        0x00,             // Substitute
        0x00,             // ESC
        0x00,             // File Separator
        0x00,             // Group Separator
        0x00,             // Record Separator
        0x00,             // Unit Separator
        0x2c,          //  ' '  -Space
        0x1e,          // !
        0x34,          // "
        0x20,          // #
        0x21,          // $
        0x22,          // %
        0x24,          // &
        0x34,          // '
        0x26,          // (
        0x27,          // )
        0x25,          // *
        0x2e,          // +
        0x36,          // ,
        0x2d,          // -
        0x37,          // .
        0x38,          // /
        0x27,          // 0
        0x1e,          // 1
        0x1f,          // 2
        0x20,          // 3
        0x21,          // 4
        0x22,          // 5
        0x23,          // 6
        0x24,          // 7
        0x25,          // 8
        0x26,          // 9
        0x33,          // :
        0x33,          // ;
        0x36,          // <
        0x2e,          // =
        0x37,          // >
        0x38,          // ?
        0x1f,          // @
        0x04,          // A
        0x05,          // B
        0x06,          // C
        0x07,          // D
        0x08,          // E
        0x09,          // F
        0x0a,          // G
        0x0b,          // H
        0x0c,          // I
        0x0d,          // J
        0x0e,          // K
        0x0f,          // L
        0x10,          // M
        0x11,          // N
        0x12,          // O
        0x13,          // P
        0x14,          // Q
        0x15,          // R
        0x16,          // S
        0x17,          // T
        0x18,          // U
        0x19,          // V
        0x1a,          // W
        0x1b,          // X
        0x1c,          // Y
        0x1d,          // Z
        0x2f,          // [
        0x31,          // "\"
        0x30,          // ]
        0x23,          // ^
        0x2d,          // _
        0x35,          // `
        0x04,          // a
        0x05,          // b
        0x06,          // c
        0x07,          // d
        0x08,          // e
        0x09,          // f
        0x0a,          // g
        0x0b,          // h
        0x0c,          // i
        0x0d,          // j
        0x0e,          // k
        0x0f,          // l
        0x10,          // m
        0x11,          // n
        0x12,          // o
        0x13,          // p
        0x14,          // q
        0x15,          // r
        0x16,          // s
        0x17,          // t
        0x18,          // u
        0x19,          // v
        0x1a,          // w
        0x1b,          // x
        0x1c,          // y
        0x1d,          // z
        0x2f,          // {
        0x31,          // |
        0x30,          // }
        0x35,          // ~
        0               // DEL
    };

    return ASCIItoKEY[key];
}
