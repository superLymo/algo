#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

namespace myAsync {
    template <typename T>
    class promise {
        T value {};
        std::atomic_bool ready {};

        std::mutex mut;
        std::condition_variable cv;

    public:
        explicit promise(T val) : value{val}, ready{true} {

        }

        auto setValue(T val) -> void {
            if (ready) {
                return;
            }

            std::scoped_lock lk(mut);

            value = val;
        }
    };
}