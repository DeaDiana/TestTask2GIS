#include <fstream>
#include "Checker.h"

#define BUFFER_SZ 1024
#define CHKSUM_SZ 4
#define FSTBIT 0
#define SNDBIT 1
#define TRDBIT 2
#define FORBIT 3

Checker::Checker(void) {
}

Checker::~Checker(void) {
}

std::string Checker::countCheckSum(const std::string &filename) {
	std::ifstream in(filename, std::ios_base::binary | std::ios_base::in);
	char fbuffer [BUFFER_SZ] = { 0 };
	char sbuffer [BUFFER_SZ] = { 0 };
	int rnum = 0;
	int rfnum = 0;
	in.read (fbuffer, BUFFER_SZ);
	rfnum = in.gcount();
//	in case file is too short
	if (CHKSUM_SZ >= rfnum) {
		fbuffer[CHKSUM_SZ] = '\0';
		return fbuffer;
	}
//	if file is bigger than BUFFER_SZ
	while (BUFFER_SZ == in.gcount()) {
		in.read (sbuffer, BUFFER_SZ);
		rnum = in.gcount();
		for(int i = 0; i < rnum; i++) {
			fbuffer[i] ^= sbuffer[i];
		}
	};
//	count check sum of buffer
	for (int i = 1; i < rfnum / CHKSUM_SZ; i++) {
		fbuffer[FSTBIT] ^= fbuffer[CHKSUM_SZ * i + FSTBIT];
		fbuffer[SNDBIT] ^= fbuffer[CHKSUM_SZ * i + SNDBIT];
		fbuffer[TRDBIT] ^= fbuffer[CHKSUM_SZ * i + TRDBIT];
		fbuffer[FORBIT] ^= fbuffer[CHKSUM_SZ * i + FORBIT];
	}
//	take into account the 'tail'
//	if the real size of buffer is less than BUFFER_SZ
//	but is not multiple of CHKSUM_SZ
	int tail_start = rfnum - rfnum % CHKSUM_SZ;
	for (int i = 0; i < rfnum % CHKSUM_SZ; i++) {
		fbuffer[i] ^= fbuffer[tail_start + i];
	}
	fbuffer[CHKSUM_SZ] = '\0';
	return fbuffer;
}