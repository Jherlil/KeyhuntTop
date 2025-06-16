SIMD ?= auto
ifeq ($(SIMD),auto)
SIMD_FLAG := $(shell if grep -q avx2 /proc/cpuinfo; then echo -mavx2; \
	             elif grep -q sse4_1 /proc/cpuinfo; then echo -msse4.1; \
	             else echo -mssse3; fi)
else ifeq ($(SIMD),avx2)
SIMD_FLAG := -mavx2
else ifeq ($(SIMD),sse4)
SIMD_FLAG := -msse4.1
else
SIMD_FLAG := -mssse3
endif

CXXFLAGS := -m64 -march=native -mtune=native $(SIMD_FLAG) -Wall -Wextra -Wno-deprecated-copy -Ofast -ftree-vectorize
CFLAGS   := -m64 -march=native -mtune=native $(SIMD_FLAG) -Wall -Wextra -Wno-unused-parameter -Ofast -ftree-vectorize

default:
	g++ $(CXXFLAGS) -flto -c oldbloom/bloom.cpp -o oldbloom.o
	g++ $(CXXFLAGS) -flto -c bloom/bloom.cpp -o bloom.o
	gcc $(CFLAGS) -c base58/base58.c -o base58.o
	gcc $(CFLAGS) -c rmd160/rmd160.c -o rmd160.o
	g++ $(CXXFLAGS) -c sha3/sha3.c -o sha3.o
	g++ $(CXXFLAGS) -c sha3/keccak.c -o keccak.o
	gcc $(CFLAGS) -c xxhash/xxhash.c -o xxhash.o
	g++ $(CXXFLAGS) -c util.c -o util.o
	g++ $(CXXFLAGS) -c secp256k1/Int.cpp -o Int.o
	g++ $(CXXFLAGS) -c secp256k1/Point.cpp -o Point.o
	g++ $(CXXFLAGS) -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ $(CXXFLAGS) -c secp256k1/IntMod.cpp -o IntMod.o
	g++ $(CXXFLAGS) -flto -c secp256k1/Random.cpp -o Random.o
	g++ $(CXXFLAGS) -flto -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ $(CXXFLAGS) -flto -c hash/ripemd160.cpp -o hash/ripemd160.o
	g++ $(CXXFLAGS) -flto -c hash/sha256.cpp -o hash/sha256.o
	g++ $(CXXFLAGS) -flto -c hash/ripemd160_sse.cpp -o hash/ripemd160_sse.o
	g++ $(CXXFLAGS) -flto -c hash/sha256_sse.cpp -o hash/sha256_sse.o
	g++ $(CXXFLAGS) -o keyhunt keyhunt.cpp base58.o rmd160.o hash/ripemd160.o hash/ripemd160_sse.o hash/sha256.o hash/sha256_sse.o bloom.o oldbloom.o xxhash.o util.o Int.o Point.o SECP256K1.o IntMod.o Random.o IntGroup.o sha3.o keccak.o -lm -lpthread
	rm -r *.o
clean:
	rm keyhunt
legacy:
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -flto -c oldbloom/bloom.cpp -o oldbloom.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -flto -c bloom/bloom.cpp -o bloom.o
	gcc -march=native -mtune=native -Wno-unused-result -Ofast -ftree-vectorize -c base58/base58.c -o base58.o
	gcc -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c xxhash/xxhash.c -o xxhash.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c util.c -o util.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c sha3/sha3.c -o sha3.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c sha3/keccak.c -o keccak.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c hashing.c -o hashing.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c gmp256k1/Int.cpp -o Int.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c gmp256k1/Point.cpp -o Point.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c gmp256k1/GMP256K1.cpp -o GMP256K1.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -c gmp256k1/IntMod.cpp -o IntMod.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -flto -c gmp256k1/Random.cpp -o Random.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -flto -c gmp256k1/IntGroup.cpp -o IntGroup.o
	g++ -march=native -mtune=native -Wall -Wextra -Ofast -ftree-vectorize -o keyhunt keyhunt_legacy.cpp base58.o bloom.o oldbloom.o xxhash.o util.o Int.o  Point.o GMP256K1.o  IntMod.o  IntGroup.o Random.o hashing.o sha3.o keccak.o -lm -lpthread -lcrypto -lgmp	
	rm -r *.o
bsgsd:
	g++ $(CXXFLAGS) -flto -c oldbloom/bloom.cpp -o oldbloom.o
	g++ $(CXXFLAGS) -flto -c bloom/bloom.cpp -o bloom.o
	gcc $(CFLAGS) -c base58/base58.c -o base58.o
	gcc $(CFLAGS) -c rmd160/rmd160.c -o rmd160.o
	g++ $(CXXFLAGS) -c sha3/sha3.c -o sha3.o
	g++ $(CXXFLAGS) -c sha3/keccak.c -o keccak.o
	gcc $(CFLAGS) -c xxhash/xxhash.c -o xxhash.o
	g++ $(CXXFLAGS) -c util.c -o util.o
	g++ $(CXXFLAGS) -c secp256k1/Int.cpp -o Int.o
	g++ $(CXXFLAGS) -c secp256k1/Point.cpp -o Point.o
	g++ $(CXXFLAGS) -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ $(CXXFLAGS) -c secp256k1/IntMod.cpp -o IntMod.o
	g++ $(CXXFLAGS) -flto -c secp256k1/Random.cpp -o Random.o
	g++ $(CXXFLAGS) -flto -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ $(CXXFLAGS) -flto -c hash/ripemd160.cpp -o hash/ripemd160.o
	g++ $(CXXFLAGS) -flto -c hash/sha256.cpp -o hash/sha256.o
	g++ $(CXXFLAGS) -flto -c hash/ripemd160_sse.cpp -o hash/ripemd160_sse.o
	g++ $(CXXFLAGS) -flto -c hash/sha256_sse.cpp -o hash/sha256_sse.o
	g++ $(CXXFLAGS) -ftree-vectorize -o bsgsd bsgsd.cpp base58.o rmd160.o hash/ripemd160.o hash/ripemd160_sse.o hash/sha256.o hash/sha256_sse.o bloom.o oldbloom.o xxhash.o util.o Int.o Point.o SECP256K1.o IntMod.o Random.o IntGroup.o sha3.o keccak.o -lm -lpthread
	rm -r *.o
