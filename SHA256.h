#ifndef SHA256_H
#define SHA256_H

#define _CRT_SECURE_NO_WARNINGS

#include <QString>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <process.h>

using std::string;

typedef unsigned char      uint8;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

class SHA256
{
public:
	static QString Hash(QString input, QString salt = "");
	static string  Hash(string  input, string  salt = "");
	static bool    CompareHash(QString input, QString hash);
	static bool    CompareHash(string  input, string  hash);

private:
	SHA256();

	void Update(const uint8 *message, uint32 length);
	void Final(uint8 *digest);
	void Transform(const uint8 *message, uint32 block);

	static string GenerateSalt(const int length);

	static const uint32 sha256_k[];
	static const uint32 blockSize = 64;
	static const uint32 digestSize = 32;
	static const uint32 saltSize = 16;

	uint8  block[2 * blockSize];
	uint32 sha256_h[8];
	uint32 length;
	uint32 totalLength;
};

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)          \
{                                      \
	*((str) + 3) = (uint8)((x));       \
	*((str) + 2) = (uint8)((x) >>  8); \
	*((str) + 1) = (uint8)((x) >> 16); \
	*((str) + 0) = (uint8)((x) >> 24); \
}
#define SHA2_PACK32(str, x)              \
{                                        \
	*(x) = ((uint32)*((str) + 3))        \
	     | ((uint32)*((str) + 2) <<  8)  \
	     | ((uint32)*((str) + 1) << 16)  \
	     | ((uint32)*((str) + 0) << 24); \
}

#endif