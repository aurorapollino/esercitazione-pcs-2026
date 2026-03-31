#pragma once

#include <concepts>
#include <iostream>
#include <numeric>


template<typename I> requires std::integral<I>
class rational
{ 
	I num_;
	I den_;
	
	void semplificazioni() {
		//Gestisco la divisione per zero
		if (den_ == 0) {
			if (num_ > 0) num_ = 1;  // restituisce +Inf
			else if (num_ < 0) num_ = -1;  // restituisce -Inf
			else num_ = 0;  // restituisce NaN
			return;
		}
		
		// Gestisco il caso quando il numeratore è zero
		if (num_ == 0) {
			den_ = 1;
			return;
		}
		
		// Il segno va posizionato al numeratore
		if (den_ < 0) {
			num_ = -num_;
			den_ = -den_;
		}
			
		// Gestisco la semplificazione
		I mcd = std::gcd(num_, den_);
		if (mcd > 1) {  // escludo = 1 perchè i due numeri sarebbero primi tra loro
			num_ /= mcd;
			den_ /= mcd;
		}
	}
		
	
public:
	//Costruttore di default
	rational()
		: num_(I{0}), den_(I{1})
	{}
	
	//Costruttore user-defined
	rational(const I& num, const I& den)
		: num_(num), den_(den)
	{	
		semplificazioni();
	}
	
	//Restituisce i valori di num e den
	I num() const { return num_;}
	I den() const { return den_;}
	
	//Implementazione canonica dell'incremento
	rational& operator+=(const rational& other) {
		if (den_ == 0 || other.den_ == 0) {
			//Se un numero dei due è NaN , il risultato è sempre NaN
			if ((den_ == 0 && num_ == 0) || (other.den_ == 0 && other.num_ == 0)) {
				num_ = 0; 
				den_ = 0; 
				return *this;
			}
			//Se i numeri sono entrambi infiniti
			if (den_ == 0 && other.den_ == 0) {
				if ((num_ > 0 && other.num_ > 0) || (num_ < 0 && other.num_ < 0)) {
					return *this; //Inf + Inf = Inf , -Inf + (-Inf) = -Inf
				} 
				else {
					num_ = 0; 
					den_ = 0; 
					return *this; //Inf + (-Inf) = NaN
				}
			}
			//Se solo uno dei due numeri è infinito
			if (den_ == 0) {
				return *this; //Inf + numero = Inf
			}
			if (other.den_ == 0) {
				num_ = other.num_; //numero + Inf = Inf
				den_ = other.den_;
				return*this;
			}
		}
	
		num_ = num_ * other.den_ + other.num_ * den_;
		den_ = den_ * other.den_;
		semplificazioni();
		return *this;
	}
	
	//Implementazione canonica della somma
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;
	}
	
	//Implementazione canonica dell'incremento negativo
	rational& operator-=(const rational& other) {
		if (den_ == 0 || other.den_ == 0) {
			//Se uno dei due numeri è NaN, il risultato è sempre NaN
			if ((den_ == 0 && num_ == 0) || (other.den_ == 0 && other.num_ == 0)) {
				num_ = 0; 
				den_ = 0; 
				return *this;
			}
			//Se i numeri sono entrambi infiniti
			if (den_ == 0 && other.den_ == 0) {
				if ((num_ > 0 && other.num_ < 0) || (num_ < 0 && other.num_ > 0)) {
					return *this; //Inf - (-Inf) = Inf + Inf = Inf
				} else {
					num_ = 0; 
					den_ = 0; 
					return *this; //Inf - Inf = NaN , -Inf - (-Inf) = NaN
				}
			}
			//Se solo uno dei due numeri è infinito
			if (den_ == 0) {
				return *this; //Inf - numero = Inf
			}
			if (other.den_ == 0) {
				num_ = -other.num_; //numero - Inf = -Inf
				den_ = other.den_;
				return *this;
			}
		}
		num_ = num_ * other.den_ - other.num_ * den_;
		den_ = den_ * other.den_;
		semplificazioni();
		return *this;
	}
	
	//Implementazione della differenza
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;
	}
		
	//Implementazione canonica di *=
	rational& operator*=(const rational& other) {
		num_ *= other.num_;
		den_ *= other.den_;
		semplificazioni();
		return *this;
	}
	
	//Implementazione canonica della moltiplicazione
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	
	//Implementazione canonica di /=
	rational& operator/=(const rational& other) {
		num_ *= other.den_;
		den_ *= other.num_;
		semplificazioni();
		return *this;
	}
	
	//Implementazione canonica della divisione
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
	//Gestisco Inf e NaN
	if (r.den() == 0) {
		if (r.num() > 0) os << "+Inf";
		else if (r.num() < 0) os << "-Inf";
		else os << "NaN";
	}
	// Se il denominatore è 1, stampo il numero intero
	else if (r.den() == 1) {
		os << r.num();
	}
	//Stampo la frazione
	else {
		os << r.num() << "/" << r.den();
	}
	return os;
}


	
