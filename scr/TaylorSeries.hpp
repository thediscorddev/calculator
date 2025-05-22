#pragma once
#include "Function_Composed.hpp"
#include "Function_Number.hpp"
#include "Function_Operation.hpp"
#include "Function_Variable.hpp"
#include "Derivative.hpp"
#include <memory>
class TaylorSeries
{
    public:
       static std::shared_ptr<Function_Composed> GenerateTaylorSeries(std::shared_ptr<Function_Composed> function, double center, int terms);
       static std::shared_ptr<Function_Composed> GenerateMaclaurinSeries(std::shared_ptr<Function_Composed> function, int terms);
       static std::shared_ptr<Function_Number> N_DerivativeAt(std::shared_ptr<Function_Composed> function, double index, int NumOrDerivative);
       static std::shared_ptr<Function_Composed> N_Derivative(std::shared_ptr<Function_Composed> function, int NumOrDerivative);
};