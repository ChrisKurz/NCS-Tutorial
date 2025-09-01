/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zcbor_decode.h>
#include <zcbor_encode.h>
#include <zcbor_common.h>
#include <stdio.h>

int main(void)
{
    char start_string[]="Hello World";
    uint8_t cbor_payload[15];
    struct zcbor_string decoded_string;
    bool success;

    printf("Hello World! %s\n", CONFIG_BOARD_TARGET);


    /* Create zcbor state variable for encoding. */
    ZCBOR_STATE_E(encoding_state, 0, cbor_payload, sizeof(cbor_payload), 0);	

    /* Encode a text string into the cbor_payload buffer */
    success = zcbor_tstr_put_lit(encoding_state, start_string);
    if (!success) {
        printf("Encoding failed: %d\r\n", zcbor_peek_error(encoding_state));
        return 0;
    }


	/* Create zcbor state variable for decoding. */
    ZCBOR_STATE_D(decoding_state, 0, cbor_payload, sizeof(cbor_payload), 1, 0);	

    /* Decode the text string into the decode_sting structure */
    success = zcbor_tstr_decode(decoding_state, &decoded_string);
    if (!success) {
        printf("Decoding failed: %d\r\n", zcbor_peek_error(decoding_state));
        return 0;
    }
    printf("Decoded string: '%.*s'\r\n", (int)decoded_string.len, decoded_string.value);	

    return 0;
}
