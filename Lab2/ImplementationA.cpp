#include <iostream>
#include <fstream>
#include <sstream>
#include <mpi.h>

int *initialize(int value, int length)
{
    int *out = new int[length];
    for (int i = 0; i < length; i++)
    {
        out[i] = value;
    }
    return out;
}

int* get_image(char *filename, int *image_size)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "ERROR: Could not open file " << filename << std::endl;
        return nullptr;
    }
    std::string workString;
    /* Remove comments '#' and check image format */
    while (std::getline(file, workString))
    {
        if (workString.at(0) != '#')
        {
            if (workString.at(1) != '2')
            {
                std::cout << "Input image is not a valid PGM image" << std::endl;
                return nullptr;
            }
            else
            {
                break;
            }
        }
        else
        {
            continue;
        }
    }
    /* Check image size */
    int image_width, image_height;
    while (std::getline(file, workString))
    {
        if (workString.at(0) != '#')
        {
            std::stringstream stream(workString);
            int n;
            stream >> n;
            image_width = n;
            stream >> n;
            image_height = n;
            break;
        }
        else
        {
            continue;
        }
    }
    /* Check image max shades */
    int image_maxShades;
    while(std::getline(file,workString))
    {
        if( workString.at(0) != '#' ){
            std::stringstream stream(workString);
            stream >> image_maxShades;
            break;
        } else {
            continue;
        }
    }
    *image_size = image_height * image_width;
    /* Fill input image matrix */
    int *inputImage = new int[*image_size];
    int pixel_val;
    for (int i = 0; i < image_height; i++)
    {
        if (std::getline(file, workString) && workString.at(0) != '#')
        {
            std::stringstream stream(workString);
            for (int j = 0; j < image_width; j++)
            {
                if (!stream)
                    break;
                stream >> pixel_val;
                inputImage[i * image_width + j] = pixel_val;
            }
        }
        else
        {
            continue;
        }
    }
    file.close();
    return inputImage;
}

int *get_matrix(char *filename, int num_of_process)
{
    int *matrix = new int[num_of_process * num_of_process];
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "ERROR: Could not open file " << filename << std::endl;
        return nullptr;
    }
    std::string workString;
    int connectivity;
    int i = 0;
    while (std::getline(file, workString))
    {
        std::stringstream stream(workString);
        for (int j = 0; j < num_of_process; j++)
        {
            if (!stream)
                break;
            stream >> connectivity;
            matrix[i] = connectivity;
            i++;
        }
    }
    file.close();
    return matrix;
}

int main(int argc, char *argv[])
{
    int rank, num_of_processes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *image, *matrix, *sub_matrix, *sub_image;
    int image_size, average_size;
    if (rank == 0)
    {
        matrix = get_matrix(argv[2], num_of_processes);
        image = get_image(argv[1], &image_size);
        for (int i = 0; i < num_of_processes; i++){
            average_size = image_size / num_of_processes;
            MPI_Send(&average_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    /* Scatter Image */
    MPI_Recv(&average_size, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    sub_image = new int[average_size];
    sub_matrix = new int[num_of_processes];
    MPI_Scatter(matrix, num_of_processes, MPI_INT, sub_matrix, num_of_processes, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(image, average_size, MPI_INT, sub_image, average_size, MPI_INT, 0, MPI_COMM_WORLD);

    /* Calculate histogram per chunk */
    int *histogram = initialize(0, 256);
    for (int i = 0; i < average_size; i++)
    {
        if (!(sub_image[i] < 0) && !(sub_image[i] > 255))
            histogram[sub_image[i]]++;
    }

    /* Tarry's Algorithm */
    int parent;
    int* message = initialize(-1, 256);
    if (rank != 2)
    {
        MPI_Recv(message, 256, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        parent = status.MPI_SOURCE;
    }
    for (int i = 0; i < num_of_processes; i++)
    {
        //std::cout << "rank: " << rank << "index: " << i << "\n";
        if (sub_matrix[i] == 1 && i != parent)
        {
            MPI_Send(message, 256, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(message, 256, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (message[0] != -1)
            {
                for (int j = 0; j < 256; j++)
                {
                    histogram[j] += message[j];
                    message[j] = -1;
                }
            }
        }
    }
    if (rank != 2)
        MPI_Send(histogram, 256, MPI_INT, parent, 0, MPI_COMM_WORLD);
    else
    {
        std::ofstream output;
        output.open(argv[3]);
        for (int i = 0; i < 255; i++)
            output << histogram[i] << "\n";
        output << histogram[255];
    }
    MPI_Finalize();
    return 0;
}
