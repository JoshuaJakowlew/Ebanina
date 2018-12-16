#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace ebanina {
	class IEbanina
	{
	public:
		virtual ~IEbanina() = 0 {};

		virtual void create(uint64_t n) = 0;
		virtual void create(std::string_view n, uint8_t base = 10) = 0;
		virtual void create(const std::vector<uintptr_t>& bits) = 0;
		virtual void free() = 0;
		virtual const std::string & toString() const noexcept = 0;
		virtual void toFile(std::string_view name) const = 0;
		virtual const std::vector<uintptr_t>& getBits() const = 0;
	private:

	};
} // namespace ebanina