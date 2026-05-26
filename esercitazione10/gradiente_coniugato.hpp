#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}


//gradiente semplice
unsigned int gradiente_semplice(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, double res_tol, unsigned int it_max)
{
	
    Eigen::VectorXd res = b - A * x;
	double res_norm_0 = res.norm();
	unsigned int it = 0;
	
	
	while (it < it_max && res.norm() > res_tol * res_norm_0)
  {
	  const double alpha_k = ((res.transpose() * res) / (res.transpose() * A * res)).value();
	  x = x + alpha_k * res;
	  res = res - alpha_k * A * res;
	  it++;
  }
  return it; //non so

}


//gradiente coniugato

unsigned int gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, double res_tol, unsigned int it_max)
{
	Eigen::VectorXd r = b - A * x;
	Eigen::VectorXd p = r;
	double r_norm_0 = r.norm();
	unsigned int it = 0;
	
	while (it < it_max && r.norm() > res_tol * r_norm_0)
  {
	  const double alpha_k = ( p.transpose() * r).value() / (( p. transpose() * A * p).value());
	  x = x + alpha_k * p;
	  
	  const Eigen::VectorXd r_k = b - A * x;
	  const double beta_k = ((p.transpose() * A * r_k).value()) /(( p. transpose() * A * p).value());
	  p = r_k - beta_k * p;
	  r = r_k;
	  it++;
  }
  return it;
}

