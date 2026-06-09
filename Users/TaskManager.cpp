#include "TaskManager.h"
#include <print>

TaskManager::TaskManager(const std::string& username, const std::string& password, Taskboard& taskBoard):User(username, password), taskboard(taskBoard)
{
}

void TaskManager::showTasks() const
{
	taskboard.showTasks();
}

void TaskManager::addTask(const std::string& product, unsigned int quantity, unsigned int rewardBalance, unsigned int rewardScore)
{
	taskboard.addTask(product, quantity, rewardBalance, rewardScore);
}

void TaskManager::removeTask(unsigned int taskId)
{
	taskboard.removeTask(taskId);
}

void TaskManager::profileInfo() const
{
	std::println("ID: {}", this->getId());
	std::println("Username: {}", this->getUsername());
	std::println("Role: TaskManager");
}

std::ostream& TaskManager::serialize(std::ostream& os) const
{
	os << "TaskManager ";
	serializeBase(os);
	os << "\n";
	return os;
}

std::istream& TaskManager::deserialize(std::istream& is)
{
	return is;
}



