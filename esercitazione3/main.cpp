#include "rational.hpp"
#include <iostream>

int main(void)
{
	//Casi in cui ho zero al denominatore
	rational<int> inf_positivo(4,0);
	std::cout << "4/0 = " << inf_positivo << "\n";
	
	rational<int> inf_negativo(-2,0);
	std::cout << "(-2)/0 = " << inf_negativo << "\n";
	
	rational<int> NaN(0,0);
	std::cout << "0/0 = " << NaN << "\n";

	//Semplificazione
	rational<int> r(2,6);
	std::cout << "Il numero 2/6 si semplifica in " << r << "\n";
	
	//Svolgo l'operazione tra 0 al numeratore e un numero qualsiasi al denominatore
	rational<int> zero(0,2);
	std::cout << "0/2: " << zero << "\n";
	
	//Svolgo l'operazione tra un numero e 1 al denominatore
	rational<int> c(3,1);
	std::cout << "3/1: " << c << "\n";
	
	//Operazioni aritmetiche
	rational<int> a(2,5);
	rational<int> b(3,7);
	rational<int> neg(-1,3);
	rational<int> neg2(1,-3);
	
	std::cout << "2/5: " << a << "\n";
	std::cout << "-(1/3): " << neg << "\n";
	std::cout << "-(1/3): " << neg2 << "\n";
	
	//Svolgo le operazioni tra i due numeri
	std::cout << a << " + " << b << " = " << a + b << "\n";
	std::cout << a << " - " << b << " = " << a - b << "\n";
	std::cout << a << " * " << b << " = " << a * b << "\n";
	std::cout << a << " / " << b << " = " << a / b << "\n";
	
	//Svolgo le operazioni con lo zero
	std::cout << a << " / 0 = " << a / zero << "\n";
	std::cout << "0 / " << a << " = " << zero / a << "\n";
	
	//Svolgo le operazioni tra un numero e un caso di un numero con denominatore uguale a zero
	//Quando ho inf_positivo
	std::cout << a << " + Inf = " << a + inf_positivo << "\n";
	std::cout << a << " - Inf = " << a - inf_positivo << "\n";
	std::cout << a << " * Inf = " << a * inf_positivo << "\n";
	std::cout << a << " / Inf = " << a / inf_positivo << "\n";
	std::cout << "Inf - " << a << " = " << inf_positivo - a << "\n";
	std::cout << "Inf / " << a << " = " << inf_positivo / a << "\n";
	//Quando ho inf_negativo
	std::cout << a << " + (-Inf) = " << a + inf_negativo << "\n";
	std::cout << a << " - (-Inf) = " << a - inf_negativo << "\n";
	std::cout << a << " * (-Inf) = " << a * inf_negativo << "\n";
	std::cout << a << " / (-Inf) = " << a / inf_negativo << "\n";
	std::cout << "-Inf - " << a << "= " << inf_negativo - a << "\n";
	std::cout << "-Inf / " << a << "= " << inf_negativo / a << "\n";
	//Quando ho NaN
	std::cout << a << " + NaN = " << a + NaN << "\n";
	std::cout << a << " - NaN = " << a - NaN << "\n";
	std::cout << a << " * NaN = " << a * NaN << "\n";
	std::cout << a << " / NaN = " << a / NaN << "\n";
	std::cout << "NaN - " << a << " = " << NaN - a << "\n";
	std::cout << "NaN / " << a << " = " << NaN / a << "\n";
	
	//Svolgo le operazioni tra Inf e NaN
	//Quando ho inf_positivo
	std::cout << "Inf + NaN = " << inf_positivo + NaN << "\n";
	std::cout << "Inf - NaN = " << inf_positivo - NaN << "\n";
	std::cout << "Inf * NaN = " << inf_positivo * NaN << "\n";
	std::cout << "Inf / NaN = " << inf_positivo / NaN << "\n";
	std::cout << " Nan - Inf = " << NaN - inf_positivo << "\n";
	std::cout << " Nan / Inf = " << NaN / inf_positivo << "\n";
	//Quando ho inf_negativo
	std::cout << "-Inf + NaN = " << inf_negativo + NaN << "\n";
	std::cout << "-Inf - NaN = " << inf_negativo - NaN << "\n";
	std::cout << "-Inf * NaN = " << inf_negativo * NaN << "\n";
	std::cout << "-Inf / NaN = " << inf_negativo / NaN << "\n";
	std::cout << " Nan - (-Inf) = " << NaN - inf_negativo << "\n";
	std::cout << " Nan / (-Inf) = " << NaN / inf_negativo << "\n";

	//Svolgo le operazioni tra Inf e Inf
	//Quando ho entrambi inf_positivo
	std::cout << "Inf + Inf = " << inf_positivo + inf_positivo << "\n";
	std::cout << "Inf - Inf = " << inf_positivo - inf_positivo << "\n";
	std::cout << "Inf * Inf = " << inf_positivo * inf_positivo << "\n";
	std::cout << "Inf / Inf = " << inf_positivo / inf_positivo << "\n";
	//Quando ho inf_positivo e inf_negativo
	std::cout << "Inf + (-Inf) = " << inf_positivo + inf_negativo << "\n";
	std::cout << "Inf - (-Inf) = " << inf_positivo - inf_negativo << "\n";
	std::cout << "Inf * (-Inf) = " << inf_positivo * inf_negativo << "\n";
	std::cout << "Inf / (-Inf) = " << inf_positivo / inf_negativo << "\n";
	std::cout << "-Inf - Inf = " << inf_negativo - inf_positivo << "\n";
	std::cout << "-Inf / Inf = " << inf_negativo / inf_positivo << "\n";
	//Quando ho entrambi inf_negativo
	std::cout << "(-Inf) + (-Inf) = " << inf_negativo + inf_negativo << "\n";
	std::cout << "(-Inf) - (-Inf) = " << inf_negativo - inf_negativo << "\n";
	std::cout << "(-Inf) * (-Inf) = " << inf_negativo * inf_negativo << "\n";
	std::cout << "(-Inf) / (-Inf) = " << inf_negativo / inf_negativo << "\n";
	
	//Svolgo le operazioni tra NaN e NaN
	std::cout << "NaN + NaN = " << NaN + NaN << "\n";
	std::cout << "NaN - NaN = " << NaN - NaN << "\n";
	std::cout << "NaN * NaN = " << NaN * NaN << "\n";
	std::cout << "NaN / NaN = " << NaN / NaN << "\n";
	
	//Svolgo le operazioni tra Inf/NaN e zero
	std::cout << "Inf * 0 = " << inf_positivo * zero << "\n";
	std::cout << "Inf / 0 = " << inf_positivo / zero << "\n";
	std::cout << " 0 / Inf = " << zero / inf_positivo << "\n";
	
	std::cout << "-Inf * 0 = " << inf_negativo * zero << "\n";
	std::cout << "-Inf / 0 = " << inf_negativo / zero << "\n";
	std::cout << " 0 / (-Inf) = " << zero / inf_negativo << "\n";
	
	std::cout << "NaN * 0 = " << NaN * zero << "\n";
	std::cout << "NaN / 0 = " << NaN / zero << "\n";
	std::cout << "0 / NaN = " << zero / NaN << "\n";
	
	//Svolgo gli operatori di assegnamento ( +=, -=, *=, /=)
	rational<int> x;
	
	x = a;
	std::cout << " a += b : " << (x += b) << "\n";
	x = a;
	std::cout << " a -= b : " << (x -= b) << "\n";
	x = a;
	std::cout << " a *= b : " << (x *= b) << "\n";
	x = a;
	std::cout << " a /= b : " << (x /= b) << "\n";
	
	//Con Inf
	x = a;
	std::cout << " a += Inf : " << (x += inf_positivo) << "\n";
	x = a;
	std::cout << " a -= Inf : " << (x -= inf_positivo) << "\n";
	x = a;
	std::cout << " a *= Inf : " << (x *= inf_positivo) << "\n";
	x = a,
	std::cout << " a /= Inf : " << (x /= inf_positivo) << "\n";
	
	//Con NaN
	x = a;
	std::cout << " a += NaN : " << (x += NaN) << "\n";
	x = a;
	std::cout << " a -= NaN : " << (x -= NaN) << "\n";
	x = a;
	std::cout << " a *= NaN : " << (x *= NaN) << "\n";
	x = a;
	std::cout << " a /= NaN : " << (x /= NaN) << "\n";
	
	return 0;
}