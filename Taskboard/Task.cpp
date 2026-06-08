#include "Task.h"
#include <print>
#include <iostream>

unsigned int Task::nextId = 0;

Task::Task(unsigned int requiredQuantity, ProductType product, unsigned int rewardBalance, unsigned int rewardScore)
	:id(++nextId), requiredQuantity(requiredQuantity), requiredProduct(product), rewardBalance(rewardBalance), rewardScore(rewardScore)
{
}

void Task::displayTask() const
{
	std::println("Id:{}, product: {}, quantity: {}, Balance reward: {}, Score reward: {} ", id, Utils::productTypeToString(requiredProduct), requiredQuantity, rewardBalance, rewardScore);
}

unsigned int Task::getId() const
{
	return id;
}

ProductType Task::getProduct() const
{
	return requiredProduct;
}

unsigned int Task::getRequiredQuantity() const
{
	return requiredQuantity;
}

unsigned int Task::getRewardBalance() const
{
	return rewardBalance;
}

unsigned int Task::getRewardScore() const
{
	return rewardScore;
}

std::ostream& operator<<(std::ostream& os, const Task& task)
{
	os << task.id << " " << Utils::productTypeToString(task.requiredProduct) << " " << task.requiredQuantity
		<< " " << task.rewardBalance << " " << task.rewardScore<<"\n";
	return os;
}

std::istream& operator>>(std::istream& is, Task& task)
{
	std::string product;
	unsigned int id, quantity, balance, score;

	if (!(is >> id >> product >> quantity >> balance >> score)) {
		return is;
	}

	task = Task(
		quantity,
		Utils::stringToProductType(product),
		balance, score
	);

	task.id = id;

	if (id >= Task::nextId) {
		Task::nextId = id + 1;
	}

	return is;
}
