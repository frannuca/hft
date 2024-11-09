#include <iostream>
#include "pca_library/pca.h"
#include "lib2/fun2.h"
#include <iostream>
int main()
{
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
    fun2();
    std::cout<<"Hello from HFT"<<std::endl;
    return 0;
}