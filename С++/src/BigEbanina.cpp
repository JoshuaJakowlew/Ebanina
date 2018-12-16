#include "BigEbanina.h"

namespace ebanina {
	void BigEbanina::create(uint64_t n)
	{
		if (n != mNumber) {
			mNumber = n;
			clearEbanina();
			prepareEbanina(n);
		}
	}

	void BigEbanina::create(std::string_view n, uint8_t base)
	{
		mpz_class x(n.data(), base);
		if (x != mNumber) {
			mNumber = x;
			clearEbanina();
			prepareEbanina(x);
		}
	}

	void BigEbanina::create(const std::vector<uintptr_t>& bits)
	{
		clearEbanina();
		mBits = bits;
		prepareEbanina(1);
	}

	void BigEbanina::create(mpz_class n)
	{
		if (n != mNumber) {
			mNumber = n;
			clearEbanina();
			prepareEbanina(n);
		}
	}

	void BigEbanina::free()
	{
		mEbanina.clear();
	}

	const std::string & BigEbanina::toString() const noexcept
	{
		return mEbanina;
	}

	void BigEbanina::toFile(std::string_view name) const
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

	const std::vector<uintptr_t>& BigEbanina::getBits() const
	{
		return mBits;
	}

	void BigEbanina::prepareEbanina(mpz_class n)
	{
		if (n == 0) mEbanina = "0";
		else createEbanina(n);
	}

	void BigEbanina::clearEbanina()
	{
		mEbanina.clear();
		mBits.clear();
	}

	void BigEbanina::createEbanina(mpz_class n)
	{
		if (mBits.empty())
		{
			size_t bitcnt = mpz_popcount(n.get_mpz_t());
			mBits.reserve(bitcnt);

			splitBits(mBits, n);
		}

		startThreads(mBits);
	}

	void BigEbanina::startThreads(std::vector<uintptr_t>& bits)
	{
		size_t hardware_concurrency = std::thread::hardware_concurrency();
		if (hardware_concurrency == 0) hardware_concurrency = 1;

		auto threads_count = std::min(bits.size(), hardware_concurrency);
		std::vector<std::thread> threads;
		threads.reserve(threads_count);

		//std::cout << "Starting threads. " << threads_count << " threads total (" << threads_count - 1 << " will be created)\n" << std::endl; // Remove

		size_t chunkSize = bits.size() / threads_count;
		for (size_t i = 0; i < threads_count - 1; ++i)
		{
			std::vector<uintptr_t> chunk(chunkSize);

			auto first = bits.begin() + chunkSize * i;
			auto last = first + chunkSize;
			std::copy(first, last, chunk.begin());

			threads.emplace_back([this, chunk] { threadFunc(chunk); });

			//std::cout << i + 1 << " thread started. thread id: " << threads[i].get_id() << "\n" << std::endl; // Remove
		}

		chunkSize = chunkSize + bits.size() % threads_count;
		std::vector<uintptr_t> chunk(chunkSize);

		auto first = bits.end() - chunkSize;
		auto last = bits.end();
		std::copy(first, last, chunk.begin());

		//std::cout << threads_count << " thread started (main). thread id: " << std::this_thread::get_id() << "\n" << std::endl; // Remove
		threadFunc(chunk);

		for (auto& t : threads)
		{
			t.join();
		}
	}

	void BigEbanina::threadFunc(std::vector<uintptr_t> bits)
	{
		// For last '|' symbol
		size_t maxEbaninaSize = bits.size();
		for (auto bit : bits)
			maxEbaninaSize += getMaxStringSize(bit) + 1;

		std::unique_ptr<std::string> localEbanina(new std::string());
		//localEbanina->reserve(maxEbaninaSize);

		for (auto bit : bits)
		{
			if (isMagicPower(bit)) appendMagicString(bit, localEbanina);
			else
			{
				localEbanina->append("-~0<<(");
				createLocalEbanina(bit, localEbanina);
				localEbanina->append(")");
			}

			localEbanina->append("|");
		}

		std::unique_lock<std::mutex> lock(mLock);

		//std::cout << "thread finished ebanina chunk calculation\n" << "Writing to big Ebanina\n" << "thread id: " << std::this_thread::get_id() << "\n" << std::endl; // Remove

		mEbanina.append(*localEbanina);

		//std::cout << "thread finished writing\nthread id: " << std::this_thread::get_id() << "\n" << std::endl; // Remove
	}

	void BigEbanina::createLocalEbanina(uintptr_t n, std::unique_ptr<std::string>& localEbanina)
	{
		static constexpr size_t maxBitsSize = (UINTPTR_MAX == UINT64_MAX) ? 64 : 32;

		std::vector<uint8_t> bits;
		bits.reserve(maxBitsSize);

		splitBits(bits, n);

		for (auto bit : bits)
		{
			if (isMagicPower(bit)) appendMagicString(bit, localEbanina);//localEbanina->append(getMagicString(bit));
			else
			{
				localEbanina->append("-~0<<(");
				createLocalEbanina(bit, localEbanina);
				localEbanina->append(")");
			}

			localEbanina->append("|");
		}

		localEbanina->pop_back();
	}
} // namespace ebanina