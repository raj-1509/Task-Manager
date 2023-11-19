#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct Task {
    std::string title;
    std::string timing;
    std::string priority;
    std::string reminder;
};

bool sortByTime(const Task &task1, const Task &task2) {
    return task1.timing < task2.timing;
}

bool sortByPriority(const Task &task1, const Task &task2) {
    return task1.priority < task2.priority;
}

int main() {
    std::map<std::string, std::vector<Task>> taskManager;

    while (true) {
        std::cout << "Task Manager Menu:" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Modify Task" << std::endl;
        std::cout << "3. Show Tasks" << std::endl;
        std::cout << "4. Delete Task" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "6. Reminder" << std::endl;

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline character from the input buffer.

        switch (choice) {
            case 1: // Add Task
            {
                std::string date;
                std::cout << "Enter the date (e.g., YYYY-MM-DD): ";
                std::cin >> date;

                Task task;
                std::cout << "Enter task title: ";
                std::cin.ignore();
                std::getline(std::cin, task.title);
                std::cout << "Enter task timing: ";
                std::getline(std::cin, task.timing);
                std::cout << "Enter task priority: ";
                std::getline(std::cin, task.priority);

                taskManager[date].push_back(task);
                std::cout << "Task added successfully." << std::endl;
                break;
            }

            case 2: // Modify Task
            {
                std::string date;
                std::cout << "Enter the date (e.g., YYYY-MM-DD) to modify tasks: ";
                std::cin >> date;

                auto dateIter = taskManager.find(date);

                if (dateIter == taskManager.end()) {
                    std::cout << "No tasks found for the specified date." << std::endl;
                } else {
                    std::cout << "Tasks for " << date << ":" << std::endl;

                    int i = 1;
                    for (const Task &task : dateIter->second) {
                        std::cout << i << ". " << task.title << " (" << task.timing << ")" << std::endl;
                        i++;
                    }

                    int taskChoice;
                    std::cout << "Enter the task number to modify or 0 to cancel: ";
                    std::cin >> taskChoice;

                    if (taskChoice == 0) {
                        break; // Exit the modification process.
                    }

                    if (taskChoice > 0 && taskChoice <= dateIter->second.size()) {
                        Task &selectedTask = dateIter->second[taskChoice - 1];

                        std::cout << "Current task title: " << selectedTask.title << std::endl;
                        std::cout << "Enter new task title: ";
                        std::cin.ignore();
                        std::getline(std::cin, selectedTask.title);
                        std::cout << "Current task timing: " << selectedTask.timing << std::endl;
                        std::cout << "Enter new task timing: ";
                        std::getline(std::cin, selectedTask.timing);
                        std::cout << "Current task priority: " << selectedTask.priority << std::endl;
                        std::cout << "Enter new task priority: ";
                        std::getline(std::cin, selectedTask.priority);

                        std::cout << "Task modified successfully." << std::endl;
                    } else {
                        std::cout << "Invalid task number." << std::endl;
                    }
                }

                break;
            }

            case 3: // Show Tasks
            {
                std::cout << "List of Tasks:" << std::endl;

                for (auto &entry : taskManager) {
                    std::string date = entry.first;
                    std::vector<Task> &tasks = entry.second;

                    std::cout << "Tasks for " << date << ":" << std::endl;

                    int i = 1;

                    // Sort the tasks by time or priority
                    std::cout << "Sort by (1) Time or (2) Priority: ";
                    int sortChoice;
                    std::cin >> sortChoice;

                    if (sortChoice == 1) {
                        std::sort(tasks.begin(), tasks.end(), sortByTime);
                    } else if (sortChoice == 2) {
                        std::sort(tasks.begin(), tasks.end(), sortByPriority);
                    } else {
                        std::cout << "Invalid sorting choice. Tasks will be displayed unsorted." << std::endl;
                    }

                    for (const Task &task : tasks) {
                        std::cout << i << ". " << task.title << " (" << task.timing << ") - Priority: " << task.priority << std::endl;
                        i++;
                    }
                }
                break;
            }

            case 4: // Delete Task
            {
                std::string date;
                std::cout << "Enter the date (e.g., YYYY-MM-DD) to delete tasks: ";
                std::cin >> date;

                auto dateIter = taskManager.find(date);

                if (dateIter == taskManager.end()) {
                    std::cout << "No tasks found for the specified date." << std::endl;
                } else {
                    std::cout << "Tasks for " << date << ":" << std::endl;

                    int i = 1;
                    for (const Task &task : dateIter->second) {
                        std::cout << i << ". " << task.title << " (" << task.timing << ")" << std::endl;
                        i++;
                    }

                    int taskChoice;
                    std::cout << "Enter the task number to delete or 0 to cancel: ";
                    std::cin >> taskChoice;

                    if (taskChoice == 0) {
                        break;
                    }

                    if (taskChoice > 0 && taskChoice <= dateIter->second.size()) {
                        dateIter->second.erase(dateIter->second.begin() + taskChoice - 1);
                        std::cout << "Task deleted successfully." << std::endl;
                    } else {
                        std::cout << "Invalid task number." << std::endl;
                    }
                }

                break;
            }

            case 5: // Quit
                std::cout << "All the best for your tasks. Goodbye!" << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
                break;
        }
    }

    return 0;
}

