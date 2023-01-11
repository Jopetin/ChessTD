#pragma once
#include <exception>
#include <iostream>

/// @brief InvalidWaveException class that derives std library exception class. 
class InvalidWaveException : public std::exception {
  virtual const char* what() const noexcept { return "Invalid wave!"; }
};
