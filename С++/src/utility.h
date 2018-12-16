#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include <mpirxx.h>

namespace ebanina {
	void splitBits(std::vector<uintptr_t>& bits, mpz_class n);
	void splitBits(std::vector<uint8_t>& bits, uint64_t n);

	bool isMagicPower(uint8_t power) noexcept;

	size_t getMaxStringSize(uint64_t n) noexcept;
	std::string getMagicString(uint8_t power);

	void appendMagicString(uint8_t power, std::unique_ptr<std::string>& localEbanina);
} // namespace ebanina