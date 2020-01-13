#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <iomanip>

int generate_one_random_number(int down_border, int up_border)
{
    std::random_device rd;
    std::uniform_int_distribution<int> uid(down_border, up_border);
    return uid(rd);
}

int process()
{
    const int N = 1000;
    const double exp = 2.71;
    double lam1 = 4.6;
    double lam2 = 3.2;
    double lam3 = 2.6;
    double input[N] = {0};
    double output1[N] = {0};
    double output2[N] = {0};
    double sum = 0;
    for (int i = 1; i < N; i++)
    {
        int x = 0;
        double p = pow(exp, -1 * lam1);
        double s = 1;
        do
        {
            x++;
            double u = (generate_one_random_number(0, 15345) % 11) * 0.1;
            s = s * u;
        } while (s >= p);
        input[i] = x - 1;
        if (input[i] >= 10) input[i] = 9;
        sum += x - 1;
    }
    std::cout << sum / N << std::endl;
    sum = 0;
    for (int i = 1; i < N; i++)
    {
        int x = 0;
        double p = pow(exp, -1 * lam2);
        double s = p;
        double u = (generate_one_random_number(0, 46578) % 11) * 0.1;
        while (u > s)
        {
            x++;
            p = p * lam2 / x;
            s += p;
        }
        output1[i] = x;
        sum += x;
    }
    std::cout << sum / N << std::endl;
    sum = 0;
    for (int i = 1; i < N; i++)
    {
        int x = 0;
        double p = pow(exp, -1 * lam3);
        double s = p;
        double u = (generate_one_random_number(0, 13278) % 11) * 0.1;
        while (u > s)
        {
            x++;
            p = p * lam3 / x;
            s += p;
        }
        output2[i] = x;
        sum += x;
    }
    std::cout << sum / N << std::endl;
    double sum_all = 0;
    double sum_1 = 0;
    double sum_2 = 0;
    int count[10] = {0};
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
    {
        sum_1 += i * input[i];
        sum_2 += input[i];
        if (input[i] < 10)
            count[int(input[i])]++;
    }
    double n = double(N);
    double new_sum = 0;
    for (int i = 0; i < 10; i++)
    {
        std::cout << i << ": " << count[i] << std::endl;
        new_sum += double(count[i] / n);
    }
    //std::cout << sum_2 / N << " -- " <<  << std::endl;
    std::cout << "\n" << std::fixed << new_sum << std::endl;
    if (count[1] > 200)
    {
        for (int i = 0; i < 200; i++)
            std::cout << "\n";
        process();
    }

    double S0[N] = {0}; // operator 1 busy
    double S1[N] = {0}; // operator 1 free
    double S2[N] = {0}; // operator 2 busy
    double S3[N] = {0}; // operator 2 free

    double sumS0 = 0;
    double sumS1 = 0;
    double sumS2 = 0;
    double sumS3 = 0;

    double sum_queue = 0;

    for (int i = 0; i < N; i++)
    {
        // Task could be done
        if (input[i] <= (output1[i] + output2[i]))
        {
            if (output1[i] != 0)
            {
                S0[i] = (input[i]) / output1[i];
                S1[i] = 1 - S0[i];
                S3[i] = 1;
            }
            else if (output2[i] != 0)
            {
                S2[i] = (input[i]) / output2[i];
                S3[i] = 1 - S2[i];
                S1[i] = 1;
            }
            else
            {
                S0[i] = S2[i] = 0;
                S1[i] = S3[i] = 1;
            }
            // Task should be distributed between two operators
            if (S0[i] >= 1 && output2[i] > 0)
            {
                if (output2[i] >= input[i])
                {
                    S2[i] = (input[i]) / output2[i];
                    S3[i] = 1 - S2[i];
                    S0[i] = 0;
                    S1[i] = 1;
                }
                else
                {
                    S0[i] = abs(input[i] - output2[i]) / output1[i];
                    S1[i] = 1 - S0[i];
                    S2[i] = abs(input[i] - output1[i]) / output2[i];
                    S3[i] = 1 - S2[i];
                }
            }
        }
        // Task could not be done
        else
        {
            S0[i] = S2[i] = 1;
            S1[i] = S3[i] = 0;
            double queue = input[i] - (output1[i] + output2[i]);
            if (i != N)
            {
                input[i + 1] += queue;
            }
            sum_queue += queue;
        }
        sumS0 += S0[i];
        sumS1 += S1[i];
        sumS2 += S2[i];
        sumS3 += S3[i];

    }


    for (int i = 0; i < N; i++)
    {
         std::cout <<  std::setprecision(3) << "input: " << input[i] << std::setw(13)
                   << "output1: " << output1[i] << std::setw(12) << "output2: " << output2[i]
                      << std::setw(12) << "S0: " << S0[i] << std::setw(4) << " (S1: " << S1[i]
                      << ")" << std::setw(12) << "S2: " << S2[i] << " (S3: " << S3[i] << ")" << std::endl;

}


    double p0 = lam1 / (lam2 + lam3);
        double p = (1 - p0) / (1 + lam2 / lam3);
        double p1 = (1 - p0) / (1 + lam2 / lam3) + p * lam2 / lam3 - (1 - p0) / (1 + lam2 / lam3) * p * lam2 / lam3;
        double p2 = (1 - p) / (1 + lam1 / lam3) * lam1 / lam3;
    std::cout << "\n";
    std::cout << "avg. sumS0 = " << sumS0 / N << "   (formula: " << p0 << ")" << std::endl;
    std::cout << "avg. sumS1 = " << sumS1 / N << "   (formula: " << 1 - p0 << ")" << std::endl;
    std::cout << "avg. sumS2 = " << sumS2 / N << "   (formula: " << p2 << ")" << std::endl;
    std::cout << "avg. sumS3 = " << sumS3 / N << "   (formula: " << 1 - p2 << ")" << std::endl;
    std::cout << "\n";
    std::cout << "avg. sum_queue = " << sum_queue / N << std::endl;


    //std::cout << sum_1 << " / " << sum_2 << " = " << sum_1 / sum_2 << std::endl;

    return 0;
}

int main()
{
    process();
    return 0;
}
