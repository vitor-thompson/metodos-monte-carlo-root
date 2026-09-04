#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <vector>

void buffon_pi() {
    // Parâmetros geométricos da simulação (comprimento da agulha e distância entre linhas)
    double l = 1.0; // Comprimento da agulha
    double d = 2.0; // Distância entre as linhas (l <= d)

    // Valores de N solicitados
    std::vector<int> N_values = {10, 50, 100, 1000};

    // Gerador de números aleatórios com semente pseudo-aleatória
    TRandom3 rand(0);

    std::cout << "==========================================" << std::endl;
    std::cout << "   Simulacao da Agulha de Buffon no ROOT  " << std::endl;
    std::cout << "==========================================" << std::endl;

    for (int N : N_values) {
        int m = 0; // Contador de cruzamentos com as linhas

        for (int i = 0; i < N; ++i) {
            // Posicao x do centro da agulha em relacao a linha mais proxima: x in [0, d/2]
            double x = rand.Uniform(0.0, d / 2.0);

            // Angulo theta formado entre a agulha e as linhas: theta in [0, pi/2]
            double theta = rand.Uniform(0.0, TMath::Pi() / 2.0);

            // Condicao de cruzamento da linha
            if (x <= (l / 2.0) * TMath::Sin(theta)) {
                m++;
            }
        }

        // Calculo da estimativa de Pi
        if (m > 0) {
            double pi_est = (2.0 * N / m) * (l / d);
            double erro = TMath::Abs(pi_est - TMath::Pi());
            
            std::cout << "N = " << N 
                      << " | Cruzamentos (m) = " << m 
                      << " | Pi Estimado = " << pi_est 
                      << " | Erro Absoluto = " << erro << std::endl;
        } else {
            std::cout << "N = " << N 
                      << " | Cruzamentos (m) = 0" 
                      << " | Pi Estimado = Indefinido (divisao por zero)" << std::endl;
        }
    }
}
