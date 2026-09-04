#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>

// Massa do elétron em keV (m_e = 511 keV)
const double m_e = 511.0;

// Fórmula teórica da Seção de Choque Diferencial de Klein-Nishina dSigma/dTheta (sem constantes físicas globais)
// x[0] -> Ângulo theta
// par[0] -> Energia do Fóton Incidente (E0 em keV)
double klein_nishina_pdf(double *x, double *par) {
    double theta = x[0];
    double E0 = par[0];
    double epsilon = E0 / m_e; // k0 / m_e

    // Razão P = E' / E0
    double P = 1.0 / (1.0 + epsilon * (1.0 - TMath::Cos(theta)));

    // dSigma/dOmega propenso a P^2 * (P + 1/P - sin^2(theta))
    double dSigma_dOmega = P * P * (P + (1.0 / P) - TMath::Power(TMath::Sin(theta), 2));

    // dSigma/dTheta = dSigma/dOmega * 2 * pi * sin(theta) (Elemento de ângulo sólido)
    return dSigma_dOmega * TMath::Sin(theta);
}

void exercicio3_compton(double E0_keV = 511.0, int nexp = 100000) {
    TRandom3 rand(0);

    // 1. Definição da Função Teórica no ROOT para busca do valor máximo e comparação
    TF1 *f_teorica = new TF1("f_teorica", klein_nishina_pdf, 0.0, TMath::Pi(), 1);
    f_teorica->SetParameter(0, E0_keV);

    // Encontra o valor máximo da distribuição numericamente para o método de Aceitação e Rejeição
    double y_max = f_teorica->GetMaximum(0.0, TMath::Pi()) * 1.05; // 5% de margem de segurança

    // 2. Histograma para armazenar o ângulo theta em radianos
    TH1D *h1 = new TH1D("h1", Form("Espalhamento Compton (E_{0} = %.1f keV, N = %d);#theta [rad];Eventos", E0_keV, nexp), 100, 0, TMath::Pi());

    int aceitos = 0;

    // 3. Método de Aceitação e Rejeição (Hit-or-Miss)
    while (aceitos < nexp) {
        double x_rand = rand.Uniform(0.0, TMath::Pi()); // theta aleatório in [0, pi]
        double y_rand = rand.Uniform(0.0, y_max);        // y aleatório in [0, y_max]

        double f_val = f_teorica->Eval(x_rand);

        if (y_rand <= f_val) {
            h1->Fill(x_rand);
            aceitos++;
        }
    }

    // 4. Salvar em Arquivo ROOT
    TFile *fOut = new TFile("histo2.root", "RECREATE");
    h1->Write();
    
    // 5. Visualização e Comparação com a Teoria
    TCanvas *c1 = new TCanvas("c1", "Klein-Nishina", 800, 600);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.7);
    h1->SetLineColor(kBlack);
    h1->Draw("E"); // Desenha com erros estatísticos (sqrt(N))

    // Normaliza a curva teórica para a área do histograma para sobreposição perfeita
    double bin_width = h1->GetBinWidth(1);
    f_teorica->SetLineColor(kRed);
    f_teorica->SetLineWidth(3);
    
    // Escala o gráfico teórico: Área_Histograma = nexp * bin_width
    TF1 *f_teorica_fit = new TF1("f_teorica_fit", [=](double *x, double *p){
        return f_teorica->Eval(x[0]) * (nexp * bin_width / f_teorica->Integral(0, TMath::Pi()));
    }, 0, TMath::Pi(), 0);
    
    f_teorica_fit->SetLineColor(kRed);
    f_teorica_fit->SetLineWidth(2);
    f_teorica_fit->Draw("SAME");

    TLegend *leg = new TLegend(0.55, 0.75, 0.88, 0.88);
    leg->AddEntry(h1, "Simulacao Monte Carlo", "lep");
    leg->AddEntry(f_teorica_fit, "Predicao Teorica (Klein-Nishina)", "l");
    leg->Draw();

    c1->SaveAs(Form("compton_E%.0f_N%d.png", E0_keV, nexp));

    std::cout << "==========================================" << std::endl;
    std::cout << "  Simulacao concluida com sucesso!" << std::endl;
    std::cout << "  Energia (E0): " << E0_keV << " keV" << std::endl;
    std::cout << "  Eventos Gerados: " << nexp << std::endl;
    std::cout << "==========================================" << std::endl;
}
