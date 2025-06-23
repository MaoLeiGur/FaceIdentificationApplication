#include "utils/logger.hpp"


Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}

std::shared_ptr<spdlog::logger>& Logger::getLogger()
{
	return logger_;
}

void Logger::init(const LoggerConfig& config) {
	config_ = config;
	// Create logger with specified name
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::from_str(config.log_level));

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(config.log_file, true);
	file_sink->set_level(spdlog::level::from_str(config.log_level));

	logger_ = std::make_shared<spdlog::logger>(config.name, spdlog::sinks_init_list{ console_sink, file_sink });
	logger_->set_level(spdlog::level::from_str(config.log_level));
	logger_->flush_on(spdlog::level::from_str(config.flush_level));
	// Set pattern for log messages
	//logger_->set_pattern(config.pattern);
}