#pragma once  

#include <memory>  


#include <spdlog/spdlog.h>  
#include <spdlog/sinks/stdout_color_sinks.h>  
#include <spdlog/sinks/basic_file_sink.h>
#include <mutex>  


#include "api/FaceIdTypes.hpp"

class Logger {
public:
    
    static Logger& getInstance();
    void init(const LoggerConfig& config);
    std::shared_ptr<spdlog::logger>& getLogger();
    // Access singleton instance  
    

private:
	Logger() = default; // Private constructor for singleton pattern


    LoggerConfig  config_;
    std::shared_ptr<spdlog::logger> logger_;
};
