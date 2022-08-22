#pragma once

#include <random>

class xorshift
{
public:
	static constexpr uint32_t(min)() { return 0; }
	static constexpr uint32_t(max)() { return UINT32_MAX; }

	xorshift() : m_seed(0xc1f651c67c62c6e0ull) {}
	explicit xorshift(std::random_device& rd)
	{
		seed(rd);
	}

	void seed(std::random_device& rd)
	{
		m_seed = uint64_t(rd()) << 31 | uint64_t(rd());
	}

	uint32_t operator()()
	{
		uint64_t result = m_seed * 0xd989bcacc137dcd5ull;
		m_seed ^= m_seed >> 11;
		m_seed ^= m_seed << 31;
		m_seed ^= m_seed >> 18;
		return uint32_t(result >> 32ull);
	}

private:
	uint64_t m_seed;
};