#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <fstream>

#include <mpirxx.h>

class Ebanina
{
public:
	Ebanina(uint64_t n);
	Ebanina(uint64_t base, uint64_t power);
	Ebanina(mpz_class n);
	Ebanina(std::string_view s, uint32_t base = 10);
	~Ebanina();

	void create();
	std::string getString();
	void toFile(std::string_view filename);

private:
	mpz_class mNumber;
	std::string mEbanina;

	bool mCacheValid = false;
private:
	// Special version for the first call
	// Splits bits which are always fit in uint64_t
	// Create mpz_class every iteration is rather expensive
	std::string createEbanina(mpz_class x);
	std::string createEbanina(uint64_t x);

	static std::pair<bool, uint64_t> isMagicPower(uint64_t x) noexcept;

	static std::string makeMagicPowString(uint64_t power) noexcept;

	void calcBitsPosition(std::vector<uint64_t> & bits, mpz_class x) noexcept;
};
