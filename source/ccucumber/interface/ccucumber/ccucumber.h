#pragma once

#include <functional>
#include <string>

namespace ccucumber
{

class Step {};
using Define = std::initializer_list<Step>;

Step Given(std::string, std::function<void()>);

} // namespace

