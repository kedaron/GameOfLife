#include "ParameterReader.h"
#include <iostream>
#include <cstring>


void ParameterReader::deleteParams(char ***params, int count){
    for(int i = 0; i < count; i++)
        delete [] (*params)[i];
    delete [] *params;
}
void ParameterReader::setParams(const char **params, int count, char ***internParams, int *internCount){
    if(*internCount > 0){
        deleteParams(internParams, *internCount);
    }
    *internCount = count;
    *internParams = new char*[count];
    for(int i = 0; i < count; i++){
        int len = std::strlen(params[i]);
        (*internParams)[i] = new char[len+1];
        strcpy_s((*internParams)[i], len+1, params[i]);
    }
}
bool ParameterReader::checkExpectedParams(char **argv, int argc) const{
    bool valid = true;
    for(int i = 0; i < expectedParamsCount_; i++){
        bool found = false;
        for(int j = 0; j < argc; j++){
            if(std::strcmp(expectedParams_[i], argv[j]) == 0){
                found = true;
                break;
            }
        }
        if(!found){
            valid = false;
            break;
        }
    }
    return valid;
}
ParameterReader::ParameterReader()
    : expectedParamsCount_(0), optionalParamsCount_(0), expectedParams_(nullptr), optionalParams_(nullptr)
{}
ParameterReader::~ParameterReader(){
    deleteParams(&expectedParams_, expectedParamsCount_);
    deleteParams(&optionalParams_, optionalParamsCount_);
}
void ParameterReader::setExpectedParams(const char **expectedParams, int count){
    setParams(expectedParams, count, &expectedParams_, &expectedParamsCount_);
}
void ParameterReader::setOptionalParams(const char **optionalParams, int count){
    setParams(optionalParams, count, &optionalParams_, &optionalParamsCount_);
}
bool ParameterReader::parseParams(char **argv, int argc){
    if(!checkExpectedParams(argv, argc)){
        return false;
    }
    for(int i = 1; i < argc; i++){ // i = 1 => first param is program name => skip
        if(argv[i][0] == '-' && argv[i][1] == '-'){
            params[argv[i]] = "";
            if((i < argc-1) && !(argv[i+1][0] && argv[i+1][1] == '-')){
                params[argv[i]] = argv[i+1];
            }
        }
    }
    return true;
}
void ParameterReader::printParams() const{
    for(auto it = params.begin(); it != params.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
}
void ParameterReader::printExpectedParams() const{
    std::cout << "Expected Parameters: ";
    for(int i = 0; i < expectedParamsCount_; i++){
        std::cout << expectedParams_[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Optional Parameters: ";
    for(int i = 0; i < optionalParamsCount_; i++){
        std::cout << optionalParams_[i] << " ";
    }
    std::cout << std::endl;
}
