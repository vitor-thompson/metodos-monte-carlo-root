# Exercício 2: Integração Numérica Definida via Método de Monte Carlo

Este projeto apresenta a implementação de um algoritmo de **integração numérica definida** utilizando o **Método de Monte Carlo** (Método do Valor Médio) em C++, integrado ao ambiente do **CERN ROOT**. O programa compara a aproximação estocástica com a integração adaptativa nativa da classe `TF1` do ROOT.

---

## 📖 Descrição Teórica

A integral definida de uma função real $f(x)$ em um intervalo $[a, b]$, dada por:

$$I = \int_{a}^{b} f(x) \, dx$$

pode ser interpretada estatisticamente através do **Teorema do Valor Médio para Integrais**. O valor médio da função no intervalo $[a, b]$ é definido como:

$$\langle f \rangle = \frac{1}{b - a} \int_{a}^{b} f(x) \, dx$$

No método de Monte Carlo da média, geramos $N$ números aleatórios $x_i$ distribuídos uniformemente no intervalo $[a, b]$. A integral é então estimada por:

$$I_{MC} \approx (b - a) \cdot \frac{1}{N} \sum_{i=1}^{N} f(x_i)$$

Pelo Teorema do Limite Central, o erro estatístico dessa aproximação escala com $\frac{1}{\sqrt{N}}$, tornando o método extremamente eficiente para integrais multidimensionais.

---

## 🛠️ Detalhes da Implementação (`exercicio2_integral.C`)

O programa foi desenvolvido para avaliar a função de teste $f(x) = x^2$ no intervalo $[0, 2]$:

1. **Método Nativo (`TF1::Integral`):** Utiliza o algoritmo adaptativo Gauss-Kronrod implementado na classe `TF1` do ROOT para obter a solução de alta precisão.
2. **Método de Monte Carlo:** Utiliza a classe `TRandom3` para sortear $N = 100.000$ pontos uniformemente no intervalo $[a, b]$, acumulando a soma $\sum f(x_i)$ para calcular a área aproximada.
3. **Solução Analítica:** O código calcula o valor exato $\int_0^2 x^2 dx = \left[ \frac{x^3}{3} \right]_0^2 = \frac{8}{3} \approx 2.66667$ para validação direta dos resultados.

---

## 💻 Como Executar no ROOT

### Pré-requisitos
* **CERN ROOT** instalado e configurado no ambiente.
