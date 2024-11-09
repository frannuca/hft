#ifndef MULTI_PROJECT_TEMPLATE_LIB1_H
#define MULTI_PROJECT_TEMPLATE_LIB1_H

#include <Eigen/Dense>

class PCA{
    public:

    PCA(size_t number_of_component, Eigen::MatrixXd& data);
    
    
    /// @brief 
    /// @param data 
    /// @return 
    Eigen::MatrixXd transform(const Eigen::MatrixXd& data);

    Eigen::MatrixXd inverse_transform(const Eigen::MatrixXd& projected);

    
    /// @brief 
    /// @return 
    const Eigen::MatrixXd& get_pricipal_compoments();

    const Eigen::VectorXd& means();

    constexpr size_t count();

    private:

    /// @brief Given a matrix of MxN, where M is the number of samples and N the number of features, computes the PCA matrix
    /// @param matrix input samples matrix
    /// @return PCA matrix of dimention KxM, with K the number of components
    void fit_transform();

    const int num_components_;
    std::optional<Eigen::MatrixXd> principal_components_;
    std::optional<Eigen::VectorXd> mean_;
    const Eigen::MatrixXd& _data;

};

#endif //MULTI_PROJECT_TEMPLATE_LIB1_H
