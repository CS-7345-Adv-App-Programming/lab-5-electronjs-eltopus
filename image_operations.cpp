#include "image.h"
#include "metrics.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include "states.cpp"

static Metrics* metric;


class ImageOperations {
    private:
        std::vector<std::string> splitBase64 (const std::string &s, char delim) {
            std::vector<std::string> result;
            std::stringstream ss (s);
            std::string item;
            while (getline (ss, item, delim)) {
                result.push_back(item);
            }

            return result;
        }


        std::vector<Image* > saves() {
            std::vector<Image* > current_states;
            for (auto i : States<Image*>::getCurrentStates()) {
                Image* current_state = new Image(*i);
                current_states.push_back(current_state); 
            }
            return current_states;
        }
       

        void restores(std::vector<Image *> oldStates) {
            States<Image*>::setCurrentStates(oldStates);
            
        }
        
        
        void Backups() {
            States<Image*>::addBackupState(this->saves());
        }

    public:

        ~ImageOperations() {
            for (auto i : States<Image*>::getCurrentStates()) delete i;
        }


        ImageOperations (){
           
        }

        ImageOperations (Image* state){
            
        }

        void createImages(char* buffer) {
            std::string base64(buffer);
            std::vector<std::string> base64Tokens = splitBase64(base64, ',');
            for (auto i : base64Tokens) {
                Image* image = new Image(i.c_str());
                States<Image*>::addCurrentState(image);
            }
            base64Tokens.clear();
            std::cout << "Current Image Size: " << States<Image*>::getCurrentStates().size() << std::endl;
           
        }
      

         //---------------------------------------------------------------------------------------------Operations begins

        const char* encodeBytes(){
            const char* result = metric->start_encodeBytes_Metrics(States<Image*>::getCurrentStates(), "encodeBytes");
            return result;
        }

        void grayscale_avgs()  {
            Backups();
            metric->start_grayscale_avgs_metrics(States<Image*>::getCurrentStates(), "grayscale_avg");
        }


        void grayscale_lums() {
            Backups();
            metric->start_grayscale_avgs_metrics(States<Image*>::getCurrentStates(), "grayscale_lums");
              
        }
        

        void colorMasks(float r, float g, float b) {
            Backups();
            metric->start_colorMasks_metrics(r, g, b, States<Image*>::getCurrentStates(), "colorMasks");
        }


        void encodeMessages(const char* message) {
            Backups();
            metric->start_encodeMessages_metrics(message, States<Image*>::getCurrentStates(), "encodeMessages");
        }

        char* decodeMessagesLib() {
            Backups();
            char* result = metric->start_decodeMessageLib_metrics(States<Image*>::getCurrentStates(), "decodeMessages");
            return result;
            
        }

        void std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc){
            Backups();
            metric->start_std_convolve_clamp_to_0_Metrics(channel, ker_w, ker_h, cr, cc, States<Image*>::getCurrentStates(), "std_convolve_clamp_to_0");
           
        }

        void std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc) {
            Backups();
            metric->start_std_convolve_clamp_to_border_Metrics(channel, ker_w, ker_h, cr, cc, States<Image*>::getCurrentStates(), "std_convolve_clamp_to_border");
           
        }

        void flipX()  {
            Backups();
            metric->start_flipX_Metrics(States<Image*>::getCurrentStates(), "flipX");

        }


        void flipY() {
            Backups();
            metric->start_flipY_Metrics(States<Image*>::getCurrentStates(), "flipY");
              
        }

        char* getMetrics() {
            std::string result;
            for (std::string r : metric->getPerformance()){
                result.append(r);
            }
            size_t len = result.length();
            char* buffer = (char*)malloc(sizeof(char) * len);
            strncpy(buffer, result.c_str(), len-1);
            buffer[len-1] = '\0';
            return buffer;
        }

        //---------------------------------------------------------------------------------------------Operations ended

         bool writes(const char* filename)  {
            States<Image*>::getCurrentStates()[0]->write(filename);
            return true;
        }

        void Undos() {
            if (States<std::vector<Image*>>::getBackupStates().size()) {
                std::cout << "Size not good" << std::endl;
                return;
            }
            std::vector<Image *> images = States<Image*>::getBackupStates().back();
            States<Image*>::pop_back();
            // std::cout << "Backup size: " << States<Image*>::getBackupStates().size() << std::endl; 
            try {
                // images[0]->write("../../Data/cPlusOutput/tiger_gray_lum_d.png") ;
                this->restores(images);
            } catch (...) {
                std::cout << "Exception occured" << std::endl;
                this->Undos();
            }
        }
        

};