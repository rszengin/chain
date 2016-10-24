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
#include <cassert>

namespace cmp {

// Helper type for controlling of the chain order
struct Order {
	struct Ascending;
	struct Descending;
};

struct Unknown_t {};

/*
 * "Conductor" object preserves information before and transfers it to the following.
 * Operations should follow chain order.
 * Ascending to ascending or descending to descending.
 * Breaking the order will result in a compile time error.
 * Mixes comparison order is not allowed.
 * Internal state is constant after construction.
 */
template<typename LType, typename ChainOrder, typename KnownType>
class Conductor {
	// "lhs_" is "rhs" value of the previous operation
	const LType& lhs_;
	// "result_" is the cumulative "&&" of the previous comparisons
	const bool result_;
	// "known_value" is the last encountered rvalue. So, guess what KnownType is?
	const KnownType& known_value_;
public:
	Conductor(	const LType& lhs, const bool result,
				const KnownType& known_value) :
		lhs_(lhs), result_(result), known_value_(known_value){}

	/*
	 * These operators are only allowed for an "Ascending" ordered comparison chain.
	 * Otherwise will result in a compile time error.
	 */
	template<typename RType>
	Conductor<RType, Order::Ascending, KnownType> operator <(RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Ascending, KnownType>(rhs, result_ && (lhs_ < rhs), known_value_);
	}
	template<typename RType>
	Conductor<RType, Order::Ascending, RType> operator <(RType&& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		assert(("Always false", !std::is_same<KnownType, Unknown_t>::value && (known_value_ >= rhs)));
		return Conductor<RType, Order::Ascending, RType>(rhs, result_ && (lhs_ < rhs), rhs);
	}
	template<typename RType>
	Conductor<RType, Order::Ascending, KnownType> operator <=(RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Ascending, KnownType>(rhs, result_ && (lhs_ <= rhs), known_value_);
	}
	template<typename RType>
	Conductor<RType, Order::Ascending, RType> operator <=(RType&& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Ascending>::value,
				"Ambiguously ordered comparison chain");
		assert(("Always false", !std::is_same<KnownType, Unknown_t>::value && (known_value_ > rhs)));
		return Conductor<RType, Order::Ascending, RType>(rhs, result_ && (lhs_ <= rhs), rhs);
	}

	/*
	 * These operators are only allowed for an "Descending" ordered comparison chain.
	 * Otherwise will result in a compile time error.
	 */
	template<typename RType>
	Conductor<RType, Order::Descending, KnownType> operator >(RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Descending, KnownType>(rhs, result_ && (lhs_ > rhs), known_value_);
	}
	template<typename RType>
	Conductor<RType, Order::Descending, RType> operator >(RType&& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		assert(("Always false", !std::is_same<KnownType, Unknown_t>::value && (known_value_ <= rhs)));
		return Conductor<RType, Order::Descending, RType>(rhs, result_ && (lhs_ > rhs), rhs);
	}
	template<typename RType>
	Conductor<RType, Order::Descending, KnownType> operator>=(RType& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		return Conductor<RType, Order::Descending, KnownType>(rhs, result_ && (lhs_>= rhs), known_value_);
	}
	template<typename RType>
	Conductor<RType, Order::Descending, RType> operator>=(RType&& rhs) const {
		static_assert(std::is_same<ChainOrder, Order::Descending>::value,
				"Ambiguously ordered comparison chain");
		assert(("Always false", !std::is_same<KnownType, Unknown_t>::value && (known_value_ < rhs)));
		return Conductor<RType, Order::Descending, RType>(rhs, result_ && (lhs_>= rhs), rhs);
	}

	inline operator bool() const {
		return result_;
	}
};

/*
 *	"Initiator" object starts comparison chaining and generates "Conductor" object.
 *	First operator after the "Initiator" object determines ordering of the chain.
 *	Starting with "<" forces ascending order.
 *	For ascending, only "<" and "<=" is allowed.
 *	Starting with ">" forces descending order.
 *	For descending, only ">" and ">=" is allowed.
 */
struct Initiator {
	template<typename RType>
	Conductor<RType, Order::Ascending, Unknown_t> operator <<(RType& rhs) const {
		return Conductor<RType, Order::Ascending, Unknown_t>(rhs, true, Unknown_t {});
	}
	template<typename RType>
	Conductor<RType, Order::Ascending, RType> operator <<(RType&& rhs) const {
		return Conductor<RType, Order::Ascending, RType>(rhs, true, rhs);
	}
	template<typename RType>
	Conductor<RType, Order::Descending, Unknown_t> operator >>(RType& rhs) const {
		return Conductor<RType, Order::Descending, Unknown_t>(rhs, true, Unknown_t {});
	}
	template<typename RType>
	Conductor<RType, Order::Descending, RType> operator >>(RType&& rhs) const {
		return Conductor<RType, Order::Descending, RType>(rhs, true, rhs);
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
