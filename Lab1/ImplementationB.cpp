#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

/* Global variables, Look at their usage in main() */
int image_height;
int image_width;
int image_maxShades;
int **inputImage;
int **outputImage;
int num_threads;
int maxChunk;
std::mutex m;

/* ****************Change and add functions below ***************** */

typedef struct chunk {
    int start;
    int end;
} chunk;



void edge_detect(std::vector<chunk *> &chunks) {
    while (true) {
        std::lock_guard<std::mutex> lock(m);
        if (chunks.empty())
            break;
        else {
            chunk* this_chunk = chunks[0];
            chunks.erase(chunks.begin());
            /* Initialize Roberts cross mask for X and Y dimension */
            int maskX[2][2];
            int maskY[2][2];
            maskX[0][0] = maskY[0][1] = 1;
            maskX[0][1] = maskX[1][0] = maskY[0][0] = maskY[1][1] = 0;
            maskX[1][1] = maskY[1][0] = -1;

            int grad_x, grad_y, grad;
            for (int x = this_chunk->start; x < this_chunk->end; ++x) {
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
    }
}

void dispatch_threads() {
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    int last_chunk = div(image_height, maxChunk).rem;
    int rows_of_chunk = div(image_height, maxChunk).quot;
    if (last_chunk > 0) {
        rows_of_chunk++;
        last_chunk = image_height - (maxChunk--) * rows_of_chunk;
    }
    int counter = 0;
    std::vector<chunk *> chunks;
    for (int i = 0; i < maxChunk; i++) {
        auto *ch = new chunk{};
        ch->start = counter;
        ch->end = counter + rows_of_chunk;
        chunks.push_back(ch);
        counter += rows_of_chunk;
    }
    if (last_chunk > 0) {
        auto *ch = new chunk{};
        ch->start = counter;
        ch->end = counter + last_chunk;
        chunks.push_back(ch);
        maxChunk++;
    }
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(edge_detect, std::ref(chunks));
    }
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
}

/* ****************Need not to change the function below ***************** */

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout
                << "ERROR: Incorrect number of arguments. Format is: <Input image filename> <Output image filename> <# of Threads> <# of Chunks>"
                << std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file " << argv[1] << std::endl;
        return 0;
    }
    num_threads = std::atoi(argv[3]);
    /* maxChunk is total number of chunks to process */
    maxChunk = std::atoi(argv[4]);

    std::cout << "Detect edges in " << argv[1] << " using " << num_threads << " threads\n" << std::endl;

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

    /************ Function that creates threads and manage dynamic allocation of chunks *********/
    dispatch_threads();

    /* ********Start writing output to your file************ */
    std::ofstream ofile(argv[2], std::ios::binary);
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
    return 0;
}