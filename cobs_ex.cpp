#include "cobs_ex.h"

cobs_ex::cobs_ex(){
    //Constructor
}

cobs_ex::~cobs_ex(){
    //Destructor
}

size_t cobs_ex::cobs_encode(const uint8_t *input, size_t length, uint8_t *output){
    const uint8_t* end = input + length;    // end of input buffer
        uint8_t* codeBytePos = output;          // holds pointer to the position of a code byte
        uint8_t codeByte = 1;                   // code byte
        size_t write_index = 0;

        /* first byte of the input buffer is in the second position of output buffer */
        ++output;

        /* iterate over the input bytes */
        while (input < end)
        {
            if (*input == 0)
            {
                *codeBytePos = codeByte;        // put the code byte in the corresponding position
                codeByte = 1;                   // reset the code count
                codeBytePos = output;           // update the code byte position
            }
            else
            {
                *output = *input;               // put the
                ++codeByte;                     //
                if (codeByte == 0xFF)
                {
                    *codeBytePos = codeByte;
                    codeByte = 1;
                    codeBytePos = output;
                }
            }
            ++output;
            ++input;
            ++write_index;
        }

        *codeBytePos = codeByte;
        ++write_index;
        return write_index;
}

size_t cobs_ex::cobs_decode(const uint8_t *input, size_t length, uint8_t *output){
    size_t read_index = 0;
       size_t write_index = 0;
       uint8_t code;

       while(read_index < length)
       {
           code = input[read_index];

           if(read_index + code > length && code != 1)
           {
               return 0;
           }

           read_index++;

           uint8_t i;
           for(i = 1; i < code; i++)
           {
               output[write_index++] = input[read_index++];
           }

           if(code != 0xFF && read_index != length)
           {
               output[write_index++] = '\0';
           }
       }

       return write_index;
}
