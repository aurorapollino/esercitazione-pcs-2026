#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

int main(int argc, char **argv) // puoi lasciare vuoto dentro
{
	const double tol = 1.0e-15;
	unsigned int n = 3;

	Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

	if (abs(B.determinant()) < tol)
		return -1;
	
	Eigen::MatrixXd A = B.transpose() * B;
	Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
	Eigen::VectorXd b = A * x_ex;
	
	const unsigned int it_max = 10000;
	const double res_tol = 1.0e-12;
  
	// gradiente semplice
	Eigen::VectorXd x_g = Eigen::VectorXd::Zero(n);
	gradiente_semplice(A, b, x_g, res_tol, it_max);
	
	
	//gradiente coniugato
	Eigen::VectorXd x_gc = Eigen::VectorXd::Zero(n);
	unsigned int it_gc = gradiente_coniugato(A, b, x_gc, res_tol, it_max);
	
	const auto err_rel_gc = (x_ex.norm() == 0.0) ? (x_gc - x_ex).norm() : (x_gc - x_ex).norm() / x_ex.norm();
	
	
	std::cout.precision(4);
	
    std::cout << std::scientific << "Iterazioni: " << it_gc << "/" << it_max << "\n";
    std::cout << std::scientific << "Errore relativo: " << err_rel_gc << "\n";
    std::cout << std::scientific << "Soluzione:\n" << x_gc << "\n";
	
	return 0;
}


