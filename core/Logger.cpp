#include "Logger.h"

const std::deque<std::string> &Logger::get_logs() {
    return logger_;
}

void Logger::add_message_to_logger(const std::string& message) {
    if (logger_.size() >= MAX_LOGGER_SIZE)
        logger_.pop_front();

    logger_.push_back(message);
}

void Logger::clear() {
    logger_.clear();
}
