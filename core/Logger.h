#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <deque>

class Logger {
private:
    static constexpr std::size_t MAX_LOGGER_SIZE = 5;
    inline static std::deque<std::string> logger_;

public:
    static void add_message_to_logger(const std::string& message);
    static const std::deque<std::string>& get_logs();
    static void clear();
};

#endif //LOGGER_H
