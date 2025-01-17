#pragma once

#include <inttypes.h>

namespace TTH
{
namespace Blowfish
{

/**
 * @brief Decrypts an 8 byte block of data using blowfish
 *
 * @param input Encrypted data
 * @return Decrypted data
 */
uint64_t DecryptBlock(uint64_t input);

/**
 * @brief Encrypts an 8 byte block of data using blowfish
 *
 * @param input Decrypted data
 * @return Encrypted data
 */
uint64_t EncryptBlock(uint64_t input);

}; // namespace Blowfish
}; // namespace TTH