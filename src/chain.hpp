/*
 * chain.hpp
 *
 *  Created on: 20 Eki 2016
 *      Author: RSZ
 */

#ifndef CHAIN_HPP_
#define CHAIN_HPP_

namespace cmp {

template<typename LType>
class Operate {
	const LType& lhs_;
	const bool result_;
public:
	Operate(const LType& lhs, const bool result) : lhs_(lhs), result_(result){}

	template<typename RType>
	Operate<RType> operator <(const RType& rhs) const {
		return Operate<RType>(rhs, result_ && (lhs_ < rhs));
	}

	inline operator bool() const {
		return result_;
	}
};

struct Initiate {
	template<typename RType>
	Operate<RType> operator <(const RType& rhs) const {
		return Operate<RType>(rhs, true);
	}
};

const Initiate chain {};

} /* namespace cmp */



#endif /* CHAIN_HPP_ */
