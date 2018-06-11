#include "Ebanina.h"

Ebanina::Ebanina(uint64_t n) : mNumber(n) {}

Ebanina::Ebanina(uint64_t base, uint64_t power)
{
	mpz_pow_ui(mNumber.get_mpz_t(), mpz_class(base).get_mpz_t(), power);
}

Ebanina::Ebanina(mpz_class n) : mNumber(n) {}

Ebanina::Ebanina(std::string_view s, uint32_t base) : mNumber(s.data(), base) {}

Ebanina::~Ebanina() {}


void Ebanina::create()
{
	if(!mCacheValid) mEbanina = createEbanina(mNumber);
	mCacheValid = true;
}

std::string Ebanina::getString()
{
	if (mCacheValid) return mEbanina;
	throw std::logic_error("Cache is not valid");
}

void Ebanina::toFile(std::string_view filename)
{
	if(!mCacheValid) throw std::logic_error("Cache is not valid");

	std::ofstream file(filename.data());
	if (!file.is_open()) throw std::runtime_error("Wrong file name");

	file << mEbanina;
	file.close();
}


std::string Ebanina::createEbanina(mpz_class x)
{
	if (x == 0) return "0";

	std::vector<uint64_t> bits;
	calcBitsPosition(bits, x);

	std::string ebanina;
	for (auto bit : bits)
	{
		auto[isMagic, power] = isMagicPower(bit);

		if (isMagic) ebanina += makeMagicPowString(power);
		else ebanina += "-~0<<(" + createEbanina(bit) + ")";

		if (bit != bits.back()) ebanina += "|";
	}

	return ebanina;
}

std::string Ebanina::createEbanina(uint64_t x)
{
	if (x == 0) return "0";

	std::vector<uint64_t> bits;
	calcBitsPosition(bits, x);

	std::string ebanina;
	for (auto bit : bits)
	{
		auto[isMagic, power] = isMagicPower(bit);

		if (isMagic) ebanina += makeMagicPowString(power);
		else ebanina += "-~0<<(" + createEbanina(bit) + ")";

		if (bit != bits.back()) ebanina += "|";
	}

	return ebanina;
}

std::pair<bool, uint64_t> Ebanina::isMagicPower(uint64_t x) noexcept
{
	switch (x)
	{
	case 0:		return std::make_pair(true, 0);
	case 1:		return std::make_pair(true, 1);
	case 2:		return std::make_pair(true, 2);
	case 4:		return std::make_pair(true, 4);
	case 16:	return std::make_pair(true, 16);
	case 65536: return std::make_pair(true, 65536);
	default:	return std::make_pair(false, 0);
	}
}

std::string Ebanina::makeMagicPowString(uint64_t power) noexcept
{
	switch (power)
	{
	case 0:		return "-~0";
	case 1:		return "-~0<<-~0";
	case 2:		return "-~0<<(-~0<<-~0)";
	case 4:		return "-~0<<(-~0<<(-~0<<-~0))";
	case 16:	return "-~0<<(-~0<<(-~0<<(-~0<<-~0)))";
	case 65536: return "-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))";
	}
}

void Ebanina::calcBitsPosition(std::vector<uint64_t>& bits, mpz_class x) noexcept
{
	uint64_t pos = 0;
	while (true)
	{
		pos = mpz_scan1(x.get_mpz_t(), pos);
		if (pos == __GMP_BITCNT_MAX) break;
		bits.push_back(pos);
		++pos;
	}

	// Init: pos++ must be 0 && pos != __GMP_BITCNT_MAX
	/*uint64_t pos = UINT64_MAX;
	while (pos++ != __GMP_BITCNT_MAX)
	{
		pos = mpz_scan1(x.get_mpz_t(), pos);
		bits.push_back(pos);
	}
	bits.pop_back();*/
}
