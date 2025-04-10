#include "GeneticAlgorithm.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <string>
#include <windows.h> // Для Windows API

using namespace std;

// ███████╗███████╗██╗  ██╗██╗   ██╗
// ██╔════╝██╔════╝╚██╗██╔╝╚██╗ ██╔╝
// █████╗  █████╗   ╚███╔╝  ╚████╔╝
// ██╔══╝  ██╔══╝   ██╔██╗   ╚██╔╝
// ██║     ███████╗██╔╝ ██╗   ██║
// ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝

class UltraVisualizer {
private:
    const string COLORS[6] = {"\033[31m", "\033[33m", "\033[32m", "\033[36m", "\033[34m", "\033[35m"};

    void clearScreen() {
        #ifdef _WIN32
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coord = {0, 0};
            DWORD count;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hStdOut, &csbi);
            FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
            SetConsoleCursorPosition(hStdOut, coord);
        #else
            cout << "\033[2J\033[1;1H";
        #endif
    }

    string getRandomColor() {
        return COLORS[rand() % 6];
    }

    void printWithBorder(const string& text) {
        string border(text.length(), '═');
        cout << "╔" << border << "╗" << endl;
        cout << "║" << text << "║" << endl;
        cout << "╚" << border << "╝" << endl;
    }

public:
    void showGeneration(int gen, const vector<int>& path, double dist, int max_gen) {
        clearScreen();

        // Header
        cout << getRandomColor();
        printWithBorder("  GENETIC TRAVELER 3000  ");
        cout << "\033[0m";

        // Generation info
        cout << "\n  🧬 \033[1mGeneration:\033[0m " << gen << "/" << max_gen << endl;
        cout << "  🏆 \033[1mBest distance:\033[0m " << fixed << setprecision(2) << dist << endl;

        // DNA visualization
        cout << "\n  \033[1mDNA Sequence:\033[0m\n  ";
        for (size_t i = 0; i < min(path.size(), size_t(15)); i++) {
            cout << getRandomColor() << path[i] << "\033[0m";
            if (i != min(path.size(), size_t(15)) - 1) cout << " -> ";
        }
        if (path.size() > 15) cout << " ...";
        cout << " -> " << getRandomColor() << path[0] << "\033[0m" << endl;

        // Progress bar
        float progress = float(gen)/max_gen;
        cout << "\n  \033[1mEvolution Progress:\033[0m\n  [";
        int barWidth = 50;
        for (int i = 0; i < barWidth; i++) {
            if (i < progress*barWidth) cout << "█";
            else cout << " ";
        }
        cout << "] " << int(progress*100.0) << "%\n";

        // Cool ASCII art
        cout << "\n  ";
        if (gen % 2 == 0) {
            cout << "   🔥\n  /|\\\n  / \\";
        } else {
            cout << "   ⚡\n  /|\\\n  / \\";
        }
    }

    void showFinalResult(const vector<int>& path, double dist, double time) {
        clearScreen();

        // Final header
        cout << "\033[35m";
        printWithBorder("  OPTIMAL ROUTE FOUND!  ");
        cout << "\033[0m";

        // Stats
        cout << "\n  ⏱ \033[1mTime:\033[0m " << fixed << setprecision(2) << time << "s" << endl;
        cout << "  📏 \033[1mDistance:\033[0m " << dist << endl;

        // Path visualization
        cout << "\n  \033[1m✨ Optimal Path:\033[0m\n  ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << getRandomColor() << path[i] << "\033[0m";
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << " -> " << getRandomColor() << path[0] << "\033[0m" << endl;

        // Final ASCII art
        cout << "\n  🚀 \033[32mMission Complete!\033[0m 🚀\n";
        cout << "     ______\n";
        cout << "   /       \\\n";
        cout << "  /         \\\n";
        cout << " /___________\\\n";
        cout << " |           |\n";
        cout << " |    WIN    |\n";
        cout << " |___________|\n";
    }
};

int main() {


    setlocale(LC_ALL, "en_US.UTF-8");

    // Для Windows: дополнительные настройки консоли
#ifdef _WIN32
    system("chcp 65001");  // Устанавливаем кодовую страницу UTF-8
    // Включаем обработку виртуального терминала (для цветного вывода)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hConsole, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, mode);
#endif
    srand(time(0));

    // Parameters
    const int NUM_CITIES = 25;
    const int POP_SIZE = 2050;
    const double MUTATION_RATE = 10.12;
    const int MAX_GENERATIONS = 50;

    // Initialize
    TSP tsp(NUM_CITIES);
    GeneticAlgorithm ga(tsp, POP_SIZE, MUTATION_RATE);
    UltraVisualizer viz;
    auto start = chrono::steady_clock::now();

    // Evolution loop
    for (int gen = 0; gen < MAX_GENERATIONS; gen++) {
        ga.run(1);

        auto best_path = ga.getBestSolution();
        double best_dist = tsp.calculateDistance(best_path);

        viz.showGeneration(gen+1, best_path, best_dist, MAX_GENERATIONS);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Results
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;

    auto final_path = ga.getBestSolution();
    double final_dist = tsp.calculateDistance(final_path);

    viz.showFinalResult(final_path, final_dist, elapsed.count());

    return 0;
}