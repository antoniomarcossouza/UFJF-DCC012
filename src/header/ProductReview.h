#ifndef PRODUCTREVIEW_H
#define PRODUCTREVIEW_H

#include <iostream>

using namespace std;

class ProductReview
{
    public:
        void setUserId(std::string userId) {this->userId = userId;}
        void setProductId(std::string productId) {this->productId = productId;}
        void setRating(float rating) {this->rating = rating;}
        void setTimestamp(int timestamp) {this->timestamp = timestamp;}

        std::string getUserId() {return this->userId; }
        std::string getProductId() {return this->userId; }
        double getRating() {return this->rating; }
        int getTimestamp() {return this->timestamp; }

        ProductReview();
        void print();

    private:
        std::string userId;
        std::string productId;
        float rating;
        int timestamp;
};

#endif