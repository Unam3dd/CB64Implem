#include "base64.h"

uint64_t get_base64_padded_size(uint64_t len)
{
    return (((len | 2) / 3) << 2);
}

uint64_t get_ascii_size_from_base64(uint64_t len)
{
    return (((len) >> 2) * 3);
}

uint32_t base64_encode(char *buffer, char *output, uint64_t len_output_buffer)
{
    uint32_t bytes[3] = {0};
    uint64_t size_of_buffer = string_len(buffer);
    uint32_t sum = 0;
    uint32_t padding[3] = {0, 2, 1};
    uint64_t size_of_encoded = get_base64_padded_size(size_of_buffer);

    // check size of output buffer
    if (len_output_buffer < size_of_encoded)
        return (1);
    
    // takes three bytes of buffer and pushes them to the left with multiples of 8 
    // (because 8 bits make 1 byte) which means that one pushes on three bytes

    for (int i = 0, x = 0; i < size_of_buffer;)
    {
        bytes[0] = i < size_of_buffer ? (unsigned char) buffer[i++] : 0;
        bytes[1] = i < size_of_buffer ? (unsigned char) buffer[i++] : 0;
        bytes[2] = i < size_of_buffer ? (unsigned char) buffer[i++] : 0;

        // stores all the values of the 3 bytes (concat three bytes)
        sum = (bytes[0] << 0x10) | (bytes[1] << 0x8) | (bytes[2]);

        // we move the bits to the right in multiples of 6 because base64 uses 6 bits per character and we want 4 characters.
        
        output[x++] = BASE64_TABLE[(sum >> 0x12) & 0x3F]; // first
        output[x++] = BASE64_TABLE[(sum >> 0xc) & 0x3F]; // second
        output[x++] = BASE64_TABLE[(sum >> 0x6) & 0x3F]; // third
        output[x++] = BASE64_TABLE[(sum) & 0x3F]; // fourth
    }

    // Add padding
    
    for (int p = 0; p < padding[size_of_buffer % 3]; p++)
        output[(size_of_encoded - 1) - p] = '=';

    return (0);
}


uint32_t base64_decode(char *buffer, char *output, uint64_t len_output_buffer)
{
    // if ascii size is > than output buffer size
    if (get_ascii_size_from_base64(string_len(buffer)) > len_output_buffer)
        return (1); // return error
    
    uint32_t bytes[4] = {0}; // bytes in 
    uint64_t sum = {0};
    uint64_t size_of_buffer = string_len(buffer);
    uint64_t size_of_output_buffer = get_ascii_size_from_base64(string_len(buffer));

    // if size buffer is not multiple of 4

    if ((size_of_buffer % 4) != 0)
        return (1);
    
    if (DECODING_TABLE_IS_NULL)
        make_decoding_table(); // create decoding table
    
    // take four bytes in buffer, and reverse the encode method

    for (int i = 0, x = 0; i < size_of_buffer;) {
        bytes[0] = buffer[i] == '=' ? 0 & i++ : DECODING_TABLE[buffer[i++]];
        bytes[1] = buffer[i] == '=' ? 0 & i++ : DECODING_TABLE[buffer[i++]];
        bytes[2] = buffer[i] == '=' ? 0 & i++ : DECODING_TABLE[buffer[i++]];
        bytes[3] = buffer[i] == '=' ? 0 & i++ : DECODING_TABLE[buffer[i++]];
        
        // concat fourth bytes
        sum = (bytes[0] << 0x12) | (bytes[1] << 0xc) | (bytes[2] << 0x6) | (bytes[3]);

        output[x++] = (sum >> 0x10) & 0xFF; // first        
        output[x++] = (sum >> 0x8) & 0xFF; // second
        output[x++] = (sum) & 0xFF; // third
    }

    return (0);
}

void make_decoding_table(void)
{
    DECODING_TABLE = malloc(0x100); // allocate 256 bytes for the decoding table because max value of ascii table is 256

    for (int i = 0; i < 0x40; i++)
        DECODING_TABLE[(unsigned char) BASE64_TABLE[i]] = i; // example : A = 65, DECODING_TABLE[65] = 1;
}


void free_decoding_table(void)
{
    free(DECODING_TABLE); // free the memory block of decoding table
}

// fonction like strlen in string.h
unsigned int string_len(char *str)
{
    int i = 0;
    
    while (*(str)++)
        i++;
    
    return (i);
}
