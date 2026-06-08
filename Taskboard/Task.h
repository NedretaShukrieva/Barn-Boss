#pragma once
#include "Utils.h"
#include <iostream>


class Task
{
private:
    static unsigned int nextId;

    unsigned int id;
    ProductType requiredProduct;
    unsigned int requiredQuantity;
    unsigned int rewardBalance;
    unsigned int rewardScore;

public:
    Task() = default;
    Task(unsigned int requiredQuantity, ProductType product, unsigned int rewardBalance, unsigned int rewardScore);

    void displayTask()const;

    unsigned int getId()const;
    ProductType getProduct()const;
    unsigned int getRequiredQuantity()const;
    unsigned int getRewardBalance()const;
    unsigned int getRewardScore()const;

    friend std::ostream& operator<<(std::ostream& os, const Task& task);
    friend std::istream& operator>>(std::istream& is, Task& task);
};

