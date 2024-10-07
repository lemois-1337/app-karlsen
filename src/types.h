/*****************************************************************************
 * MIT License
 *
 * Copyright (c) 2023 coderofstuff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/
#pragma once

#include <stddef.h>  // size_t
#include <stdint.h>  // uint*_t

#include "constants.h"
#include "transaction/types.h"
#include "bip32.h"

/**
 * Enumeration with expected INS of APDU commands.
 */
typedef enum {
#ifdef HAVE_DEBUG_APDU
    DEBUG_APDU = 0xde,  /// debug test cases
#endif
    GET_VERSION = 0x03,     /// version of the application
    GET_APP_NAME = 0x04,    /// name of the application
    GET_PUBLIC_KEY = 0x05,  /// public key of corresponding BIP32 path
    SIGN_TX = 0x06,         /// sign transaction with BIP32 path
    SIGN_MESSAGE = 0x07     /// sign a personal message with BIP32 path
} command_e;

/**
 * Enumeration with parsing state.
 */
typedef enum {
    STATE_NONE,     /// No state
    STATE_PARSED,   /// Transaction data parsed
    STATE_APPROVED  /// Transaction data approved
} state_e;

typedef enum {
    SCHNORR,  // Display the 61 byte address for schnorr
    ECDSA,    // Display the 63 byte address for ecdsa
    P2SH      // Display the 61 byte address for p2sh (also schnorr)
} address_type_e;

/**
 * Enumeration with user request type.
 */
typedef enum {
    CONFIRM_ADDRESS,      /// confirm address derived from public key
    CONFIRM_TRANSACTION,  /// confirm transaction information
    CONFIRM_MESSAGE       /// confirm message information
} request_type_e;

/**
 * Structure for public key context information.
 */
typedef struct {
    uint8_t raw_public_key[64];  /// x-coordinate (32), y-coodinate (32)
    uint8_t chain_code[32];      /// for public key derivation
} pubkey_ctx_t;

/**
 * Structure for transaction information context.
 */
typedef struct {
    transaction_t transaction;           /// structured transaction
    uint8_t signature[MAX_DER_SIG_LEN];  /// transaction input signature encoded in DER
    uint8_t signing_input_index;         /// The input index currently being signed
    uint8_t sighash[32];                 /// The sighash being signed
    uint8_t parsing_input_index;
    uint8_t parsing_output_index;
} transaction_ctx_t;

/**
 * Structure for message signing information context.
 */
typedef struct {
    size_t message_len;                  /// message length
    uint8_t message[128];                /// message bytes
    uint8_t message_hash[32];            /// message hash
    uint8_t signature[MAX_DER_SIG_LEN];  /// signature of the message
    uint32_t account;                    /// The account this message will be signed with
    uint8_t address_type;                /// address type to use for bip32 path
    uint32_t address_index;              /// address index to use for bip32 path
} message_sign_ctx_t;

/**
 * Structure for global context.
 */
typedef struct {
    state_e state;  /// state of the context
    union {
        pubkey_ctx_t pk_info;         /// public key context
        transaction_ctx_t tx_info;    /// transaction context
        message_sign_ctx_t msg_info;  /// message sign context
    };
    request_type_e req_type;                          /// user request
    uint32_t bip32_path[KARLSEN_MAX_BIP32_PATH_LEN];  /// BIP32 path
    uint8_t bip32_path_len;                           /// length of BIP32 path
} global_ctx_t;
