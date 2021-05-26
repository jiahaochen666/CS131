#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <omp.h>

int ** inputImage;
int chunkSize;
int *histogram;
int image_width, image_height;
char* path;
int image_size;

void get_image(char *filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file " << filename << std::endl;
    }
    std::string workString;
    /* Remove comments '#' and check image format */
    while (std::getline(file, workString)) {
        if (workString.at(0) != '#') {
            if (workString.at(1) != '2') {
                std::cout << "Input image is not a valid PGM image" << std::endl;
            } else {
                break;
            }
        } else {
            continue;
        }
    }
    /* Check image size */
    while (std::getline(file, workString)) {
        if (workString.at(0) != '#') {
            std::stringstream stream(workString);
            int n;
            stream >> n;
            image_width = n;
            stream >> n;
            image_height = n;
            break;
        } else {
            continue;
        }
    }
    /* Check image max shades */
    int image_maxShades;
    while (std::getline(file, workString)) {
        if (workString.at(0) != '#') {
            std::stringstream stream(workString);
            stream >> image_maxShades;
            break;
        } else {
            continue;
        }
    }
    /* Fill input image matrix */
    inputImage = new int *[image_height];
    for (int i = 0; i < image_height; ++i) {
        inputImage[i] = new int[image_width];
    }
    image_size = image_height * image_width;
    int pixel_val;
    for (int i = 0; i < image_height; i++) {
        if (std::getline(file, workString) && workString.at(0) != '#') {
            std::stringstream stream(workString);
            for (int j = 0; j < image_width; j++) {
                if (!stream)
                    break;
                stream >> pixel_val;
                inputImage[i][j] = pixel_val;
            }
        } else {
            continue;
        }
    }
    file.close();
}

void get_calc(int i){
    //std::cout << "thread" << omp_get_thread_num() << " do " << i << "\n";
}

void calc_hist()
{
    #pragma omp parallel
    #pragma omp single nowait
    {
        int count = 0;
        while (count < image_height){
            #pragma omp task firstprivate(count) shared(histogram, inputImage, image_height, chunkSize)
            {
                for (int x = count; x < count + chunkSize && x < image_height; x++){
                    for (int y = 0; y < image_width; y++){
                        int temp = inputImage[x][y];
                        if (temp >= 0 && temp < 256){
                            #pragma omp atomic update
                            histogram[temp]++;
                        }
                    }
                }
            }
            count += chunkSize;
        }
    }
#pragma omp barrier
if (0 == omp_get_thread_num()){
    std::ofstream output;
    output.open(path);
    for (int i = 0; i < 255; i++)
        output << histogram[i] << "\n";
    output << histogram[255];
    }
}

int main(int argc, char *argv[]) {
    get_image(argv[1]);
    chunkSize = std::atoi(argv[2]);
    path = argv[3];

    //std::cout << image_height << " " << image_width << " " << chunkSize;

    /* Calculate histogram per chunk */
    histogram = new int[256];
    for (int i = 0; i < 256; i++){
        histogram[i] = 0;
    }

    calc_hist();


    return 0;
}