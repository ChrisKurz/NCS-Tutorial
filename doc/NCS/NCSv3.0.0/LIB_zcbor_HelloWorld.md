<sup>SDK version: NCS v3.0.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/Modules/tree/main/Workspace/NCS/NCSv3.0.0/zcbor_HelloWorld</sup>

# Add ZCBOR to project and handling of Encoding/Decoding

## Introduction

ZCBOR is a low footprint [CBOR](https://en.wikipedia.org/wiki/CBOR) library in the C language (C++ compatible), tailored for use in microcontrollers. It comes with a schema-driven script tool that can validate your data, or even generate code. The schema language (CDDL) allows creating very advanced and detailed schemas. The validation and conversion part of the tool works with YAML and JSON data, in addition to CBOR.
It can for example validate a YAML file against a schema and convert it into CBOR. The code generation part of the tool generates C code based on the given schema. The generated code performs CBOR encoding and decoding using the C library, while also validating the data against all the rules in the schema. The schema language used by zcbor is CDDL (Concise Data Definition Language) which is a powerful human-readable data description language defined in [IETF RFC 8610](https://datatracker.ietf.org/doc/rfc8610/).


## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.0.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create needed Folders and Files

1) Create a new application. Use the _zephyr/samples/hello_world_ sample. Change the project name to __zbor_HelloWorld__, so it is easier lateron to identify the ZCBOR project.  


### Add ZCBOR library to the project

2) We add the ZCBOR library to our project by adding following lines in __prj.conf__ file.

  <sup>_prj.conf_</sup>  

    CONFIG_ZCBOR=y
    CONFIG_ZCBOR_STOP_ON_ERROR=y


### Adding ZCBOR to main and preparing needed variables

3) First, add the required include files.

  <sup>_src/main.c_</sup>  

    #include <zcbor_decode.h>
    #include <zcbor_encode.h>
    #include <zcbor_common.h>

4) In this simple sample we start with the __start_string__"Hello World" and first of all we encode it. The encoded data will be stored in the array __cbor_payload[]__. And finally, the decoding is done again and the decoded string is stored in __decoded_string__ structure. We will use macros that return false in case any error occured. We handle this one with the boolean __success__. Let's declare these variables. 

  <sup>_src/main.c_ => main() function</sup>  

        char start_string[]="Hello World";
        uint8_t cbor_payload[15];
        struct zcbor_string decoded_string;
        bool success;

### Encode a text string

5) We have to create a ZCBOR state variable for encryption. We can use the macro __ZCBOR_STATE_E()__ for this.

  <sup>_src/main.c_ => main() function</sup>  
         
        /* Create zcbor state variable for encoding. */
        ZCBOR_STATE_E(encoding_state, 0, cbor_payload, sizeof(cbor_payload), 0);

6) Encoding of the text string is done with following line. The encoded data is stored in the array __cbor_payload__.

  <sup>_src/main.c_ => main() function</sup>  
         
        /* Encode a text string into the cbor_payload buffer */
        success = zcbor_tstr_put_lit(encoding_state, start_string);
        if (!success) {
            printf("Encoding failed: %d\r\n", zcbor_peek_error(encoding_state));
            return 0;
        }

### Decode the CBOR data of a text string

7) We need also a ZCBOR state variable for decoding. We can use the macro __ZCBOR_STATE_D()__ for this.

  <sup>_src/main.c_ => main() function</sup>  
         
        /* Create zcbor state variable for decoding. */
        ZCBOR_STATE_D(decoding_state, 0, cbor_payload, sizeof(cbor_payload), 1, 0);

8) And then decode the __cbor_payload__ data into the __decode_sting__ structure.

  <sup>_src/main.c_ => main() function</sup>  
         
        /* Decode the text string into the decode_sting structure */
        success = zcbor_tstr_decode(decoding_state, &decoded_string);
        if (!success) {
            printf("Decoding failed: %d\r\n", zcbor_peek_error(decoding_state));
            return 0;
        }
        printf("Decoded string: '%.*s'\r\n", (int)decoded_string.len, decoded_string.value);


## Testing

9) Build the project and check the output in a Serial Termninal. Use the Debugger and its "Watch" window to check the content of __cbor_payload[]__ array. 
