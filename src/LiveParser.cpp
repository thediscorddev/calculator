#include "../scr/LiveParser.hpp"
LiveParser::LiveParser()
{

}
void LiveParser::InstantlyParseFunction(std::string newInput)
{
    if(newInput == "SPECIALLEFT")
    {
        position=(position>0)?position-1:0;
    }else if(newInput == "SPECIALRIGHT")
    {

    }else if(newInput == "SPECIALUP")
    {

    }else if(newInput == "SPECIALDOWN")
    {

    }else if(newInput == "SPECIALBACKSPACE")
    {

    }else {

    }
}
void LiveParser::ClearFunc()
{
    expressionId = 0;
    isNonNumeral = false;
    ExpressionList.clear();
    ArgList.clear();
}
double LiveParser::CalculateOperation()
{

}
Function_Composed LiveParser::getFunction()
{

} //if isNonNumber is true