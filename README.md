# Face Detection with OpenCV DNN + CUDA (C++)

🚀 A real-time face detection application using OpenCV's DNN module accelerated with CUDA.  
This project demonstrates how to load a pretrained Caffe model and perform fast, GPU-accelerated inference using OpenCV in C++.

---

## 📷 Features

- Real-time face detection from webcam input
- GPU acceleration via OpenCV DNN + CUDA
- Uses the `res10_300x300_ssd` model (accurate and fast)
- Clean, minimal CMake-based build

---

## 🛠️ Requirements

- OpenCV **compiled with CUDA** support (`WITH_CUDA=ON`, `OPENCV_DNN_CUDA=ON`)
- CMake ≥ 3.10
- NVIDIA GPU with CUDA drivers installed
- Linux or Windows

---

## 📁 Project Structure

FaceDetectCUDA/
├── CMakeLists.txt
├── main.cpp
└── models/
├── deploy.prototxt
└── res10_300x300_ssd_iter_140000.caffemodel

yaml
Copy
Edit

---

## 🔧 Setup Instructions

### 1. Clone the Repo (or Copy Files)
```bash
git clone <your-repo-url>
cd FaceDetectCUDA
2. Download Model Files
Download from OpenCV GitHub:

deploy.prototxt

res10_300x300_ssd_iter_140000.caffemodel

Place them in the models/ directory.

3. Build the Project
bash
Copy
Edit
mkdir build && cd build
cmake ..
make
4. Run
bash
Copy
Edit
./face_detect_cuda
Press ESC to exit.

🧠 How It Works
Uses cv::dnn::readNetFromCaffe() to load the model

Converts the webcam frame into a blob with cv::dnn::blobFromImage

Runs forward pass on the GPU using:

cpp
Copy
Edit
net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
Draws rectangles around faces if detection confidence > 0.5

📌 Example Output

📚 References
OpenCV DNN Docs

Model Zoo: Face Detector

📝 License
MIT License – feel free to use and modify.

✨ Future Ideas
Add face tracking

Use ONNX models (e.g., RetinaFace)

Add face recognition (embedding + matching)

Stream results via web interface

vbnet
Copy
Edit

Let me know if you'd like me to include a GIF/image demo placeholder or generate a downloadable `.zip` archive for offline use.










