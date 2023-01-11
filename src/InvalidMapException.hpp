#pragma once
#include <exception>
#include <iostream>

/// @brief InvalidMapException class that derives std library exception class.
class InvalidMapException : public std::exception {
  virtual const char* what() const noexcept { return "Invalid map!"; }
};
