# AUTORIA
- Nicolas de Sousa Maia - 15481857
- Felipe Camargo Cerri - 15451119

# Sobre
Escolhemos duas estruturas de dados para representar o SET, a primeira foi uma árvore AVL, a segunda, 
por sua vez, foi uma árvore rubro-negra (RBT). As escolhas foram realizadas devido à propriedade de
auto-balanceamento presente nas duas árvores por meio das rotações e demais ajustes, de forma que 
essas estruturas são extremamente eficientes para as operações que queremos em nosso TAD SET, como 
busca, inserção, entre outros.

# Observações:
1. A pior altura possível para uma árvore AVL é de 1,44logn e da RBT é de 2logn 
    (seja n a quantidade de nós), isso dirá respeito à complexidade do pior caso
    na busca de um nó, o que na prática gera impacto no tempo de execução das demais 
    operações, especialmente comparativamente. No entanto, por simplicidade, consideraremos 
    apenas a quantidade de comparações necessária para o caso médio (log(n)).
2. Não estamos levando em conta a frequência em que os ajustes de árvore são necessários 
    em cada uma das implementações (rotação, inversão, etc.), mesmo que isso possa apresentar 
    diferença na performance prática comparativamente. Vale ressaltar que essas operações 
    possuem complexidade O(1) para serem realizadas.

# Complexidade
Faremos a análise das complexidades nas duas estruturas lado a lado:
- **avl_inserir()**:
    Possui complexidade para o caso médio O(2*log²(n)) = O(log²(n)), sendo n a quantidade 
    de nós da árvore, uma vez que faz uma busca em árvore binária até o local de inserção 
    do nó, que tem complexidade log(n), chamando depois, para calcular o FB do nó, duas vezes
    a função altura_no(), que também tem complexidade log(n), sendo a complexidade final:
    log(n)*(2*log(n)) = 2*log²(n) = O(log²(n)).

- **rbt_inseri**:
    Possui complexidade para o caso médio de O(2*log(n)) = O(log(n)), sendo n a quantidade 
    de nós da árvore, uma vez que faz uma busca em árvore binária até o local de inserção do 
    nó através de log(n) comparações, e consequente chamada da função arruma_arvore (O(1))
    log(n) vezes, sendo a complexidade final:
    log(n) + O(1)*log(n) = O(2*log(n)) = O(log(n)).

- **avl_remover**():
    Possui complexidade O(2*log²(n)) = O(log²(n)), por motivos análogos ao da inserção,
    sendo que nesse caso o cálculo da complexidade também envolve a função troca_max_esq,
    que tem complexidade log(n), sendo o cálculo final:
    log(n)*(2*log(n)) + log(n) = 2*log²(n) + log(n) = O(log²(n)).

- **rbt_remover**:
    Possui complexidade para o caso médio de O(5*log(n)) = O(log(n)), uma vez que será necessário primeiramente encontrar o nó que será removido em log(n) comparações acompanhado pelo ajuste na estrutura da árvore durante descida pela possível chamada das funções move_dir O(1) ou move_esq O(1) log(n) vezes, encontrado o nó a função acha_minimo e deleta_min serão chamadas e possuem complexidade log(n). Finalmente, na volta da recursão, a função arruma_arvore (O(1)) é chamada log(n) vezes, sendo o cálculo final:
    log(n) + O(1)*log(n) + 2*log(n) + O(1)*log(n) = 5*log(n) = O(log(n)).


- **avl_uniao():**
    Possui complexidade O(N*log²(n)), contudo, vejamos seu cálculo:
    N * (log²(n) + log(n)), pois faz uma operação de busca e outra de inserção.
    O que nos permite ver que é pior do que a anterior.

- **rbt_uniao():**
    Possui complexidade O(N*log(n)), contudo, vejamos seu cálculo:
    N * (log(n) + log(n)), pois faz uma operação de busca e outra de inserção.
    O que nos permite ver que é pior do que a anterior.

- **avl_inter():**
    Possui complexidade O(N*log²(n)), por motivos análogos à avl_uniao(), sendo o cálculo o
    mesmo.

- **rbt_inter():**
    Possui complexidade O(N*log(n)), por motivos análogos à rbt_uniao(), sendo o cálculo o
    mesmo.

- **avl_copiar():**
    Possui complexidade O(N*log²(n)), uma vez que para cada nó da árvore de origem, faz uma
    operação de inserção na árvore de destino.

- **rbt_copiar():**
    Possui complexidade O(N*log(n)), uma vez que para cada nó da árvore de origem, faz uma
    operação de inserção na árvore de destino.

- **buscar_no():**
    Possui complexidade O(2log(n)) para o caso médio, pois sempre faz duas comparações nas 
    chamadas recursivas em que entra. Vale ressaltar que a busca na AVL será levemente superior 
    em média devido à diferença da altura máxima entre as árvores.

## Funções de complexidade idêntica nas duas estruturas do SET:

- **avl_criar(), avl_vazia(), avl_cheia() / rbt_criar()**
    Possuem complexidade constante, já que só realizam uma quantidade limitada e pe-
    quena de operações.

- **imprimir():**
    Possui complexidade O(2N) = O(N), em que N é o número de elementos da árvore, uma vez que
    as única operações que realiza enquanto faz as visitas pelos nós é imprimí-los e
    verificar se não são nulos, visitando todos os nós.

