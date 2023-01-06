#include "ProductReview.h"

#include <iostream>

using namespace std;

ProductReview::ProductReview() {
    this->userId = "";
    this->productId = "";
    this->rating = 0.0;
    this->timestamp = 0;
}

void ProductReview::print() {
    cout << "USER ID: " << this->userId << endl;
    cout << "PRODUCT ID: " << this->productId << endl;
    cout << "RATING: " << this->rating << endl;
    cout << "TIMESTAMP: " << this->timestamp << endl;
}

string ProductReview::toString() {
    string retorno = "";
    retorno += this->userId;
    retorno += "/";
    retorno += this->productId;
    retorno += "/";
    retorno += to_string(this->rating);
    retorno += "/";
    retorno += to_string(this->timestamp);
    retorno += "/";
    return retorno;
}