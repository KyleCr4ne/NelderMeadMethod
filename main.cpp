#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

double LeftBord = -50.0;
double RightBord = 100.0;
void start(std::vector<std::pair<std::pair<double, double>, double>> &simplex) {
    double Value;
    char c;

    double X1, Y1;
    std::cin >> X1 >> Y1 >> Value;
    simplex.push_back({{X1, Y1}, Value});

    double X2 = std::max(LeftBord, std::min(RightBord, X1 + 5));
    double Y2 = std::max(LeftBord, std::min(RightBord, Y1));

    std::cout << X2 << ' ' << Y2 << '\n';
    fflush(stdout);
    std::cin >> c;
    std::cin >> Value;
    if (c == '+') exit(0);
    simplex.push_back({{X2, Y2}, Value});

    double X3 = std::max(LeftBord, std::min(RightBord, X1));
    double Y3 = std::max(LeftBord, std::min(RightBord, Y1 + 5));

    std::cout << X3 << ' ' << Y3 << '\n';
    fflush(stdout);
    std::cin >> c;
    std::cin >> Value;
    if (c == '+') exit(0);
    simplex.push_back({{X3, Y3}, Value});
}

void sorting(std::vector<std::pair<std::pair<double, double>, double>> &simplex) {
    std::sort(simplex.begin(), simplex.end(), [&](std::pair<std::pair<double, double>, double> cur1, std::pair<std::pair<double, double>, double> cur2){return cur1.second < cur2.second;});
}

int main() {
    double alpha = 1.0, beta = 0.5, gamma = 2.0;
    char c;
    std::vector<std::pair<std::pair<double, double>, double>> simplex;
    start(simplex);
    while (true) {
        sorting(simplex);
        std::pair<double, double> Xc = {(simplex[1].first.first + simplex[2].first.first) / 2.0, (simplex[1].first.second + simplex[2].first.second) / 2.0};
        std::pair<double, double> Xr = {(1 + alpha) * Xc.first - alpha * simplex[0].first.first, (1 + alpha) * Xc.second - alpha * simplex[0].first.second};
        double valueR;
        std::cout << Xr.first << ' ' << Xr.second << '\n';
        fflush(stdout);
        std::cin >> c;
        std::cin >> valueR;
        if (c == '+') exit(0);
        if (valueR > simplex[0].second) {
            std::pair<double, double> Xe = {(1 - gamma) * Xc.first + gamma * Xr.first, (1 - gamma) * Xc.second + gamma * Xr.second};
            double valueE;
            std::cout << Xe.first << ' ' << Xe.second << '\n';
            fflush(stdout);
            std::cin >> c;
            std::cin >> valueE;
            if (c == '+') exit(0);
            if (valueE > valueR) {
                simplex[0].first.first = Xe.first;
                simplex[0].first.second = Xe.second;
                simplex[0].second = valueE;
            } else {
                simplex[0].first.first = Xr.first;
                simplex[0].first.second = Xr.second;
                simplex[0].second = valueR;
            }
        } else if (simplex[2].second > valueR && valueR > simplex[1].second) {
            simplex[0].first.first = Xr.first;
            simplex[0].first.second = Xr.second;
            simplex[0].second = valueR;
        } else if (simplex[1].second > valueR && valueR > simplex[0].second) {
            std::pair<double, double> tmp_point;
            double tmp_value;
            tmp_point.first = Xr.first;
            tmp_point.second = Xr.second;
            tmp_value = valueR;
            Xr.first = simplex[0].first.first;
            Xr.second = simplex[0].first.second;
            valueR = simplex[0].second;
            simplex[0].first.first = tmp_point.first;
            simplex[0].first.second = tmp_point.second;
            simplex[0].second = tmp_value;
            
            std::pair<double, double> Xs = {beta * simplex[0].first.first + (1 - beta) * Xc.first, beta * simplex[0].first.second + (1 - beta) * Xc.second};
            double valueS;
            std::cout << Xs.first << ' ' << Xs.second << '\n';
            fflush(stdout);
            std::cin >> c;
            std::cin >> valueS;
            if (c == '+') exit(0);
            if (valueS > simplex[0].second) {
                simplex[0].first.first = Xs.first;
                simplex[0].first.second = Xs.second;
                simplex[0].second = valueS;
            } else {
                for (int i = 0; i < 2; i++) {
                    simplex[i].first.first = simplex[2].first.first + (simplex[i].first.first - simplex[2].first.first) / 2.0;
                    simplex[i].first.second = simplex[2].first.second + (simplex[i].first.second - simplex[2].first.second) / 2.0;
                    double curS;
                    std::cout << simplex[i].first.first << ' ' << simplex[i].first.second << '\n';
                    fflush(stdout);
                    std::cin >> c;
                    std::cin >> curS;
                    if (c == '+') exit(0);
                    simplex[i].second = curS;
                }
            }
        } else if (simplex[0].second > valueR) {
            std::pair<double, double> Xs = {beta * simplex[0].first.first + (1 - beta) * Xc.first, beta * simplex[0].first.second + (1 - beta) * Xc.second};
            double valueS;
            std::cout << Xs.first << ' ' << Xs.second << '\n';
            fflush(stdout);
            std::cin >> c;
            std::cin >> valueS;
            if (c == '+') exit(0);
            if (valueS > simplex[0].second) {
                simplex[0].first.first = Xs.first;
                simplex[0].first.second = Xs.second;
                simplex[0].second = valueS;
            } else {
                for (int i = 0; i < 2; i++) {
                    simplex[i].first.first = simplex[2].first.first + (simplex[i].first.first - simplex[2].first.first) / 2.0;
                    simplex[i].first.second = simplex[2].first.second + (simplex[i].first.second - simplex[2].first.second) / 2.0;
                    double curS;
                    std::cout << simplex[i].first.first << ' ' << simplex[i].first.second << '\n';
                    fflush(stdout);
                    std::cin >> c;
                    std::cin >> curS;
                    if (c == '+') exit(0);
                    simplex[i].second = curS;
                }
            }
        }
        
    }

    return 0;
}