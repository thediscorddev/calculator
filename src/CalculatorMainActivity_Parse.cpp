#include "../scr/CalculatorMainActivity.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
double CalculatorMainActivity::Calculate(int index)
{
    //Parser
    float CurrentNumPart = 0;
    int decimalNum = 0;
    int bracketLevel = 0;
    std::vector<int> FinishedId;
    int Hid = 0;
    int CurrentId = 0;
    std::map<std::string,std::vector<std::string>> ValueList; //important
    std::map<std::string, bool> CalculatedValueList; // important
    std::map<std::string,std::string> Ftype; //important
    std::vector<std::string> PlannedOperation;

    for(int i = index-1; i < CurrentInput.size(); i++)
    {
        const auto& a = CurrentInput.at(i);
        try
        {
            if(decimalNum == 0) CurrentNumPart=CurrentNumPart*10+std::stoi(a);
            else {
                int m = 1;
                for(int i = 0; i < decimalNum; i++)
                {
                    m*=10;
                }
                CurrentNumPart+=(float) std::stoi(a)/m;
                decimalNum++;
            }
        }
        catch(const std::exception& e)
        {
            // Not a number, possibly "*", "-", "+", "\", "sin("
            if(a == ".") {
                decimalNum = 1;
            } else if(a == "+" || a == "-" || a == "*" || a == "/") {
                std::string o = a;
                if(CurrentId == 0) {
                    if(CurrentNumPart != 0) PlannedOperation.push_back(std::to_string(CurrentNumPart));
                    PlannedOperation.push_back(o);
                }else {
                    if(CurrentNumPart != 0) ValueList["__id_"+std::to_string(CurrentId)].push_back(std::to_string(CurrentNumPart));
                    ValueList["__id_"+std::to_string(CurrentId)].push_back(o);
                }
                CurrentNumPart = 0;
                decimalNum = 0;
            }else if (a == "("|| a !=")")
            {
                //KEEP AN EYE
                std::vector<std::string> a_;
                Hid++;
                if(CurrentId==0) PlannedOperation.push_back("__id_"+std::to_string(Hid));
                else ValueList["__id_"+std::to_string(CurrentId)].push_back("__id_"+std::to_string(Hid));
                CurrentId=Hid;
                ValueList["__id_"+std::to_string(CurrentId)] = a_;
                if(a=="(") Ftype["__id_"+std::to_string(CurrentId)] = "normal";
                else Ftype["__id_"+std::to_string(CurrentId)] = a;
            }else if (a == ")")
            {
                if(CurrentNumPart!= 0)ValueList["__id_"+std::to_string(CurrentId)].push_back(std::to_string(CurrentNumPart));
                CurrentNumPart = 0;
                decimalNum = 0;
                FinishedId.push_back(CurrentId);
                bool conflict = true;
                while(conflict)
                {
                    conflict=false;
                    for(const auto& a: FinishedId)
                    {
                        if(a == CurrentId)
                        {
                            conflict=true;
                            CurrentId--;
                        }
                    }
                }
            }
        }
    }
    if(CurrentId != 0)
    {
        //error
        throw std::runtime_error("Syntax Error");
    }
    if(CurrentNumPart!= 0)PlannedOperation.push_back(std::to_string(CurrentNumPart));
    CurrentNumPart = 0;
    decimalNum = 0;
    bool hasDoneDefiningValue = false;
    while(hasDoneDefiningValue != true)
    {
        hasDoneDefiningValue=true;
        // This loop run unitl the value list is solved
        for(int i = 1; i <= Hid; i++)
        {
            if(CalculatedValueList.find("__id_"+std::to_string(i)) == CalculatedValueList.end()) {
                //Not fully resolved
                bool FullyResolvedConstant=true;
                for(int el_el = 0; el_el < ValueList["__id_"+std::to_string(i)].size(); el_el++)
                {
                    const auto& el__ = ValueList["__id_"+std::to_string(i)].at(el_el);
                    try
                    {
                        /* code */
                        std::stod(el__); //check if it is a number
                    }
                    catch(const std::exception& e)
                    {
                        if(el__ != "+" && el__ != "-" && el__ != "*" && el__ != "/")
                        {
                            //ID or a function bracket
                            hasDoneDefiningValue=false;
                            if(CalculatedValueList.find(el__) == CalculatedValueList.end())
                            {
                                FullyResolvedConstant = false;
                            }else {
                                ValueList["__id_"+std::to_string(i)].at(el_el) = ValueList[el__].at(0);
                            }

                        }
                    }

                }
                if(FullyResolvedConstant == true)
                {
                    CalculatedValueList["__id_"+std::to_string(i)] = true;
                    //Perhaps it is time to solve this:
                    if(Ftype["__id_"+std::to_string(i)] == "normal") ValueList["__id_"+std::to_string(i)] = CalculateOperation(ValueList["__id_"+std::to_string(i)]);
                    else {
                        std::vector<std::string> Temp_Vec;
                        try {
                            /*std::string st_d = ValueList[el__].at(0);
                            while(ValueList.find(st_d) != ValueList.end()) {
                                st_d = ValueList[st_d].at(0);
                            }*/
                            Temp_Vec.push_back(std::to_string(FunctionBatchOne[Ftype["__id_"+std::to_string(i)]](std::stod(CalculateOperation(ValueList["__id_"+std::to_string(i)]).at(0)))));
                            ValueList["__id_"+std::to_string(i)] = Temp_Vec;
                        }catch(std::exception& e)
                        {
                            std::cout << e.what() << std::endl;
                            throw std::runtime_error(e.what());
                        }
                    }
                }
            }
        }
    }
        for(int el_el = 0; el_el < PlannedOperation.size(); el_el++)
        {
            const auto& el__ = PlannedOperation.at(el_el);
            try
            {
                /* code */
                std::stod(el__); //check if it is a number
            }
            catch(const std::exception& e)
            {
                if(el__ != "+" && el__ != "-" && el__ != "*" && el__ != "/")
                {
                    std::string st_d = ValueList[el__].at(0);
                    while(ValueList.find(st_d) != ValueList.end()) {
                        st_d = ValueList[st_d].at(0);
                        
                    }
                    //if(Ftype[el__] == "normal") 
                    PlannedOperation.at(el_el) = st_d;
                   /* else {
                        try
                        {
                            std::cout << st_d << std::endl;
                            //std::cout << ValueList[el__].at(0) <<std::endl << FunctionBatchOne[Ftype[el__]](std::stod(ValueList[el__].at(0))) << std::endl;
                            PlannedOperation.at(el_el) = std::to_string(FunctionBatchOne[Ftype[el__]](std::stod(st_d))); 
                        }
                        catch(std::exception& e)
                        {
                            std::cout << e.what() << std::endl;
                            throw std::runtime_error(e.what());
                        }
                        
                    }*/
                    //If I did everything correctly, then this one should only be replacing values
                }
            }
            
        }
    
    std::vector<std::string> NewValues = CalculateOperation(PlannedOperation);
    if(NewValues.size() != 1)
    {
        //Error
    }
    return std::stod(NewValues.at(0));
}