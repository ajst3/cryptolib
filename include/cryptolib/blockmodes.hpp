/*! \defgroup Enumerations */
#ifndef BLOCKMODES
#define BLOCKMODES

/*! \ingroup Enumerations */
//*! Enum used to set the blockmode for cryptobase object */
enum blockmodes
{
  CBC, /*!< Cipher Block Chaining */
  CBC_PARALLEL /*!< Same as CBC, but decryption is parallel */
};

#endif
