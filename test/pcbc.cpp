#include <stdint.h>
#include <iostream>
#include <cassert>

#include "test.h"
#include "../src/crypter.h"

void Tests::test_pcbc(void) {
  std::cout << "Testing PCBC: \n";

  uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
  uint8_t in[]  = { 0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
                    0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
                    0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
                    0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7 };
  uint8_t* input_data = &in[0];
  size_t* data_len = new size_t(64);

  uint8_t* encrypted_data = Crypter::PCBC_encrypt(input_data, data_len, (char*) &key[0]);

  assert(*data_len == 96); // IV + 64 data + CRC + padding

  uint8_t same_key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
  uint8_t* plaintext_data = Crypter::PCBC_decrypt(encrypted_data, data_len, (char*) &same_key[0]);


  assert(*data_len == 64);
  uint8_t expected[] = {0x76, 0x49, 0xab, 0xac, 0x81, 0x19};
  assert(0 == strncmp((char*)expected, (char*)plaintext_data, 6));
  std::cout << "PCBC Tests Passed\n\n";
}


