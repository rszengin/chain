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

template<typename LType>
class Comparator {
	const LType& lhs_;
	const bool result_;
public:
	Comparator(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	template<typename RType>
	Comparator<RType> operator <(const RType& rhs) const {
		return Comparator<RType>(rhs, result_ && (lhs_ < rhs));
	}
	template<typename RType>
	Comparator<RType> operator <=(const RType& rhs) const {
		return Comparator<RType>(rhs, result_ && (lhs_ <= rhs));
	}
	template<typename RType>
	Comparator<RType> operator >(const RType& rhs) const {
		return Comparator<RType>(rhs, result_ && (lhs_ > rhs));
	}
	template<typename RType>
	Comparator<RType> operator >=(const RType& rhs) const {
		return Comparator<RType>(rhs, result_ && (lhs_ >= rhs));
	}

	inline operator bool() const {
		return result_;
	}
};

struct Initiator {
	template<typename RType>
	Comparator<RType> operator <(const RType& rhs) const {
		return Comparator<RType>(rhs, true);
	}
	template<typename RType>
	Comparator<RType> operator <=(const RType& rhs) const {
		return Comparator<RType>(rhs, true);
	}
	template<typename RType>
	Comparator<RType> operator >(const RType& rhs) const {
		return Comparator<RType>(rhs, true);
	}
	template<typename RType>
	Comparator<RType> operator >=(const RType& rhs) const {
		return Comparator<RType>(rhs, true);
	}
};

constexpr Initiator chain {};

} /* namespace cmp */



#endif /* CHAIN_HPP_ */
