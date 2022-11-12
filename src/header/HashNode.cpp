#include "HashNode.h"

HashNode::HashNode(ProductReview review)
{
    val.productId = review.getProductId();
    val.qtdReviews = 1;
    next = NULL;
}

void HashNode::setNext(HashNode *next)
{
    this->next = next;
}

string HashNode::getProductId()
{
    return val.productId;
}

HashNode* HashNode::getNext()
{
    return next;
}

int HashNode::getQtdReviews()
{
    return val.qtdReviews;
}

void HashNode::incrementaQtdReviews()
{
    val.qtdReviews++;
}
