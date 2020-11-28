// https://leetcode.com/problems/building-h2o/
#include <mutex>
#include <condition_variable>

class H2O {
private:
    std::mutex hydro_mutex;
    std::queue<function<void()>> hydro_queue;
    std::mutex oxy_mutex;
    std::queue<function<void()>> oxy_queue;

public:
    void log(std::string msg) {
        cout << msg << "\n";
    }

    void hydrogen(function<void()> releaseHydrogen) {
        {
            std::lock_guard lock(hydro_mutex);
            hydro_queue.push(releaseHydrogen);
        }

        tryRelease();
    }

    void oxygen(function<void()> releaseOxygen) {
        {
            std::lock_guard lock(oxy_mutex);
            oxy_queue.push(releaseOxygen);
        }

        tryRelease();
    }
    
    void tryRelease() {
        std::lock(hydro_mutex, oxy_mutex);
        log("tryRelease()");
        log("Hydrogen:" + to_string(hydro_queue.size()));
        log("Oxygen:" + to_string(oxy_queue.size()));
        if(hydro_queue.size() >= 2 && oxy_queue.size() >=1) {
            hydro_queue.front()();
            hydro_queue.pop();
            
            hydro_queue.front()();
            hydro_queue.pop();
            
            oxy_queue.front()();
            oxy_queue.pop();
        }
        hydro_mutex.unlock();
        oxy_mutex.unlock();
    }
};
