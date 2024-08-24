///
/// @file    Task.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-01 11:08:51
///

#ifndef __WD_TASK_HPP__
#define __WD_TASK_HPP__

#include <functional>
#include <memory>
#include "./Thread.hpp"

namespace se
{

    using Task = std::function<void()>;

} //end of namespace se

#endif
