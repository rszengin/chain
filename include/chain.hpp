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

// Helper type for controlling of the chain order
struct Order {
	struct Ascending;
	struct Descending;
};

/*
 * "Conductor" object preserves information before and transfers it to the following.
 * Operations should follow chain order.
 * Ascending to ascending or descending to descending.
 * Breaking the order will result in a compile time error.
 * Mixes comparison order is not allowed.
 * Internal state is constant after construction.
 */
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

/*
 *	"Initiator" object starts comparison chaining and generates "Conductor" object.
 *	First operator after the "Initiator" object determines ordering of the chain.
 *	Starting with "<<" forces ascending order.
 *	For Ascending order, only "<" and "<=" is allowed.
 *	Starting with ">>" forces descending order.
 *	For Descending order, only ">" and ">=" is allowed.
 */
struct Initiator {
	template<typename RType>
	Conductor<RType, Order::Ascending> operator <<(const RType& rhs) const {
		return Conductor<RType, Order::Ascending>(rhs, true);
	}
	template<typename RType>
	Conductor<RType, Order::Descending> operator >>(const RType& rhs) const {
		return Conductor<RType, Order::Descending>(rhs, true);
	}
};

/*
 * "chain" is the default "Initiator" instance. It doesn't have internal state.
 * It is defined for ease and comfort. Usage of "Initiator {}" in place of "chain"
 * is also possible.
 */
constexpr Initiator chain {};

} /* namespace cmp */



#endif /* CHAIN_HPP_ */
