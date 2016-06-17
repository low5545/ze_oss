#pragma once

#include <memory>
#include <imp/core/image_base.hpp>
#include <ze/imu/imu_buffer.h>
#include <ze/common/types.h>
#include <ze/common/time_conversions.h>
#include <ze/data_provider/camera_imu_synchronizer_base.hpp>

namespace ze {

// fwd
class DataProviderBase;
class ImageBase;

// -----------------------------------------------------------------------------
//! Uses an IMU Buffer that can handle model-based measurement corrections and
//! synchronization of gyroscope and accelerometer.it
class CameraImuSynchronizerUnsync: public CameraImuSynchronizerBase
{
public:
  // convenience typedefs
  using ImuSyncBuffer = ImuBufferLinear2000;
  using ImuBufferVector = std::vector<ImuSyncBuffer::Ptr>;

  //! Default constructor.
  CameraImuSynchronizerUnsync(DataProviderBase& data_provider,
                              const std::vector<ImuModel::Ptr>& imu_models);

  //! Add a Gyroscope measurement to the frame synchronizer.
  void addGyroData(
      int64_t stamp,
      const Vector3& gyr,
      const uint32_t imu_idx);

  //! Add an Accelerometer measurement to the frame synchronizer.
  void addAccelData(
      int64_t stamp,
      const Vector3& acc,
      const uint32_t imu_idx);

private:
  //! IMU buffer stores all imu measurements, size of imu_count_.
  ImuBufferVector imu_buffers_;

  //! Register callbacks in data provider to this class' addImgData, addGyroData
  //! and addAccelData.
  virtual void subscribeDataProvider(DataProviderBase& data_provider) override;

  //! Initialize the image and gyro/accel buffers
  void initBuffers(const std::vector<ImuModel::Ptr>& imu_models);

  //! This function checks if we have all data ready to call the callback.
  virtual void checkImuDataAndCallback();
};

} // namespace ze
