#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <utility>

using namespace std;

string createEbanina(uint64_t x);

void setBitsOffset(vector<uint64_t> & bits, uint64_t x);
string makeMagicPowString(uint64_t power);
pair<bool, uint64_t> isMagicPower(uint64_t x);

int main()
{
	uint64_t n;
	cin >> n;
	cout << createEbanina(n) << endl;
}

string createEbanina(uint64_t x)
{
	if (x == 0) return "0";

	vector<uint64_t> bits;
	setBitsOffset(bits, x);

	string ebanina;
	for (auto bit : bits)
	{
		auto[isMagic, power] = isMagicPower(bit);

		if (isMagic) ebanina += makeMagicPowString(power);
		else ebanina += "(-~0<<(" + createEbanina(bit) + "))";

		if (bit != bits.back()) ebanina += "|";
	}

	if (ebanina.front() != '(')
	{
		ebanina = "(" + ebanina + ")";
	}

	return ebanina;
}

void setBitsOffset(vector<uint64_t> & bits, uint64_t x)
{
	for (uint64_t i = 0; i <= log2(x); ++i)
	{
		if (x & (uint64_t(1) << i)) bits.emplace_back(i);
	}
}

string makeMagicPowString(uint64_t power)
{
	if (power == 0) return string("(-~0<<0)");

	string begin, end;
	for (int i = 0; i <= int(log2(power)) + 1; ++i)
	{
		begin += "(-~0<<";
		end += ")";
	}

	return begin + "0" + end;
}

pair<bool, uint64_t> isMagicPower(uint64_t x)
{
	static array<uint64_t, 4> powers = { 0, 1, 2, 4 };

	for (auto s : powers)
		if (x == s) return make_pair(true, s);

	return make_pair(false, 0);
}