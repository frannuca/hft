#include <string>
#include <sstream>

#include <Eigen/Eigenvalues>
#include "pca/pca.hpp"

using namespace hft::pca;

PCA::PCA(size_t number_of_component, Eigen::MatrixXd& data):num_components_(number_of_component),_data(data){
    
}

void PCA::fit_transform()
{
    if(!principal_components_ || !mean_){
        const auto data = _data;
        Eigen::VectorXd mean = data.colwise().mean();
        Eigen::MatrixXd centered = data.rowwise() - mean.transpose();
        Eigen::MatrixXd cov = (centered.adjoint() * centered)/(data.rows() -1);

        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(cov);
        Eigen::MatrixXd principal_components = solver.eigenvectors().rightCols(num_components_);      
        
        std::tie(principal_components_,mean_) = std::make_tuple(principal_components,mean);  
    }
}

Eigen::MatrixXd PCA::transform(const Eigen::MatrixXd &data)
{    
    fit_transform();
    auto& mean = *mean_;
    auto& principal_components = *principal_components_;

    if(mean.count() != data.cols()) {
        std::string errmsg =  (std::ostringstream("number of columns in input matrix does not match the expected PCA dimenstions {}") << mean.count()).str();
        throw std::runtime_error(errmsg);
    }
    
    Eigen::MatrixXd centered = data.rowwise()-mean.transpose();
    
    return centered * principal_components;
}

Eigen::MatrixXd PCA::inverse_transform(const Eigen::MatrixXd &projected)
{
    fit_transform();
    if(projected.cols() != num_components_){
        std::string errmsg =  (std::ostringstream("number of columns in input transformed matrix does not match the expected PCA dimenstions {}") << num_components_).str();
        throw std::runtime_error(errmsg);
    }
    auto x = (projected * principal_components_->transpose()).rowwise() + mean_->transpose();
    return x;
}
const Eigen::MatrixXd &PCA::get_pricipal_compoments()
{
    fit_transform();
    return *principal_components_;
}

const Eigen::VectorXd&  PCA::means(){
    fit_transform();
    return *mean_;
}
