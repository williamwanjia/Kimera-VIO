/* ----------------------------------------------------------------------------
 * Copyright 2017, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Luca Carlone, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 * -------------------------------------------------------------------------- */

/**
 * @file   LoggerMatlab.h
 * @brief  Logging information for matlab stats and visualizations
 * @author Luca Carlone, Antoni Rosinol
 */

#ifndef LoggerMatlab_H_
#define LoggerMatlab_H_

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "VioBackEnd.h"
#include "datasource/ETH_parser.h"

namespace VIO {

// TODO Make Logger Thread-safe!
////////////////////////////////////////////////////////////////////////////////
/// \brief The LoggerMatlab class
///
class LoggerMatlab {
 public:
  LoggerMatlab();

  // Path where to store output files.
  const std::string output_path_;
  std::ofstream outputFile_;
  std::ofstream outputFile_posesVIO_;
  std::ofstream outputFile_posesVIO_csv_;
  std::ofstream outputFile_posesVIO_csv_pipeline_;
  std::ofstream outputFile_posesGT_;
  std::ofstream outputFile_landmarks_;
  std::ofstream outputFile_normals_;
  std::ofstream outputFile_smartFactors_;
  std::ofstream outputFile_timingVIO_;
  std::ofstream outputFile_timingTracker_;
  std::ofstream outputFile_timingOverall_;
  std::ofstream outputFile_statsTracker_;
  std::ofstream outputFile_statsFactors_;
  std::ofstream outputFile_mesh_;
  std::ofstream outputFile_frontend_;
  std::ofstream outputFile_initPerformance_;

  gtsam::Pose3 W_Pose_Bprevkf_vio_;

  double timing_loadStereoFrame_, timing_processStereoFrame_,
      timing_featureSelection_, timing_loggerBackend_;

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void openLogFiles(int i = -1, const std::string& output_file_name = "",
                    bool open_file_in_append_mode = false);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void closeLogFiles(int i = -1);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logFrontendResults(const TrackerStatusSummary& tracker_summary,
                          const size_t& nrKeypoints);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logLandmarks(const PointsWithId& lmks);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logLandmarks(const cv::Mat& lmks);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logNormals(const std::vector<cv::Point3f>& normals);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logMesh(const cv::Mat& lmks, const cv::Mat& colors, const cv::Mat& mesh,
               const double& timestamp, bool log_accumulated_mesh = false);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logBackendResultsCSV(const VioBackEndOutputPayload& vio_output);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logPipelineResultsCSV(const SpinOutputPacket& vio_output);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logInitializationResultsCSV(const InitializationPerformance& perf,
                                  const double& ba_duration,
                                  const double& alignment_duration,
                                  const bool& is_successful);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logBackendResults(
      const ETHDatasetParser& dataset,
      const TrackerStatusSummary& tracker_status_summary,
      const gtsam::Pose3& relative_pose_body_mono, const Tracker& tracker,
      const gtsam::Pose3& relative_pose_body_stereo,
      const std::shared_ptr<VioBackEndOutputPayload>& vio_output,
      const double& horizon, const Timestamp& timestamp_lkf,
      const Timestamp& timestamp_k, const size_t& k);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void logPipelineOverallTiming(const std::chrono::milliseconds& duration);

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void displayInitialStateVioInfo(const std::unique_ptr<VioBackEnd>& vio,
                                  gtNavState initialStateGT,
                                  const ImuAccGyrS& imu_accgyr,
                                  const Timestamp timestamp_k) const;

  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  void displayOverallTiming() const;
};

}  // namespace VIO
#endif /* LoggerMatlab_H_ */
