#include "Taskboard.h"
#include <print>
#include "GameException.h"

Taskboard::Taskboard()
{
	tasks.push_back({ 5, ProductType::Wheat, 50, 10 });
	tasks.push_back({ 3, ProductType::Milk, 120, 20 });
}

void Taskboard::showTasks() const
{
	for (const auto& task : tasks) {
		task.displayTask(); 
	}
}

void Taskboard::addTask(const std::string& product, unsigned int quantity, unsigned int rewardBalance, unsigned int rewardScore)
{
	Task newTask = Task(quantity, Utils::stringToProductType(product), rewardBalance, rewardScore);
	tasks.push_back(newTask);

    std::println("Task successfully added!");
}

void Taskboard::removeTask(unsigned int taskId)
{
	std::erase_if(tasks, [taskId](const Task& t) {
		return t.getId() == taskId;
		});

    std::println("Task successfully removed!");
}

Task* Taskboard::findTask(unsigned int taskId)
{
	auto it = std::find_if(tasks.begin(), tasks.end(),
		[taskId](const Task& t) { return t.getId() == taskId; });
	return it != tasks.end() ? &(*it) : nullptr;
}

std::ostream& operator<<(std::ostream& os, const Taskboard& taskboard) {

    os << "TASKS " << taskboard.tasks.size() << "\n"; 
    for (const auto& task : taskboard.tasks) {
        os << task;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Taskboard& taskboard) {

    std::string section;
    unsigned int taskCount;
    is >> section >> taskCount; 

    if (section != "TASKS")
        throw InvalidFileFormatException();


    taskboard.tasks.clear();

    for (unsigned int i = 0; i < taskCount; i++) {
        Task task;

        if (!(is >> task)) {
            throw InvalidFileFormatException();
        }

        taskboard.tasks.push_back(task);
    }
    return is;
}
