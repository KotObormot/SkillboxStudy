#include <iostream>
#include <ctime>
#include <limits> // для std::numeric_limits
#include <iomanip>
#include <fstream>
#include <map>
#include <string>

struct Task {
    std::time_t timeStart;
    bool isTaskCompleted;
    std::string taskName;
};

void new_task(std::map<std::time_t, Task>& todo_list) {
    Task task;
    task.isTaskCompleted = false;
    task.timeStart = std::time(nullptr);
    std::cout << "Enter task name--> ";
    std::getline(std::cin, task.taskName);
    std::cout << "Start time " << std::put_time(std::gmtime(&task.timeStart), "%d.%m.%Y %H:%M:%S %Z") << ".\n";
    std::time_t timeFinish {0};
    std::pair<std::time_t, Task> task_new(timeFinish, task);
    todo_list.insert(task_new);
}

void end_task(std::map<std::time_t, Task>& todo_list) {
    std::map<std::time_t, Task>::iterator it_complete(todo_list.begin());
    if(it_complete->second.isTaskCompleted) {
        std::cout << "There are no unfinished tasks.\n";
        return;
    } else {
        std::time_t timeFinish1 = std::time(nullptr);
        Task task1 {};
        task1.timeStart = it_complete->second.timeStart;
        task1.isTaskCompleted = true;
        task1.taskName = it_complete->second.taskName;
        todo_list.erase(it_complete);
        std::pair<std::time_t, Task> task_completed(timeFinish1, task1);
        todo_list.insert(task_completed);
        std::cout << "Task completed.\n";
    }
}

void safe_todo_list(const std::string& directory, const std::map<std::time_t, Task>& todo_list) {
    std::ofstream tsks(directory + "todo_list.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    size_t list_size = todo_list.size();
    tsks.write((char*)& list_size, sizeof(list_size));
    for(const auto& [timeFinish, task] : todo_list) {
        tsks.write((char*)& timeFinish, sizeof(timeFinish));
        tsks.write((char*)& task.timeStart, sizeof(task.timeStart));
        tsks.write((char*)& task.isTaskCompleted, sizeof(task.isTaskCompleted));
        int len = task.taskName.length();
        tsks.write((char*)& len, sizeof(len));
        tsks.write(task.taskName.c_str(), len);
    }
    tsks.close();
}

bool load_todo_list(const std::string& directory, std::map<std::time_t, Task>& todo_list) {
    bool isTasks {false};
    Task task;
    std::ifstream tsks(directory + "todo_list.bin", std::ios::in | std::ios::binary); 
    if(!tsks.is_open()) {
        return isTasks;
    }                                  
    else {
        isTasks = true;
        while(true) {
            std::time_t timeFinish {};
            Task task {};
            size_t list_size {};
            tsks.read((char*)& list_size, sizeof(list_size));
            for(int i = 0; i < list_size; ++i) {
                tsks.read((char*)& timeFinish, sizeof(timeFinish));
                tsks.read((char*)& task.timeStart, sizeof(task.timeStart));
                tsks.read((char*)& task.isTaskCompleted, sizeof(task.isTaskCompleted));
                int len {};
                tsks.read((char*)& len, sizeof(len));
                task.taskName.resize(len);
                tsks.read((char*) task.taskName.c_str(), len);
                std::pair<std::time_t, Task> task_new(timeFinish, task);
                todo_list.insert(task_new);
            }
            if(tsks.eof()) {           
                break;                 
            }
        }
        tsks.close();                               
    }
    return isTasks;
}

void print_tasks(std::map<std::time_t, Task>& todo_list, bool show_completed) {
    if(show_completed) {
        std::cout << "COMPLETED TASKS\n"; 
        for(const auto& [key, task] : todo_list) {
            if(task.isTaskCompleted) {
                std::cout << task.taskName << "\n";
                std::cout << "Start time " << std::put_time(std::gmtime(&task.timeStart), "%d.%m.%Y %H:%M:%S %Z") << ".\n";
                std::cout << "Finish time " << std::put_time(std::gmtime(&key), "%d.%m.%Y %H:%M:%S %Z") << ".\n";
                double duration_of_work = std::difftime(key, task.timeStart);
                std::cout << "Duration " 
                          << (int)duration_of_work / (3600 * 24) << " days "
                          << ((int)duration_of_work % (3600 * 24)) / 3600 << " hrs. "
                          << ((int)duration_of_work % 3600) / 60 << " min. "
                          << ((int)duration_of_work % 3600) % 60 << " sec.\n";
            }
            std::cout << "-------------------------------------------------\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "UNFINISHED TASKS\n";
        std::map<std::time_t, Task>::iterator it_complete(todo_list.begin());
        if(it_complete->second.isTaskCompleted) {
            std::cout << "There are no unfinished tasks.\n";
            return;
        } else { 
            std::cout << it_complete->second.taskName << "\n";
            std::cout << "Start time " << std::put_time(std::gmtime(&it_complete->second.timeStart), "%d.%m.%Y %H:%M:%S %Z") << ".\n";
            std::cout << "Not done.\n";
        }
        std::cout << "\n";
    }    
}

int main() {
    std::cout << "Hello!\n";
    std::map<std::time_t, Task> todo_list {};
    std::cout << "Loading... Just a moment please.\nSpecify the directory with the saved to-do list --> ";
    std::string directory {};
    std::cin >> directory;
    if(!load_todo_list(directory, todo_list)) {
        std::cerr << "No saved to-do list. Start a new task please.\n";
        new_task(todo_list);
    } else {
        std::map<std::time_t, Task>::iterator it {todo_list.begin()};       
        if(it->second.isTaskCompleted) {
            std::cout << "All tasks are completed. You have no unfinished tasks.\n";
        } else {
            std::cout << "You have an unfinished task: \n";
            print_tasks(todo_list, it->second.isTaskCompleted);
        }        
    }
    std::string command {};
    while(command != "exit") {
        std::cout << "Give the command--> ";
        std::cin.clear();
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i {0}; i < command.size(); ++i) {
            command[i] = std::tolower(command[i]);
        }
        while(command != "begin"
                && command != "end"
                && command != "status"
                && command != "exit") {        
            std::cout << "Give me the right command at last--> ";
            std::cin.clear();
            std::cin >> command;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for(int i {0}; i < command.size(); ++i) {
                command[i] = std::tolower(command[i]);
            }   
        }
        if(command == "begin") {
            end_task(todo_list);
            new_task(todo_list);
        } else if(command == "end") {
            end_task(todo_list);
        } else if(command == "status") {
            print_tasks(todo_list, true);
            print_tasks(todo_list, false);
        } else if(command == "exit") {
            safe_todo_list(directory, todo_list);
        }
    }
    return 0;
}