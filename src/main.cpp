#if defined(_WIN32) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include <cstring>
#include <string>

class InputReader{
private:
    int expectedParamsCount_, optionalParamsCount_;
    char **expectedParams_, **optionalParams_;
    void deleteParams(char ***params, int count){
        for(int i = 0; i < count; i++)
            delete [] (*params)[i];
        delete [] *params;
    }
    void setParams(const char **params, int count, char ***internParams, int *internCount){
        if(*internCount > 0){
            deleteParams(internParams, *internCount);
        }
        *internCount = count;
        *internParams = new char*[count];
        for(int i = 0; i < count; i++){
            int len = std::strlen(params[i]);
            (*internParams)[i] = new char[len];
            strcpy_s((*internParams)[i], len+1, params[i]);
        }
    }
public:
    InputReader(){
        expectedParamsCount_ = 0;
        expectedParams_ = {};
        optionalParamsCount_ = 0;
        optionalParams_ = {};
    }
    ~InputReader(){
        deleteParams(&expectedParams_, expectedParamsCount_);
        deleteParams(&optionalParams_, optionalParamsCount_);
    }
    void setExpectedParams(const char **expectedParams, int count){
        setParams(expectedParams, count, &expectedParams_, &expectedParamsCount_);
    }
    void setOptionalParams(const char **optionalParams, int count){
        setParams(optionalParams, count, &optionalParams_, &optionalParamsCount_);
    }
    void printParams(){
        std::cout << "Expected Parameters: ";
        for(int i = 0; i < expectedParamsCount_; i++){
            std::cout << expectedParams_[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char** argv){
#if defined (_WIN32) && defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _WIN32 && _DEBUG

    InputReader reader;
    const int epCount = 3;
    const char *ep[epCount] = {"--load", "--save", "--generations"};
    int *test = new int;

    reader.setExpectedParams(ep, epCount);
    reader.printParams();
    bool validInput = true;
    for(int i = 1; i < argc; i++){
        //std::cout << argv[i] << std::endl;
        if(std::strcmp(argv[i], "--load") == 0){
            // load
        }
        if(std::strcmp(argv[i], "--save") == 0){
            // save
        }
        if(std::strcmp(argv[i], "--generations") == 0){
            // generations
        }
        if(std::strcmp(argv[i], "--measure") == 0){
            // save
        }
    }

    return 0;
}