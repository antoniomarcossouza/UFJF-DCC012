#include "ProductReview.h"
#include <iostream>

using namespace std;

ProductReview::ProductReview()
{
    this->userId = "";
    this->productId = "";
    this->rating = 0.0;
    this->timestamp = 0;
}

void ProductReview::print()
{
    cout << "USER ID: " << this->userId << endl;
    cout << "PRODUCT ID: " << this->productId << endl;
    cout << "RATING: " << this->rating << endl;
    cout << "TIMESTAMP: " << this->timestamp << endl;
}