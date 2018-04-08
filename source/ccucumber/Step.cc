#include "ccucumber.h"

namespace ccucumber
{

class CcStep : public Step {
  public:
    virtual void action(std::function<void()>) override;
};

void CcStep::action(std::function<void()>) {
}

Step & Given(std::string) {
  static CcStep dummy;
  return dummy;
}

} // namespace

