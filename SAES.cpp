#include "SAES.h"
#include <cmath>
#include <iostream>
#include "lib/aes.h"
#include "lib/aes.cpp"
#include <cstdlib>
#include <time.h>

SAES::~SAES() {
    delete[] blocks;
    delete iv;
}


// Transforms an arbitrary string into an character array
// With length being an exact multiple of 16
// Pads with extra zeros if required
void SAES::blockify(std::string data){

    uint8_t* keyarr = new uint8_t[data.length() - 1];

    double num = ceil((double)data.size() / 16);
    numblocks = (int)num;
    size = 16*numblocks;

    uint8_t* iv = new uint8_t[16];

    for (int i = 0; i<16; i++){
        iv[i] = (uint8_t)'a';
    }

    const uint8_t* iv2 = iv;

    blocks = new uint8_t[size];

    for (int i = 0; i < size; i++){
        if (i < data.length()){
            blocks[i] = (uint8_t)data[i];
        }
        else{
            blocks[i] = 0;
        }
    }
}


// Transforms an arbitrary key into a 16-length byte array
// Pads key with extra zeros if required
uint8_t* SAES::arrayKey(std::string key){
    uint8_t* keyarr = new uint8_t[16];


    for (int i = 0; i < 16; i++){
        if (i < key.length()){
            keyarr[i] = (uint8_t)key[i];
        }
        else {
            keyarr[i] = 0;
        }
    }

    return keyarr;
}

void SAES::encryptText(std::string key){

    const uint8_t* keyarr = arrayKey(key);
    AES128_CBC_encrypt_buffer16_ip(blocks, (uint8_t)size, keyarr, iv);

}

void SAES::decryptText(std::string key) {

    const uint8_t* keyarr = arrayKey(key);
    AES128_CBC_decrypt_buffer16_ip(blocks, (uint8_t)size, keyarr, iv);
}

void SAES::setiv(){

    // NOT SECURE! USES POOR RNG
    srand(time(NULL));
    try{
        delete[] iv;
        iv = NULL;
    }
    catch (int e){}

    iv = new uint8_t[16];

    for (int i = 0; i< 16; i++){
        iv[i] = (uint8_t)(rand() % 256);
    }
}
