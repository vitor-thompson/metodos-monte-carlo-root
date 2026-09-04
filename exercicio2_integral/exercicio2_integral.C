#include <TF1.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>

// Exemplo de funcao a ser integrada: f(x) = x^2
double minhaFuncao(double *x, double *par) {
    return x[0] * x[0];
}

void exercicio2_integral() {
    // Limites de integracao [a, b]
    double a = 0.0;
    double b = 2.0;

    // -------------------------------------------------------------
    // METODO 1: Integracao Nativa do ROOT (TF1::Integral)
    // -------------------------------------------------------------
    TF1 *f1 = new TF1("f1", minhaFuncao, a, b, 0);
    double integral_root = f1->Integral(a, b);

    // -------------------------------------------------------------
    // METODO 2: Integracao por Monte Carlo (Metodo da Media)
    // -------------------------------------------------------------
    int N = 100000; // Numero de pontos
    TRandom3 rand(0); // Gerador aleatorio
    double soma = 0.0;

    for (int i = 0; i < N; ++i) {
        double x_rand = rand.Uniform(a, b);
        soma += f1->Eval(x_rand);
    }

    double integral_mc = (b - a) * (soma / N);

    // -------------------------------------------------------------
    // Exibicao dos Resultados
    // -------------------------------------------------------------
    std::cout << "==========================================" << std::endl;
    std::cout << "      Calculo de Integral Definida        " << std::endl;
    std::cout << "      Funcao: f(x) = x^2 no intervalo [" << a << ", " << b << "]" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Valor Exato (Analitico): " << (std::pow(b, 3) - std::pow(a, 3)) / 3.0 << std::endl;
    std::cout << "Integral (ROOT TF1::Integral): " << integral_root << std::endl;
    std::cout << "Integral (Monte Carlo N=" << N << "): " << integral_mc << std::endl;
    std::cout << "==========================================" << std::endl;
}
