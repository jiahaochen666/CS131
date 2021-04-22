#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

typedef struct phil_data {
    int phil_num;
    int course;
    std::atomic<bool> fork; // false - available for use, true - occupied
    std::time_t meal_time[3];
} phil_data;

std::time_t start_time;

int num_threads;

/* ****************Change function below***************** */
void eat_meal(phil_data &this_philosopher, phil_data &next_philosopher) {
/* 3 course meal: Each need to acquire both forks 3 times.
 * First try for fork in front.
 * Then for the one on the right, if not fetched, put the first one back.
 * If both acquired, eat one course.
 * Record time for each meal for the philosophers.
 * Use 'std::this_thread::sleep_for (std::chrono::seconds(1));' to sleep the thread for 1 second.
 */
    while (this_philosopher.course < 3) {
        bool first_fork = false;
        if ((this_philosopher.fork).compare_exchange_strong(first_fork, false)) {
            this_philosopher.fork = true;
            //std::cout << "Philosopher " << this_philosopher.phil_num << " starts to eat." << std::endl;
            if ((next_philosopher.fork).compare_exchange_strong(first_fork, false)) {
                next_philosopher.fork = true;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                //std::cout << "Philosopher " << this_philosopher.phil_num << " finishes eating " << this_philosopher.course << " time" << std::endl;
                this_philosopher.fork = false;
                next_philosopher.fork = false;
                std::time_t current_time;
                this_philosopher.meal_time[this_philosopher.course] = std::time(&current_time);
                this_philosopher.course++;
            } else {
                this_philosopher.fork = false;
//                std::cout << "Philosopher " << this_philosopher.phil_num << " pauses eating to wait for others."
//                          << std::endl;
            }
        } else {
            //std::cout << "Philosopher " << this_philosopher.phil_num << " has no fork to use." << std::endl;
        }
    }
}

/* ****************Change function below***************** */
void dispatch_threads(phil_data *philosophers) {
/* Create and Join threads here
 * Each thread will represent a philosopher
 */
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads - 1; i++) {
        threads.emplace_back(eat_meal, std::ref(philosophers[i]), std::ref(philosophers[i + 1]));
    }
    threads.emplace_back(eat_meal, std::ref(philosophers[num_threads - 1]), std::ref(philosophers[0]));
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
}

int main(int argc, char **argv) {
    int num_philosophers, num_forks, error;

    if (argc < 2) {
        std::cerr << "Format: " << argv[0] << " <Number of philosophers>" << std::endl;
        return 0;
    }

    num_philosophers = num_threads = num_forks = std::atoi(argv[1]);
    phil_data *philosophers = new phil_data[num_threads];

    /* Initialize philosophers */
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].phil_num = i;
        philosophers[i].course = 0;
        philosophers[i].fork = false;
    }

    /* Syntax to record time.
    While printing meal times for each philosopher, subtract start_time from recorded values */
    std::time(&start_time);

    /* Launch threads */
    dispatch_threads(philosophers);

    /*******************Print meal times for each philosopher here************/

    for (int i = 0; i < num_philosophers; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << "Philosopher " << i + 1 << " finish NO." << j + 1 << " meal at time "
                      << philosophers[i].meal_time[j] - start_time << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}