# Trabalho Prático: Sistema de Gestão de Treinos Pessoais (SGTP)

## Objetivo do Sistema

O objetivo deste trabalho é desenvolver um sistema completo em C++ para que **qualquer pessoa possa gerenciar suas próprias rotinas de exercícios**. Imagine que você deseja abandonar as fichas de papel da academia e ter seu próprio controle digital, personalizável e inteligente. O sistema funcionará como uma "biblioteca pessoal" de exercícios, permitindo cadastrar suas atividades favoritas e combiná-las em fichas de treino para a semana (ex: "Segunda - Peito", "Terça - Cardio").

Além de apenas organizar os treinos, o grande diferencial do sistema será a capacidade de **estimar automaticamente** quanto tempo um treino vai durar e quantas calorias ele deve queimar. Para realizar isso, você utilizará conceitos fundamentais de Orientação a Objetos, especificamente **Herança** e **Polimorfismo**, pois precisará aplicar regras de cálculo diferentes dependendo se o exercício é aeróbico (Cardio) ou de musculação (Força), tratando-os de forma unificada dentro das fichas.

---

## Entidades e Regras de Negócio

Para modelar este problema, identificamos três conceitos principais que devem ser transformados em classes no seu código. Abaixo explicamos detalhadamente o papel de cada uma.

### 1. O Conceito de "Exercício" (Cardio e Força)
No mundo real, exercícios têm naturezas e métricas muito diferentes. Uma corrida na esteira é medida essencialmente pelo tempo e velocidade, enquanto um supino é medido por séries, repetições e carga. No seu sistema, você não pode misturar essas lógicas em uma única classe bagunçada.

Você deve criar uma classe base abstrata chamada `Exercicio` e duas classes filhas:

#### A. Exercício de Cardio
Esta classe representa todas as atividades de resistência cardiovascular e longa duração, como esteira, bicicleta ergométrica, elíptico ou pular corda.
*   **O que armazenar:** Além do nome e ID (que vêm da base), você precisa guardar a **Duração** (em minutos) e a intensidade, que mediremos em **Calorias por Minuto**.
*   **Cálculo de Tempo:** É direto. O tempo estimado do treino é exatamente a duração cadastrada.
*   **Cálculo de Calorias:** Multiplica-se a duração pelo gasto calórico por minuto.
    *   *Exemplo:* Se você cadastrar "Esteira" com 30 minutos e 12 cal/min, o sistema calculará 360 calorias.
*   **Exibição:** O método `exibirDetalhes()` deve mostrar o tipo (Cardio), nome, ID, status (Ativo/Inativo), duração e calorias por minuto.

#### B. Exercício de Força
Esta classe representa atividades de musculação, calistenia ou levantamento de peso. Aqui a lógica muda: o tempo não é fixo, ele depende de quantas repetições você faz e quanto descansa.
*   **O que armazenar:** Nome, ID, **Carga** (peso em kg), **Séries** (quantas vezes realiza o exercício), **Repetições** (quantos movimentos por série) e **Tempo de Descanso** (pausa entre séries em segundos).
*   **Cálculo de Tempo:** O sistema deve fazer uma estimativa. Assuma que cada repetição leva em média **3 segundos** para ser executada. O tempo total é a soma do tempo fazendo força mais o tempo descansando.
    *   *Fórmula:* `(Séries × Repetições × 3 seg) + (Séries × Tempo de Descanso)`.
    *   *Importante:* O resultado desta conta será em segundos. Lembre-se de converter para minutos (dividindo por 60.0) antes de retornar.
*   **Cálculo de Calorias:** Usaremos uma fórmula de estimativa baseada no volume de carga levantado.
    *   *Fórmula:* `Séries × Repetições × Carga × 0.15`.
*   **Exibição:** O método `exibirDetalhes()` deve mostrar o tipo (Força), nome, ID, status (Ativo/Inativo), carga, séries, repetições e tempo de descanso.

### 2. A Ficha de Treino
A Ficha é o "container" que agrupa os exercícios. Ela representa o treino de um dia específico.
*   **Estrutura:** Cada ficha deve ter um **ID único**, um **Nome** (ex: "Treino A - Superiores") e, o mais importante, uma **Lista de Exercícios**. Essa lista deve ser capaz de armazenar tanto exercícios de Cardio quanto de Força misturados (uso de ponteiros para a classe base).
*   **Responsabilidade:** A Ficha deve saber responder "Quanto tempo este treino vai levar?". Para isso, ela deve percorrer sua lista de exercícios, chamar o método de cálculo de cada um (polimorfismo) e somar os resultados.

### 3. O Histórico de Execução
O Histórico serve para "gamificar" e registrar o progresso. Ele é apenas um registro simples. Cada vez que o usuário seleciona a opção "Registrar Treino", o sistema cria uma entrada no histórico contendo: a Data/Hora atual, qual Ficha foi realizada, e quais foram os totais de tempo e calorias calculados naquele momento.

---

## O Desafio dos IDs e Persistência

Um dos maiores desafios deste trabalho é gerenciar os IDs (identificadores únicos) dos exercícios, especialmente porque eles precisam ser salvos em arquivo e recarregados depois sem perder a sequência.

### O Problema
Quando você cadastra um exercício novo, o sistema deve dar a ele o ID 1. O próximo será o 2, e assim por diante. Porém, quando você fecha o programa e abre de novo, o sistema precisa ler o arquivo e saber que o último ID usado foi o 2, para que o próximo cadastro receba o 3. Se ele começar do 1 de novo, você terá exercícios duplicados e suas fichas apontarão para os exercícios errados.

### A Solução Técnica
Você deve usar uma variável **estática** (`static int proximoId`) na classe `Exercicio` para controlar o contador global, e implementar **dois construtores** diferentes:

1.  **Construtor para Novos Cadastros:** Não recebe ID como parâmetro. Ele pega o valor de `proximoId`, atribui ao objeto e incrementa o contador.
2.  **Construtor para Leitura de Arquivo:** Recebe o ID como parâmetro. Ele atribui esse ID específico ao objeto e **NÃO** incrementa o contador automaticamente.

### Exemplo de Implementação

```cpp
// Arquivo Exercicio.h
class Exercicio {
protected:
    int id;
    string nome;
    bool ativo;
    
    // Variável compartilhada por TODAS as instâncias
    static int proximoId; 

public:
    // CONSTRUTOR 1: Para novos cadastros (gera ID automático)
    Exercicio(string n) {
        this->nome = n;
        this->ativo = true;
        this->id = proximoId++; // Pega o atual e incrementa
    }

    // CONSTRUTOR 2: Para leitura de arquivo (força um ID existente)
    Exercicio(int idExistente, string n, bool status) {
        this->id = idExistente;
        this->nome = n;
        this->ativo = status;
        
        // Lógica inteligente: se o ID lido for maior que o nosso contador,
        // atualizamos o contador para evitar conflitos futuros.
        if (idExistente >= proximoId) {
            proximoId = idExistente + 1;
        }
    }
    
    int getId() { return id; }
};

// Arquivo Exercicio.cpp
// Inicialização obrigatória da variável estática
int Exercicio::proximoId = 1;
```

**Importante:** Com essa lógica no construtor, você não precisa se preocupar em varrer a lista para achar o maior ID. A própria classe se ajusta à medida que você carrega os exercícios do arquivo.

---

## Funcionalidades e Menu

Seu programa deve exibir um menu principal no console com as seguintes opções:

### 1. Gerenciar Banco de Exercícios
*   **Cadastrar:** Pergunta se é Cardio ou Força, pede os dados e cria o objeto (usando o Construtor 1).
*   **Listar:** Mostra todos os exercícios **Ativos**. Exiba o ID, Nome e os detalhes (Duração/Calorias).
*   **Excluir (Lógico):** Pede um ID. O sistema busca o objeto e muda seu status para **Inativo**. Não use `delete` ou `remove` do vetor, pois isso quebraria as fichas que referenciam este exercício. Apenas filtre para não exibi-lo mais nas listagens de novos cadastros.

### 2. Gerenciar Fichas de Treino
*   **Criar Ficha:** Pede um nome e cria uma nova ficha vazia.
*   **Adicionar Exercício:**
    1. O usuário escolhe uma Ficha (pelo ID).
    2. O usuário escolhe um Exercício (pelo ID).
    3. O sistema adiciona o ponteiro do exercício na lista da ficha.
*   **Visualizar Fichas:** Lista todas as fichas cadastradas. Ao exibir uma ficha, mostre seus exercícios e, no final, os totais somados de Tempo e Calorias.

### 3. Registrar Execução (Treinar)
*   O usuário seleciona qual Ficha acabou de realizar.
*   O sistema calcula os totais atuais daquela ficha.
*   O sistema salva um registro no histórico contendo: Data/Hora atual, Nome da Ficha e os valores totais.

### 4. Consultar Histórico
*   Exibe a lista cronológica de execuções salvas, permitindo que o usuário veja seu histórico de treinos.

### 0. Sair
Salva todos os dados nos arquivos de texto e encerra o programa.

---

## Persistência de Dados (Arquivos)

O sistema deve ser capaz de salvar e recuperar seu estado. Você usará três arquivos de texto.

### 1. Arquivo `exercicios.txt`
Armazena o catálogo de exercícios.
*   **Formato:** `TIPO;ID;NOME;...;STATUS`
*   **Dica:** O primeiro campo (Tipo) serve para você saber qual classe instanciar (`new Cardio` ou `new Forca`) enquanto lê o arquivo.
*   **Exemplo:**
    ```text
    1;5;Esteira;30;12;1
    2;6;Supino;40;3;12;60;1
    ```

### 2. Arquivo `fichas.txt`
Armazena a estrutura das fichas. Como uma ficha tem vários exercícios, precisamos saber quantos ler.
*   **Formato:** `ID_FICHA;NOME_FICHA;TOTAL_EXERCICIOS;ID_EX_1;ID_EX_2;...`
*   **Exemplo:** `1;Treino A;3;5;6;8`
    *   Lê-se: Ficha 1 ("Treino A") tem **3** exercícios. Os IDs deles são 5, 6 e 8.
    *   Seu programa deve ler esses IDs, buscar os ponteiros correspondentes na lista de exercícios carregada e adicioná-los à ficha.

### 3. Arquivo `historico.txt`
Armazena o log de execuções.
*   **Formato:** `DATA;ID_FICHA;NOME_FICHA;TEMPO_TOTAL;CALORIAS_TOTAL`

---

### Tabela de Formato dos Arquivos

Para facilitar a implementação, abaixo está a especificação completa de cada arquivo com todos os campos na ordem correta:

#### `exercicios.txt`

| Campo | Tipo | Descrição | Exemplo |
|-------|------|-----------|---------|
| TIPO | int | 1 = Cardio, 2 = Força | 1 ou 2 |
| ID | int | Identificador único | 5 |
| NOME | string | Nome do exercício | "Esteira" |
| **Para Cardio (TIPO=1):** |
| DURACAO | int | Duração em minutos | 30 |
| CALORIAS_POR_MIN | double | Calorias por minuto | 12.0 |
| STATUS | int | 1 = Ativo, 0 = Inativo | 1 |
| **Para Força (TIPO=2):** |
| CARGA | double | Peso em kg | 40.0 |
| SERIES | int | Número de séries | 3 |
| REPETICOES | int | Repetições por série | 12 |
| DESCANSO | int | Tempo de descanso em segundos | 60 |
| STATUS | int | 1 = Ativo, 0 = Inativo | 1 |

**Exemplo completo:**
- Cardio: `1;5;Esteira;30;12.0;1` (6 campos)
- Força: `2;6;Supino;40.0;3;12;60;1` (8 campos)

#### `fichas.txt`

| Campo | Tipo | Descrição | Exemplo |
|-------|------|-----------|---------|
| ID_FICHA | int | Identificador único da ficha | 1 |
| NOME_FICHA | string | Nome da ficha | "Treino A" |
| TOTAL_EXERCICIOS | int | Quantidade de exercícios na ficha | 3 |
| ID_EX_1 | int | ID do primeiro exercício | 5 |
| ID_EX_2 | int | ID do segundo exercício | 6 |
| ID_EX_N | int | ID do N-ésimo exercício | 8 |

**Exemplo completo:**
- `1;Treino A;3;5;6;8` (6 campos: 3 fixos + 3 IDs de exercícios)

#### `historico.txt`

| Campo | Tipo | Descrição | Exemplo |
|-------|------|-----------|---------|
| DATA | string | Data e hora no formato DD/MM/AAAA HH:MM:SS | "01/01/2025 10:30:00" |
| ID_FICHA | int | ID da ficha realizada | 1 |
| NOME_FICHA | string | Nome da ficha realizada | "Treino A" |
| TEMPO_TOTAL | double | Tempo total em minutos | 45.5 |
| CALORIAS_TOTAL | double | Calorias totais | 320.75 |

**Exemplo completo:**
- `01/01/2025 10:30:00;1;Treino A;45.5;320.75` (5 campos)

**Observações importantes:**
- Todos os campos são separados por ponto e vírgula (`;`)
- Números decimais devem usar ponto (`.`) como separador
- Strings podem conter espaços
- Cada linha representa um registro completo

---

## Código Base (Esqueleto)

Para facilitar o início do desenvolvimento, será fornecido um projeto contendo a estrutura de pastas e arquivos (`.h` e `.cpp`) com as classes definidas, mas com os métodos vazios. Sua tarefa será implementar a lógica interna de cada método e garantir que tudo funcione conforme esta especificação.
