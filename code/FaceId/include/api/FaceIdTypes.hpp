#pragma once

#include <vector>
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>


// Forward declarations
struct Point2D;
struct BoundingBox;
struct FaceDetection;
struct FaceLandmarks;
struct FaceEmbedding;
struct FaceMatch;
struct Person;

// Basic geometric types
struct Point2D {
    float x, y;
    Point2D() : x(0), y(0) {}
    Point2D(float x, float y) : x(x), y(y) {}
};

struct BoundingBox {
    float x, y, width, height;
    float confidence;
    
    BoundingBox() : x(0), y(0), width(0), height(0), confidence(0.0f) {}
    BoundingBox(float x, float y, float w, float h, float conf = 1.0f)
        : x(x), y(y), width(w), height(h), confidence(conf) {}
    
    cv::Rect toCvRect() const {
        return cv::Rect(static_cast<int>(x), static_cast<int>(y), 
                       static_cast<int>(width), static_cast<int>(height));
    }
};

// Face detection result
struct FaceDetection {
    BoundingBox bbox;
    float confidence;
    cv::Mat face_image;
    
    FaceDetection() : confidence(0.0f) {}
    FaceDetection(const BoundingBox& box, float conf) 
        : bbox(box), confidence(conf) {}
};

// Face landmarks (68 points standard)
struct FaceLandmarks {
    std::vector<Point2D> points;
    float confidence;
    
    FaceLandmarks() : confidence(0.0f) {}
    
    // Get specific landmark groups
    std::vector<Point2D> getLeftEye() const;
    std::vector<Point2D> getRightEye() const;
    std::vector<Point2D> getNose() const;
    std::vector<Point2D> getMouth() const;
    std::vector<Point2D> getJawline() const;
};

// Face embedding/encoding
struct FaceEmbedding {
    std::vector<float> features;
    std::string model_name;
    float quality_score;
    
    FaceEmbedding() : quality_score(0.0f) {}
    FaceEmbedding(const std::vector<float>& feat, const std::string& model = "", float quality = 1.0f)
        : features(feat), model_name(model), quality_score(quality) {}
    
    // Calculate cosine similarity
    float cosineSimilarity(const FaceEmbedding& other) const;
    float euclideanDistance(const FaceEmbedding& other) const;
};

// Face match result
struct FaceMatch {
    std::string person_id;
    std::string person_name;
    float similarity;
    float distance;
    bool is_match;
    
    FaceMatch() : similarity(0.0f), distance(1.0f), is_match(false) {}
    FaceMatch(const std::string& id, const std::string& name, float sim, float dist, bool match)
        : person_id(id), person_name(name), similarity(sim), distance(dist), is_match(match) {}
};

// Person in database
struct Person {
    std::string id;
    std::string name;
    std::string metadata;
    std::vector<FaceEmbedding> embeddings;
    std::vector<std::string> image_paths;
    
    Person() {}
    Person(const std::string& person_id, const std::string& person_name)
        : id(person_id), name(person_name) {}
};

// Configuration structures
struct ImageProcessingConfig {
    bool flip = false;
    bool normalize = true;
    bool resize = true;
    int resize_width = 640;
    int resize_height = 640;
    bool grayscale = false;
    bool equalize = false;
    bool rotate = false;
    int rotate_angle = 0;
    bool crop = false;
    uint16_t crop_x = 0;
    uint16_t crop_y = 0;
    uint16_t crop_width = 0;
    uint16_t crop_height = 0;
    bool detect_faces = false;
};


struct DetectionConfig {
    float confidence_threshold = 0.7f;
    float nms_threshold = 0.4f;
    int input_size = 640;
    std::string model_path;
    std::string backend = "opencv";
};

struct RecognitionConfig {
    float similarity_threshold = 0.6f;
    int embedding_size = 512;
    bool normalize_embeddings = true;
    std::string model_path;
    std::string backend = "opencv";
};

struct DatabaseConfig {
    std::string type = "sqlite";
    std::string connection_string;
    std::string table_name = "faces";
    bool auto_create = true;
};


struct FaceEncoderConfig
{
	std::string model_path;
	int batch_size = 1; // Default batch size
	std::string backend = "opencv";
};


struct FaceAlignerConfig
{
	std::string model_path;
	int input_size = 112; // Default input size for face alignment
	bool normalize = true; // Normalize the aligned face
	std::string backend = "opencv";
};

// Error codes
enum class ErrorCode {
    SUCCESS = 0,
    INVALID_CONFIG,
    INVALID_INPUT,
    MODEL_LOAD_FAILED,
    INFERENCE_FAILED,
    DATABASE_ERROR,
    NO_FACE_DETECTED,
    POOR_QUALITY_IMAGE,
    PERSON_NOT_FOUND,
    DUPLICATE_PERSON,
    CONFIGURATION_ERROR
};

// Result wrapper
template<typename T>
struct Result {
    T data;
    ErrorCode error_code;
    std::string error_message;
    
    Result() : error_code(ErrorCode::SUCCESS) {}
    Result(const T& d) : data(d), error_code(ErrorCode::SUCCESS) {}
    Result(ErrorCode code, const std::string& msg) : error_code(code), error_message(msg) {}
    
    bool isSuccess() const { return error_code == ErrorCode::SUCCESS; }
    bool hasError() const { return error_code != ErrorCode::SUCCESS; }
};



struct LoggerConfig
{
	std::string name = "faceid_logger";
	// Default values
	std::string log_file = "faceid.log";
    std::string log_level = "info"; //spdlog::level::info;
	std::string flush_level = "warn"; //spdlog::level::warn;
	bool enable_console_output = true;
	bool enable_file_output = true;
	std::string console_pattern = "[%Y-%m-%d %H:%M:%S] [%l] %v";
	std::string file_pattern = "[%Y-%m-%d %H:%M:%S] [%l] %v";
};

// Image quality assessment
enum class QualityMetric {
    SHARPNESS,
    BRIGHTNESS,
    CONTRAST,
    FACE_SIZE,
    HEAD_POSE,
    EYE_OPENNESS,
    OVERALL
};

struct QualityAssessment {
    float sharpness_score = 0.0f;
    float brightness_score = 0.0f;
    float contrast_score = 0.0f;
    float face_size_score = 0.0f;
    float head_pose_score = 0.0f;
    float eye_openness_score = 0.0f;
    float overall_score = 0.0f;
    bool is_acceptable = false;
    
    float getScore(QualityMetric metric) const;
};