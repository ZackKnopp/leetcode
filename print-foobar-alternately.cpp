// https://leetcode.com/problems/print-foobar-alternately/
class FooBar {
private:
    int n;
    std::mutex mutex;
    std::condition_variable cv;
    bool shouldFoo = true; // true if should foo, otherwise should bar

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return shouldFoo;
            });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            shouldFoo = false;
            mutex.unlock();
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] {
                return !shouldFoo; 
            });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            shouldFoo = true;
            mutex.unlock();
            cv.notify_all();
        }
    }
};
