#pragma once

#include <functional>
#include <string>

namespace ccucumber
{

class Steps {
  public:
    Steps(std::function<void()>);
};

class Step {
  public:
    virtual void action(std::function<void()>) = 0;
};

Step & Given(std::string);

} // namespace

