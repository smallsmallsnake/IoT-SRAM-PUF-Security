#ifndef AES_H
#define AES_H

#include <stdint.h>


#define AES_KEY_SIZE_128 16
#define AES_KEY_SIZE_192 24
#define AES_KEY_SIZE_256 32
#define AES_BLOCK_SIZE   16

typedef struct {
    uint32_t eK[60];
    uint32_t dK[60];
    uint_fast32_t Nr;
} AesContext;

int AesInitialise(AesContext *Context, void const *Key, uint32_t KeySize);

void AesEncrypt(AesContext const *Context, uint8_t const Input[AES_BLOCK_SIZE],
                uint8_t Output[AES_BLOCK_SIZE]);

void AesDecrypt(AesContext const *Context, uint8_t const Input[AES_BLOCK_SIZE],
                uint8_t Output[AES_BLOCK_SIZE]);

void AesEncryptInPlace(AesContext const *Context,
                       uint8_t Block[AES_BLOCK_SIZE]);

void AesDecryptInPlace(AesContext const *Context,
                       uint8_t Block[AES_BLOCK_SIZE]);

#endif // AES_H
