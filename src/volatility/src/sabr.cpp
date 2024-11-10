#include "volatility/sabr.hpp"

using namespace volatility;

SABR::SABR(double alpha, double beta, double rho, double nu)
:alpha_(alpha),beta_(beta),rho_(rho),nu_(nu){
    
};

SABR::SABR(SABRData data){
};

double SABR::operator()(double F, double K, double T) const{
    return 0.0;
};



