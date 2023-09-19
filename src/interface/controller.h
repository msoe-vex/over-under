#pragma once
namespace interface {
enum class ControllerJoystick { kLeftX, kLeftY, kRightX, kRightY };

enum class ControllerButton {
  kA,
  kX,
  kY,
  kB,
  kLeftBumper,
  kRightBumper,
  kUp,
  kDown,
  kLeft,
  kRight
};  // last four variables refer to the d-pad

enum class ControllerTrigger { kLeft, kRight };  // refers to triggers

class Controller {
 public:
  [[nodiscard]] virtual int GetJoystickAnalog(
      ControllerJoystick joystick) const = 0;
  [[nodiscard]] virtual float GetJoystickVoltage(
      ControllerJoystick joystick) const = 0;
  [[nodiscard]] virtual bool GetButton(ControllerButton button) const = 0;
  [[nodiscard]] virtual float GetTrigger(ControllerTrigger trigger) const = 0;

  virtual ~Controller() = default;
};
}  // namespace interface