

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#define TIME 150
    

void create_first_gen(int** world, int height, int width) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((rand() % 10 == 5) or (rand() % 10 == 0)) {
                world[i][j] = 1;
            }
            else {
                world[i][j] = 0;
            }
        }
    }
}

void show_world(int** world, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (world[i][j] == 1) {
                std::cout << '*';

            }
            else {
                std::cout << ' ';
            }

        }
        std::cout << std::endl;
    }

}
void copy_world(int** world, int** copied, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copied[i][j] = world[i][j];

        }
    }
}
int get_X(int i, int width) {
    return (width + i) % width;
}
int get_Y(int j, int height) {
    return (height + j) % height;
}

int count_livings(int** world,int height,int width) {
    int alive = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            alive += world[i][j];
        }
    }
    return (int)alive;
}
int compare_worlds(int** world, int** world1, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (world[i][j] != world1[i][j]) {
                return -1;
            }
        }
        }
    return 0;
}
void next_step(int** world, int height, int width) {
    int** prev_world = new int* [height];
    for (int i = 0; i < height; i++) {
        prev_world[i] = new int[width];
    }
   
    copy_world(world, prev_world, height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int neighbors = 0;
            neighbors += prev_world[get_X(i - 1, width)][get_Y(j - 1, height)];
            neighbors += prev_world[get_X(i - 1, width)][get_Y(j, height)];
            neighbors += prev_world[get_X(i - 1, width)][get_Y(j + 1, height)];
            neighbors += prev_world[get_X(i + 1, width)][get_Y(j - 1, height)];
            neighbors += prev_world[get_X(i + 1, width)][get_Y(j + 1, height)];
            neighbors += prev_world[get_X(i + 1, width)][get_Y(j, height)];
            neighbors += prev_world[get_X(i, width)][get_Y(j - 1, height)];
            neighbors += prev_world[get_X(i, width)][get_Y(j + 1, height)];
            if ((prev_world[i][j] == 0) && (neighbors == 3)) {
                world[i][j] = 1;

            }
            else if ((neighbors > 3) || (neighbors < 2)) {
                world[i][j] = 0;
            }

            
        }
    }
}
void delete_world(int** world) {
    if (world != nullptr) {
        delete[] world;
    }
}
    int main()
{
        int world_height;
        int world_width;
        bool stable = false;
        bool periodic = false;
        std::cout << "Input height of world: ";
        std::cin >> world_height;
        std::cout << "Input width of world: ";
        std::cin >> world_width;
        int** world = new int* [world_height];
        for (int i = 0; i < world_height; i++) {
            world[i] = new int[world_width];
        }
        
        int** copied_world = new int* [world_height];
        for (int i = 0; i < world_height; i++) {
            copied_world[i] = new int[world_width];
        }
        int** copy_copy_world = new int* [world_height];
        for (int i = 0; i < world_height; i++) {
            copy_copy_world[i] = new int[world_width];
        }
        create_first_gen(world, world_height, world_width);
        int i = 0;
        while ((true) && (i < 2)) {
            
            
            copy_world(world, copied_world, world_height, world_width);
            show_world(world, world_height, world_width);
            next_step(world, world_height, world_width);
            stable = compare_worlds(world, copied_world, world_height, world_width) == 0;
            std::cout << "Alive: " << count_livings(world, world_height, world_width) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            i += 1;
            
            if (count_livings(world, world_height, world_width) == 0) {
                std::cout << "They are all dead" << std::endl;
                break;
            }
            if (stable == 1) {
                std::cout << "This is a stable configuration" << std::endl;
                break;
            }
            system("cls");
        }
        while ((true)) {

            copy_world(copied_world, copy_copy_world, world_height, world_width);
            copy_world(world, copied_world, world_height, world_width);
         
            show_world(world, world_height, world_width);
            next_step(world, world_height, world_width);
            periodic = compare_worlds(world, copy_copy_world, world_height, world_width) == 0;
            stable = compare_worlds(world, copied_world, world_height, world_width) == 0;
            std::cout << "Alive: " << count_livings(world, world_height, world_width) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            if (periodic == 1) {
                std::cout << "This is periodic configuration" << std::endl;
                break;
            }

            if (count_livings(world, world_height, world_width) == 0) {
                std::cout << "They are all dead" << std::endl;
                break;
            }
            if (stable == 1) {
                std::cout << "This is a stable configuration" << std::endl;
                break;
            }
            system("cls");
        }
        delete_world(world);
        delete_world(copied_world);
        delete_world(copy_copy_world);
}


