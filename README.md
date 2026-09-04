# Exercícios de Monte Carlo e Simulação com CERN ROOT

Repositório dedicado aos exercícios de métodos numéricos, simulações de Monte Carlo e gerador de eventos Pythia8.

---

### **Exercício 1: Estimativa de $\pi$ (Agulha de Buffon)**
* **Arquivo:** `buffon_pi.C`
* **O que faz:** Utiliza o método de Monte Carlo geométrico para simular o lançamento aleatório de agulhas de comprimento $l$ sobre linhas paralelas separadas por $d$. Conta quantas agulhas cruzam as linhas ($m$) para estimar o valor de $\pi$ através da fórmula $\pi \approx \frac{2N}{m} \cdot \frac{l}{d}$ para diferentes valores de $N$ ($10, 50, 100, 1000$).

---

### **Exercício 2: Integração Numérica por Monte Carlo**
* **Arquivo:** `exercicio2_integral.C`
* **O que faz:** Calcula a integral definida de uma função $f(x)$ no intervalo $[a, b]$. O código compara a integração adaptativa nativa do ROOT (`TF1::Integral`) com o método de Monte Carlo do valor médio, gerando números aleatórios uniformes e avaliando a precisão da aproximação.

---

### **Exercício 3: Espalhamento Compton (Klein-Nishina)**
* **Arquivo:** `exercicio3_compton.C`
* **O que faz:** Simula a distribuição angular ($\theta$) do espalhamento de fótons por elétrons livres utilizando o algoritmo de **Aceitação e Rejeição (Hit-or-Miss)**. Permite alterar a energia inicial do fóton ($E_0$) e o número de eventos ($N$), sobrepondo o histograma gerado à curva teórica de Klein-Nishina.

---

### **Exercício 4: Gerador de Eventos Pythia8**
* **Arquivo:** `exercicio4_pythia.C`
* **O que faz:** Simula a produção de pares de quarks top ($t\bar{t}$) a uma energia do centro de massa de $13\text{ TeV}$ usando o Pythia8 integrado ao ROOT. O código salva as partículas finais em um `TTree`, cria histogramas para $p_T$, $\eta$ e $\phi$, e aplica seleções/cortes com `TCut` para isolar sinais de múons.
