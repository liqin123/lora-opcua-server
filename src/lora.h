#ifndef SRC_LORA_H_
#define SRC_LORA_H_

#include <stdint.h>

typedef struct {
	unsigned char DevAddr[4];
	unsigned char FCtrl;
	unsigned char FCnt[2];
	unsigned char FOpts[15];
} Fhdr;

typedef struct {
	Fhdr FHDR;
	unsigned char FPort;
	unsigned char FRMPayload[250]; /* Maximum allowed for Datarate 7 */
	unsigned char FRMPayloadLen;
} MacPayload;

/**
 * C Struct representation of a PHYPayload package as
 * specified in the LoraWan specification.
 *
 */
typedef struct {
	unsigned char MHDR;
	MacPayload MACPayload;
	unsigned char MIC[4];
} PhyPayload;

typedef enum { UPLINK = 0, DOWNLINK = 1 } LoraDir;

/**
 * Decrypt the FRMPayload in the given PhyPayload structure.
 * Decryption is done in place, so the FRMPayLoad field of phy_payload
 * will contain the plaintext payload
 *
 * @param	phy_payload	Pointer to PhyPayload whose FRMPayload needs to be decrypted
 * @param	aesKey		AES key for decryption
 *
 * @return 	Nonzero on success, zero on failure
 */
int decrypt_frmpayload(PhyPayload * phy_payload, const unsigned char * aesKey);
/*
 * Map the raw binary representation of the PHY payload onto a C structure
 *
 * @param phy_payload 		Pointer to caller allocated structure
 * @param raw_payload 		Pointer to buffer containing raw_payload
 * @param raw_payload_size	Size of the raw_payload buffer in bytes
 */
int phypayload_parse(PhyPayload * phy_payload, unsigned char * raw_payload, size_t raw_payload_size);

uint32_t compute_mic(uint8_t * data, size_t data_len, const unsigned char * aesKey, LoraDir direction);


#endif /* SRC_LORA_H_ */
