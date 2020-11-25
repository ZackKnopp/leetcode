// https://leetcode.com/problems/the-dining-philosophers/
class DiningPhilosophers {
private:
    std::mutex fork_mutexes[5];

public:
    // Deadlock occurs if everyone picks up right fork at same time
    // or everyone picks up left for at same time.
    // Avoid deadlock by picking up 2 at a time whenever you touch a fork
    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int right = philosopher;
        int left = (philosopher + 1) % 5;
        
        // Lock both at the same time
        std::lock(fork_mutexes[right], fork_mutexes[left]);

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        
        // Unlock both
        fork_mutexes[right].unlock();
        fork_mutexes[left].unlock();        
    }
};
