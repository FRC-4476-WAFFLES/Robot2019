/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
using namespace frc;
using namespace nt;

class CameraSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<NetworkTable> camera = NetworkTableInstance::GetDefault().GetTable("limelight");
 public:
  CameraSubsystem();
  void InitDefaultCommand() override;
  void SetLedMode(int mode);
  double GetCameraTX();
  double GetCameraTV();
  double GetCameraTS();
  double GetCameraTA();
  void SetCameraProcessingMode(int mode);
  enum CameraLEDMode {
    Default = 0,
    Off = 1,
    Strobe = 2,
    On = 3,
  };
  enum ProcessingMode {
    Vision = 0,
    Driver = 1,
  };
};
//getting data
/*
tv	Whether the limelight has any valid targets (0 or 1)
tx	Horizontal Offset From Crosshair To Target (-27 degrees to 27 degrees)
ty	Vertical Offset From Crosshair To Target (-20.5 degrees to 20.5 degrees)
ta	Target Area (0% of image to 100% of image)
ts	Skew or rotation (-90 degrees to 0 degrees)
tl	The pipeline’s latency contribution (ms) Add at least 11ms for image capture latency.
tshort	Sidelength of shortest side of the fitted bounding box (pixels)
tlong	Sidelength of longest side of the fitted bounding box (pixels)
thor	Horizontal sidelength of the rough bounding box (0 - 320 pixels)
tvert	Vertical sidelength of the rough bounding box (0 - 320 pixels)
getpipe	True active pipeline index of the camera (0 .. 9)
*/

//sending data
/*
ledMode	Sets limelight’s LED state
0	use the LED Mode set in the current pipeline
1	force off
2	force blink
3	force on

camMode	Sets limelight’s operation mode
0	Vision processor
1	Driver Camera (Increases exposure, disables vision processing)

stream	Sets limelight’s streaming mode
0	Standard - Side-by-side streams if a webcam is attached to Limelight
1	PiP Main - The secondary camera stream is placed in the lower-right corner of the primary camera stream
2	PiP Secondary - The primary camera stream is placed in the lower-right corner of the secondary camera stream
*/