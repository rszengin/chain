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
class Conductor {
	// lhs_ is rhs value of the previous operator
	const LType& lhs_;
	// result_ is the cumulative && of the previous comparisons
	const bool result_;
public:
	Conductor(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	/*
	 * These operators are only allowed for an "Ascending" ordered comparison chain.
	 * Otherwise will result in a compile time error.
	 */
	template<typename RType>
	Conductor<RType, Order::Ascending> operator <(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Ascending>(rhs, result_ && (lhs_ < rhs));
	}
	template<typename RType>
	Conductor<RType, Order::Ascending> operator <=(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Ascending>(rhs, result_ && (lhs_ <= rhs));
	}

	/*
	 * These operators are only allowed for an "Descending" ordered comparison chain.
	 * Otherwise will result in a compile time error.
	 */
	template<typename RType>
	Conductor<RType, Order::Descending> operator >(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Descending>(rhs, result_ && (lhs_ > rhs));
	}
	template<typename RType>
	Conductor<RType, Order::Descending> operator >=(const RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Descending>(rhs, result_ && (lhs_ >= rhs));
	}


	inline operator bool() const {
		return result_;
	}
};


struct Initiator {
	template<typename RType>
	Conductor<RType, Order::Ascending> operator <(const RType& rhs) const {
		return Conductor<RType, Order::Ascending>(rhs, true);
	}
	template<typename RType>
	Conductor<RType, Order::Descending> operator >(const RType& rhs) const {
		return Conductor<RType, Order::Descending>(rhs, true);
	}
};

constexpr Initiator chain {};

} /* namespace cmp */



#endif /* CHAIN_HPP_ */
