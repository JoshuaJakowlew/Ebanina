#include "SmallEbanina.h"

namespace ebanina {
	void SmallEbanina::create(uint64_t n)
	{
		if (n != mNumber) {
			mNumber = n;
			clearEbanina();
			prepareEbanina(n);
		}
	}

	void SmallEbanina::create(std::string_view n, uint8_t base)
	{
		uint64_t x = std::stoull(n.data(), nullptr, int{ base });
		if (x != mNumber) {
			mNumber = x;
			clearEbanina();
			prepareEbanina(x);
		}
	}

	void SmallEbanina::create(const std::vector<uintptr_t>& bits)
	{
		clearEbanina();
		mBits = bits;
		prepareEbanina(1);
	}

	void SmallEbanina::free()
	{
		mEbanina.clear();
	}

	void SmallEbanina::toFile(std::string_view name) const
	{
		std::ofstream fout(name.data());
		if (!fout.is_open())
		{
			fout.close();
			throw std::runtime_error("Can't open file");
		}

		fout << mEbanina;
		fout.close();
	}

	const std::vector<uintptr_t>& SmallEbanina::getBits() const
	{
		return mBits;
	}

	const std::string & SmallEbanina::toString() const noexcept
	{
		return mEbanina;
	}


	void SmallEbanina::prepareEbanina(uint64_t n)
	{
		if (n == 0) mEbanina = "0";
		else
		{
			reserveEbaninaString(mNumber);
			createEbanina(mNumber);
		}
	}

	void SmallEbanina::clearEbanina()
	{
		mEbanina.clear();
	}

	void SmallEbanina::createEbanina(uint64_t n)
	{
		std::vector<uint8_t> bits;
		bits.reserve(64);

		splitBits(bits, n);

		for (auto bit : bits)
		{
			if (isMagicPower(bit)) appendMagicString(bit);
			else
			{
				mEbanina.append("-~0<<(");
				createEbanina(bit);
				mEbanina.append(")");
			}

			mEbanina.append("|");
		}
		mEbanina.pop_back();
	}

	void SmallEbanina::splitBits(std::vector<uint8_t> & bits, uint64_t n)
	{
		uint8_t maxIter = static_cast<uint8_t>(log2(n));
		for (uint8_t i = 0; i <= maxIter; ++i)
		{
			if (n & (1ull << i)) bits.emplace_back(i);
		}
	}

	bool SmallEbanina::isMagicPower(uint8_t power) noexcept
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

	void SmallEbanina::appendMagicString(uint8_t power)
	{
		if (power == 0)				mEbanina.append("-~0");
		else if (power == 1)		mEbanina.append("-~0<<-~0");
		else if (power == 2)		mEbanina.append("-~0<<(-~0<<-~0)");
		else if (power == 4)		mEbanina.append("-~0<<(-~0<<(-~0<<-~0))");
		else if (power == 16)		mEbanina.append("-~0<<(-~0<<(-~0<<(-~0<<-~0)))");
		else if (power == 65535)	mEbanina.append("-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))");
	}

	std::size_t SmallEbanina::getMaxStringSize(uint64_t n) noexcept
	{
		if (n < 255)					return 166;	 // 2^8 - 1
		if (n < 65535)					return 498;	 // 2^16 - 1
		if (n < 16777215)				return 854;	 // 2^24 - 1
		if (n < 2147483647)				return 1291; // 2^31 - 1
		if (n < 4294967295)				return 1370; // 2^32 - 1
		if (n < 1099511627775)			return 1758; // 2^40 - 1
		if (n < 281474976710655)		return 2306; // 2^48 - 1
		if (n < 72057594037927935)		return 2878; // 2^56 - 1
		if (n < 18446744073709551615)	return 3649; // 2^64 - 1
		else							return 3649; // This branch will never be selected. Just for safety.
	}

	void SmallEbanina::reserveEbaninaString(uint64_t n)
	{
		mEbanina.reserve(getMaxStringSize(n));
	}
}