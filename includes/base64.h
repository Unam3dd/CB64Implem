#pragma once
#include <stdlib.h>
#include <stdint.h>

#define DECODING_TABLE_IS_NULL (DECODING_TABLE == NULL)

static char BASE64_TABLE[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static unsigned char *DECODING_TABLE = NULL;

uint64_t get_base64_padded_size(uint64_t len);
uint64_t get_ascii_size_from_base64(uint64_t len);
uint32_t base64_encode(char *buffer, char *output, uint64_t len_output_buffer);
uint32_t base64_decode(char *buffer, char *output, uint64_t len_output_buffer);
void make_decoding_table(void);
void free_decoding_table(void);
unsigned int string_len(char *str);