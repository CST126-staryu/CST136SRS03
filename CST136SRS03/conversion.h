#pragma once
#include <stdexcept>

//limited number of options user can choose from
enum class country { US, AU, NZ, FJ, TO, PG, SB };

//Combining dollars and cents
template<typename MoneyCombined>
MoneyCombined money(MoneyCombined dollars, MoneyCombined cents)
{
	auto money_total = dollars + (cents / 100) *1.0;
}

//Setting a currency rate per location
template <typename CurrencyRate>
CurrencyRate currency_rate (const country location)
{
	switch (location)
	{
	case country::US:
		return 1.0;
	case country::AU:
		return 0.76;
	case country::NZ:
		return 0.71;
	case country::FJ:
		return 0.49;
	case country::TO:
		return 0.45;
	case country::PG:
		return 0.31;
	case country::SB:
		return 0.13;
	default:
		throw std::out_of_range("Please enter one of the following: US, AU, NZ, FJ, TO, PG, SB"); // wrong input entered
	}
}


template<country Nation, typename Money>
class conversion;
template <country currency, int dollars, int cents>
class conversion <currency_rate, money<dollars,cents>>	
{
	const auto rate{ currency_rate<> };
	const auto finalValue{ money<dollars,cents>::money_total };
};

template <country toCountry, country fromCountry, typename final>
class conversion < toCountry, conversion < fromCountry, final >>
{
	const auto rate{ conversion < toCountry,final::finalValue * (toCountry / fromCountry) };
	final rate{ currency_rate<>};
};
