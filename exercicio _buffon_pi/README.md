# Exercício 1: Estimativa de $\pi$ via Experimento da Agulha de Buffon

Este projeto consiste em uma simulação de Monte Carlo para estimar o valor da constante matemática $\pi$ utilizando o clássico **Experimento da Agulha de Buffon**, implementado em C++ no ambiente do **CERN ROOT**.

---

## 📖 Descrição Teórica

O experimento proposto por Georges-Louis Leclerc (Conde de Buffon) em 1777 consiste em lançar uma agulha de comprimento $l$ sobre um plano marcado com linhas paralelas separadas por uma distância $d$ (onde $l \le d$).

A probabilidade $P$ de a agulha cruzar uma das linhas paralelas é dada por:

$$P = \frac{2l}{\pi d}$$

Ao realizar $N$ lançamentos aleatórios e contar o número $m$ de vezes em que a agulha cruza uma linha, a frequência relativa $\frac{m}{N}$ aproxima a probabilidade $P$. A partir dessa relação, podemos estimar o valor de $\pi$ usando a fórmula:

$$\pi \approx \left(\frac{2N}{m}\right) \cdot \left(\frac{l}{d}\right)$$

---

## 🛠️ Detalhes da Implementação (`buffon_pi.C`)

O código em ROOT C++ simula geometricamente a posição e orientação de cada agulha utilizando a classe `TRandom3`:

1. **Posição do centro da agulha ($x$):** Sorteada uniformemente no intervalo $x \in [0, d/2]$ em relação à linha paralela mais próxima.
2. **Ângulo da agulha ($\theta$):** Sorteado uniformemente no intervalo $\theta \in [0, \pi/2]$.
3. **Condição de Cruzamento:** A agulha cruza a linha se a seguinte relação for satisfeita:
   $$x \le \frac{l}{2} \sin(\theta)$$
4. **Execução e Amostragem:** A simulação roda sequencialmente para diferentes tamanhos de amostra:
   $$N \in \{10, 50, 100, 1000\}$$

---

## 💻 Como Executar no ROOT

### Pré-requisitos
* **CERN ROOT** instalado e configurado no seu sistema ou ambiente JupyterHub.
