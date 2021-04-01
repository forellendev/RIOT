#ifndef AES_DRIVER_H
#define AES_DRIVER_H


#include "../../device/avr_compiler.h"

/* Length of one block. Always 128-bits (16 bytes). */
#define AES_BLOCK_LENGTH 16



/* Definitions of macros */

/*! \brief  This macro enable AES module encryption mode. */
#define AES_encryption_mode_set()   ( AES.CTRL = AES.CTRL & (~AES_DECRYPT_bm) )

/*! \brief  This macro enable AES module decryption mode. */
#define AES_decryption_mode_set()   ( AES.CTRL |= AES_DECRYPT_bm )

/*! \brief  This macro enable the auto start feature in the AES module. */
#define AES_auto_enable()           ( AES.CTRL |= AES_AUTO_bm )

/*! \brief  This macro disable the auto start feature in the AES module. */
#define AES_auto_disable()          ( AES.CTRL = AES.CTRL & (~AES_AUTO_bm) )

/*! \brief  This macro enable the xor feature in the AES module. */
#define AES_xor_enable()            ( AES.CTRL |= AES_XOR_bm )

/*! \brief  This macro disable the xor feature in the AES module. */
#define AES_xor_disable()           ( AES.CTRL = AES.CTRL & (~AES_XOR_bm) )

/*! \brief  This macro resets all registers in AES module. */
#define AES_software_reset()        ( AES.CTRL = AES_RESET_bm )

/*! \brief  This macro starts a decryption/encryption. */
#define AES_start()                 ( AES.CTRL |= AES_START_bm )

/*! \brief  This macro checks if AES state ready interrupt flag is set.
 *
 *   \retval true  if State Ready interrupt flag is set.
 *   \retval false if State Ready interrupt flag is not set.
 */
#define AES_state_ready_flag_check()((AES.STATUS & AES_SRIF_bm) != 0)

/*! \brief  This macro checks if the error flag is set.
 *
 *  \retval true  if AES Error flag is set.
 *  \retval false if AES Error flag not set.
 */
#define AES_error_flag_check()    ((AES.STATUS & AES_ERROR_bm) != 0)


/* Prototyping of Polled driver functions */
bool AES_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key);
bool AES_encrypt_backtoback(uint8_t * plaintext, uint8_t * ciphertext);
bool AES_decrypt(uint8_t * ciphertext, uint8_t * plaintext, uint8_t * key);
#endif
