//   Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "yaml-cpp/yaml.h"

#ifdef _WIN32
#define OS_PATH_SEP "\\"
#else
#define OS_PATH_SEP "/"
#endif

namespace PaddleDetection {

// Inference model configuration parser
class ConfigPaser {
 public:
  ConfigPaser() {}

  ~ConfigPaser() {}

  bool load_config(const std::string& model_dir,
                   const std::string& cfg = "infer_cfg.yml") {
    // Load as a YAML::Node
    YAML::Node config;
    config = YAML::LoadFile(model_dir + OS_PATH_SEP + cfg);

    // Get runtime mode : fluid, trt_fp16, trt_fp32
    if (config["mode"].IsDefined()) {
      mode_ = config["mode"].as<std::string>();
    } else {
      std::cerr << "Please set mode, "
                << "support value : fluid/trt_fp16/trt_fp32."
                << std::endl;
      return false;
    }

    // Get model arch : YOLO, SSD, RetinaNet, RCNN, Face
    if (config["arch"].IsDefined()) {
      arch_ = config["arch"].as<std::string>();
    } else {
      std::cerr << "Please set model arch,"
                << "support value : YOLO, SSD, RetinaNet, RCNN, Face."
                << std::endl;
      return false;
    }

    // Get min_subgraph_size for tensorrt
    if (config["min_subgraph_size"].IsDefined()) {
      min_subgraph_size_ = config["min_subgraph_size"].as<int>();
    } else {
      std::cerr << "Please set min_subgraph_size." << std::endl;
      return false;
    }
    // Get draw_threshold for visualization
    if (config["draw_threshold"].IsDefined()) {
      draw_threshold_ = config["draw_threshold"].as<float>();
    } else {
      std::cerr << "Please set draw_threshold." << std::endl;
      return false;
    }
    // Get Preprocess for preprocessing
    if (config["Preprocess"].IsDefined()) {
      preprocess_info_ = config["Preprocess"];
    } else {
      std::cerr << "Please set Preprocess." << std::endl;
      return false;
    }
    // Get label_list for visualization
    if (config["label_list"].IsDefined()) {
      label_list_ = config["label_list"].as<std::vector<std::string>>();
    } else {
      std::cerr << "Please set label_list." << std::endl;
      return false;
    }

    // Get use_dynamic_shape for TensorRT
    if (config["use_dynamic_shape"].IsDefined()) {
      use_dynamic_shape_ = config["use_dynamic_shape"].as<bool>();
    } else {
      std::cerr << "Please set use_dynamic_shape." << std::endl;
      return false;
    }

    return true;
  }
  std::string mode_;
  float draw_threshold_;
  std::string arch_;
  int min_subgraph_size_;
  YAML::Node preprocess_info_;
  std::vector<std::string> label_list_;
  bool use_dynamic_shape_;
};

}  // namespace PaddleDetection

