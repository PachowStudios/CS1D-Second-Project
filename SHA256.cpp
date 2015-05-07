#include "SHA256.h"

const uint32 SHA256::sha256_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

QString SHA256::Hash(QString input, QString salt)
{
	return QString::fromStdString(Hash(input.toStdString(), salt.toStdString()));
}

string SHA256::Hash(string input, string salt)
{
	SHA256 sha256;
	uint8 digest[digestSize];

	salt = (salt == "") ? GenerateSalt(saltSize) : salt;
	memset(digest, 0, digestSize);
	sha256.Update((uint8*)input.c_str(), input.length());
	sha256.Update((uint8*)salt.c_str(), salt.length());
	sha256.Final(digest);

	char buffer[2 * digestSize + 1];
	buffer[2 * digestSize] = 0;

	for (int i = 0; i < digestSize; i++)
		sprintf(buffer + i * 2, "%02x", digest[i]);

	return salt + string(buffer);
}

bool SHA256::CompareHash(QString input, QString hash)
{
	return CompareHash(input.toStdString(), hash.toStdString());
}

bool SHA256::CompareHash(string input, string hash)
{
	string salt;

	for (int i = 0; i < saltSize; i++)
		salt += hash[i];

	return Hash(input, salt) == hash;
}

SHA256::SHA256()
	: length(0), totalLength(0)
{
	srand(time(NULL) ^ getpid());

	sha256_h[0] = 0x6a09e667;
	sha256_h[1] = 0xbb67ae85;
	sha256_h[2] = 0x3c6ef372;
	sha256_h[3] = 0xa54ff53a;
	sha256_h[4] = 0x510e527f;
	sha256_h[5] = 0x9b05688c;
	sha256_h[6] = 0x1f83d9ab;
	sha256_h[7] = 0x5be0cd19;
}

void SHA256::Update(const uint8 *message, uint32 updateLength)
{
	const uint8 *shiftedMessage;
	uint32 updateBlock;
	uint32 newLength, remLength, tempLength;

	tempLength = blockSize - length;
	remLength = (updateLength < tempLength) ? updateLength : tempLength;
	memcpy(&block[length], message, remLength);

	if (length + updateLength < blockSize)
	{
		length += updateLength;
	}
	else
	{
		newLength = updateLength - remLength;
		updateBlock = newLength / blockSize;
		shiftedMessage = message + remLength;
		Transform(block, 1);
		Transform(shiftedMessage, updateBlock);
		remLength = newLength % blockSize;
		memcpy(block, &shiftedMessage[updateBlock << 6], remLength);
		length = remLength;
		totalLength += (updateBlock + 1) << 6;
	}
}

void SHA256::Final(uint8 *digest)
{
	uint32 currentBlock;
	uint32 blockLength;
	uint32 pmLength;

	currentBlock = (1 + ((blockSize - 9) < (length % blockSize)));
	blockLength = (totalLength + length) << 3;
	pmLength = currentBlock << 6;
	memset(block + length, 0, pmLength - length);
	block[length] = 0x80;
	SHA2_UNPACK32(blockLength, block + pmLength - 4);
	Transform(block, currentBlock);

	for (int i = 0; i < 8; i++)
		SHA2_UNPACK32(sha256_h[i], &digest[i << 2]);
}

void SHA256::Transform(const uint8 *message, uint32 transformBlock)
{
	const uint8 *subBlock;
	uint32 w[64];
	uint32 wv[8];
	uint32 t1, t2;
	int i, j;

	for (i = 0; i < (int)transformBlock; i++)
	{
		subBlock = message + (i << 6);

		for (j = 0; j < 16; j++)
			SHA2_PACK32(&subBlock[j << 2], &w[j]);

		for (j = 16; j < 64; j++)
			w[j] = SHA256_F4(w[j - 2]) + w[j - 7]
			+ SHA256_F3(w[j - 15]) + w[j - 16];

		for (j = 0; j < 8; j++)
			wv[j] = sha256_h[j];

		for (j = 0; j < 64; j++)
		{
			t1 = SHA256_F2(wv[4])
				+ SHA2_CH(wv[4], wv[5], wv[6])
				+ sha256_k[j] + w[j] + wv[7];

			t2 = SHA256_F1(wv[0])
				+ SHA2_MAJ(wv[0], wv[1], wv[2]);

			wv[7] = wv[6];
			wv[6] = wv[5];
			wv[5] = wv[4];
			wv[4] = wv[3] + t1;
			wv[3] = wv[2];
			wv[2] = wv[1];
			wv[1] = wv[0];
			wv[0] = t1 + t2;
		}

		for (j = 0; j < 8; j++)
			sha256_h[j] += wv[j];
	}
}

string SHA256::GenerateSalt(const int length)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string salt;

	for (int i = 0; i < length; i++)
		salt += alphanum[rand() % (sizeof(alphanum) - 1)];

	return salt;
}