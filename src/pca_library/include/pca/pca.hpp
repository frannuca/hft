#ifndef MULTI_PROJECT_TEMPLATE_LIB1_H
#define MULTI_PROJECT_TEMPLATE_LIB1_H

#include <Eigen/Dense>

namespace hft::pca{
/// @brief Principal Component Analysis (PCA) class for dimensionality reduction.
/// This class provides methods to perform PCA on a given dataset, including
/// transforming the data to a lower-dimensional space and reconstructing it back.
class PCA {
public:
    /// @brief Constructs a PCA object with the specified number of components and data.
    /// @param number_of_component The number of principal components to compute.
    /// @param data The input data matrix (MxN) where M is the number of samples and N is the number of features.
    PCA(size_t number_of_component, Eigen::MatrixXd& data);

    /// @brief Transforms the input data to the lower-dimensional space defined by the principal components.
    /// @param data The input data matrix to transform.
    /// @return The transformed data matrix.
    Eigen::MatrixXd transform(const Eigen::MatrixXd& data);

    /// @brief Reconstructs the data from the lower-dimensional space back to the original space.
    /// @param projected The data matrix in the lower-dimensional space.
    /// @return The reconstructed data matrix.
    Eigen::MatrixXd inverse_transform(const Eigen::MatrixXd& projected);

    /// @brief Gets the principal components computed by PCA.
    /// @return A matrix where each column is a principal component.
    const Eigen::MatrixXd& get_pricipal_compoments();

    /// @brief Gets the mean vector of the original data.
    /// @return The mean vector.
    const Eigen::VectorXd& means();

    /// @brief Gets the number of principal components.
    /// @return The number of principal components.
    constexpr int count() { return num_components_; };

private:
    /// @brief Computes the PCA matrix and stores the principal components and mean vector.
    /// This function is called internally by other methods when needed.
    void fit_transform();

    const int num_components_; ///< The number of principal components.
    std::optional<Eigen::MatrixXd> principal_components_; ///< The principal components matrix.
    std::optional<Eigen::VectorXd> mean_; ///< The mean vector of the original data.
    const Eigen::MatrixXd& _data; ///< The input data matrix.
};
}
#endif //MULTI_PROJECT_TEMPLATE_LIB1_H
