#pragma once
#include <cstdint>
#include <vector>
#include <fstream>

#include "IEbanina.h"

namespace ebanina {
	class SmallEbanina : public IEbanina
	{
	public:
		virtual void create(uint64_t n) override;
		virtual void create(std::string_view n, uint8_t base = 10) override;
		virtual void create(const std::vector<uintptr_t>& bits) override;

		virtual void free() override;

		virtual const std::string & toString() const noexcept override;
		virtual void toFile(std::string_view name) const override;

		virtual const std::vector<uintptr_t>& getBits() const override;
	private:
		uint64_t mNumber;
		std::string mEbanina;
		std::vector<uintptr_t> mBits;
	private:
		void prepareEbanina(uint64_t n);
		void clearEbanina();

		void createEbanina(uint64_t n);

		void splitBits(std::vector<uint8_t> & bits, uint64_t n);

		static bool isMagicPower(uint8_t power) noexcept;
		void appendMagicString(uint8_t power);

		static std::size_t getMaxStringSize(uint64_t n) noexcept;
		void reserveEbaninaString(uint64_t n);
	};
} // namespace ebanina