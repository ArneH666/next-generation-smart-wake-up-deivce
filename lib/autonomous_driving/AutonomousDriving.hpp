#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AUTONOMOUSDRIVING_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AUTONOMOUSDRIVING_HPP

namespace autonomous_driving {
class Driver {
 public:
  Driver();
  void drive();

  bool activated = false;

 private:
  unsigned long last_step_millis = 0;
};
}  // namespace autonomous_driving

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AUTONOMOUSDRIVING_HPP
