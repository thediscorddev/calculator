#include "../scr/FileManager.hpp"
std::string FileManager::MathJax = "";
void FileManager::PrepareFile()
{
    //std::ifstream mathjax("js/mathjax/es5/tex-mml-chtml.js");
    std::ifstream mathjax("mathjax.js");
    std::string jsContent((std::istreambuf_iterator<char>(mathjax)),
                          std::istreambuf_iterator<char>());
    MathJax = jsContent;
}