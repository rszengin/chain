//============================================================================
// Name        : chain.hpp
// Author      : Rahman Salim Zengin
// Version     :
// Copyright   : rsz@gufatek.com
// Description : Chained comparison implementation
//============================================================================

#ifndef CHAIN_HPP_
#define CHAIN_HPP_

namespace cmp {

enum class Order {Ascending, Descending};

template<typename LType, Order>
class Comparator {
	Comparator() = delete;
};

template<typename LType>
class Comparator<LType, Order::Ascending> {
	const LType& lhs_;
	const bool result_;
public:
	Comparator(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	template<typename RType>
	Comparator<RType, Order::Ascending> operator <(const RType& rhs) const {
		return Comparator<RType, Order::Ascending>(rhs, result_ && (lhs_ < rhs));
	}
	template<typename RType>
	Comparator<RType, Order::Ascending> operator <=(const RType& rhs) const {
		return Comparator<RType, Order::Ascending>(rhs, result_ && (lhs_ <= rhs));
	}

	inline operator bool() const {
		return result_;
	}
};

template<typename LType>
class Comparator<LType, Order::Descending> {
	const LType& lhs_;
	const bool result_;
public:
	Comparator(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	template<typename RType>
	Comparator<RType, Order::Descending> operator >(const RType& rhs) const {
		return Comparator<RType, Order::Descending>(rhs, result_ && (lhs_ > rhs));
	}
	template<typename RType>
	Comparator<RType, Order::Descending> operator >=(const RType& rhs) const {
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
