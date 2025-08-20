#pragma once
#include "date/date.h"
#include <sstream>
#include <vector>

enum class ValidationResult
{
    SUCCESS,
    EMPTY,
    INVALID_DATE,
    NEGATIVE,
    NONNUMERIC,
    EXCEEDS
};

struct normalDateStatus
{
    ValidationResult status;
    std::string normalDate;
};

namespace Validation
{
    normalDateStatus validateAndNormalizeDate(const std::string& date);
    ValidationResult validateAmount(const std::string& amount);
    ValidationResult validateString(const std::string& str);
}
