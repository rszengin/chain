//============================================================================
// Name        : chain.hpp
// Author      : Rahman Salim Zengin
// Version     :
// Copyright   : rsz@gufatek.com
// Description : Chained comparison implementation
//============================================================================

#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <type_traits>

namespace cmp {

struct Order {
	struct Ascending;
	struct Descending;
};

template<typename LType, typename ChainOrder>
class Comparator {
	// lhs_ is rhs value of the previous operator
	const LType& lhs_;
	// result_ is the cumulative && of the previous comparisons
	const bool result_;
public:
	Comparator(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	/*
	 * These operators are not allowed for an Descending ordered comparison chain.
	 * Usage of these operators in an Descending ordered comparison chain will
	 * result in a compile time error.
	 */
	template<typename RType>
	Comparator<RType, Order::Ascending> operator <(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Comparator<RType, Order::Ascending>(rhs, result_ && (lhs_ < rhs));
	}
	template<typename RType>
	Comparator<RType, Order::Ascending> operator <=(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Comparator<RType, Order::Ascending>(rhs, result_ && (lhs_ <= rhs));
	}

	/*
	 * These operators are not allowed for an Ascending ordered comparison chain.
	 * Usage of these operators in an Ascending ordered comparison chain will
	 * result in a compile time error.
	 */
	template<typename RType>
	Comparator<RType, Order::Descending> operator >(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Comparator<RType, Order::Descending>(rhs, result_ && (lhs_ > rhs));
	}
	template<typename RType>
	Comparator<RType, Order::Descending> operator >=(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Comparator<RType, Order::Descending>(rhs, result_ && (lhs_ >= rhs));
	}


	inline operator bool() const {
		return result_;
	}
};


struct Initiator {
	template<typename RType>
	Comparator<RType, Order::Ascending> operator <(const RType& rhs) const {
		return Comparator<RType, Order::Ascending>(rhs, true);
	}
	template<typename RType>
	Comparator<RType, Order::Descending> operator >(const RType& rhs) const {
		return Comparator<RType, Order::Descending>(rhs, true);
	}
};

constexpr Initiator chain {};

} /* namespace cmp */



#endif /* CHAIN_HPP_ */
