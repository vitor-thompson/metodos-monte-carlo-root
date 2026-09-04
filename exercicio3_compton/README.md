# Exercício 3: Simulação do Espalhamento Compton e Fórmula de Klein-Nishina

Este projeto implementa uma simulação de Monte Carlo do **Espalhamento Compton** ($\gamma + e^- \rightarrow \gamma' + e^-$) em C++ utilizando a biblioteca **CERN ROOT**. O programa simula a distribuição angular dos fótons espalhados com base na **Seção de Choque Diferencial de Klein-Nishina** e compara o histograma gerado por simulação com a curva teórica analítica.

---

## 📖 Descrição Teórica

### 1. Espalhamento Compton
O espalhamento Compton descreve o espalhamento inelástico de um fóton por um elétron livre (ou fracamente ligado). A variação do comprimento de onda do fóton dependente do ângulo de espalhamento $\theta$ é dada por:

$$\lambda' - \lambda = \frac{h}{m_e c} (1 - \cos\theta)$$

Em termos de energia, a energia do fóton espalhado $E'$ em função da energia incidente $E_0$ é dada por:

$$E' = \frac{E_0}{1 + \epsilon (1 - \cos\theta)}, \quad \text{onde } \epsilon = \frac{E_0}{m_e c^2}$$

### 2. Seção de Choque de Klein-Nishina
A probabilidade de um fóton ser espalhado em um determinado ângulo sólido $d\Omega$ é regida pela equação de **Klein-Nishina** (em unidades relativas $P = E'/E_0$):

$$\frac{d\sigma}{d\Omega} = \frac{r_e^2}{2} P^2 \left( P + \frac{1}{P} - \sin^2\theta \right)$$

Para obter a distribuição em função do ângulo polar $\theta$ ($d\sigma/d\theta$), integra-se sobre o ângulo azimutal $\phi$ ($d\Omega = 2\pi \sin\theta \, d\theta$), resultando em:

$$\frac{d\sigma}{d\theta} = 2\pi \sin\theta \cdot \frac{d\sigma}{d\Omega}$$

---

## 🛠️ Detalhes da Implementação (`exercicio3_compton.C`)

A simulação utiliza o **Método de Aceitação e Rejeição (Hit-or-Miss)** para gerar números aleatórios que seguem a distribuição de probabilidade teórica:

1. **Amostragem Aleatória:**
   * Sorteia-se um ângulo $\theta \in [0, \pi]$ uniforme via `TRandom3`.
   * Sorteia-se um valor $y \in [0, y_{\text{máx}}]$ uniforme.
2. **Critério de Aceitação:**
   * O evento é aceito se $y \le \frac{d\sigma}{d\theta}(\theta)$. Caso contrário, é rejeitado e um novo par é gerado.
3. **Parametrização Dinâmica:**
   * O código aceita a energia inicial do fóton ($E_0$ em keV) e o número de eventos ($N$) como argumentos configuráveis.
4. **Visualização:**
   * Gera o histograma $h(\theta)$ com erros estatísticos ($\sqrt{N}$) e sobrepõe a curva teórica de Klein-Nishina normalizada pela área do histograma.

---

## 💻 Como Executar no ROOT

### Pré-requisitos
* **CERN ROOT** instalado no sistema.

### Passos de Execução

Você pode rodar a função alterando a energia $E_0$ (em keV) e o número de eventos $N$ diretamente do terminal:

* **Caso Padrão ($E_0 = 511\text{ keV}$ e $N = 100.000$):**
  ```bash
  root -l 'exercicio3_compton.C(511.0, 100000)'
