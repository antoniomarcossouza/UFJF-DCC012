#ifndef PRODUCTREVIEW_H
#define PRODUCTREVIEW_H

#include <iostream>

using namespace std;

class ProductReview {
   public:
    void setUserId(std::string userId) { this->userId = userId; }
    void setProductId(std::string productId) { this->productId = productId; }
    void setRating(float rating) { this->rating = rating; }
    void setTimestamp(int timestamp) { this->timestamp = timestamp; }
    void setBinFileLocation(int binFileLocation) { this->binFileLocation = binFileLocation; }

    std::string getUserId() { return this->userId; }
    std::string getProductId() { return this->productId; }
    double getRating() { return this->rating; }
    int getTimestamp() { return this->timestamp; }
    int getBinFileLocation() { return this->binFileLocation; }

    ProductReview();
    void print();

    string toString();

   private:
    std::string userId;
    std::string productId;
    int binFileLocation;
    float rating;
    int timestamp;
};

#endif