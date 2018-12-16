#include "utility.h"

namespace ebanina {
	void splitBits(std::vector<uintptr_t>& bits, mpz_class n)
	{
		uintptr_t pos = 0;
		while (true)
		{
			pos = mpz_scan1(n.get_mpz_t(), pos);
			if (pos == __GMP_BITCNT_MAX) break;
			bits.emplace_back(pos);
			++pos;
		}
	}

	void splitBits(std::vector<uint8_t>& bits, uint64_t n)
	{
		uint8_t maxIter = static_cast<uint8_t>(log2(n));
		for (uint8_t i = 0; i <= maxIter; ++i)
		{
			if (n & (1ull << i)) bits.emplace_back(i);
		}
	}

	bool isMagicPower(uint8_t power) noexcept
	{
		switch (power)
		{
		case 0:		return true;
		case 1:		return true;
		case 2:		return true;
		case 4:		return true;
		case 16:	return true;
		case 65536: return true;
		default:	return false;
		}
	}

	size_t getMaxStringSize(uint64_t n) noexcept
	{
		if (n == 1)		return 3;
		if (n == 2)		return 8;
		if (n == 3)		return 12;
		if (n == 4)		return 15;
		if (n == 5)		return 19;
		if (n == 6)		return 24;
		if (n == 7)		return 28;
		if (n == 8)		return 19;
		if (n == 9)		return 21;
		if (n == 10)	return 28;
		if (n == 11)	return 32;
		if (n == 12)	return 35;
		if (n == 13)	return 39;
		if (n == 14)	return 44;
		if (n == 15)	return 49;
		if (n == 16)	return 22;

		if (n < 1ull << 5)				return 71;
		if (n < 1ull << 6)				return 98;
		if (n < 1ull << 7)				return 130;
		if (n < 1ull << 8)				return 166;
		if (n < 1ull << 9)				return 193;
		if (n < 1ull << 10)				return 224;
		if (n < 1ull << 11)				return 260;
		if (n < 1ull << 12)				return 300;
		if (n < 1ull << 13)				return 343;
		if (n < 1ull << 14)				return 390;
		if (n < 1ull << 15)				return 442;
		if (n < 1ull << 16)				return 498;

		if (n < 1ull << 24)				return 854;
		if (n < 1ull << 31)				return 1291;
		if (n < 1ull << 32)				return 1370;
		if (n < 1ull << 40)				return 1758;
		if (n < 1ull << 48)				return 2306;
		if (n < 1ull << 56)				return 2878;
		if (n < 18446744073709551615)	return 3649; // 2^64 - 1

		return 0; // This branch will never be selected. Just for safety.
	}

	std::string getMagicString(uint8_t power)
	{
		if (power == 0)				return std::string("-~0");
		else if (power == 1)		return std::string("-~0<<-~0");
		else if (power == 2)		return std::string("-~0<<(-~0<<-~0)");
		else if (power == 4)		return std::string("-~0<<(-~0<<(-~0<<-~0))");
		else if (power == 16)		return std::string("-~0<<(-~0<<(-~0<<(-~0<<-~0)))");
		else if (power == 65535)	return std::string("-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))");
	}

	void appendMagicString(uint8_t power, std::unique_ptr<std::string>& localEbanina)
	{
		if (power == 0)				localEbanina->append("-~0");
		else if (power == 1)		localEbanina->append("-~0<<-~0");
		else if (power == 2)		localEbanina->append("-~0<<(-~0<<-~0)");
		else if (power == 4)		localEbanina->append("-~0<<(-~0<<(-~0<<-~0))");
		else if (power == 16)		localEbanina->append("-~0<<(-~0<<(-~0<<(-~0<<-~0)))");
		else if (power == 65535)	localEbanina->append("-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))");
	}
}