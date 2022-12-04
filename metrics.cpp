#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <string.h>
#include <functional>
#include <thread>  

#include <iostream>
#include <fstream>
#include "image.h"
#include "states.cpp"
#include <atomic>


//static int indexN = 0;
static std::atomic<int> indexN{};
static std::atomic<char*> encodedString{};

class Metrics {

    private:
        bool fileExists(std::string& fileName) {
            return static_cast<bool>(std::ifstream(fileName));
        }

        static void generateCSVString(std::string functionName, std::string timeTaken) {
            std::stringstream ss;
            ss << "\"" << getIndex() << "\",";
            ss << "\"" << std::this_thread::get_id() << "\",";
            ss << "\"" << functionName << "\",";
            ss << "\"" << timeTaken << "\"";
            States<std::string>::addPerformance((ss.str() + "\n"));
            
        }

    public:
        

        Metrics(){

        };
        ~Metrics();

    
        // No args Image functions

        void start_grayscale_avgs_metrics(std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
               i->grayscale_avgs();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

         void start_grayscale_lums_metrics(std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
               i->grayscale_lums();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        void start_flipX_Metrics(std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
               i->flipX();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        void start_flipY_Metrics(std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
               i->flipY();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
            
        }

        //************************************************************************************************************************

        // void function with args

        void start_std_convolve_clamp_to_0_Metrics(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc, std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
                 i->std_convolve_clamp_to_0(channel, ker_w, ker_h, cr, cc);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        void start_std_convolve_clamp_to_border_Metrics(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc, std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
                  i->std_convolve_clamp_to_border(channel, ker_w, ker_h, cr, cc);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        //***************************************************************************************************************************

        void start_colorMasks_metrics(float r, float g, float b, std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
                   i->colorMasks(r, g, b);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        //***************************************************************************************************************************

        void start_encodeMessages_metrics(const char* message, std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
                   i->encodeMessages(message);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
        }

        //*********************************************************************************************************************************

        char* start_decodeMessageLib_metrics(std::vector<Image*> states_, std::string func) {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            char buffer[256] = {0};
            size_t messageLength = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto i : states_) {
                i->decodeMessages(buffer, &messageLength);
                break;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("%s Time measured for %s is: %.3f seconds.\n", oss.str().c_str(), func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
            char* p = &buffer[0];
            return p;
           
        }

        const char* start_encodeBytes_Metrics(std::vector<Image*> states_, std::string func){

            auto begin = std::chrono::high_resolution_clock::now();
            std::string base64Images_s;
            for (auto i : states_) {
                base64Images_s.append(i->encodeByteString() + ",");
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("Time measured for %s is: %.3f seconds.\n", func.c_str(), elapsed.count() * 1e-9);
            generateCSVString(func,std::to_string(elapsed.count() * 1e-9));
            return base64Images_s.c_str();

            
        }


        std::vector<std::string> getPerformance() {
            return States<std::string>::getPerformance();
        }

        static int getIndex(){
            indexN.store(++indexN);
            return indexN.load();
        }

};