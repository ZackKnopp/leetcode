// https://leetcode.com/problems/fizz-buzz-multithreaded/
#include <mutex>
#include <condition_variable>

enum FizzType {
    FIZZ,
    BUZZ,
    FIZZBUZZ,
    NONE,
    TYPE_NOT_FOUND
};

class FizzBuzz {
private:
    int n;
    int i = 1;
    std::mutex mutex;
    std::condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
    }
    
    FizzType getType() {
        if(i % 3 != 0 && i % 5 != 0) {
            return NONE;
        } else if(i % 3 == 0 && i % 5 == 0) {
            return FIZZBUZZ;
        } else if(i % 5 == 0) {
            return BUZZ;
        } else if(i % 3 == 0) {
            return FIZZ;
        }
        
        return TYPE_NOT_FOUND;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return getType() == FIZZ || i > n;
            });
            
            if(i > n) {
                break;
            }
            
            printFizz();
            
            i++;
            cv.notify_all();
        }
       
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return getType() == BUZZ || i > n;
            });
            
            if(i > n) {
                break;
            }
            
            printBuzz();

            i++;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return getType() == FIZZBUZZ || i > n;
            });
            
            if(i > n) {
                break;
            }
            
            printFizzBuzz();

            i++;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return getType() == NONE || i > n;
            });
            
            if(i > n) {
                break;
            }
            
            printNumber(i);
            
            i++;
            cv.notify_all();
        }
    }
};
