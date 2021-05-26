#include <omp.h>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

/* Global variables, Look at their usage in main() */
int image_height;
int image_width;
int image_maxShades;
int **inputImage;
int **outputImage;
int numChunks;

/* ****************Change and add functions below ***************** */

void edge_detect(int i, int numChunks) {
    /* Initialize Roberts cross mask for X and Y dimension */
    int maskX[2][2];
    int maskY[2][2];
    maskX[0][0] = maskY[0][1] = 1;
    maskX[0][1] = maskX[1][0] = maskY[0][0] = maskY[1][1] = 0;
    maskX[1][1] = maskY[1][0] = -1;

    int grad_x, grad_y, grad;
    for (int x = i; x < i + numChunks && x < image_height; x++) {
        for (int y = 0; y < image_width; ++y) {
            grad_x = grad_y = 0;
            if (x == image_height - 1 || y == image_width - 1)
                grad = 0; // image boundaries
            else {
                /* Gradient calculation in X dimension */
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        grad_x += inputImage[x + i][y + j] * maskX[i][j];
                    }
                }
                /* Gradient calculation in Y dimension */
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        grad_y += inputImage[x + i][y + j] * maskY[i][j];
                    }
                }
                /* Gradient magnitude */
                grad = (int) sqrt((grad_x * grad_x) + (grad_y * grad_y));
            }
            outputImage[x][y] = grad <= 255 ? grad : 255;
        }
    }
}

void compute_roberts_static() {
#pragma omp parallel for schedule(static, numChunks) shared(outputImage, inputImage, numChunks, image_height, image_width)
    for (int i = 0; i < image_height; i++) {
        std::cout << "Thread " << omp_get_thread_num() << " -> Processing Chunk starting at Row " << i << std::endl;
        edge_detect(i, numChunks);
        i += numChunks - 1;
    }
}

void compute_roberts_dynamic() {
    int i;
#pragma omp parallel for schedule(dynamic, numChunks) shared(inputImage, outputImage) private(i)
    for (i = 0; i < image_height; i++) {
        std::cout << "Thread " << omp_get_thread_num() << " -> Processing Chunk starting at Row " << i << std::endl;
        edge_detect(i, numChunks);
        i += numChunks - 1;
    }
}

/* **************** Change the function below if you need to ***************** */

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout
                << "ERROR: Incorrect number of arguments. Format is: <Input image filename> <Output image filename> <# of chunks> <a1/a2>"
                << std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file " << argv[1] << std::endl;
        return 0;
    }
    numChunks = std::atoi(argv[3]);

    std::cout << "Detect edges in " << argv[1] << " using OpenMP threads\n" << std::endl;

    /* ******Reading image into 2-D array below******** */

    std::string workString;
    /* Remove comments '#' and check image format */
    while (std::getline(file, workString)) {
        if (workString.at(0) != '#') {
            if (workString.at(1) != '2') {
                std::cout << "Input image is not a valid PGM image" << std::endl;
                return 0;
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

    inputImage = new int *[image_height];
    outputImage = new int *[image_height];
    for (int i = 0; i < image_height; ++i) {
        inputImage[i] = new int[image_width];
        outputImage[i] = new int[image_width];
    }

    /* Check image max shades */
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

    /************ Call functions to process image *********/
    std::string opt = argv[4];
    if (!opt.compare("a1")) {
        double dtime_static = omp_get_wtime();
        compute_roberts_static();
        dtime_static = omp_get_wtime() - dtime_static;
        std::cout << "Time: " << dtime_static << std::endl;
    } else {
        double dtime_dyn = omp_get_wtime();
        compute_roberts_dynamic();
        dtime_dyn = omp_get_wtime() - dtime_dyn;
        std::cout << "Time: " << dtime_dyn << std::endl;
    }

    /* ********Start writing output to your file************ */
    if (0 == omp_get_thread_num()) {
        std::ofstream ofile(argv[2]);
        if (ofile.is_open()) {
            ofile << "P2" << "\n" << image_width << " " << image_height << "\n" << image_maxShades << "\n";
            for (int i = 0; i < image_height; i++) {
                for (int j = 0; j < image_width; j++) {
                    ofile << outputImage[i][j] << " ";
                }
                ofile << "\n";
            }
        } else {
            std::cout << "ERROR: Could not open output file " << argv[2] << std::endl;
            return 0;
        }
    }
    return 0;
}