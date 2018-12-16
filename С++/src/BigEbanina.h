#pragma once
#include <cstdint>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <iostream>

#include <mpirxx.h>

#include "utility.h"
#include "IEbanina.h"

namespace ebanina {
	class BigEbanina : public IEbanina
	{
	public:
		virtual void create(uint64_t n) override;
		virtual void create(std::string_view n, uint8_t base = 10) override;
		virtual void create(const std::vector<uintptr_t>& bits) override;
		virtual void create(mpz_class n);

		virtual void free() override;

		virtual const std::string & toString() const noexcept override;
		virtual void toFile(std::string_view name) const override;

		virtual const std::vector<uintptr_t>& getBits() const override;
	private:
		mpz_class mNumber;
		std::string mEbanina;
		std::vector<uintptr_t> mBits;
		std::mutex mLock;
	private:
		void prepareEbanina(mpz_class n);
		void clearEbanina();

		void createEbanina(mpz_class n);

		void startThreads(std::vector<uintptr_t> & bits);
		void threadFunc(std::vector<uintptr_t> bits);

		void createLocalEbanina(uintptr_t n, std::unique_ptr<std::string>& localEbanina);
	};
} // namespace ebanina