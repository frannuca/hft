#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <pca_library/pca.h>

// Test the PCA fit and transform
TEST(PCA, FitTransform) {
    Eigen::MatrixXd data = Eigen::MatrixXd::Random(4,2);
    

    std::cout<<"Original"<<std::endl;
    std::cout<<data<<std::endl;
    PCA pca(2,data);
    auto x = pca.transform(data);
    std::cout<<"Projected"<<std::endl;
    std::cout<<x.transpose()<<std::endl;

    auto y = pca.inverse_transform(x);
    std::cout<<"Reconstructed"<<std::endl;
    std::cout<<y<<std::endl;


    std::cout<<"Differences"<<std::endl;
    std::cout<<(data-y)<<std::endl;
    
    std::cout<<"Hello from HFT"<<std::endl;

    ASSERT_EQ(x.rows(),data.rows());
    ASSERT_EQ(x.cols(),pca.count());

    ASSERT_EQ(y.rows(),data.rows());
    ASSERT_EQ(y.cols(),data.cols());

    auto error = (data-y).cwiseAbs().maxCoeff();
    ASSERT_LE(error,0.25);


}
