// https://leetcode.com/problems/print-zero-even-odd/
enum PrintType {
    ZERO,
    ODD,
    EVEN
};

class ZeroEvenOdd {
private:
    int n;
    int i = 1;
    std::mutex mutex;
    std::condition_variable cv;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }
    
    PrintType shouldPrint(int i) {
        if(i % 2 == 1) {
            return ZERO;
        } else if(i % 4 == 0) {
            return EVEN;
        }
        
        return ODD;
    };
    
    bool done() {
        return i > 2 * n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            
            cv.wait(lock, [this] {
                return shouldPrint(i) == ZERO || done();
            });
            
            if(done()) {
                break;
            }

            printNumber(0);
            i++;
            mutex.unlock();
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            
            cv.wait(lock, [this] {
                return shouldPrint(i) == EVEN || done();
            });
            
            if(done()) {
                break;
            }

            printNumber(i/2);
            i++;
            mutex.unlock();
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(true) {
            std::unique_lock<std::mutex> lock(mutex);
            
            cv.wait(lock, [this] {
                return shouldPrint(i) == ODD || done();
            });
            
            if(done()) {
                break;
            }

            printNumber(i/2);
            i++;
            mutex.unlock();
            cv.notify_all();
        }
    }
};
